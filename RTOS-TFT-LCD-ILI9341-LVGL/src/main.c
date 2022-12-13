/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include <asf.h>
#include <string.h>
#include <math.h>
#include "ili9341.h"
#include "lvgl.h"
#include "touch/touch.h"
#include "fundo_inicial.h"
#include "logo.h"
#include "logoAoLigar.h"
#include "icones.h"
#include "rec.h"
#include "reset.h"
#include "clock.h"
#include "branco.h"
#include "line.h"
#include "acelarando.h"
#include "desacelarando.h"
#include "logoConfig.h"
#include "rodaConfig.h"

// -------- SIMULA PULSO ---------
 
#include "arm_math.h"

#define TASK_SIMULATOR_STACK_SIZE (4096 / sizeof(portSTACK_TYPE))
#define TASK_SIMULATOR_STACK_PRIORITY (tskIDLE_PRIORITY)

#define VEL_MAX_KMH  5.0f
#define VEL_MIN_KMH  0.5f
//#define RAMP

/************************************************************************/
/* LCD / LVGL                                                           */
/************************************************************************/

#define LV_HOR_RES_MAX          (240)
#define LV_VER_RES_MAX          (320)
LV_FONT_DECLARE(cascadia20);
LV_FONT_DECLARE(cascadia25);
LV_FONT_DECLARE(cascadia17);
LV_FONT_DECLARE(cascadia65);

// declarar a tela como global e estï¿½tica
static lv_obj_t * scr0;  // screen 0  --- Tela de "descanï¿½o"
static lv_obj_t * scr1;  // screen 1  --- Tela principal
static lv_obj_t * scr2;  // screen 2  --- Tela de configuraï¿½ï¿½o

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];
static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
static lv_indev_drv_t indev_drv;

// globais 
lv_obj_t * labelBtn1, * labelBtnPlayPause;
lv_obj_t * labelClock, * labelKmValue, * labelMMSS, * labelAvarageSpeed, * labelAvarageSpeedFloat,* labelMode, * labelKm, * labelMMSSunit, * labelSpeedUnity, * labelCurrentSpeed, * labelCurrentSpeedUnity, * labelDiameter, * labelAvarageSpeedUnity, * labelBack, *labelDot,*labelCurrentSpeedFloat, * labelHorn, *labelKmDot, *labelKmhDot,  *labelKmFloat10, *labelKmFloat100;
lv_obj_t * acelerandoVerde;
lv_obj_t * desacelerandoRed;
lv_obj_t * rec_laranja;

volatile int gravando;
volatile int total_time_traj;


// Global que controla pausa ou nao do percurso
// Semáforo
SemaphoreHandle_t xSemaphoreSettings;
SemaphoreHandle_t xSemaphoreGoBack;
SemaphoreHandle_t xSemaphore1sec;
SemaphoreHandle_t xSemaphoreRotateTime;

SemaphoreHandle_t xSemaphoreREC;
SemaphoreHandle_t xSemaphoreRESET;
SemaphoreHandle_t xSemaphoreHorn;

// Fila
QueueHandle_t xQueueLCD;

typedef struct {
	float aceleracao;
	float velocidade;
	float distancia;
	float velocidade_media;
} data;

// RTC:
typedef struct  {
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t week;
	uint32_t hour;
	uint32_t minute;
	uint32_t seccond;
} calendar;

uint32_t current_hour, current_min, current_sec;

// Pino para a leitura do sensor PA19
#define SENSOR_PIO          PIOA
#define SENSOR_PIO_ID       ID_PIOA
#define SENSOR_PIO_IDX      19
#define SENSOR_IDX_MASK (1 << SENSOR_PIO_IDX)

#define BUZZER_PIO				PIOB
#define BUZZER_PIO_ID			ID_PIOB
#define BUZZER_PIO_IDX			2
#define BUZZER_PIO_IDX_MASK     (1 << BUZZER_PIO_IDX)

#define DELTA_CONSTANTE 0.1

// Diametrode de 20 inch
float RAIO = 0.508/2;

// Inicialmente definido como km/h
float unidade_amostragem = 1.0;

/************************************************************************/
/* RTOS                                                                 */
/************************************************************************/

#define TASK_LCD_STACK_SIZE                (1024*6/sizeof(portSTACK_TYPE))
#define TASK_LCD_STACK_PRIORITY            (tskIDLE_PRIORITY)

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,  signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName) {
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	for (;;) {	}
}

extern void vApplicationIdleHook(void) { }

extern void vApplicationTickHook(void) { }

extern void vApplicationMallocFailedHook(void) {
	configASSERT( ( volatile void * ) NULL );
}

void RTC_init(Rtc *rtc, uint32_t id_rtc, calendar t, uint32_t irq_type);
static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource);

/************************************************************************/
/* handler                                                               */
/************************************************************************/


void sensor_callback(void)
{

	// Caso borda de descida = pegar valor do contador
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xSemaphoreRotateTime , &xHigherPriorityTaskWoken);

}

void RTT_Handler(void) {
	uint32_t ul_status;

	/* Get RTT status - ACK */
	ul_status = rtt_get_status(RTT);
	
	/* IRQ due to Alarm */
	if ((ul_status & RTT_SR_ALMS) == RTT_SR_ALMS) {
		printf("\nalarme\n");
	}

}

void RTC_Handler(void) {
	uint32_t ul_status = rtc_get_status(RTC);
	
	/* seccond tick */
	if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC) {
		// o código para irq de segundo vem aqui
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphore1sec , &xHigherPriorityTaskWoken);
	}
	
	/* Time or date alarm */
	if ((ul_status & RTC_SR_ALARM) == RTC_SR_ALARM) {
		
	}

	rtc_clear_status(RTC, RTC_SCCR_SECCLR);
	rtc_clear_status(RTC, RTC_SCCR_ALRCLR);
	rtc_clear_status(RTC, RTC_SCCR_ACKCLR);
	rtc_clear_status(RTC, RTC_SCCR_TIMCLR);
	rtc_clear_status(RTC, RTC_SCCR_CALCLR);
	rtc_clear_status(RTC, RTC_SCCR_TDERRCLR);
}

