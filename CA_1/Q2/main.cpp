#include "stdio.h"
#include "x86intrin.h"

typedef union {
	__m128i 			int128;
	
	unsigned char		m128_u8[16];
	signed char			m128_i8[16];

	unsigned short		m128_u16[8];
	signed short		m128_i16[8];

	unsigned int        m128_u32[4];
	signed int          m128_i32[4];

	unsigned long		m128_u64[2];
	signed long		    m128_i64[2];

	__m128  			float128;

	float               m128_ps[4];

} intVec;

void print_u8 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=15; i>0; i--) {
		printf ("%X, ", tmp.m128_u8[i]);
	}
	printf ("%X]\n\n", tmp.m128_u8[0]);
}

void print_i8 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=15; i>0; i--) {
		printf ("%i, ", tmp.m128_i8[i]);
	}
	printf ("%i]\n\n", tmp.m128_i8[0]);
}

void print_u16 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=7; i>0; i--) {
		printf ("%X, ", tmp.m128_u16[i]);
	}
	printf ("%X]\n\n", tmp.m128_u16[0]);
}

void print_i16 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=7; i>0; i--) {
		printf ("%i, ", tmp.m128_i16[i]);
	}
	printf ("%i]\n\n", tmp.m128_i16[0]);
}

void print_u32 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=3; i>0; i--) {
		printf ("%X, ", tmp.m128_u32[i]);
	}
	printf ("%X]\n\n", tmp.m128_u32[0]);
}

void print_i32 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=3; i>0; i--) {
		printf ("%i, ", tmp.m128_i32[i]);
	}
	printf ("%i]\n\n", tmp.m128_i32[0]);
}

void print_u64 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=1; i>0; i--) {
		printf ("%lX, ", tmp.m128_u64[i]);
	}
	printf ("%lX]\n\n", tmp.m128_u64[0]);
}

void print_i64 (__m128i a)
{
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	for (int i=1; i>0; i--) {
		printf ("%li, ", tmp.m128_i64[i]);
	}
	printf ("%li]\n\n", tmp.m128_i64[0]);
}

void print_int_vector (__m128i a, char* type)
{
	switch(type)
	{
		case:
			"u8": printf ("16 Unsigned bytes:\n"); print_u8 (a); break;
			"i8": printf ("16 Signed bytes:\n"); print_i8 (a); break;
			"u16": printf ("8 Unsigned words:\n"); print_u16 (a); break;
			"i16": printf ("8 Signed words:\n"); print_i16 (a); break;
			"u32": printf ("4 Unsigned words:\n"); print_u32 (a); break;
			"i32": printf ("4 Signed words:\n"); print_i32 (a); break;
			"u64": printf ("2 Unsigned words:\n"); print_u64 (a); break;
			"i64": printf ("2 Signed words:\n"); print_i64 (a); break;														
	}
}

void print_spsf_vector (__m128 a)
{
	intVec tmp;
	tmp.float128 = a;
	printf ("[");
	for (int i=3; i>0; i--) {
		printf ("%f, ", tmp.m128_ps[i]);
	}
	printf ("%f]\n\n", tmp.m128_ps[0]);
}

unsigned char intArray [16] = {	0X00, 0X11, 0X22, 0X33, 0X44, 0X55, 0X66, 0X77,
								0X88, 0X99, 0XAA, 0XBB, 0XCC, 0XDD, 0XEE, 0XFF};

int main(void)
{
	__m128i a;
	a = _mm_load_si128((const __m128i*)intArray);

	__m128 b;
	b = _mm_load_ps((float*)intArray);

	print_int_vector(a, "u8");

	print_int_vector(a, "i8");

	print_int_vector(a, "u16");

	print_int_vector(a, "i16");

	print_int_vector(a, "u32");

	print_int_vector(a, "i32");

	print_int_vector(a, "u64");

	print_int_vector(a, "i64");			

	printf ("Single Precision Floating point:\n");
	print_spsf_vector (b);
	
	return 0;
}
