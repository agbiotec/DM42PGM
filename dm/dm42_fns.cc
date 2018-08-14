/*

  Copyright (c) 2018 SwissMicros GmbH

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

  3. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.


  The SDK and related material is released as “NOMAS”  (NOt MAnufacturer Supported).

  1. Info is released to assist customers using, exploring and extending the product
  2. Do NOT contact the manufacturer with questions, seeking support, etc. regarding
     NOMAS material as no support is implied or committed-to by the Manufacturer
  3. The Manufacturer may reply and/or update materials if and when needed solely at
     their discretion

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "core_main.h"
#include "core_aux.h"


//#define OLD_PRINTER_CHAR_MASKING

#ifdef OLD_PRINTER_CHAR_MASKING

const unsigned char hp2printer_table[] = {
  129, // 00 - ÷                division sign (U+00F7)
  130, // 01 - ×                multiplication sign (U+00D7)
  131, // 02 - √                square root (U+221A)
  132, // 03 - ∫                integral (U+222B)
  127, // 04 - ▒        medium shade (U+2592)
  133, // 05 - Σ                greek capital letter sigma (U+03A3)
  134, // 06 - ▶                black right-pointing triangle (U+25B6)
  135, // 07 - π                greek small letter pi (U+03C0)
  185, // 08 - ¿                inverted question mark (U+00BF)
  137, // 09 - ≤                less-than or equal to (U+2264)
  144, // 0a - LF       symbol for line feed (U+240A)
  138, // 0b - ≥                greater-than or equal to (U+2265)
  139, // 0c - ≠                not equal to (U+2260)
  244, // 0d - ↲ CR subst. by ¶ downwards arrow with tip leftwards (U+21B2)
  'v', // 0e - ↓                downwards arrow (U+2193)
  141, // 0f - →                rightwards arrow (U+2192)
  142, // 10 - ←                leftwards arrow (U+2190)
  143, // 11 - μ                greek small letter mu (U+03BC)
  175, // 12 - £                pound sign (U+00A3)
  145, // 13 - °                degree sign (U+00B0)
  208, // 14 - Å                latin capital letter a with ring above (U+00C5)
  182, // 15 - Ñ                latin capital letter n with tilde (U+00D1)
  216, // 16 - Ä                latin capital letter a with diaeresis (U+00C4)
  160, // 17 - ∡                measured angle (U+2221)
  'E', // 18 - ᴇ   subst. by E  latin letter small capital e (U+1D07)
  211, // 19 - Æ                latin capital letter ae (U+00C6)
  155, // 1a - …   subst by ..  horizontal ellipsis (U+2026)
  163, //1b-ESC s.by È   symbol for escape (U+241B)
  218, // 1c - Ö                latin capital letter o with diaeresis (U+00D6)
  219, // 1d - Ü                latin capital letter u with diaeresis (U+00DC)
  127, // 1e - ▒                medium shade (U+2592)
  242, // 1f - ■                black square (U+25A0)
  148, // 7f - ├                box drawings light vertical and right (U+251C)
  ':', // 80 - ﹕   subst. by :
  'Y'  // 81 - ʏ   subst. by Y
};

#else

const unsigned char hp2printer_table[] = {
  129, // 00 - ÷                division sign (U+00F7)
  130, // 01 - ×                multiplication sign (U+00D7)
  131, // 02 - √                square root (U+221A)
  132, // 03 - ∫                integral (U+222B)
  0x4, // 127, // 04 - ▒        medium shade (U+2592)
  133, // 05 - Σ                greek capital letter sigma (U+03A3)
  134, // 06 - ▶                black right-pointing triangle (U+25B6)
  135, // 07 - π                greek small letter pi (U+03C0)
  185, // 08 - ¿                inverted question mark (U+00BF)
  137, // 09 - ≤                less-than or equal to (U+2264)
  0xa, // 144, // 0a - LF       symbol for line feed (U+240A)
  138, // 0b - ≥                greater-than or equal to (U+2265)
  139, // 0c - ≠                not equal to (U+2260)
  244, // 0d - ↲ CR subst. by ¶ downwards arrow with tip leftwards (U+21B2)
  'v', // 0e - ↓                downwards arrow (U+2193)
  141, // 0f - →                rightwards arrow (U+2192)
  142, // 10 - ←                leftwards arrow (U+2190)
  143, // 11 - μ                greek small letter mu (U+03BC)
  175, // 12 - £                pound sign (U+00A3)
  145, // 13 - °                degree sign (U+00B0)
  208, // 14 - Å                latin capital letter a with ring above (U+00C5)
  182, // 15 - Ñ                latin capital letter n with tilde (U+00D1)
  216, // 16 - Ä                latin capital letter a with diaeresis (U+00C4)
  160, // 17 - ∡                measured angle (U+2221)
  'E', // 18 - ᴇ   subst. by E  latin letter small capital e (U+1D07)
  211, // 19 - Æ                latin capital letter ae (U+00C6)
  155, // 1a - …   subst by ..  horizontal ellipsis (U+2026)
 0x1b, //163, //1b-ESC s.by È   symbol for escape (U+241B)
  218, // 1c - Ö                latin capital letter o with diaeresis (U+00D6)
  219, // 1d - Ü                latin capital letter u with diaeresis (U+00DC)
  127, // 1e - ▒                medium shade (U+2592)
  242, // 1f - ■                black square (U+25A0)
  148, // 7f - ├                box drawings light vertical and right (U+251C)
  ':', // 80 - ﹕   subst. by :
  'Y'  // 81 - ʏ   subst. by Y
};
#endif


int hp2print(char *dst, const char *src, int srclen) {
  unsigned char c;

  for (int s = 0; s < srclen; s++) {
    c = src[s];
#ifdef OLD_PRINTER_CHAR_MASKING
    // Characters in command names could have 7th bit set -> mask everything outside 0-0x81 range
    if (c > 0x81) c &= 0x7f;

    // Special characters are 00-1F,7f-81
    if (c < ' ' || c >= 0x7f ) {
      if ( c >= 0x7f ) c -= 0x7f - ' '; // Map chars 0x7f-0x81 to 0x20-0x22
      c = hp2printer_table[c]; // Translate to printer chars
    }
#else
    
    if (c == 0x7f) c = 148; // 7f to |-
    if (c == 0x8a) c = 144; // 8a to LF
    // Special characters are 00-1F
    if (c < ' ')
      c = hp2printer_table[c]; // Translate to printer chars

#endif

    *dst++ = c;
  }
  return srclen;
}


int hp2ascii(char *dst, const char *src, int srclen) {
  const char *esc;
  unsigned char c;
  int s, d = 0;
  for (s = 0; s < srclen; s++) {
    c = src[s];
    if (c >= 130 && c != 138)
        c &= 0x7f;
    switch (c) {
      case  0:   esc = "\xf7"; break; // ÷
      case  1:   esc = "\xd7"; break; // ×
      case  2:   esc = "\\sqrt"; break;
      case  3:   esc = "\\int";  break;
      case  4:   esc = "\\gray1";break;
      case  5:   esc = "\\Sigma";break;
      case  6:   esc = ">";    break;
      case  7:   esc = "\\pi"; break;
      case  8:   esc = "\xbf"; break; // ¿
      case  9:   esc = "<=";   break;
      case 11:   esc = ">=";   break;
      case 12:   esc = "!=";   break;
      case 13:   esc = "\\r";  break;
      case 14:   esc = "v";    break;
      case 15:   esc = "->";   break;
      case 16:   esc = "<-";   break;
      case 17:   esc = "\xb5"; break; // µ
      case 18:   esc = "\xa3"; break; // £
      case 19:   esc = "\xb0"; break; // °
      case 20:   esc = "\xc5"; break; // Å
      case 21:   esc = "\xd1"; break; // Ñ
      case 22:   esc = "\xc4"; break; // Ä
      //case 23: esc = "\\angle"; break;
      case 23:   esc = "<";    break;
      case 24:   esc = "E";    break;
      case 25:   esc = "\xc6"; break; // Æ
      case 26:   esc = "...";  break;
      case 27:   esc = "\\esc";break;
      case 28:   esc = "\xd6"; break; // Ö
      case 29:   esc = "\xdc"; break; // Ü
      case 30:   esc = "\\gray2"; break;
      case 31:   esc = "\\bullet";break;
      case '\\': esc = "\\\\"; break;
      case 127:  esc = "|-";   break;
      case 128:  esc = ":";    break;
      case 129:  esc = "y";    break;
      case 138:  esc = "\\LF"; break;
      default:   dst[d++] = c; continue;
    }
    while (*esc != 0)
        dst[d++] = *esc++;
  }
  return d;
}


int hp2font(char *dst, const char *src, int srclen) {
  unsigned char c;
  int s, d = 0;
  for (s = 0; s < srclen; s++) {
    c = src[s];
    if (c == 0x80) {
      if ( dst[d-1] == 'x' ) dst[d-1]='X';
      dst[d++] = ':';
      continue; 
    }
    if (c == 0x81) { dst[d++] = 'Y';    continue; }
    c &= 0x7f;
    if (c < ' ')   { dst[d++] = c|0x80; continue; }
    dst[d++] = c;
  }
  dst[d] = 0;
  return d;
}


#if 0 // Old fonts
int hp2regs(char *dst, const char *src, int srclen) {
  const char *esc;
  unsigned char c;
  int s, d = 0;
  for (s = 0; s < srclen; s++) {
    c = src[s];
    if (c >= 130 && c != 138)
        c &= 127;
    switch (c) {
      case  0:   esc = "\xf7"; break; // ÷
      case  1:   esc = "\xd7"; break; // ×
      case  2:   esc = "\\sqrt"; break;
      case  3:   esc = "\\int";  break;
      case  4:   esc = "\\gray1";break;
      case  5:   esc = "\\Sigma";break;
      case  6:   esc = ">";    break;
      case  7:   esc = "\\pi"; break;
      case  8:   esc = "\xbf"; break; // ¿
      case  9:   esc = "<=";   break;
      case 11:   esc = ">=";   break;
      case 12:   esc = "!=";   break;
      case 13:   esc = "\\r";  break;
      case 14:   esc = "v";    break;
      case 15:   esc = "->";   break;
      case 16:   esc = "<-";   break;
      case 17:   esc = "\xb5"; break; // µ
      case 18:   esc = "\xa3"; break; // £
      case 19:   esc = "\xb0"; break; // °
      case 20:   esc = "\xc5"; break; // Å
      case 21:   esc = "\xd1"; break; // Ñ
      case 22:   esc = "\xc4"; break; // Ä
      case 23:   esc = "\x80"; break; // Angle
      case 24:   esc = "\x81"; break; // Exp
      case 25:   esc = "\xc6"; break; // Æ
      case 26:   esc = "...";  break;
      case 27:   esc = "\\esc";break;
      case 28:   esc = "\xd6"; break; // Ö
      case 29:   esc = "\xdc"; break; // Ü
      case 30:   esc = "\\gray2"; break;
      case 31:   esc = "\\bullet";break;
      case '\\': esc = "\\\\"; break;
      case 127:  esc = "|-";   break;
      case 128:  esc = ":";    break;
      case 129:  esc = "y";    break;
      case 138:  esc = "\\LF"; break;
      default:   dst[d++] = c; continue;
    }
    while (*esc != 0)
        dst[d++] = *esc++;
  }
  return d;
}
#endif



/* ▄▄   ▄▄▄▄▄  ▄    ▄
   ██   █   ▀█ ██  ██
  █  █  █▄▄▄▄▀ █ ██ █
  █▄▄█  █   ▀▄ █ ▀▀ █
 █    █ █    ▀ █    █ */

#ifndef FW_RELEASE
#define SHELL_DEBUG
//#define SHELL_DEBUG_STATE_RW
#define THELL_DEBUG
#endif

#ifdef SHELL_DEBUG
  //#define DBGSHELL(...) lcd_print(__VA_ARGS__)
  #define DBGSHELL(...) printf(__VA_ARGS__)
  #define DBG_NOLCD
#else
  #define DBGSHELL(...)
#endif

#ifdef THELL_DEBUG
  //#define DBGSHELL(...) lcd_print(__VA_ARGS__)
  #define DBGTHELL(...) printf(__VA_ARGS__)
#else
  #define DBGTHELL(...)
#endif

#if defined(SHELL_DEBUG_STATE_RW) && defined(SHELL_DEBUG)
  #define DUMPBUF(buf,...)  dump_buffer((char*)buf,__VA_ARGS__)
  #define DBGSHELL_STATE_RW(...) DBGSHELL(__VA_ARGS__)
#else
  #define DBGSHELL_STATE_RW(...)
  #define DUMPBUF(...)
#endif



