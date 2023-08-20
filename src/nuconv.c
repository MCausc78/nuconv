#include <nuconv.h>
#include <stdbool.h>

#ifndef NUCONV_NO_STDLIB
#include <ctype.h>
#include <string.h>
#endif

#define NUCONV_MIN(type, fn) \
type fn(type x, type y)      \
{                            \
  return x < y ? x : y;      \
}

#define NUCONV_MAX(type, fn) \
type fn(type x, type y)      \
{                            \
  return x > y ? x : y;      \
}

void* nuconv_memchr(const void* x, int y, size_t z)
{
#ifndef NUCONV_NO_STDLIB
  return memchr(x, y, z);
#else
  const uint8_t* a = (const uint8_t*)x;
  for (; z != 0; --z) {
    if (*a == (unsigned char)y) {
      return a;
    }
    ++a;
  }
  return NULL;
#endif
}

int nuconv_memcmp(const char* x, const char* y, size_t z)
{
#ifndef NUCONV_NO_STDLIB
  return memcmp(x, y, z);
#else
  for (; z != 0 && *x == *y; ++x, ++y, --z);
  return ((int)*(uint8_t*)x) - ((int)*(uint8_t*)y);
#endif
}

void* nuconv_memcpy(void* dst, const void* src, size_t z)
{
#ifndef NUCONV_NO_STDLIB
  return memcpy(dst, src, z);
#else
  uint8_t* d = (uint8_t*)dst;
  const uint8_t* s = (const uint8_t*)src;
  for (; z != 0; --z) {
    *d++ = *s++;
  }
  return d;
#endif
}

void* nuconv_memmem(const void* haystack, size_t haystacklen,
                    const void* needle, size_t needlelen)
{
  if (needlelen > haystacklen || haystacklen < needlelen) {
    return NULL;
  }
  size_t i, j;
  for (i = 0, j = haystacklen-needlelen; i < j; ++i) {
    if (nuconv_memcmp((const char*)(((uint8_t*)haystack) + i), needle, needlelen) == 0) {
      return ((uint8_t*)haystack) + i;
    }
  }
  return NULL;
}

void* nuconv_memmove(void* dst, const void* src, size_t z)
{
#ifndef NUCONV_NO_STDLIB
  return memmove(dst, src, z);
#else
  uint8_t* d = ((uint8_t*)dst)+z;
  const uint8_t* s = ((const uint8_t*)src)+z;
  for (; z != 0; --z) {
    *d-- = *s--;
  }
  return d;
#endif
}

size_t nuconv_memrev(char* buf, size_t n)
{
  size_t i;
  for (i = 0; i < n/2; ++i) {
    const char x = buf[i];
    buf[i] = buf[n - i - 1];
    buf[n - i - 1] = x;
  }
  return i;
}

void* nuconv_memset(char* x, int y, size_t z)
{
#ifndef NUCONV_NO_STDLIB
  return memset(x, y, z);
#else
  for (; z != 0; --z)
    *x++ = (unsigned char)y;
  return x;
#endif
}

char* nuconv_strchr(const char* str, int ch)
{
#ifndef NUCONV_NO_STDLIB
  return strchr(str, ch);
#else
  if (ch == '\0') {
    return nuconv_strlen(str);
  }
  for (;;) {
    if (*str == ch) {
      return str;
    }
    if (*str == '\0') {
      break;
    }
    ++str;
  }
  return NULL;
#endif
}

int nuconv_strcmp(const char* x, const char* y)
{
#ifndef NUCONV_NO_STDLIB
  return strcmp(x, y);
#else
  return nuconv_memcmp(x, y, nuconv_zmax(nuconv_strlen(x), nuconv_strlen(y)));
#endif
}

char* nuconv_strcpy(char* dst, const char* src)
{
#ifndef NUCONV_NO_STDLIB
  return strcpy(dst, src);
#else
  for (; *src != '\0'; ++src) {
    *dst++ = *src;
  }
  return dst;
#endif
}

size_t nuconv_strlen(const char* str)
{
#ifndef NUCONV_NO_STDLIB
  return strlen(str);
#else
  size_t n = 0;
  while (*str++) {
    ++n;
  }
  return n;
#endif
}

char* nuconv_strmove(char* dst, const char* src)
{
  return nuconv_memmove(dst, src, nuconv_strlen(src));
}

size_t nuconv_strrev(char* str)
{
  return nuconv_memrev(str, nuconv_strlen(str));
}

