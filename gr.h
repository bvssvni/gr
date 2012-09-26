/*
 
 Gr - Basic group oriented programming in C.
 BSD license.
 by Sven Nilsen, 2012
 http://www.cutoutpro.com
 
 Version: 0.000
 in angular degrees versioning notation
 http://isprogrammingeasy.blogspot.no/2012/08/angular-degrees-versioning-notation.html
 
 */
/*
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 */
/*
 
 Group oriented programming is a paradigm of problem solving where operations
 on groups are optimized rather than objects.
 
 When we have 4 bytes, one per line, we can read the bits vertically and think
 of each column as a group of states. These are two equivalent way of thinking
 of the bits. In group oriented programming, the binary states are stored
 separately from the objects. In traditional programming this is done by
 using hash tables, but these are slow on chunks of data.
 
    01001100	A group can thought of being a 'column' when an object
    11001111	is a 'row' of states. This make parallel processing,
    00000000	parsing of text, compression of solutions etc. a lot
    11111111	more sophisticated.
 
 A group is a collection of unique identities (ids),
 where operations OR, AND, EXCEPT are efficient and well defined.
 It is like Venn diagrams, only for programming.
 
 Group oriented programming may or may not be faster than normal algorithms.
 Because the memory to contain information about a group is dynamically
 allocated, the algorithms can suffer when 'malloc' and 'free' is slow.
 On the other hand, since you can do Boolean operations, this will save
 loops later when you read the data.
 
 The power of group oriented programming is it allows an approach to
 problem solving by preprosessing information. Generic algorithms are easy
 to implement because a group can be used as a filter and passed around.
 
 This library supports slices and bits.
 
    gr_	    slices	0,40 80,95 1103,1502 ...
	    Efficient for few ids in large address space.
 
    bin_    bits	00011101011011101010011 ...
	    Efficient for small address spaces.
 
 Both operates on arrays of longs. For slices, this is beneficial since
 a pointer can be converted from a long.
 
 */

#ifndef GR_MEMGUARD
#define GR_MEMGUARD

// Performs a boolean AND on slices.
long *gr_and(const long *a, const long *b);

// Performs a boolean OR on slices.
long *gr_or(const long *a, const long *b);

// Performas a boolean EXCEPT on slices.
long *gr_except(const long *a, const long *b);

// The number of bits making up the group.
long gr_size(const long *a);

// The last number in the group.
long gr_last(const long *a);

// Calculates te ratio of compression.
// Less than 1 is bad.
// Bigger than 1 is good.
double gr_ratio(const long* a);

// Writes 1's to an bit array.
// start - The bit to start writing.
// end - The bit to end writing.
void bin_set_slice_true(long *a, long start, long end);

// Reads slice from bit array.
// Returns an array of ints telling the state of each bit.
int *bin_read_slice(const long *a, long start, long end);

// Performs a boolean AND on bit array.
long *bin_and(const long *a, const long *b);

// Performs a boolean OR on bit array.
long *bin_or(const long *a, const long *b);

// Performs a boolean EXCEPT on bit array.
long *bin_except(const long *a, const long *b);

// Performs a boolean XOR on bit array.
long *bin_xor(const long *a, const long *b);

#endif
