#include "float16.h"

float16 ToFloat16(float f) {
    union fp32 f32;
    f32.f = f;
    union fp16 f16 = { 0 };
    if (f32.e == 0) // Signed zero/denormal (which will underflow)
        f16.e = 0;
    else if (f32.e == 255) { // Inf or NaN (all exponent bits set)
        f16.e = 31;
        f16.m = f32.m ? 0x200 : 0;
    }
    else { // Normalized number
        // Exponent unbias the single, then bias the halfp
        int newexp = f32.e - 127 + 15;
        if (newexp >= 31) // Overflow, return signed infinity
            f16.e = 31;
        else if (newexp <= 0) { // Underflow
            if ((14 - newexp) <= 24) { // Mantissa might be non-zero
                uint32_t mant = f32.m | 0x800000; // Hidden 1 bit
                f16.m = mant >> (14 - newexp);
                if ((mant >> (13 - newexp)) & 1) // Check for rounding
                    f16.u++; // Round, might overflow into exp bit, but this is OK
            }
        }
        else {
            f16.e = newexp;
            f16.m = f32.m >> 13;
            if (f32.m & 0x1000) // Check for rounding
                f16.u++; // Round, might overflow to inf, this is OK
        }
    }
    f16.s = f32.s;
    return f16.u;
}

float ToFloat32(float16 h) {
    static const union fp32 magic = { 113 << 23 };
    static const uint32_t shifted_exp = 0x7c00 << 13; // exponent mask after shift
    union fp32 f32;
    union fp16 f16;
    f16.u = h;
    f32.u = (f16.u & 0x7fff) << 13;     // exponent/mantissa bits
    uint32_t exp = shifted_exp & f32.u; // just the exponent
    f32.u += (127 - 15) << 23;          // exponent adjust
    // handle exponent special cases
    if (exp == shifted_exp) // Inf/NaN?
        f32.u += (128 - 16) << 23; // extra exp adjust
    else if (exp == 0) { // Zero/Denormal?
        f32.u += 1 << 23; // extra exp adjust
        f32.f -= magic.f; // renormalize
    }
    f32.u |= (f16.u & 0x8000) << 16; // sign bit
    return f32.f;
}

float16 Add(float16 a, float16 b) {
    return ToFloat16(ToFloat32(a) + ToFloat32(b));
}

float16 Sub(float16 a, float16 b) {
    return ToFloat16(ToFloat32(a) - ToFloat32(b));
}

float16 Mul(float16 a, float16 b) {
    return ToFloat16(ToFloat32(a) * ToFloat32(b));
}

float16 Div(float16 a, float16 b) {
    return ToFloat16(ToFloat32(a) / ToFloat32(b));
}

float16 Inc(float16 x) {
    return Add(x, 0x3C00);
}

float16 Dec(float16 x) {
    return Sub(x, 0x3C00);
}

float16 Neg(float16 x) {
    return Sub(0, x);
}

float16 Inv(float16 x) {
    return Div(0x3C00, x);
}

#if defined(_MSC_VER)
    float16 va_add(const char* vargsstr, ...) {
        va_list vargs;
        va_start(vargs, vargsstr);
        float16 result = va_arg(vargs, float16);
        for (int i = 0; vargsstr[i]; vargsstr[++i] == ',' ? result = Add(result, va_arg(vargs, float16)) : *vargsstr++) {}
        return result;
    }

    float16 va_mul(const char* vargsstr, ...) {
        va_list vargs;
        va_start(vargs, vargsstr);
        float16 result = va_arg(vargs, float16);
        for (int i = 0; vargsstr[i]; vargsstr[++i] == ',' ? result = Mul(result, va_arg(vargs, float16)) : *vargsstr++) {}
        return result;
    }
#elif defined(__GNUC__)
    float16 va_add(const char* vargsstr, ...) {
        va_list vargs;
        va_start(vargs, vargsstr);
        float16 result = (float16)(va_arg(vargs, int));
        for (int i = 0; vargsstr[i]; vargsstr[++i] == ',' ? result = Add(result, (float16)va_arg(vargs, int)) : *vargsstr++) {}
        return result;
    }

    float16 va_mul(const char* vargsstr, ...) {
        va_list vargs;
        va_start(vargs, vargsstr);
        float16 result = (float16)(va_arg(vargs, int));
        for (int i = 0; vargsstr[i]; vargsstr[++i] == ',' ? result = Mul(result, (float16)va_arg(vargs, int)) : *vargsstr++) {}
        return result;
    }
