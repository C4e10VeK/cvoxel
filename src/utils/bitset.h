#ifndef CVOXEL_BITSET_H
#define CVOXEL_BITSET_H

#include <stdlib.h>
#include <assert.h>
#include "macro.h"
#include "types.h"

// realization functiona and macro from http://c-faq.com/misc/bitsets.html

#ifdef CHAR_BIT
#undef CHAR_BIT
#endif

#define CHAR_BIT 8

typedef struct
{
	u8 *data;
	size_t size;
} Bitset;

#define BITS_TO_BYTES(n) ((n + CHAR_BIT - 1) / CHAR_BIT)

CVOX_STATIC_INLINE Bitset bitsetInit()
{
	return (Bitset){NULL, 0};
}

CVOX_STATIC_INLINE void bitsetAlloc(Bitset *bitset, size_t n)
{
	assert(bitset);
	bitset->data = (u8*)calloc(1, BITS_TO_BYTES(n));
	bitset->size = n;
}

CVOX_STATIC_INLINE void bitsetSet(Bitset *bitset, size_t n)
{
	assert(bitset && n < bitset->size);
	bitset->data[n / CHAR_BIT] |= 1 << (n % CHAR_BIT); 
}

CVOX_STATIC_INLINE void bitsetClear(Bitset *bitset, size_t n)
{
	assert(bitset && n < bitset->size);
	bitset->data[n / CHAR_BIT] &= ~(1 << n % CHAR_BIT);
}

CVOX_STATIC_INLINE bool bitsetTest(Bitset *bitset, size_t n)
{
	assert(bitset && n < bitset->size);
	return bitset->data[n / CHAR_BIT] & (1 << n % CHAR_BIT);
}

CVOX_STATIC_INLINE void bitsetFree(Bitset *bitset)
{
	assert(bitset);
	if (bitset->data)
		free(bitset->data);
	bitset->size = 0;
}

#endif