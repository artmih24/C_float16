#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <math.h>

/// <summary>
/// prints half precision floating point number variable name and value
/// </summary>
/// <param name="f">half precision floating point number to be printed</param>
#if defined(__GNUC__)
    #define printvar_float16(var) printf("%s = %f\n", #var, ToFloat32(var))
#elif defined(_MSC_VER)
    #define printvar_float16(var) printf(#var ## " = %f\n", ToFloat32(var))
#endif

/// <summary>
/// half precision floating point number
/// </summary>
typedef uint16_t float16;

/// <summary>
/// union containing single precision floating point number and its mantissa, exponent and sign
/// </summary>
union fp32 {
    uint32_t u; // float number as uint32
    float f;    // float number
    struct {
        uint32_t m : 23;    // mantissa, -------- -####### ######## ########
        uint32_t e : 8;     // exponent, -####### #------- -------- --------
        uint32_t s : 1;     // sign,     #------- -------- -------- --------
    };
};

/// <summary>
/// union containing half precision floating point number and its mantissa, exponent and sign
/// </summary>
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

/// <summary>
/// Sum of two half precision floating point numbers
/// </summary>
/// <param name="a">1st half precision floating point number</param>
/// <param name="b">2nd half precision floating point number</param>
/// <returns>sum of a and b as half precision floating point number</returns>
float16 Add(float16 a, float16 b);

/// <summary>
/// Subtraction of 2nd half precision floating point number from 1st half precision floating point number
/// </summary>
/// <param name="a">minuend as half precision floating point number</param>
/// <param name="b">subtrahend as half precision floating point number</param>
/// <returns>difference between a nd b as half precision floating point number</returns>
float16 Sub(float16 a, float16 b);

/// <summary>
/// Product of two half precision floating point numbers
/// </summary>
/// <param name="a">1st half precision floating point number</param>
/// <param name="b">2nd half precision floating point number</param>
/// <returns>product of a nd b as half precision floating point number</returns>
float16 Mul(float16 a, float16 b);

/// <summary>
/// Division of 1st half precision floating point number by 2nd half precision floating point number
/// </summary>
/// <param name="a">dividend as half precision floating point number</param>
/// <param name="b">divisor as half precision floating point number</param>
/// <returns>a divided by b as half precision floating point number</returns>
float16 Div(float16 a, float16 b);

/// <summary>
/// Increment of half precision floating point number (adds 1)
/// </summary>
/// <param name="x">number to increment</param>
/// <returns>incremented number</returns>
float16 Inc(float16 x);

/// <summary>
/// Decrement of half precision floating point number (subtracts 1)
/// </summary>
/// <param name="x">number to be decremented</param>
/// <returns>decremented number</returns>
float16 Dec(float16 x);

/// <summary>
/// Inversion of half precision floating point number (division of 1 by this number)
/// </summary>
/// <param name="x">half precision floating point number to divide 1 by it</param>
/// <returns>1 divided by half precision floating point number</returns>
float16 Inv(float16 x);

/// <summary>
/// Negatiion of half precision floating point number (subtraction from zero)
/// </summary>
/// <param name="x">half precision floating point number to subtract it from zero</param>
/// <returns>half precision floating point number with negative sign</returns>
float16 Neg(float16 x);

/// <summary>
/// Sum of any quantity of half precision floating point numbers
/// </summary>
/// <param name="varargsstr">characters array containing summands as half precision floating point numbers</param>
/// <param name="...">summands as half precision floating point numbers</param>
/// <returns>sum of half precision floating point numbers</returns>
float16 va_add(const char* vargsstr, ...);

/// <summary>
/// Product of any quantity of half precision floating point numbers
/// </summary>
/// <param name="varargsstr">characters array containing multipliers as half precision floating point numbers</param>
/// <param name="...">multipliers as half precision floating point numbers</param>
/// <returns>product of half precision floating point numbers</returns>
float16 va_mul(const char* vargsstr, ...);

/// <summary>
/// Absolute value of half precision floating point number
/// </summary>
/// <param name="x">half precision floating point number to get its absolute value</param>
/// <returns>absolute value of half precision floating point number</returns>
float16 Fabs(float16 x);