static void play_pause_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		LV_LOG_USER("Clicked");
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphoreREC , &xHigherPriorityTaskWoken);
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		LV_LOG_USER("Toggled");
	}
}

static void roller_handler(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	if(code == LV_EVENT_VALUE_CHANGED) {
		char buf[32];
		lv_roller_get_selected_str(obj, buf, sizeof(buf));
		printf("\nSelected size: %s\n", buf);

		// ---- Atualiza Raio da bicicleta em metros (m)
		RAIO = (atoi(buf)*0.0254)/2;

		LV_LOG_USER("Selected size: %s\n", buf);
	}
}

static void back_handler (lv_event_t * e){
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_label_set_text_fmt(labelMode, "Ride");
		lv_scr_load(scr1);
		LV_LOG_USER("Clicked");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		LV_LOG_USER("Toggled");
	}
}

static void config_handler (lv_event_t * e){
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphoreSettings , &xHigherPriorityTaskWoken);
		printf("CLIQUEI CONFIG");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		LV_LOG_USER("Toggled");
	}
}

static void reset_handler(lv_event_t * e){
	lv_event_code_t code = lv_event_get_code(e);
	if(code == LV_EVENT_CLICKED) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphoreRESET, &xHigherPriorityTaskWoken);
		printf("CLIQUEI RESET");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		LV_LOG_USER("Toggled");
	}
}

static uint32_t active_index_1 = 0;
static void radio_event_handler(lv_event_t * e)
{
	
	static lv_style_t style_radio;
	static lv_style_t style_radio_chk;
	
	uint32_t * active_id = lv_event_get_user_data(e);
	lv_obj_t * cont = lv_event_get_current_target(e);
	lv_obj_t * act_cb = lv_event_get_target(e);
	lv_obj_t * old_cb = lv_obj_get_child(cont, *active_id);

	/*Do nothing if the container was clicked*/
	if(act_cb == cont) return;

	lv_obj_clear_state(old_cb, LV_STATE_CHECKED);   /*Uncheck the previous radio button*/
	lv_obj_add_state(act_cb, LV_STATE_CHECKED);     /*Uncheck the current radio button*/

	*active_id = lv_obj_get_index(act_cb);

	LV_LOG_USER("Selected radio buttons: %d, %d", (int)active_index_1);
	
	printf("Selected radio buttons: %d ", (int)active_index_1);

	if(active_index_1 == 0){
		// 1 km = 0,621371 milhas
		// ---- Unidade em Km/h ----
		unidade_amostragem = 1.0;

		}else{
		// ---- Unidade em mph ----
		unidade_amostragem = 0.621371;
	}

	LV_LOG_USER("Selected radio buttons: %d ", (int)active_index_1);
}

static void horn_handler (lv_event_t * e){
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphoreHorn , &xHigherPriorityTaskWoken);
		printf("CLIQUEI BUZINA");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		LV_LOG_USER("Toggled");
	}
}

/************************************************************************/
/* lvgl                                                                 */
/************************************************************************/

static void radiobutton_create(lv_obj_t * parent, const char * txt)
{
	lv_obj_t * obj = lv_checkbox_create(parent);
	lv_checkbox_set_text(obj, txt);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
	static lv_style_t style_radio;
	lv_style_init(&style_radio);
	lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);
	static lv_style_t style_radio_chk;
	lv_style_init(&style_radio_chk);
	lv_style_set_bg_img_src(&style_radio_chk, NULL);
	
	lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR);
	lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);

}

