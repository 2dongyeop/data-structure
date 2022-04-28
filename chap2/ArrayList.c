#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayListNodeType {
	int data;
} ArrayListNode;

typedef struct ArrayListType {
	int maxCount;
	int currentCount;
	ArrayListNode *pData;
} ArrayList;

ArrayList *createList(int count) 
{
	ArrayList *pReturn = (ArrayList *)malloc(sizeof(ArrayList));
	pReturn -> maxCount = count;
	pReturn -> currentCount = 0; //19
	pReturn -> pData = (ArrayList *)malloc(sizeof(ArrayListNode) * count); //20
	memset(pReturn -> pData, 0, sizeof(ArrayList) * count); //21

	return pReturn;
}

int addListData(ArrayList* pList, int position, int data)
{
	int i = 0;
	for(i = pList -> currentCount - 1; i >= position; i--) {
		pList -> pData[i + 1] = pList -> pData[i]; //자료를 오른쪽으로 한 칸씩 이동
	}
	pList -> pData[position].data = data; //실제 자료 추가
	pList -> currentCount++; //현재 저장된 자료 개수를 1 증가

	return 0;
}

int removeListData(ArrayList* pList, int position)
{
	int i = 0;
	for(i = position; i < pList -> currentCount - 1; i++) {
		pList -> pData[i] = pList -> pData[i+1]; //자료 제거 이후 후처리 과정
	}
	pList -> currentCount--; //모든 자료 이동이 끝난 후 마지막 원소 없애기
	return 0;
}

int getListData(ArrayList* pList, int position)
{
	return pList -> pData[position].data;
}

void deleteList(ArrayList* pList)
{
	free(pList -> pData);
	free(pList);
}

int main(int argc, char *argv[])
{
	ArrayList *pList = NULL;
	int value = 0;
	
	pList = createList(5);     //Step-1
	addListData(pList, 0, 10); //Step-2 
	addListData(pList, 1, 20); //Step-3
	addListData(pList, 0, 30); //Step-4

	value = getListData(pList, 1); //Step-5
	printf("위치: %d, 값: %d\n", 1, value);

	removeListData(pList, 0); //Step-6
	deleteList(pList); //Step-7

	return 0;
}