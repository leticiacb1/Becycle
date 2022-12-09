/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include <asf.h>
#include <string.h>
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



/************************************************************************/
/* LCD / LVGL                                                           */
/************************************************************************/

#define LV_HOR_RES_MAX          (240)
#define LV_VER_RES_MAX          (320)
LV_FONT_DECLARE(cascadia20);
LV_FONT_DECLARE(cascadia25);
LV_FONT_DECLARE(cascadia17);
LV_FONT_DECLARE(cascadia65);

// declarar a tela como global e estática
static lv_obj_t * scr1;  // screen 1
static lv_obj_t * scr2;  // screen 2

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];
static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
static lv_indev_drv_t indev_drv;

// globais 
lv_obj_t * labelBtn1, * labelBtnPlayPause;
lv_obj_t * labelClock, * labelKmValue, * labelMMSS, * labelAvarageSpeed, * labelMode, * labelKm, * labelMMSSunit, * labelSpeedUnity, * labelCurrentSpeed, * labelCurrentSpeedUnity, * labelDiameter, * labelSpeedUnity, * labelBack;

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

/************************************************************************/
/* lvgl                                                                 */
/************************************************************************/

static void event_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		LV_LOG_USER("Clicked");
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
		lv_label_set_text_fmt(labelMode, "Settings");
		lv_scr_load(scr2);
		LV_LOG_USER("Clicked");
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
}

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

void lv_ex_btn_1(void) {
// 	lv_obj_t * label;
// 
// 	lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
// 	lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
// 	lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
// 
// 	label = lv_label_create(btn1);
// 	lv_label_set_text(label, "Corsi");
// 	lv_obj_center(label);
// 
// 	lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
// 	lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
// 	lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
// 	lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
// 	lv_obj_set_height(btn2, LV_SIZE_CONTENT);
// 
// 	label = lv_label_create(btn2);
// 	lv_label_set_text(label, "Toggle");
// 	lv_obj_center(label);
}

