#include "Encryption_XTEA.h"


void Encipher(const unsigned long *const inBuf, unsigned long *const outBuf, const unsigned long * const key) {
	unsigned long v1 = inBuf[0];
	unsigned long v2 = inBuf[1];
	unsigned long sum = 0;     
	unsigned long delta = 0x9E3779B9;     

	for (unsigned long n = 32; n > 0; n--) {
		v1 += (v2 << 4 ^ v2 >> 5) + v2 ^ sum + key[sum & 3];
		sum += delta;         
		v2 += (v1 << 4 ^ v1 >> 5) + v1 ^ sum + key[sum >> 11 & 3];
	}     
	outBuf[0] = v1; outBuf[1] = v2;
}
