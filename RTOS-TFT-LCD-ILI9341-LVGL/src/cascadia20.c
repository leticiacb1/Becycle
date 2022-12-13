/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/
#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CASCADIA20
#define CASCADIA20 1
#endif

#if CASCADIA20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0030 "0" */
    0x3e, 0x3f, 0x98, 0xdc, 0x7c, 0x1e, 0xef, 0x77,
    0xbb, 0xc1, 0xe0, 0xf0, 0xec, 0x67, 0xf1, 0xf0,

    /* U+0031 "1" */
    0x7c, 0x7e, 0x23, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x8f, 0xff, 0xfc,

    /* U+0032 "2" */
    0x3c, 0x3f, 0x31, 0xd8, 0x60, 0x30, 0x18, 0xc,
    0xc, 0xc, 0xe, 0xe, 0x1c, 0xf, 0xff, 0xfc,

    /* U+0033 "3" */
    0x3e, 0x3f, 0xf8, 0xf8, 0x30, 0x18, 0x18, 0xf0,
    0x3e, 0x3, 0x80, 0xf0, 0x7c, 0x77, 0xf1, 0xf0,

    /* U+0034 "4" */
    0x1, 0x86, 0x30, 0xc6, 0x30, 0xc6, 0x18, 0xc3,
    0x18, 0x63, 0xc, 0x41, 0x9f, 0xff, 0xff, 0x80,
    0xc0, 0x18, 0x3, 0x0,

    /* U+0035 "5" */
    0x7f, 0x3f, 0x98, 0xc, 0x7, 0xe3, 0xf9, 0xe,
    0x3, 0x1, 0x80, 0xf0, 0x7c, 0x77, 0xf1, 0xf0,

    /* U+0036 "6" */
    0xf, 0xf, 0x8e, 0xc, 0x6, 0x6, 0x73, 0x7d,
    0xc7, 0xc1, 0xe0, 0xf0, 0x6c, 0x77, 0xf1, 0xf0,

    /* U+0037 "7" */
    0xff, 0xff, 0xfc, 0x1b, 0x6, 0xc3, 0x80, 0xc0,
    0x30, 0x1c, 0x6, 0x1, 0x80, 0xe0, 0x30, 0xc,
    0x7, 0x0,

    /* U+0038 "8" */
    0x3e, 0x7f, 0xf8, 0xf8, 0x3e, 0x3b, 0xf0, 0xf8,
    0xc6, 0xc1, 0xe0, 0xf0, 0x7c, 0x77, 0xf1, 0xf0,

    /* U+0039 "9" */
    0x3e, 0x3f, 0xb8, 0xd8, 0x3c, 0x1e, 0xf, 0x8e,
    0xfb, 0x3d, 0x81, 0x80, 0xc1, 0xc7, 0xc3, 0xc0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0xff, 0x80,

    /* U+0044 "D" */
    0xfc, 0x3f, 0xcc, 0x3b, 0x6, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0x1f, 0xe, 0xff,
    0x3f, 0x80,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x7c, 0x77, 0xf1, 0xf0,

    /* U+005E "^" */
    0x38, 0x3c, 0x6c, 0x66, 0x66, 0xc7,

    /* U+0061 "a" */
    0x7e, 0x1f, 0xc0, 0x38, 0x6, 0x3f, 0x9f, 0xee,
    0x1b, 0x6, 0xc3, 0xbf, 0xf7, 0xdc,

    /* U+0063 "c" */
    0x1e, 0x3f, 0x98, 0xf8, 0x3c, 0x6, 0x3, 0x1,
    0x80, 0x60, 0x3f, 0xc7, 0xe0,

    /* U+0064 "d" */
    0x1, 0x80, 0xc0, 0x60, 0x33, 0xdb, 0xff, 0x8f,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3e, 0x3b, 0xfc,
    0xf6,

    /* U+0065 "e" */
    0x3e, 0x3f, 0x98, 0xd8, 0x3c, 0x1f, 0xff, 0xff,
    0x80, 0x60, 0x3f, 0x87, 0xc0,

    /* U+0069 "i" */
    0x1c, 0xe, 0x7, 0x0, 0x7, 0xc3, 0xe0, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xc7, 0xff,
    0xfe,

    /* U+006C "l" */
    0xf8, 0x7c, 0x6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xfc,
    0x3e,

    /* U+006D "m" */
    0xd9, 0xbf, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcc,

    /* U+006E "n" */
    0xde, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+006F "o" */
    0x3e, 0x3f, 0x98, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0x63, 0x3f, 0x8f, 0x80,

    /* U+0072 "r" */
    0xf7, 0xbd, 0xf3, 0x8c, 0xe3, 0x30, 0xc, 0x3,
    0x0, 0xc0, 0x30, 0x3f, 0x8f, 0xe0,

    /* U+0074 "t" */
    0x18, 0xc, 0x6, 0x1f, 0xff, 0xf8, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x80, 0xf8, 0x3c,

    /* U+0076 "v" */
    0xc0, 0xf0, 0x66, 0x19, 0x86, 0x63, 0xc, 0xc3,
    0x30, 0xd8, 0x1e, 0x7, 0x81, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 188, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 188, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 188, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 188, .box_w = 3, .box_h = 11, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 188, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 188, .box_w = 8, .box_h = 6, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 212, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 188, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 188, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 188, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 188, .box_w = 9, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 188, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 188, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 188, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 188, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x24, 0x35, 0x3e, 0x41,
    0x43, 0x44, 0x45, 0x49, 0x4c, 0x4d, 0x4e, 0x4f,
    0x52, 0x54, 0x56
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 87, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 27, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    .cmap_num = 1,
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
const lv_font_t cascadia20 = {
#else
lv_font_t cascadia20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CASCADIA20*/