void tela_settings(void){
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 0);
	lv_style_set_arc_rounded(&style, 0);
	lv_style_set_img_recolor_opa(&style, LV_OPA_30);
	lv_style_set_img_recolor(&style, lv_color_black());
	
	//######################################################################################
	//#								Tela Settings                                          #
	//######################################################################################
	
	// ----------------	Branco	-----------
	lv_obj_t * white = lv_img_create(scr2);
	lv_img_set_src(white, &branco);
	lv_obj_align(white, LV_ALIGN_CENTER, 0, 0);
	// ---------------------------------------------------
	
	// ----------------	Logo posicionada nas telas	-----------
	lv_obj_t * logoSettings = lv_img_create(scr2);
	lv_img_set_src(logoSettings, &logoConfig);
	lv_obj_align(logoSettings, LV_ALIGN_BOTTOM_MID, 0, -10);
	// ---------------------------------------------------
	
	// ----------------	Linha do header  -----------
	lv_obj_t * lineDivisora = lv_img_create(scr2);
	lv_img_set_src(lineDivisora, &line);
	lv_obj_align(lineDivisora, LV_ALIGN_TOP_LEFT, 0, 24);
	// ---------------------------------------------------
	
	// ----------------	Modo atual (config)-----------
	labelMode = lv_label_create(scr2);
	lv_obj_align(labelMode, LV_ALIGN_TOP_MID, 5, 2);
	lv_obj_set_style_text_font(labelMode, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMode, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMode, "Settings");
	// ---------------------------------------------------
	
	// ------------------Botão Back ------------------------
	lv_obj_t * btnBack = lv_btn_create(scr2);
	lv_obj_add_event_cb(btnBack, back_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btnBack, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btnBack, LV_ALIGN_TOP_LEFT, 6, 2);
	lv_obj_set_width(btnBack, 45);  lv_obj_set_height(btnBack, 30);
	lv_obj_add_style(btnBack, &style, 0);
	
	labelBack = lv_label_create(btnBack);
	lv_label_set_text(labelBack, LV_SYMBOL_LEFT);
	lv_obj_center(labelBack);
	//----------------------------------------------------------
	
	
	
	// ----------------	Diâmetro-----------
	labelDiameter = lv_label_create(scr2);
	lv_obj_align(labelDiameter,  LV_ALIGN_CENTER, 0, -108);
	lv_obj_set_style_text_font(labelDiameter, &cascadia20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelDiameter, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelDiameter, "Diametro");
	// ---------------------------------------------------
	
	// ----------------	Icones roda	-----------
	lv_obj_t * iconWheel = lv_img_create(scr2);
	lv_img_set_src(iconWheel, &rodaConfig);
	lv_obj_align(iconWheel,  LV_ALIGN_CENTER, -50, -34);
	// ---------------------------------------------------
	
	// -----------------Roller Aro ---------------
	 lv_obj_t * roller1 = lv_roller_create(scr2);
	 lv_roller_set_options(roller1,
	 "20''\n"
	 "24''\n"
	 "26''\n"
	 "27,5''\n"
	 "29''\n"
	 "700",
	 LV_ROLLER_MODE_INFINITE);

	 lv_roller_set_visible_row_count(roller1, 3);
	 lv_obj_center(roller1);
	 lv_obj_add_event_cb(roller1, roller_handler, LV_EVENT_ALL, NULL);
	 lv_obj_align(roller1,  LV_ALIGN_CENTER, 40, -34);

	// -------------------------------------------
	
	
	//------------------Unidade da velocidade-----------------
	labelSpeedUnity = lv_label_create(scr2);
	lv_obj_align(labelSpeedUnity,  LV_ALIGN_CENTER, 0, 36);
	lv_obj_set_style_text_font(labelSpeedUnity, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelSpeedUnity, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelSpeedUnity, "Unidade da velocidade");
	//--------------------------------------------------------
	
	// ---- Checkboxes as radio buttons para Unidade de Velocidade ---
	 
	 uint32_t i;
	 char buf[32];

	 lv_obj_t * cont1 = lv_obj_create(scr2);
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
void lv_bike(void) {
// ---------------- Estilo --------------------
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 0);
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
	lv_obj_t * white = lv_img_create(scr1);
	lv_img_set_src(white, &branco);
	lv_obj_align(white, LV_ALIGN_CENTER, 0, 0);
// ---------------------------------------------------

// ----------------	Icones tela main	-----------
	lv_obj_t * icons = lv_img_create(scr1);
	lv_img_set_src(icons, &icones);
	lv_obj_align(icons, LV_ALIGN_CENTER,0, 30);
// ---------------------------------------------------

//------------------------ (o número) [km]--------------------
	labelKmValue = lv_label_create(scr1);
	lv_obj_align(labelKmValue, LV_ALIGN_CENTER, -93, 85); 
	lv_obj_set_style_text_font(labelKmValue, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelKmValue, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelKmValue, "%d",13);
// -------------------------------------------------



//------------------------ (os números do cronômetro) [MM:SS]--------------------
	labelMMSS = lv_label_create(scr1);
	lv_obj_align(labelMMSS, LV_ALIGN_CENTER, -5, 85);
	lv_obj_set_style_text_font(labelMMSS, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMMSS, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMMSS, "%d%d:%d%d",3,4,5,5);
// -------------------------------------------------


//------------------------ (o valor) [km/h]--------------------
	labelAvarageSpeed = lv_label_create(scr1);
	lv_obj_align(labelAvarageSpeed, LV_ALIGN_CENTER, 90, 85);
	lv_obj_set_style_text_font(labelAvarageSpeed, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelAvarageSpeed, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelAvarageSpeed, "%d", 18);
// -------------------------------------------------


// ----------------	Imagem da tela de ligar	-----------
// 	lv_obj_t * logoOn = lv_img_create(lv_scr_act());
// 	lv_img_set_src(logoOn, &logoAoLigar);
// 	lv_obj_align(logoOn, LV_ALIGN_CENTER, 0, 0);
// ---------------------------------------------------