char* nuconv_strset(char* x, int y)
{
  return nuconv_memset(x, y, nuconv_strlen(x));
}

char* nuconv_strstr(const char* haystack,
                    const char* needle)
{
  return nuconv_memmem(
    haystack, nuconv_strlen(haystack),
    needle, nuconv_strlen(needle)
  );
}

uint16_t nuconv_ctype[] = {
  NUCONV_CNTRL,                                                                             /* 0x00 NUL   */
  NUCONV_CNTRL,                                                                             /* 0x01 SOH   */
  NUCONV_CNTRL,                                                                             /* 0x02 STX   */
  NUCONV_CNTRL,                                                                             /* 0x03 ETX   */
  NUCONV_CNTRL,                                                                             /* 0x04 EOT   */
  NUCONV_CNTRL,                                                                             /* 0x05 ENQ   */
  NUCONV_CNTRL,                                                                             /* 0x06 ACK   */
  NUCONV_CNTRL,                                                                             /* 0x07 BEL   */
  NUCONV_CNTRL,                                                                             /* 0x08 BS    */
  NUCONV_CNTRL | NUCONV_SPACE | NUCONV_BLANK,                                               /* 0x09 TAB   */
  NUCONV_CNTRL | NUCONV_SPACE,                                                              /* 0x0A LF    */
  NUCONV_CNTRL | NUCONV_SPACE,                                                              /* 0x0B VT    */
  NUCONV_CNTRL | NUCONV_SPACE,                                                              /* 0x0C FF    */
  NUCONV_CNTRL | NUCONV_SPACE,                                                              /* 0x0D CR    */
  NUCONV_CNTRL,                                                                             /* 0x0E SO    */
  NUCONV_CNTRL,                                                                             /* 0x0F SI    */
  NUCONV_CNTRL,                                                                             /* 0x10 DLE   */
  NUCONV_CNTRL,                                                                             /* 0x11 DC1   */
  NUCONV_CNTRL,                                                                             /* 0x12 DC2   */
  NUCONV_CNTRL,                                                                             /* 0x13 DC3   */
  NUCONV_CNTRL,                                                                             /* 0x14 DC4   */
  NUCONV_CNTRL,                                                                             /* 0x15 NAK   */
  NUCONV_CNTRL,                                                                             /* 0x16 SYN   */
  NUCONV_CNTRL,                                                                             /* 0x17 ETB   */
  NUCONV_CNTRL,                                                                             /* 0x18 CAN   */
  NUCONV_CNTRL,                                                                             /* 0x19 EM    */
  NUCONV_CNTRL,                                                                             /* 0x1A SUB   */
  NUCONV_CNTRL,                                                                             /* 0x1B ESC   */
  NUCONV_CNTRL,                                                                             /* 0x1C FS    */
  NUCONV_CNTRL,                                                                             /* 0x1D GS    */
  NUCONV_CNTRL,                                                                             /* 0x1E RS    */
  NUCONV_CNTRL,                                                                             /* 0x1F US    */
  NUCONV_PRINT | NUCONV_SPACE | NUCONV_BLANK,                                               /* 0x20 Space */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x21 '!'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x22 '"'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x23 '#'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x24 '$'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x25 '%'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x26 '&'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x27 '\''  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x28 '('   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x29 ')'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x2A '*'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x2B '+'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x2C ','   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x2D '-'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x2E '.'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x2F '/'   */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x30 '0'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x31 '1'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x32 '2'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x33 '3'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x34 '4'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x35 '5'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x36 '6'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x37 '7'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x38 '8'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_DIGIT | NUCONV_XDIGIT,                /* 0x39 '9'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x3A ':'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x3B ';'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x3C '<'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x3D '='  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x3E '>'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x3F '?'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x40 '@'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER | NUCONV_XDIGIT, /* 0x41 'A'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER | NUCONV_XDIGIT, /* 0x42 'B'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER | NUCONV_XDIGIT, /* 0x43 'C'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER | NUCONV_XDIGIT, /* 0x44 'D'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER | NUCONV_XDIGIT, /* 0x45 'E'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER | NUCONV_XDIGIT, /* 0x46 'F'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x47 'G'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x48 'H'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x49 'I'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x4A 'J'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x4B 'K'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x4C 'L'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x4D 'M'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x4E 'N'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x4F 'O'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x50 'P'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x51 'Q'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x52 'R'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x53 'S'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x54 'T'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x55 'U'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x56 'V'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x57 'W'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x58 'X'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x59 'Y'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_UPPER,                 /* 0x5A 'Z'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x5B '['  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x5C '\'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x5D ']'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x5E '^'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x5F '_'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x60 '`'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER | NUCONV_XDIGIT, /* 0x61 'a'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER | NUCONV_XDIGIT, /* 0x62 'b'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER | NUCONV_XDIGIT, /* 0x63 'c'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER | NUCONV_XDIGIT, /* 0x64 'd'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER | NUCONV_XDIGIT, /* 0x65 'e'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER | NUCONV_XDIGIT, /* 0x66 'f'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x67 'g'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x68 'h'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x69 'i'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x6A 'j'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x6B 'k'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x6C 'l'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x6D 'm'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x6E 'n'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x6F 'o'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x70 'p'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x71 'q'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x72 'r'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x73 's'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x74 't'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x75 'u'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x76 'v'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x77 'w'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x78 'x'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x79 'y'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_ALNUM | NUCONV_ALPHA | NUCONV_LOWER,                 /* 0x7A 'z'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x7B '{'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x7C '|'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x7D '}'  */
  NUCONV_PRINT | NUCONV_GRAPH | NUCONV_PUNCT,                                               /* 0x7E '~'  */
  NUCONV_CNTRL,                                                                             /* 0x7F DEL  */
  NUCONV_NONE,                                                                              /* 0x80 */
  NUCONV_NONE,                                                                              /* 0x8A */
  NUCONV_NONE,                                                                              /* 0x8B */
  NUCONV_NONE,                                                                              /* 0x8C */
  NUCONV_NONE,                                                                              /* 0x8D */
  NUCONV_NONE,                                                                              /* 0x8E */
  NUCONV_NONE,                                                                              /* 0x8F */
  NUCONV_NONE,                                                                              /* 0x90 */
  NUCONV_NONE,                                                                              /* 0x91 */
  NUCONV_NONE,                                                                              /* 0x92 */
  NUCONV_NONE,                                                                              /* 0x93 */
  NUCONV_NONE,                                                                              /* 0x94 */
  NUCONV_NONE,                                                                              /* 0x95 */
  NUCONV_NONE,                                                                              /* 0x96 */
  NUCONV_NONE,                                                                              /* 0x97 */
  NUCONV_NONE,                                                                              /* 0x98 */
  NUCONV_NONE,                                                                              /* 0x99 */
  NUCONV_NONE,                                                                              /* 0x9A */
  NUCONV_NONE,                                                                              /* 0x9B */
  NUCONV_NONE,                                                                              /* 0x9C */
  NUCONV_NONE,                                                                              /* 0x9D */
  NUCONV_NONE,                                                                              /* 0x9E */
  NUCONV_NONE,                                                                              /* 0x9F */
  NUCONV_NONE,                                                                              /* 0xA0 */
  NUCONV_NONE,                                                                              /* 0xA1 */
  NUCONV_NONE,                                                                              /* 0xA2 */
  NUCONV_NONE,                                                                              /* 0xA3 */
  NUCONV_NONE,                                                                              /* 0xA4 */
  NUCONV_NONE,                                                                              /* 0xA5 */
  NUCONV_NONE,                                                                              /* 0xA6 */
  NUCONV_NONE,                                                                              /* 0xA7 */
  NUCONV_NONE,                                                                              /* 0xA8 */
  NUCONV_NONE,                                                                              /* 0xA9 */
  NUCONV_NONE,                                                                              /* 0xAA */
  NUCONV_NONE,                                                                              /* 0xAB */
  NUCONV_NONE,                                                                              /* 0xAC */
  NUCONV_NONE,                                                                              /* 0xAD */
  NUCONV_NONE,                                                                              /* 0xAE */
  NUCONV_NONE,                                                                              /* 0xAF */
  NUCONV_NONE,                                                                              /* 0xB0 */
  NUCONV_NONE,                                                                              /* 0xB1 */
  NUCONV_NONE,                                                                              /* 0xB2 */
  NUCONV_NONE,                                                                              /* 0xB3 */
  NUCONV_NONE,                                                                              /* 0xB4 */
  NUCONV_NONE,                                                                              /* 0xB5 */
  NUCONV_NONE,                                                                              /* 0xB6 */
  NUCONV_NONE,                                                                              /* 0xB7 */
  NUCONV_NONE,                                                                              /* 0xB8 */
  NUCONV_NONE,                                                                              /* 0xB9 */
  NUCONV_NONE,                                                                              /* 0xBA */
  NUCONV_NONE,                                                                              /* 0xBB */
  NUCONV_NONE,                                                                              /* 0xBC */
  NUCONV_NONE,                                                                              /* 0xBD */
  NUCONV_NONE,                                                                              /* 0xBE */
  NUCONV_NONE,                                                                              /* 0xBF */
  NUCONV_NONE,                                                                              /* 0xC0 */
  NUCONV_NONE,                                                                              /* 0xC1 */
  NUCONV_NONE,                                                                              /* 0xC2 */
  NUCONV_NONE,                                                                              /* 0xC3 */
  NUCONV_NONE,                                                                              /* 0xC4 */
  NUCONV_NONE,                                                                              /* 0xC5 */
  NUCONV_NONE,                                                                              /* 0xC6 */
  NUCONV_NONE,                                                                              /* 0xC7 */
  NUCONV_NONE,                                                                              /* 0xC8 */
  NUCONV_NONE,                                                                              /* 0xC9 */
  NUCONV_NONE,                                                                              /* 0xCA */
  NUCONV_NONE,                                                                              /* 0xCB */
  NUCONV_NONE,                                                                              /* 0xCC */
  NUCONV_NONE,                                                                              /* 0xCD */
  NUCONV_NONE,                                                                              /* 0xCE */
  NUCONV_NONE,                                                                              /* 0xCF */
  NUCONV_NONE,                                                                              /* 0xD0 */
  NUCONV_NONE,                                                                              /* 0xD1 */
  NUCONV_NONE,                                                                              /* 0xD2 */
  NUCONV_NONE,                                                                              /* 0xD3 */
  NUCONV_NONE,                                                                              /* 0xD4 */
  NUCONV_NONE,                                                                              /* 0xD5 */
  NUCONV_NONE,                                                                              /* 0xD6 */
  NUCONV_NONE,                                                                              /* 0xD7 */
  NUCONV_NONE,                                                                              /* 0xD8 */
  NUCONV_NONE,                                                                              /* 0xD9 */
  NUCONV_NONE,                                                                              /* 0xDA */
  NUCONV_NONE,                                                                              /* 0xDB */
  NUCONV_NONE,                                                                              /* 0xDC */
  NUCONV_NONE,                                                                              /* 0xDD */
  NUCONV_NONE,                                                                              /* 0xDE */
  NUCONV_NONE,                                                                              /* 0xDF */
  NUCONV_NONE,                                                                              /* 0xE0 */
  NUCONV_NONE,                                                                              /* 0xE1 */
  NUCONV_NONE,                                                                              /* 0xE2 */
  NUCONV_NONE,                                                                              /* 0xE3 */
  NUCONV_NONE,                                                                              /* 0xE4 */
  NUCONV_NONE,                                                                              /* 0xE5 */
  NUCONV_NONE,                                                                              /* 0xE6 */
  NUCONV_NONE,                                                                              /* 0xE7 */
  NUCONV_NONE,                                                                              /* 0xE8 */
  NUCONV_NONE,                                                                              /* 0xE9 */
  NUCONV_NONE,                                                                              /* 0xEA */
  NUCONV_NONE,                                                                              /* 0xEB */
  NUCONV_NONE,                                                                              /* 0xEC */
  NUCONV_NONE,                                                                              /* 0xED */
  NUCONV_NONE,                                                                              /* 0xEE */
  NUCONV_NONE,                                                                              /* 0xEF */
  NUCONV_NONE,                                                                              /* 0xF0 */
  NUCONV_NONE,                                                                              /* 0xF1 */
  NUCONV_NONE,                                                                              /* 0xF2 */
  NUCONV_NONE,                                                                              /* 0xF3 */
  NUCONV_NONE,                                                                              /* 0xF4 */
  NUCONV_NONE,                                                                              /* 0xF5 */
  NUCONV_NONE,                                                                              /* 0xF6 */
  NUCONV_NONE,                                                                              /* 0xF7 */
  NUCONV_NONE,                                                                              /* 0xF8 */
  NUCONV_NONE,                                                                              /* 0xF9 */
  NUCONV_NONE,                                                                              /* 0xFA */
  NUCONV_NONE,                                                                              /* 0xFB */
  NUCONV_NONE,                                                                              /* 0xFC */
  NUCONV_NONE,                                                                              /* 0xFD */
  NUCONV_NONE,                                                                              /* 0xFE */
  NUCONV_NONE                                                                               /* 0xFF */
};