extern "C" {
  
// -- External prototypes
#include <main.h>
#include <dmcp.h>

#include <dm42_menu.h>
#include <dm42_fns.h>

#ifndef assert_param
#define assert_param(c)
#endif


// -- Local prototypes --
void setTimeout3(int ms_value);
void start_runner();
void disp_header();
void disp_regs(int what);
int savestat_init(int save_ix);
void savestat_erase(int save_ix);
int header_timeout();
int lcd_update_timeout();
void clear_lcd_update_timeout();
void set_lcd_update_timeout();
void skin_repaint_annunciator(int which, bool state);
// ----------------------
extern uint8_t is_graphics;
// ----------------------



//uint8_t draw_old_lcd = 0;
//uint8_t disp_main_menu = 0;
uint8_t disp_was_menu_drawn = 0;

int8_t reg_font_ix = 5; // Default register font
int8_t pgm_font_ix = 2; // Default program font

uint32_t reg_font_offset = 0;        // Default font offsets
uint32_t stack_layout = STACK_XYZT;  // Default stack layout

#define REG_ALIGN_LEFT  2
#define REG_LINES       1


#define is_REG_ALIGN_LEFT  (draw_reg_mode & REG_ALIGN_LEFT)
#define is_REG_LINES       (draw_reg_mode & REG_LINES)

#define DRAW_REG_MODE_MAX  REG_ALIGN_LEFT

// 0 - RIGHT no lines
// 1 - RIGHT with lines
// 2 - LEFT
uint8_t draw_reg_mode = REG_ALIGN_LEFT;



#define TIMEOUT_REPEAT  0
#define TIMEOUT_CORE1   1
#define TIMEOUT_CORE2   2
#define TIMEOUT_CORE3   3


static uint8_t timeout0_type = TIMEOUT_REPEAT;

uint8_t decimal_point = 1;
volatile bool core_initialized;
volatile  int repeat_timeout;


// Savestat data
//#define SAVEST_BASE    (QSPI_SAVESTAT)
//#define SAVEST_SIZE            0x18000
//#define SAVEST_DATA_OFFS          0x20
//#define SAVEST_CNT                   4
// Savestat index values
//#define SAVEST_EMPTY    0xFFFFFFFF
//#define SAVEST_NONE              0
//#define SAVEST_NEWEST           -1
//#define SAVEST_FREE             -2

#define SAVESTAT_MAGIC  0xd342da7a
//#define SAVESTAT_FLAG_BEEP_MUTE   BIT(0)  // Using calc flag now
#define SAVESTAT_FLAG_SLOW_AUTOREP  BIT(1)
#define SAVESTAT_FLAG_DISP_VOLTAGE  BIT(2)
#define SAVESTAT_FLAG_REG_LEFT      BIT(3)
#define SAVESTAT_FLAG_REG_LINES     BIT(4)
#define SAVESTAT_FLAG_GMODE0        BIT(5)
#define SAVESTAT_FLAG_GMODE1        BIT(6)
#define SAVESTAT_FLAG_REFLCD0       BIT(7)
#define SAVESTAT_FLAG_REFLCD1       BIT(8)
#define SAVESTAT_FLAG_REFLCD2       BIT(9)

#define SAVESTAT_DISP_STATFN       BIT(10)
#define SAVESTAT_DISP_DOW          BIT(11)
#define SAVESTAT_DISP_DATE         BIT(12)
#define SAVESTAT_DISP_DATE_SEP0    BIT(13)
#define SAVESTAT_DISP_DATE_SEP1    BIT(14)
#define SAVESTAT_DISP_SHORTMON     BIT(15)
#define SAVESTAT_DISP_TIME         BIT(16)

#define SAVESTAT_PERM_MAIN_MENU    BIT(17)


typedef struct {
  uint32_t magic;         // Magic for check
  uint32_t flags;         // Save flags
  char platf_ver[12];     // Platform version
  uint8_t  century;       // Current century
  uint8_t  printer_delay; // Printer delay in cs
  uint8_t  reg_font_ix;   // Current register font index
  uint8_t  stack_layout;  // Current stack layout
  uint8_t  pgm_font_ix;   // Current program font index
  uint8_t  font_offsets[3];// Register font offsets
  uint8_t  dummy[4];      // .. for future use
} __packed savestat_data_t;


STATIC_ASSERT(sizeof(savestat_data_t) == 32, "sizeof(savestat_header_t) != 32");


//uint8_t savestat_ix = 0;     // Current savestat in use

// Pointers for load/save state functions
uint8_t * pgm_ptr;
int pgm_sz = 0;

// Program load/save
FRESULT pgm_res = FR_OK;

// ---

#define     ANN(x)      VAL(ANN_ ## x, ann_state)
#define VAL_ANN(x)      VAL(x,ann_state)
#define CLR_ANN(x)      CLR(x,ann_state)
#define SET_ANN(x)      SET(x,ann_state)
#define NOT_ANN(x)      (!ANN(x))
#define SETMSK_ANN(x,m) SETMSK(x,m,ann_state) 
#define SETBY_ANN(c,x)  SETBY(c,x,ann_state)


// Annunciators
#define ANN_UPDOWN      BIT(0)
#define ANN_SHIFT       BIT(1)
#define ANN_PRINT       BIT(2)
#define ANN_RUN         BIT(3)
#define ANN_BATTERY     BIT(4)
#define ANN_G           BIT(5)
#define ANN_RAD         BIT(6)
#define ANN_CNT             7


// Program state

#define     PS(x)      VAL(PST_ ## x, pgm_state)
#define VAL_PS(x)      VAL(PST_ ## x,pgm_state)
#define CLR_PS(x)      CLR(PST_ ## x,pgm_state)
#define SET_PS(x)      SET(PST_ ## x,pgm_state)
#define NOT_PS(x)      (!PS(x))
#define SETMSK_PS(x,m) SETMSK(PST_ ## x,m,pgm_state) 
#define SETBY_PS(c,x)  SETBY(c,PST_ ## x,pgm_state)


#define PST_DISP_VOLTAGE      BIT(0)
#define PST_DISP_STATFN       BIT(1)
#define PST_DISP_DOW          BIT(2)
#define PST_DISP_DATE         BIT(3)
#define PST_DISP_DATE_SEP0    BIT(4)
#define PST_DISP_DATE_SEP1    BIT(5)
#define PST_DISP_SHORTMON     BIT(6)
#define PST_DISP_TIME         BIT(7)

#define PST_PERM_MAIN_MENU    BIT(8)


static volatile uint32_t ann_state = 0;
static volatile uint32_t pgm_state = 0;


#define LCD_CHG_FORCE    8
#define LCD_CHG_HEADER   4
#define LCD_CHG_REGS     2
#define LCD_CHG_LCD      1

static uint32_t lcd_changed = 0;
static uint32_t last_header_min;

#define LCD_HP_CHARS 22
#define LCD_UPDATE_TIMEOUT    200

static uint32_t last_lcd_update_ms = 0;

#define TLCD_LINELEN   LCD_HP_CHARS
char tlcd[2][TLCD_LINELEN+1];


//char annstr[64];

// Just flag for calc_runner initialization
int read_statefile; /// ???? really here?




/* Alpha translation table 

   +--------+--------+--------+--------+--------+--------+
   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |
   |   38   |   39   |   40   |   41   |   42   |   43   |
   +--------+--------+--------+--------+--------+--------+
 S |  Sum-  |  y^x   |  x^2   |  10^x  |  e^x   |  GTO   |
   |  Sum+  |  1/x   |  Sqrt  |  Log   |  Ln    |  XEQ   |
   |   1    |   2    |   3    |   4    |   5    |   6    |
 A |   A    |   B    |   C    |   D    |   E    |   F    |
   +--------+--------+--------+--------+--------+--------+
 S | Complx |   %    |  Pi    |  ASIN  |  ACOS  |  ATAN  |
   |  STO   |  RCL   |  R_dwn |   SIN  |   COS  |   TAN  |
   |   7    |   8    |   9    |   10   |   11   |   12   |
 A |   G    |   H    |   I    |    J   |    K   |    L   |
   +--------+--------+--------+--------+--------+--------+
 S |     Alpha       | Last x |  MODES |  DISP  |  CLEAR |
   |     ENTER       |  x<>y  |  +/-   |   E    |   <--  |
   |       13        |   14   |   15   |   16   |   17   |
 A |                 |    M   |    N   |    O   |        |
   +--------+--------+-+------+----+---+-------++--------+
 S |   BST  | Solver   |  Int f(x) |  Matrix   |  STAT   |
   |   Up   |    7     |     8     |     9     |   /     |
   |   18   |   19     |    20     |    21     |   22    |
 A |        |    P     |     Q     |     R     |    S    |
   +--------+----------+-----------+-----------+---------+
 S |   SST  |  BASE    |  CONVERT  |  FLAGS    |  PROB   |
   |  Down  |    4     |     5     |     6     |    x    |
   |   23   |   24     |    25     |    26     |   27    |
 A |        |    T     |     U     |     V     |    W    |
   +--------+----------+-----------+-----------+---------+
 S |        | ASSIGN   |  CUSTOM   |  PGM.FCN  |  PRINT  |
   |  SHIFT |    1     |     2     |     3     |    -    |
   |   28   |   29     |    30     |    31     |   32    |
 A |        |    x     |     Y     |     Z     |    -    |
   +--------+----------+-----------+-----------+---------+
 S |  OFF   |  TOP.FCN |   SHOW    |   PRGM    | CATALOG |
   |  EXIT  |    0     |     .     |    R/S    |    +    |
   |   33   |   34     |    35     |    36     |   37    |
 A |        |    :     |     .     |     ?     |   ' '   |
   +--------+----------+-----------+-----------+---------+

*/


const char alpha_upper_transl[] = "_" // code 0 unused
  "ABCDEF"
  "GHIJKL"
   "_MNO_"
   "_PQRS"
   "_TUVW"
   "_XYZ-"
   "_:._ ";
//   "_:.? "; // R/S used in alpha mode !

const char alpha_lower_transl[] = "_" // code 0 unused
  "abcdef"
  "ghijkl"
   "_mno_"
   "_pqrs"
   "_tuvw"
   "_xyz-"
   "_:._ ";
//   "_:.? "; // R/S used in alpha mode !


const char alpha_shift_upper_transl[] = "_" // code 0 unused
  "ABCDEF"
  "GHIJKL"
   "_MNO_"
   "_789/"
   "_456*"
   "_123-"
   "_0.?+";


const char alpha_shift_lower_transl[] = "_" // code 0 unused
  "abcdef"
  "ghijkl"
   "_mno_"
   "_789/"
   "_456*"
   "_123-"
   "_0.?+";


const char *alpha_tables[] = {
  NULL,                 // Orig table -> no translation
  alpha_upper_transl,
  alpha_lower_transl
};


const char *alpha_shift_tables[] = {
  NULL,                 // Orig table -> no translation
  alpha_shift_upper_transl,
  alpha_shift_lower_transl
};


/*
const char alpha_shift_transl[] = "_" // code 0 unused
  "abcdef"
  "ghijkl"
   "_MNO_"
   "_789/"
   "_456*"
   "_123-"
   "_0.?+";
*/


// Calculator icons
const char ann00[] = 
#include "data/ann00.c"
;

// Alpha annunciator
const char ann01[] = 
#include "data/ann01.c"
;

// USB and battery icons
const char ann02[] = 
#include "data/ann02.c"
;

// Flag icons
const char ann03[] = 
#include "data/ann03.c"
;


//const  uint8_t ann_offs[ANN_CNT]    = { 0, 4, 8, 13, 16, 20, 22};
const  uint8_t ann_offs[ANN_CNT]    = { 0, 4, 9, 14, 17, 21, 23};
const  uint8_t ann_dx[ANN_CNT+1]    = { 4, 5, 5,  3,  4,  2,  4,  3};
//const uint16_t ann_lcd_x[ANN_CNT+1] = { 8,48,96,120,160,184,210,300}; // Old one
const uint16_t ann_lcd_x[ANN_CNT+1]   = { 8,48,88,112,  0,128,156,300}; // Old one

#define ANN_BPL    26 // Bytes per line
#define ANN2_BPL   32 // Bytes per line

#define ANN_LCD_Y LCD_HEADER_LINES

#define ANN_LCD_X  (ANN_BPL*8)
#define ANN2_LCD_X (ANN2_BPL*8)
#define ANN_LCD_DY  16

#define ANN_FLAG_CNT 11

#define ALPHA_ORIG          0
#define ALPHA_UPPER         1
#define ALPHA_LOWER         2
#define ALPHA_TABLE_COUNT   3
#define ALPHA_INACTIVE    0xf
uint8_t alpha_table = ALPHA_INACTIVE;
uint8_t last_alpha_table = 0;

#define TEST_ANNUNCIATORS 0

void repaint_annunciators() {
  int a;

  // No repaints in main menu
  if ( ST(STAT_MENU) ) return;

  if (is_graphics>1)
    return;


  // Clear the annunciator area
//  lcd_fillLines(ANN_LCD_Y, LCD_EMPTY_VALUE, ANN_LCD_DY);
  lcd_fill_rect(0, ANN_LCD_Y, 207, ANN_LCD_DY, 0);

/* Orig
  uint32_t m = 1;
  for(a=0; a<ANN_CNT; a++,m<<=1)
    if ( (ann_state & m) != 0 || TEST_ANNUNCIATORS)
      lcd_draw_img_part(ann00+ANN_BPL-ann_offs[a]-ann_dx[a],
        360-ann_lcd_x[a], ANN_LCD_Y,
        ANN_LCD_X, ANN_LCD_DY, 8*ann_dx[a]);

  // Draw Alpha annunciator
  if ( alpha_table != ALPHA_INACTIVE ) {
    lcd_draw_img_part(ann01+ANN_BPL-3*alpha_table-ann_dx[a],
          360-ann_lcd_x[a], ANN_LCD_Y,
          ANN_LCD_X, ANN_LCD_DY, 8*ann_dx[a]);
  }
*/

  uint32_t m = 1;
  for(a=0; a<ANN_CNT; a++,m<<=1) {
    if ( m == ANN_BATTERY ) continue;
    if ( (ann_state & m) != 0 || TEST_ANNUNCIATORS)
      lcd_draw_img_part(ann00+ANN2_BPL-ann_offs[a]-ann_dx[a],
        376-ann_lcd_x[a], ANN_LCD_Y,
        ANN2_LCD_X, ANN_LCD_DY, 8*ann_dx[a]);
  }

  // Draw Alpha annunciator
  if ( alpha_table != ALPHA_INACTIVE ) {
    lcd_draw_img_part(ann01+ANN_BPL-3*alpha_table-ann_dx[a],
          496-ann_lcd_x[a], ANN_LCD_Y,
          ANN_LCD_X, ANN_LCD_DY, 8*ann_dx[a]);
  }

  lcd_changed |= LCD_CHG_LCD;
}


void check_for_repaint(int what) {
  // No repaints in main menu
  if ( ST(STAT_MENU) ) return;

  // Drive the repaint directly from here
  if ( what>=0 || header_timeout() || (lcd_update_timeout() && !is_pgm_mode()) ) {
    if ( header_timeout() )
      disp_header();
    if ( (what>=0 || lcd_update_timeout()) && !is_pgm_mode() )
      disp_regs(what);
    lcd_refresh();
    lcd_changed = 0;
  }
}


/*
 ▄▄▄▄▄           ▀             ▄                 
 █   ▀█  ▄ ▄▄  ▄▄▄    ▄ ▄▄   ▄▄█▄▄   ▄▄▄    ▄ ▄▄ 
 █▄▄▄█▀  █▀  ▀   █    █▀  █    █    █▀  █   █▀  ▀
 █       █       █    █   █    █    █▀▀▀▀   █    
 █       █     ▄▄█▄▄  █   █    ▀▄▄  ▀█▄▄▀   █    

*/


void print_wait_for(int what) {
  while ( printer_busy_for(what) ) {
    check_for_repaint(LCD_UPD_DFLT);
  }
}

int is_gr_print = 0;

volatile uint8_t printer_was_graphics = 0;

uint get_printer_delay() {
  return core_printer_delay();
}


char* str_from_hp(char const* s, int length) {
  static char ss[80];
  //memcpy(ss, s, length);
  int a = hp2ascii(ss,s,length);
  ss[a] = 0;
  return ss;
}


void draw_hp42_lcd(const char *bits, int bytesperline, int x, int y, int width, int height) {

  #define HP_LCD_X 131
  #define HP_LCD_Y  16

   // Pixel size
  uint const px = is_graphics ? 3 : 2;
  uint const py = is_graphics ? 4 : 2;
  uint const x_shft = is_graphics ? 0 : 1;

  uint const lcd_y_base = LCD_HEADER_LINES + LCD_ANN_LINES + 2; // Bottom // Top: LCD_Y - 4;

  uint const adx = px*(HP_LCD_X+1)+1;
  uint const ady = py*HP_LCD_Y;
  uint const ax = LCD_X - adx - 8*x_shft;
  uint const ay = lcd_y_base;
  lcd_fill_rect(ax-2, ay-2, adx+4, ady+4,1);
  lcd_fill_rect(ax-1, ay-1, adx+2, ady+2,0);

  uint const px_mask = (1 << px)-1;
  #define HP_LCD_X_BYTES ((HP_LCD_X*px+7)/8)
  #define LCD_X_BYTES (LCD_X/8)
  uint lcd_y = lcd_y_base + py*y;
  uint8_t *c;
  uint i,j;
  for (int v = y; v < y + height; v++) {
    uint8_t *bi = (uint8_t*)(bits + (v+1) * bytesperline - 1 );
    c = lcd_line_addr(lcd_y) + x_shft; // lbuf+2
    uint n = HP_LCD_X_BYTES;
    uint outbits = 8;
    uint z=0xFFFFFF, m=px_mask; // This way z support px <= 3
    uint i_mask = 8;

    // Translate each byte
    for(;;) {
      int b = *bi--;
      for( i=i_mask; i; i>>=1) {
        if ( (b&i) != 0) z &= ~m;
        m <<= px;
        if ( !--outbits ) {
          for(j=0; j<px; j++) {
            c[0] = z & 0xFF; z >>= 8; c++; n--; if (n==0) goto lbuf_end;
          }
          outbits=8; z=0xFFFFFF; m=px_mask;
        }
      }
      i_mask = 0x80;
    }
lbuf_end:
    c = lcd_line_addr(lcd_y++)+x_shft; // First line already filled
    for(i=1; i<py; i++) {
      uint8_t * cc = lcd_line_addr(lcd_y++)+x_shft;
      memcpy(cc,c,HP_LCD_X_BYTES);
    }
  }
}


} // "C"