void tela_settings(lv_obj_t * scr){
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 0);
	lv_style_set_arc_rounded(&style, 0);
	lv_style_set_img_recolor_opa(&style, LV_OPA_30);
	lv_style_set_img_recolor(&style, lv_color_black());
		
	// ----------------	Branco	-----------
	lv_obj_t * white = lv_img_create(scr);
	lv_img_set_src(white, &branco);
	lv_obj_align(white, LV_ALIGN_CENTER, 0, 0);
	// ---------------------------------------------------
	
	// ----------------	Logo posicionada nas telas	-----------
	lv_obj_t * logoSettings = lv_img_create(scr);
	lv_img_set_src(logoSettings, &logoConfig);
	lv_obj_align(logoSettings, LV_ALIGN_BOTTOM_MID, 0, -10);
	// ---------------------------------------------------
	
	// ----------------	Linha do header  -----------
	lv_obj_t * lineDivisora = lv_img_create(scr);
	lv_img_set_src(lineDivisora, &line);
	lv_obj_align(lineDivisora, LV_ALIGN_TOP_LEFT, 0, 24);
	// ---------------------------------------------------
	
	// ----------------	Modo atual (config)-----------
	labelMode = lv_label_create(scr);
	lv_obj_align(labelMode, LV_ALIGN_TOP_MID, 5, 2);
	lv_obj_set_style_text_font(labelMode, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMode, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMode, "Settings");
	// ---------------------------------------------------
	
	// ------------------Botão Back ------------------------
	lv_obj_t * btnBack = lv_btn_create(scr);
	lv_obj_add_event_cb(btnBack, back_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btnBack, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btnBack, LV_ALIGN_TOP_LEFT, 6, 2);
	lv_obj_set_width(btnBack, 45);  lv_obj_set_height(btnBack, 30);
	lv_obj_add_style(btnBack, &style, 0);
	
	labelBack = lv_label_create(btnBack);
	lv_label_set_text(labelBack, LV_SYMBOL_LEFT);
	lv_obj_center(labelBack);
	//----------------------------------------------------------
	
	// ----------------	Diametro-----------
	labelDiameter = lv_label_create(scr);
	lv_obj_align(labelDiameter,  LV_ALIGN_CENTER, 0, -108);
	lv_obj_set_style_text_font(labelDiameter, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelDiameter, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelDiameter, "Diametro ['']");
	// ---------------------------------------------------
	
	// ----------------	Icones roda	-----------
	lv_obj_t * iconWheel = lv_img_create(scr);
	lv_img_set_src(iconWheel, &rodaConfig);
	lv_obj_align(iconWheel,  LV_ALIGN_CENTER, -50, -34);
	// ---------------------------------------------------
	
	// -----------------Roller Aro ---------------
	 lv_obj_t * roller1 = lv_roller_create(scr);
	 lv_roller_set_options(roller1,
	  "20\n"
	 "24\n"
	 "26\n"
	 "27,5\n"
	 "29",
	 LV_ROLLER_MODE_INFINITE);

	 lv_roller_set_visible_row_count(roller1, 3);
	 lv_obj_center(roller1);
	 lv_obj_add_event_cb(roller1, roller_handler, LV_EVENT_ALL, NULL);
	 lv_obj_align(roller1,  LV_ALIGN_CENTER, 40, -34);

	// -------------------------------------------
	
	
	//------------------Unidade da velocidade-----------------
	labelSpeedUnity = lv_label_create(scr);
	lv_obj_align(labelSpeedUnity,  LV_ALIGN_CENTER, 0, 36);
	lv_obj_set_style_text_font(labelSpeedUnity, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelSpeedUnity, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelSpeedUnity, "Unidade da velocidade");
	//--------------------------------------------------------
	
	// ---- Checkboxes as radio buttons para Unidade de Velocidade ---
	 
	 uint32_t i;
	 char buf[32];

	 lv_obj_t * cont1 = lv_obj_create(scr);
	 lv_obj_set_flex_flow(cont1, LV_FLEX_FLOW_ROW);
	 lv_obj_set_size(cont1, lv_pct(40), lv_pct(80));
	 lv_obj_add_event_cb(cont1, radio_event_handler, LV_EVENT_CLICKED, &active_index_1);

	 lv_snprintf(buf, sizeof(buf), "km/h");
	 radiobutton_create(cont1, buf);
	 
	 lv_snprintf(buf, sizeof(buf), "mph");
	 radiobutton_create(cont1, buf);

	 /*Make the first checkbox checked*/
	 lv_obj_add_state(lv_obj_get_child(cont1, 0), LV_STATE_CHECKED);
	 
	 lv_obj_align(cont1,  LV_ALIGN_CENTER, 0, 70);
	 lv_obj_set_width(cont1, 170);  lv_obj_set_height(cont1, 45);
	 lv_obj_clear_flag(cont1, LV_OBJ_FLAG_SCROLLABLE);
	 lv_obj_add_style(cont1, &style, 0);
	 
	//----------------------------------------------------
	
	
	
}
void lv_bike(lv_obj_t * scr) {
// ---------------- Estilo --------------------
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 1);
	lv_style_set_arc_rounded(&style, 0);
	lv_style_set_img_recolor_opa(&style, LV_OPA_30);
	lv_style_set_img_recolor(&style, lv_color_black());
	
// --------------------------------------------
// ----------------	Base tela main	-----------
// 	lv_obj_t * img = lv_img_create(lv_scr_act());
// 	lv_img_set_src(img, &fundo_inicial);
// 	lv_obj_align(img, LV_ALIGN_CENTER,0, 0);
// ---------------------------------------------------

// ----------------	Branco	-----------
	lv_obj_t * white = lv_img_create(scr);
	lv_img_set_src(white, &branco);
	lv_obj_align(white, LV_ALIGN_CENTER, 0, 0);
// ---------------------------------------------------


// ----------------	Conjunto de Icones tela main	-----------
	lv_obj_t * icons = lv_img_create(scr);
	lv_img_set_src(icons, &icones);
	lv_obj_align(icons, LV_ALIGN_CENTER,0, 30);
// ---------------------------------------------------

//------------------------ (o nï¿½mero) [km]--------------------
	labelKmValue = lv_label_create(scr);
	lv_obj_align(labelKmValue, LV_ALIGN_CENTER, -90, 85);
	lv_obj_set_style_text_font(labelKmValue, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelKmValue, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelKmValue, "%.1f",0.0);
// -------------------------------------------------

// ---------------------------------------------------
//------------------------ (os nï¿½meros do cronï¿½metro) [MM:SS]--------------------
	labelMMSS = lv_label_create(scr);
	lv_obj_align(labelMMSS, LV_ALIGN_CENTER, -5, 85);
	lv_obj_set_style_text_font(labelMMSS, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMMSS, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMMSS, "%d%d:%d%d",0,0,0,0);
// -------------------------------------------------


//------------------------ (o valor) [km/h]--------------------
	labelAvarageSpeed = lv_label_create(scr);
	lv_obj_align(labelAvarageSpeed, LV_ALIGN_CENTER, 80, 85);
	lv_obj_set_style_text_font(labelAvarageSpeed, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelAvarageSpeed, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelAvarageSpeed, "%d", 0);
// -------------------------------------------------

//------------------------ (o ponto) [km/h]--------------------
	labelKmDot = lv_label_create(scr);
	lv_obj_align(labelKmDot, LV_ALIGN_CENTER, 96, 85);
	lv_obj_set_style_text_font(labelKmDot, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelKmDot, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelKmDot, ".");
// -------------------------------------------------

//------------------------ (o valor float) [km/h]--------------------
	labelAvarageSpeedFloat = lv_label_create(scr);
	lv_obj_align(labelAvarageSpeedFloat, LV_ALIGN_CENTER, 106, 85);
	lv_obj_set_style_text_font(labelAvarageSpeedFloat, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelAvarageSpeedFloat, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelAvarageSpeedFloat, "%d", 0);
// -------------------------------------------------

// ----------------	Imagem da tela de ligar	-----------
// 	lv_obj_t * logoOn = lv_img_create(lv_scr_act());
// 	lv_img_set_src(logoOn, &logoAoLigar);																																																																																																																																																																																																																																																																																																																																																																																												
// 	lv_obj_align(logoOn, LV_ALIGN_CENTER, 0, 0);
// ---------------------------------------------------

