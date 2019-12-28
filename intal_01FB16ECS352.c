#include "intal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void* zero_array() {
	char *z_arr = (char *)malloc(sizeof(char) * 2);
	z_arr[0] = '0';
	z_arr[1] = '\0';
	return z_arr;
}

void* intal_create(const char* str) {
	char *intal;
	long int i = 0, z_count = 0, eff_len = 0;
	
	if(str[0] > '9' || str[0] < '0') return zero_array();

	//while() is used count the number of zeros.
	while(str[i] != '\0') {
		if(str[i] == '0') z_count += 1;
		else break;
		i += 1;
	}
	
	//For 0, 00, 000, 0000, . . . . . . . .
	if(str[i - 1] == '0' && strlen(str) == z_count) z_count -= 1;
	
	//"eff_len" is the count of all valid numbers before the non-decimal digit and after removing all preceeding 0s.
	for(i = z_count; str[i] != '\0'; i++) {
		if(str[i] >= '0' && str[i] <= '9') eff_len += 1;
		else break;
	}
	
	if(eff_len == 0) return zero_array();//printf("num_count : %d\n", num_count);
	
	//Length of the intal after removing insignificant 0's before non-zero MSB.Ex: For 0012, eff_len will be 4-2 = 2
	intal = (char *)malloc(sizeof(char) * (eff_len + 1));//One extra space for null character. 
	
	for(i = 0; i < eff_len; i++)
		intal[i] = str[i + z_count];//To extract the number from the string
	intal[i] = '\0';
	
	return intal;	
}

void intal_destroy(void* intal) {
	if(intal == NULL) return;
	
	free(intal);
	
	return;
}

char* intal2str(void* intal) {
	if(intal == NULL) {
		char *nan = (char *)malloc(sizeof(char) * 4);
		strcpy(nan, "NaN");
		nan[3] = '\0';
		return nan;
	}
	
	char *itl = (char *)intal;
	long int len = strlen(itl);
	char *f_itl = (char *)malloc(sizeof(char) * (len + 1));
	strcpy(f_itl, itl);
	f_itl[len] = '\0';
	
	return f_itl;
}

void* intal_increment(void* intal) {
	char *nan = NULL;
	if(intal == NULL) return nan;
	
	char *f_itl = (char *)intal;
	long int i;
	int carry = 0, sum = 0, digit;

	for(i = strlen(intal) - 1; i >= 0; i--) {
		digit = f_itl[i] - '0';//printf("Digit : %d\n", digit);
		
		if(i == strlen(intal) - 1) {
			sum = carry + digit + 1;
			if(sum / 10 == 1) {
				carry = 1;
				sum = sum % 10;
				f_itl[i] = sum + '0';
			}
			else {
				carry = 0;
				f_itl[i] = sum + '0';
			}//printf("Char in if : %c\n", f_itl[i]);
		}
		else {
			if(carry == 1) {
				sum = carry + digit;
				if(sum / 10 == 1) {
					carry = 1;
					sum = sum % 10;
					f_itl[i] = sum + '0';
				}
				else {
					carry = 0;
					f_itl[i] = sum + '0';
				}
			}
			else break;//printf("Char in else : %c\n", f_itl[i]);
		}
	}
	
	if(carry == 1) {
		char *new_intal;
		int i;
	
		new_intal = (char *)malloc(sizeof(char) * strlen(f_itl) + 2);//+2 because, 1 for new increase in array size, 1 for NULL character
	
		new_intal[0] = '1';//Carry, i.e., 1
		for(i = 1; i <= strlen(f_itl); i++)
			new_intal[i] = f_itl[i - 1];//To extract the number from the string
			
		new_intal[i] = '\0';
		
		intal_destroy(intal);
		
		return new_intal;
	}
	
	//printf("The inc. string : %s\n", f_itl);
	return f_itl;
}