// ----------------	Logo posicionada nas telas	-----------
	lv_obj_t * logoLetras = lv_img_create(scr1);
	lv_img_set_src(logoLetras, &logo);
	lv_obj_align(logoLetras, LV_ALIGN_TOP_LEFT, 4, 4);
// ---------------------------------------------------

// ----------------	Modo atual (ride/config)-----------
	labelMode = lv_label_create(scr1);
	lv_obj_align(labelMode, LV_ALIGN_TOP_MID, 5, 4);
	lv_obj_set_style_text_font(labelMode, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMode, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMode, "Ride");
// ---------------------------------------------------

// ----------------	LInha do header  -----------
	lv_obj_t * lineDivisora = lv_img_create(scr1);
	lv_img_set_src(lineDivisora, &line);
	lv_obj_align(lineDivisora, LV_ALIGN_TOP_LEFT, 0, 24);
// ---------------------------------------------------

// ----------------	Reloginho	-----------
	lv_obj_t * clockzinho = lv_img_create(scr1);
	lv_img_set_src(clockzinho, &clock);
	lv_obj_align(clockzinho, LV_ALIGN_TOP_LEFT, 63, 44);
// ---------------------------------------------------

//------------------------ Hora--------------------
	labelClock = lv_label_create(scr1);
	lv_obj_align(labelClock, LV_ALIGN_TOP_LEFT, 84, 47);
	lv_obj_set_style_text_font(labelClock, &cascadia20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelClock, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelClock, "%d%d:%d%d:%d%d",2,3,4,5,4,7);
// -------------------------------------------------

//------------------------ Velocidade Instantanea--------------------
	labelCurrentSpeed = lv_label_create(scr1);
	lv_obj_align(labelCurrentSpeed, LV_ALIGN_CENTER, 0, -60);
	lv_obj_set_style_text_font(labelCurrentSpeed, &cascadia65, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelCurrentSpeed, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelCurrentSpeed, "%d", 23);
// -------------------------------------------------

//------------------------ Unidade da Velocidade Instantanea--------------------
	labelCurrentSpeedUnity = lv_label_create(scr1);
	lv_obj_align(labelCurrentSpeedUnity, LV_ALIGN_CENTER, 0, -18);
	lv_obj_set_style_text_font(labelCurrentSpeedUnity, &cascadia25, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelCurrentSpeedUnity, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelCurrentSpeedUnity, "km/h");
// -------------------------------------------------

// ----------------	Flecha acelarando verde	-----------
	lv_obj_t * acelerandoVerde = lv_img_create(scr1);
	lv_img_set_src(acelerandoVerde, &acelarando); 
	lv_obj_align(acelerandoVerde,  LV_ALIGN_CENTER, 60, -60);
// ---------------------------------------------------

// ----------------	Flecha DESacelarando vermelha	-----------
	lv_obj_t * desacelerandoRed = lv_img_create(scr1);
	lv_img_set_src(desacelerandoRed, &desacelarando);
	lv_obj_align(desacelerandoRed,  LV_ALIGN_CENTER, -60, -60);
// ---------------------------------------------------

// ------------------Botão Config ------------------------
	lv_obj_t * btn1 = lv_btn_create(scr1);
	lv_obj_add_event_cb(btn1, config_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btn1, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btn1, LV_ALIGN_TOP_RIGHT, -6, 2);
	lv_obj_set_width(btn1, 45);  lv_obj_set_height(btn1, 30);
	lv_obj_add_style(btn1, &style, 0);
		
	labelBtn1 = lv_label_create(btn1);
	lv_label_set_text(labelBtn1, LV_SYMBOL_SETTINGS);
	lv_obj_center(labelBtn1);
//----------------------------------------------------------

// ----------------	LInha do footter  -----------
	lv_obj_t * lineDivisoraF = lv_img_create(scr1);
	lv_img_set_src(lineDivisoraF, &line);
	lv_obj_align(lineDivisoraF, LV_ALIGN_BOTTOM_MID, 0, -35);
// ---------------------------------------------------