// ----------------	Logo posicionada nas telas	-----------
	lv_obj_t * logoLetras = lv_img_create(scr);
	lv_img_set_src(logoLetras, &logo);
	lv_obj_align(logoLetras, LV_ALIGN_TOP_LEFT, 4, 4);
// ---------------------------------------------------


// ----------------	Modo atual (ride/config)-----------
	labelMode = lv_label_create(scr);
	lv_obj_align(labelMode, LV_ALIGN_TOP_MID, 4, 6);
	lv_obj_set_style_text_font(labelMode, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMode, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMode, "Ride");
// ---------------------------------------------------

// ----------------	LInha do header  -----------
	lv_obj_t * lineDivisora = lv_img_create(scr);
	lv_img_set_src(lineDivisora, &line);
	lv_obj_align(lineDivisora, LV_ALIGN_TOP_LEFT, 0, 24);
// ---------------------------------------------------


// ----------------	Reloginho	-----------
	lv_obj_t * clockzinho = lv_img_create(scr);
	lv_img_set_src(clockzinho, &clock);
	lv_obj_align(clockzinho, LV_ALIGN_TOP_LEFT, 63, 44);
// ---------------------------------------------------

//------------------------ Hora--------------------
	labelClock = lv_label_create(scr);
	lv_obj_align(labelClock, LV_ALIGN_TOP_LEFT, 84, 47);
	lv_obj_set_style_text_font(labelClock, &cascadia20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelClock, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelClock, "%d%d:%d%d:%d%d",2,3,4,5,4,7);
// -------------------------------------------------


//------------------------ Velocidade Instantanea--------------------
	labelCurrentSpeed = lv_label_create(scr);
	lv_obj_align(labelCurrentSpeed, LV_ALIGN_CENTER, -23, -60);
	lv_obj_set_style_text_font(labelCurrentSpeed, &cascadia65, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelCurrentSpeed, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelCurrentSpeed, "%d%d", 0,0);
// -------------------------------------------------
//------------------------ Velocidade Instantanea (o ponto)--------------------
	labelDot = lv_label_create(scr);
	lv_obj_align(labelDot, LV_ALIGN_CENTER, 18, -60);
	lv_obj_set_style_text_font(labelDot, &cascadia65, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelDot, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelDot, ".");
// -------------------------------------------------

//------------------------ Velocidade Instantanea Float--------------------
	labelCurrentSpeedFloat = lv_label_create(scr);
	lv_obj_align(labelCurrentSpeedFloat, LV_ALIGN_CENTER, 36, -60);
	lv_obj_set_style_text_font(labelCurrentSpeedFloat, &cascadia65, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelCurrentSpeedFloat, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelCurrentSpeedFloat, "%d", 0);
// ------------------------------------------------------------------
//------------------------ Unidade da Velocidade Instantanea--------------------
	labelCurrentSpeedUnity = lv_label_create(scr);
	lv_obj_align(labelCurrentSpeedUnity, LV_ALIGN_CENTER, 0, -18);
	lv_obj_set_style_text_font(labelCurrentSpeedUnity, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelCurrentSpeedUnity, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelCurrentSpeedUnity, "Km/h");
// -------------------------------------------------


// ----------------	Flecha acelarando verde	-----------
	acelerandoVerde = lv_img_create(scr);
	lv_img_set_src(acelerandoVerde, &acelarando); 
	lv_obj_align(acelerandoVerde,  LV_ALIGN_CENTER, 90, -60);
	lv_obj_add_flag(acelerandoVerde, LV_OBJ_FLAG_HIDDEN);
// ---------------------------------------------------

// ------------------Botão Buzina (horn) ------------------------
	lv_obj_t * btnHorn = lv_btn_create(scr);
	lv_obj_add_event_cb(btnHorn, horn_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btnHorn, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btnHorn,  LV_ALIGN_CENTER, -90, -105);
	lv_obj_set_width(btnHorn, 45);  lv_obj_set_height(btnHorn, 30);
	lv_obj_add_style(btnHorn, &style, 0);

	labelHorn = lv_label_create(btnHorn);
	lv_label_set_text(labelHorn, LV_SYMBOL_VOLUME_MAX);
	lv_obj_center(labelHorn);
//----------------------------------------------------------

// ----------------	Flecha Desacelarando vermelha	-----------
	desacelerandoRed = lv_img_create(scr);
	lv_img_set_src(desacelerandoRed, &desacelarando);
	lv_obj_align(desacelerandoRed,  LV_ALIGN_CENTER, -90, -60);
	lv_obj_add_flag(desacelerandoRed, LV_OBJ_FLAG_HIDDEN);
// ---------------------------------------------------

// ------------------Botão Config ------------------------
	lv_obj_t * btn1 = lv_btn_create(scr);
	lv_obj_add_event_cb(btn1, config_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btn1, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btn1, LV_ALIGN_TOP_RIGHT, 0, 4);
	lv_obj_set_width(btn1, 45);  
	lv_obj_set_height(btn1, 30);
	lv_obj_add_style(btn1, &style, 0);
		
	labelBtn1 = lv_label_create(btn1);
	lv_label_set_text(labelBtn1, LV_SYMBOL_SETTINGS);
	lv_obj_center(labelBtn1);
	
	
//----------------------------------------------------------

// ----------------	LInha do footter  -----------
	lv_obj_t * lineDivisoraF = lv_img_create(scr);
	lv_img_set_src(lineDivisoraF, &line);
	lv_obj_align(lineDivisoraF, LV_ALIGN_BOTTOM_MID, 0, -35);
// ---------------------------------------------------

// ----------------Rec laranja (gravando) ---------------------
	rec_laranja = lv_img_create(scr);
	lv_img_set_src(rec_laranja, &rec);
	lv_obj_align(rec_laranja, LV_ALIGN_BOTTOM_MID,0,-2);
	lv_obj_add_flag(rec_laranja, LV_OBJ_FLAG_HIDDEN);
