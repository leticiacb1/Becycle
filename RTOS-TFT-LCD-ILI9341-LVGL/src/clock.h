#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_CLOCK
#define LV_ATTRIBUTE_IMG_CLOCK
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_CLOCK uint8_t clock_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x92, 0x92, 0x92, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0x25, 0x00, 0x25, 0x92, 0xdb, 0xb7, 0xdb, 0x92, 0x25, 0x00, 0x25, 0xdb, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x49, 0x00, 0x92, 0xdb, 0xff, 0xdb, 0x25, 0xdb, 0xff, 0xdb, 0x92, 0x24, 0x25, 0xdb, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x6d, 0x00, 0xb6, 0xff, 0xb7, 0xdb, 0xb7, 0x24, 0xb6, 0xff, 0xb6, 0xff, 0xb7, 0x00, 0x49, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xb7, 0x24, 0x6d, 0xff, 0xff, 0xff, 0xff, 0xb6, 0x24, 0xb6, 0xff, 0xff, 0xff, 0xff, 0x92, 0x00, 0x92, 0xff, 0xff, 
  0xff, 0xff, 0x6e, 0x24, 0xdb, 0xb7, 0xff, 0xff, 0xff, 0xb7, 0x00, 0xb6, 0xff, 0xff, 0xff, 0xb6, 0xff, 0x24, 0x49, 0xff, 0xff, 
  0xff, 0xff, 0x49, 0x25, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0x00, 0xb6, 0xff, 0xff, 0xff, 0xff, 0xff, 0x49, 0x25, 0xff, 0xff, 
  0xff, 0xff, 0x24, 0x49, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xb7, 0x49, 0x25, 0x49, 0x49, 0x49, 0x49, 0xb7, 0x6e, 0x00, 0xdb, 0xff, 
  0xff, 0xff, 0x25, 0x49, 0x92, 0xdb, 0xff, 0xff, 0xff, 0xdb, 0x92, 0x24, 0x00, 0x00, 0x00, 0x24, 0x92, 0x6e, 0x24, 0xdb, 0xff, 
  0xff, 0xff, 0x25, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6d, 0x24, 0xff, 0xff, 
  0xff, 0xff, 0x6d, 0x24, 0xdb, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0x49, 0x49, 0xff, 0xff, 
  0xff, 0xff, 0xb7, 0x00, 0x92, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xb7, 0x00, 0x92, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x49, 0x24, 0xdb, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xdb, 0x25, 0x24, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xdb, 0x24, 0x25, 0xdb, 0xdb, 0xff, 0xff, 0xb6, 0xff, 0xff, 0xb7, 0xdb, 0x25, 0x24, 0x92, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xb7, 0x24, 0x00, 0x6e, 0xdb, 0xff, 0x92, 0xff, 0xdb, 0x6e, 0x00, 0x00, 0x92, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x49, 0x00, 0x00, 0x24, 0x25, 0x00, 0x00, 0x00, 0x49, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x6e, 0x49, 0x25, 0x49, 0x6d, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0xef, 0xb7, 0xbd, 0x10, 0x84, 0xaf, 0x7b, 0x51, 0x8c, 0x96, 0xb5, 0x3c, 0xe7, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0x5d, 0xef, 0x31, 0x8c, 0x24, 0x21, 0x41, 0x08, 0x61, 0x08, 0x62, 0x10, 0x41, 0x08, 0x00, 0x00, 0x24, 0x21, 0xae, 0x73, 0xdb, 0xde, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7a, 0xd6, 0x86, 0x31, 0x82, 0x10, 0x66, 0x31, 0xcf, 0x7b, 0xd7, 0xbd, 0x35, 0xad, 0xf8, 0xc5, 0x72, 0x94, 0x65, 0x29, 0x41, 0x08, 0x45, 0x29, 0xb6, 0xb5, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x9a, 0xd6, 0xc7, 0x39, 0x61, 0x08, 0xf0, 0x83, 0x79, 0xce, 0xff, 0xff, 0x7a, 0xd6, 0x86, 0x31, 0xb6, 0xb5, 0xbf, 0xff, 0x9a, 0xd6, 0x31, 0x8c, 0xa2, 0x10, 0x45, 0x29, 0xb7, 0xbd, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xbe, 0xf7, 0xaa, 0x52, 0x21, 0x08, 0xf3, 0x9c, 0xbf, 0xff, 0x55, 0xad, 0x9a, 0xd6, 0x75, 0xad, 0xa2, 0x10, 0xb3, 0x9c, 0x5d, 0xef, 0xb2, 0x94, 0xdf, 0xff, 0x76, 0xb5, 0x62, 0x10, 0x08, 0x42, 0x1c, 0xe7, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x96, 0xb5, 0xa2, 0x10, 0xab, 0x5a, 0xfc, 0xe6, 0xff, 0xff, 0xbe, 0xf7, 0xff, 0xff, 0xf4, 0xa4, 0x82, 0x10, 0x14, 0xa5, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0xe7, 0xcf, 0x7b, 0x41, 0x08, 0x51, 0x8c, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xdf, 0xff, 0x6e, 0x73, 0x82, 0x10, 0xd7, 0xbd, 0x55, 0xad, 0x3c, 0xe7, 0xff, 0xff, 0xff, 0xff, 0x35, 0xad, 0x82, 0x10, 0xf3, 0x9c, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xf7, 0xd3, 0x9c, 0xbb, 0xde, 0x04, 0x21, 0x08, 0x42, 0xdf, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x5d, 0xef, 0xe7, 0x39, 0x45, 0x29, 0x3d, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x34, 0xa5, 0x82, 0x10, 0xd3, 0x9c, 0xff, 0xff, 0xdf, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0x69, 0x4a, 0x24, 0x21, 0xbb, 0xde, 0xff, 0xff, 
  0xff, 0xff, 0x1c, 0xe7, 0xe3, 0x18, 0x28, 0x42, 0x59, 0xce, 0x7e, 0xf7, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0x96, 0xb5, 0xa7, 0x39, 0x04, 0x21, 0x08, 0x42, 0x49, 0x4a, 0x08, 0x42, 0x49, 0x4a, 0x14, 0xa5, 0x4d, 0x6b, 0x62, 0x10, 0x18, 0xc6, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0xe6, 0x04, 0x21, 0xe8, 0x41, 0x72, 0x94, 0x59, 0xce, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x59, 0xce, 0xaf, 0x7b, 0xc3, 0x18, 0x61, 0x08, 0x41, 0x08, 0x41, 0x08, 0xa2, 0x10, 0xae, 0x73, 0x0c, 0x63, 0xa3, 0x18, 0xd7, 0xbd, 0xff, 0xff, 
  0xff, 0xff, 0x5d, 0xef, 0x45, 0x29, 0xc7, 0x39, 0x9e, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0xf7, 0x7d, 0xef, 0x9e, 0xf7, 0x7d, 0xef, 0x9e, 0xf7, 0x7d, 0xef, 0x7e, 0xf7, 0xcb, 0x5a, 0xa2, 0x10, 0x9a, 0xd6, 0xff, 0xff, 
  0xff, 0xff, 0xdf, 0xff, 0xeb, 0x5a, 0xe3, 0x18, 0x59, 0xce, 0x9a, 0xd6, 0x7e, 0xf7, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0xf7, 0x9a, 0xd6, 0x1c, 0xe7, 0xc7, 0x39, 0xa6, 0x31, 0x9e, 0xf7, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x14, 0xa5, 0x61, 0x08, 0x10, 0x84, 0x79, 0xce, 0xbe, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xf7, 0x59, 0xce, 0x34, 0xa5, 0x41, 0x08, 0xcf, 0x7b, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x7d, 0xef, 0xa7, 0x39, 0xe3, 0x18, 0xb6, 0xb5, 0xff, 0xff, 0x39, 0xce, 0x3c, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5d, 0xef, 0x18, 0xc6, 0xdf, 0xff, 0x9a, 0xd6, 0x24, 0x21, 0xe4, 0x20, 0xfc, 0xe6, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x96, 0xb5, 0xa3, 0x18, 0x45, 0x29, 0xb6, 0xb5, 0xb6, 0xb5, 0x3c, 0xe7, 0xdf, 0xff, 0xf3, 0x9c, 0x5d, 0xef, 0x9e, 0xf7, 0x35, 0xad, 0x59, 0xce, 0x86, 0x31, 0xa2, 0x10, 0x71, 0x8c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x14, 0xa5, 0x04, 0x21, 0x41, 0x08, 0x0c, 0x63, 0x18, 0xc6, 0x1c, 0xe7, 0x51, 0x8c, 0x1c, 0xe7, 0x18, 0xc6, 0x2c, 0x63, 0x82, 0x10, 0x82, 0x10, 0x92, 0x94, 0xbe, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xbd, 0x49, 0x4a, 0x00, 0x00, 0x00, 0x00, 0xa2, 0x10, 0x25, 0x29, 0x62, 0x10, 0x20, 0x00, 0x62, 0x10, 0x86, 0x31, 0x55, 0xad, 0xbe, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0xef, 0x39, 0xce, 0x4d, 0x6b, 0xa7, 0x39, 0x45, 0x29, 0xc7, 0x39, 0xeb, 0x5a, 0x55, 0xad, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit BUT the 2 bytes are swapped*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x7d, 0xbd, 0xb7, 0x84, 0x10, 0x7b, 0xaf, 0x8c, 0x51, 0xb5, 0x96, 0xe7, 0x3c, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xbf, 0xef, 0x5d, 0x8c, 0x31, 0x21, 0x24, 0x08, 0x41, 0x08, 0x61, 0x10, 0x62, 0x08, 0x41, 0x00, 0x00, 0x21, 0x24, 0x73, 0xae, 0xde, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6, 0x7a, 0x31, 0x86, 0x10, 0x82, 0x31, 0x66, 0x7b, 0xcf, 0xbd, 0xd7, 0xad, 0x35, 0xc5, 0xf8, 0x94, 0x72, 0x29, 0x65, 0x08, 0x41, 0x29, 0x45, 0xb5, 0xb6, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xd6, 0x9a, 0x39, 0xc7, 0x08, 0x61, 0x83, 0xf0, 0xce, 0x79, 0xff, 0xff, 0xd6, 0x7a, 0x31, 0x86, 0xb5, 0xb6, 0xff, 0xbf, 0xd6, 0x9a, 0x8c, 0x31, 0x10, 0xa2, 0x29, 0x45, 0xbd, 0xb7, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x52, 0xaa, 0x08, 0x21, 0x9c, 0xf3, 0xff, 0xbf, 0xad, 0x55, 0xd6, 0x9a, 0xad, 0x75, 0x10, 0xa2, 0x9c, 0xb3, 0xef, 0x5d, 0x94, 0xb2, 0xff, 0xdf, 0xb5, 0x76, 0x10, 0x62, 0x42, 0x08, 0xe7, 0x1c, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x10, 0xa2, 0x5a, 0xab, 0xe6, 0xfc, 0xff, 0xff, 0xf7, 0xbe, 0xff, 0xff, 0xa4, 0xf4, 0x10, 0x82, 0xa5, 0x14, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x3c, 0x7b, 0xcf, 0x08, 0x41, 0x8c, 0x51, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xdf, 0x73, 0x6e, 0x10, 0x82, 0xbd, 0xd7, 0xad, 0x55, 0xe7, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xad, 0x35, 0x10, 0x82, 0x9c, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x9c, 0xd3, 0xde, 0xbb, 0x21, 0x04, 0x42, 0x08, 0xff, 0xdf, 0xff, 0xff, 
  0xff, 0xff, 0xef, 0x5d, 0x39, 0xe7, 0x29, 0x45, 0xef, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa5, 0x34, 0x10, 0x82, 0x9c, 0xd3, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xbf, 0x4a, 0x69, 0x21, 0x24, 0xde, 0xbb, 0xff, 0xff, 
  0xff, 0xff, 0xe7, 0x1c, 0x18, 0xe3, 0x42, 0x28, 0xce, 0x59, 0xf7, 0x7e, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xb5, 0x96, 0x39, 0xa7, 0x21, 0x04, 0x42, 0x08, 0x4a, 0x49, 0x42, 0x08, 0x4a, 0x49, 0xa5, 0x14, 0x6b, 0x4d, 0x10, 0x62, 0xc6, 0x18, 0xff, 0xff, 
  0xff, 0xff, 0xe6, 0xfc, 0x21, 0x04, 0x41, 0xe8, 0x94, 0x72, 0xce, 0x59, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xce, 0x59, 0x7b, 0xaf, 0x18, 0xc3, 0x08, 0x61, 0x08, 0x41, 0x08, 0x41, 0x10, 0xa2, 0x73, 0xae, 0x63, 0x0c, 0x18, 0xa3, 0xbd, 0xd7, 0xff, 0xff, 
  0xff, 0xff, 0xef, 0x5d, 0x29, 0x45, 0x39, 0xc7, 0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0xef, 0x7d, 0xf7, 0x9e, 0xef, 0x7d, 0xf7, 0x9e, 0xef, 0x7d, 0xf7, 0x7e, 0x5a, 0xcb, 0x10, 0xa2, 0xd6, 0x9a, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xdf, 0x5a, 0xeb, 0x18, 0xe3, 0xce, 0x59, 0xd6, 0x9a, 0xf7, 0x7e, 0xff, 0xdf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 0xd6, 0x9a, 0xe7, 0x1c, 0x39, 0xc7, 0x31, 0xa6, 0xf7, 0x9e, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa5, 0x14, 0x08, 0x61, 0x84, 0x10, 0xce, 0x79, 0xf7, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0xce, 0x59, 0xa5, 0x34, 0x08, 0x41, 0x7b, 0xcf, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xef, 0x7d, 0x39, 0xa7, 0x18, 0xe3, 0xb5, 0xb6, 0xff, 0xff, 0xce, 0x39, 0xe7, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xc6, 0x18, 0xff, 0xdf, 0xd6, 0x9a, 0x21, 0x24, 0x20, 0xe4, 0xe6, 0xfc, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x96, 0x18, 0xa3, 0x29, 0x45, 0xb5, 0xb6, 0xb5, 0xb6, 0xe7, 0x3c, 0xff, 0xdf, 0x9c, 0xf3, 0xef, 0x5d, 0xf7, 0x9e, 0xad, 0x35, 0xce, 0x59, 0x31, 0x86, 0x10, 0xa2, 0x8c, 0x71, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xa5, 0x14, 0x21, 0x04, 0x08, 0x41, 0x63, 0x0c, 0xc6, 0x18, 0xe7, 0x1c, 0x8c, 0x51, 0xe7, 0x1c, 0xc6, 0x18, 0x63, 0x2c, 0x10, 0x82, 0x10, 0x82, 0x94, 0x92, 0xf7, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xb7, 0x4a, 0x49, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa2, 0x29, 0x25, 0x10, 0x62, 0x00, 0x20, 0x10, 0x62, 0x31, 0x86, 0xad, 0x55, 0xf7, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x7d, 0xce, 0x39, 0x6b, 0x4d, 0x39, 0xa7, 0x29, 0x45, 0x39, 0xc7, 0x5a, 0xeb, 0xad, 0x55, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format: Fix 0xFF: 8 bit, Red: 8 bit, Green: 8 bit, Blue: 8 bit*/
  0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0xf4, 0xf4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 
  0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xea, 0xea, 0xea, 0xff, 0xb4, 0xb4, 0xb4, 0xff, 0x80, 0x80, 0x80, 0xff, 0x75, 0x75, 0x75, 0xff, 0x86, 0x86, 0x86, 0xff, 0xae, 0xae, 0xae, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0x85, 0x85, 0x85, 0xff, 0x22, 0x22, 0x22, 0xff, 0x09, 0x09, 0x09, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0d, 0x0d, 0x0d, 0xff, 0x07, 0x07, 0x07, 0xff, 0x00, 0x00, 0x00, 0xff, 0x22, 0x22, 0x22, 0xff, 0x72, 0x72, 0x72, 0xff, 0xd6, 0xd6, 0xd6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 
  0xfc, 0xfc, 0xfc, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0x2f, 0x2f, 0x2f, 0xff, 0x0e, 0x0e, 0x0e, 0xff, 0x2d, 0x2d, 0x2d, 0xff, 0x77, 0x77, 0x77, 0xff, 0xb8, 0xb8, 0xb8, 0xff, 0xa5, 0xa5, 0xa5, 0xff, 0xbc, 0xbc, 0xbc, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x2a, 0x2a, 0x2a, 0xff, 0x08, 0x08, 0x08, 0xff, 0x29, 0x29, 0x29, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 
  0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0x38, 0x38, 0x38, 0xff, 0x0b, 0x0b, 0x0b, 0xff, 0x7c, 0x7c, 0x7c, 0xff, 0xca, 0xca, 0xca, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xcd, 0xcd, 0xcd, 0xff, 0x2e, 0x2e, 0x2e, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xce, 0xce, 0xce, 0xff, 0x84, 0x84, 0x84, 0xff, 0x12, 0x12, 0x12, 0xff, 0x28, 0x28, 0x28, 0xff, 0xb4, 0xb4, 0xb4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfd, 0xfd, 0xfd, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xf3, 0xf3, 0xf3, 0xff, 0x53, 0x53, 0x53, 0xff, 0x04, 0x04, 0x04, 0xff, 0x9a, 0x9a, 0x9a, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xa6, 0xa6, 0xa6, 0xff, 0xcf, 0xcf, 0xcf, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0x12, 0x12, 0x12, 0xff, 0x95, 0x95, 0x95, 0xff, 0xe9, 0xe9, 0xe9, 0xff, 0x93, 0x93, 0x93, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xad, 0xad, 0xad, 0xff, 0x0d, 0x0d, 0x0d, 0xff, 0x40, 0x40, 0x40, 0xff, 0xdf, 0xdf, 0xdf, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfc, 0xfc, 0xfc, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xae, 0xae, 0xae, 0xff, 0x12, 0x12, 0x12, 0xff, 0x54, 0x54, 0x54, 0xff, 0xdd, 0xdd, 0xdd, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xf3, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0x9c, 0x9c, 0xff, 0x10, 0x10, 0x10, 0xff, 0x9e, 0x9e, 0x9e, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xe2, 0xe2, 0xe2, 0xff, 0x77, 0x77, 0x77, 0xff, 0x08, 0x08, 0x08, 0xff, 0x86, 0x86, 0x86, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0x6d, 0x6d, 0x6d, 0xff, 0x10, 0x10, 0x10, 0xff, 0xb6, 0xb6, 0xb6, 0xff, 0xa7, 0xa7, 0xa7, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x0e, 0x0e, 0x0e, 0xff, 0x9b, 0x9b, 0x9b, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xf3, 0xf3, 0xf3, 0xff, 0x99, 0x99, 0x99, 0xff, 0xd5, 0xd5, 0xd5, 0xff, 0x1f, 0x1f, 0x1f, 0xff, 0x40, 0x40, 0x40, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe8, 0xe8, 0xe8, 0xff, 0x3b, 0x3b, 0x3b, 0xff, 0x29, 0x29, 0x29, 0xff, 0xe4, 0xe4, 0xe4, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xa2, 0xa2, 0xa2, 0xff, 0x0e, 0x0e, 0x0e, 0xff, 0x99, 0x99, 0x99, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xf4, 0xf4, 0xf4, 0xff, 0x4a, 0x4a, 0x4a, 0xff, 0x22, 0x22, 0x22, 0xff, 0xd5, 0xd5, 0xd5, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 
  0xfd, 0xfd, 0xfd, 0xff, 0xde, 0xde, 0xde, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0x43, 0x43, 0x43, 0xff, 0xc8, 0xc8, 0xc8, 0xff, 0xed, 0xed, 0xed, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xaf, 0xaf, 0xaf, 0xff, 0x35, 0x35, 0x35, 0xff, 0x20, 0x20, 0x20, 0xff, 0x41, 0x41, 0x41, 0xff, 0x47, 0x47, 0x47, 0xff, 0x3f, 0x3f, 0x3f, 0xff, 0x47, 0x47, 0x47, 0xff, 0xa1, 0xa1, 0xa1, 0xff, 0x69, 0x69, 0x69, 0xff, 0x0c, 0x0c, 0x0c, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfb, 0xfb, 0xfb, 0xff, 0xdc, 0xdc, 0xdc, 0xff, 0x20, 0x20, 0x20, 0xff, 0x3c, 0x3c, 0x3c, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0xc9, 0xc9, 0xc9, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xc9, 0xc9, 0xc9, 0xff, 0x74, 0x74, 0x74, 0xff, 0x19, 0x19, 0x19, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x06, 0x06, 0x06, 0xff, 0x07, 0x07, 0x07, 0xff, 0x13, 0x13, 0x13, 0xff, 0x73, 0x73, 0x73, 0xff, 0x61, 0x61, 0x61, 0xff, 0x15, 0x15, 0x15, 0xff, 0xb8, 0xb8, 0xb8, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe9, 0xe9, 0xe9, 0xff, 0x27, 0x27, 0x27, 0xff, 0x37, 0x37, 0x37, 0xff, 0xee, 0xee, 0xee, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xee, 0xee, 0xee, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0xf1, 0xf1, 0xf1, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0xec, 0xec, 0xec, 0xff, 0x57, 0x57, 0x57, 0xff, 0x12, 0x12, 0x12, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfc, 0xfc, 0xfc, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0x5b, 0x5b, 0x5b, 0xff, 0x1b, 0x1b, 0x1b, 0xff, 0xc7, 0xc7, 0xc7, 0xff, 0xce, 0xce, 0xce, 0xff, 0xed, 0xed, 0xed, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xef, 0xef, 0xef, 0xff, 0xcf, 0xcf, 0xcf, 0xff, 0xe0, 0xe0, 0xe0, 0xff, 0x36, 0x36, 0x36, 0xff, 0x33, 0x33, 0x33, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 
  0xfb, 0xfb, 0xfb, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xa0, 0xa0, 0xa0, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x7e, 0x7e, 0x7e, 0xff, 0xcb, 0xcb, 0xcb, 0xff, 0xf2, 0xf2, 0xf2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xf3, 0xff, 0xc6, 0xc6, 0xc6, 0xff, 0xa2, 0xa2, 0xa2, 0xff, 0x07, 0x07, 0x07, 0xff, 0x78, 0x78, 0x78, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfa, 0xfa, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0x34, 0x34, 0x34, 0xff, 0x1a, 0x1a, 0x1a, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xc4, 0xc4, 0xc4, 0xff, 0xe2, 0xe2, 0xe2, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xc1, 0xc1, 0xc1, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xce, 0xce, 0xce, 0xff, 0x23, 0x23, 0x23, 0xff, 0x1c, 0x1c, 0x1c, 0xff, 0xdc, 0xdc, 0xdc, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xb1, 0xb1, 0xb1, 0xff, 0x14, 0x14, 0x14, 0xff, 0x28, 0x28, 0x28, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xb3, 0xb3, 0xb3, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0x9b, 0x9b, 0x9b, 0xff, 0xe8, 0xe8, 0xe8, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0xc9, 0xc9, 0xc9, 0xff, 0x2f, 0x2f, 0x2f, 0xff, 0x12, 0x12, 0x12, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfe, 0xfe, 0xfe, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xa1, 0xa1, 0xa1, 0xff, 0x1e, 0x1e, 0x1e, 0xff, 0x09, 0x09, 0x09, 0xff, 0x60, 0x60, 0x60, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xde, 0xde, 0xde, 0xff, 0x89, 0x89, 0x89, 0xff, 0xe1, 0xe1, 0xe1, 0xff, 0xc1, 0xc1, 0xc1, 0xff, 0x62, 0x62, 0x62, 0xff, 0x0e, 0x0e, 0x0e, 0xff, 0x0f, 0x0f, 0x0f, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0xf2, 0xf2, 0xf2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xb5, 0xb5, 0xb5, 0xff, 0x49, 0x49, 0x49, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x13, 0x13, 0x13, 0xff, 0x25, 0x25, 0x25, 0xff, 0x0c, 0x0c, 0x0c, 0xff, 0x03, 0x03, 0x03, 0xff, 0x0c, 0x0c, 0x0c, 0xff, 0x31, 0x31, 0x31, 0xff, 0xa9, 0xa9, 0xa9, 0xff, 0xf3, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeb, 0xeb, 0xeb, 0xff, 0xc4, 0xc4, 0xc4, 0xff, 0x67, 0x67, 0x67, 0xff, 0x35, 0x35, 0x35, 0xff, 0x29, 0x29, 0x29, 0xff, 0x39, 0x39, 0x39, 0xff, 0x5b, 0x5b, 0x5b, 0xff, 0xa9, 0xa9, 0xa9, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0xf4, 0xf4, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xfa, 0xfa, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfd, 0xfd, 0xfd, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf7, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0xf6, 0xf6, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
#endif
};

const lv_img_dsc_t clock = {
  .header.cf = LV_IMG_CF_TRUE_COLOR,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 21,
  .header.h = 21,
  .data_size = 441 * LV_COLOR_SIZE / 8,
  .data = clock_map,
};
