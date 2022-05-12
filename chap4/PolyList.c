#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TermType { //항을 나타내는 구조체
	double coef; //계수
	int degree;  //차수
} Term;

typedef struct LinkedListNodeType { //노드를 나타내는 구조체
	Term data;                        //구조체 Term 타입의 자료
	struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType {  //다항식을 나타내는 구조체
	int currentCount;
	LinkedListNode headerNode;
} LinkedList, PolyList;

LinkedList *createLinkedList() {
	LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
	memset(pReturn, 0, sizeof(LinkedList));   //할당된 메모리를 0으로 초기화
	return pReturn;
}

Term getLinkedListData(LinkedList* pList, int position) {
	int i = 0;

	LinkedListNode *pCurrentNode = &(pList->headerNode);
	for(i = 0; i <= position; i++) {
		pCurrentNode = pCurrentNode->pLink;
	}

	return pCurrentNode->data;
}

int addLinkedListData(LinkedList* pList, int position, Term data) {
	int i = 0;
	LinkedListNode *pNewNode = NULL;
	LinkedListNode *pPreNode = NULL;

	pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	pNewNode->data = data;

	pPreNode = &(pList->headerNode);
	for(i = 0; i < position; i++) {
		pPreNode = pPreNode->pLink;
	}

	pNewNode->pLink = pPreNode->pLink;
	pPreNode->pLink = pNewNode;
	pList->currentCount++;
	return 1;
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
	if (NULL != pList) {
		return pList->currentCount++;
	}
	return 0;
}
int addPolyNodeLast(PolyList* pList, double coef, int degree)
{
	int ret = 0, position = 0;

	Term term = {0,};
	term.coef = coef;
	term.degree = degree;

	if(pList != NULL) {
		position = pList->currentCount;
		ret = addLinkedListData(pList, position, term);
	}

	return ret;
}

void displayPolyList(PolyList* pList)
{
	int i = 0;
	LinkedListNode* pNode = NULL;
	pNode = pList->headerNode.pLink;
	if(0 == pList->currentCount) { //내용이 없는 빈 다항식인 경우
		printf("자료가 없습니다.\n");
	}
	else {
		for(i = 0; i < pList->currentCount; i++) {
			if(i > 0) {
				printf(" + ");
			}
			printf("%.1fx^%d", pNode->data.coef, pNode->data.degree);
			pNode = pNode->pLink;
		}
		printf("\n");
	}
}

PolyList* polyAdd(PolyList* pListA, PolyList* pListB)
{
	PolyList* pReturn = NULL;
	LinkedListNode *pNodeA = NULL, *pNodeB = NULL;
	double coefSum = 0;

	if(pListA != NULL && pListB != NULL) {
		pReturn = createLinkedList();
		if(pReturn == NULL) {
			printf("메모리 할당 오류, polyAdd()\n");
			return NULL;
		}

		pNodeA = pListA->headerNode.pLink;
		pNodeB = pListB->headerNode.pLink;
		while(pNodeA != NULL && pNodeB != NULL) {
			int degreeA = pNodeA->data.degree;
			int degreeB = pNodeB->daga.degree;
			if(degreeA < degreeB) {
				coefSum = pNodeA->data.coef;
				addPolyNodeLast(pReturn, coefSym, defreeA);
				pNodeA = pNodeA->pLink;
			}
			else if(degreeA == degreeB) {
		
				coefSum = pNodeA->data.coef + pNodeB->data.coef;
				addPolyNodeLast(pReturn, coefSum, degreeA);
				pNodeA = pNodeA->pLink;
				pNodeB = pNodeB->pLink;
			}
			else { 
				coefSum = pNodeB->data.coef;
				addPolyNodeLast(pReturn, coefSum, degreeB);
				pNodeB = pNodeB->pLink;
			}
		}

		while(pNodeA != NULL) {
			coefSum = pNodeA->data.coef;
			addPolyNodeLast(pReturn, coefSum, pNodeA->data.degree);
			pNodeA = pNodeA->pLink;
		}

		while(pNodeB != NULL) {
			coefSum = pNode->data.coef;
			addPolyNodeLast(pReturn, coefSum, pNodeB->data.degree);
			pNodeB = pNodeB->pLink;
		}
	}
	else
	{
		printf("오류, NULL 다항식이 전달되었습니다, polyAdd()\n");
	}
	
	return pReturn;
}

int main(int argc, char *argv[])
{
	PolyList *pListA = NULL;
	PolyList *pListB = NULL;
	PolyList *pListC = NULL;

	pListA = createLinkedList();
	pListB = createLinkedList();

	if(pListA != NULL && pListB != NULL)
	{
		//다항식 초기화
		//pListA: 7x^6 + 3x^5 + 5x^2
		//pListB: 1x^5 + 2x^4 + 4x^0
		addPolyNodeLast(pListA, 7, 6);
		addPolyNodeLast(pListA, 3, 5);
		addPolyNodeLast(pListA, 5, 2);
		displayPolyList(pListA);

		addPolyNodeLast(pListB, 1, 5);
		addPolyNodeLast(pListB, 2, 4);
		addPolyNodeLast(pListB, 4, 0);
		displayPolyList(pListB);

		pListC = polyAdd(pListA, pListb);
		if(pListC != NULL) {
			displayPolyList(pListC);
			deleteLinkedList(pListC);
		}

		deleteLinkedList(pListA);
		deleteLinkedList(pListB);
	}
	return 0;
}