int nuconv_isalnum(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isalnum(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_ALNUM) != 0;
#endif
}

int nuconv_isalpha(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isalpha(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_ALPHA) != 0;
#endif
}

int nuconv_islower(int c)
{
#ifndef NUCONV_NO_STDLIB
  return islower(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_LOWER) != 0;
#endif
}

int nuconv_isupper(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isupper(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_UPPER) != 0;
#endif
}

int nuconv_isdigit(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isdigit(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_DIGIT) != 0;
#endif
}

int nuconv_isxdigit(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isxdigit(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_XDIGIT) != 0;
#endif
}

int nuconv_iscntrl(int c)
{
#ifndef NUCONV_NO_STDLIB
  return iscntrl(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_CNTRL) != 0;
#endif
}

int nuconv_isgraph(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isgraph(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_GRAPH) != 0;
#endif
}

int nuconv_isspace(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isspace(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_SPACE) != 0;
#endif
}

int nuconv_isblank(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isblank(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_BLANK) != 0;
#endif
}

int nuconv_isprint(int c)
{
#ifndef NUCONV_NO_STDLIB
  return isprint(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_PRINT) != 0;
#endif
}

int nuconv_ispunct(int c)
{
#ifndef NUCONV_NO_STDLIB
  return ispunct(c);
#else
  return (nuconv_ctype[(unsigned char)c] & NUCONV_PUNCT) != 0;
#endif
}


