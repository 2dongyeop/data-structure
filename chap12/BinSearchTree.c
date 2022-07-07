#include <stdio.h>
#include <stdlib.h>

typedef struct BinSearchTreeNodeType {
    int key;
    char value;

    struct BinSearchTreeNodeType *pLeftChild;
    struct BinSearchTreeNodeType *pRightChild;
} BinSearchTreeNode;

typedef struct BinSearchTreeType {
    BinSearchTreeNode *pRootNode;
} BinSearchTree;

BinSearchTree *createBinSearchTree() {
    BinSearchTree *pReturn = NULL;
    pReturn = (BinSearchTree *) malloc(sizeof(BinSearchTree));
    if (pReturn != NULL) {
        pReturn->pRootNode = NULL;
    } else {
        printf("오류, 메모리 할당");
    }

    return pReturn;
}

BinSearchTreeNode *searchBTS(BinSearchTree *pBinSearchTree, int key) {
    BinSearchTreeNode *pReturn = NULL;

    if (pBinSearchTree == NULL) {
        return NULL;
    }

    pReturn = pBinSearchTree->pRootNode;
    while (pReturn != NULL) {
        if (key == pReturn->key) {
            break;
        } else if (key < pReturn->key) {
            pReturn = pReturn->pLeftChild;
        } else {
            pReturn = pReturn->pRightChild;
        }
    }

    return pReturn;
}

int getParentNode(BinSearchTreeNode *pCurrentNode, int key, BinSearchTreeNode **ppResult) {
    int ret = 1;
    BinSearchTree *pParentNode = NULL;

    while (pCurrentNode != NULL) {
        if (key == pCurrentNode->key) {
            printf("오류, 중복된 키");
            ret = 0;
            return ret;
        } else if (key < pCurrentNode->key) {
            pParentNode = pCurrentNode;
            pCurrentNode = pCurrentNode->pLeftChild;
        } else {
            pParentNode = pCurrentNode;
            pCurrentNode = pCurrentNode->pRightChild;
        }
    }
    if (1 == ret) {
        *ppResult = pParentNode;
    }

    return ret;
}

BinSearchTreeNode *createNewBinSearchTreeNode(int key, char value) {
    BinSearchTreeNode *pNewNode = NULL;

    pNewNode = (BinSearchTreeNode *) malloc(sizeof(BinSearchTreeNode));
    if (pNewNode != NULL) {
        pNewNode->key = key;
        pNewNode->value = value;
        pNewNode->pLeftChild = NULL;
        pNewNode->pRightChild = NULL;
    }

    return pNewNode;
}

void insertNewBinSearchTreeNode(BinSearchTree *pBinSearchTree,
                                BinSearchTreeNode *pParentNode, BinSearchTreeNode *pNewNode) {
    if (pParentNode == NULL) {
        pBinSearchTree->pRootNode = pNewNode;
    } else {
        if (pNewNode->key < pParentNode->key) {
            pParentNode->pLeftChild = pNewNode;
        } else {
            pParentNode->pRightChild = pNewNode;
        }
    }
}

BinSearchTreeNode *searchWithParentNodeBST(BinSearchTree *pBinSearchTree,
                                           int key, BinSearchTreeNode **ppParentNode) {
    BinSearchTreeNode *pReturn = NULL;
    BinSearchTreeNode *pParentNode = NULL;

    if (pBinSearchTree == NULL) {
        return NULL;
    }
    pReturn = pBinSearchTree->pRootNode;

    while (pReturn != NULL) {
        if (key == pReturn->key) {
            break;
        }
        pParentNode = pReturn;

        if (key < pReturn->key) {
            pReturn = pReturn->pLeftChild;
        } else {
            pReturn = pReturn->pRightChild;
        }
    }

    if (NULL != ppParentNode) {
        *ppParentNode = pParentNode;
    }

    return pReturn;
}

void deleteNodeNoChild(BinSearchTree *pBinSearchTree,
                       BinSearchTreeNode *pParentNode, BinSearchTreeNode *pDelNode) {
    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == pDelNode) {
            pParentNode->pLeftChild = NULL;
        } else {
            pParentNode->pRightChild = NULL;
        }
    } else {
        pBinSearchTree->pRootNode = NULL;
    }
}

