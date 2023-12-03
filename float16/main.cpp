// float16.cpp : example
//

#include <iostream>
#include <cstdio>

#include "float16.h"

int main() {
	// conversion between float and float16 types 
	// and precision loss caused by conversion
	float f32 = 3.14159f;
	float16 f16 = ToFloat16(f32);
	float f32new = ToFloat32(f16);
	printf("float:              %f\n", f32);
	printf("float   -> float16: %f\n", ToFloat32(f16));
	printf("float16 -> float:   %f\n", f32new);

	printf("\n");

	// basic arithmetic operations
	float16 a = ToFloat16(5.5f),
			b = ToFloat16(3.3f),
			c = Add(a, b),
			d = Sub(a, b),
			e = Mul(a, b),
			f = Div(a, b),
			g = Inc(a),
			h = Dec(a),
			i = Inv(b),
			j = Neg(a);
	#if defined(_MSC_VER)
		float16 k = VA_Add(a, b, d, f),
			    l = VA_Mul(a, d, f, i);
	#endif

	printvar_float16(a);
	printvar_float16(b);
	printf("a + b = %f\n", ToFloat32(c));
	printf("a - b = %f\n", ToFloat32(d));
	printf("a * b = %f\n", ToFloat32(e));
	printf("a / b = %f\n", ToFloat32(f));
	printf("a + 1 = %f\n", ToFloat32(g));
	printf("a - 1 = %f\n", ToFloat32(h));
	printf("1 / b = %f\n", ToFloat32(i));
	printf("-a    = %f\n", ToFloat32(j));

	printf("\n");

	#if defined(_MSC_VER)
		printf("a + b + d + f = %f\n", ToFloat32(k));
		printf("a * d * f * i = %f\n", ToFloat32(l));

		printf("\n");
	#endif

	// comparisons
	bool b1 = Cmp_eq(a, b),
		 b2 = Cmp_eq(a, a),
		 b3 = Cmp_ne(a, a),
		 b4 = Cmp_ne(a, b),
		 b5 = Cmp_gt(b, a),
		 b6 = Cmp_gt(a, b);

	printf("a == b: %s\n", b1 ? "true" : "false");
	printf("a == a: %s\n", b2 ? "true" : "false");
	printf("a != a: %s\n", b3 ? "true" : "false");
	printf("a != b: %s\n", b4 ? "true" : "false");
	printf("b > a:  %s\n", b5 ? "true" : "false");
	printf("a > b:  %s\n", b6 ? "true" : "false");
	
	return 0;
}