void* intal_decrement(void* intal) {
	char *f_itl = (char *)intal;
	
	char *nan = NULL;
	if(intal == NULL) return nan;
	
	int i, borrow = 0, diff = 0;
	int digit; 
	int org_len = strlen(intal);//Original length of string, before decrementation.
	
	if(strlen(intal) == 1 && f_itl[0] == '0') return intal;
	if(strlen(intal) == 1 && f_itl[0] == '1') {
		f_itl[0] = '0';
		return f_itl;
	} 
	
	for(i = strlen(intal) - 1; i >= 0; i--) {
		digit = f_itl[i] - '0';
		if(i == strlen(intal) - 1) {
			
			if(digit == 0) {
				borrow += 1;
				f_itl[i] = 9 + '0';
			}
			else {
				diff = digit - 1;
				f_itl[i] = diff + '0';
			}//printf("Char in if : %c\n", f_itl[i]);
		}
		else {
			
			if(digit != 0 && borrow > 0) {
				diff = digit - borrow;
				borrow -= 1;
				f_itl[i] = diff + '0';
			}
			//Filling all 0s with 9, because of borrow.
			else if(borrow != 0) {
				f_itl[i] = 9 + '0';
			}
			else {
				//f_itl[i] = digit + '0';
				break;
			}//printf("Char in else : %c\n", f_itl[i]);
		}
	}
	
	//Creating new array if first digit becomes zero after decrementation
	if(f_itl[0] == '0') {
		char *new_intal;
		int i;
	
		new_intal = (char *)malloc(sizeof(char) * org_len);//+2 because, 1 for new increase in array size, 1 for NULL character
	
		for(i = 0; i < (org_len - 1); i++)
			new_intal[i] = f_itl[i + 1];//To extract the number from the string
			
		new_intal[i] = '\0';
		
		intal_destroy(intal);
		
		return new_intal;
	}
	
	return f_itl;
	
}

void* intal_add(void* intal1, void* intal2) {
	if(intal1 == NULL || intal2 == NULL) return NULL;
	
	char *itl1 = (char *)intal1;
	char *itl2 = (char *)intal2;
	long int f_len;
	long int i = 0, j = strlen(itl1) - 1, k = strlen(itl2) - 1;
	int sum = 0, carry = 0;
	
	if(intal_compare(intal1, intal2) > 0) f_len = strlen(itl1);
	else f_len = strlen(itl2);
	
	char *f_itl = (char *)malloc(sizeof(char) * (f_len + 1));//One extra for NULL character
	f_itl[f_len] = '\0';//printf("Length : %ld\n", f_len);
	
	i = f_len - 1;//To access the last digit(because, \0 and 0-based indexing)
	while(i >= 0 && j >= 0 && k >= 0) {
		sum = (itl1[j] - '0') + (itl2[k] - '0') + carry;//printf("i = %d j = %d k = %d\n", i, j, k);
		
		j -= 1;k -= 1;
		
		if(sum / 10 > 0) {
			carry = sum / 10;
			f_itl[i] = (sum % 10) + '0';
		}
		else {
			f_itl[i] = sum + '0';
			carry = 0;
		}//printf("Array : %d\n", f_itl[i] - '0');
		i -= 1;
	}
	
	while(i >= 0 && k >= 0) {
		sum = (itl2[k] - '0') + carry;//printf("i = %d j = %d k = %d\n", i, j, k);
		
		k -= 1;
		
		if(sum / 10 > 0) {
			carry = sum / 10;
			f_itl[i] = (sum % 10) + '0';
		}
		else {
			f_itl[i] = sum + '0';
			carry = 0;
		}//printf("Array : %d\n", f_itl[i] - '0');
		i -= 1;
	}
	while(i >= 0 && j >= 0) {
		sum = (itl1[j] - '0') + carry;//printf("i = %d j = %d k = %d\n", i, j, k);
		
		j -= 1;
		
		if(sum / 10 > 0) {
			carry = sum / 10;
			f_itl[i] = (sum % 10) + '0';
		}
		else {
			f_itl[i] = sum + '0';
			carry = 0;
		}//printf("Array : %d\n", f_itl[i] - '0');
		i -= 1;
	}
	
	if(carry != 0) {
		char *new_intal;
		int i;
	
		new_intal = (char *)malloc(sizeof(char) * strlen(f_itl) + 2);//+2 because, 1 for new increase in array size, 1 for NULL character
	
		new_intal[0] = '1';
		new_intal[0] = carry + '0';//Carry, i.e., 1
		for(i = 1; i <= strlen(f_itl); i++)
			new_intal[i] = f_itl[i - 1];//To extract the number from the string
			
		new_intal[i] = '\0';
		
		intal_destroy(f_itl);
		
		return new_intal;
		
	}
	
	return f_itl;
}