int nuconv_tolower(int c)
{
#ifndef NUCONV_NO_STDLIB
  return tolower(c);
#else
  return nuconv_isupper(c)
    ? c - 'a' + 'A'
    : c;
#endif
}

int nuconv_toupper(int c)
{
#ifndef NUCONV_NO_STDLIB
  return toupper(c);
#else
  return nuconv_islower(c)
    ? c - 'A' + 'a'
    : c;
#endif
}

const char* const nuconv_alphabetu = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* const nuconv_alphabetl = "0123456789abcdefghijklmnopqrstuvwxyz";

int nuconv_do_atoi(int64_t* dst, const char* target, unsigned radix, int flags)
{
  int64_t res = 0;
  bool looped = false;
  bool sign = false;
  bool succ = false;
  bool overflow = false;
  if (radix < 2 || radix > 36) {
    return -NUCONV_ERROR_RADIX;
  }
  const char* ptr = target;
  char c;
  while ((c = *ptr++) != 0) {
    if (c == '-') {
      sign = true;
      continue;
    }
    if (nuconv_strchr("\t\n\v\f\r +_", c) != NULL) {
      continue;
    }
    looped = true;
    char* x = nuconv_strchr(nuconv_alphabetl, nuconv_toupper(c));
    if (x == NULL) {
      break;
    }
    size_t pos = x - nuconv_alphabetl;
    if (pos >= radix) {
      break;
    }
    succ = true;
    overflow = __builtin_mul_overflow(res, radix, &res) || overflow;
    overflow = __builtin_add_overflow(res, pos, &res) || overflow;
  }
  if (sign) {
    res = -res;
  }
  *dst = res;
  return !succ
    ? looped
      ? -NUCONV_ERROR_INVALID_CHARACTER
      : -NUCONV_ERROR_EMPTY
    : overflow
      ? NUCONV_WARN_OVERFLOW
      : NUCONV_OK;
}

