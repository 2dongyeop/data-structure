#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct LinkedListNodeType {
	int data;                        //int형 정수를 자료로 저장하는 노드
	struct LinkedListNodeType *pLink;    //다음 노드의 연결 정보를 저장
} LinkedListNode;

typedef struct LinkedListType {
	int currentCount;             //현재 노드 개수를 저장
	LinkedListNode headerNode;    //헤더 노드
} LinkedList;

LinkedList *createLinkedList() {
	LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
	memset(pReturn, 0, sizeof(LinkedList));   //할당된 메모리를 0으로 초기화
	return pReturn;
}

int getLinkedListData(LinkedList *pList, int position) {
	int i = 0;
	
	LinkedListNode *pCurrentNode = &(pList->headerNode);
	for (i = 0; i <= position; i++) {
		pCurrentNode = pCurrentNode->pLink;
	}
	
	return pCurrentNode->data;
}
 
int addLinkedListData(LinkedList *pList, int position, int data) {
	int i = 0;
	LinkedListNode *pNewNode = NULL;
	LinkedListNode *pPreNode = NULL;
	
	pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	pNewNode->data = data;
	
	pPreNode = &(pList->headerNode);
	for (i = 0; i < position; i++) {
		pPreNode = pPreNode->pLink;      //새로운 자료를 추가할 위치로 이동
	}

	pNewNode->pLink = pPreNode->pLink; //다음 노드의 처리
	pPreNode->pLink = pNewNode;        //이전 노드의 처리
	pList->currentCount++;             //현재 노드 개수 1 증가
	return 0;
}

int removeLinkedListData(LinkedList *pList, int position) {
	int i = 0;
	LinkedListNode *pDelNode = NULL;
	LinkedListNode *pPreNode = NULL;
	
	pPreNode = &(pList->headerNode);
	for (i = 0; i < position; i++) {
		pPreNode = pPreNode->pLink;
	}
	
	pDelNode = pPreNode->pLink;          //(전처리) 제거하려는 노드 지정
	pPreNode->pLink = pDelNode->pLink;   //이전 노드의 처리

	free(pDelNode);                      //제거 노드의 메모리 해제
	pList->currentCount--;               //현재 노드 개수 1 감소
	return 0;
}

void deleteLinkedList(LinkedList *pList) {
	LinkedListNode *pDelNode = NULL;
	LinkedListNode *pPreNode = pList->headerNode.pLink;
	while(pPreNode != NULL) {
		pDelNode = pPreNode;
		pPreNode = pPreNode->pLink;
		
		free(pDelNode);
	}

	free(pList);
}

int getLinkedListLength(LinkedList *pList) {
	if (NULL != pList) {
		return pList->currentCount++;
	}
	return 0;
}

void iterateLinkedList(LinkedList *pList)
{
	int count = 0;
	LinkedListNode* pNode = NULL;
	
	pNode = pList->headerNode.pLink;
	while(pNode != NULL) {
		printf("[%d],%d\n", count, pNode->data); //로직 처리 부분: 자료를 출력
		count++;

		pNode = pNode->pLink;
	}
	printf("노드 개수 : %d\n", count);
}

int main(int argc, char *argv[]) {
	LinkedList *pList = createLinkedList();
    int i = 0;
	
    bool run = true;
    int count = 0;
    double sum = 0;
    float avg = 0;
  
    while(run) {
		float input = 0.0;
	
		printf("%d번째 점수는(-1을 입력하면 끝납니다)? ",(count + 1));
		scanf("%f", &input);

		if(input == (-1)) {
			if(count == 0) {
				printf("1명 이상의 점수를 입력해야 합니다.");
			}
			break;
		} 
		else {
			addLinkedListData(pList, count, input);
			count++; 
		}
    }
    for(i = 0; i < getLinkedListLength(pList); i++) {
        sum += getLinkedListData(pList, i);
    }
    avg = sum / count;
    printf("%d명의 평균 : %f", count, avg);

    deleteLinkedList(pList);            //리스트 자체를 삭제
	return 0;
}