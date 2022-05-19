#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayStackNodeType {
	int data;
    /*char data;*/
} ArrayStackNode;

typedef struct ArrayStackType {
	int maxCount;
	int currentCount;
	ArrayStackNode *pData;
} ArrayStack;
ArrayStack* createArrayStack(int size)
{
	if(size <= 0) return NULL;
	else {
		ArrayStack *pReturn = NULL;
		pReturn = (ArrayStack *)malloc(sizeof(ArrayStack)); //메모리 할당
		if(pReturn == NULL) return NULL;
		else {
			memset(pReturn, 0, sizeof(ArrayStack)); //메모리 초기화
			pReturn->maxCount = size;  //최대 자료 개수 지정

			pReturn->pData = (ArrayStackNode *)malloc(sizeof(ArrayStackNode) * size);
			if(pReturn->pData == NULL) return NULL;
			else {
				memset(pReturn->pData, 0, sizeof(ArrayStackNode) * size);

				return pReturn;
			}
		}
	}
} 

int isArrayStackFull(ArrayStack* pStack)
{
	int ret  = 0;
	if(pStack != NULL) {
		if(pStack->currentCount == pStack->maxCount) {
			ret = 1;
		}
	}
    return ret;
}
/*int pushAS(ArrayStack* pStack, char data)*/
int pushAS(ArrayStack* pStack, int data)
{
	int ret = 0;
	if(isArrayStackFull(pStack) == 0) {
		pStack->pData[pStack->currentCount].data = data;
		pStack->currentCount++;
		ret = 1;
	}
	else {
		printf("오류, 스택이 가득 찼습니다. pushAS()\n");
	}
	return ret;
}

int isArrayStackEmpty(ArrayStack* pStack)
{
	int ret = 0;

	if(pStack != NULL) {
		if(pStack->currentCount == 0) {
			ret = 1;
		}
	}

	return ret;
}

ArrayStackNode* popAS(ArrayStack* pStack) 
{
	ArrayStackNode *pReturn = NULL;

	if(0 == isArrayStackEmpty(pStack)) {
		pReturn = (ArrayStackNode *)malloc(sizeof(ArrayStackNode));
		if(pReturn != NULL) {
			pReturn->data = pStack->pData[pStack->currentCount - 1].data;
			pStack->currentCount--;
		}
		else {
			printf("오류, 메모리 할당, popAS()\n");
		}
	}
	
	return pReturn;
}

ArrayStackNode* peekAS(ArrayStack* pStack)
{
	ArrayStackNode* pReturn = NULL;
	if(pStack != NULL) {
		if(isArrayStackEmpty(pStack) == 0) {
			pReturn = &(pStack->pData[pStack->currentCount - 1]);
		}
	}

	return pReturn;
}

void deleteArrayStack(ArrayStack* pStack)
{
	if(pStack != NULL) {
		if(pStack->pData != NULL) {
			free(pStack->pData);
		}
		free(pStack);
	}
}

void displayArrayStack(ArrayStack *pStack)
{
	int i = 0 ;
	if(pStack != NULL) {
		int size = pStack->maxCount;
		int top = pStack->currentCount;

		printf("스택 크기: %d, 현재 노드 개수: %d\n", pStack->maxCount, pStack->currentCount);
		for(i = size - 1; i >= top; i--) {
			printf("[%d]-[Empty]\n", i);
		}
		
		for(i = top - 1; i >= 0; i--) {
			printf("[%d]-[%d]\n", i, pStack->pData[i].data);
            /*printf("[%d]-[%c]\n", i, pStack->pData[i].data);*/

		}
	}
}

int main(int argc, char *argv[])
{
	ArrayStack *pStack = NULL;
	ArrayStackNode *pNode = NULL;

	pStack = createArrayStack(6);
	if(pStack != NULL) {
		pushAS(pStack, 10);	
		pushAS(pStack, 20);	
		pushAS(pStack, 30);	
		pushAS(pStack, 40);	
		displayArrayStack(pStack);

		pNode = popAS(pStack);
		if(pNode != NULL) {
			printf("Pop 값 - [%d]\n", pNode->data);
			free(pNode);
		}
		

		
		displayArrayStack(pStack);

		pNode = peekAS(pStack);
		if(pNode != NULL) {
			printf("Peek 값-[%d]\n", pNode->data);
		}
		displayArrayStack(pStack);

		deleteArrayStack(pStack);
	}
	return 0;
}