#include <stdio.h>

int factorial(int n);

int main()
{
	int input_value = 3;
	int result = 0;

	result = factorial(input_value);  // 3!을 구하고자 재귀 함수 호출
	printf("%d! = %d\n", input_value, result);

	return 0;
}

int factorial(int n)
{
	int ret = 0;
	if (n <= 1) //종료 조건
	{
		ret = 1;
	}
	else
	{
		ret = n * factorial(n - 1); //문제의 범위가 줄어듬
	}
	return ret;
}

//팩토리얼 함수를 재귀를 반복으로 바꾼 경우
int factorial_iter(int n){
	int ret = 1;
	int i = 1;
	
	for(i = n; i > 1; i--) {
		ret = ret * i; 
	}

	return ret;
}