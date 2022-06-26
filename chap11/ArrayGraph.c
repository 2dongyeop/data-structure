#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_GRAPH_TYPE_DIRECT 0
#define ARRAY_GRAPH_TYPE_UNDIRECT 1

typedef struct ArrayGraphType {
    int graphType; //그래프의 종류 : 방향 그래프, 무방향 그래프
    int nodeCount;
    int **ppEdge;
} ArrayGraph;

ArrayGraph *createArrayGraph(int graphType, int nodeCount) {
    int i;
    ArrayGraph *pReturn = NULL;

    pReturn = (ArrayGraph *) malloc(sizeof(ArrayGraph));
    if (pReturn == NULL) return NULL;

    pReturn->graphType = graphType;
    pReturn->nodeCount = nodeCount;
    pReturn->ppEdge = (int **) malloc(sizeof(int *) * nodeCount);
    if (pReturn->ppEdge == NULL) return NULL;

    for (i = 0; i < nodeCount; i++) {
        pReturn->ppEdge[i] = (int *) malloc(sizeof(int) * nodeCount);
        if (pReturn->ppEdge[i] == NULL) return NULL; //중간에 할당된 메모리 해제 필요

        memset(pReturn->ppEdge[i], 0, sizeof(int) * nodeCount);
    }

    return pReturn;
}

int checkVertexValid(DirectArrayGraph *pGraph, int node) {
    if (pGraph != NULL && node < pGraph->nodeCount && node >= 0) {
        return 1;
    } else {
        return 0;
    }
}

int addEdgeInternalAG(ArrayGraph* pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL & checkVertexValid(pGraph, fromNode) && createArrayGraph(pGraph, toNode)) {
        pGraph->ppEdge[fromNode][toNode] = 1;
    }
    else {
        ret = -1;
    }

    return ret;
}

int addEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    ret = addEdgeInternalAG(pGraph, fromNode, toNode);
    if (0 == ret && ARRAY_GRAPH_TYPE_UNDIRECT = pGraph->graphType) {
        ret = addEdgeInternalAG(pGraph, toNode, fromNode);
    }

    return ret;
}

int removeEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        pGraph->ppEdge[fromNode][toNode] = 0;
    } else {
        ret = -1;
    }

    return ret;
}

int removeEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    ret = removeEdgeInternalAG(pGraph, fromNode, toNode);
    if (0 == ret && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = removeEdgeInternalAG(pGraph, toNode, fromNode);
    }

    return ret;
}

int getEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        ret = pGraph->ppEdge[fromNode][toNode];
    }

    return ret;
}

void displayGraphDAG(ArrayGraph* pGraph) {
    int i = 0, j = 0;
    int count = 0;

    if (pGraph != NULL) {
        count = pGraph->nodeCount;
        for (i = 0; i < count; i++) {
            for (j = 0; j < count; j++) {
                printf("%d ", getEdgeDAG(pGraph, i, j));
            }
            printf("\n");
        }
    }
}

void deleteGraphDAG(ArrayGraph* pGraph) {
    int i = 0;

    if (pGraph != NULL) {
        for (i = 0; i < pGraph->nodeCount; i++) {
            free(pGraph->ppEdge[i]);
        }
        free(pGraph->ppEdge);
        free(pGraph);
    }
}

int main(int argc, char *argv[]) {
    int nodeCount = 6;
    ArrayGraph *pG2 = createArrayGraph(nodeCount);

    if (pG2 != NULL) {
        addEdgeDAG(pG2, 0, 1);
        addEdgeDAG(pG2, 1, 2);
        addEdgeDAG(pG2, 2, 0);
        addEdgeDAG(pG2, 2, 3);
        addEdgeDAG(pG2, 3, 2);
        addEdgeDAG(pG2, 3, 4);
        addEdgeDAG(pG2, 4, 5);
        addEdgeDAG(pG2, 5, 3);

        printf("G2: 방향 그래프\n");
        displayGraphDAG(pG2);

        deleteGraphDAG(pG2);
    }

    return 0;
}