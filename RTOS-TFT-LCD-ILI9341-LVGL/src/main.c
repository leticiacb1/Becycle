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


/************************************************************************/
/* LCD / LVGL                                                           */
/************************************************************************/

#define LV_HOR_RES_MAX          (240)
#define LV_VER_RES_MAX          (320)

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];
static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
static lv_indev_drv_t indev_drv;

// globais 
lv_obj_t * labelBtn1, * labelBtnPlayPause;
lv_obj_t * labelClock;

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


void lv_bike(void) {
// ---------------- Estilo --------------------
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 0);
// --------------------------------------------
// ----------------	Base tela main	-----------
	lv_obj_t * img = lv_img_create(lv_scr_act());
	lv_img_set_src(img, &fundo_inicial);
	lv_obj_align(img, LV_ALIGN_CENTER,0, 0);
// ---------------------------------------------------

// ----------------	Icones tela main	-----------
	lv_obj_t * icons = lv_img_create(lv_scr_act());
	lv_img_set_src(icons, &icones);
	lv_obj_align(icons, LV_ALIGN_CENTER,0, 30);
// ---------------------------------------------------

// ----------------	Imagem da tela de ligar	-----------
// 	lv_obj_t * logoOn = lv_img_create(lv_scr_act());
// 	lv_img_set_src(logoOn, &logoAoLigar);
// 	lv_obj_align(logoOn, LV_ALIGN_CENTER, 0, 0);
// ---------------------------------------------------

// ----------------	Logo posicionada nas telas	-----------
	lv_obj_t * logoLetras = lv_img_create(lv_scr_act());
	lv_img_set_src(logoLetras, &logo);
	lv_obj_align(logoLetras, LV_ALIGN_TOP_LEFT, 4, 4);
// ---------------------------------------------------

// ----------------	Reloginho	-----------
	lv_obj_t * clockzinho = lv_img_create(lv_scr_act());
	lv_img_set_src(clockzinho, &clock);
	lv_obj_align(clockzinho, LV_ALIGN_TOP_LEFT, 63, 44);
// ---------------------------------------------------

//------------------------ Hora--------------------
// 	labelClock = lv_label_create(lv_scr_act());
// 	lv_obj_align(labelClock, LV_ALIGN_LEFT_MID, 35 , -45);
// 	lv_obj_set_style_text_font(labelClock, &cascadia25, LV_STATE_DEFAULT);
// 	lv_obj_set_style_text_color(labelClock, lv_color_white(), LV_STATE_DEFAULT);
// 	lv_label_set_text_fmt(labelClock, "%02d", 23);
// -------------------------------------------------

// ------------------Bot�o Config ------------------------
	lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
	lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btn1, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btn1, LV_ALIGN_TOP_RIGHT, -6, 2);
	lv_obj_set_width(btn1, 35);  lv_obj_set_height(btn1, 32);
	lv_obj_add_style(btn1, &style, 0);
		
	labelBtn1 = lv_label_create(btn1);
	lv_label_set_text(labelBtn1, LV_SYMBOL_SETTINGS);
	lv_obj_center(labelBtn1);
//----------------------------------------------------------

// ----------------Rec laranja (gravando) ---------------------
	lv_obj_t * rec_laranja = lv_img_create(lv_scr_act());
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

	lv_obj_t * btnReset = lv_imgbtn_create(lv_scr_act());
	lv_imgbtn_set_src(btnReset, LV_IMGBTN_STATE_RELEASED, NULL, NULL, &reset);
	lv_obj_add_style(btnReset, &style_def, 0);
	lv_obj_add_style(btnReset, &style_pr, LV_STATE_PRESSED);
	lv_obj_align_to(btnReset, rec_laranja, LV_ALIGN_BOTTOM_LEFT, -180, 99);
	//lv_obj_align(btnReset, LV_ALIGN_BOTTOM_LEFT, 0, -2); // pq n funciona?
//----------------------------------------------------------

// ------------------Bot�o Play/Pause ------------------------
	lv_obj_t * btn_play_pause = lv_btn_create(lv_scr_act());
	lv_obj_add_event_cb(btn_play_pause, event_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_text_color(btn_play_pause, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_align(btn_play_pause, LV_ALIGN_BOTTOM_RIGHT, -22, -2);
	lv_obj_set_width(btn_play_pause, 35);  lv_obj_set_height(btn_play_pause, 32);
	lv_obj_add_style(btn_play_pause, &style, 0);

	labelBtnPlayPause = lv_label_create(btn_play_pause);
	lv_label_set_text(labelBtnPlayPause, LV_SYMBOL_STOP);
	lv_obj_center(labelBtnPlayPause);
//----------------------------------------------------------
	
}

/************************************************************************/
/* TASKS                                                                */
/************************************************************************/


static void task_lcd(void *pvParameters) {
	int px, py;

	lv_ex_btn_1();
	lv_bike();
	lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
	

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
