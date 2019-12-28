//A sample client for intal.h

//Expected output for this client:
/*
First intal: 4999
Second intal: 2001
Two intals after increment and decrement:
5000
2000
Max of two intals: 5000
Sum: 7000
Diff: 3000
Product: 10000000
Quotient: 2
5000 ^ 2: 25000000
*/

#include "intal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double time_elapsed(struct timespec *start, struct timespec *end);

int main(int argc, char const *argv[]) {
	char *str1;
	char *str2;
	void *intal1;
	void *intal2;
	void *sum;
	void *diff;
	void *product;
	void *quotient;
	void *exp;
	struct timespec start, end;
	
	char *buffer = (char *)malloc(23249425 * sizeof(char));

	//Creating a input string using buffer's length and copy same to str1.
	scanf(" %[^\n]", buffer);
	str1 = (char *)malloc(1 + strlen(buffer) * sizeof(char));
	strcpy(str1, buffer);
	//Creating a input string using buffer's length and copy same to str2.
	scanf(" %[^\n]", buffer);
	str2 = (char *)malloc(1 + strlen(buffer) * sizeof(char));
	strcpy(str2, buffer);
	
	free(buffer);

	intal1 = intal_create(str1); //4999
	intal2 = intal_create(str2); //2001
	
	free(str1);
	free(str2);
	
	printf("First intal: %s\n", intal2str(intal1)); //4999
	printf("Second intal: %s\n", intal2str(intal2)); //2001
	
	/*clock_gettime(CLOCK_REALTIME, &start);
	intal1 = intal_increment(intal1); //5000
	intal2 = intal_decrement(intal2); //2000
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Inc-Dec Time :%lf seconds.\n", time_elapsed(&start, &end));

	printf("Two intals after increment and decrement : \n");
	printf("%s\n", intal2str(intal1)); //5000
	printf("%s\n", intal2str(intal2)); //2000
	
	printf("Max of two intals: %s\n", (intal_compare(intal1, intal2) > 0) ? intal2str(intal1) : intal2str(intal2)); //5000
	
	clock_gettime(CLOCK_REALTIME, &start);
	sum = intal_add(intal1, intal2); //7000
	printf("Sum: %s\t", intal2str(sum));
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Time : %lf seconds.\n", time_elapsed(&start, &end));
	
	clock_gettime(CLOCK_REALTIME, &start);
	diff = intal_diff(intal1, intal2); //3000
	printf("Diff: %s\t", intal2str(diff));
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Time : %lf seconds.\n", time_elapsed(&start, &end));*/
	
	clock_gettime(CLOCK_REALTIME, &start);
	product = intal_multiply(intal1, intal2); //10000000
	printf("Product: %s\n", intal2str(product));
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Time : %lf seconds.\n", time_elapsed(&start, &end));

	/*quotient = intal_divide(intal1, intal2); //2
	printf("Quotient: %s\n", intal2str(quotient));

	exp = intal_pow(intal1, quotient); //5000^2 = 25000000
	printf("%s ^ %s: %s\n", intal2str(intal1), intal2str(quotient), intal2str(exp));*/

	//Make sure you destroy all the intals created.
	//intal_destroy(sum);
	//intal_destroy(diff);
	intal_destroy(product);
	//intal_destroy(quotient);
	//intal_destroy(exp);
	intal_destroy(intal1);	
	intal_destroy(intal2);
	return 0;
}

double time_elapsed(struct timespec *start, struct timespec *end) {
	double t;
	
	//tv_sec has the time elasped in seconds
	t = (end->tv_sec - start->tv_sec);
	
	//tv_nsec has the time elasped in nano seconds
	//Final time will be precise with nano seconds
	t += ((end->tv_nsec - start->tv_nsec) * 0.000000001);
	
	return t;
}
