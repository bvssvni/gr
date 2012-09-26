
#include "arr.h"

long countAnd(const long *a, const long *b);

long countAnd(const long *a, const long *b)
{
	long list = 0;
	
    long alength = arr_len(a);
    long blength = arr_len(b);
	if (alength == 0 || blength == 0) return list;
	
	long i = 0, j = 0; long ba = 0; long bb = 0; long oldB = 0;
	long pa, pb;
	while (i < alength || j < blength) {
		pa = a[i>=alength?alength-1:i];
		pb = b[j>=blength?blength-1:j];
		
		if (pa == pb) {
			ba = !ba;
			bb = !bb;
			if ((ba && bb) != oldB) list++;
            
			i++;
			j++;
		}
		else if ((pa < pb || j >= blength) && i < alength) {
			ba = !ba;
			if ((ba && bb) != oldB) list++;
            
			i++;
		}
		else if (j < blength) {
			bb = !bb;
			if ((ba && bb) != oldB) list++;
            
			j++;
		}
		else break;
		
		oldB = ba && bb;
	}
	
	return list;
}


long* gr_and(const long *a, const long *b)
{
    if (a == NULL || b == NULL) return NULL;
	
	long list = 0;
    long len = countAnd(a, b);
    arr_init_size(long, arr, len);
	
    long alength = arr_len(a);
    long blength = arr_len(b);
	if (alength == 0 || blength == 0) return arr;
	
	long i = 0, j = 0; long ba = 0; long bb = 0; long oldB = 0;
	long pa, pb;
	while (i < alength || j < blength) {
		pa = a[i>=alength?alength-1:i];
		pb = b[j>=blength?blength-1:j];
		
		if (pa == pb) {
			ba = !ba; bb = !bb;
			if ((ba && bb) != oldB) arr[list++] = pa;
            
			i++; j++;
		}
		else if ((pa < pb || j >= blength) && i < alength) {
			ba = !ba;
			if ((ba && bb) != oldB) arr[list++] = pa;
            
			i++;
		}
		else if (j < blength) {
			bb = !bb;
			if ((ba && bb) != oldB) arr[list++] = pb;
            
			j++;
		}
		else break;
		
		oldB = ba && bb;
	}
	
	return arr;
}


long countOr(const long *a, const long *b);

long countOr(const long *a, const long *b)
{
    long alength = arr_len(a);
    long blength = arr_len(b);
	if (alength == 0 && blength == 0) return 0;
    if (alength == 0) return blength;
    if (blength == 0) return alength;
	
	long i = 0, j = 0; long ba = 0; long bb = 0; long oldB = 0;
    long pa, pb; long counter = 0;
	while (i < alength || j < blength) {
		pa = a[i>=alength?alength-1:i];
		pb = b[j>=blength?blength-1:j];
		
		if (pa == pb) {
			ba = !ba; bb = !bb;
			if ((ba || bb) != oldB) counter++;
            
			i++; j++;
		}
		else if ((pa < pb || j >= blength) && i < alength) {
			ba = !ba;
			if ((ba || bb) != oldB) counter++;
            
			i++;
		}
		else if (j < blength) {
			bb = !bb;
			if ((ba || bb) != oldB) counter++;
            
			j++;
		}
		else break;
		
		oldB = ba || bb;
	}
	
	return counter;
}


long* gr_or(const long *a, const long *b)
{
    if (a == NULL || b == NULL) return NULL;
	
	long count = countOr(a,b);
    arr_init_size(long, list, count);
	
	long counter = 0;
	const long a_length = arr_len(a);
	const long b_length = arr_len(b);
	
	if (a_length == 0 && b_length == 0) return list;
	
	long k;
	if (a_length == 0) {
		for (k = 0; k < b_length; k++) list[counter++] = b[k];
        
		return list;
	}
    if (b_length == 0) {
		for (k = 0; k < a_length; k++) list[counter++] = a[k];
        
		return list;
	}
	
	long i = 0, j = 0; long ba = 0; long bb = 0; long oldB = 0;
    long pa, pb;
	while (i < a_length || j < b_length) {
		pa = a[i>=a_length?a_length-1:i];
		pb = b[j>=b_length?b_length-1:j];
		
		if (pa == pb) {
			ba = !ba; bb = !bb;
			if ((ba || bb) != oldB) list[counter++] = pa;
            
			i++; j++;
		}
		else if ((pa < pb || j >= b_length) && i < a_length) {
			ba = !ba;
			if ((ba || bb) != oldB) list[counter++] = pa;
            
			i++;
		}
		else if (j < b_length) {
			bb = !bb;
			if ((ba || bb) != oldB) list[counter++] = pb;
            
			j++;
		}
		else break;
		
		oldB = ba || bb;
	}
	
	return list;
}


long countExcept(const long *a, const long *b);

