#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string>
#define MAX_SIZE 1000
void char_to_int(char temp[],int num[],char* sign) {
	if (temp[strlen(temp) - 1] == '\n')
		temp[strlen(temp) - 1] = '\0';
	for (int i = 0; i < strlen(temp); i++){
		if (temp[i] == '-')*sign='2';
		else
		num[strlen(temp)-1-i] = temp[i]-'0';
	}
}
void BigNumberAdd(int num1[],int num2[],int sum[]) {
	for (int i = 0,carry=0; i < MAX_SIZE ; i++) {
		sum[i] = num1[i] + num2[i] + carry;
		carry = sum[i] / 10;
		sum[i] %= 10;
	}
}
void BigNumberMinus(int num1[], int num2[], int sum[]) {
	for (int i = 0, carry_out = 0; i < MAX_SIZE; i++) {
		sum[i] = num1[i] - num2[i] - carry_out;
		if (sum[i] < 0) {
			carry_out = 1; sum[i] += 10;
		}
		else {
			carry_out = 0;
		}
	}

}
void PrintSum(int sum[]) {
	int i=MAX_SIZE-1;
	for (;i>0 && sum[i]==0; --i);
	while (i >=0)printf("%d", sum[i]),--i;
	printf("\n");
}
int CompareNumber(int num1[],int num2[]) {
	int i=MAX_SIZE - 1;
	while (i >= 0 && num1[i] == num2[i])--i;
	return num1[i] - num2[i];
}
int main() {
	FILE* file_ptr;
	file_ptr = fopen("123.txt", "r");
	while (!feof(file_ptr)) {
		char operation[4] = { '0' };
		char sign_num1='1', sign_num2='1';
		int num1_length, num2_length;
		char temp[MAX_SIZE] = { '0' };
		int num1[MAX_SIZE] = { }, num2[MAX_SIZE] = { }, sum[MAX_SIZE] = {  };
		fgets(operation, 4, file_ptr);
		fgets(temp, MAX_SIZE, file_ptr);
		char_to_int(temp,num1,&sign_num1);
		num1_length = strlen(temp);
		fgets(temp, MAX_SIZE, file_ptr);
		char_to_int(temp, num2,&sign_num2);
		num2_length = strlen(temp);
		if (operation[0] == '1') {
			if (sign_num1 == '1' && sign_num2 == '1') {
				BigNumberAdd(num1, num2, sum),PrintSum(sum);
			}
			if (sign_num1 == '2' && sign_num2 == '2') {
				printf("-"), BigNumberAdd(num1, num2, sum), PrintSum(sum);
			}
			if (sign_num1 == '1' && sign_num2 == '2') {
				if (CompareNumber(num1, num2) < 0) printf("-"), BigNumberMinus(num2, num1, sum);
				else BigNumberMinus(num1, num2, sum);
					PrintSum(sum);
			}
			if (sign_num1 == '2' && sign_num2 == '1') {
				if (CompareNumber(num2, num1) < 0) printf("-"), BigNumberMinus(num1, num2, sum);
				else BigNumberMinus(num2, num1, sum);
				PrintSum(sum);
			}
		}
		if (operation[0] == '2') {
			if (sign_num1 == '1' && sign_num2 == '1') {
				if (CompareNumber(num1, num2) < 0)printf("-"), BigNumberMinus(num2, num1, sum);
				else BigNumberMinus(num1, num2, sum);
				PrintSum(sum);
			}
			if (sign_num1 == '2' && sign_num2 == '2') {
				if (CompareNumber(num2, num1) < 0)printf("-"), BigNumberMinus(num1, num2, sum);
				else BigNumberMinus(num2, num1, sum);
				PrintSum(sum);
			}
			if (sign_num1 == '1' && sign_num2 == '2') {
				BigNumberAdd(num1, num2, sum), PrintSum(sum);
			}
			if (sign_num1 == '2' && sign_num2 == '1') {
				printf("-"), BigNumberAdd(num1, num2, sum), PrintSum(sum);
			}
		}
	}


	return 0;
}