void* intal_diff(void* intal1, void* intal2) {
	if(intal1 == NULL || intal2 == NULL) return NULL;
	
	char *itl1;
	char *itl2;
	char *f_itl;
	
	int check = intal_compare(intal1, intal2);
	if(check > 0) {
		itl1 = (char *)intal1;
		itl2 = (char *)intal2;
	}
	else if(check < 0){
		itl1 = (char *)intal2;
		itl2 = (char *)intal1;
	}
	else {
		return zero_array();
	}
	
	//If smaller operand is '1', simply calling intal_decrement() and return decremented value 
	if(strlen(itl2) == 1 && itl2[0] == '1') {
		f_itl = (char *)malloc(sizeof(char) * (strlen(itl1) + 1));
		strcpy(f_itl, itl1);
		f_itl[strlen(itl1)] = '\0';
		return(intal_decrement(f_itl));
	}
	
	long int f_len = strlen(itl1);
	long int i = strlen(itl1) - 1, j = strlen(itl2) - 1, k;
	int diff = 0, borrow = 0, unwant = 0;
	
	f_itl = (char *)malloc(sizeof(char) * (f_len + 1));//One extra for NULL character
	f_itl[f_len] = '\0';
	
	k = f_len - 1;//Points to last location of resultant array
	while(k >= 0 && i >= 0 && j >= 0) {
		
		diff = (itl1[i] - '0') - (itl2[j] - '0');//printf("i = %ld j = %ld k = %ld\n", i, j, k);printf("DIff : %d\n", diff);
		
		if(diff < 0) {
			f_itl[k] =  (((itl1[i] - '0') + 10) - ((itl2[j] - '0') + borrow)) + '0';//'borrow' is added to second operand, to satisfy the borrowal
			borrow = 1;
			//printf("Borrow in IF : %d\n", borrow);printf("Array in if, f_itl[%ld] : %c\n\n", k, f_itl[k]);
		}
		else if(diff == 0 && borrow != 0) {
			f_itl[k] = (((itl1[i] - '0') + 10)	 - ((itl2[j] - '0') + borrow)) + '0';
			borrow = 1;
		}
		else {
			//printf("Borrow in ELSE : %d\n", borrow);
			f_itl[k] = diff - borrow + '0';
			borrow = 0;//printf("Array in else, f_itl[%ld] : %c\n\n", k, f_itl[k]);
		}
		
		i -= 1;j -= 1;
		k -= 1;
	}
	
	while(k >= 0 && i >= 0) {
		diff = (itl1[i] - '0') - borrow;//printf("i = %ld j = %ld k = %ld\n", i, j, k);
		
		//'borrow' is taken from a 0-digit
		if(diff <= 0) {
			f_itl[k] =  (((itl1[i] - '0') + 10) - borrow) + '0';//'borrow' is added to second operand, to satisfy the borrowal
			borrow = 1;//printf("Array in if, f_itl[%ld] : %c\n", k, f_itl[k]);
		}
		else {	
			f_itl[k] = diff + '0';
			borrow = 0;
		}
		i -= 1;		
		k -= 1;
	}
	
	if(f_itl[0] < '0' || f_itl[0] > '9') {
		int r;
		for(r = 0; r < f_len; r++) {
			if(f_itl[r] < '0' || f_itl[r] > '9')
				unwant += 1;
		}//printf("unwant : %d\n", unwant);
		for(r = 0; f_itl[r + unwant] != '\0'; r++) {
			f_itl[r] = f_itl[r + unwant];
		}
		f_itl[r] = '\0';	
	}
	
	if(f_itl[0] == '0') {
		char *new_itl = intal_create(f_itl);
		free(f_itl);
		return new_itl;
	}

	return f_itl;
}

