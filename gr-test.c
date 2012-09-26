
#include <stdio.h>
#include <math.h>

#include "gr.h"
#include "gr.c"

#define Err() do {printf("%i Error\n", __LINE__); exit(1);} while (0)
#define Zero(a) (fabs(a) < 0.000000001)

void test(void)
{
    {
        // Test basic boolean operations.
        arr_init(long, a, 2, 4);
        arr_init(long, b, 3, 5);
        if (gr_size(a) != 2) Err();
        if (gr_size(b) != 2) Err();
	if (gr_last(a) != 4) Err();
	if (gr_last(b) != 5) Err();
        
        long *c = gr_and(a, b);
        if (arr_len(c) != 2) Err();
        if (c[0] != 3) Err();
        if (c[1] != 4) Err();
        
        arr_free(c);
        c = gr_or(a, b);
        if (arr_len(c) != 2) Err();
        if (c[0] != 2) Err();
        if (c[1] != 5) Err();
        
        arr_free(c);
        c = gr_except(a, b);
        if (arr_len(c) != 2) Err();
        if (c[0] != 2) Err();
        if (c[1] != 3) Err();
        
        arr_free(c);
        arr_free(a);
        arr_free(b);
    }
    {
	// Check the ratio of compression.
	arr_init(long, a, 0, 128);
	double ratio = gr_ratio(a);
	if (!Zero(ratio - 1.0)) Err();
    }
    {
	// Check that shift operations behave as required.
	long a = ~0UL;
	int ls = 8 * sizeof(long);
	long b[ls];
	int i;
	for (i = 0; i < ls; i++) {
	    b[i] = a & (1L << (ls - i - 1));
	    if (!b[i]) Err();
	}
	a = ~0UL >> 2;
	for (i = 0; i < ls; i++) {
	    b[i] = a & (1L << (ls - i - 1));
	}
	if (b[0]) Err();
	if (b[1]) Err();
	if (!b[2]) Err();
    }
    {
	// Check that generating a slice within a long works.
	int ls = 8 * sizeof(long);
	int cap = 3;
	int len = 5;
	long a = ~0UL << (ls - len) >> cap;
	int bits = 0;
	int i;
	for (i = 0; i < ls; i++) {
	    if (a & (1L << (ls - i - 1))) bits++;
	}
	if (bits != 5) Err();
    }
    {
	// Check that calculation of cap, len is correct.
	int start = 80;
	int end = 127;
	int ls = 8 * sizeof(long);
	int blockStart = start / ls;
	if (blockStart != 1) Err();
	
	// Cap is the position with the block where we start 1's.
	int cap = start - ls * blockStart;
	// Len is the number of bits uptil the end of block.
	int len = end - start;
	len = len > ls - cap ? ls - cap : len;
	if (cap != 16) Err();
	if (len != 47) Err();
    }
    {
	// Check that calculation of cap, len is correct.
	int start = 80;
	int end = 200;
	int ls = 8 * sizeof(long);
	int blockStart = start / ls;
	if (blockStart != 1) Err();
	int cap = start - ls * blockStart;
	int len = end - start;
	len = len > ls - cap ? ls - cap : len;
	if (cap != 16) Err();
	if (len != 48) Err();
    }
    {
	// Testing that reading and writing to bit array works.
	arr_init_size(long, a, 2);
	bin_set_slice_true(a, 10, 20);
	int *b = bin_read_slice(a, 9, 21);
	if (b[0]) Err();
	if (!b[1]) Err();
	if (!b[10]) Err();
	if (b[11]) Err();
	
	arr_free(b);
	arr_free(a);
    }
    {
	// Test bit array 'and'.
	arr_init_size(long, a, 10);
	bin_set_slice_true(a, 2, 4);
	arr_init_size(long, b, 20);
	bin_set_slice_true(b, 3, 5);
	long *c = bin_and(a, b);
	
	int *d = bin_read_slice(c, 0, 10);
	if (d[0]) Err();
	if (d[2]) Err();
	if (!d[3]) Err();
	if (d[4]) Err();
	
	arr_free(d);
	arr_free(c);
	arr_free(b);
	arr_free(a);
    }
    {
	// Test bit array 'or'.
	arr_init_size(long, a, 10);
	bin_set_slice_true(a, 2, 4);
	arr_init_size(long, b, 20);
	bin_set_slice_true(b, 3, 5);
	long *c = bin_or(a, b);
	
	int *d = bin_read_slice(c, 0, 10);
	if (d[0]) Err();
	if (!d[2]) Err();
	if (!d[3]) Err();
	if (!d[4]) Err();
	if (d[5]) Err();
	
	arr_free(d);
	arr_free(c);
	arr_free(b);
	arr_free(a);
    }
    {
	// Test bit array 'except'.
	arr_init_size(long, a, 10);
	bin_set_slice_true(a, 2, 4);
	arr_init_size(long, b, 20);
	bin_set_slice_true(b, 3, 5);
	long *c = bin_except(a, b);
	
	int *d = bin_read_slice(c, 0, 10);
	if (d[0]) Err();
	if (!d[2]) Err();
	if (d[3]) Err();
	if (d[4]) Err();
	if (d[5]) Err();
	
	arr_free(d);
	arr_free(c);
	arr_free(b);
	arr_free(a);
    }
    {
	// Test bit array 'xor'.
	arr_init_size(long, a, 10);
	bin_set_slice_true(a, 2, 4);
	arr_init_size(long, b, 20);
	bin_set_slice_true(b, 3, 5);
	long *c = bin_xor(a, b);
	
	int *d = bin_read_slice(c, 0, 10);
	if (d[0]) Err();
	if (!d[2]) Err();
	if (d[3]) Err();
	if (!d[4]) Err();
	if (d[5]) Err();
	
	arr_free(d);
	arr_free(c);
	arr_free(b);
	arr_free(a);
    }
}

int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < (1<<0); i++) {
        test();
    }
    printf("gr unit tests completed!\n");
    return 0;
}