int nuconv_do_atou(uint64_t* dst, const char* target, unsigned radix, int flags)
{
  uint64_t res  = 0;
  bool looped   = false;
  bool succ     = false;
  bool overflow = false;
  if (radix < 2 || radix > 36) {
    return -NUCONV_ERROR_RADIX;
  }
  const char* ptr = target;
  char c;
  while ((c = *ptr++) != 0) {
    if (nuconv_strchr("\t\n\v\f\r +_", c) != NULL) {
      continue;
    }
    looped = true;
    char* x = nuconv_strchr(nuconv_alphabetl, nuconv_toupper(c));
    if (x == NULL) {
      break;
    }
    size_t pos = x - nuconv_alphabetl;
    if (pos >= radix) {
      break;
    }
    succ = true;
    overflow = __builtin_mul_overflow(res, radix, &res) || overflow;
    overflow = __builtin_add_overflow(res, pos, &res) || overflow;
  }
  *dst = res;
  return !succ
    ? looped
      ? -NUCONV_ERROR_INVALID_CHARACTER
      : -NUCONV_ERROR_EMPTY
    : overflow
      ? NUCONV_WARN_OVERFLOW
      : NUCONV_OK;
}

int nuconv_do_itoa(int64_t target, char* buf, unsigned radix, int flags)
{
  if (radix < 2 || radix > 36) {
    return -NUCONV_ERROR_RADIX;
  }
  bool sign = false;
  if (target < 0) {
    sign = true;
    target = -target;
  }
  char* low = buf;
  if ((flags & NUCONV_FLAG_UPPERCASE) != 0)
    do
      *buf++ = nuconv_alphabetu[target % radix];
    while (target /= radix);
  else
    do
      *buf++ = nuconv_alphabetl[target % radix];
    while (target /= radix);
  if ((flags & NUCONV_FLAG_ABS) == 0) && sign) {
    *buf++ = '-';
  }
  *buf++ = '\0';
  nuconv_strrev(low);
  return NUCONV_OK;
}

