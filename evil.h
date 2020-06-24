#ifndef CNOEVIL
#define CNOEVIL "3.0.0"

// Programmer's Notes
//
// Every part of CNOEvil must be able to do one of:
// * Be excluded by a preprocessor definition (e.g. #define EVIL_NO_MODULE)
// * Be included by a preprocessor definition (e.g. #define EVIL_MODULE)
//
// We reserve EVIL_ for module names.
// Long module names are discouraged.
//
// We try and extend C. Now and then we might have to break it, but that is
// truly exceptional, and must be thoroughly documented.
//
// CNoEvil is intended to be intuitive to write,
// and clear to read.
//
// C11 features are fine. We assume a modern compiler.
//
// Whitespace sensitivity is abhorrent, and should never be introduced.
//
// Your code should make sense once it's expanded. (Human readable. Not only machine readable.)
//
// Libraries that might be expected to instantly be available in a higher-level language can be
// automatically included. All others must be specified.
//
// CNoEvil is a 1-file header library.
// That doesn't mean we're bound to macros-only, but it's probably a good
// idea to limit the number of functions.
//
// Yes, we have lots of header files. They all get compiled into a single one.
//
// All macros and functions _must_ have a matching counterpart in:
// * evil_help routines
// * examples/ folder
//
// CNoEvil aims to be a language atop C, aimed at making the programmer's life
// *simpler*. Simpler =/= easier. The programmer can be expected to know C.
//

/*
Copyright 2020 James Milne,

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. The licensee acknowledges that this software is utterly insane in it's nature, and not fit for any purpose.

2. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

3. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

4. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

***THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.***
*/

#define EVIL_HASH_VER "c0e70cd41f053e"


#ifdef EVIL_ASSERT

	#ifndef NDEBUG

	#include <stdio.h>
	#include <signal.h>

	#define Assert(_expression) if((_expression) != 1) { fprintf(stderr, "Assertion `%s` failed\n%s @ line %d\nin `%s`\n", #_expression, __FILE__, __LINE__, __func__); raise(SIGABRT); }

	#define AssertMsg(_expression, _reason) if((_expression) != 1) { fprintf(stderr, "Assertion `%s` failed: %s\n%s @ line %d\nin `%s`\n", #_expression, #_reason, __FILE__, __LINE__, __func__); raise(SIGABRT); }

	#else

	#define Assert(ignore)((void) 0)
	#define AssertMsg(ignore, ignore_again)((void) 0)

	#endif

#endif
#ifdef EVIL_BIT

  #define BIT_AND(a, b) (a & b)
  #define BIT_OR(a, b) (a | b)
  #define BIT_XOR(a, b) (a ^ b)
  #define BIT_NOT(a) (~a)
  #define BIT_RSHIFT(a, b) (a >> b)
  #define BIT_LSHIFT(a, b) (a << b)
  

#endif
#ifndef EVIL_NO_BOOL
  // Included by default
  #include <stdbool.h>
#endif

#ifdef EVIL_CLI
  //Taken from my library, colors.h (https://github.com/shakna-israel/colors)
  //Also taken from my library, damned (curses for shell) (https://github.com/shakna-israel/damned)
  #include <stdio.h>

  #ifndef EVIL_ASSERT
    #warning "EVIL_CLI depends on EVIL_ASSERT. Without it, cli_fg_256 and cli_bg_256 will be unavailable."
  #endif

  #define cli_reset() printf("%s", "\x1b[0m"); fflush(stdout)

  #ifdef EVIL_ASSERT
    #define cli_fg_256(num) Assert(num < 256); printf("%s%d%s", "\x1b[38;5;", num, "m")
    #define cli_bg_256(num) Assert(num < 256); printf("%s%d%s", "\x1b[48;5;", val, "m")
  #endif

  // Also known as truecolor.
  #define cli_fg_rgb(a, b, c) printf("\x1b[38;2;%d;%d;%d", a, b, c)
  #define cli_bg_rgb(a, b, c) printf("\x1b[48;2;%d;%d;%d", a, b, c)

  #define cli_fg_black() printf("%s", "\x1b[30m")
  #define cli_fg_red() printf("%s", "\x1b[31m")
  #define cli_fg_green() printf("%s", "\x1b[32m")
  #define cli_fg_yellow() printf("%s", "\x1b[33m")
  #define cli_fg_blue() printf("%s", "\x1b[34m")
  #define cli_fg_magenta() printf("%s", "\x1b[35m")
  #define cli_fg_cyan() printf("%s", "\x1b[36m")
  #define cli_fg_white() printf("%s", "\x1b[37m")

  #define cli_fg_bright_black() printf("%s", "\x1b[30;1m")
  #define cli_fg_bright_red() printf("%s", "\x1b[31;1m")
  #define cli_fg_bright_green() printf("%s", "\x1b[32;1m")
  #define cli_fg_bright_yellow() printf("%s", "\x1b[33;1m")
  #define cli_fg_bright_blue() printf("%s", "\x1b[34;1m")
  #define cli_fg_bright_magenta() printf("%s", "\x1b[35;1m")
  #define cli_fg_bright_cyan() printf("%s", "\x1b[36;1m")
  #define cli_fg_bright_white() printf("%s", "\x1b[37;1m")

  #define cli_bg_black() printf("%s", "\x1b[40m")
  #define cli_bg_red() printf("%s", "\x1b[41m")
  #define cli_bg_green() printf("%s", "\x1b[42m")
  #define cli_bg_yellow() printf("%s", "\x1b[43m")
  #define cli_bg_blue() printf("%s", "\x1b[44m")
  #define cli_bg_magenta() printf("%s", "\x1b[45m")
  #define cli_bg_cyan() printf("%s", "\x1b[46m")
  #define cli_bg_white() printf("%s", "\x1b[47m")

  #define cli_bg_bright_black() printf("%s", "\x1b[40;1m")
  #define cli_bg_bright_red() printf("%s", "\x1b[41;1m")
  #define cli_bg_bright_green() printf("%s", "\x1b[42;1m")
  #define cli_bg_bright_yellow() printf("%s", "\x1b[43;1m")
  #define cli_bg_bright_blue() printf("%s", "\x1b[44;1m")
  #define cli_bg_bright_magenta() printf("%s", "\x1b[45;1m")
  #define cli_bg_bright_cyan() printf("%s", "\x1b[46;1m")
  #define cli_bg_bright_white() printf("%s", "\x1b[47;1m")

  #define cli_cursor_up(num) printf("\x1b%dA", num)
  #define cli_cursor_down(num) printf("\x1b%dB", num)
  #define cli_cursor_left(num) printf("\x1b%dC", num)
  #define cli_cursor_right(num) printf("\x1b%dD", num)
  #define cli_cursor_save() printf("\x1bs")
  #define cli_cursor_restore() printf("\x1bu")

  #define cli_screen_clear() printf("%s", "\x1b[2J\x1b[1;1H"); fflush(stdout)
  #define cli_screen_clear_before() printf("%s", "\x1b[1J"); fflush(stdout)
  #define cli_screen_clear_after() printf("%s", "\x1b[0J"); fflush(stdout)

  #define cli_line_clear() printf("%s", "\x1b[2K"); fflush(stdout)
  #define cli_line_clear_before() printf("%s", "\x1b[1K"); fflush(stdout)
  #define cli_line_clear_after() printf("%s", "\x1b[0K"); fflush(stdout)

  #define cli_effect_bold() printf("%s", "\x1b[1m")
  #define cli_effect_underline() printf("%s", "\x1b[4m")
  #define cli_effect_reverse() printf("%s", "\x1b[7m")
  #define cli_effect_blink() printf("%s", "\x1b[5m")
  #define cli_effect_invisible() printf("%s", "\x1b[8m")
  #define cli_effect_reset() printf("%s", "\x1b[0m")
#endif

#ifndef EVIL_NO_COMMENT
  // Included by default
  #define comment(...) /* __VA_ARGS__ */
#endif

#ifdef EVIL_COROUTINE
  // This lovely hack makes use of switch statements,
  // And the __LINE__ C macro
  // It tracks the current state, and switches case.
  // But... I imagine awful things may happen with an extra semi-colon.
  // Which would be hard to debug.
  #if defined(EVIL_LAMBDA) && !defined(EVIL_NO_WARN)
    // And bad things happen with expression statements.
    #warning "Lambda's don't play well with Coroutines."
" Avoid using them in the body of a coroutine."
  #endif
  #ifndef EVIL_NO_WARN
    #warning "Coroutine's don't support nesting. It may work sometimes,"
" other times it may explode."
  #endif

  // Original macro hack by Robert Elder (c) 2016. Used against
  // their advice, but with their permission.
  #define coroutine() static int state=0; switch(state) { case 0:
  #define co_return(x) { state=__LINE__; return x; case __LINE__:; }
  #define co_end() }
#endif


