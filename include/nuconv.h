#ifndef NUCONV_H
#define NUCONV_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#define NUCONV_NONE   (0x0000)
#define NUCONV_ALNUM  (0x0001)
#define NUCONV_ALPHA  (0x0002)
#define NUCONV_LOWER  (0x0004)
#define NUCONV_UPPER  (0x0008)
#define NUCONV_DIGIT  (0x0010)
#define NUCONV_XDIGIT (0x0020)
#define NUCONV_CNTRL  (0x0040)
#define NUCONV_GRAPH  (0x0080)
#define NUCONV_SPACE  (0x0100)
#define NUCONV_BLANK  (0x0200)
#define NUCONV_PRINT  (0x0400)
#define NUCONV_PUNCT  (0x0800)

#define NUCONV_ERROR_INVALID_CHARACTER (0x00000002)
#define NUCONV_ERROR_EMPTY             (0x00000001)
#define NUCONV_ERROR_RADIX             (0x00000004)
#define NUCONV_WARN_OVERFLOW           (0x00000001)
#define NUCONV_OK                      (0x00000000)

#define NUCONV_FLAG_UPPERCASE (0x00000001)
#define NUCONV_FLAG_ABS       (0x00000002)

void* nuconv_memchr(const void* x, int y, size_t z);
int nuconv_memcmp(const char* x, const char* y, size_t z);
void* nuconv_memcpy(void* dst, const void* src, size_t z);
void* nuconv_memmem(const void* haystack, size_t haystacklen,
                    const void* needle, size_t needlelen);
void* nuconv_memmove(void* dst, const void* src, size_t z);
size_t nuconv_memrev(char* buf, size_t n);
void* nuconv_memset(char* x, int y, size_t z);

char* nuconv_strchr(const char* str, int ch);
int nuconv_strcmp(const char* x, const char* y);
char* nuconv_strcpy(char* dst, const char* src);
size_t nuconv_strlen(const char* str);
size_t nuconv_strrev(char* str);
char* nuconv_strset(char* x, int y);
char* nuconv_strstr(const char* haystack,
                    const char* needle);

extern uint16_t nuconv_ctype[];

int nuconv_isalnum(int c);
int nuconv_isalpha(int c);
int nuconv_islower(int c);
int nuconv_isupper(int c);
int nuconv_isdigit(int c);
int nuconv_isxdigit(int c);
int nuconv_iscntrl(int c);
int nuconv_isgraph(int c);
int nuconv_isspace(int c);
int nuconv_isblank(int c);
int nuconv_isprint(int c);
int nuconv_ispunct(int c);

int nuconv_tolower(int c);
int nuconv_toupper(int c);

int nuconv_do_atoi(int64_t* dst, const char* target, unsigned radix, int flags);
int nuconv_do_atou(uint64_t* dst, const char* target, unsigned radix, int flags);

int nuconv_do_itoa(int64_t target, char* buf, unsigned radix, int flags);
int nuconv_do_utoa(uint64_t target, char* buf, unsigned radix, int flags);

int nuconv_atoi(const char* buf);
unsigned int nconv_atou(const char* buf);

char* nuconv_itoa(int n, char* buf, int radix);
char* nuconv_utoa(unsigned int n, char* buf, int radix);


size_t             nuconv_zmin   (size_t x, size_t y);
char               nuconv_cmin   (char x, char y);
signed char        nuconv_scmin  (signed char x, signed char y);
unsigned char      nuconv_ucmin  (unsigned char x, unsigned char y);
short              nuconv_smin   (short x, short y);
signed short       nuconv_ssmin  (signed short x, signed short y);
unsigned short     nuconv_usmin  (unsigned short x, unsigned short y);
int                nuconv_imin   (int x, int y);
signed int         nuconv_simin  (signed int x, signed int y);
unsigned int       nuconv_uimin  (unsigned int x, unsigned int y);
long               nuconv_lmin   (long x, long y);
signed long        nuconv_slmin  (signed long x, signed long y);
unsigned long      nuconv_ulmin  (unsigned long x, unsigned long y);
long long          nuconv_llmin  (long long x, long long y);
signed long long   nuconv_sllmin (signed long long x, signed long long y);
unsigned long long nuconv_ullmin (unsigned long long x, unsigned long long y);

size_t             nuconv_zmax   (size_t x, size_t y);
char               nuconv_cmax   (char x, char y);
signed char        nuconv_scmax  (signed char x, signed char y);
unsigned char      nuconv_ucmax  (unsigned char x, unsigned char y);
short              nuconv_smax   (short x, short y);
signed short       nuconv_ssmax  (signed short x, signed short y);
unsigned short     nuconv_usmax  (unsigned short x, unsigned short y);
int                nuconv_imax   (int x, int y);
signed int         nuconv_simax  (signed int x, signed int y);
unsigned int       nuconv_uimax  (unsigned int x, unsigned int y);
long               nuconv_lmax   (long x, long y);
signed long        nuconv_slmax  (signed long x, signed long y);
unsigned long      nuconv_ulmax  (unsigned long x, unsigned long y);
long long          nuconv_llmax  (long long x, long long y);
signed long long   nuconv_sllmax (signed long long x, signed long long y);
unsigned long long nuconv_ullmax (unsigned long long x, unsigned long long y);

#ifdef __cplusplus
}
#endif

#endif /* NUCONV_H */
