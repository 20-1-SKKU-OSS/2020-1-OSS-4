#include<stdio.h>

/* 
 * subtractable_check - x-y가 오버플로우를 일으키는지 확인
 */

int subtractable_check(int x, int y) {
	int sub = x + ~y + 1;
	int x_sign = x >> 31;
	int y_sign = y >> 31;
	int sub_sign = sub >> 31;
	
	return !((x_sign^y_sign) && (x_sign^sub_sign));
}

/*
* byteSwap - x의 n번째 바이트와 m번쨰 바이트를 서로 교환
*/
int byteSwap(int x, int n, int m) {
  int n_byte = n << 3;
  int m_byte = m << 3;
  int nmask = 0xff << n_byte;
  int mmask = 0xff << m_byte;
  int totalmask = nmask | mmask;
  int remainder = x & ~totalmask;

  int n_value = ((x & nmask) >> n_byte) & 0xff;
  int m_value = ((x & mmask) >> m_byte) & 0xff;

  return remainder | (n_value << m_byte) | (m_value << n_byte);
}

/*
* isGreater - x와 y의 값을 비교해 x가 더 큰 경우 1, 그 외에는 0을 반환
*/
int isGreater(int x, int y) {
	int x_sign = (x >> 31) & 0x1;
	int y_sign = (y >> 31) & 0x1;
	int sign_differ = x_sign ^ y_sign;
	int sub_sign = ((y + ~x + 1) >> 31) & 0x1;
	printf("sign %d %d\n", sign_differ, sub_sign);
	return ((!x_sign) & sign_differ) | (((~sign_differ & 0x1) & sub_sign));
}

/*
* fitsbits - x를 n개의 비트로 표현할 수 있으면 1, 없으면 0을 반환
*/

int fitsbits(int x, int n) {//Can X be expressed by n-bit?
	int y = 33 + ~n;
	int result = (x << y);
	result = result >> y;
	result = result ^ x;
	return !result;
}

/*
* logicalShift - x를 n번 logicalShift한 값을 반환
*/

int logicalShift(int x, int n) {
	int bit = 32 + ~n + 1;
	int full = (0xff << 24) + (0xff << 16) + (0xff << 8) + 0xff;
	int mask = ~(full << bit + ~1 +1 << 1);
	printf("%d %x %x\n", bit, full, full << bit-1 << 1);
	return (x >> n) & mask;
}

/*
* countbit - x를 2의 보수로 표현했을 때 1의 개수 반환
*/

int countbit(int x) {//count 1 in the x for two's complement expression
	x = (x >> 1 & 0x55555555) + (x & 0x55555555);
	x = (x >> 2 & 0x33333333) + (x & 0x33333333);
	x = ((x >> 4) + x) & 0x0f0f0f0f;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return x & 0x3f;
}

/*
* rotate - x를 n번 left shift함, 단 carry out은 비어있는 low bit로 이동
*/

int rotate(int x, int n) {
	int bit = 32 + ~n + 1;
	int full = (0xff << 24) + (0xff << 16) + (0xff << 8) + 0xff;
	int sub_bit = x & (full << bit);
	int mask = ~(full << n);

	return (x << n) | ((sub_bit >> bit) & mask);
}

/*
* float_absolute_vale - float value의 절대값을 반환
* 단 NaN이나 infinity는 값을 그대로 반환
*/

unsigned float_absolute_value(unsigned uf) {
	unsigned uFP = uf & 0x7fffffff;
	printf("%d %d\n", uFP, uFP + 0xff900000);
	if (!(uFP - 0x7f900000 >> 31)) {
		printf("passed\n");
		return uf;
	}
	else return uFP;
}

/*
* int_to_float_cast - int형 입력을 float value로 반환
* 단 NaN이나 infinity는 값을 그대로 반환
*/

unsigned int_to_float_cast(int x) {
	int k=31;
	int sign_bit = x >> 31 << 31;
	int e, frac;
	if (!x) return 0;
	if (x == 0x80000000) {
		e = 158 << 23;
		return sign_bit + e;
	}
	if (x < 0) x = -x;
	if (x > 0) {
		while (1) {
			if (x == 0) break;
			else if (x&(1 << k))	break;
			else k--;
		}
		e = (k + 127);
		printf("%d %x\n", k, e);
		e = e << 23;
		int frac, mask = 0, count = k-1;
		while (count >= 0) {
			mask += 1 << (count);
			count--;
		}
		if (k > 23) {
			frac = (x & (0xffffff << (k - 24))) >> (k - 24);
			if ((frac & 0x7) >= 3) {
				frac = (frac >> 1) + 1;
			}
			else frac = frac >> 1;
		}
		else frac = (x & mask) << (23-k);
		unsigned FP = sign_bit + e + frac;
		return FP;
	}
	
}

/*
* float_twice - float value의 두배를 반환
* 단 NaN이나 infinity는 값을 그대로 반환
*/

unsigned float_twice(unsigned uf) {
	int sign = uf >> 31 << 31;
	int e = (uf - sign) >> 23;
	int frac = uf & 0x7fffff;

	if (e == 0) frac *= 2; //denormalized
	else if (e < 0xff) e++; //normalized
	else return uf; //special
	return sign + (e << 23) + frac;
}