#ifdef EVIL_ENCODE

  #include <stdlib.h>
  #include <string.h>

  #ifndef EVIL_NO_WARN
    #warning "ENCODE module is still under construction."
  #endif

  // Declerations.
  char* base16_encode(char* input, size_t length); // NULL on failure.
  char* base16_decode(char* input, size_t length); // NULL on failure.

  char* morse_encode(char* input, size_t length); // NULL on failure.
  char* morse_decode(char* input, size_t length); // NULL on failure.

  // TODO: base64

  // TODO: base32

  // base16
  char* base16_encode(char* input, size_t length)
  {
    static const char* const lut = "0123456789ABCDEF";

    size_t str_pos = 0;
    char* output = malloc(sizeof(char) * (length * 2));
    if(!output) {
      return NULL;
    }

    for(size_t i = 0; i < length; i++) {
      const unsigned char c = input[i];
      output[str_pos] = lut[c >> 4];
      str_pos++;
      output[str_pos] = lut[c & 15];
      str_pos++;
    }
    return output;
  }

  char* base16_decode(char* input, size_t length)
  {
    static const char* const lut = "0123456789ABCDEF";

    // Length must be even
    if(length % 2 != 0) {
      return NULL;
    }

    char* output = malloc(sizeof(char) * (length / 2));

    for(size_t i = 0, j = 0; i < (length/2); i++, j++) {
      output[i] = (input[j] & '@' ? input[j] + 9 : input[j]) << 4, j++;
      output[i] |= (input[j] & '@' ? input[j] + 9 : input[j]) & 0xF;
    }
    output[length/2] = 0;
    return output;
  }

  // morse
  char* morse_encode(char* input, size_t inlength)
  {
    // Get the output length. Morse isn't fixed width.
    size_t length = 0;
    for(size_t i = 0; i < inlength; i++) {
      switch(input[i]) {
        case('A'):
        case('a'):
          // .- [space]
          length += 3;
          break;
        case('B'):
        case('b'):
          // -... [space]
          length += 5;
          break;
        case('C'):
        case('c'):
          // -.-. [space]
          length += 5;
          break;
        case('D'):
        case('d'):
          // -.. [space]
          length += 4;
          break;
        case('E'):
        case('e'):
          // . [space]
          length += 2;
          break;
        case('F'):
        case('f'):
          // ..-. [space]
          length += 5;
          break;
        case('G'):
        case('g'):
          // --. [space]
          length += 4;
          break;
        case('H'):
        case('h'):
          // .... [space]
          length += 5;
          break;
        case('I'):
        case('i'):
          // .. [space]
          length += 3;
          break;
        case('J'):
        case('j'):
          // .--- [space]
          length += 5;
          break;
        case('K'):
        case('k'):
          // -.- [space]
          length += 4;
          break;
        case('L'):
        case('l'):
          // .--- [space]
          length += 5;
          break;
        case('M'):
        case('m'):
          // -- [space]
          length += 3;
          break;
        case('N'):
        case('n'):
          // -. [space]
          length += 3;
          break;
        case('O'):
        case('o'):
          // --- [space]
          length += 4;
          break;
        case('P'):
        case('p'):
          // .--. [space]
          length += 5;
          break;
        case('Q'):
        case('q'):
          // --.- [space]
          length += 5;
          break;
        case('R'):
        case('r'):
          // .-. [space]
          length += 4;
          break;
        case('S'):
        case('s'):
          // ... [space]
          length += 4;
          break;
        case('T'):
        case('t'):
          // - [space]
          length += 2;
          break;
        case('U'):
        case('u'):
          // ..- [space]
          length += 4;
          break;
        case('V'):
        case('v'):
          // ...- [space]
          length += 5;
          break;
        case('W'):
        case('w'):
          // .-- [space]
          length += 4;
          break;
        case('X'):
        case('x'):
          // -..- [space]
          length += 5;
          break;
        case('Y'):
        case('y'):
          // -.-- [space]
          length += 5;
          break;
        case('Z'):
        case('z'):
          // --.. [space]
          length += 5;
          break;
        case('0'):
          // ----- [space]
          length += 6;
          break;
        case('1'):
          // .---- [space]
          length += 6;
          break;
        case('2'):
          // ..--- [space]
          length += 6;
          break;
        case('3'):
          // ...-- [space]
          length += 6;
          break;
        case('4'):
          // ....- [space]
          length += 6;
          break;
        case('5'):
          // ..... [space]
          length += 6;
          break;
        case('6'):
          // -.... [space]
          length += 6;
          break;
        case('7'):
          // --... [space]
          length += 6;
          break;
        case('8'):
          // ---.. [space]
          length += 6;
          break;
        case('9'):
          // ----. [space]
          length += 6;
          break;
        default:
          // Ignore unknown characters
          break;
      }
    }

    // Allocate
    char* s = malloc(sizeof(char) * (length + 1));

    if(!s) {
      return NULL;
    }

    // Iterate
    size_t out_pos = 0;
    for(size_t i = 0; i < inlength; i++) {
      switch(input[i]) {
        case('A'):
        case('a'):
          // .- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = ' ';
          out_pos += 3;
          break;
        case('B'):
        case('b'):
          // -... [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('C'):
        case('c'):
          // -.-. [space]
          s[out_pos] = '-';
          s[out_pos] = '.';
          s[out_pos] = '-';
          s[out_pos] = '.';
          s[out_pos] = ' ';
          out_pos += 5;
          break;
        case('D'):
        case('d'):
          // -.. [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('E'):
        case('e'):
          // . [space]
          s[out_pos] = '.';
          s[out_pos+1] = ' ';
          out_pos += 2;
          break;
        case('F'):
        case('f'):
          // ..-. [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '-';
          s[out_pos+3] = '.';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('G'):
        case('g'):
          // --. [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '.';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('H'):
        case('h'):
          // .... [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('I'):
        case('i'):
          // .. [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = ' ';
          out_pos += 3;
          break;
        case('J'):
        case('j'):
          // .--- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = '-';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('K'):
        case('k'):
          // -.- [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = '-';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('L'):
        case('l'):
          // .-.. [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('M'):
        case('m'):
          // -- [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = ' ';
          out_pos += 3;
          break;
        case('N'):
        case('n'):
          // -. [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = ' ';
          out_pos += 3;
          break;
        case('O'):
        case('o'):
          // --- [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('P'):
        case('p'):
          // .--. [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = '.';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('Q'):
        case('q'):
          // --.- [space]
          s[out_pos] = '-';
          s[out_pos] = '-';
          s[out_pos] = '.';
          s[out_pos] = '-';
          s[out_pos] = ' ';
          length += 4;
          break;
        case('R'):
        case('r'):
          // .-. [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = '.';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('S'):
        case('s'):
          // ... [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('T'):
        case('t'):
          // - [space]
          s[out_pos] = '-';
          s[out_pos+1] = ' ';
          out_pos += 2;
          break;
        case('U'):
        case('u'):
          // ..- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '-';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('V'):
        case('v'):
          // ...- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '-';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('W'):
        case('w'):
          // .-- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = ' ';
          out_pos += 4;
          break;
        case('X'):
        case('x'):
          // -..- [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '-';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('Y'):
        case('y'):
          // -.-- [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = '-';
          s[out_pos+3] = '-';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('Z'):
        case('z'):
          // --.. [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = ' ';
          out_pos += 5;
          break;
        case('0'):
          // ----- [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = '-';
          s[out_pos+4] = '-';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('1'):
          // .---- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = '-';
          s[out_pos+4] = '-';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('2'):
          // ..--- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '-';
          s[out_pos+3] = '-';
          s[out_pos+4] = '-';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('3'):
          // ...-- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '-';
          s[out_pos+4] = '-';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('4'):
          // ....- [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = '-';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('5'):
          // ..... [space]
          s[out_pos] = '.';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = '.';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('6'):
          // -.... [space]
          s[out_pos] = '-';
          s[out_pos+1] = '.';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = '.';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('7'):
          // --... [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '.';
          s[out_pos+3] = '.';
          s[out_pos+4] = '.';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('8'):
          // ---.. [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = '.';
          s[out_pos+4] = '.';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        case('9'):
          // ----. [space]
          s[out_pos] = '-';
          s[out_pos+1] = '-';
          s[out_pos+2] = '-';
          s[out_pos+3] = '-';
          s[out_pos+4] = '.';
          s[out_pos+5] = ' ';
          out_pos += 6;
          break;
        default:
          // Ignore unknown characters
          break;
      }
    }
    s[out_pos] = 0;

    return s;
  }

  char* morse_decode(char* input, size_t inlength)
  {

    // Check the input makes sense.
    size_t length = 0;
    for(size_t i = 0; i < inlength; i++) {
      switch(input[i]) {
        case('.'):
        case('-'):
          break;
        case(' '):
          length++;
          break;
        default:
          // Invalid char, fail.
          return NULL;
      }
    }

    char* s = malloc(sizeof(char) * (length + 1));
    if(!s) {
      return NULL;
    }

    size_t pos = 0;
    char* token = strtok(input, " ");
    while(token != NULL) {

      if(strcmp(token, ".-") == 0) {
        s[pos] = 'A';
        pos++;
      } else
      if(strcmp(token, "-...") == 0) {
        s[pos] = 'B';
        pos++;
      } else
      if(strcmp(token, "-.-.") == 0) {
        s[pos] = 'C';
        pos++;
      } else
      if(strcmp(token, "-..") == 0) {
        s[pos] = 'D';
        pos++;
      } else
      if(strcmp(token, ".") == 0) {
        s[pos] = 'E';
        pos++;
      } else
      if(strcmp(token, "..-.") == 0) {
        s[pos] = 'F';
        pos++;
      } else
      if(strcmp(token, "--.") == 0) {
        s[pos] = 'G';
        pos++;
      } else
      if(strcmp(token, "....") == 0) {
        s[pos] = 'H';
        pos++;
      } else
      if(strcmp(token, "..") == 0) {
        s[pos] = 'I';
        pos++;
      } else
      if(strcmp(token, ".---") == 0) {
        s[pos] = 'J';
        pos++;
      } else
      if(strcmp(token, "-.-") == 0) {
        s[pos] = 'K';
        pos++;
      } else
      if(strcmp(token, ".-..") == 0) {
        s[pos] = 'L';
        pos++;
      } else
      if(strcmp(token, "--") == 0) {
        s[pos] = 'M';
        pos++;
      } else
      if(strcmp(token, "-.") == 0) {
        s[pos] = 'N';
        pos++;
      } else
      if(strcmp(token, "---") == 0) {
        s[pos] = 'O';
        pos++;
      } else
      if(strcmp(token, ".--.") == 0) {
        s[pos] = 'P';
        pos++;
      } else
      if(strcmp(token, "--.-") == 0) {
        s[pos] = 'Q';
        pos++;
      } else
      if(strcmp(token, ".-.") == 0) {
        s[pos] = 'R';
        pos++;
      } else
      if(strcmp(token, "...") == 0) {
        s[pos] = 'S';
        pos++;
      } else
      if(strcmp(token, "-") == 0) {
        s[pos] = 'T';
        pos++;
      } else
      if(strcmp(token, "..-") == 0) {
        s[pos] = 'U';
        pos++;
      } else
      if(strcmp(token, "...-") == 0) {
        s[pos] = 'V';
        pos++;
      } else
      if(strcmp(token, ".--") == 0) {
        s[pos] = 'W';
        pos++;
      } else
      if(strcmp(token, "-..-") == 0) {
        s[pos] = 'X';
        pos++;
      } else
      if(strcmp(token, "-.--") == 0) {
        s[pos] = 'Y';
        pos++;
      } else
      if(strcmp(token, "--..") == 0) {
        s[pos] = 'Z';
        pos++;
      } else
      if(strcmp(token, ".----") == 0) {
        s[pos] = '1';
        pos++;
      } else
      if(strcmp(token, "..---") == 0) {
        s[pos] = '2';
        pos++;
      } else
      if(strcmp(token, "...--") == 0) {
        s[pos] = '3';
        pos++;
      } else
      if(strcmp(token, "....-") == 0) {
        s[pos] = '4';
        pos++;
      } else
      if(strcmp(token, ".....") == 0) {
        s[pos] = '5';
        pos++;
      } else
      if(strcmp(token, "-....") == 0) {
        s[pos] = '6';
        pos++;
      } else
      if(strcmp(token, "--...") == 0) {
        s[pos] = '7';
        pos++;
      } else
      if(strcmp(token, "---..") == 0) {
        s[pos] = '8';
        pos++;
      } else
      if(strcmp(token, "----.") == 0) {
        s[pos] = '9';
        pos++;
      } else
      if(strcmp(token, "-----") == 0) {
        s[pos] = '0';
        pos++;
      } else

      {
        // This should be unreachable!
        free(s);
        return NULL;
      }

      token = strtok(NULL, " ");
    }

    s[pos] = 0;

    return s;

  }

  // TODO: ROTN
  // Our alphabet might be bigger than traditional.
  // Don't care.
  //char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
  //char* rotn_encode(char* input, size_t inlength, size_t n);

  // TODO: ITA2

#endif

#ifndef EVIL_NO_FLOW
  // Included by default
  
  #define then ){
  #define end }
  #define If if(
  #define Else } else {
  #define For for(
  #define While while(
  #define Do do{
  #define Switch(x) switch(x){
  #define Case(x) case x:
#endif