void* intal_multiply(void* intal1, void* intal2) {
	if(intal1 == NULL || intal2 == NULL) return NULL;
	
	char *itl1, *itl2, *f_itl;
	
	if(intal_compare(intal1, intal2) > 0) {
		itl1 = (char *)intal1;
		itl2 = (char *)intal2;
	}
	else {
		itl1 = (char *)intal2;
		itl2 = (char *)intal1;
	}
	
	long int i1_len = strlen(itl1), i2_len2 = strlen(itl2);
	
	if(i2_len2 == 1 || i1_len == 1) {
		if(itl2[0] == '0' || itl1[0] == '0')
			return zero_array();
		
		if(itl2[0] == '1' && i2_len2 == 1) {
			f_itl = (char *)malloc(sizeof(char) * (strlen(itl1) + 1));
			strcpy(f_itl, itl1);
			f_itl[strlen(itl1)] = '\0';
			return f_itl;
		}
		
		if(itl1[0] == '1' && i1_len == 1) {
			f_itl = (char *)malloc(sizeof(char) * (strlen(itl2) + 1));
			strcpy(f_itl, itl2);
			f_itl[strlen(itl2)] = '\0';
			return f_itl;
		}
	}
	
	long int i, j = i2_len2 - 1;
	long int f_len = i1_len + i2_len2;
	long int i2_len = j;
	
	f_itl = (char *)malloc(sizeof(char) * (f_len + 1));//+1 for NULL character
	for(int w = 0; w < f_len; w++) f_itl[w] = '0';
	f_itl[f_len] = '\0';
	
	long int k = f_len - 1;
	int carry = 0, prod = 0, sum = 0, s_carry = 0;
	
	while(j >= 0) {
		i = i1_len - 1;
		
		while(i >= 0) {
			prod = ((itl2[j] - '0') * (itl1[i] - '0')) + carry;//printf("Prod : %d\n",  prod);
			
			if(prod >= 10) {
				carry = prod / 10;//printf("First prod : %d\t", prod);
				sum = (f_itl[k] - '0') + (prod % 10) + s_carry;//printf("First sum : %d\n", sum);
				if(sum > 9) {
					s_carry = sum / 10;
					f_itl[k] = (sum % 10) + '0';
				}
				else {
					s_carry = 0;
					f_itl[k] = sum + '0';
				}//printf("First : f_itl[%d] : %c\n",  k, f_itl[k]);
			}
			else {
				carry = 0;//printf("Second prod : %d\t", prod);
				sum = (f_itl[k] - '0') + prod + s_carry;//printf("Second sum : %d\n", sum);
				if(sum > 9) {
					s_carry = sum / 10;
					f_itl[k] = (sum % 10) + '0';
				}
				else {
					s_carry = 0;
					f_itl[k] = sum + '0';
				}//printf("Second : f_itl[%d] : %c\n",  k, f_itl[k]);
				
			}//printf("k val, i val : %d\t%d\n\n", k, i);
			k -= 1;
			i -= 1;
		}//printf("Carry : %d\n", carry);
		if(carry != 0 || s_carry != 0) {
			sum = (f_itl[k] - '0') + carry + s_carry;//printf("Last sum : %d\n", sum);
			if(sum > 9) {
					s_carry = sum / 10;
					f_itl[k] = (sum % 10) + '0';
			}
			else {
				s_carry = 0;
				f_itl[k] = sum + '0';
			}
			carry = 0;//printf("f_itl[%d] : %c\n\n",  k, f_itl[k]);
			k -= 1;
		}
		
		
		j -= 1;
		
		k = (f_len - 1) - (i2_len - j);//One vacant space after multiplication of one digit j with itl1
	}

	if(f_itl[0] == '0') {
		char *new_itl = intal_create(f_itl);
		free(f_itl);
		return new_itl;
	}
	
	return f_itl;
}

void* intal_divide(void* intal1, void* intal2)
{       if(!intal1) return NULL;
    if(!intal2) return NULL;    
    if (!strcmp(intal2str(intal2), "0"))
        return NULL;
    if (!strcmp(intal2str(intal1), "0"))
        return intal_create("0");
    if (!intal_compare(intal1, intal2))
        return intal_create("1");
    if (-1==intal_compare(intal1, intal2))
        return intal_create("0");


    char *intal11 = intal2str(intal1);
    char *intal22 = intal2str(intal2);
    char *partintal1 = (char*)malloc(sizeof(char*) * strlen(intal22));
    partintal1[0] = intal11[0];
    int i = 0;
    char *result;
    char *res = (char*)malloc(sizeof(char) * strlen(intal11));
    
    int count = 0;
    while(intal_compare(intal_create(partintal1), intal2) != 1)
    {
        i++;
        partintal1[i] = intal11[i];
    }

    partintal1 = realloc(partintal1, sizeof(partintal1)+sizeof(char));

    int index=0, length=1;
    while(i < strlen(intal11))
    {
        while(intal_compare(intal_create(partintal1), intal2) >= 0)
        {
            strcpy(partintal1, intal2str(intal_diff(intal_create(partintal1), intal2)));
            count++;
        }
        
        result = (char*)malloc(sizeof(char));
        result[index] = count + '0';
        strcat(res, intal2str(intal_create(result)));
        count = 0;
        strcpy(partintal1, intal2str(intal_create(partintal1)));
        int j = strlen(partintal1) - 1;

        if(!intal11[i+1])   break;

        while(intal_compare(intal_create(partintal1), intal2) != 1)
        {   j++; i++; 
            partintal1[j] = intal11[i];
            break;
        }
    }
    return intal_create(res);
}

