/*******************************************************************************
 * Size: 19 px
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

    /* U+002D "-" */
    0xff, 0xff, 0xc0,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x1, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30,
    0x18, 0x18, 0xc, 0x4, 0x6, 0x2, 0x3, 0x1,
    0x81, 0x80, 0xc0, 0x0,

    /* U+0030 "0" */
    0x3e, 0x3f, 0x98, 0xd8, 0x3c, 0x1e, 0xef, 0x77,
    0xbb, 0xc1, 0xe0, 0xd8, 0xcf, 0xe3, 0xe0,

    /* U+0031 "1" */
    0x78, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0xff, 0xff,

    /* U+0032 "2" */
    0x3c, 0x3f, 0x31, 0xd8, 0x60, 0x30, 0x18, 0x18,
    0xc, 0x1c, 0x1c, 0x38, 0x1f, 0xff, 0xf8,

    /* U+0033 "3" */
    0x3e, 0x3f, 0xf8, 0xf8, 0x30, 0x10, 0x70, 0xf8,
    0x6, 0x1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+0034 "4" */
    0x1, 0x8c, 0x63, 0x18, 0xc6, 0x61, 0x98, 0x66,
    0x19, 0x86, 0x7f, 0xdf, 0xf0, 0x18, 0x6, 0x1,
    0x80,

    /* U+0035 "5" */
    0x7f, 0x3f, 0x98, 0xc, 0x7, 0xe3, 0xf9, 0xe,
    0x3, 0x1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+0036 "6" */
    0xf, 0x1f, 0x9e, 0xc, 0xc, 0xe6, 0xfb, 0x8f,
    0x83, 0xc1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+0037 "7" */
    0xff, 0xff, 0xec, 0x1b, 0xe, 0xc3, 0x0, 0xc0,
    0x60, 0x18, 0x6, 0x3, 0x0, 0xc0, 0x30, 0x18,
    0x0,

    /* U+0038 "8" */
    0x3e, 0x7f, 0xf8, 0xf8, 0x3e, 0x3b, 0xf1, 0xfd,
    0xc7, 0xc1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+0039 "9" */
    0x3e, 0x3f, 0xb8, 0xf8, 0x3c, 0x1f, 0x1d, 0xf6,
    0x73, 0x3, 0x81, 0x83, 0xcf, 0xc7, 0x80,

    /* U+003A ":" */
    0xfc, 0x0, 0x7, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 178, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 178, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 4, .adv_w = 178, .box_w = 3, .box_h = 3, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 178, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 26, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 178, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 178, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 178, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 178, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 178, .box_w = 3, .box_h = 10, .ofs_x = 4, .ofs_y = 0}
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
const lv_font_t cascadia20 = {
#else
lv_font_t cascadia20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
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