void deleteNodeOneChild(BinSearchTree *pBinSearchTree,
                        BinSearchTreeNode *pParentNode, BinSearchTreeNode *pDelNode) {
    BinSearchTreeNode *pChildNode = NULL;

    if (pDelNode->pLeftChild != NULL) {
        pChildNode = pDelNode->pLeftChild;
    } else {
        pChildNode = pDelNode->pRightChild;
    }

    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == pDelNode) {
            pParentNode->pLeftChild = pChildNode;
        } else {
            pParentNode->pRightChild = pChildNode;
        }
    } else {
        pBinSearchTree->pRootNode = pChildNode;
    }
}

void deleteNodeTwoChilden(BinSearchTree *pBinSearchTree,
                          BinSearchTreeNode *pParentNode, BinSearchTreeNode *pDelNode) {
    BinSearchTreeNode *pPredecessor = NULL, *pSuccessor = NULL;

    pPredecessor = pDelNode;
    pSuccessor = pDelNode->pLeftChild;
    while (pSuccessor->pRightChild != NULL) {
        pPredecessor = pSuccessor;
        pSuccessor = pSuccessor->pRightChild;
    }

    pPredecessor->pRightChild = pSuccessor->pLeftChild;
    pSuccessor->pLeftChild = pDelNode->pLeftChild;
    pSuccessor->pRightChild = pDelNode->pRightChild;

    if (pParentNode != NULL) {
        if (pParentNode->pLeftChild == pDelNode) {
            pParentNode->pLeftChild = pSuccessor;
        } else {
            pParentNode->pRightChild = pSuccessor;
        }
    } else {
        pBinSearchTree->pRootNode = pSuccessor;
    }
}

int deleteDataBST(BinSearchTree *pBinSearchTree, int key) {
    int ret = 1;
    BinSearchTreeNode *pDelNode = NULL, *pParentNode = NULL;

    if (pBinSearchTree == NULL) {
        ret = 0;
        return ret;
    }
    pDelNode = searchWithParentNodeBST(pBinSearchTree, key, &pParentNode);

    if (pDelNode == NULL) {
        printf("오류, 존재하지 않는 키");
        ret = 0;
        return ret;
    }

    if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
        deleteNodeNoChild(pBinSearchTree, pParentNode, pDelNode);
    } else if (pDelNode->pLeftChild != NULL && pDelNode->pRightChild != NULL) {
        deleteNodeTwoChilden(pBinSearchTree, pParentNode, pDelNode);
    } else {
        deleteNodeOneChild(pBinSearchTree, pParentNode, pDelNode);
    }

    free(pDelNode);
    return ret;
}

void deleteBinSearchTreeInternal(BinSearchTreeNode* pTreeNode) {
    if (pTreeNode != NULL) {
        deleteBinSearchTreeInternal(pTreeNode->pLeftChild);
        deleteBinSearchTreeInternal(pTreeNode->pRightChild);
        free(pTreeNode);
    }
}

void delteBinSearchTree(BinSearchTree* pBinSearchTree) {
    if (pBinSearchTree != NULL) {
        deleteBinSearchTreeInternal(pBinSearchTree->pRootNode);
        free(pBinSearchTree);
    }
}

void displayBinSearchTre(BinSearchTreeNode *pTreeNode, int level, char type) {
    int i = 0;

    if (pTreeNode != NULL) {
        for (i = 0; i < level; i++) {
            printf("    ");
        }

        printf("-(%c)-key: %i, value-%c\n", type,
               pTreeNode->key, pTreeNode->value);

        displayBinSearchTre(pTreeNode->pLeftChild, level + 1, 'L');
        displayBinSearchTre(pTreeNode->pRightChild, level + 1, 'R');
    }
}

int main() {
    BinSearchTree *pTree = NULL;
    BinSearchTreeNode *pSearchNode = NULL;
    int key = 0;

    pTree = createBinSearchTree();
}