/*
▄▄▄▄▄▄▄  ▄▄▄▄  ▄▄▄▄    ▄▄▄▄         ▄    ▄          ▀                  ▀▀█                                  ▄               █ 
   █    ▄▀  ▀▄ █   ▀▄ ▄▀  ▀▄        █    █ ▄ ▄▄   ▄▄▄    ▄▄▄▄▄  ▄▄▄▄     █     ▄▄▄   ▄▄▄▄▄   ▄▄▄   ▄ ▄▄   ▄▄█▄▄   ▄▄▄    ▄▄▄█ 
   █    █    █ █    █ █    █   █    █    █ █▀  █    █    █ █ █  █▀ ▀█    █    █▀  █  █ █ █  █▀  █  █▀  █    █    █▀  █  █▀ ▀█ 
   █    █    █ █    █ █    █        █    █ █   █    █    █ █ █  █   █    █    █▀▀▀▀  █ █ █  █▀▀▀▀  █   █    █    █▀▀▀▀  █   █ 
   █     █▄▄█  █▄▄▄▀   █▄▄█    █    ▀▄▄▄▄▀ █   █  ▄▄█▄▄  █ █ █  ██▄█▀    ▀▄▄  ▀█▄▄▀  █ █ █  ▀█▄▄▀  █   █    ▀▄▄  ▀█▄▄▀  ▀█▄██ 
                                                                █                                                             */





// Position related callbacks
int shell_get_acceleration(double *x, double *y, double *z) {
  DBGSHELL("shell_get_acceleration\n");
  return 0;
}
int shell_get_location(double*, double*, double*, double*, double*) {
  DBGSHELL("shell_get_location\n");
  return 0;
}
int shell_get_heading(double*, double*, double*, double*, double*, double*) {
  DBGSHELL("shell_get_heading\n");
  return 0;
}
// -----


/*
  ▄▄▄▄  █             ▀▀█    ▀▀█             ▄▄   ▄▄▄▄▄  ▄▄▄▄▄ 
 █▀   ▀ █ ▄▄    ▄▄▄     █      █             ██   █   ▀█   █   
 ▀█▄▄▄  █▀  █  █▀  █    █      █            █  █  █▄▄▄█▀   █   
     ▀█ █   █  █▀▀▀▀    █      █            █▄▄█  █        █   
 ▀▄▄▄█▀ █   █  ▀█▄▄▀    ▀▄▄    ▀▄▄         █    █ █      ▄▄█▄▄ */



void shell_print(const char *text, int length,
  const char *bits, int bytesperline,
  int x, int y, int width, int height)
{
  const int sz = 24; // Printer has 24 chars per line
  char bb[sz+1];
  int len = (length > sz) ? sz : length;
  hp2print(bb,text,len);
  bb[len]=0;

  printer_set_delay(get_printer_delay());

#ifdef SHELL_DEBUG
  DBGSHELL("shell_print: %s[%i]  delay=%i\n", bb, length, get_printer_delay());
  DBGSHELL(".. xy=%ix%i wh=%ix%i bpl=%i\n", x,y, width,height, bytesperline);
  //dump_buffer(bits, bytesperline*height);
#endif

  if ( !strncmp(text,"<lcd>",5) ) {
    if ( width > MAX_82240_WIDTH )
      width = MAX_82240_WIDTH;

    lcd_refresh(); // Show annunciator
    
    // Display graphics
    if ( !printer_was_graphics ) {
      print_byte(4); // Print line and leave print head at right; use before each line of graphics to ensure that multiple lines of graphics line up vertically.
      printer_was_graphics = 1;
    }
    
    for(uint iy = 0; iy < (uint)height; iy+=8 ) {
      uint ix = iy*bytesperline;
      
      // Print single line (= 8 lines from bits)
      print_wait_for(PRINT_GRA_LN);
      print_byte(27);    // ESC
      print_byte(width); // number of columns
      
      for(uint xx=0; xx < (uint)width; xx++) {

        uint8_t msk = 1 << (xx & 7);
        uint k = ix + (xx>>3);

        uint8_t a = 0; // byte to send
        uint8_t amsk = 1;
        const uint lasty = (iy+8 < (uint)height) ? iy+8 : height; // Limit for y
        for (uint yy=0; yy < lasty; yy++,k+=bytesperline,amsk<<=1)
          if ( bits[k] & msk ) a |= amsk;
        print_byte(a);
      }
      // Whole line sent
      print_byte(4); // Flush the line
      printer_advance_buf(PRINT_GRA_LN);
    }
    return;
  }
  
  lcd_refresh(); // Show annunciator
  print_wait_for(PRINT_TXT_LN);
  
  if ( !is_gr_print && is_wide_print() ) {
    print_byte(27); // ESC
    print_byte(253);// Start printing expanded characters
  }

  for(int i = 0; i < length; i++) {
    char b = is_gr_print ? text[i] : bb[i];
    if ( !is_gr_print && (b == 0x1b) && (i+1<length) && text[i+1]<=166 ) {
      is_gr_print = text[i+1]+2;
      print_wait_for(PRINT_GRA_LN);
    }
    //if ( b == '\n' ) b = 10; // printer expects LF
    printf("[%02x:%c]\n",(int)b,isprint(b)?b:'_');
    print_byte(b);
    if (is_gr_print > 0) {
      is_gr_print--;
      if (!is_gr_print)
        printer_advance_buf(PRINT_TXT_LN);
    }
  }
  if ( !is_gr_print ) {
    print_byte(10); // Flush the line
    if ( is_wide_print() ) {
      print_byte(27); // ESC
      print_byte(252);// Return to normal-width characters
    }
    printer_advance_buf(PRINT_TXT_LN);
    printer_was_graphics = 0;
  }
}



void shell_malloc_fail(size_t size, const char * file, int line) {
  char * fn = (char*)file;
  int flen = strlen(file);

  lcd_writeNl(t20);  
  t20->y = lcd_for_dm42(DISP_ALLOC_FAIL);
  t20->y += 18;
  if ( flen > 40 ) fn += flen-40;

  lcd_puts(t20,"Unhandled memory allocation fail file:");
  lcd_puts(t20, fn);
  lcd_print(t20,"at line %i", line);
  lcd_print(t20,"size %i",size);
  t20->y = LCD_Y-lcd_lineHeight(t20);
  lcd_puts(t20,"Press EXIT to RESET the calculator...");
  lcd_refresh();
  set_reset_magic(ALLOC_FAIL_MAGIC);
  sys_reset();
}


int shell_low_battery() {
  bool lowbat = get_lowbat_state();
  DBGSHELL("shell_low_battery\n");
  
  if (lowbat == NOT_ANN(BATTERY)) {
    SETBY_ANN(lowbat,ANN_BATTERY);
    skin_repaint_annunciator(0, 0); // Always repaint all
  }
  return lowbat;
}

double shell_vbat() {
  double d = get_vbat();
  return d/1000;
}

int shell_dev_id() {
  return get_hw_id();
}


/* pre 2.0.7 */
#ifdef FREE42_PRE_207_IFC

double shell_random_seed() {
  DBGSHELL("shell_random_seed\n");
  dt_t dt;
  tm_t tm;
  rtc_read(&tm, &dt);
  int z = ((tm.hour*60+tm.min)*60+tm.sec)*100+tm.csec;
  return fmod(0.78237947239847*z,1.0);
}

#else

int64_t shell_random_seed() {
  DBGSHELL("shell_random_seed\n");
  dt_t dt;
  tm_t tm;
  rtc_read(&tm, &dt);
  int64_t z = ((tm.hour*60+tm.min)*60+tm.sec)*100+tm.csec;
  z = z*11574074 + julian_day(&dt);
  return z;
}


