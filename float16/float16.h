#pragma once

#include <stdint.h>
#include <stdarg.h>

#define printvar_float16(var) printf("%s = %f\n", #var, ToFloat32(var))

/// <summary>
/// half precision floating point number
/// </summary>
typedef uint16_t float16;

//#ifndef __cplusplus
//    typedef enum { false, true } bool;
//#endif

union fp32 {
    uint32_t u; // float number as uint32
    float f;    // float number
    struct {
        uint32_t m : 23;    // mantissa, -------- -####### ######## ########
        uint32_t e : 8;     // exponent, -####### #------- -------- --------
        uint32_t s : 1;     // sign,     #------- -------- -------- --------
    };
};

union fp16 {
    uint16_t u; // float16 number as uint16
    struct {
        uint32_t m : 10;    // mantissa, ------## ########
        uint32_t e : 5;     // exponent, -#####-- --------
        uint32_t s : 1;     // sign,     #------- --------
    };
};

#ifdef __cplusplus
    extern "C" {
#endif

/// <summary>
/// single precision floating point number conversion to half precision
/// </summary>
/// <param name="f">single precision floating point number</param>
/// <returns>same number in half precision</returns>
float16 ToFloat16(float f);

/// <summary>
/// half precision floating point number conversion to single precision
/// </summary>
/// <param name="h">half precision floating point number</param>
/// <returns>same number in single precision</returns>
float ToFloat32(float16 h);

float16 Add(float16 a, float16 b);

float16 Sub(float16 a, float16 b);

float16 Mul(float16 a, float16 b);

float16 Div(float16 a, float16 b);

float16 Inc(float16 x);

float16 Dec(float16 x);

float16 Inv(float16 x);

float16 Neg(float16 x);

float16 va_add(const char* vargsstr, ...);

float16 va_mul(const char* vargsstr, ...);

int Cmp_eq(float16 a, float16 b);

int Cmp_ne(float16 a, float16 b);

int Cmp_gt(float16 a, float16 b);

int Cmp_lt(float16 a, float16 b);

int Cmp_ge(float16 a, float16 b);

int Cmp_le(float16 a, float16 b);

#ifdef __cplusplus
    }
#endif

#define VA_Add(...) va_add(#__VA_ARGS__, __VA_ARGS__)

#define VA_Mul(...) va_mul(#__VA_ARGS__, __VA_ARGS__)
