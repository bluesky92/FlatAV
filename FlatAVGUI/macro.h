/****************************************************************************\
*
*   Contains useful macro.
*
\****************************************************************************/
#ifndef FLATAV_MACRO_H
#define FLATAV_MACRO_H



/* Typecast macro for data type char* */
#define PTR(type, data) (*((type*)&(data)))
/* Typecast macro for data type void* */
#define PTROFF(type, data, offset) (*((type*)((unsigned char*)(data)+(offset))))
/* Align x to n bytes */
#define ALIGN(x, n) ((x + (n - 1)) & ~(n - 1))
#endif