/// <summary>
/// Absolute value of half precision floating point number
/// </summary>
/// <param name="x">half precision floating point number to get its absolute value</param>
/// <returns>absolute value of half precision floating point number</returns>
float16 Abs(float16 x);

float16 Fmod(float16 a, float16 b);

float16 Round(float16 x);

float16 Ceil(float16 x);

float16 Floor(float16 x);

float16 Trunc(float16 x);

float16 Nearbyint(float16 x);

float16 Rint(float16 x);

float16 Pow(float16 a, float16 b);

float16 Sqrt(float16 x);

float16 Cbrt(float16 x);

float16 Exp(float16 x);

float16 Exp2(float16 x);

float16 Expm1(float16 x);

float16 Log(float16 x);

float16 Log10(float16 x);

float16 Log1p(float16 x);

float16 Log2(float16 x);

float16 Logb(float16 x);

float16 Sin(float16 x);

float16 Cos(float16 x);

float16 Tan(float16 x);

float16 Sinh(float16 x);

float16 Cosh(float16 x);

float16 Tanh(float16 x);

float16 Asin(float16 x);

float16 Acos(float16 x);

float16 Atan(float16 x);

float16 Atan2(float16 a, float16 b);

float16 Asinh(float16 x);

float16 Acosh(float16 x);

float16 Atanh(float16 x);

float16 Hypot(float16 a, float16 b);

/// <summary>
/// Comparison of two half precision floating point numbers, returns 1 if they are equal
/// </summary>
/// <param name="a">1st half precision floating point number to be compared</param>
/// <param name="b">2nd half precision floating point number to be compared</param>
/// <returns>1 if numbers are equal, else 0</returns>
int Cmp_eq(float16 a, float16 b);

/// <summary>
/// Comparison of two half precision floating point numbers, returns 1 if they are not equal
/// </summary>
/// <param name="a">1st half precision floating point number to be compared</param>
/// <param name="b">2nd half precision floating point number to be compared</param>
/// <returns>1 if numbers are not equal, else 0</returns>
int Cmp_ne(float16 a, float16 b);

/// <summary>
/// Comparison of two half precision floating point numbers, returns 1 if left number is greater than right
/// </summary>
/// <param name="a">1st half precision floating point number to be compared</param>
/// <param name="b">2nd half precision floating point number to be compared</param>
/// <returns>1 if left number is greater than right, else 0</returns>
int Cmp_gt(float16 a, float16 b);

/// <summary>
/// Comparison of two half precision floating point numbers, returns 1 if left number is less than right
/// </summary>
/// <param name="a">1st half precision floating point number to be compared</param>
/// <param name="b">2nd half precision floating point number to be compared</param>
/// <returns>1 if left number is less than right, else 0</returns>
int Cmp_lt(float16 a, float16 b);

/// <summary>
/// Comparison of two half precision floating point numbers, returns 1 if left number is greater than right or equal to it
/// </summary>
/// <param name="a">1st half precision floating point number to be compared</param>
/// <param name="b">2nd half precision floating point number to be compared</param>
/// <returns>1 if left number is greater than right or equal to it, else 0</returns>
int Cmp_ge(float16 a, float16 b);

/// <summary>
/// Comparison of two half precision floating point numbers, returns 1 if left number is less than right or equal to it
/// </summary>
/// <param name="a">1st half precision floating point number to be compared</param>
/// <param name="b">2nd half precision floating point number to be compared</param>
/// <returns>1 if left number is less than right or equal to it, else 0</returns>
int Cmp_le(float16 a, float16 b);

#ifdef __cplusplus
    }
#endif

/// <summary>
/// Sum of any quantity of half precision floating point numbers
/// </summary>
/// <param name="...">summands as half precision floating point numbers</param>
/// <returns>sum of half precision floating point numbers</returns>
#define VA_Add(...) va_add(#__VA_ARGS__, __VA_ARGS__)

/// <summary>
/// Product of any quantity of half precision floating point numbers
/// </summary>
/// <param name="...">multipliers as half precision floating point numbers</param>
/// <returns>product of half precision floating point numbers</returns>
#define VA_Mul(...) va_mul(#__VA_ARGS__, __VA_ARGS__)

// some half precision floating point constants

#define float16_PI 0x4248
#define float16_0  0
#define float16_1  0x3C00
