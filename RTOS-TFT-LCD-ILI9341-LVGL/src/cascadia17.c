/*******************************************************************************
 * Size: 17 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/
#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CASCADIA17
#define CASCADIA17 1
#endif

#if CASCADIA17

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x3, 0x2, 0x6, 0x6, 0xc, 0xc, 0x8, 0x18,
    0x10, 0x30, 0x20, 0x60, 0x60, 0xc0, 0xc0,

    /* U+0030 "0" */
    0x3c, 0x66, 0x42, 0xc3, 0xc3, 0xc3, 0xdb, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0031 "1" */
    0x79, 0xf0, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30, 0x67, 0xf0,

    /* U+0032 "2" */
    0x7c, 0xce, 0xc6, 0x6, 0x6, 0x6, 0xc, 0x1c,
    0x18, 0x30, 0xc0, 0xff,

    /* U+0033 "3" */
    0x3e, 0xe3, 0xc3, 0x3, 0x6, 0x38, 0x1e, 0x3,
    0x3, 0xc3, 0xe7, 0x7c,

    /* U+0034 "4" */
    0x3, 0x11, 0x98, 0xcc, 0x66, 0x33, 0x19, 0xd,
    0x86, 0xff, 0x81, 0x80, 0xc0, 0x60,

    /* U+0035 "5" */
    0x7e, 0x60, 0x60, 0x60, 0x7e, 0x46, 0x3, 0x3,
    0x3, 0xc3, 0xe6, 0x3c,

    /* U+0036 "6" */
    0xe, 0x30, 0x60, 0x60, 0xc0, 0xde, 0xe7, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0037 "7" */
    0xff, 0xe1, 0xb0, 0xd8, 0x60, 0x60, 0x30, 0x18,
    0x18, 0xc, 0x6, 0x6, 0x3, 0x0,

    /* U+0038 "8" */
    0x7c, 0xe7, 0xc3, 0xc3, 0x66, 0x18, 0x66, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xe7, 0x7b, 0x3,
    0x6, 0x6, 0xc, 0x70,

    /* U+003A ":" */
    0xc0, 0x0, 0xc0,

    /* U+0044 "D" */
    0xf8, 0xc6, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc6, 0xc6, 0xf8,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+005B "[" */
    0xff, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x30, 0xc3, 0xf, 0xc0,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8f, 0xe0,

    /* U+0061 "a" */
    0x78, 0x6, 0x1, 0x80, 0xc7, 0xe6, 0x33, 0x19,
    0x94, 0x7b, 0x80,

    /* U+0063 "c" */
    0x3e, 0x63, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0x60,
    0x3f,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3b, 0x67, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x63, 0x3f,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x60,
    0x3e,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xd, 0xdc, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x60,

    /* U+0069 "i" */
    0x18, 0x0, 0x0, 0x0, 0x78, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0xff,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc3, 0xc6, 0xce,
    0xfc, 0xcc, 0xc6, 0xc7, 0xc3,

    /* U+006C "l" */
    0xf8, 0xc, 0x6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x0, 0xf8,

    /* U+006D "m" */
    0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb,

    /* U+006E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6,
    0xfc, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0072 "r" */
    0xf7, 0x1c, 0xcc, 0x66, 0x3, 0x1, 0x80, 0xc0,
    0x60, 0xfc, 0x0,

    /* U+0073 "s" */
    0x7f, 0x83, 0x7, 0xc7, 0xc3, 0xc1, 0x83, 0xfc,

    /* U+0074 "t" */
    0x30, 0x30, 0x30, 0xff, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x38, 0xf,

    /* U+0076 "v" */
    0xc3, 0xc3, 0x42, 0x66, 0x66, 0x24, 0x3c, 0x3c,
    0x18
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 159, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 159, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 3, .adv_w = 159, .box_w = 2, .box_h = 1, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 159, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 19, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 159, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 159, .box_w = 2, .box_h = 9, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 159, .box_w = 6, .box_h = 15, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 181, .adv_w = 159, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 191, .adv_w = 159, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 159, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 159, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 325, .adv_w = 159, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 159, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x7, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x24,
    0x35, 0x3b, 0x3d, 0x41, 0x43, 0x44, 0x45, 0x48,
    0x49, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x52,
    0x53, 0x54, 0x56
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 87, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 35, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t cascadia17 = {
#else
lv_font_t cascadia17 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CASCADIA17*/

