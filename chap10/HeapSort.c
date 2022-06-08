#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNodeType {
    int data;
} HeapNode;

typedef struct ArrayHeapType {
    int maxCount;
    int currentCount;
    HeapNode *pData;
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap *createArrayMaxHeap(int maxCount) {
    ArrayMaxHeap *pReturn = NULL;
    if (maxCount > 0) {
        pReturn = (ArrayMaxHeap *) malloc(sizeof(ArrayMaxHeap));
        pReturn->maxCount = maxCount;
        pReturn->currentCount = 0;
        pReturn->pData = (HeapNode *) malloc(sizeof(HeapNode) * (maxCount + 1));
        memset(pReturn->pData, 0, sizeof(HeapNode) * (maxCount + 1));
    } else {
        printf("최대 원소 개수는 0보다 커야 합니다\n");
    }

    return pReturn;
}

int insertMaxHeapAH(ArrayMaxHeap *pHeap, int value) {
    int i = 0;

    if (pHeap != NULL) {
        if (pHeap->currentCount == pHeap->maxCount) {
            printf("오류, 히프가 가득 찼습니다[%d], insertMaxHeapAH()\n", pHeap->maxCount);
            return 0;
        }
        pHeap->currentCount;
        i = pHeap->currentCount;
        while ((i != 1) && (value > pHeap->pData[i / 2].data)) {
            pHeap->pData[i] = pHeap->pData[i / 2];
            i /= 2;
        }
        pHeap->pData[i].data = value;
    }

    return i;
}

HeapNode *removeMaxHeapAH(ArrayMaxHeap *pHeap) {
    HeapNode *pReturn = NULL;
    HeapNode *pTemp = NULL;
    int parent = 1, child = 2;

    if (pHeap != NULL && pHeap->currentCount > 0) {
        pReturn = (HeapNode *) malloc(sizeof(HeapNode));
        if (pReturn == NULL) {
            printf("오류, 메모리 할당, deleteMaxHeapAH()\n");
            return NULL;
        }
        pReturn->data = pHeap->pData[1].data;

        pTemp = &(pHeap->pData[pHeap->currentCount]);
        pHeap->currentCount--;

        while (child <= pHeap->currentCount) {
            if ((child < pHeap->currentCount) && pHeap->pData[child].data < pHeap->pData[child + 1].data) {
                child++;
            }

            if (pTemp->data >= pHeap->pData[child].data) {
                break;
            }

            pHeap->pData[parent] = pHeap->pData[child];
            parent = child;
            child *= 2;
        } //end-of-while
        pHeap->pData[parent] = *pTemp;
    }

    return pReturn;
}

void deleteArrayMaxHeap(ArrayMaxHeap *pHeap) {
    if (pHeap != NULL) {
        if (pHeap->pData != NULL) {
            free(pHeap->pData);
        }
        free(pHeap);
    }
}

void displayArrayHeap(ArrayMaxHeap *pHeap) {
    int i = 0;
    if (pHeap != NULL) {
        for (i = 1; i <= pHeap->currentCount; i++) {
            printf(("[%d],%d\n", i, pHeap->pData[i].data));
        }
    }
}

//히프 정렬
void heapSort(int values[], int count) {
    int i = 0;
    ArrayMaxHeap *pHeap = NULL;

    pHeap = createArrayMaxHeap(10);
    if (pHeap != NULL) {
        for (i = 0; i < count; i++) {
            insertMaxHeapAH(pHeap, values[i]);
        }

        for (i = 0; i < count; i++) {
            HeapNode *pNode = removeMaxHeapAH(pHeap);
            if (pNode != NULL) {
                values[i] = pNode->data;
                free(pNode);
            }
        }

        deleteArrayMaxHeap(pHeap);
    } else {
        printf("오류, createArrayMaxHeap() in heapSort()\n");
        return;
    }
}

void printArray(int values[], int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("%d ", values);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int values[] = {10, 50, 70, 80, 60, 20, 40, 30};

    printf("Before Sort\n");
    printArray(values, 0);

    heapSort(values, 0);

    printf("After Sort\n");
    printArray(values, 0);

    return 0;
}