int nuconv_do_utoa(uint64_t target, char* buf, unsigned radix, int flags)
{
  if (radix < 2 || radix > 36) {
    return -NUCONV_ERROR_RADIX;
  }
  char* low = buf;
  if ((flags & NUCONV_FLAG_UPPERCASE) != 0)
    do
      *buf++ = nuconv_alphabetu[target % radix];
    while (target /= radix);
  else
    do
      *buf++ = nuconv_alphabetl[target % radix];
  *buf++ = '\0';
  nuconv_strrev(low);
  return NUCONV_OK;
}

int nuconv_atoi(const char* buf)
{
  int64_t res;
  return nuconv_do_atoi(&res, buf, 10) < 0
    ? 0
    : (int)res;
}

unsigned int nuconv_atou(const char* buf)
{
  uint64_t res;
  return nuconv_do_atou(&res, buf, 10) < 0
    ? 0
    : (unsigned int)res;
}

char* nuconv_itoa(int n, char* buf, int radix)
{
  nuconv_do_itoa((int64_t) n, buf, (unsigned) radix);
  return buf + nuconv_strlen(buf);
}

char* nuconv_utoa(unsigned int n, char* buf, int radix)
{
  nuconv_do_utoa((uint64_t) n, buf, (unsigned) radix);
  return buf + nuconv_strlen(buf);
}

NUCONV_MIN(size_t,             nuconv_zmin)
NUCONV_MIN(char,               nuconv_cmin)
NUCONV_MIN(signed char,        nuconv_scmin)
NUCONV_MIN(unsigned char,      nuconv_ucmin)
NUCONV_MIN(short,              nuconv_smin)
NUCONV_MIN(signed short,       nuconv_ssmin)
NUCONV_MIN(unsigned short,     nuconv_usmin)
NUCONV_MIN(int,                nuconv_imin)
NUCONV_MIN(signed int,         nuconv_simin)
NUCONV_MIN(unsigned int,       nuconv_uimin)
NUCONV_MIN(long,               nuconv_lmin)
NUCONV_MIN(signed long,        nuconv_slmin)
NUCONV_MIN(unsigned long,      nuconv_ulmin)
NUCONV_MIN(long long,          nuconv_llmin)
NUCONV_MIN(signed long long,   nuconv_sllmin)
NUCONV_MIN(unsigned long long, nuconv_ullmin)

NUCONV_MAX(size_t,             nuconv_zmax)
NUCONV_MAX(char,               nuconv_cmax)
NUCONV_MAX(signed char,        nuconv_scmax)
NUCONV_MAX(unsigned char,      nuconv_ucmax)
NUCONV_MAX(short,              nuconv_smax)
NUCONV_MAX(signed short,       nuconv_ssmax)
NUCONV_MAX(unsigned short,     nuconv_usmax)
NUCONV_MAX(int,                nuconv_imax)
NUCONV_MAX(signed int,         nuconv_simax)
NUCONV_MAX(unsigned int,       nuconv_uimax)
NUCONV_MAX(long,               nuconv_lmax)
NUCONV_MAX(signed long,        nuconv_slmax)
NUCONV_MAX(unsigned long,      nuconv_ulmax)
NUCONV_MAX(long long,          nuconv_llmax)
NUCONV_MAX(signed long long,   nuconv_sllmax)
NUCONV_MAX(unsigned long long, nuconv_ullmax)