//----------------------------------------------------------

// ----------------Reset ---------------------
	LV_IMG_DECLARE(imgReset);

	static lv_style_t style_def;
	lv_style_init(&style_def); //Darken the button when pressed and make it wider
	
	static lv_style_t style_pr;
	lv_style_init(&style_pr);
	lv_style_set_img_recolor_opa(&style_pr, LV_OPA_30);
	lv_style_set_img_recolor(&style_pr, lv_color_black());

	lv_obj_t * btnReset = lv_imgbtn_create(scr);
	lv_imgbtn_set_src(btnReset, LV_IMGBTN_STATE_RELEASED, NULL, NULL, &reset);
	lv_obj_add_event_cb(btnReset, reset_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_style(btnReset, &style, LV_STATE_PRESSED);
	lv_obj_align_to(btnReset, rec_laranja, LV_ALIGN_BOTTOM_LEFT, -180, 96);
	
//----------------------------------------------------------


// ------------------Botï¿½o Play/Pause ------------------------
	lv_obj_t * btn_play_pause = lv_btn_create(scr);
	lv_obj_add_event_cb(btn_play_pause, play_pause_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btn_play_pause, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btn_play_pause, LV_ALIGN_BOTTOM_RIGHT, -22, -4);
	lv_obj_set_width(btn_play_pause, 35);  lv_obj_set_height(btn_play_pause, 32);
	lv_obj_add_style(btn_play_pause, &style, 0);

	labelBtnPlayPause = lv_label_create(btn_play_pause);
	lv_label_set_text(labelBtnPlayPause, LV_SYMBOL_PLAY);
	lv_obj_center(labelBtnPlayPause);
//----------------------------------------------------------

	//------------------------ (a unidade de medida) [km]--------------------
	labelKm = lv_label_create(scr);
	lv_obj_align(labelKm, LV_ALIGN_CENTER, -96, 105);
	lv_obj_set_style_text_font(labelKm, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelKm, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelKm, "km");
	// -------------------------------------------------

	//------------------------ (a unidade) [km/h]--------------------
	labelAvarageSpeedUnity = lv_label_create(scr);
	lv_obj_align(labelAvarageSpeedUnity, LV_ALIGN_CENTER, 90, 105);
	lv_obj_set_style_text_font(labelAvarageSpeedUnity, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelAvarageSpeedUnity, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelAvarageSpeedUnity, "km/h");
	// -------------------------------------------------

	//------------------------ (a unidade do cronï¿½metro) [MM:SS]--------------------
	labelMMSSunit = lv_label_create(scr);
	lv_obj_align(labelMMSSunit, LV_ALIGN_CENTER, -5, 105);
	lv_obj_set_style_text_font(labelMMSSunit, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMMSSunit, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMMSSunit, "mm:ss");
	// -------------------------------------------------
}

/************************************************************************/
/* FUNCTIONS                                                            */
/************************************************************************/

/**
* raio 20" => 50,8 cm (diametro) => 0.508/2 = 0.254m (raio)
* w = 2 pi f (m/s)
* v [km/h] = (w*r) / 3.6 = (2 pi f r) / 3.6
* f = v / (2 pi r 3.6)
* Exemplo : 5 km / h = 1.38 m/s
*           f = 0.87Hz
*           t = 1/f => 1/0.87 = 1,149s
*/

float mod(float number){
	if(number < 0){
		return (-1)*number;
	}
	return number;
}


float kmh_to_hz(float vel, float raio) {
	float f = vel / (2*PI*raio*3.6);
	return(f);
}

void config_sensor(){
	// ------- Configura pino de leitura do sensor
	pmc_enable_periph_clk(SENSOR_PIO_ID);
	
	pio_configure(SENSOR_PIO, PIO_INPUT, SENSOR_IDX_MASK, PIO_DEFAULT);
	pio_set_debounce_filter(SENSOR_PIO, SENSOR_IDX_MASK, 60);
	
	pio_handler_set(SENSOR_PIO,
	SENSOR_PIO_ID,
	SENSOR_IDX_MASK,
	PIO_IT_FALL_EDGE,
	sensor_callback);
	
	pio_enable_interrupt(SENSOR_PIO, SENSOR_IDX_MASK);
	pio_get_interrupt_status(SENSOR_PIO);
	
	NVIC_EnableIRQ(SENSOR_PIO_ID);
	NVIC_SetPriority(SENSOR_PIO_ID, 4);
}