#endif


int shell_decimal_point() {
  return decimal_point ? 1 : 0;
}


void shell_beeper(int frequency, int duration) {
  DBGSHELL("shell_beeper fr=%i dur=%i\n", frequency, duration);
  // FIXME: Eat the time when BEEP is OFF?
  //if ( !ST(STAT_BEEP_MUTE) ) 
  {
    if ( duration > 1000 ) duration = 1000; // Well, we don't want to block for ages
    start_buzzer_freq(frequency*1000);
    for( ; duration > 0 ; duration -= 10) {
      sys_delay(duration > 10 ? 10 : duration);
      check_for_repaint(LCD_UPD_DFLT);
      // FIXME: Break on key press?
    }
  }
  stop_buzzer();
}


void shell_get_time_date(uint4 *tim, uint4 *date, int *weekday) {
#ifndef DBG_NOLCD
  DBGSHELL("shell_get_time_date\n");
#endif

  dt_t dt;
  tm_t tm;

  rtc_read(&tm, &dt);
  if(tim)
    *tim  = ((tm.hour*100 + tm.min)*100 + tm.sec)*100 + tm.csec; // 12345600;
  if(date)
    *date = dt.year*10000 + dt.month*100 + dt.day; // 20160103;
  if(weekday)
    *weekday = tm.dow==6 ? 0 : tm.dow+1; // Free42 0-Sun,1-Mon ... Our lib 0-Mon, 1-Tue
}




void shell_blitter(const char *bits, int bytesperline, int x, int y, int width, int height) {
#ifndef DBG_NOLCD  
  DBGSHELL("Shell blitter: bpl=%i  x=%i y=%i   w=%i h=%i  tick=%li  exttim=%i\n",
    bytesperline, x, y, width, height, sys_tick_count(), core_settings.enable_ext_time);
#endif

  lcd_changed |= LCD_CHG_LCD|LCD_CHG_REGS;

#if defined(THELL_DEBUG) && !defined(DBG_NOLCD)
  char bb[LCD_HP_CHARS+1];
  hp2font(bb,tlcd[0],LCD_HP_CHARS);
  DBGSHELL("LCD[0]:%s\n",bb);
  hp2font(bb,tlcd[1],LCD_HP_CHARS);
  DBGSHELL("LCD[1]:%s\n",bb);
#endif
  set_lcd_update_timeout();

}


void skin_repaint_annunciator(int which, bool state) {
#ifndef DBG_NOLCD
  DBGSHELL("skin_repaint_annunciator\n");
#endif

  // No more strings
  //lcd_print_at(5, annstr);

  repaint_annunciators();
}

void shell_annunciators(int updn, int shf, int prt, int run, int g, int rad) {
  DBGSHELL("shell_annunciators\n");
    if (updn != -1 && NOT_ANN(UPDOWN) == updn) {
      SETBY_ANN(updn,ANN_UPDOWN);
      //skin_repaint_annunciator(1, ann_updown);
    }
    if (shf != -1 && NOT_ANN(SHIFT) == shf) {
      SETBY_ANN(shf,ANN_SHIFT);
      //skin_repaint_annunciator(2, ann_shift);
    }
    if (prt != -1 && NOT_ANN(PRINT) == prt) {
      SETBY_ANN(prt,ANN_PRINT);
      //skin_repaint_annunciator(3, ann_print);
    }
    if (run != -1 && NOT_ANN(RUN) == run) {
      SETBY_ANN(run,ANN_RUN);
      //skin_repaint_annunciator(4, ann_run);
    }
    if (g != -1 && NOT_ANN(G) == g) {
      SETBY_ANN(g,ANN_G);
      //skin_repaint_annunciator(6, ann_g);
    }
    if (rad != -1 && NOT_ANN(RAD) == rad) {
      SETBY_ANN(rad,ANN_RAD);
      //skin_repaint_annunciator(7, ann_rad);
    }

#if 0
  sprintf(annstr, "%s  %s  %s  %s  %s%s",
    ANN(UPDOWN)?"^v":"  ",
    ANN(SHIFT)?"SHIFT":"     ",
    ANN(PRINT)?"PRINT":"     ",
    ANN(RUN)?"RUN":"   ",
    ANN(G)?"G":" ",
    ANN(RAD)?"RAD":"   "
  );
#endif
  skin_repaint_annunciator(0, 0); // Always repaint all

  //DBGSHELL("Shell annunciators %s\n", annstr);

}

/* Should be called periodically by core.
   Return 1 on available event */
int shell_wants_cpu() {
  int res = !key_empty(); // || header_timeout() || lcd_update_timeout();
  
  reset_auto_off();
  check_for_repaint(LCD_UPD_DFLT);

  if ( res )  {
    DBGSHELL("shell_wants_cpu: key=%i  hdr_tout=%i  lcd_tout=%i\n", !key_empty(), header_timeout(), lcd_update_timeout());
  }
  return res;
}


int shell_read(char *buf, int4 buflen) {
  DBGSHELL("shell_read: %08x : %i\n", (unsigned)buf, buflen);
  uint rd;
  pgm_res = f_read(ppgm_fp, buf, buflen, &rd);
  DBGSHELL(" ... read %i  err=%i\n",rd,pgm_res);
  return rd;
}


int shell_write(const char *buf, int4 buflen) {
  DBGSHELL("shell_read: %08x : %i\n", (unsigned)buf, buflen);
  uint wr;
  pgm_res = f_write(ppgm_fp, buf, buflen, &wr);
  DBGSHELL(" ... write %i  err=%i\n",wr,pgm_res);
  return wr;
}


uint4 shell_get_mem() {
  DBGSHELL("shell_get_mem: %i\n", sys_free_mem());
  return sys_free_mem(); // Returns free mem
}

uint4 shell_milliseconds() {
  //DBGSHELL("shell_milliseconds %i  aoff=%li\n", sys_current_ms(), auto_off_cnt);
  reset_auto_off();
  return sys_current_ms();
}

void shell_request_timeout3(int delay) {
  DBGSHELL("shell_request_timeout3 %i\n", delay);
  setTimeout3(delay);
}

void shell_delay(int duration) {
  DBGSHELL("shell_delay: %i\n", duration);
  sys_delay(duration);
  DBGSHELL("shell_delay end\n");
}

void shell_powerdown() {
  DBGSHELL("shell_powerdown\n");
  SET_ST(STAT_PGM_END);
}

//#define STATEFILE_READ_DBG
#ifdef  STATEFILE_READ_DBG
int readix = 0;
#endif


int4 shell_read_saved_state(void *buf, int4 buflen) {
  DBGSHELL_STATE_RW("shell_read_saved_state: %08x : %i  from %08lx\n", (unsigned)buf, buflen, (uint32_t)pgm_ptr);
#ifdef STATEFILE_READ_DBG
  readix += buflen;
  if ( readix > 0x1e90 ) {
    readix++;
  }
#endif  
  uint rd;
  pgm_res = f_read(ppgm_fp, buf, buflen, &rd);
  DBGSHELL(" ... read %i  err=%i\n",rd,pgm_res);
  return rd;
}

bool shell_write_saved_state(const void *buf, int4 buflen) {
  DBGSHELL_STATE_RW("shell_write_saved_state: %08x : %i  to %08lx\n", (unsigned)buf, buflen,(uint32_t)pgm_ptr);

  if ( ST(STAT_SOFT_OFF) ) return true; // Don't write on soft off

  uint wr;
  pgm_res = f_write(ppgm_fp, buf, buflen, &wr);
  DBGSHELL(" ... write %i  err=%i\n",wr,pgm_res);
  return pgm_res == FR_OK;
}


void shell_force_lcd_refresh(int what) {
  check_for_repaint(what); // Force repaint
}





/*
▄▄▄▄▄▄▄ █             ▀▀█    ▀▀█             ▄▄   ▄▄▄▄▄  ▄▄▄▄▄ 
   █    █ ▄▄    ▄▄▄     █      █             ██   █   ▀█   █   
   █    █▀  █  █▀  █    █      █            █  █  █▄▄▄█▀   █   
   █    █   █  █▀▀▀▀    █      █            █▄▄█  █        █   
   █    █   █  ▀█▄▄▀    ▀▄▄    ▀▄▄         █    █ █      ▄▄█▄▄ 
*/

extern "C" {

#define EDIT_PROMPT_LEN  15
#define EDIT_LINE_LEN    79

char edit_prompt[EDIT_PROMPT_LEN+1];
char edit_line[EDIT_LINE_LEN+1];
uint8_t is_edit;
uint8_t is_edit_x;
uint8_t is_graphics;
uint8_t is_show;

void clear_tlcd_row(int row) {
  assert_param(row>=0 && row<2);
  memset(tlcd[row],' ',TLCD_LINELEN);
  tlcd[row][TLCD_LINELEN] = 0;
  if(is_graphics>1) {
    // Was HiRes -> repaint header
    lcd_clear_buf();
  }

  if (!is_number_entry()) {
    is_show = 0;
    is_edit = is_edit_x = 0;
  }
}


/*
 ptrn  - pattern bytes by columns
 mask  - mask for current line
 width - width of the pattern (dx)
 dbl   - double each pixel
*/
int get_pattern_pixels(const char * ptrn, int width, int mask, int dbl) {
  //const char * p = ptrn+width-1;
  const char * p = ptrn;
  int val = 0;

  // Two loops with constant shifts and ors seems to be better for performance
  if ( dbl ) {
    while ( width-- > 0 ) {
      val <<= 2;
      if (*p++ & mask) val |= 3;
    }
  } else {
    while ( width-- > 0 ) {
      val <<= 1;
      if (*p++ & mask) val |= 1;
    }
  }
  return val;
}


} // C


void thell_draw_menu_key(int n, int highlight, const char *s, int length) {
  DBGTHELL("thell_draw_menu_key[%i:%c%s]\n", n, highlight?'#':' ', str_from_hp(s, length));

  // No repaints in main menu
  if ( ST(STAT_MENU) ) return;

  disp_was_menu_drawn = 1; // Note the menu was actually drawn

  // Free42 always starts menu drawing by first key, paint backgroung before first item
  if (n == 0)
    lcd_draw_menu_bg();

  // Re-encode menu text to normal string
  char t[MENU_KEY_LABEL_LEN+2];
  uint j = 0;
  for(int i=0; i<length; i++) {
    // Skip chars with 8th bit set - that way denotes free42 how to shortcut command names
    if( s[i] & 0x80 ) continue;
    // Copy and normalize
    t[j++] = s[i]>=' ' ? s[i] : s[i]|0x80;
    // Limit the length
    if (j==MENU_KEY_LABEL_LEN) break;
  }
  t[j]=0;

  lcd_draw_menu_key(n, t, highlight);
}


void thell_edit_number(const char * prompt, int prompt_len, const char * line, int line_len) {
  assert_param(prompt_len <= EDIT_PROMPT_LEN);
  assert_param(line_len <= EDIT_LINE_LEN);

  hp2font(edit_prompt, prompt, prompt_len);
  hp2font(edit_line, line, line_len);

  is_edit = 1;
  is_edit_x = prompt[0] == 'x' && prompt[1] == 0x80;
}


void thell_draw_char(int x, int y, char c) {
  //DBGTHELL("thell_draw_char %i %i : '%s'\n", x,y, str_from_hp(&c,1));
  assert_param(x>=0 && x<TLCD_LINELEN);
  assert_param(y>=0 && y<2);

  if(is_graphics>1) {
    // Was HiRes -> repaint header
    is_graphics = 0;
    calc_lcd_redraw();
  }
  is_graphics = 0;

  tlcd[y][x] = c;
}



// Mode: 0=or, 1=set, 2=and_not, 3=xor 
void thell_draw_pattern(int x, int y, const char * pattern, int pattern_width, int mode) {
  DBGTHELL("thell_draw_pattern[%i] %i x %i - %i\n", mode, x,y, pattern_width);
  int gm = graphics_mode();
  
  if (!gm) {
    // Original graphics mode
    is_graphics = 1;
    return;
  }

  if (!is_graphics) {
    // First call - clear LCD
    lcd_clear_buf();
  }

  const int blt_ops[]  = {BLT_OR, BLT_OR, BLT_ANDN, BLT_XOR};
  const int blt_sets[] = {BLT_NONE, BLT_SET, BLT_NONE, BLT_NONE};
  const int blt_op = blt_ops[mode];
  const int blt_set = blt_sets[mode];
  const int MAXX = gr_MAXX();
  //const int MAXY = gr_MAXY();

  // Normalize
  if (x<0) {
    pattern_width += x;
    pattern += -x;
    x=0;
  }

  if (x + pattern_width > MAXX) {
    pattern_width = MAXX - x;
  }

  is_graphics = gm;
  if ( gm == 2 ) {
    // 2x2 pixels
    for( ; pattern_width > 0; pattern_width-=12, pattern+=12, x+=12) {
      int const w = pattern_width<12 ? pattern_width : 12;
      int const ww = 2*w;
      int yy = 2*y;
      for(int m = 1; m<0x100; m<<=1,yy+=2) {
        int val = get_pattern_pixels(pattern, w, m, 1);
        bitblt24(2*x, ww, yy,   val, blt_op, blt_set);
        bitblt24(2*x, ww, yy+1, val, blt_op, blt_set);
      }
    }
  }

  if ( gm == 3 ) {
    // 1x1 pixels
    for( ; pattern_width > 0; pattern_width-=24, pattern+=24, x+=24) {
      int const w = pattern_width<24 ? pattern_width : 24;
      int yy = y;
      for(int m = 1; m<0x100; m<<=1,yy++) {
        int val = get_pattern_pixels(pattern, w, m, 0);
        bitblt24(x, w, yy, val, blt_op, blt_set);
      }
    }
  }

  lcd_changed |= LCD_CHG_REGS;
  set_lcd_update_timeout();
}