#endif

float16 Fabs(float16 x) {
    return ToFloat16(fabsf(ToFloat32(x)));
}

float16 Abs(float16 x) {
    return ToFloat16(fabsf(ToFloat32(x)));
}

float16 Fmod(float16 a, float16 b) {
    return ToFloat16(fmodf(ToFloat32(a), ToFloat32(b)));
}

float16 Round(float16 x) {
    return ToFloat16(roundf(ToFloat32(x)));
}

float16 Ceil(float16 x) {
    return ToFloat16(ceilf(ToFloat32(x)));
}

float16 Floor(float16 x) {
    return ToFloat16(floorf(ToFloat32(x)));
}

float16 Trunc(float16 x) {
    return ToFloat16(truncf(ToFloat32(x)));
}

float16 Nearbyint(float16 x) {
    return ToFloat16(nearbyintf(ToFloat32(x)));
}

float16 Rint(float16 x) {
    return ToFloat16(rintf(ToFloat32(x)));
}

float16 Pow(float16 a, float16 b) {
    return ToFloat16(powf(ToFloat32(a), ToFloat32(b)));
}

float16 Sqrt(float16 x) {
    return ToFloat16(sqrtf(ToFloat32(x)));
}

float16 Cbrt(float16 x) {
    return ToFloat16(cbrtf(ToFloat32(x)));
}

float16 Exp(float16 x) {
    return ToFloat16(expf(ToFloat32(x)));
}

float16 Exp2(float16 x) {
    return ToFloat16(exp2f(ToFloat32(x)));
}

float16 Expm1(float16 x) {
    return ToFloat16(expm1f(ToFloat32(x)));
}

float16 Log(float16 x) {
    return ToFloat16(logf(ToFloat32(x)));
}

float16 Log10(float16 x) {
    return ToFloat16(log10f(ToFloat32(x)));
}

float16 Log1p(float16 x) {
    return ToFloat16(log1pf(ToFloat32(x)));
}

float16 Log2(float16 x) {
    return ToFloat16(log2f(ToFloat32(x)));
}

float16 Logb(float16 x) {
    return ToFloat16(logbf(ToFloat32(x)));
}

float16 Sin(float16 x) {
    return ToFloat16(sinf(ToFloat32(x)));
}

float16 Cos(float16 x) {
    return ToFloat16(cosf(ToFloat32(x)));
}

float16 Tan(float16 x) {
    return ToFloat16(tanf(ToFloat32(x)));
}

float16 Sinh(float16 x) {
    return ToFloat16(sinhf(ToFloat32(x)));
}

float16 Cosh(float16 x) {
    return ToFloat16(coshf(ToFloat32(x)));
}

float16 Tanh(float16 x) {
    return ToFloat16(tanhf(ToFloat32(x)));
}

float16 Asin(float16 x) {
    return ToFloat16(asinf(ToFloat32(x)));
}

float16 Acos(float16 x) {
    return ToFloat16(acosf(ToFloat32(x)));
}

float16 Atan(float16 x) {
    return ToFloat16(atanf(ToFloat32(x)));
}

float16 Atan2(float16 a, float16 b) {
    return ToFloat16(atan2f(ToFloat32(a), ToFloat32(b)));
}

float16 Asinh(float16 x) {
    return ToFloat16(asinhf(ToFloat32(x)));
}

float16 Acosh(float16 x) {
    return ToFloat16(acoshf(ToFloat32(x)));
}

float16 Atanh(float16 x) {
    return ToFloat16(atanhf(ToFloat32(x)));
}

float16 Hypot(float16 a, float16 b) {
    return ToFloat16(hypotf(ToFloat32(a), ToFloat32(b)));
}

int Cmp_eq(float16 a, float16 b) {
    return (a == b);
}

int Cmp_ne(float16 a, float16 b) {
    return (a != b);
}

int Cmp_gt(float16 a, float16 b) {
    return (ToFloat32(a) > ToFloat32(b));
}

int Cmp_lt(float16 a, float16 b) {
    return (ToFloat32(a) < ToFloat32(b));
}

int Cmp_ge(float16 a, float16 b) {
    return (ToFloat32(a) >= ToFloat32(b));
}

int Cmp_le(float16 a, float16 b) {
    return (ToFloat32(a) <= ToFloat32(b));
}