long countExcept(const long *a, const long *b)
{
	const long a_length = arr_len(a);
	const long b_length = arr_len(b);
	
	if (a_length == 0 || b_length == 0) return 0;
	
	long i = 0, j = 0; long ba = 0; long bb = 1; long oldB = 0;
	long pa; long pb; long list = 0;
	while (i < a_length || j < b_length) {
		pa = a[i>=a_length?a_length-1:i];
		pb = b[j>=b_length?b_length-1:j];
		
		if (pa == pb) {
			ba = !ba; bb = !bb;
			if ((ba && bb) != oldB) list++;
            
			i++; j++;
		}
		else if ((pa < pb || j >= b_length) && i < a_length) {
			ba = !ba;
			if ((ba && bb) != oldB) list++;
            
			i++;
		}
		else if (j < b_length) {
			bb = !bb;
			if ((ba && bb) != oldB) list++;
            
			j++;
		}
		else break;
		
		oldB = ba && bb;
	}
	
	return list;
}


long* gr_except
(const long *a, const long *b)
{
    if (a == NULL || b == NULL) return NULL;
	
	const long a_length = arr_len(a);
	const long b_length = arr_len(b);
	if (b_length == 0) {
        arr_init_size(long, c, a_length);
        memcpy(c, a, sizeof(long)*a_length);
        return c;
    }
	
    long count = countExcept(a, b);
    arr_init_size(long, arr, count);
	
	if (a_length == 0 || b_length == 0) return arr;
	
	long i = 0, j = 0; long ba = 0; long bb = 1; long oldB = 0;
	long pa; long pb; long list = 0;
	while (i < a_length || j < b_length) {
		pa = a[i>=a_length?a_length-1:i];
		pb = b[j>=b_length?b_length-1:j];
		
		if (pa == pb) {
			ba = !ba; bb = !bb;
			if ((ba && bb) != oldB) arr[list++] = pa;
            
			i++; j++;
		}
		else if ((pa < pb || j >= b_length) && i < a_length) {
			ba = !ba;
			if ((ba && bb) != oldB) arr[list++] = pa;
            
			i++;
		}
		else if (j < b_length) {
			bb = !bb;
			if ((ba && bb) != oldB) arr[list++] = pb;
            
			j++;
		}
		else break;
		
		oldB = ba && bb;
	}
	
	return arr;
}

long gr_size(const long *a)
{
    long len = arr_len(a);
    if (len & 1) return -1;
    
    long i, size = 0;
    for (i = 0; i < len; i+=2) {
        size += a[i+1]-a[i];
    }
    return size;
}

long gr_last(const long *a)
{
    long len = arr_len(a);
    return a[len-1];
}

double gr_ratio(const long* a)
{
    long last = gr_last(a);
    return last / (8.0 * sizeof(long) * arr_len(a));
}

void bin_set_slice_true(long *a, long start, long end)
{
    const int ls = 8 * sizeof(long);
    long max = arr_len(a) * ls;
    long remaining = end - start;
    int cap, len;
    long blockStart;
    
    while (remaining > 0) {
	blockStart = start / ls;
	cap = start - ls * blockStart;
	len = end - start;
	len = len > ls - cap ? ls - cap : len;
	a[blockStart] |= ~0UL << (ls - len) >> cap;
	
	remaining = start - end - len;
	start = (blockStart + 1);
	if (start >= max) return;
    }
}

int *bin_read_slice(const long *a, long start, long end)
{
    const int ls = 8 * sizeof(long);
    long max = ls * arr_len(a);
    end = end > max ? max : end;
    long size = end - start;
    arr_init_size(int, res, size);
    long blockStart;
    int cap;
    
    long i;
    for (i = start; i < end; i++) {
	blockStart = i / ls;
	cap = i - blockStart * ls;
	res[i-start] = 0 != (a[blockStart] & (1L << (ls - cap - 1)));
    }
    
    return res;
}

long *bin_and(const long *a, const long *b)
{
    long alen = arr_len(a);
    long blen = arr_len(b);
    long min = alen < blen ? alen : blen;
    arr_init_size(long, c, min);
    long i;
    for (i = 0; i < min; i++) c[i] = a[i] & b[i];
    
    return c;
}

long *bin_or(const long *a, const long *b)
{
    long alen = arr_len(a);
    long blen = arr_len(b);
    long max = alen > blen ? alen : blen;
    arr_init_size(long, c, max);
    long i;
    for (i = 0; i < max; i++) c[i] = a[i] | b[i];
    
    return c;
}

long *bin_except(const long *a, const long *b)
{
    long alen = arr_len(a);
    long blen = arr_len(b);
    long min = alen < blen ? alen : blen;
    arr_init_size(long, c, min);
    long i;
    for (i = 0; i < min; i++) c[i] = a[i] & ~b[i];
    
    return c;
}

long *bin_xor(const long *a, const long *b)
{
    long alen = arr_len(a);
    long blen = arr_len(b);
    long max = alen > blen ? alen : blen;
    arr_init_size(long, c, max);
    long i;
    for (i = 0; i < max; i++) c[i] = a[i] ^ b[i];
    
    return c;
}