void thell_draw_pixel(int x, int y) {
  int gm = graphics_mode();
  DBGTHELL("thell_draw_pixel[%i] %i x %i\n",gm,x,y);

  if (!gm) {
    // Original graphics mode
    is_graphics = 1;
    return;
  }

  if (!is_graphics) {
    // First call - clear LCD
    lcd_clear_buf();
  }

  is_graphics = gm;
  if ( gm == 2 ) {
    // 2x2 pixels
    x<<=1; y<<=1;
    bitblt24(x, 2, y,   3, BLT_OR, BLT_NONE);
    bitblt24(x, 2, y+1, 3, BLT_OR, BLT_NONE);
  }

  if ( gm == 3 ) {
    // 1x1 pixels
    bitblt24(x, 1, y, 1, BLT_OR, BLT_NONE);
  }

  lcd_changed |= LCD_CHG_REGS;
  set_lcd_update_timeout();
}



void thell_start_show() {
  DBGTHELL("thell_start_show\n");
  is_show = 1;
}

void thell_clear_display() {
  clear_tlcd_row(0);
  clear_tlcd_row(1);
}



void thell_clear_row(int row) {
  clear_tlcd_row(row);
}



/*
 ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄
 ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄▄▄▄
*/







extern "C"  {


// -------------

#define CALC_FLAG_AUDIO_ON  26

void dm42_set_beep_mute(int val) {
  set_calc_flag(CALC_FLAG_AUDIO_ON, !val);
}

int dm42_is_beep_mute() {
  //return ST(STAT_BEEP_MUTE);
  return !get_calc_flag(CALC_FLAG_AUDIO_ON);
}



void set_disp_main_menu(int val) {
  SETBY_PS(val, PERM_MAIN_MENU);
}

int is_disp_main_menu() {
  return PS(PERM_MAIN_MENU);
}





#define MAX_DATE_SEPARATORS   3

char date_separators[] = "/-.";



char get_disp_date_sep() {
  int ix = is_disp(DISP_DATE_SEP);
  return date_separators[ix];
}


void toggle_disp(int what) {
  switch (what) {
    case DISP_STATFN: {
        int newval = !PS(DISP_STATFN);
        SETBY_PS(newval, DISP_STATFN);
      }
      break;
    case DISP_DOW: {
        int newval = !PS(DISP_DOW);
        SETBY_PS(newval, DISP_DOW);
      }
      break;
    case DISP_DATE: {
        int newval = !PS(DISP_DATE);
        SETBY_PS(newval, DISP_DATE);
      }
      break;
    case DISP_DATE_SEP: {
        int newval = is_disp(DISP_DATE_SEP)+1;
        if (newval >= MAX_DATE_SEPARATORS) newval=0;
        SETBY_PS(newval&1, DISP_DATE_SEP0);
        SETBY_PS(newval&2, DISP_DATE_SEP1);
      }
      break;
    case DISP_SHORTMON: {
        int newval = !PS(DISP_SHORTMON);
        SETBY_PS(newval, DISP_SHORTMON);
      }
      break;
    case DISP_TIME: {
        int newval = !PS(DISP_TIME);
        SETBY_PS(newval, DISP_TIME);
      }
      break;
    case DISP_VOLTAGE: {
        int newval = !PS(DISP_VOLTAGE);
        SETBY_PS(newval, DISP_VOLTAGE);
      }
      break;
  }
}

int is_disp(int what) {
  int val = 0;

  switch (what) {
    case DISP_STATFN:   val = PS(DISP_STATFN);   break;
    case DISP_DOW:      val = PS(DISP_DOW);      break;
    case DISP_DATE:     val = PS(DISP_DATE);     break;
    case DISP_SHORTMON: val = PS(DISP_SHORTMON); break;
    case DISP_TIME:     val = PS(DISP_TIME);     break;
    case DISP_VOLTAGE:  val = PS(DISP_VOLTAGE);  break;

    case DISP_DATE_SEP:
      val  = PS(DISP_DATE_SEP0) ? 1 : 0;
      val |= PS(DISP_DATE_SEP1) ? 2 : 0;
      break;
  }

  return val;
}


#define REG_OFFS_BITS  4
#define REG_OFFS_RANGE (1<<REG_OFFS_BITS)
#define REG_OFFS_MASK  (REG_OFFS_RANGE - 1)
#define REG_OFFS_HALF  (1<<(REG_OFFS_BITS-1))

#define REG_OFFS_MAX   ( REG_OFFS_HALF - 1)
#define REG_OFFS_MIN   (-REG_OFFS_HALF    )

#define MAX_REG_OFFS 5

int get_reg_font_offset(int line_reg_nr) {
  int offs = (reg_font_offset >> (line_reg_nr*REG_OFFS_BITS)) & REG_OFFS_MASK;
  return (offs < REG_OFFS_HALF) ? offs : offs-REG_OFFS_RANGE;
}

int inc_reg_font_offset(int line_reg_nr) {
  int offs = get_reg_font_offset(line_reg_nr)+1;
  if (offs > MAX_REG_OFFS) offs = -MAX_REG_OFFS;
  set_reg_font_offset(line_reg_nr, offs);
  return offs;
}


int set_reg_font_offset(int line_reg_nr, int offs) {
  uint32_t val = 0;
  int shift = line_reg_nr * REG_OFFS_BITS;
  uint32_t msk = REG_OFFS_MASK << shift;

  if ( offs >= 0 ) {
    if ( offs > REG_OFFS_MAX ) offs = REG_OFFS_MAX;
    val = offs;
  } else {
    if ( offs < REG_OFFS_MIN ) offs = REG_OFFS_MIN;
    val = offs & REG_OFFS_MASK;
  }

  reg_font_offset = (reg_font_offset & ~msk) | (val << shift);

  return offs;
}



void set_stack_layout(int layout) {
  stack_layout = layout;
}

int get_stack_layout() {
  return stack_layout;
}

char * get_stack_layout_str(char *s, int layout) {
  char * t = s;
  
  if ( layout & STACK_REG_L0) *t++ = 'L';

  *t++ = 'X'; // Always X

  if ( layout & STACK_REG_Y ) *t++ = 'Y';
  if ( layout & STACK_REG_Z ) *t++ = 'Z';
  if ( layout & STACK_REG_T ) *t++ = 'T';
  if ( layout & STACK_REG_L ) *t++ = 'L';
  if ( layout & STACK_REG_A ) *t++ = 'A';

  *t = 0;
  return s;
}




// Savestate functions


// 0 - OK
int savestat_init_read() {
  uint ver[2];
  uint rd;
  char * state_file_name = get_reset_state_file();
  pgm_res = FR_DISK_ERR;
  if ( !sys_disk_ok() || state_file_name == NULL ) return -1;
  pgm_res = f_open(ppgm_fp,  state_file_name , FA_READ);
  if ( pgm_res != FR_OK ) return -1;
  pgm_res = f_lseek(ppgm_fp, f_size(ppgm_fp)-sizeof(savestat_data_t)-sizeof(uint) );
  if ( pgm_res != FR_OK ) return -1;
  pgm_res = f_read(ppgm_fp,ver,sizeof(ver),&rd);
  if ( pgm_res != FR_OK || rd != sizeof(ver) || ver[1] != SAVESTAT_MAGIC) return -1;
  pgm_res = f_lseek(ppgm_fp, 0);
  if ( pgm_res != FR_OK ) return -1;
  return ver[0];
}

// 0 - OK
int savestat_init_write() {
  char * state_file_name = get_reset_state_file();
  pgm_res = FR_DISK_ERR;

  if ( !sys_disk_ok()  || state_file_name == NULL ) return 1;
  // Create /STATE directory if missing
  if ( check_create_dir(STATE_DIR) )
    return 1;
  pgm_res = f_open(ppgm_fp, state_file_name, FA_WRITE|FA_CREATE_ALWAYS);
  return pgm_res != FR_OK;
}


void copy_reset_state_filename(char *s, int maxlen) {
  char * f = get_reset_state_file();

  if ( f != NULL ) {
    int len = strlen(f);
    char * t = s + strlen(s);
    int lendir = strlen(STATE_DIR);

    // Skip /STATE directory in filename
    if ( len > lendir && f[lendir] == '/' ) {
      f += lendir+1;
      len = strlen(f);
    }

    // Trunc flename if too long
    if ( len >= maxlen ) {
      strncpy(t, f, maxlen-1);
      t[maxlen] = 0;
    } else {
      strcpy(t, f);
    }

    // Remove extension (not perfect, but reasonable enough :) )
    t = strrchr(s,'.');
    if (t) t[0] = 0;

  } else {
    strcat(s,"none");
  }
}



// Disp regs

int current_font_nr() {
  return is_pgm_mode() ? pgm_font_ix : reg_font_ix;
}

void disp_aligned_line(const char *prompt, const char *s) {
  char pr[EDIT_PROMPT_LEN+1];

  //lcd_putsAt(fReg,ln,""); // Fill the line
  lcd_prevLn(fReg);
  lcd_puts(fReg,""); // Fill the line
  fReg->lnfill = 0;
  if (is_REG_LINES) {
    int yln = fReg->y+lcd_baseHeight(fReg)+2;
    if ( yln > fReg->y_top_grd)
      lcd_fillLines(yln, 0xAA, 1);
  }
  
  int plen = strlen(prompt);
  if ( prompt[plen-1] == ':' ) {
    strcpy(pr,prompt);
    pr[plen-1] = 0;
    lcd_puts(fReg,pr);
    int x = fReg->x;
    int dy = current_font_nr() < 0 ? 0 : lcd_lineHeight(fReg)/12;
    fReg->fixed = 0;
    fReg->y -= dy;
    lcd_puts(fReg, ":");
    fReg->y += dy;

    fReg->fixed = 1;
    fReg->x = x+lcd_charWidth(fReg, ':');
  } else
    lcd_puts(fReg,prompt);
  
  if ( !is_REG_ALIGN_LEFT ) {
    // Align to the right
    int newx = LCD_X - strlen(s)*lcd_fontWidth(fReg) - fReg->xoffs;
    if ( newx > fReg->x ) fReg->x = newx;
  }
  lcd_puts(fReg,s);
  fReg->lnfill = 1;
}


void set_reg_font(int offset) {
  int fnr = current_font_nr();

  for(;offset > 0; offset--) fnr = lcd_nextFontNr(fnr);
  for(;offset < 0; offset++) fnr = lcd_prevFontNr(fnr);

  lcd_switchFont(fReg, fnr);
  if (fnr < 0 && !is_pgm_mode() && NR2T(fnr) < 5)
    fReg->ya++;
  if (fnr >= 0 && is_pgm_mode() )
    fReg->yb = -1;
}


void disp_reg(const char *prompt, reg_id_t reg_id, int line_reg_nr) {

  set_reg_font(get_reg_font_offset(line_reg_nr));

  const int linelen = (LCD_X + fReg->xoffs)/lcd_fontWidth(fReg); //(LCD_X - fReg->xoffs)/fReg->f->width;
  const int buflen = linelen; //64; //32;
  char buf[buflen];
  int len;

  len = reg2str(buf, buflen-strlen(prompt), reg_id);
  len = hp2font(buf, buf,len); buf[len] = 0;
  disp_aligned_line(prompt, buf);
}


void disp_regs(int what) {
  static int last_pgm_top_line = 0;
  char bb[LCD_HP_CHARS+2];
  int len;

#ifndef DBG_NOLCD
  printf("Disp regs\n");
#endif

  int is_running = ANN(RUN);
  int refresh_mask = is_running ? what : LCD_UPD_ALL;

  if (refresh_mask < 0)
    refresh_mask = get_reflcd_mask();

  printf("reflcd=%i  goose=%i  run=%i  refmsk=%i  ms=%i\n", get_reflcd_mask(), is_goose(), is_running, refresh_mask, (int)sys_current_ms());

  if (is_graphics>1) {
    clear_lcd_update_timeout();
    if (refresh_mask & LCD_UPD_MAIN)
      lcd_refresh();
    else
      set_lcd_update_timeout(); // No paint just repeat timeout
    return;
  }

  const int top_y_lines = LCD_HEADER_LINES + LCD_ANN_LINES;
  const int display_core_menu = (core_menu() && disp_was_menu_drawn);

  set_reg_font(0);

  // Protect header and annunciators
  fReg->y_top_grd = top_y_lines;

  // == Display DM42 top menu ==
  if ( is_disp_main_menu() && !display_core_menu ) {
    const char * menu[] = 
      // {"Menu-","Vol-","Vol+","RegFmt","Font-","Font+"};
      {"Help","Menu","","Volume","RegFmt","FonSz"};
    lcd_draw_menu_keys(menu);
  }


  // == Display program lines ==
  if ( is_pgm_mode() ) {
    int y_lines = LCD_Y - top_y_lines;
    int font_lines = y_lines/lcd_lineHeight(fReg);
    int last_line = 0;
    int const linelen = (LCD_X + fReg->xoffs)/lcd_fontWidth(fReg); //(LCD_X - fReg->xoffs)/fReg->f->width;

    pgm_info_t pi;
    get_pgm_info(&pi);

    // == Adjust main area when menu shown ==
    if ( is_disp_main_menu() || display_core_menu ) {
      y_lines -= LCD_MENU_LINES;
      font_lines = y_lines/lcd_lineHeight(fReg);
    }

    // From the top
    fReg->ln_offs = top_y_lines;

    // == Clear main area ==
    lcd_fillLines(top_y_lines, LCD_EMPTY_VALUE, y_lines);

    // Show displays current pgm line over two lcd lines
    if (is_show) font_lines--;

    if ( pi.pgm_line < last_pgm_top_line ) 
      last_pgm_top_line = pi.pgm_line;
    if ( last_pgm_top_line <= (pi.pgm_line - font_lines) )
      last_pgm_top_line = pi.pgm_line - font_lines + 1;

    //lcd_printAt(fReg, last_line++, "ln=%i  y=%i", pi.pgm_line, pi.y_row);
    #define PGM_LINE_LEN 100
    char pb[PGM_LINE_LEN];
    pgm_line_t pln;
    pgm_line_init(&pln, pb, linelen);

    int pgm_line = last_pgm_top_line;
    int pgm_line_end = last_pgm_top_line + font_lines;
    for( ; !pln.is_end && pgm_line < pgm_line_end; pgm_line++ ) {
      len = get_pgm_line(&pln, pgm_line);
      if ( pgm_line == pi.pgm_line ) {
        if (is_show) {
          // Display both lines
          hp2font(bb,tlcd[0],LCD_HP_CHARS);
          lcd_putsAt(fReg, last_line++, bb);
          pi.y_row=1;
        }
        hp2font(bb,tlcd[pi.y_row],LCD_HP_CHARS);
        lcd_putsAt(fReg, last_line++, bb);
      } else {
        hp2font(pb,pb,len);
        lcd_putsAt(fReg, last_line++, pb);
      }
    }

  } else { // if ( is_pgm_mode() ) 

    // == Display stack area ==

    //int y_lines = LCD_Y - top_y_lines;
    fReg->y = LCD_Y;

    //fReg->ln_offs = LCD_Y - font_lines*lcd_lineHeight(fReg);


    // == Adjust main area when menu shown ==
    if ( is_disp_main_menu() || display_core_menu ) {
      //fReg->ln_offs -= LCD_MENU_LINES;
      //y_lines -= LCD_MENU_LINES;
      fReg->y -= LCD_MENU_LINES;
    }

    if (refresh_mask & LCD_UPD_MAIN) {
      // == Clear main area ==
      lcd_fillLines(top_y_lines, LCD_EMPTY_VALUE, fReg->y - top_y_lines);

#if 0
      // == TEST ==
      set_reg_font_offset(LINE_REG_X,  3);
      set_reg_font_offset(LINE_REG_Y,  1);
      set_reg_font_offset(LINE_REG_Z, -1);
      set_reg_font_offset(LINE_REG_T, -3);
      set_reg_font_offset(LINE_REG_L, -3);
      set_reg_font_offset(LINE_REG_A, -3);
      // == TEST END ==
#endif

      if ( stack_layout & STACK_REG_L0)
        disp_reg("L:",REG_LX, LINE_REG_L);

      // X is always displayed as edit or reg
      if (is_edit_x) { // (is_edit) - INPUT edit in text area already
        // Print edit line if available
        set_reg_font(get_reg_font_offset(LINE_REG_X));
  
        int plen = strlen(edit_prompt), llen = strlen(edit_line);
        int const linelen = (LCD_X + fReg->xoffs)/lcd_fontWidth(fReg); //(LCD_X - fReg->xoffs)/fReg->f->width;

        char s[linelen+2];
        if ( plen+llen < linelen )
          sprintf(s, "%s_", edit_line);
        else {
          sprintf(s, "\x9a%s_", edit_line+llen-(linelen-plen-2));
        }
        disp_aligned_line(edit_prompt, s);
      }

      if (!is_edit_x)
        disp_reg("X:",REG_X, LINE_REG_X);


      // Display other registers according to the configuration

      if ( stack_layout & STACK_REG_Y)
        disp_reg("Y:",REG_Y, LINE_REG_Y);
      
      if ( stack_layout & STACK_REG_Z)
        disp_reg("Z:",REG_Z, LINE_REG_Z);
      
      if ( stack_layout & STACK_REG_T)
        disp_reg("T:",REG_T, LINE_REG_T);
      
      if ( stack_layout & STACK_REG_L)
        disp_reg("L:",REG_LX, LINE_REG_L);

      if ( stack_layout & STACK_REG_A)
        disp_reg("A:",REG_A, LINE_REG_A);
    }

  }


  // == Draw the top text lines ==
  if ( !is_pgm_mode() && (!is_goose() || (is_goose() && (refresh_mask & LCD_UPD_GOOSE))) ) {
    int wasy = 0; // Anything was drawn
    int last_line = 0;
    // Print from text buffer all what isn't especially handled
    fReg->ln_offs = top_y_lines; // From the top
    for(int j=0; j<2; j++) {
      // Ignore if second char is 0x80 -> register display
      if (tlcd[j][1] == 0x80) continue;

      // Ignore continuation lines while in edit mode
      if (!is_pgm_mode() && is_edit && tlcd[j][0] == 0x1a) continue;
      
      // Ignore if line is empty
      char * t = tlcd[j]; while(*t==' ') t++; if (*t == 0) continue;

      len = hp2font(bb,tlcd[j],LCD_HP_CHARS); bb[len] = 0;

      // FIXME: Clear some more background?
      lcd_putsAt(fReg, last_line++, bb);
      wasy = fReg->y;
    }

    // Draw black line under text area if at least one line was printed
    if ( wasy )
      lcd_fillLines(wasy+lcd_lineHeight(fReg), LCD_SET_VALUE, 2);
  }


  // == Draw flag icons ==
  if (refresh_mask & LCD_UPD_ANN) {
    int a;
    lcd_draw_img_part(ann03+ANN2_BPL-24,
      0, ANN_LCD_Y,
      ANN2_LCD_X, ANN_LCD_DY, 8*24);

    for(a=0; a<ANN_FLAG_CNT; a++) {
      if ( !get_calc_flag(a) && !TEST_ANNUNCIATORS) {
        // Empty particular space
        lcd_fill_rect(210+a*17, ANN_LCD_Y, 16, ANN_LCD_DY, 0);
      }
    }
  }

  //is_edit_x = is_edit = 0;

  clear_lcd_update_timeout();

  if ( is_graphics == 1 && (refresh_mask & LCD_UPD_MAIN)) // draw_old_lcd ||
    draw_hp42_lcd(core_display_buffer(), 17, 0,0, 131,16);
  else
    set_lcd_update_timeout(); // No paint just repeat timeout

  if ( !core_menu() )
    disp_was_menu_drawn = 0;

}



void empty_keydown() {
  int dummy1, dummy2, keep_running;
  do {
    printf("empty keydown:\n");
    keep_running = core_keydown(0, &dummy1, &dummy2);
    printf("end of empty keydown: keep_running=%i\n", keep_running);
  } while (keep_running);
}






/*
 ▄▄▄▄▄                                    
 █   ▀█ ▄   ▄  ▄ ▄▄   ▄ ▄▄    ▄▄▄    ▄ ▄▄ 
 █▄▄▄▄▀ █   █  █▀  █  █▀  █  █▀  █   █▀  ▀
 █   ▀▄ █   █  █   █  █   █  █▀▀▀▀   █    
 █    ▀ ▀▄▄▀█  █   █  █   █  ▀█▄▄▀   █    */


#define TIMER0 0
#define TIMER3 1

// Value in ms
void setTimeout0(int timeout_type, int value) {
  if ( is_pgm_mode() && !is_slow_autorepeat() && (sys_last_key() == KEY_UP || sys_last_key() == KEY_DOWN) )
    value = value/2; // Half in pgm mode
  printf("setTimeout0: %i : %i\n",timeout_type, value);

  timeout0_type = timeout_type;
  sys_timer_start(TIMER0, value);
}

void clearTimeout0() {
  sys_timer_disable(TIMER0);
}

void setTimeout3(int value) {
  sys_timer_start(TIMER3, value);
}

void clearTimeout3() {
  sys_timer_disable(TIMER3);
}



int header_timeout() {
  return last_header_min != rtc_read_min() && is_graphics < 2;
}

void clear_header_timeout() {
  last_header_min = rtc_read_min();
}

void force_header_timeout() {
  last_header_min = 77; // Force header timeout
}


int lcd_update_timeout() {
  return last_lcd_update_ms 
    ? (sys_current_ms() - last_lcd_update_ms > LCD_UPDATE_TIMEOUT)
    :  0;
}

void clear_lcd_update_timeout() {
  last_lcd_update_ms = 0;
}

void set_lcd_update_timeout() {
  if (last_lcd_update_ms == 0)
    last_lcd_update_ms = sys_current_ms();
}



void calc_lcd_redraw() {
  lcd_for_dm42(DISP_CALC);
  core_redisplay();
  skin_repaint_annunciator(0, 0); // Always repaint all
  lcd_changed |= LCD_CHG_FORCE|LCD_CHG_HEADER|LCD_CHG_LCD|LCD_CHG_REGS;
}



uint8_t last_header_clk24 = 0;
uint8_t last_header_dmy = 0;


void disp_header() {
  // Refresh header each second
  dt_t dt;
  tm_t tm;

  // No repaints in main menu
  if ( ST(STAT_MENU) ) return;

  if (is_graphics>1)
    return;

  rtc_wakeup_delay();
  rtc_read(&tm, &dt);
  int vdd = (int)read_power_voltage();

  // Update lowbat flag
  shell_low_battery();


  last_header_clk24 = is_clk24();
  last_header_dmy = is_dmy();

  //uint8_t lnfill; // Fill whole lines before writing line
  //uint8_t newln;  // New line after writing line

  lcd_writeClr(t24);
  t24->y = -2; // FIXME: calculate from font dimensions?
  t24->newln = 0;
  t24->lnfill = 0;

  // Black the header area
  lcd_fillLines(0, LCD_SET_VALUE, LCD_HEADER_LINES-2);

  //lcd_printR(t24,"%i:",lll);   // DEBUG! REMOVE!
/*
  char s[PRINT_DT_TM_SZ], t[PRINT_DT_TM_SZ];
  const char * dowstr = is_disp(DISP_DOW) ? get_wday_shortcut(tm.dow) : "";
  print_dmy_date(s,PRINT_DT_TM_SZ,&dt,dowstr,get_disp_date_sep());
  print_clk24_time(t,PRINT_DT_TM_SZ,&tm,0,0);

  lcd_printR(t24,"%s %s", s, t);
*/

  char s[MAX_LCD_LINE_LEN]; // LCD line // FIXME: the size constant?
  char t[MAX_LCD_LINE_LEN]; // state file name
  int ix, w, maxw = is_disp(DISP_VOLTAGE) ? 312 : 364;
  s[0] = 0; t[0] = 0;

  if ( is_disp(DISP_DOW) ) {
    strcat(s, get_wday_shortcut(tm.dow));
  }
  if ( is_disp(DISP_DATE) ) {
    if (s[0]) strcat(s," ");
    print_dmy_date(s+strlen(s),PRINT_DT_TM_SZ,&dt,NULL,is_disp(DISP_SHORTMON),get_disp_date_sep());
  }
  if ( is_disp(DISP_TIME) ) {
    if (s[0]) strcat(s," ");
    print_clk24_time(s+strlen(s),PRINT_DT_TM_SZ,&tm,0,0);
  }

  if ( is_disp(DISP_STATFN) ) {
    copy_reset_state_filename(t, MAX_LCD_LINE_LEN-2); // minus final space and terminator
    
    w = maxw - lcd_textWidth(t24, s) - 2*lcd_fontWidth(t24); // Two spaces

    ix = lcd_textToWidth(t24, t, w, NULL);
    if ( ix > 0 &&  t[ix] != 0 ) {
      // Not all string fits - shorten the name and place ... at the end
      t[ix] = 0;
      t[ix-1] = '\x9a'; // ...
    }
    lcd_putsR(t24,t);
    lcd_putsR(t24," ");
  }

  lcd_putsR(t24,s);

  // Print voltage
  if ( is_disp(DISP_VOLTAGE) ) {
    t24->x  = maxw;
    lcd_printR(t24, "%i.%02iV", vdd/1000, (vdd/10)%100);
  }

  int icon_ix = 0; // USB

  if ( !usb_powered() ) {
    icon_ix = (3090-vdd)/150;
    if (icon_ix < 1) icon_ix = 1;
    if (icon_ix > 7) icon_ix = 7;
    icon_ix <<= 2;
  }

  // Draw power annunciator
  lcd_draw_img_part(ann02+ANN2_BPL-icon_ix-4,
           0,         2, ANN2_LCD_X, ANN_LCD_DY, 30); //8*4);
//        32, ANN_LCD_Y, ANN_LCD_X, ANN_LCD_DY, 8*2);

  t24->newln = 1; 
  t24->lnfill = 1;

  lcd_changed |= LCD_CHG_HEADER;
  clear_header_timeout();
}









void clr_shift() {
  if ( ANN(SHIFT) ) {
    int key = 28; // Turn off shift
    printf("clr_shift: key press %i\n",key);
    core_keydown(key, NULL, NULL);
  }
}

void set_shift() {
  if ( !ANN(SHIFT) ) {
    int key = 28; // Turn off shift
    printf("set_shift: key press %i\n",key);
    core_keydown(key, NULL, NULL);
  }
}


void update_aplha_table() {
  // Check whether alpha mode was activated/deactivated and 
  // change state and annunciators accordingly
  if ( core_alpha_menu() ) {
    if ( alpha_table == ALPHA_INACTIVE ) {
      // Alpha mode activated
      alpha_table = last_alpha_table; //ALPHA_ORIG;
      repaint_annunciators();
    }
  } else {
    if ( alpha_table != ALPHA_INACTIVE ) {
      // Alpha mode deactivated
      last_alpha_table = alpha_table;
      alpha_table = ALPHA_INACTIVE;
      repaint_annunciators();
    }
  }
}



void program_main() {
  int enqueued, repeat, keep_running = 0;
  int resume_run = 0;
  int key = 0;
  int no_menu_key = 0;

  // Init
  clearTimeout0();
  clearTimeout3();

  run_menu_item_app = run_menu_item;
  menu_line_str_app = menu_line_str;

  after_fat_format = after_fat_format_dm42;

  is_flag_dmy = is_dmy;
  set_flag_dmy = set_dmy;
  is_flag_clk24 = is_clk24;
  set_flag_clk24 = set_clk24;
  is_beep_mute = dm42_is_beep_mute;
  set_beep_mute = dm42_set_beep_mute;

  key_to_alpha_table = alpha_upper_transl;

  repeat_timeout = 0;
  read_statefile = !ST(STAT_CLEAN_RESET);

  SET_ST(STAT_CLK_WKUP_ENABLE); // Enable wakeup each minute (for clock update)

  for(;;)
  {
    if (last_header_clk24 != is_clk24() || last_header_dmy != is_dmy() )
      force_header_timeout();

    if ( (!ST(STAT_PGM_END) && !keep_running && key_empty()) ||
         ( ST(STAT_PGM_END) && ST(STAT_SUSPENDED) ) ) 
    {
      // Go to sleep
      if ( core_initialized ) {
        printf("Idle: menu[%i,a:%i,h:%i,off:%i] aoff=%i lcd=%lx\n",core_menu(), core_alpha_menu(), core_hex_menu(),
          ST(STAT_OFF)!=0, sys_auto_off_cnt(), lcd_changed);
        
        // Pending LCD repaint
        if ( lcd_changed && !ST(STAT_OFF) ) {
          if ( ( /* !ANN(RUN) && */ (lcd_changed & LCD_CHG_REGS) ) || (LCD_CHG_FORCE & lcd_changed) )
            disp_regs(LCD_UPD_DFLT);
          if ( header_timeout() || (LCD_CHG_FORCE & lcd_changed) )
            disp_header();
          lcd_refresh();
          lcd_changed = 0;
        }
        CLR_ST(STAT_RUNNING);
        sys_sleep();
        printf("Runner wake-up\n");
      } else {
        printf("Idle: before init\n");
      }
    }

    if ( keep_running || !key_empty() ) {
      reset_auto_off();
    }

    // Force header repaint when USB/BAT power changes
    if ( ST(STAT_POWER_CHANGE) )
      force_header_timeout();

    // =======================
    // Externally forced LCD repaint
    if ( !ST(STAT_OFF) && (lcd_changed || header_timeout()) ) {
      if ( header_timeout() || (LCD_CHG_FORCE & lcd_changed) )
        disp_header();
      if ( LCD_CHG_FORCE & lcd_changed ) {
        disp_regs(LCD_UPD_DFLT);
        lcd_changed &= ~LCD_CHG_REGS;
      }
      lcd_refresh();
      lcd_changed &= ~(LCD_CHG_FORCE|LCD_CHG_HEADER);
    }
    if ( ST(STAT_CLK_WKUP_FLAG) ) {
      CLR_ST(STAT_CLK_WKUP_FLAG);
      continue;
    }
    if ( ST(STAT_POWER_CHANGE) ) {
      CLR_ST(STAT_POWER_CHANGE);
      continue;
    }

    // =======================
    // Off or statefile save
    if (ST(STAT_PGM_END) || ST(STAT_SUSPENDED) ) {
      if (!ST(STAT_SUSPENDED)) {
        pgm_res = FR_OK; // Clear pgm_res for plain power OFF

        LCD_clear();

        // Quit ... saving state and leave ...
        if ( !ST(STAT_SOFT_OFF) && sys_disk_ok() ) {
          lcd_for_dm42(DISP_SAVING_STATE);

          sys_disk_write_enable(1);
          
          mark_region(MARK_42_STAT_SAVE);
          savestat_init_write();
        }
        // Saves the state, but we want to get back so 
        // we don't want to call core_quit()
        core_enter_background();

        if ( !ST(STAT_SOFT_OFF) && sys_disk_ok() ) {
          savestat_data_t dat;
          uint wr;
          memset(&dat,0,sizeof(dat));
          dat.magic = SAVESTAT_MAGIC;

          // == Statefile save flags
          dat.flags = 0;
          //dat.flags |= ST(STAT_BEEP_MUTE) ? SAVESTAT_FLAG_BEEP_MUTE : 0; // Using calc flag now
          dat.flags |= ST(STAT_SLOW_AUTOREP) ? SAVESTAT_FLAG_SLOW_AUTOREP : 0;
          dat.flags |= PS(PERM_MAIN_MENU) ? SAVESTAT_PERM_MAIN_MENU : 0;

          // Top-bar header - DOW/DATE/TIME inverted as they are by default displayed
          dat.flags |=  PS(DISP_STATFN)   ? SAVESTAT_DISP_STATFN   : 0;
          dat.flags |= !PS(DISP_DOW)      ? SAVESTAT_DISP_DOW      : 0;
          dat.flags |= !PS(DISP_DATE)     ? SAVESTAT_DISP_DATE     : 0;
          dat.flags |=  PS(DISP_DATE_SEP0)? SAVESTAT_DISP_DATE_SEP0: 0;
          dat.flags |=  PS(DISP_DATE_SEP1)? SAVESTAT_DISP_DATE_SEP1: 0;
          dat.flags |=  PS(DISP_SHORTMON) ? SAVESTAT_DISP_SHORTMON : 0;
          dat.flags |= !PS(DISP_TIME)     ? SAVESTAT_DISP_TIME     : 0;
          dat.flags |=  PS(DISP_VOLTAGE)  ? SAVESTAT_FLAG_DISP_VOLTAGE : 0;
          // --

          int gm = graphics_mode();
          dat.flags |= (gm & 1) ? SAVESTAT_FLAG_GMODE0 : 0;
          dat.flags |= (gm & 2) ? SAVESTAT_FLAG_GMODE1 : 0;
          
          dat.flags |= is_REG_ALIGN_LEFT ? SAVESTAT_FLAG_REG_LEFT  : 0;
          dat.flags |= is_REG_LINES      ? SAVESTAT_FLAG_REG_LINES : 0;
          
          int reflcd = ~get_reflcd_mask() & 7;
          dat.flags |= (reflcd & 1) ? SAVESTAT_FLAG_REFLCD0 : 0;
          dat.flags |= (reflcd & 2) ? SAVESTAT_FLAG_REFLCD1 : 0;
          dat.flags |= (reflcd & 4) ? SAVESTAT_FLAG_REFLCD2 : 0;
          // ==

          dat.reg_font_ix = reg_font_ix;
          dat.pgm_font_ix = pgm_font_ix;

          dat.font_offsets[0] = (reg_font_offset>> 0) & 0xff;
          dat.font_offsets[1] = (reg_font_offset>> 8) & 0xff;
          dat.font_offsets[2] = (reg_font_offset>>16) & 0xff;

          strcpy(dat.platf_ver,PLATFORM_VERSION);
          dat.century = rtc_read_century();
          
          dat.printer_delay = core_printer_delay()/10;
          if ( dat.printer_delay == 0 ) dat.printer_delay = 1;

          dat.stack_layout = stack_layout;
          
          if (pgm_res == FR_OK)
            pgm_res = f_write(ppgm_fp, &dat, sizeof(savestat_data_t), &wr);
          FRESULT cls_res = f_close(ppgm_fp);

          no_region();

          sys_disk_check_valid(); // Unmount drive if disk is invalid
          if ( sys_disk_ok() && (pgm_res != FR_OK || cls_res != FR_OK) ) {
            // Fat storage OK but save state failed.
            // That means statefile isn't saved and everything
            // will be lost - display just write fail info and switch to
            // soft off mode.
            lcd_for_dm42(DISP_SAVE_FAILED);
            SET_ST(STAT_SOFT_OFF);
          }
        }
        else {
          lcd_set_buf_cleared(0); // Mark no buffer change region
          draw_power_off_image(is_graphics<=1);
          printf("--- run=%i lcdclr=%i\n",resume_run,lcd_get_buf_cleared());
        }

        if ( sys_is_disk_write_enable() )
          sys_disk_write_enable(0);

        if ( !ST(STAT_SOFT_OFF) && !sys_disk_ok() ) {
          // Disk fail means statefile isn't saved and everything
          // will be lost - display just disk fail info and switch to
          // soft off mode
          disp_disk_info("Save Calculator State");
          SET_ST(STAT_SOFT_OFF);
        }
        
        // -- Switch the calc state off --
        sys_critical_start();
        SET_ST(STAT_SUSPENDED);
        LCD_power_off(0);
        SET_ST(STAT_OFF);
        sys_critical_end();
        // --
      }
      keep_running = 0;
      key_pop_all();
      continue;
    }

    // Well, we are woken-up
    SET_ST(STAT_RUNNING);

    // =======================
    // Switch from OFF to ON state 
    if ( ST(STAT_OFF) ) {
      LCD_power_on();
      rtc_wakeup_delay();

      CLR_ST(STAT_OFF);
      resume_run = core_powercycle();
      printf("Power ON: run=%i lcdclr=%i\n",resume_run,lcd_get_buf_cleared());

/*
      if ( is_graphics > 1 )
        draw_gr_off_image();
      else
        calc_lcd_redraw();
*/
      if (lcd_get_buf_cleared())
        calc_lcd_redraw(); // Force complete repaint
      else
      {
        force_header_timeout();
        lcd_forced_refresh(); // Just redraw from LCD buffer
      }
    }
    
    // Clear suspended state, because now we are definitely reached the active state
    CLR_ST(STAT_SUSPENDED);

    // ========================
    // First initialization
    if ( !core_initialized ) {
      int ver = FREE42_VERSION;

      printf("DM42 start\n");
      //savestat_init(SAVEST_NEWEST); // Get one last saved
      if ( read_statefile ) {
        mark_region(MARK_42_STAT_LOAD);
        ver = savestat_init_read();
        if ( pgm_res ) // No state file -> just restart
          read_statefile = 0;
      }
      // Init read start
#ifdef STATEFILE_READ_DBG
      readix = 0;
#endif
      core_init(read_statefile, ver);
      //core_init(read_statefile, FREE42_VERSION);
      if ( read_statefile ) {
        savestat_data_t dat;
        uint rd;
        pgm_res = f_read(ppgm_fp, &dat, sizeof(savestat_data_t), &rd);
        if ( pgm_res == FR_OK && dat.magic == SAVESTAT_MAGIC ) {
          rtc_write_century(dat.century);
          core_set_printer_delay(dat.printer_delay ? (10*(uint)dat.printer_delay) : DFLT_82240_LINE_DUR); // Turn 0 to default

          // == Statefile load flags
          //SETBY_ST(dat.flags & SAVESTAT_FLAG_BEEP_MUTE, STAT_BEEP_MUTE);
          runner_key_tout_init(dat.flags & SAVESTAT_FLAG_SLOW_AUTOREP);
          SETBY_PS(dat.flags & SAVESTAT_PERM_MAIN_MENU, PERM_MAIN_MENU);

          // Top-Bar header DOW/DATE/TIME negative as those are displayed by default 
          SETBY_PS(  (dat.flags & SAVESTAT_DISP_STATFN), DISP_STATFN);
          SETBY_PS( !(dat.flags & SAVESTAT_DISP_DOW), DISP_DOW);
          SETBY_PS( !(dat.flags & SAVESTAT_DISP_DATE), DISP_DATE);
          SETBY_PS(  (dat.flags & SAVESTAT_DISP_DATE_SEP0), DISP_DATE_SEP0);
          SETBY_PS(  (dat.flags & SAVESTAT_DISP_DATE_SEP1), DISP_DATE_SEP1);
          SETBY_PS(  (dat.flags & SAVESTAT_DISP_SHORTMON), DISP_SHORTMON);
          SETBY_PS( !(dat.flags & SAVESTAT_DISP_TIME), DISP_TIME);
          SETBY_PS(   dat.flags & SAVESTAT_FLAG_DISP_VOLTAGE, DISP_VOLTAGE);

          int gm = 0;
          gm |= (dat.flags & SAVESTAT_FLAG_GMODE0) ? 1 : 0;
          gm |= (dat.flags & SAVESTAT_FLAG_GMODE1) ? 2 : 0;
          set_graphics_mode(gm);

          int reflcd = 0;
          reflcd |= (dat.flags & SAVESTAT_FLAG_REFLCD0) ? 1 : 0;
          reflcd |= (dat.flags & SAVESTAT_FLAG_REFLCD1) ? 2 : 0;
          reflcd |= (dat.flags & SAVESTAT_FLAG_REFLCD2) ? 4 : 0;
          set_reflcd_mask(~reflcd & 7);

          draw_reg_mode = 0;
          draw_reg_mode |= (dat.flags & SAVESTAT_FLAG_REG_LEFT)  ? REG_ALIGN_LEFT : 0;
          draw_reg_mode |= (dat.flags & SAVESTAT_FLAG_REG_LINES) ? REG_LINES      : 0;
          // ==
          
          reg_font_ix = dat.reg_font_ix;
          pgm_font_ix = dat.pgm_font_ix;

          reg_font_offset = ((uint32_t*)dat.font_offsets)[0] & 0xffffff;

          stack_layout = dat.stack_layout;
          if (stack_layout == 0) stack_layout = STACK_XYZTL; // Fall down to default for old savefiles
        }
        f_close(ppgm_fp);
      } else {
        // State defaults
        SET_PS(DISP_DOW);
        SET_PS(DISP_DATE);
        SET_PS(DISP_TIME);
      }
      resume_run = core_powercycle();
      no_region();
      read_statefile = 0;
      printf("DM42 initialized\n");
      core_initialized = true;

      // Init read end

      //if ( is_graphics > 1 )
      //  draw_gr_off_image();
      //else 
      {
        rtc_check_unset();
        calc_lcd_redraw();
      }

    }

    // ========================
    // Second start without core_init ... just ignore state file read
    if ( read_statefile ) {
      read_statefile = 0;
      core_repaint_display();
      skin_repaint_annunciator(0, 0); // Always repaint all
    }

    // ========================
    // == Timeout event handling
    if ( sys_timer_timeout(TIMER0) ) {
      repeat_timeout = 1;
    } else {
      if ( sys_timer_timeout(TIMER3) ) 
        repeat_timeout = 2;
    }
    if ( repeat_timeout ) {
      if ( repeat_timeout == 1 ) {
        printf("Timeout %i\n", timeout0_type);
        switch ( timeout0_type ) {
          case TIMEOUT_REPEAT: {
              int repeat = core_repeat();
              if ( repeat == 0 )
                clearTimeout0();
              else
                setTimeout0(TIMEOUT_REPEAT, repeat == 1 ? 200 : 100);
            }
            break;
          case TIMEOUT_CORE1:
            core_keytimeout1();
            setTimeout0(TIMEOUT_CORE2, 1750);
            break;
          case TIMEOUT_CORE2:
            core_keytimeout2();
            clearTimeout0();
            break;
        }
      } else {
        // timeout3
        printf("Timeout:3\n");
        keep_running = core_timeout3(1);
        clearTimeout3();
      }
      repeat_timeout = 0;
      continue;
    }

    // ========================
    // Resume Run or key read
    if ( resume_run ) {
      resume_run = 0;
      sys_delay(100); // Give some time to read key for automatic stop
      key = key_tail();
      if ( key == KEY_RUN ) {
        // Stop
        key = key_pop();
      } else {
        // Run again
        if(key==0) key_pop();
        clear_no_keystrokes_yet();
        key = -1; // Proceed
      }
    } else {
      // Fetch the key
      //  < 0 -> No key event
      //  > 0 -> Key pressed
      // == 0 -> Key released
      key = key_pop();
    }

#ifdef SWO_DEBUG
    if (key == KEY_F6) hwdbg_trace_init();
#endif


    /* =========================
       Main menu - Function keys

           F1 - Help
           F2 - Toggle main menu
           F3 - (not assigned)
           F4 - Increase volume 
     Shift-F4 - Decrease volume
           F5 - Stack alignment
     Shift-F5 - Vintage/sans font
           F6 - Increase font size
     Shift-F6 - Decrease font size
    */

    if ( !core_menu() && key>=KEY_F1 && key<=KEY_F6 ) {
      int consume_key = 1;
      int redraw = 1;

      switch (key) {
        case KEY_F1:
          // Start Help system
          //test_help_fonts();
          //help_demo();
          if ( !ANN(RUN) ) { // We don't want to display help during program run
            run_help();
            calc_lcd_redraw();
          } 
          break;

        case KEY_F2:
          // Toggle main menu visibility
          set_disp_main_menu(!is_disp_main_menu());
          break;
        
        case KEY_F3:
          break;

        case KEY_F4:
          ANN(SHIFT) ? beep_volume_down() : beep_volume_up();
          consume_key = 0; // We want the beep (by passing invalid key to core)
          redraw = 0; // No visual changes
          break;

        case KEY_F5:
          if ( ANN(SHIFT) ) {
            // Shift-F5 = Toggle to HP font
            if ( is_pgm_mode() )
              pgm_font_ix = lcd_toggleFontT(pgm_font_ix);
            else
              reg_font_ix = lcd_toggleFontT(reg_font_ix);
          } else {
            // F5 = Stack alignment
            draw_reg_mode++;
            if(draw_reg_mode > DRAW_REG_MODE_MAX) draw_reg_mode=0;
          }
          break;

        case KEY_F6:
          if ( ANN(SHIFT) ) {
            // Shift-F6 = decrease font size
            if ( is_pgm_mode() )
              pgm_font_ix = lcd_prevFontNr(pgm_font_ix);
            else
              reg_font_ix = lcd_prevFontNr(reg_font_ix);
          } else {
            // F6 = Increase font size
            if ( is_pgm_mode() )
              pgm_font_ix = lcd_nextFontNr(pgm_font_ix);
            else
              reg_font_ix = lcd_nextFontNr(reg_font_ix);
          }
          break;
      }

      // Consume shift
      if ( ANN(SHIFT) )
        clr_shift();

      if ( consume_key ) key = -1;

      if ( redraw && !ANN(RUN) ) {
        disp_regs(LCD_UPD_DFLT);
        lcd_refresh();
      }

    } // == End of main menu function keys handling


    if (key == KEY_SCREENSHOT) {
      start_buzzer_freq(4400); sys_delay(10); stop_buzzer();
      // Turn OFF SHIFT
      if ( ANN(SHIFT) )
        keep_running = core_keydown(KEY_SHIFT, &enqueued, &repeat);
      // Make screenshot
      if ( create_screenshot(1) == 2 ) {
        wait_for_key_press();
        calc_lcd_redraw();
      }
      start_buzzer_freq(8800); sys_delay(10); stop_buzzer();
      key = -1;
    }

    if ( key == KEY_DOUBLE_RELEASE )
      key = -1; // Ignore double key release

    // == Key translation

    update_aplha_table();

    if ( alpha_table != ALPHA_INACTIVE && ANN(SHIFT) ) {
      if ( key == KEY_UP ) {
        alpha_table = (alpha_table+1)%ALPHA_TABLE_COUNT;
        key = KEY_SHIFT;
      }
      if ( key == KEY_DOWN ) {
        alpha_table = (alpha_table+ALPHA_TABLE_COUNT-1)%ALPHA_TABLE_COUNT;
        key = KEY_SHIFT;
      }
    }


    if ( alpha_table != ALPHA_INACTIVE ) {
      if ( key == KEY_SH_UP ) {
        set_shift();
        key = KEY_UP;
      }
      if ( key == KEY_SH_DOWN ) {
        set_shift();
        key = KEY_DOWN;
      }
    }

    // Interpret the key as normal key (not F1-F6) if menu is displayed and key1-key6 pressed
    uint8_t is_menu_active = core_menu() || core_hex_menu() || core_alpha_menu();
    no_menu_key = is_menu_active && key > 0 && key < 7;

    if ( (key > 0 && key <= MAX_KEY_NR) && alpha_table != ALPHA_INACTIVE ) {
      // Translate alpha keys
      const char * transl = ANN(SHIFT) ? alpha_shift_tables[alpha_table] : alpha_tables[alpha_table];
      char c = ALPHA_NO_TRANSL;
      if ( transl )
        c = transl[key];

      //if ( ANN(SHIFT) && (c >= '0' && c <= '9' ) ) {
      //  key = nr_to_key(c-'0');
      //} else {
        if ( c != ALPHA_NO_TRANSL ) {
          key = 0x400 | c;
        }
      //}
      //clr_shift();
    } else
      // Translate top row into function keys if function menu or alpha menu is activated
      if ( (key > MAX_KEY_NR && key <= MAX_FNKEY_NR) && is_menu_active ) {
        key -= MAX_KEY_NR; // Translate FN keys to codes 1-6
      }

    // ==================================
    // == Setup key - Setup MENU
    // ==================================
    if ( key == KEY_0 && ANN(SHIFT)) { 
      key = KEY_SHIFT; // Key remains SHIFT to turn the shift off or rewrite for special actions
      
      // We don't want to display menu during program run
      // as well as during hires graphics modes
      if ( !ANN(RUN) && is_graphics <= 1) {
        SET_ST(STAT_MENU);
        int ret = handle_menu(&MID_MENU, MENU_RESET, 0);
        CLR_ST(STAT_MENU);
        if ( ret == MRET_SAVESTATE ) { // FIXME: Really?
          CLR_ST(STAT_SOFT_OFF); // Hard off
          key = KEY_EXIT;
        }
        calc_lcd_redraw();
        wait_for_key_release(-1);
      } else {
        // Just beep :)
        shell_beeper(1835, 125);
      }
    }

    // == Key press
    if ( key > 0 ) {
      if ( sys_timer_active(TIMER3) && key != KEY_SHIFT ) {
        clearTimeout3();
        core_timeout3(0);
      }

      // We don't want to process other key when exiting
      if (ST(STAT_PGM_END)) continue;

      // Press key
      printf("key press %i nomenu=%i\n",key,no_menu_key);
      mark_region(MARK_42_KEYP);
      keep_running = core_keydown_ex(key, &enqueued, &repeat, no_menu_key);
      no_region();
      printf("end of keydown: keep_running=%i  enqueued=%i  repeat=%i\n", keep_running, enqueued, repeat);

      if ( keep_running ) {
        // keep running
      } else {
        // Set timeouts
        if (repeat != 0) {
          if ( is_pgm_mode() && !is_slow_autorepeat()  && (sys_last_key() == KEY_UP || sys_last_key() == KEY_DOWN) )
            setTimeout0(TIMEOUT_REPEAT, repeat == 1 ?  400 : 200); // First repeat is longer
          else
            setTimeout0(TIMEOUT_REPEAT, repeat == 1 ? 1000 : 500); // First repeat is longer
        }
        else if (!enqueued)
          setTimeout0(TIMEOUT_CORE1, 250);
      }
    }

    // == Key up
    if ( key == 0 ) {
      clearTimeout0();
      printf("keyup\n");
      mark_region(MARK_42_KEYR);
      keep_running = core_keyup();
      no_region();
      printf("end of keyup: keep_running=%i\n", keep_running);
    }

    /* Empty key 
       - we were woken-up and no key waits for handling
       - or we reiterate on keep_running
       - !mode_pause - Important here! core_keydown cancels running flag otherwise */
    if ( key < 0 && !is_mode_pause() ) {
      printf("RUN: empty key press\n");
      //keep_running = core_keydown(0, &dummy1, &dummy2);
      mark_region(MARK_42_KEY0);
      keep_running = core_keydown(0, &enqueued, &repeat);
      no_region();
      printf("RUN: end of keydown: keep_running=%i\n", keep_running);
    }

    update_aplha_table();

  }  // Main loop
}


} // extern "C"