#ifdef EVIL_HASH
  #include <stdint.h>
  #include <stddef.h>

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  #pragma GCC diagnostic ignored "-Wconversion"

  #ifdef INT64_MAX
  uint64_t jenkins64(char* key, size_t length) {
    size_t i = 0;
    uint64_t hash = 0;
    while(i != length) {
      hash += (uint64_t)key[i++];
      hash += hash << 10;
      hash += hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
  }
  uint64_t fletcher64(char* key, size_t length) {
    uint64_t a = 0;
    uint64_t b = 0;
    for(size_t i = 0; i < length; i++) {
      a = (a + (uint64_t)key[i]) % 4294967295;
      b = (b + a) % 4294967295;
    }
    return (b << 16) | a;
  }
  #endif

  uint32_t jenkins32(char* key, size_t length) {
    size_t i = 0;
    uint32_t hash = 0;
    while(i != length) {
      hash += key[i++];
      hash += hash << 10;
      hash += hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
  }
  uint32_t adler32(char* key, size_t length) {
    uint32_t sa = 1;
    uint32_t sb = 0;
    for(size_t i = 0; i < length; i++) {
      sa = (sa + (uint32_t)key[i]) % 65521;
      sb = (sb + sa) % 65521;
    }
    return (sb << 16) | sa;
  }
  uint32_t fletcher32(char* key, size_t length) {
    uint32_t a = 0;
    uint32_t b = 0;
    for(size_t i = 0; i < length; i++) {
      a = (a + (uint32_t)key[i]) % 65535;
      b = (b + a) % 65535;
    }
    return (b << 16) | a;
  }
  uint16_t fletcher16(char* key, size_t length) {
    uint16_t a = 0;
    uint16_t b = 0;
    for(size_t i = 0; i < length; i++) {
      a = (a + (uint16_t)key[i]) % 255;
      b = (b + a) % 255;
    }
    return (b << 16) | a;
  }

  #pragma GCC diagnostic pop

#endif
#ifdef EVIL_HELP
  // Excluded by default: Includes a lot of strings.


  #include <stdio.h>
  #include <string.h>

  #ifndef EVIL_NO_HELP_MANUAL
  void evil_manual(void);
  #endif

  void evil_explain(const char* token);

  #ifndef EVIL_NO_WARN
  #warning "Not Yet Fully Implemented"
  #endif

  #ifndef EVIL_NO_HELP_MANUAL
  void evil_manual(void) {
  	printf("# CNoEvil v%s\n\n", CNOEVIL);
  	printf("Using hash version: %s\n\n", EVIL_HASH_VER);

    printf("%s\n\n", "CNoEvil abuses the hell out of the C pre-processor, and other C language features, to create a language that is still technically C, but looks and behaves differently, whilst remaining fully compatible with C.");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "# Expected Behaviour");
  	printf("%s\n\n", "Some definitions can produce warnings. Hide these by defining `EVIL_NO_WARN` before including `evil.h`.");
    printf("%s\n\n", "Some definitions can produce errors. There is no option to hide these.");
    printf("%s\n\n", "Definitions are expected to be created before the `evil.h` file is included.");
    printf("%s\n\n", "e.g.");

    printf("%s\n\n", "    #define EVIL_HASH");
    printf("%s\n\n", "    #include \"evil.h\"");

    printf("%s", "\n---\n\n");
  	printf("%s\n\n", "# Libraries Available by Default:");
  	printf("%s\n\n", "* Evil_Bool (Exclude by defining `EVIL_NO_BOOL` before including evil.h)");
  	printf("%s\n\n", "* Evil_Comment (Exclude by defining `EVIL_NO_COMMENT` before including evil.h)");
  	printf("%s\n\n", "* Evil_Flow (Exclude by defining `EVIL_NO_FLOW` before including evil.h)");
  	printf("%s\n\n", "* Evil_Int (Exclude by defining `EVIL_NO_INT` before including evil.h)");
  	printf("%s\n\n", "* Evil_IO (Exclude by defining `EVIL_NO_IO` before including evil.h)");
    printf("%s\n\n", "* Evil_Klass (Exclude by defining `EVIL_NO_KLASS` before including evil.h)");
  	printf("%s\n\n", "* Evil_Main (Exclude by defining `EVIL_NO_MAIN` before including evil.h)");
  	printf("%s\n\n", "* Evil_Proc (Exclude by defining `EVIL_NO_PROC` before including evil.h)");
  	printf("%s\n\n", "* Evil_Specifier (Exclude by defining `EVIL_NO_SPECIFIER` before including evil.h)");
  	printf("%s\n\n", "* Evil_Structures (Exclude by defining `EVIL_NO_STRUCT` before including evil.h)");
  	printf("%s", "\n---\n\n");

  	printf("%s\n\n", "# Other Libraries Available:");
  	printf("%s\n\n", "* Evil Assert (Import be defining `EVIL_ASSERT` before including evil.h)");
    printf("%s\n\n", "* Evil Bit (Import by defining `EVIL_BIT` before including evil.h)");
  	printf("%s\n\n", "* Evil Cli (Import be defining `EVIL_CLI` before including evil.h)");
  	printf("%s\n\n", "* Evil Coroutine (Import be defining `EVIL_COROUTINE` before including evil.h)");
    printf("%s\n\n", "* Evil Encode (Import by defining `EVIL_ENCODE` before including evil.h)");
  	printf("%s\n\n", "* Evil Hash (Import be defining `EVIL_HASH` before including evil.h)");
  	printf("%s\n\n", "* Evil Help (Import be defining `EVIL_HELP` before including evil.h)");
  	printf("%s\n\n", "* Evil Lambda (Import be defining `EVIL_LAMBDA` before including evil.h)");
  	printf("%s\n\n", "* Evil List (Import be defining `EVIL_LIST` before including evil.h)");
  	printf("%s\n\n", "* Evil Log (Import be defining `EVIL_LOG` before including evil.h)");
  	printf("%s\n\n", "* Evil Malloc (Import be defining `EVIL_MALLOC` before including evil.h)");
  	printf("%s\n\n", "* Evil Math (Import be defining `EVIL_MATH` before including evil.h)");
  	printf("%s\n\n", "* Evil Random (Import be defining `EVIL_RANDOM` before including evil.h)");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "# Libraries:");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Bool");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_BOOL` before including evil.h");
  	printf("%s\n\n", "This library ensures that the identifies `true`, `false` and `bool` are defined.");
  	printf("%s\n\n", "It can be thought of as an equivalent to stdbool.h");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Comment");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_COMMENT` before including evil.h");
  	printf("%s\n\n", "Allows you to use the `comment(...)` syntax for creating comments.");
  	printf("%s\n\n", "### Example");

  	printf("%s\n\n", "    comment(1 + 2 = 3);");

  	printf("%s\n\n", "`comment` can take any valid identifier. You may want to use strings normally.");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Flow");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_FLOW` before including evil.h");
  	printf("%s\n\n", "Defines the keywords for most of CNoEvil's syntax.");
    printf("%s\n\n", "* then - A keyword, used to follow some constructs (such as If, While, etc.)");
    printf("%s\n\n", "* end - A keyword, used to close functions, and some other constructs.");
    printf("%s\n\n", "* If - A keyword, used to replace C's bracket'd `if`. i.e. Equivalent to `if(`.");
    printf("%s\n\n", "* For - A keyword, used to replace C's bracket'd `for`. i.e. Equivalent to `for(`.");
    printf("%s\n\n", "* While - A keyword, used to replace C's bracket'd `while`. i.e. Equivalent to `while(`.");
    printf("%s\n\n", "* Do - A keyword, replaces C's `do`, and opens the block automatically.");
    printf("%s\n\n", "* Switch(T) - A macro, creates and opens the block of a switch statement.");
  	printf("%s\n\n", "### Example");

  	printf("%s\n", "    If 1 + 2 == 3 then");
  	printf("%s\n", "        return 1;");
  	printf("%s\n", "    Else");
  	printf("%s\n", "        return 0;");
  	printf("%s\n\n", "    end");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Int");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_INT` before including evil.h");
  	printf("%s\n\n", "Defines up to two type specifiers:");
  	printf("%s\n\n", "* Number (if `int64_t` is supported). Equivalent to `int64_t`.");
  	printf("%s\n\n", "* Decimal. Equivalent to `long double`.");
    printf("%s\n\n", "Defines up to two macros:");
    printf("%s\n\n", "* MaxNumber (if `int64_t` is supported). Equivalent to `INT64_MAX`.");
    printf("%s\n\n", "* MaxDecimal. Equivalent to `LDBL_MAX`.");
  	printf("%s\n\n", "### Example");

  	printf("%s\n", "    Decimal(y);");
  	printf("%s\n\n", "    Number(x) = 12;");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil IO");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_IO` before including evil.h");
  	printf("%s\n\n", "display(T) - Prints a representation of the given value to stdout.");
    printf("%s\n\n", "displayf(F, T) - Prints a representation of the given value to F, a `FILE*`.");
    printf("%s\n\n", "displayln(T) - Prints a representation of the given value to stdout, followed by a system-compatible line ending.");
    printf("%s\n\n", "displayfln(F, T) - Prints a representation of the given value to F, a `FILE*`, followed by a system-compatible line ending.");
    printf("%s\n\n", "endl - A keyword. Prints a system-comaptible line ending to stdout.");
    printf("%s\n\n", "endlf(F) - Prints a system-comaptible line ending to F, a `FILE*`.");
    printf("%s\n\n", "repr_type(T) - Returns a `char*` containing a text representation of the type. Optimisation may effect results. Returns \"Unknown\" for any type that cannot be accounted for.");
    printf("%s\n\n", "### Example");
    printf("%s\n", "    displayln(\"Hello, World!\");");
    printf("%s\n", "    displayln(213);");
    printf("%s\n\n", "    displayln(repr_type(\"Hello, World!\"));");

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Main");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_MAIN` before including evil.h");
  	printf("%s\n\n", "* Main - A keyword, expected to be followed by keyword `then`. Automatically makes argc and argv available. Use instead of the `main` function. Exclude by defining `EVIL_NO_MAIN`.");
  	printf("%s\n\n", "### Example");

  	printf("%s\n\n", "    #include \"evil.h\"");
  	printf("%s\n", "    Main then");
  	printf("%s\n", "      displayln(\"Hello, World!\");");
  	printf("%s\n\n", "    end");
  	
  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Proc");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_PROC` before including evil.h");
  	printf("%s\n\n", "Introduces two syntactic elements:");
  	printf("%s\n\n", "* declare(Name, ReturnType, ...); - A variadic macro. Arguments are as in C function arguments. Declares a C function.");
    printf("%s\n\n", "* proc(Name, ReturnType, ...) - A variadic macro. Arguments are as in C function arguments. Creates the start of a C function, that is, it is followed by a function body.");
    printf("%s\n\n", "### Example");

	  printf("%s\n\n","    #include \"evil.h\"");
	  printf("%s\n\n","    declare(add2, int, int a);");
	  printf("%s\n","    proc(add2, int, int a)");
	  printf("%s\n","      return a + 2;");
	  printf("%s\n\n","    end");
	  printf("%s\n","    Main then");
	  printf("%s\n","      displayln(add2(2));");
	  printf("%s\n\n","    end");
  	
  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Specifier");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_SPECIFIER` before including evil.h");
  	printf("%s\n\n", "contant(Type, Name, Value) - A macro, generates a `const`.");
    printf("%s\n\n", "storage(Type, Name, Value) - A macro, generates a `static`.");
    printf("%s\n\n", "### Example");
    printf("%s\n", "    constant(int, x, 12);");
    printf("%s\n\n", "    storage(int, y, 12);");
  	
  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Structures");
  	printf("%s\n\n", "Exclude by defining `EVIL_NO_STRUCT` before including evil.h");
  	printf("%s\n\n", "Struct(Name) - Starts a struct definition.");
    printf("%s\n\n", "Union(Name) - Start a union definition.");
    printf("%s\n\n", "Typedef - A keyword, exactly equivalent to `typedef`.");
    printf("%s\n\n", "BitField(Name, Type, Width) - Used for defining a Bitfield inside a struct.");
    printf("%s\n\n", "### Example");
    printf("%s\n", "    Struct(Pair)");
    printf("%s\n", "        int a;");
    printf("%s\n", "        int b;");
    printf("%s\n\n", "    end;");
    printf("%s\n\n", "    struct Pair x = {1, 2};");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Klass");
    printf("%s\n\n", "Exclude by defining `EVIL_NO_KLASS` before including evil.h");
    printf("%s\n\n", "This module is still under construction.");
    // TODO

  	printf("%s", "\n---\n\n");
  	printf("%s\n\n", "## Evil Assert");
  	printf("%s\n\n", "Import by defining `EVIL_ASSERT` before including evil.h");
  	printf("%s\n\n", "Defines two identifiers:");
  	printf("%s\n\n", "* Assert(statement);");
  	printf("%s\n\n", "* AssertMsg(statement, reason);");
  	printf("%s\n\n", "If NDEBUG is defined, they become no-ops.");
  	printf("%s\n\n", "Otherwise, if the statement is true, the halt the program and spit out a helpful trace.");

  	printf("%s\n\n", "### Example");
  	printf("%s\n", "    Assert(false == true);");
  	printf("%s\n\n", "    AssertMsg(false == true, \"This is impossible.\");");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Cli");
    printf("%s\n\n", "Import by defining `EVIL_CLI` before including evil.h");
    printf("%s\n\n", "This module provides a variety of functions for working with the terminal, by using ANSI escape sequences.");
    printf("%s\n\n", "### Warnings");
    printf("%s\n\n", "* If EVIL_ASSERT is not defined, then cli_fg_256 and cli_bg_256 will be unavailable.");
    printf("%s\n\n", "* None of the module's functions check if the function is supported by current terminal.");
    printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "* cli_reset() - Removes any active effects and colors from the terminal.");
    printf("%s\n\n", "* cli_fg_256(N) - Takes a number between 0-255, and applies the corresponding color to the terminal text.");
    printf("%s\n\n", "* cli_bg_256(N) - Takes a number between 0-255, and applies the corresponding color to the terminal background.");
    printf("%s\n\n", "* cli_fg_rgb(R,G,B) - Takes three values (Red, Green, Blue), each of which is a number in the range 0-255, and applies the corresponding truecolor to the terminal text.");
    printf("%s\n\n", "* cli_bg_rgb(R,G,B) - Takes three values (Red, Green, Blue), each of which is a number in the range 0-255, and applies the corresponding truecolor to the terminal background.");
    printf("%s\n\n", "* cli_cursor_up(N) - Moves the console cursor up N lines.");
    printf("%s\n\n", "* cli_cursor_down(N) - Moves the console cursor down N lines.");
    printf("%s\n\n", "* cli_cursor_right(N) - Moves the console cursor right N characters.");
    printf("%s\n\n", "* cli_cursor_left(N) - Moves the console cursor left N characters.");
    printf("%s\n\n", "* cli_cursor_save() - Saves the current cursor position.");
    printf("%s\n\n", "* cli_cursor_restore() - Moves the cursor to the last saved position.");
    printf("%s\n\n", "* cli_screen_clear() - Clears the current terminal screen.");
    printf("%s\n\n", "* cli_screen_clear_before() - Clears the current terminal screen, before the cursor.");
    printf("%s\n\n", "* cli_screen_clear_after() - Clears the current terminal screen, after the cursor.");
    printf("%s\n\n", "* cli_line_clear() - Clears the current terminal line.");
    printf("%s\n\n", "* cli_line_clear_before() - Clears the current terminal line, before the cursor.");
    printf("%s\n\n", "* cli_line_clear_after() - Clears the current terminal line, after the cursor.");
    printf("%s\n\n", "* cli_effect_reset() - Removes any active effects from the terminal.");
    printf("%s\n\n", "* cli_effect_bold() - Activates the bold text terminal effect.");
    printf("%s\n\n", "* cli_effect_underline() - Activates the underlined text terminal effect.");
    printf("%s\n\n", "* cli_effect_reverse() - Activates the reversed text terminal effect.");
    printf("%s\n\n", "* cli_effect_blink() - Activates the blinking text terminal effect. (Often disabled on modern terminals).");
    printf("%s\n\n", "* cli_effect_invisible() - Activates the invisible text terminal effect.");
    printf("%s\n\n", "* cli_fg_black() - Sets the terminal text to simple black.");
    printf("%s\n\n", "* cli_fg_red() - Sets the terminal text to simple red.");
    printf("%s\n\n", "* cli_fg_green() - Sets the terminal text to simple green.");
    printf("%s\n\n", "* cli_fg_yellow() - Sets the terminal text to simple yellow.");
    printf("%s\n\n", "* cli_fg_blue() - Sets the terminal text to simple blue.");
    printf("%s\n\n", "* cli_fg_magenta() - Sets the terminal text to simple magenta.");
    printf("%s\n\n", "* cli_fg_cyan() - Sets the terminal text to simple cyan.");
    printf("%s\n\n", "* cli_fg_white() - Sets the terminal text to simple white.");
    printf("%s\n\n", "* cli_fg_bright_black() - Sets the terminal text to complex black.");
    printf("%s\n\n", "* cli_fg_bright_red() - Sets the terminal text to complex red.");
    printf("%s\n\n", "* cli_fg_bright_green() - Sets the terminal text to complex green.");
    printf("%s\n\n", "* cli_fg_bright_yellow() - Sets the terminal text to complex yellow.");
    printf("%s\n\n", "* cli_fg_bright_blue() - Sets the terminal text to complex blue.");
    printf("%s\n\n", "* cli_fg_bright_magenta() - Sets the terminal text to complex magenta.");
    printf("%s\n\n", "* cli_fg_bright_cyan() - Sets the terminal text to complex cyan.");
    printf("%s\n\n", "* cli_fg_bright_white() - Sets the terminal text to complex white.");
    printf("%s\n\n", "* cli_bg_black() - Sets the terminal background to simple black.");
    printf("%s\n\n", "* cli_bg_red() - Sets the terminal background to simple red.");
    printf("%s\n\n", "* cli_bg_green() - Sets the terminal background to simple green.");
    printf("%s\n\n", "* cli_bg_yellow() - Sets the terminal background to simple yellow.");
    printf("%s\n\n", "* cli_bg_blue() - Sets the terminal background to simple blue.");
    printf("%s\n\n", "* cli_bg_magenta() - Sets the terminal background to simple magenta.");
    printf("%s\n\n", "* cli_bg_cyan() - Sets the terminal background to simple cyan.");
    printf("%s\n\n", "* cli_bg_white() - Sets the terminal background to simple white.");
    printf("%s\n\n", "* cli_bg_bright_black() - Sets the terminal background to complex black.");
    printf("%s\n\n", "* cli_bg_bright_red() - Sets the terminal background to complex red.");
    printf("%s\n\n", "* cli_bg_bright_green() - Sets the terminal background to complex green.");
    printf("%s\n\n", "* cli_bg_bright_yellow() - Sets the terminal background to complex yellow.");
    printf("%s\n\n", "* cli_bg_bright_blue() - Sets the terminal background to complex blue.");
    printf("%s\n\n", "* cli_bg_bright_magenta() - Sets the terminal background to complex magenta.");
    printf("%s\n\n", "* cli_bg_bright_cyan() - Sets the terminal background to complex cyan.");
    printf("%s\n\n", "* cli_bg_bright_white() - Sets the terminal background to complex white.");
    printf("%s\n\n", "## Example");
    printf("%s\n\n", "```");
    printf("%s\n", "    #define EVIL_IO");
    printf("%s\n", "    #define EVIL_CLI");
    printf("%s\n", "    #include \"evil.h\"");
    printf("\n");
    printf("%s\n", "    Main then");
    printf("%s\n", "      cli_fg_magenta();");
    printf("%s\n", "      cli_bg_white();");
    printf("%s\n", "      displayln(\"Coloured text!\");");
    printf("%s\n", "      cli_reset();");
    printf("%s\n", "    end");
    printf("%s\n\n", "```");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Coroutine");
    printf("%s\n\n", "Import by defining `EVIL_COROUTINE` before including evil.h");
    printf("%s\n\n", "### Warnings:");
    printf("%s\n\n", "* Lambda's don't play well with Coroutines. Avoid using them in the body of a coroutine.");
    printf("%s\n\n", "* Coroutine's don't support nesting. It may work sometimes, other times it may explode.");
    printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "coroutine() - A macro that marks the beginning of a coroutine body.");
    printf("%s\n\n", "co_return(T) - A macro that marks a return from a coroutine.");
    printf("%s\n\n", "co_end() - A macro that closes a coroutine body.");
    printf("%s\n\n", "### Example");
    printf("%s\n", "```");
    printf("%s\n", "    #define EVIL_IO");
    printf("%s\n", "    #define EVIL_COROUTINE");
    printf("%s\n", "    #include \"evil.h\"");
    printf("%s\n", "    proc(example, int)");
    printf("%s\n", "    storage(int, i, 0);");
    printf("%s\n", "    coroutine();");
    printf("%s\n", "    While true then");
    printf("%s\n", "      co_return(++i);");
    printf("%s\n", "    end");
    printf("%s\n", "    co_end();");
    printf("%s\n", "    return i;");
    printf("%s\n", "  end");
    printf("\n\n");
    printf("%s\n", "  Main then");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "    displayln(example());");
    printf("%s\n", "  end");
    printf("%s\n\n", "```");
  	
    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Hash");
    printf("%s\n\n", "Import by defining `EVIL_HASH` before including evil.h");
    printf("%s\n\n", "### Warnings");
    printf("%s\n\n", "* if int64_t is unavailable, then jenkins64, fletcher64 won't be defined.");
    printf("%s\n\n", "* These are _not_ cryptographic safe hashes.");
    printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "* jenkins64(char* key, size_t length) - Hash a given string into a uint64_t. Based on Jenkins One-At-A-Time hash.");
    printf("%s\n\n", "* jenkins32(char* key, size_t length) - Hash a given string into a uint32_t. Based on Jenkins One-At-A-Time hash.");

    printf("%s\n\n", "* fletcher64(char* key, size_t length) - Hash a given string into a uint64_t. Based on Fletcher's checksum.");
    printf("%s\n\n", "* fletcher32(char* key, size_t length) - Hash a given string into a uint32_t. Based on Fletcher's checksum.");
    printf("%s\n\n", "* fletcher16(char* key, size_t length) - Hash a given string into a uint16_t. Based on Fletcher's checksum.");
    
    printf("%s\n\n", "* adler32(char* key, size_t length) - Hash a given string into a uint32_t. Based on Adler-32.");

    printf("%s\n\n", "### Example");
    printf("%s\n\n", "```");
    printf("%s\n", "    #define EVIL_HASH");
    printf("%s\n", "    #include \"evil.h\"");
    printf("%c", '\n');
    printf("%s\n", "    Main then");
    printf("%s\n", "      displayln(jenkins64(\"Hello, World!\", 12));");
    printf("%s\n", "      displayln(jenkins32(\"Hello, World!\", 12));");
    printf("%c", '\n');      
    printf("%s\n", "      displayln(fletcher64(\"Hello, World!\", 12));");
    printf("%s\n", "      displayln(fletcher32(\"Hello, World!\", 12));");
    printf("%s\n", "      displayln(fletcher16(\"Hello, World!\", 12));");
    printf("%c", '\n');
    printf("%s\n", "      displayln(adler32(\"Hello, World!\", 12));");
    printf("%s\n", "    end");
    printf("%s\n\n", "```");
  	
    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Help");
    printf("%s\n\n", "Import by defining `EVIL_HELP` before including evil.h");
    printf("%s\n\n", "Defines two functions:");
    printf("%s\n\n", "* void evil_explain(const char* s)");
    printf("%s\n\n", "* void evil_manual(void)");
    printf("%s\n\n", "evil_manual prints this entire document to stdout.");
    printf("%s\n\n", "evil_explain looks up an identifier and prints some information about it to stdout.");
    printf("%s\n\n", "If `EVIL_NO_HELP_MANUAL` is defined, then evil_manual won't be created.");
  	
    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Lambda");
    printf("%s\n\n", "Import by defining `EVIL_LAMBDA` before including evil.h");
    printf("%s\n\n", "functionPointer = lambda(returnType, body)");
    printf("%s\n\n", "Lambda is a slightly more advanced feature, which requires the user how to construct and use function pointers.");
    printf("%s\n", "```");
    printf("%s\n\n", "### Example");
    printf("%s\n", "    #define EVIL_LAMBDA");
    printf("%s\n", "    #include \"evil.h\"");
    printf("%c", '\n');
    printf("%s\n", "    Main then");
    printf("%s\n", "      int (*max)(int, int) = lambda(int,");
    printf("%s\n", "                                 (int x, int y) {");
    printf("%s\n", "                                  return x > y ? x : y;");
    printf("%s\n", "                                 });");
    printf("%c", '\n');
    printf("%s\n", "      displayln(max(1, 2));");
    printf("%s\n", "    end");
    printf("%s\n\n", "```");
  	
    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Malloc");
    printf("%s\n\n", "Import by defining `EVIL_MALLOC` before including evil.h");
    printf("%s\n\n", "Provides checked_malloc:");
    printf("%s\n\n", "`checked_malloc(object, object_type, buffer, fail_msg, exit_q)`");
    printf("%s\n\n", "* object - The identifier being assigned to.");
    printf("%s\n\n", "* object_type - The type of the identifier being assigned to.");
    printf("%s\n\n", "* buffer - The size of the buffer to pass to malloc.");
    printf("%s\n\n", "* fail_msg - A string to print to stderr if it fails to allocate.");
    printf("%s\n\n", "* exit_q - A boolean. If true, terminates the program.");
    printf("%s\n\n", "### Example");
    printf("%s\n", "```");
    printf("%s\n","    #define EVIL_MALLOC");
    printf("%s\n","    #include \"evil.h\"");
    printf("%c", '\n');
    printf("%s\n","    Main then");
    printf("%s\n","      comment(\"This will exit if malloc fails.\");");
    printf("%s\n","      checked_malloc(x, char*, sizeof(char) * 6, \"Out of Memory\", true);");
    printf("%c", '\n');
    printf("%s\n","      x[0] = 'H';");
    printf("%s\n","      x[1] = 'e';");
    printf("%s\n","      x[2] = 'l';");
    printf("%s\n","      x[3] = 'l';");
    printf("%s\n","      x[4] = 'o';");
    printf("%s\n","      x[5] = '\0';");
    printf("%c", '\n');
    printf("%s\n","      displayln(x);");
    printf("%s\n","      free(x);");
    printf("%s\n","    end");
    printf("%s\n\n", "```");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Managed");
    printf("%s\n\n", "Import by defining `EVIL_MANAGED` before including evil.h");
  	printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "* finalise(func)");
    printf("%s\n\n", "* var(type, finaliser, name)");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Math");
    printf("%s\n\n", "Import by defining `EVIL_MATH` before including evil.h");
    printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "* add(a, b)");
    printf("%s\n\n", "* take(a, b)");
    printf("%s\n\n", "* multiply(a, b)");
    printf("%s\n\n", "* divide(a, b)");
    printf("%s\n\n", "* math.h");
  	
    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Random");
    printf("%s\n\n", "Import by defining `EVIL_RANDOM` before including evil.h");
    printf("%s\n\n", "### Warnings");
    printf("%s\n\n", "* `randomseed` and `random` use C-rand, which is not cryptographically strong.");
    printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "* `randomseed(void)` - Seed the random generator.");
    printf("%s\n\n", "* `random(min, max)` - Get a random integer in a given range.");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Log");
    printf("%s\n\n", "Import by defining `EVIL_LOG` before including evil.h");
    printf("%s\n\n", "### Warnings");
    printf("%s\n\n", "* `debug(char*)` is a no-op, unless `DEBUG_LOG` is defined.");
    printf("%s\n\n", "### Definitions");
    printf("%s\n\n", "* `message(char* )` \n\n Logs a message to stdout. If (char\\*)message_file has a length > 0, then logs to that file in append mode. If (char\\*)log_file has a length > 0, then logs to that file in append mode.");
    printf("%s\n\n", "* `warning(char* )` \n\n Logs a message to stdout. If (char\\*)warning_file has a length > 0, then logs to that file in append mode. If (char\\*)log_file has a length > 0, then logs to that file in append mode.");
    printf("%s\n\n", "* `critical(char* )` \n\n Logs a message to stderr. If (char\\*)critical_file has a length > 0, then logs to that file in append mode. If (char\\*)log_file has a length > 0, then logs to that file in append mode.");
    printf("%s\n\n", "* `error(char* )` \n\n Logs a message to stderr. If (char\\*)error_file has a length > 0, then logs to that file in append mode. If (char\\*)log_file has a length > 0, then logs to that file in append mode.");
    printf("%s\n\n", "* `info(char* )` \n\n Logs a message to stdout. If (char\\*)info_file has a length > 0, then logs to that file in append mode. If (char\\*)log_file has a length > 0, then logs to that file in append mode.");
    printf("%s\n\n", "* `debug(char* )` \n\n If DEBUG_LOG defined, logs a message to stdout. If (char\\*)debug_file has a length > 0, then logs to that file in append mode. If (char*)log_file has a length > 0, then logs to that file in append mode.");
    printf("%s\n\n", "* `debug(char* )` \n\n If DEBUG_LOG not defined, doesn't do anything.");
  	
    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Bit");
    printf("%s\n\n", "Import by defining `EVIL_BIT` before including evil.h");
    printf("%s\n\n", "Adds worded bit operators.");
    printf("%s\n\n", "# Defines:");
    printf("%s\n\n", "* BIT_AND(a, b)");
    printf("%s\n\n", "* BIT_OR(a, b)");
    printf("%s\n\n", "* BIT_XOR(a, b)");
    printf("%s\n\n", "* BIT_NOT(a)");
    printf("%s\n\n", "* BIT_RSHIFT(a, b)");
    printf("%s\n\n", "* BIT_LSHIFT(a, b)");

    printf("%s", "\n---\n\n");
    printf("%s\n\n", "## Evil Encode");
    printf("%s\n\n", "Import by defining `EVIL_ENCODE` before including evil.h");
    printf("%s\n\n", "This module is still under construction.");
    // TODO
  }
  #endif