static void* power_divide(void* intal1, void* intal2) {
	if(intal1 == NULL || intal2 == NULL) return NULL;
	
	char *itl1 = (char *)intal1;//dividend
	char *itl2 = (char *)intal2;//divisor
	char *f_itl;//quotient
	
	//Return NaN, if anyone of the second operand is zero.
	if(strlen(itl2) == 1 && itl2[0] == '0') {
		char *nan = NULL;
		return nan;
	}

	int flag = intal_compare(intal1, intal2), i;
	if(flag < 0)
		return zero_array();

	else if(flag == 0) {
		f_itl = (char *)malloc(sizeof(char) * 2);
		f_itl[0] = '1';
		f_itl[1] = '\0';
		return f_itl;
	}
	
	char *new_itl1 = (char *)malloc(sizeof(char) * (strlen(itl1) + 1));//Intermediate dividend
	strcpy(new_itl1, itl1);
	new_itl1[strlen(itl1)] = '\0';
	char *new_itl12;
	
	long int f_len = strlen(itl1) - strlen(itl2) + 1;	
	f_itl = (char *)malloc(sizeof(char) * (f_len + 1));
	f_itl[f_len] = '\0';
	for(int w = 0; w < f_len; w++) f_itl[w] = '0';

	flag = intal_compare((void *)new_itl1, (void *)itl2);
	while(flag >= 0) {
		new_itl12 = intal_diff(new_itl1, itl2);//passing string(or void)
		strcpy(new_itl1, new_itl12);
		new_itl1[strlen(new_itl12)] = '\0';
		free(new_itl12);
		f_itl = intal_increment(f_itl);//passing string(or void)
		flag = intal_compare(new_itl1, itl2);
	}
	free(new_itl1);
	
	
	if(f_itl[0] == '0') {
		char *new_intal = (char *)malloc(sizeof(char) * f_len);
	
		for(i = 1; i < f_len; i++)
			new_intal[i - 1] = f_itl[i];//To extract the number from the string
		new_intal[f_len - 1] = '\0';
		
		intal_destroy(f_itl);
		
		return new_intal;
	}
	
	return f_itl;
}

int intal_compare(void* intal1, void* intal2) {
	if(intal1 == NULL || intal2 == NULL) return 0;

	char *itl1 = (char *)intal1;
	char *itl2 = (char *)intal2;
	int len1 = strlen(itl1);
	int len2 = strlen(itl2);
	
	if(len1 == len2) {
		int i = 0;
		while(i < len1) {
			if(itl1[i] - '0' == itl2[i] - '0') 
				i += 1;
			else if(itl1[i] - '0' > itl2[i] - '0')
				return 1;
			else
				return -1;
		}
		if(i == len2)
			return 0;
	}
	else if(len1 > len2)
		return 1;
	else
		return -1;
}

void* intal_pow(void* intal1, void* intal2) {
	if(intal1 == NULL || intal2 == NULL) return NULL;
	
	char *itl1 = (char *)intal1, *itl2 = (char *)intal2, *f_itl;
	long int i1_len = strlen(itl1), i2_len = strlen(itl2), f_len = 0;
	
	if(itl2[0] == '0' && itl1[0] == '0')
		return zero_array();
		
	if((itl1[0] == '1' && i1_len == 1) || (itl2[0] == '0' && i2_len == 1)) {
		f_itl = (char *)malloc(sizeof(char) * 2);
		f_itl[0] = '1';
		f_itl[1] = '\0';
		return f_itl;
	}
	
	if(itl2[0] == '1' && i2_len == 1) {
		f_itl = (char *)malloc(sizeof(char) * (strlen(itl2) + 1));
		strcpy(f_itl, itl1);
		f_itl[strlen(itl1)] = '\0';
		return f_itl;
	}
	
	char *base = (char *)malloc(sizeof(char) * (i1_len + 1));
	strcpy(base, itl1);
	base[i1_len] = '\0';
	char *power = (char *)malloc(sizeof(char) * (i2_len + 1)), *p_temp;
	strcpy(power, itl2);
	power[i2_len] = '\0';
	char *divby2 = (char *)malloc(sizeof(char) * 2);
	divby2[0] = '2';divby2[1] = '\0';
	char *initial = (char *)malloc(sizeof(char) * 2);
	initial[0] = '1';initial[1] = '\0';
	
	while(1) {//printf("Pow : %s\n", power);
		if(strlen(power) != 1 || power[0] != '1') {
			if((power[strlen(power) - 1] - '0') % 2 == 1) {
				power = intal_decrement(power);
				initial = intal_multiply(base, initial);
			}
			base = intal_multiply(base, base);
			p_temp = power_divide(power, divby2);//printf("Exp : %s\n", base);
			free(power);
			power = p_temp;
		}
		else break;
	}
		
	base = intal_multiply(base, initial);//printf("Exp : %s\n", base);
	free(initial);
	free(power);
	return base;
}
