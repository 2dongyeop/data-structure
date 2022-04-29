#include <stdio.h>

//재귀 호출을 이용해 구현한 피보나치 수열 함수
int fib(int n)
{
	int ret = 0;
	
	if (n == 0) {
		ret = 0;
	}
	else if (n == 1) {
		ret = 1;
	}
	else {
		ret = fib(n - 1) + fib(n - 2);
	}

	return ret;
}

//반복 호출을 이용해 피보나치 수열을 구현
int fib_iter(int n) {
	int ret = 0;
	
	if (n < 2) {
		ret = n;
	}
	else {
		int i = 0, temp = 0, current = 1, last = 0;
		
		for(i = 2; i <= n; i++) {
			temp = current;
			current += last;
			last = temp;
		}
		ret = current;
	}
	
	return ret;
}