// ----------------Rec laranja (gravando) ---------------------
	lv_obj_t * rec_laranja = lv_img_create(scr1);
	lv_img_set_src(rec_laranja, &rec);
	lv_obj_align(rec_laranja, LV_ALIGN_BOTTOM_MID,0,-2);
//----------------------------------------------------------

// ----------------Reset ---------------------
	LV_IMG_DECLARE(imgReset);

	static lv_style_t style_def;

	lv_style_init(&style_def); /*Darken the button when pressed and make it wider*/
	static lv_style_t style_pr;
	lv_style_init(&style_pr);
	lv_style_set_img_recolor_opa(&style_pr, LV_OPA_30);
	lv_style_set_img_recolor(&style_pr, lv_color_black());

	lv_obj_t * btnReset = lv_imgbtn_create(scr1);
	lv_imgbtn_set_src(btnReset, LV_IMGBTN_STATE_RELEASED, NULL, NULL, &reset);
	lv_obj_add_style(btnReset, &style, LV_STATE_PRESSED);
	lv_obj_align_to(btnReset, rec_laranja, LV_ALIGN_BOTTOM_LEFT, -180, 96);
	//lv_obj_align(btnReset, LV_ALIGN_BOTTOM_LEFT, 0, -2); // pq n funciona?
//----------------------------------------------------------

// ------------------Botão Play/Pause ------------------------
	lv_obj_t * btn_play_pause = lv_btn_create(scr1);
	lv_obj_add_event_cb(btn_play_pause, event_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btn_play_pause, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btn_play_pause, LV_ALIGN_BOTTOM_RIGHT, -22, -8);
	lv_obj_set_width(btn_play_pause, 35);  lv_obj_set_height(btn_play_pause, 32);
	lv_obj_add_style(btn_play_pause, &style, 0);

	labelBtnPlayPause = lv_label_create(btn_play_pause);
	lv_label_set_text(labelBtnPlayPause, LV_SYMBOL_STOP);
	lv_obj_center(labelBtnPlayPause);
//----------------------------------------------------------

	//------------------------ (a unidade de medida) [km]--------------------
	labelKm = lv_label_create(scr1);
	lv_obj_align(labelKm, LV_ALIGN_CENTER, -96, 105);
	lv_obj_set_style_text_font(labelKm, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelKm, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelKm, "km");
	// -------------------------------------------------

	//------------------------ (a unidade) [km/h]--------------------
	labelSpeedUnity = lv_label_create(scr1);
	lv_obj_align(labelSpeedUnity, LV_ALIGN_CENTER, 90, 105);
	lv_obj_set_style_text_font(labelSpeedUnity, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelSpeedUnity, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelSpeedUnity, "km/h");
	// -------------------------------------------------

	//------------------------ (a unidade do cronômetro) [MM:SS]--------------------
	labelMMSSunit = lv_label_create(scr1);
	lv_obj_align(labelMMSSunit, LV_ALIGN_CENTER, -5, 105);
	lv_obj_set_style_text_font(labelMMSSunit, &cascadia17, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(labelMMSSunit, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(labelMMSSunit, "mm:ss");
	// -------------------------------------------------

}

/************************************************************************/
/* TASKS                                                                */
/************************************************************************/


static void task_lcd(void *pvParameters) {
	int px, py;

	//lv_ex_btn_1();
	// Criando duas telas
	scr1  = lv_obj_create(NULL);
	scr2  = lv_obj_create(NULL);
	lv_bike();
	lv_obj_clear_flag(scr1, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_clear_flag(scr2, LV_OBJ_FLAG_SCROLLABLE);
	lv_scr_load(scr1); // exibe tela 1
	tela_settings();

	for (;;)  {
		lv_tick_inc(50);
		lv_task_handler();
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

	/* LCd, touch and lvgl init*/
	configure_lcd();
	ili9341_set_orientation(ILI9341_FLIP_Y | ILI9341_SWITCH_XY);
	configure_touch();
	configure_lvgl();

	/* Create task to control oled */
	if (xTaskCreate(task_lcd, "LCD", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create lcd task\r\n");
	}
	
	/* Start the scheduler. */
	vTaskStartScheduler();

	while(1){ }
}
