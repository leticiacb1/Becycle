/*******************************************************************************
 * Size: 25 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CASCADIA25
#define CASCADIA25 1
#endif

#if CASCADIA25

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0xff, 0xff, 0xff,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x0, 0x30, 0x7, 0x0, 0x60, 0xe, 0x0, 0xc0,
    0x1c, 0x1, 0x80, 0x38, 0x3, 0x80, 0x30, 0x7,
    0x0, 0x60, 0xe, 0x0, 0xc0, 0x1c, 0x1, 0x80,
    0x38, 0x3, 0x0, 0x70, 0x6, 0x0, 0xe0, 0xc,
    0x0,

    /* U+0030 "0" */
    0x1f, 0x83, 0xfc, 0x79, 0xe7, 0xe, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x77, 0xe7, 0x7e, 0x77, 0xe0,
    0x7e, 0x7, 0xe0, 0x77, 0xe, 0x79, 0xe3, 0xfc,
    0x1f, 0x80,

    /* U+0031 "1" */
    0x3e, 0x1f, 0xc3, 0xf8, 0x7, 0x0, 0xe0, 0x1c,
    0x3, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x38, 0x7,
    0x0, 0xe0, 0x1c, 0x3, 0x87, 0xff, 0xff, 0xe0,

    /* U+0032 "2" */
    0x1f, 0x7, 0xfc, 0xf1, 0xce, 0xe, 0x0, 0xe0,
    0xe, 0x0, 0xe0, 0xe, 0x1, 0xc0, 0x3c, 0x3,
    0x80, 0x70, 0x1e, 0x3, 0xc0, 0xf0, 0xf, 0xff,
    0xff, 0xf0,

    /* U+0033 "3" */
    0x1f, 0xc7, 0xfe, 0xf0, 0xfe, 0x7, 0x0, 0x70,
    0x6, 0x1, 0xe0, 0xf0, 0xf, 0xc0, 0x1e, 0x0,
    0xf0, 0x7, 0xe0, 0x7e, 0x7, 0xf0, 0xe7, 0xfe,
    0x1f, 0x80,

    /* U+0034 "4" */
    0x0, 0x70, 0xc3, 0x8e, 0x1c, 0x70, 0xe3, 0x87,
    0x18, 0x38, 0xc1, 0xce, 0xe, 0x70, 0x73, 0x83,
    0x98, 0x1c, 0xff, 0xff, 0xff, 0x80, 0x38, 0x1,
    0xc0, 0xe, 0x0, 0x70,

    /* U+0035 "5" */
    0x7f, 0xe7, 0xfe, 0x70, 0x7, 0x0, 0x70, 0x7,
    0x0, 0x7f, 0x87, 0xfe, 0x60, 0xe0, 0x7, 0x0,
    0x70, 0x7, 0xe0, 0x7e, 0x7, 0xf0, 0xe7, 0xfc,
    0x1f, 0x80,

    /* U+0036 "6" */
    0x3, 0xc0, 0xfc, 0x1e, 0x3, 0x80, 0x70, 0x7,
    0x0, 0xe7, 0xce, 0xfe, 0xf0, 0xee, 0x7, 0xe0,
    0x7e, 0x7, 0xe0, 0x7e, 0x7, 0x70, 0xe3, 0xfe,
    0x1f, 0x80,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xf8, 0x1d, 0xc0, 0xee, 0x7,
    0x70, 0x70, 0x3, 0x80, 0x1c, 0x1, 0xc0, 0xe,
    0x0, 0x60, 0x7, 0x0, 0x38, 0x1, 0x80, 0x1c,
    0x0, 0xe0, 0x6, 0x0,

    /* U+0038 "8" */
    0x1f, 0x87, 0xfe, 0xf0, 0xfe, 0x7, 0xe0, 0x7e,
    0x7, 0x70, 0xe1, 0xfc, 0x3f, 0xc7, 0xe, 0xe0,
    0x7e, 0x7, 0xe0, 0x7e, 0x7, 0x70, 0xe7, 0xfe,
    0x1f, 0x80,

    /* U+0039 "9" */
    0x1f, 0x87, 0xfc, 0x70, 0xee, 0x6, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xf0, 0xf7, 0xf7, 0x3e,
    0x70, 0xe, 0x0, 0xe0, 0x1c, 0x7, 0x83, 0xf0,
    0x3c, 0x0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0x3, 0xfe
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 234, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 234, .box_w = 12, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 4, .adv_w = 234, .box_w = 3, .box_h = 3, .ofs_x = 6, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 234, .box_w = 12, .box_h = 22, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 39, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 234, .box_w = 11, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 234, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 234, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 234, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 234, .box_w = 3, .box_h = 13, .ofs_x = 6, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 45, .range_length = 14, .glyph_id_start = 2,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t cascadia25 = {
#else
lv_font_t cascadia25 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 22,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CASCADIA25*/