void set_buzzer(void){
	// coloca 1 no pino do BUZZER.
	pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(void){
	// coloca 0 no pino do BUZZER
	pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void tone(int freq, int time){ // freq em Hz , time em ms
	//contar quantos pulsos (freq) existem dentro de um tempo (time) e
	//ent?o fazer um loop que gere a quantidade de pulsos (na frequ?ncia certa).
	float periodo = 1.0/freq;
	int quantidade_de_pulsos = (freq*time)/1000;
	for (int i = 0; i < quantidade_de_pulsos; i++){
		set_buzzer();
		delay_us(periodo*500000); //T*10^6/2
		clear_buzzer();
		delay_us(periodo*500000); //T*10^6/2
	}
}

/************************************************************************/
/* TASKS                                                                */
/************************************************************************/

static void task_rtc(void *pvParameters) {
	
	printf("\n Init task rtc \n");
	
	char str_hora[128] , str_min[128] , str_seg[128];
	
	// STRING hora
	char str_time[128];
	
	/** Configura RTC */
	calendar rtc_initial = {2018, 3, 19, 12, 2, 5 ,1};
	RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_SECEN);

	rtc_get_time(RTC, &current_hour, &current_min, &current_sec);
	
	sprintf(str_time, "%d:%d:%d", current_hour , current_min , current_sec);
	lv_label_set_text_fmt(labelClock, "%s", str_time);
	
	for (;;)  {
		
		if(xSemaphoreTake(xSemaphore1sec , 0 )){
			
			// ------------- Atualiza time - GLOBAL -------------
			rtc_get_time(RTC, &current_hour, &current_min, &current_sec);
			
			if(current_hour < 10){
				sprintf(str_hora, "0%d", current_hour);
				}else{
				sprintf(str_hora, "%d", current_hour);
			}
			
			if(current_min < 10){
				sprintf(str_min, "0%d", current_min);
				}else{
				sprintf(str_min, "%d", current_min);
			}
			
			if(current_sec < 10){
				sprintf(str_seg, "0%d", current_sec);
				}else{
				sprintf(str_seg, "%d", current_sec);
			}
			
			sprintf(str_time, "%s:%s:%s", str_hora , str_min , str_seg);
			lv_label_set_text_fmt(labelClock, "%s", str_time);
			
			// -------------------------------------------------
			
			
			// ------------- Atualiza time - TRAJETO -------------
			if(gravando){
				char str_trajec_min[128] , str_trajec_sec[128] , str_trajec_time[256];
				
				total_time_traj++;
				
				int time_min = (total_time_traj/60) % 60;
				int time_sec = total_time_traj % 60;
				
				//printf("\n [TRAJETO] total : %d \n min: %d \n sec: %d \n", total_time_traj , time_min , time_sec);
				
				if(time_min < 10){
					sprintf(str_trajec_min, "0%d", time_min);
					}else{
					sprintf(str_trajec_min, "%d", time_min);
				}
				
				if(time_sec < 10){
					sprintf(str_trajec_sec, "0%d", time_sec);
					}else{
					sprintf(str_trajec_sec, "%d", time_sec);
				}
				
				sprintf(str_trajec_time, "%s:%s", str_trajec_min , str_trajec_sec);
				lv_label_set_text_fmt( labelMMSS, "%s", str_trajec_time);
				
			}
			// -------------------------------------------------
			
		}
		
	}
	
}


static void task_sensor(void *pvParameters) {
	
	printf("\n Init task sensor \n");
	
	// Configuração 
	config_sensor();
	
	// LCD
	data data_lcd;
	
	// Contar segundo pulso
	float conversor = 0.001;
	int calcula_delta_t = 0;
	
	// Guarda delta t e pega contador do RTT 
	int counter = 0;
	float t = 0;
	float freq = 0;
	
	float v = 0;
	float vel_anterior = 0;
	float acel ;

	float fator_km = 3.6;
		
	// Cria variável que indica se Trajeto esta sendo gravado ou não:
	gravando = 0 ;
	
	// ----- Informações do trajeto -----
	float distancia_percorrida = 0;
	float vel_media = 0;
	
	total_time_traj= 0;
	
	for (;;)  {
		
		if(xSemaphoreTake(xSemaphoreRESET, 0)){
			
			// Inicializa variáveis do trajeto
			gravando = 0;
			total_time_traj= 0;
			distancia_percorrida = 0;
			vel_media = 0;
			
			// ---- ENvia informações para serem atualizadas no LCD ----
			lv_label_set_text_fmt( labelMMSS, "%s" , "00:00");
			lv_obj_add_flag(rec_laranja, LV_OBJ_FLAG_HIDDEN);
			lv_label_set_text(labelBtnPlayPause, LV_SYMBOL_PLAY);
			
			data_lcd.velocidade = v;
			data_lcd.aceleracao = acel;
			data_lcd.velocidade_media = vel_media;
			data_lcd.distancia = distancia_percorrida;
			
			xQueueSend(xQueueLCD, &data_lcd , 0);
			printf("\nREINICIA GRAVAÇÃO\n");
			
		}
		
		
		if(xSemaphoreTake(xSemaphoreREC, 0)){
			if(gravando){
				gravando = 0;
				
				printf("\nPARA GRAVAÇÃO\n");
				
				// --- Altera LCD ---
				lv_obj_add_flag(rec_laranja, LV_OBJ_FLAG_HIDDEN);
				lv_label_set_text(labelBtnPlayPause, LV_SYMBOL_PLAY);
				
			}else{
				gravando = 1;
				
				printf("\n GRAVANDO ..  \n");
				
				// --- Altera LCD ---
				lv_obj_clear_flag(rec_laranja, LV_OBJ_FLAG_HIDDEN);
				lv_label_set_text(labelBtnPlayPause, LV_SYMBOL_PAUSE);
				
			}
		}
		
		if(xSemaphoreTake(xSemaphoreRotateTime , 0)){
				
				// ---- Calcula frequencia de giro ----
				counter = rtt_read_timer_value(RTT);
				t = counter*conversor;
			    freq = 1/t;
				
				// ---- Reinicia Tempo ----
				RTT_init(1000, 0 , 0);																																																																																				
				
				// ---- Cacula velocidade [km/h] ----																																																																																																																																																																																																																																																																																																																											
				v = 2*PI*freq*RAIO*fator_km;																																																																																																																																																																																																																								
				
				//printf("\n Counter : %d",  counter);
				//printf("\n Tempo : %f s \n",  t);
				//printf("\n Freq : %f Hz \n",  freq);
				//printf("\n Velocidade : %.4f km/h \n",  v);
				
				// ---- Sinal Aceleração ----
				acel = v - vel_anterior;
				
				// ----- Informações de trajeto -----
				if(gravando){
					
					// Atualiza a distancia a cada volta [km]
					distancia_percorrida += 2*PI*RAIO*0.001;
					printf("\n [TRAJETO] Distancia : %f \n", distancia_percorrida);

					// Velocidade média atualizada após 30s de percurso:
					float time_h = (total_time_traj/3600.0);
					vel_media = distancia_percorrida/time_h;
					printf("\n [TRAJETO] Velocidade Media : %f \n", vel_media);
					
					
				}
				
				// ---- Atutaliza velocidade anterior
				vel_anterior = v;
				
				
				// ---- ENvia informações para serem atualizadas no LCD ----
				data_lcd.velocidade = v;
				data_lcd.aceleracao = acel;
				data_lcd.velocidade_media = vel_media;
				data_lcd.distancia = distancia_percorrida;
				
				xQueueSend(xQueueLCD, &data_lcd , 0);
				
		}
		
	}
																																																																																																																																																																																																																																																							
}

static void task_simulador(void *pvParameters) {
	
	printf("\n Init task simulador \n");
	
	pmc_enable_periph_clk(ID_PIOC);
	pio_set_output(PIOC, PIO_PC31, 1, 0, 0);

	float vel = VEL_MAX_KMH;
	float f;
	int ramp_up = 1;

	while(1){
		pio_clear(PIOC, PIO_PC31);
		delay_ms(1);
		pio_set(PIOC, PIO_PC31);
			
		/*		
		// --------------------- Descomentar para velocidade variável ---------------------																																																																																																																																																																																																																																																																																																																																												#ifdef RAMP
		if (ramp_up) {
			printf("[SIMU] ACELERANDO: %d \n", (int) (10*vel));
			vel += 0.5;
			} else {
			printf("[SIMU] DESACELERANDO: %d \n",  (int) (10*vel));
			vel -= 0.5;
		}

		if (vel >= VEL_MAX_KMH)																																																																																				
		ramp_up = 0;														
		else if (vel <= VEL_MIN_KMH)
		ramp_up = 1;
		// ---------------------------------------------------------------------------------																														
		*/
		
		// --------------------- Descomentar para velocidade constante ---------------------
		vel = 120;
		// printf("\n[SIMU] CONSTANTE: %d \n", (int) (10*vel));
		// ---------------------------------------------------------------------------------
	
		f = kmh_to_hz(vel, RAIO);
		int t = 965*(1.0/f); //UTILIZADO 965 como multiplicador ao invés de 1000
		//para compensar o atraso gerado pelo Escalonador do freeRTOS
		delay_ms(t);
	}
}

static void task_lcd(void *pvParameters) {
	
	printf("\n Init task lcd \n");
	
	int px, py;
	
	// LCD
	data data_lcd;
	
	// ----- Tela de Descanso
	scr0  = lv_obj_create(NULL);
	//lv_ex_btn_1(scr0);

	// ----- Tela Principal
	scr1  = lv_obj_create(NULL);
	lv_bike(scr1);

	// ----- Tela Configuraçao
	scr2  = lv_obj_create(NULL);
	tela_settings(scr2);
	
	lv_obj_clear_flag(scr1, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_clear_flag(scr2, LV_OBJ_FLAG_SCROLLABLE);
	
	lv_scr_load(scr1); 

	for (;;)  {
		lv_tick_inc(50);
		lv_task_handler();
		
		if(xSemaphoreTake(xSemaphoreSettings , 0)){
			// ------------- Tela de Configuração
			lv_label_set_text_fmt(labelMode, "Settings");
			lv_scr_load(scr2);
			
		}
		
		if(xSemaphoreTake(xSemaphoreHorn , 0)){
			// -------------Toca Buzina
			tone(3500, 50);
			printf("buzinaaar.\n");
		}
		
		
		if(xQueueReceive(xQueueLCD , &data_lcd,  0)){
			// ------------ Mudanças no LCD ------------
			lv_label_set_text_fmt(labelCurrentSpeed, "%d", (int) data_lcd.velocidade);
			int csf = (int) fmod(data_lcd.velocidade*10, 10);
			lv_label_set_text_fmt(labelCurrentSpeedFloat, "%d", csf);
			
			if(mod(data_lcd.aceleracao) < DELTA_CONSTANTE){
				printf("\n CONSTANTE \n");
				
				lv_obj_add_flag(acelerandoVerde, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(desacelerandoRed, LV_OBJ_FLAG_HIDDEN);
				
				}else if (data_lcd.aceleracao < 0){
				//printf("\nDESACELERA\n");
				
				lv_obj_add_flag(acelerandoVerde, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(desacelerandoRed, LV_OBJ_FLAG_HIDDEN);
				}else if(data_lcd.aceleracao > 0){
				//printf("\nACELERA\n");
				
				lv_obj_add_flag(desacelerandoRed, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(acelerandoVerde, LV_OBJ_FLAG_HIDDEN);
			}
			
			lv_label_set_text_fmt(labelKmValue, "%.1f", data_lcd.distancia);
			int avarageSpeedFloat = (int) fmod(data_lcd.velocidade_media*10, 10);
			lv_label_set_text_fmt(labelAvarageSpeed, "%d", (int) data_lcd.velocidade_media);
			lv_label_set_text_fmt(labelAvarageSpeedFloat, "%d", avarageSpeedFloat);
			
			if(unidade_amostragem == 1){
				// ----- Vel. Instantanea -----
				lv_label_set_text_fmt(labelCurrentSpeedUnity, "kh/h");
				// ----- Distancia -----
				lv_label_set_text_fmt(labelKm, "km");
				// ----- Vel. Média -----
				lv_label_set_text_fmt(labelAvarageSpeedUnity, "km/h");

				}else{
				// ----- Vel. Instantanea -----
				lv_label_set_text_fmt(labelCurrentSpeedUnity, "mph");
				// ----- Distancia -----
				lv_label_set_text_fmt(labelKm, "mi");
				// ----- Vel. Média -----
				lv_label_set_text_fmt(labelAvarageSpeedUnity, "mph");
			}

		}
		
		
		vTaskDelay(50);
	}
}

/************************************************************************/
/* configs                                                              */
/************************************************************************/

static void configure_lcd(void) {
	/**LCD pin configure on SPI*/
	pio_configure_pin(LCD_SPI_MISO_PIO, LCD_SPI_MISO_FLAGS);  //
	pio_configure_pin(LCD_SPI_MOSI_PIO, LCD_SPI_MOSI_FLAGS);
	pio_configure_pin(LCD_SPI_SPCK_PIO, LCD_SPI_SPCK_FLAGS);
	pio_configure_pin(LCD_SPI_NPCS_PIO, LCD_SPI_NPCS_FLAGS);
	pio_configure_pin(LCD_SPI_RESET_PIO, LCD_SPI_RESET_FLAGS);
	pio_configure_pin(LCD_SPI_CDS_PIO, LCD_SPI_CDS_FLAGS);
	
	ili9341_init();
	ili9341_backlight_on();
}

static void configure_console(void) {
	const usart_serial_options_t uart_serial_options = {
		.baudrate = USART_SERIAL_EXAMPLE_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT,
	};

	/* Configure console UART. */
	stdio_serial_init(CONSOLE_UART, &uart_serial_options);

	/* Specify that stdout should not be buffered. */
	setbuf(stdout, NULL);
}

void RTC_init(Rtc *rtc, uint32_t id_rtc, calendar t, uint32_t irq_type) {
	/* Configura o PMC */
	pmc_enable_periph_clk(ID_RTC);

	/* Default RTC configuration, 24-hour mode */
	rtc_set_hour_mode(rtc, 0);

	/* Configura data e hora manualmente */
	rtc_set_date(rtc, t.year, t.month, t.day, t.week);
	rtc_set_time(rtc, t.hour, t.minute, t.seccond);

	/* Configure RTC interrupts */
	NVIC_DisableIRQ(id_rtc);
	NVIC_ClearPendingIRQ(id_rtc);
	NVIC_SetPriority(id_rtc, 4);
	NVIC_EnableIRQ(id_rtc);

	/* Ativa interrupcao via alarme */
	rtc_enable_interrupt(rtc,  irq_type);
}

static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource) {

	uint16_t pllPreScale = (int) (((float) 32768) / freqPrescale);
	
	rtt_sel_source(RTT, false);
	rtt_init(RTT, pllPreScale);
	
	if (rttIRQSource & RTT_MR_ALMIEN) {
		uint32_t ul_previous_time;
		ul_previous_time = rtt_read_timer_value(RTT);
		while (ul_previous_time == rtt_read_timer_value(RTT));
		rtt_write_alarm_time(RTT, IrqNPulses+ul_previous_time);
	}

	/* config NVIC */
	NVIC_DisableIRQ(RTT_IRQn);
	NVIC_ClearPendingIRQ(RTT_IRQn);
	NVIC_SetPriority(RTT_IRQn, 4);
	NVIC_EnableIRQ(RTT_IRQn);

	/* Enable RTT interrupt */
	if (rttIRQSource & (RTT_MR_RTTINCIEN | RTT_MR_ALMIEN))
	rtt_enable_interrupt(RTT, rttIRQSource);
	else
	rtt_disable_interrupt(RTT, RTT_MR_RTTINCIEN | RTT_MR_ALMIEN);
	
}

/************************************************************************/
/* port lvgl                                                            */
/************************************************************************/

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
	ili9341_set_top_left_limit(area->x1, area->y1);   ili9341_set_bottom_right_limit(area->x2, area->y2);
	ili9341_copy_pixels_to_screen(color_p,  (area->x2 + 1 - area->x1) * (area->y2 + 1 - area->y1));
	
	/* IMPORTANT!!!
	* Inform the graphics library that you are ready with the flushing*/
	lv_disp_flush_ready(disp_drv);
}

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
	int px, py, pressed;
	
	if (readPoint(&px, &py))
		data->state = LV_INDEV_STATE_PRESSED;
	else
		data->state = LV_INDEV_STATE_RELEASED; 
	
	data->point.x = py;
	data->point.y = 320 - px;
}

void configure_lvgl(void) {
	lv_init();
	lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);
	
	lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
	disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
	disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
	disp_drv.hor_res = LV_HOR_RES_MAX;      /*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = LV_VER_RES_MAX;      /*Set the vertical resolution in pixels*/

	lv_disp_t * disp;
	disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
	
	/* Init input on LVGL */
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_input_read;
	lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);
}

