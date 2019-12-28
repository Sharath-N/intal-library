//Trivial implementation of intal.h
//Doesn't really implement an arbitrary length version.
//So, it works for small enough examples, which fit in 64-bit int.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "intal.h"

//String (array of chars with a null termination) of decimal digits converted to intal type.
//Input str has most significant digit at the head of the string.
//"void *" hides the format of intal.
//The returned pointer points to the intal "object. Client need not know the format of the intal.
//Even if the format of an intal is "char*" just like the input string, it's expected to a create
//a new copy because the intal object should be modifiable, but the input could be a constant literal.
void* intal_create(const char* str) {
	long int *a;
	a = (long int*) malloc(sizeof(long int));
	a[0] = atol(str);
	return (void*) a;
}

//Destroy the created "object"
void intal_destroy(void* intal) {
	if(intal) free(intal);
}

//Converts intal to a string of decimal digits for mostly display purpose.
//Returned string has most significant non-zero digit at the head of the string.
char* intal2str(void* intal) {
	char *s = (char *) malloc(21 * sizeof(char));
	sprintf(s, "%ld", ((long int*)intal)[0]);
	return s;
}

//Increments the integer by one.
void* intal_increment(void* intal) {
	(((long int*)intal)[0])++;
	return intal;
}

//Decrements the integer by one.
//No change if the intal is zero because it is nonnegative integer.
void* intal_decrement(void* intal) {
	(((long int*)intal)[0])--;
	return intal;
}

//Adds two intals and returns their sum.
void* intal_add(void* intal1, void* intal2) {
	long int *a;
	a = (long int*) malloc(sizeof(long int));
	a[0] = (((long int*)intal1)[0]) + (((long int*)intal2)[0]);
	return (void*) a;
}

//Returns the difference (obviously, nonnegative) of two intals.
void* intal_diff(void* intal1, void* intal2){
	long int *a;
	a = (long int*) malloc(sizeof(long int));
	if((((long int*)intal1)[0]) > (((long int*)intal2)[0]))
		a[0] = (((long int*)intal1)[0]) - (((long int*)intal2)[0]);
	else
		a[0] = (((long int*)intal2)[0]) - (((long int*)intal1)[0]);
	return (void*) a;
}

//Multiplies two intals and returns the product.
void* intal_multiply(void* intal1, void* intal2) {
	long int *a;
	a = (long int*) malloc(sizeof(long int));
	a[0] = (((long int*)intal1)[0]) * (((long int*)intal2)[0]);
	return (void*) a;
}

//Integer division
//Returns the integer part of the quotient of intal1/intal2.
void* intal_divide(void* intal1, void* intal2) {
	long int *a;
	a = (long int*) malloc(sizeof(long int));
	a[0] = (((long int*)intal1)[0]) / (((long int*)intal2)[0]);
	return (void*) a;
}

//Returns -1, 0, +1
int intal_compare(void* intal1, void* intal2){
	if((((long int*)intal1)[0]) == (((long int*)intal2)[0]))
		return 0;
	else if((((long int*)intal1)[0]) > (((long int*)intal2)[0]))
		return 1;
	return -1;
}

//Returns intal1^intal2.
void* intal_pow(void* intal1, void* intal2){
	long int *a;
	double d1 = (double)(((long int*)intal1)[0]);
	double d2 = (double)(((long int*)intal2)[0]);
	double d3;
	d3 = pow(d1, d2);

	a = (long int*) malloc(sizeof(long int));
	a[0] = (long int) d3;
	return (void*) a;
}
