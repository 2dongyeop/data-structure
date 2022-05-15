#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType {
	int data;                        //int형 정수를 자료로 저장하는 노드
	struct LinkedListNode *pLink;    //다음 노드의 연결 정보를 저장
} LinkedListNode;

typedef struct LinkedListType {
	int currentCount;             //현재 노드 개수를 저장
	LinkedListNode headerNode;    //헤더 노드
} LinkedList;

LinkedList *createLinkedList() {
	LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
	if (pReturn != NULL) {
	memset(pReturn, 0, sizeof(LinkedList));   //할당된 메모리를 0으로 초기화
	}
	return pReturn;
}

int getLinkedListData(LinkedList* pList, int position) {
	int i = 0;
	
	LinkedListNode *pCurrentNode = &(pList->headerNode);
	for (i = 0; i <= position; i++) {
		pCurrentNode = pCurrentNode->pLink;
	}
	
	return pCurrentNode->data;
}
 
int addLinkedListData(LinkedList* pList, int position, int data) {
	int i = 0;
	LinkedListNode *pNewNode = NULL;
	LinkedListNode *pPreNode = NULL;
	
	pNewNode = (LinkedListNode* )malloc(sizeof(LinkedListNode));
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

int removeLinkedListData(LinkedList* pList, int position) {
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

void deleteLinkedList(LinkedList* pList) {
	LinkedListNode *pDelNode = NULL;
	LinkedListNode *pPreNode = pList->headerNode.pLink;
	while(pPreNode != NULL) {
		pDelNode = pPreNode;
		pPreNode = pPreNode->pLink;
		
		free(pDelNode);
	}

	free(pList);
}

int getLinkedListLength(LinkedList* pList) {
    iterateLinkedList(pList);    
}

void iterateLinkedList(LinkedList* pList)
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

void concatLinkedList(LinkedList* pListA, LinkedList* pListB) {
	LinkedListNode* pNodeA = NULL;
	if (pListA != NULL && pListB != NULL) {    //입력 파라미터 유효성 점검
		pNodeA = pListA->headerNode.pLink;
		while(pNodeA != NULL && pNodeA->pLink !=NULL) {
			pNodeA = pNodeA->pLink;
		}
		pNodeA->pLink = pListB->headerNode.pLink;
		pListB->headerNode.pLink = NULL;
	}
}

int main(int argc, char *argv[]) {
	int value = 0;

	LinkedList *pList = createList();
    addLinkedListData(pList, 0, 10);
	addLinkedListData(pList, 1, 0);
	addLinkedListData(pList, 1, 30);

	value = getListLength(pList);
	printf("자료의 개수: %d\n", value);

    return 0;
}