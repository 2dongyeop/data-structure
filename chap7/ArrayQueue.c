#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayQueueNodeType
{
    char data;
} ArrayQueueNode;

typedef struct ArrayQueueType
{
    int maxCount;
    int currentCount;
    int front;
    int rear;
    ArrayQueueNode *pData;
} ArrayQueue;

int isArrayQueueFull(ArrayQueue* pQueue);
int isArrayQueueEmpty(ArrayQueue* pQueue);

ArrayQueue* createArrayQueue(int size)
{
    ArrayQueue *pReturn = NULL;
    pReturn = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    memset(pReturn, 0, sizeof(ArrayQueue));
    pReturn->maxCount = size;
    pReturn->front = -1;
    pReturn->rear = -1;

    pReturn->pData = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode)* size);
    memset(pReturn->pData, 0, sizeof(ArrayQueueNode)*size);

    return pReturn;
}

int enqueueAQ(ArrayQueue* pQueue, char data)
{
    int ret = 0;

    if(pQueue != NULL) {
        if (isArrayQueueFull(pQueue) == 0)
        {
            pQueue->rear++;
            pQueue->pData[pQueue->rear].data = data;
            pQueue->currentCount;
            ret = 1;
        }
        else {
            printf("오류, 큐가 가득 찼습니다, enqueueAQ()\n");
        }
    }

    return ret;
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
    int ret = 0;

    if(pQueue != NULL) {
        if (pQueue->currentCount == pQueue->maxCount
            || pQueue->rear == pQueue->maxCount -1)
        {
            ret = 1;
        }
    }

    return ret;
}