/************************************************************************/
/* main                                                                 */
/************************************************************************/
int main(void) {
	/* board and sys init */
	board_init();
	sysclk_init();
	configure_console();
	
	// Ativa o PIO na qual o BUZZER foi conectado
	// para que possamos controlar o BUZZER.
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	
	//Inicializa PA21 como sa?da
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);

	/* LCd, touch and lvgl init*/
	configure_lcd();
	ili9341_set_orientation(ILI9341_FLIP_Y | ILI9341_SWITCH_XY);
	configure_touch();
	configure_lvgl();
	
	// Cria fila :
	xQueueLCD = xQueueCreate(30, sizeof(data));
	
	if (xQueueLCD == NULL )
	printf("falha em criar a queue xQueueLCD \n");
	
	 // Cria semáforo
	xSemaphoreSettings = xSemaphoreCreateBinary();
	xSemaphoreGoBack = xSemaphoreCreateBinary();
	xSemaphore1sec = xSemaphoreCreateBinary();
	xSemaphoreRotateTime =  xSemaphoreCreateBinary();
	xSemaphoreREC = xSemaphoreCreateBinary();
	xSemaphoreRESET = xSemaphoreCreateBinary();
	xSemaphoreHorn = xSemaphoreCreateBinary();
	
	/* Create tasks */
	if (xTaskCreate(task_lcd, "LCD", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create lcd task\r\n");
	}
	
	if (xTaskCreate(task_rtc, "RTC", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create RTC task\r\n");
	}
	
	if (xTaskCreate(task_sensor, "SENSOR", TASK_SIMULATOR_STACK_SIZE, NULL, TASK_SIMULATOR_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create sensor task\r\n");
	}
	
	if (xTaskCreate(task_simulador, "SIMUL", TASK_SIMULATOR_STACK_SIZE, NULL, TASK_SIMULATOR_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create simu task\r\n");
	}
	
	/* Start the scheduler. */
	vTaskStartScheduler();

	while(1){ }
}