void evil_explain(const char* token) {
  if(strncmp("EVIL_NO_WARN", token, 12) == 0) {
    printf("%s\n\n", "Silences CnoEvil compile-time warnings, when defined.");
    printf("%s\n\n", "Do not use unless you understand the full implications.");
  } else
  // EVIL_BOOL (default)
  if(strncmp("true", token, 6) == 0) {
    printf("%s\n\n", "bool - defined in `EVIL_BOOL`.");
  } else
  if(strncmp("false", token, 6) == 0) {
    printf("%s\n\n", "bool - defined in `EVIL_BOOL`.");
  } else
  if(strncmp("bool", token, 5) == 0) {
    printf("%s\n\n", "type - defined in `EVIL_BOOL`.");
  } else
  if(strncmp("__bool_true_false_are_defined", token, 27) == 0) {
    printf("%s\n\n", "Value of 1 - defined in `EVIL_BOOL`.");
  } else
  if(strncmp("EVIL_BOOL", token, 9) == 0) {
    printf("%s\n\n","module - Adds booleans.");
    printf("%s\n\n","Available by default.");
    printf("%s\n\n","Exclude by defining `EVIL_NO_BOOL`");
  } else
  if(strncmp("EVIL_NO_BOOL", token, 12) == 0) {
    printf("%s\n\n","Exclude the `EVIL_BOOL` module when defined.");
  } else
  // EVIL_COMMENT (default)
  if(strncmp("EVIL_COMMENT", token, 11) == 0) {
    printf("%s\n\n","module - Adds a comment syntax.");
    printf("%s\n\n","Available by default.");
    printf("%s\n\n","Exclude by defining `EVIL_NO_COMMENT`");
  } else
  if(strncmp("EVIL_NO_COMMENT", token, 15) == 0) {
    printf("%s\n\n","Exclude the `EVIL_COMMENT` module when defined.");
  } else
  if(strncmp("comment", token, 7) == 0) {
    printf("%s\n\n","`comment(statement);` - Make comments like normal functions.");
    printf("%s\n\n", "Defined in `EVIL_COMMENT`.");
  } else
  // EVIL_FLOW (default)
  if(strncmp("EVIL_FLOW", token, 10) == 0) {
    printf("%s\n\n","module - Adds a new syntax.");
    printf("%s\n\n","Available by default.");
    printf("%s\n\n","Exclude by defining `EVIL_NO_FLOW`");
  } else
  if(strncmp("EVIL_NO_FLOW", token, 12) == 0) {
    printf("%s\n\n","Exclude the `EVIL_FLOW` module when defined.");
  } else
  if(strncmp("then", token, 5) == 0) {
    printf("%s\n\n","`then` - Meant to follow most flow statements.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("end", token, 4) == 0) {
    printf("%s\n\n","`end` - Meant to finish most flow statements.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("If", token, 3) == 0) {
    printf("%s\n\n","`If` - Opens an if statement without the need for braces.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("Else", token, 5) == 0) {
    printf("%s\n\n","`Else` - Closes one body, injects `else`, and opens a new body.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("For", token, 4) == 0) {
    printf("%s\n\n","`For` - Opens a for statement without the need for braces.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("While", token, 6) == 0) {
    printf("%s\n\n","`While` - Opens a while statement without the need for braces.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("Do", token, 3) == 0) {
    printf("%s\n\n","`Do` - Opens a do statement without the need for braces.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("Switch", token, 7) == 0) {
    printf("%s\n\n","`Switch(x)` - Opens a switch statement without the need for a following brace.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  if(strncmp("Case", token, 5) == 0) {
    printf("%s\n\n","`Case(x)` - Opens a case in a syntax-consistent way.");
    printf("%s\n\n", "Defined in `EVIL_FLOW`.");
  } else
  // EVIL_INT (default)
  if(strncmp("EVIL_INT", token, 9) == 0) {
    printf("%s\n\n","module - Adds number specifiers.");
    printf("%s\n\n","Available by default.");
    printf("%s\n\n","Exclude by defining `EVIL_NO_INT`");
  } else
  if(strncmp("EVIL_NO_INT", token, 11) == 0) {
    printf("%s\n\n","Exclude the `EVIL_INT` module when defined.");
  } else
  if(strncmp("Number", token, 7) == 0) {
    printf("%s\n\n","`Number(x)` - declare a number type. Equivalent to `int64_t`. If int64_t is not supported, this method is unavailable.");
    printf("%s\n\n", "Defined in `EVIL_INT`.");
  } else
  if(strncmp("Decimal", token, 8) == 0) {
    printf("%s\n\n","`Decimal(x)` - declare a float type. Equivalent to `long double`.");
    printf("%s\n\n", "Defined in `EVIL_INT`.");
  } else
  if(strncmp("MaxDecimal", token, 11) == 0) {
    printf("%s\n\n","`MaxDecimal` - The maximum value for a Decimal type.");
    printf("%s\n\n", "Defined in `EVIL_INT`.");
  } else
  if(strncmp("MaxNumber", token, 10) == 0) {
    printf("%s\n\n","`MaxNumber` - The maximum value for a Number type.");
    printf("%s\n\n", "Defined in `EVIL_INT`.");
  } else
  // EVIL_IO (default)
  if(strncmp("EVIL_IO", token, 7) == 0) {
    printf("%s\n\n","module - Adds IO helpers.");
    printf("%s\n\n","Available by default.");
    printf("%s\n\n","Exclude by defining `EVIL_NO_IO`");
  } else
  if(strncmp("EVIL_NO_IO", token, 10) == 0) {
    printf("%s\n\n","Exclude the `EVIL_IO` module when defined.");
  } else
  // display_format
  if(strncmp("display_format", token, 15) == 0) {
    printf("%s\n\n", "`display_format(x);`");
    printf("%s\n\n", "Creates a string that is probably a format specifier for the given object.");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // display
  if(strncmp("display", token, 15) == 0) {
    printf("%s\n\n", "`display(x);`");
    printf("%s\n\n", "Prints a representation of the given object to stdout.");
    printf("%s\n\n", "Also see: displayf, displayln, displayfln, endl.");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // displayf
  if(strncmp("displayf", token, 16) == 0) {
    printf("%s\n\n", "`displayf(file, x);`");
    printf("%s\n\n", "Prints a representation of the given object to the `FILE*` given as the first argument.");
    printf("%s\n\n", "Also see: display, displayln, displayfln, endl.");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // displayln
  if(strncmp("displayln", token, 17) == 0) {
    printf("%s\n\n", "`displayln(x);`");
    printf("%s\n\n", "Prints a representation of the given object to stdout, followed by a system-dependant newline.");
    printf("%s\n\n", "Also see: displayf, display, displayfln, endl.");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // displayfln
  if(strncmp("displayfln", token, 18) == 0) {
    printf("%s\n\n", "`displayfln(file, x);`");
    printf("%s\n\n", "Prints a representation of the given object to the `FILE*` given as the first argument, followed by a system-dependant newline.");
    printf("%s\n\n", "Also see: displayf, display, displayln, endl.");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // repr_type
  if(strncmp("repr_type", token, 10) == 0) {
    printf("%s\n\n", "`repr_type(x)`");
    printf("%s\n\n", "Creates a string representation of the type that the object probably is.");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // endl
  if(strncmp("endl", token, 5) == 0) {
    printf("%s\n\n", "`endl;`");
    printf("%s\n\n", "Sends a system-dependant newline to stdout.");
    printf("%s\n\n", "Also see: endlf");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // endlf
  if(strncmp("endlf", token, 5) == 0) {
    printf("%s\n\n", "`endlf(file);`");
    printf("%s\n\n", "Sends a system-dependant newline to the `FILE*` given as the first argument.");
    printf("%s\n\n", "Also see: endl");
    printf("%s\n\n", "Defined in `EVIL_IO`.");
  } else
  // stdio
  if(strncmp("stdio", token, 6) == 0) {
    printf("%s\n\n", "The stdio module.");
    printf("%s\n\n", "Imported by `EVIL_IO`.");
  } else
  // EVIL_MAIN (default)
  if(strncmp("EVIL_MAIN", token, 9) == 0) {
    printf("%s\n\n","module - Adds `Main`.");
    printf("%s\n\n","Available by default.");
    printf("%s\n\n","Exclude by defining `EVIL_NO_MAIN`");
  } else
  if(strncmp("EVIL_NO_MAIN", token, 13) == 0) {
    printf("%s\n\n", "Excludes `EVIL_MAIN1 when defined.");
  } else
  if(strncmp("Main", token, 5) == 0) {
    printf("%s\n\n", "Opens the `main` function, and defines argc and argv.");
    printf("%s\n\n", "See also: argc, argv");
    printf("%s\n\n", "Defined in `EVIL_MAIN`.");
  } else
  if(strncmp("argc", token, 5) == 0) {
    printf("%s\n\n", "Automatically available under `Main`.");
    printf("%s\n\n", "An `int` representing the number of arguments given on the command line.");
    printf("%s\n\n", "See also: Main, argv");
  } else
  if(strncmp("argv", token, 5) == 0) {
    printf("%s\n\n", "Automatically available under `Main`.");
    printf("%s\n\n", "A `char*[]` containing the arguments given on the command line.");
    printf("%s\n\n", "See also: Main, argc");
  } else
  // EVIL_PROC (default)
  if(strncmp("EVIL_PROC", token, 9) == 0) {
    printf("%s\n\n", "module - adds `proc` and `declare`.");
    printf("%s\n\n", "Available by default.");
    printf("%s\n\n", "Exclude by defining `EVIL_NO_PROC`");
  } else
  if(strncmp("EVIL_NO_PROC", token, 13) == 0) {
    printf("%s\n\n", "Exclude `EVIL_PROC` when defined");
  } else
  if(strncmp("proc", token, 5) == 0) {
    printf("%s\n\n", "proc(name, return type, args...) - Opens the body of a function definition.");
    printf("%s\n\n", "Defined in `EVIL_PROC`.");
  } else
  if(strncmp("declare", token, 5) == 0) {
    printf("%s\n\n", "declare(name, return type, args...); - Creates a function decleration.");
    printf("%s\n\n", "Defined in `EVIL_PROC`.");
  } else
  // EVIL_SPECIFIER (default)
  if(strncmp("EVIL_SPECIFIER", token, 15) == 0) {
    printf("%s\n\n", "module - Adds `constant` and `storage`.");
    printf("%s\n\n", "Available by default.");
    printf("%s\n\n", "Exclude by defining `EVIL_NO_SPECIFIER`.");
  } else
  if(strncmp("EVIL_NO_SPECIFIER", token, 17) == 0) {
    printf("%s\n\n", "Exclude `EVIL_SPECIFIER` when defined.");
  } else
  if(strncmp("constant", token, 8) == 0) {
    printf("%s\n\n", "constant(type, name, value); - Create constant value.");
    printf("%s\n\n", "Defined in `EVIL_SPECIFIER`.");
  } else
  if(strncmp("storage", token, 8) == 0) {
    printf("%s\n\n", "storage(type, name, value); - Create what the C standard calls a \"storage-class specifier\" value, a `static` value.");
    printf("%s\n\n", "Defined in `EVIL_SPECIFIER`.");
  } else
  // EVIL_STRUCTURES (default)
  if(strncmp("EVIL_STRUCTURES", token, 10) == 0) {
    printf("%s\n\n", "module - adds Struct, Union, Typedef and BitField.");
    printf("%s\n\n", "Available by default.");
    printf("%s\n\n", "Exclude by defining `EVIL_NO_STRUCT`");
  } else
  if(strncmp("EVIL_NO_STRUCT", token, 14) == 0) {
    printf("%s\n\n", "Exclude `EVIL_STRUCTURES` by defining.");
  } else
  if(strncmp("Struct", token, 6) == 0) {
    printf("%s\n\n", "Struct(name) - Opens a new structure definition.");
    printf("%s\n\n", "Defined in `EVIL_STRUCTURES`.");
  } else
  if(strncmp("Union", token, 6) == 0) {
    printf("%s\n\n", "Union(name) - Opens a new union definition.");
    printf("%s\n\n", "Defined in `EVIL_STRUCTURES`.");
  } else
  if(strncmp("BitField", token, 6) == 0) {
    printf("%s\n\n", "BitField(name, type, width); - Creates a bitfield specification.");
    printf("%s\n\n", "Defined in `EVIL_STRUCTURES`.");
  } else
  if(strncmp("Typedef", token, 6) == 0) {
    printf("%s\n\n", "Typedef - Creates a typedef in the same manner as `typedef`.");
    printf("%s\n\n", "Defined in `EVIL_STRUCTURES`.");
  } else
  // EVIL_ASSERT
  if(strncmp("EVIL_ASSERT", token, 11) == 0) {
    printf("%s\n\n", "module - An assertion library.");
    printf("%s\n\n", "Defines: Assert, AssertMsg");
    printf("%s\n\n", "See also: NDEBUG");
    printf("%s\n\n", "Import by defining `EVIL_ASSERT` before including `evil.h`.");
  } else
  if(strncmp("NDEBUG", token, 6) == 0) {
    printf("%s\n\n", "If defined, Assert and AssertMsg become no-nops.");
  } else
  if(strncmp("AssertMsg", token, 9) == 0) {
    printf("%s\n\n", "AssertMsg(statement, message); - If statement is not true, print a stacktrace with a given message, then raise SIGABRT.");
    printf("%s\n\n", "Defined in `EVIL_ASSERT`.");
  } else
  if(strncmp("Assert", token, 6) == 0) {
    printf("%s\n\n", "Assert(statement, message); - If statement is not true, print a stacktrace, then raise SIGABRT.");
    printf("%s\n\n", "Defined in `EVIL_ASSERT`.");
  } else
  // EVIL_MALLOC
  if(strncmp("EVIL_MALLOC", token, 11) == 0) {
    printf("%s\n\n", "module - A 'safer' malloc.");
    printf("%s\n\n", "Defines: checked_malloc");
    printf("%s\n\n", "Import by defining `EVIL_MALLOC` before including `evil.h`");
  } else
  if(strncmp("checked_malloc", token, 14) == 0) {
    printf("%s\n\n", "`checked_malloc(object, object_type, buffer, fail_msg, exit_q);`");
    printf("%s\n\n", "* object - The identifier being assigned to.");
    printf("%s\n\n", "* object_type - The type of the identifier being assigned to.");
    printf("%s\n\n", "* buffer - The size of the buffer to pass to malloc.");
    printf("%s\n\n", "* fail_msg - A string to print to stderr if it fails to allocate.");
    printf("%s\n\n", "* exit_q - A boolean. If true, terminates the program.");
    printf("%s\n\n", "Defined in `EVIL_MALLOC`.");
  } else
  // EVIL_MANAGED
  if(strncmp("EVIL_MANAGED", token, 12) == 0) {
    printf("%s\n\n", "module - Automatic variable cleanup.");
    printf("%s\n\n", "Defines: var, finalise");
    printf("%s\n\n", "Import by defining `EVIL_MANAGED` before including `evil.h`");
  } else
  // TODO: var, finalise
  // EVIL_LAMBDA
  if(strncmp("EVIL_LAMBDA", token, 10) == 0) {
    printf("%s\n\n", "module - Lambda support.");
    printf("%s\n\n", "Defines - `lambda`");
    printf("%s\n\n", "Import by defining `EVIL_LAMBDA` before including `evil.h`");
  } else
  if(strncmp("lambda", token, 7) == 0) {
    printf("%s\n\n", "`lambda(return type, body)`");
    printf("%s\n\n", "A lambda returns a function pointer, and takes a return type and body definition.");
    printf("%s\n\n", "Defined in `EVIL_LAMBDA`");
    printf("%s\n\n", "Best to check the examples and `evil_manual` for this one.");
  } else
  // EVIL_RANDOM
  if(strncmp("EVIL_RANDOM", token, 11) == 0) {
    printf("%s\n\n", "module - Random numbers.");
    printf("%s\n\n", "Defines: `randomseed` and `random`");
    printf("%s\n\n", "Import by defining `EVIL_RANDOM` before including `evil.h`");
  } else
  if(strncmp("randomseed", token, 10) == 0) {
    printf("%s\n\n", "`randomseed()` - Seeds the C-rand number generator.");
    printf("%s\n\n", "Defined in `EVIL_RANDOM`.");
  } else
  if(strncmp("random", token, 6) == 0) {
    printf("%s\n\n", "`random(min, max)` - Takes two `int`s, and produces an `int` within the range.");
    printf("%s\n\n", "Defined in `EVIL_RANDOM`.");
  } else
  // EVIL_HELP
  if(strncmp("EVIL_HELP", token, 9) == 0) {
    printf("%s\n\n", "module - Provides help documentation.");
    printf("%s\n\n", "Defines: `evil_manual` and `evil_explain`");
    printf("%s\n\n", "See also: `EVIL_NO_HELP_MANUAL`");
    printf("%s\n\n", "Import by defining `EVIL_HELP` before including `evil.h`.");
  } else
  if(strncmp("EVIL_NO_HELP_MANUAL", token, 18) == 0) {
    printf("%s\n\n", "If defined before `EVIL_HELP` then `evil_manual` won't be defined.");
    printf("%s\n\n", "This should help reduce the size of the eventual binary.");
  } else
  if(strncmp("evil_manual", token, 11) == 0) {
    printf("%s\n\n", "`evil_manual();`");
    printf("%s\n\n", "Prints general help to stdout.");
    printf("%s\n\n", "Defined in `EVIL_HELP`");
  } else
  if(strncmp("evil_explain", token, 12) == 0) {
    printf("%s\n\n", "`evil_explain(const char* s);`");
    printf("%s\n\n", "Prints help about a specific identifier.");
    printf("%s\n\n", "Defined in `EVIL_HELP`");
  } else
  // EVIL_COROUTINE
  if(strncmp("EVIL_COROUTINE", token, 14) == 0) {
    printf("%s\n\n", "module - Adds coroutine support.");
    printf("%s\n\n", "Defines: `coroutine`, `co_return` and `co_end`.");
    printf("%s\n\n", "Import by defining `EVIL_COROUTINE` before including `evil.h`.");
  } else
  if(strncmp("coroutine", token, 9) == 0) {
    printf("%s\n\n", "`coroutine();` - Begin a coroutine body.");
    printf("%s\n\n", "Defined in `EVIL_COROUTINE`.");
  } else
  if(strncmp("co_return", token, 9) == 0) {
    printf("%s\n\n", "`co_return(value)` - Yield a value.");
    printf("%s\n\n", "Defined in `EVIL_COROUTINE`");
  } else
  if(strncmp("co_end", token, 6) == 0) {
    printf("%s\n\n", "`co_end();` - End the coroutine body.");
    printf("%s\n\n", "Defined in `EVIL_COROUTINE`");
  } else
  // EVIL_MATH
  if(strncmp("EVIL_MATH", token, 9) == 0) {
    printf("%s\n\n", "module - Adds better math support.");
    printf("%s\n\n", "Links to `math.h`.");
    printf("%s\n\n", "Defines: `add`, `take`, `divide` and `multiply` generics.");
    printf("%s\n\n", "Import by defining `EVIL_MATH` before including `evil.h`.");
  } else
  if(strncmp("add", token, 4) == 0) {
    printf("%s\n\n", "`add(a, b)` - Translated to `( a + b )`, allowing it to act as a generic.");
    printf("%s\n\n", "Defined in `EVIL_MATH`.");
  } else
  if(strncmp("take", token, 4) == 0) {
    printf("%s\n\n", "`take(a, b)` - Translated to `( a - b )`, allowing it to act as a generic.");
    printf("%s\n\n", "Defined in `EVIL_MATH`.");
  } else
  if(strncmp("multiply", token, 4) == 0) {
    printf("%s\n\n", "`multiply(a, b)` - Translated to `( a * b )`, allowing it to act as a generic.");
    printf("%s\n\n", "Defined in `EVIL_MATH`.");
  } else
  if(strncmp("divide", token, 4) == 0) {
    printf("%s\n\n", "`divide(a, b)` - Translated to `( a / b )`, allowing it to act as a generic.");
    printf("%s\n\n", "Defined in `EVIL_MATH`.");
  } else
  // EVIL_HASH
  if(strncmp("EVIL_HASH", token, 9) == 0) {
    printf("%s\n\n", "module - Provides string hash functions.");
    printf("%s\n\n", "Defines: `jenkins64`, `jenkins32`, `fletcher64`, `fletcher32`, `fletcher16`, `adler32`.");
    printf("%s\n\n", "Import by defining `EVIL_HASH` before including `evil.h`.");
  } else
  if(strncmp("jenkins64", token, 9) == 0) {
    printf("%s\n\n", "uint64_t jenkins64(char* key, size_t length);");
    printf("%s\n\n", "Only defined if int64_t available.");
    printf("%s\n\n", "The same input should always get the same output.");
    printf("%s\n\n", "This is an implementation of a Jenkins One-At-A-Time Hash.");
    printf("%s\n\n", "This is not a cryptographic hash function.");
    printf("%s\n\n", "Defined in `EVIL_HASH`.");
  } else
  if(strncmp("jenkins32", token, 9) == 0) {
    printf("%s\n\n", "uint32_t jenkins32(char* key, size_t length);");
    printf("%s\n\n", "The same input should always get the same output.");
    printf("%s\n\n", "This is an implementation of a Jenkins One-At-A-Time Hash.");
    printf("%s\n\n", "This is not a cryptographic hash function.");
    printf("%s\n\n", "Defined in `EVIL_HASH`.");
  } else
  if(strncmp("fletcher64", token, 10) == 0) {
    printf("%s\n\n", "uint64_t fletcher64(char* key, size_t length);");
    printf("%s\n\n", "Only defined if int64_t available.");
    printf("%s\n\n", "The same input should always get the same output.");
    printf("%s\n\n", "This is an implementation of a Fletcher's Checksum.");
    printf("%s\n\n", "This is not a cryptographic hash function.");
    printf("%s\n\n", "Defined in `EVIL_HASH`.");
  } else
  if(strncmp("fletcher32", token, 10) == 0) {
    printf("%s\n\n", "uint32_t fletcher32(char* key, size_t length);");
    printf("%s\n\n", "The same input should always get the same output.");
    printf("%s\n\n", "This is an implementation of a Fletcher's Checksum.");
    printf("%s\n\n", "This is not a cryptographic hash function.");
    printf("%s\n\n", "Defined in `EVIL_HASH`.");
  } else
  if(strncmp("fletcher16", token, 10) == 0) {
    printf("%s\n\n", "uint16_t fletcher16(char* key, size_t length);");
    printf("%s\n\n", "The same input should always get the same output.");
    printf("%s\n\n", "This is an implementation of a Fletcher's Checksum.");
    printf("%s\n\n", "This is not a cryptographic hash function.");
    printf("%s\n\n", "Defined in `EVIL_HASH`.");
  } else
  if(strncmp("adler32", token, 8) == 0) {
    printf("%s\n\n", "uint32_t adler32(char* key, size_t length);");
    printf("%s\n\n", "The same input should always get the same output.");
    printf("%s\n\n", "This is an implementation of a Adler-32 checksum.");
    printf("%s\n\n", "This is not a cryptographic hash function.");
    printf("%s\n\n", "Defined in `EVIL_HASH`.");
  } else
  // EVIL_BIT
  if(strncmp("EVIL_BIT", token, 9) == 0) {
    printf("%s\n\n", "module - defines macros for worded bit operators.");
    printf("%s\n\n", "Defines: `BIT_AND`, `BIT_OR`, `BIT_XOR`, `BIT_NOT`, `BIT_RSHIFT`, `BIT_LSHIFT`.");
    printf("%s\n\n", "Import by defining `EVIL_BIT` before including `evil.h`.");
  } else
  if(strncmp("BIT_AND", token, 8) == 0) {
    printf("%s\n\n", "BIT_AND(a, b) - Return a bitwise AND.");
    printf("%s\n\n", "Defined in `EVIL_BIT`");
  } else
  if(strncmp("BIT_OR", token, 7) == 0) {
    printf("%s\n\n", "BIT_OR(a, b) - Return a bitwise OR.");
    printf("%s\n\n", "Defined in `EVIL_BIT`");
  } else
  if(strncmp("BIT_XOR", token, 8) == 0) {
    printf("%s\n\n", "BIT_XOR(a, b) - Return a bitwise XOR.");
    printf("%s\n\n", "Defined in `EVIL_BIT`");
  } else
  if(strncmp("BIT_NOT", token, 8) == 0) {
    printf("%s\n\n", "BIT_NOT(a, b) - Return a bitwise NOT.");
    printf("%s\n\n", "Defined in `EVIL_BIT`");
  } else
  if(strncmp("BIT_RSHIFT", token, 10) == 0) {
    printf("%s\n\n", "BIT_RSHIFT(a, b) - Return a bitwise right shift.");
    printf("%s\n\n", "Defined in `EVIL_BIT`");
  } else
  if(strncmp("BIT_LSHIFT", token, 10) == 0) {
    printf("%s\n\n", "BIT_LSHIFT(a, b) - Return a bitwise left shift.");
    printf("%s\n\n", "Defined in `EVIL_BIT`");
  } else
  // EVIL_LOG
  if(strncmp("EVIL_LOG", token, 8) == 0) {
    printf("%s\n\n", "module - a helpful logging module.");
    printf("%s\n\n", "Defines:");
    printf("%s\n\n", "* message_file");
    printf("%s\n\n", "* warning_file");
    printf("%s\n\n", "* critical_file");
    printf("%s\n\n", "* error_file");
    printf("%s\n\n", "* info_file");
    printf("%s\n\n", "* debug_file");
    printf("%s\n\n", "* log_file");
    printf("%s\n\n", "* message");
    printf("%s\n\n", "* warning");
    printf("%s\n\n", "* critical");
    printf("%s\n\n", "* error");
    printf("%s\n\n", "* info");
    printf("%s\n\n", "* debug");
    printf("%s\n\n", "See also: DEBUG_LOG");
  } else
  if(strncmp("DEBUG_LOG", token, 10) == 0) {
    printf("%s\n\n", "If defined, then `debug` works as expected.");
    printf("%s\n\n", "If _not_ defined, then `debug` is a no-op.");
    printf("%s\n\n", "Referenced in `EVIL_LOG`.");
  } else
  if(strncmp("debug_file", token, 10) == 0) {
    printf("%s\n\n", "`char* debug_file`");
    printf("%s\n\n", "See `debug`.");
    printf("%s\n\n", "Defined in `EVIL_LOG`");
  } else
  if(strncmp("debug", token, 6) == 0) {
    printf("%s\n\n", "void debug(char* str); - When `EVIL_LOG` defined, prints a structured message to stdout.");
    printf("%s\n\n", "If `debug_file` is not 0-length, then prints a structured message to the file found at that path.");
    printf("%s\n\n", "Defined in `EVIL_LOG`.");
  } else
  if(strncmp("info_file", token, 10) == 0) {
    printf("%s\n\n", "`char* info_file`");
    printf("%s\n\n", "See `info`.");
    printf("%s\n\n", "Defined in `EVIL_LOG`");
  } else
  if(strncmp("info", token, 6) == 0) {
    printf("%s\n\n", "void info(char* str); - Prints a structured message to stdout.");
    printf("%s\n\n", "If `info_file` is not 0-length, then prints a structured message to the file found at that path.");
    printf("%s\n\n", "Defined in `EVIL_LOG`.");
  } else
  if(strncmp("error_file", token, 10) == 0) {
    printf("%s\n\n", "`char* error_file`");
    printf("%s\n\n", "See `error`.");
    printf("%s\n\n", "Defined in `EVIL_LOG`");
  } else
  if(strncmp("error", token, 6) == 0) {
    printf("%s\n\n", "void error(char* str); - Prints a structured message to stderr.");
    printf("%s\n\n", "If `error_file` is not 0-length, then prints a structured message to the file found at that path.");
    printf("%s\n\n", "Defined in `EVIL_LOG`.");
  } else
  if(strncmp("critical_file", token, 10) == 0) {
    printf("%s\n\n", "`char* critical_file`");
    printf("%s\n\n", "See `critical`.");
    printf("%s\n\n", "Defined in `EVIL_LOG`");
  } else
  if(strncmp("critical", token, 6) == 0) {
    printf("%s\n\n", "void critical(char* str); - Prints a structured message to stderr.");
    printf("%s\n\n", "If `critical_file` is not 0-length, then prints a structured message to the file found at that path.");
    printf("%s\n\n", "Defined in `EVIL_LOG`.");
  } else
  if(strncmp("warning_file", token, 10) == 0) {
    printf("%s\n\n", "`char* warning_file`");
    printf("%s\n\n", "See `warning`.");
    printf("%s\n\n", "Defined in `EVIL_LOG`");
  } else
  if(strncmp("warning", token, 6) == 0) {
    printf("%s\n\n", "void warning(char* str); - Prints a structured message to stdout.");
    printf("%s\n\n", "If `warning_file` is not 0-length, then prints a structured message to the file found at that path.");
    printf("%s\n\n", "Defined in `EVIL_LOG`.");
  } else
  if(strncmp("message_file", token, 10) == 0) {
    printf("%s\n\n", "`char* message_file`");
    printf("%s\n\n", "See `message`.");
    printf("%s\n\n", "Defined in `EVIL_LOG`");
  } else
  if(strncmp("message", token, 6) == 0) {
    printf("%s\n\n", "void message(char* str); - Prints a structured message to stdout.");
    printf("%s\n\n", "If `message_file` is not 0-length, then prints a structured message to the file found at that path.");
    printf("%s\n\n", "Defined in `EVIL_LOG`.");
  } else

  // TODO: EVIL_CLI 54

  // TODO: EVIL_KLASS
  
  // TODO: EVIL_ENCODE

  // NOT YET IMPLEMENTED
  // TODO: EVIL_STRING
  // TODO: EVIL_PARSE_ARG
  // TODO: EVIL_LIST

  {
    printf("%s: %s\n", "No documentation found for", token);
  }
}

#endif

#ifndef EVIL_NO_INT
  // Included by default.

  #include <stdint.h>
  #include <float.h>
  #ifdef INT64_MAX
    #define Number(x) int64_t x
    #define MaxNumber INT64_MAX
  #endif
  #define Decimal(x) long double x
  #define MaxDecimal LDBL_MAX
  // TODO: itoa, convenience.
#endif
#ifndef EVIL_NO_IO
  // The IO Module.
  // Included by default. To pretend C is high-level.


  // User wants IO, give the all the IO.
  #include <stdio.h>

  // Yes, Generics. (aka type-switch). It's C11 only,
  // but who cares.
  // stdint identifiers (inttypes.h) should be catered for by the below.
  // Original display_format macro by Robert Gamble, (c) 2012
  // used with permission.
  // Expanded upon to incorporate const, volatile and const volatile types,
  // as they don't get selected for. (static does for obvious reasons).

  // Whilst volatile types can change between accesses, technically using a
  // _Generic _shouldn't_ access it, but compile to the right choice.

  #define display_format(x) _Generic((x), \
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p", \
    volatile char: "%c", \
    volatile signed char: "%hhd", \
    volatile unsigned char: "%hhu", \
    volatile signed short: "%hd", \
    volatile unsigned short: "%hu", \
    volatile signed int: "%d", \
    volatile unsigned int: "%u", \
    volatile long int: "%ld", \
    volatile unsigned long int: "%lu", \
    volatile long long int: "%lld", \
    volatile unsigned long long int: "%llu", \
    volatile float: "%f", \
    volatile double: "%f", \
    volatile long double: "%Lf", \
    volatile char *: "%s", \
    volatile void *: "%p", \
    const char: "%c", \
    const signed char: "%hhd", \
    const unsigned char: "%hhu", \
    const signed short: "%hd", \
    const unsigned short: "%hu", \
    const signed int: "%d", \
    const unsigned int: "%u", \
    const long int: "%ld", \
    const unsigned long int: "%lu", \
    const long long int: "%lld", \
    const unsigned long long int: "%llu", \
    const float: "%f", \
    const double: "%f", \
    const long double: "%Lf", \
    const char *: "%s", \
    const void *: "%p", \
    const volatile char: "%c", \
    const volatile signed char: "%hhd", \
    const volatile unsigned char: "%hhu", \
    const volatile signed short: "%hd", \
    const volatile unsigned short: "%hu", \
    const volatile signed int: "%d", \
    const volatile unsigned int: "%u", \
    const volatile long int: "%ld", \
    const volatile unsigned long int: "%lu", \
    const volatile long long int: "%lld", \
    const volatile unsigned long long int: "%llu", \
    const volatile float: "%f", \
    const volatile double: "%f", \
    const volatile long double: "%Lf", \
    const volatile char *: "%s", \
    const volatile void *: "%p", \
    default: "%d")

  // The main printing function.
  #define display(x) printf(display_format(x), x)
  #define displayf(f, x) fprintf(f, display_format(x), x)

  // Windows has a different line ending.
  #if defined(_WIN32) || defined(__WIN32) || defined(WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64) || defined(WIN64) || defined(__WIN64__) || defined(__WINNT) || defined(__WINNT__) || defined(WINNT)
    #define displayln(x) do { printf(display_format(x), x); printf("%s", "\r\n"); } while(0)
    #define displayfln(f, x) do { fprintf(f, display_format(x), x); printf("%s", "\r\n"); } while(0)
  #else
    #define displayln(x) do { printf(display_format(x), x); printf("%c", '\n'); } while(0)
    #define displayfln(f, x) do { fprintf(f, display_format(x), x); printf("%c", '\n'); } while(0)
  #endif

  // Basically a _Generic.
  #define repr_type(x) _Generic((0,x), \
    char: "char", \
    signed char: "signed char", \
    unsigned char: "unsigned char", \
    signed short: "signed short", \
    unsigned short: "unsigned short", \
    signed int: "signed int", \
    unsigned int: "unsigned int", \
    long int: "long int", \
    unsigned long int: "unsigned long int", \
    long long int: "long long int", \
    unsigned long long int: "unsigned long long int", \
    float: "float", \
    double: "double", \
    long double: "long double", \
    char *: "char pointer", \
    void *: "void pointer", \
    volatile char: "volatile char", \
    volatile signed char: "volatile signed char", \
    volatile unsigned char: "volatile unsigned char", \
    volatile signed short: "volatile signed short", \
    volatile unsigned short: "volatile unsigned short", \
    volatile signed int: "volatile signed int", \
    volatile unsigned int: "volatile unsigned int", \
    volatile long int: "volatile long int", \
    volatile unsigned long int: "volatile unsigned long int", \
    volatile long long int: "volatile long long int", \
    volatile unsigned long long int: "volatile unsigned long long int", \
    volatile float: "volatile float", \
    volatile double: "volatile double", \
    volatile long double: "volatile long double", \
    volatile char *: "volatile char pointer", \
    volatile void *: "volatile void pointer", \
    const char: "const char", \
    const signed char: "const signed char", \
    const unsigned char: "const unsigned char", \
    const signed short: "const signed short", \
    const unsigned short: "const unsigned short", \
    const signed int: "const signed int", \
    const unsigned int: "const unsigned int", \
    const long int: "const long int", \
    const unsigned long int: "const unsigned long int", \
    const long long int: "const long long int", \
    const unsigned long long int: "const unsigned long long int", \
    const float: "const float", \
    const double: "const double", \
    const long double: "const long double", \
    const char *: "const char pointer", \
    const void *: "const void pointer", \
    const volatile char: "const volatile char", \
    const volatile signed char: "const volatile signed char", \
    const volatile unsigned char: "const volatile unsigned char", \
    const volatile signed short: "const volatile signed short", \
    const volatile unsigned short: "const volatile unsigned short", \
    const volatile signed int: "const volatile signed int", \
    const volatile unsigned int: "const volatile unsigned int", \
    const volatile long int: "const volatile long int", \
    const volatile unsigned long int: "const volatile unsigned long int", \
    const volatile long long int: "const volatile long long int", \
    const volatile unsigned long long int: "const volatile unsigned long long int", \
    const volatile float: "const volatile float", \
    const volatile double: "const volatile double", \
    const volatile long double: "const volatile long double", \
    const volatile char *: "const volatile char pointer", \
    const volatile void *: "const volatile void pointer", \
    default: "Unknown")


  // endl, just a symbol that can be used to produce the normal
  // line ending.
  // endlf can take a file to print to.
  // e.g. ```display(x); display(y); endl;```
  //  ```endlf(FILE* x);```
  // Windows has a different line ending.
  #if defined(_WIN32) || defined(__WIN32) || defined(WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64) || defined(WIN64) || defined(__WIN64__) || defined(__WINNT) || defined(__WINNT__) || defined(WINNT)
    #define endl printf("%s", "\r\n")
    #define endlf(f) fprintf(f, "%s", "\r\n")
  #else
    #define endl printf("%c", '\n')
    #define endlf(f) fprintf(f, "%c", '\n')
  #endif

#endif

#ifdef EVIL_LIST

  // TODO: gc-backed linked list library
  #error "Not Yet Implemented"

#endif
#ifdef EVIL_LOG

  // File definitions for the user to control.
  char* message_file = "";
  char* warning_file = "";
  char* critical_file = "";
  char* error_file = "";
  char* info_file = "";
  char* debug_file = "";
  char* log_file = "";

  // Libraries we need
  #include <stdio.h>
  #include <time.h>
  #include <assert.h>

  void message(char* str) {
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if(log_file[0] != '\0') {
      // Opening in append mode is Not ANSI C, but ISO C
      FILE* logFile = fopen(log_file, "a");
      assert(logFile != NULL);
      fprintf(logFile, "%s\n%u %s%s\n%s\n", "---MESSAGE---", (unsigned)time(NULL), asctime(timeinfo), str, "---END MESSAGE---");
      fclose(logFile);
    }
    if(message_file[0] != '\0') {
      // Opening in append mode is Not ANSI C, but ISO C
      FILE* messageFile = fopen(message_file, "a");
      assert(messageFile != NULL);
      fprintf(messageFile, "%s\n%u %s%s\n%s\n", "---MESSAGE---", (unsigned)time(NULL), asctime(timeinfo), str, "---END MESSAGE---");
      fclose(messageFile);
    }
    //NOTE: asctime has a newline.
    printf("%s\n%u %s%s\n%s\n", "---MESSAGE---", (unsigned)time(NULL), asctime(timeinfo), str, "---END MESSAGE---");
  }

  void warning(char* str) {
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if(log_file[0] != '\0') {
    	FILE* logFile = fopen(log_file, "a");
    	assert(logFile != NULL);
    	fprintf(logFile, "%s\n%u %s%s\n%s\n", "---WARNING---", (unsigned)time(NULL), asctime(timeinfo), str, "---END WARNING---");
    	fclose(logFile);
    }

    if(warning_file[0] != '\0') {
      //NOTE: asctime has a newline.
      FILE* warningFile = fopen(warning_file, "a");
      assert(warningFile);
      fprintf(warningFile, "\x1b[30m%s\n%u %s%s\n%s\n\x1b[0m", "---WARNING---", (unsigned)time(NULL), asctime(timeinfo), str, "---END WARNING---");
      fclose(warningFile);
    }  	
    printf("\x1b[30m%s\n%u %s%s\n%s\n\x1b[0m", "---WARNING---", (unsigned)time(NULL), asctime(timeinfo), str, "---END WARNING---");
  }

  void critical(char* str) {
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if(log_file[0] != '\0') {
    	FILE* logFile = fopen(log_file, "a");
    	assert(logFile != NULL);
    	fprintf(logFile, "%s\n%u %s%s\n%s\n", "---CRITICAL---", (unsigned)time(NULL), asctime(timeinfo), str, "---END CRITICAL---");
    	fclose(logFile);
    }

    if(critical_file[0] != '\0') {
      //NOTE: asctime has a newline.
      FILE* criticalFile = fopen(critical_file, "a");
      assert(criticalFile);
      fprintf(criticalFile, "%s\n%u %s%s\n%s\n", "---CRITICAL---", (unsigned)time(NULL), asctime(timeinfo), str, "---END CRITICAL---");
      fclose(criticalFile);
    }
    fprintf(stderr, "\x1b[5m\x1b[33m%s\n%u %s%s\n%s\n\x1b[0m", "---CRITICAL---", (unsigned)time(NULL), asctime(timeinfo), str, "---END CRITICAL---");
  }

  void error(char* str) {
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if(log_file[0] != '\0') {
    	FILE* logFile = fopen(log_file, "a");
    	assert(logFile != NULL);
    	fprintf(logFile, "%s\n%u %s%s\n%s\n", "---ERROR---", (unsigned)time(NULL), asctime(timeinfo), str, "---END ERROR---");
    	fclose(logFile);
    }

    if(error_file[0] != '\0') {
      //NOTE: asctime has a newline.
      FILE* errorFile = fopen(error_file, "a");
      assert(errorFile);
      fprintf(errorFile, "%s\n%u %s%s\n%s\n", "---ERROR---", (unsigned)time(NULL), asctime(timeinfo), str, "---END ERROR---");
      fclose(errorFile);
    }
    fprintf(stderr, "\x1b[35m%s\n%u %s%s\n%s\n\x1b[0m", "---ERROR---", (unsigned)time(NULL), asctime(timeinfo), str, "---END ERROR---");
  }

  void info(char* str) {
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if(log_file[0] != '\0') {
    	FILE* logFile = fopen(log_file, "a");
    	assert(logFile != NULL);
    	fprintf(logFile, "%s\n%u %s%s\n%s\n", "---INFO---", (unsigned)time(NULL), asctime(timeinfo), str, "---END INFO---");
    	fclose(logFile);
    }

    if(info_file[0] != '\0') {
      //NOTE: asctime has a newline.
      FILE* infoFile = fopen(info_file, "a");
      assert(infoFile);
      fprintf(infoFile, "%s\n%u %s%s\n%s\n", "---INFO---", (unsigned)time(NULL), asctime(timeinfo), str, "---END INFO---");
      fclose(infoFile);
    }
    printf("%s\n%u %s%s\n%s\n", "---INFO---", (unsigned)time(NULL), asctime(timeinfo), str, "---END INFO---");
  }

  #ifdef DEBUG_LOG
    void debug(char* str) {
	    time_t now;
	    struct tm* timeinfo;
	    time(&now);
	    timeinfo = localtime(&now);

	    if(log_file[0] != '\0') {
	    	FILE* logFile = fopen(log_file, "a");
	    	assert(logFile != NULL);
	    	fprintf(logFile, "%s\n%u %s%s\n%s\n", "---DEBUG---", (unsigned)time(NULL), asctime(timeinfo), str, "---END DEBUG---");
	    	fclose(logFile);
	    }

	    if(debug_file[0] != '\0') {
	      //NOTE: asctime has a newline.
	      FILE* debugFile = fopen(debug_file, "a");
	      assert(debugFile);
	      fprintf(debugFile, "%s\n%u %s%s\n%s\n", "---DEBUG---", (unsigned)time(NULL), asctime(timeinfo), str, "---END DEBUG---");
	      fclose(debugFile);
	    }
	    printf("%s\n%u %s%s\n%s\n", "---DEBUG---", (unsigned)time(NULL), asctime(timeinfo), str, "---END DEBUG---");
	  }
  #else
    void debug(char* str) {return; }
  #endif
#endif


#ifndef EVIL_NO_MAIN
  // Included by default
  #define Main int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv
#endif
#ifdef EVIL_MALLOC
  // Excluded by default: stdlib is a big dependency.

  // Provides a "safer" malloc pattern

  #include <stdlib.h>
  #include <stdio.h>
  #define checked_malloc(object, object_type, buffer, fail_msg, exit_q) object_type object = malloc(buffer); if(!object){fprintf(stderr, "%s\n", fail_msg); if(exit_q){exit(EXIT_FAILURE);}}
#endif

#ifdef EVIL_MANAGED

#define finalise(_func) __attribute__ ((__cleanup__(_func)))

#define var(type, finaliser, name) type name __attribute__ ((__cleanup__(finaliser)))

#endif

#ifdef EVIL_MATH

  // This library does the heavy lifting.
  #include <math.h>
  // TODO: Make math.h functions use _Generic to
  // handle multiple types.
  #define add(_a, _b) (_a + _b)
  #define take(_a, _b) (_a - _b)
  #define multiply(_a, _b) (_a * _b)
  #define divide(_a, _b) (_a / _b)
#endif
#ifdef EVIL_PARSE_ARG

  #error "Not Yet Implemented"

  /*

  Needs to handle:

  Single letter flags:

  -a -b
  -ab

  Key word flags:

  --word=x
  --word x

  Setting boolean flags:
  (absence implies false)

  --bool-flag true
  --bool-flag false
  ---bool-flag


  */

#endif

#ifndef EVIL_NO_PROC
  // Included by default

  #define declare(_name, _ret, ...) _ret _name(__VA_ARGS__)
  #define proc(_name, _ret, ...) _ret _name(__VA_ARGS__){
#endif
#ifdef EVIL_RANDOM
  #include <stdlib.h>
  #include <time.h>

  #ifndef EVIL_NO_WARN
	#warning "randomseed and random(min, max) depend on C's rand. They are not cryptographically safe. They are not even good pseudorandom generators."
  #endif

  // Crappy C-standard stuff.
  #define randomseed() srand((unsigned int)time(NULL))
  #define random(min, max) (rand() % (max + 1 - min)) + min
  // TODO: Mersenne Twister (see http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/CODES/mt19937ar.c)
#endif
#ifndef EVIL_NO_SPECIFIER
  // Included by default.

  #define constant(_type, _name, _value) const _type _name = _value

  // Static vars are usually referred to as storage-class
  // specifiers in the C standard.
  #define storage(_type, _name, _value) static _type _name = _value
#endif
#ifdef EVIL_STRING

  // TODO: gc-backed cord lib
  #error "Not Yet Implemented"

  // Should also provide wrapper functions for any other modules
  // that use a C String.

#endif

#ifndef EVIL_NO_STRUCT
  // Imported by default

  #define BitField(_name, _type, _width) _type _name : _width
  #define Struct(_name) struct _name {
  #define Union(_name) union __name {
  #define Typedef typedef
#endif

// TODO: OGW Specifics

#endif
