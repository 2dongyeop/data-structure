#include <stdio.h>
#include <stdlib.h>

#include "bintree.h"

BinTree* createExampleBinTree();
void preorderTraversalRecursiveBinTree(BinTree *pBinTree);
void inorderTraversalRecursiveBinTree(BinTree *pBinTree);
void postorderTraversalRecursiveBinTree(BinTree *pBinTree);
int main(int argc, char *argv[])
{
    BinTree *pBinTree = createExampleBinTree();
    if (pBinTree != NULL) {
        printf("전위 순회 결과: ");
        preorderTraversalRecursiveBinTree(pBinTree);
        printf("중위 순회 결과: ");
        inorderTraversalRecursiveBinTree(pBinTree);
        printf("후위 순회 결과: ");
        postorderTraversalRecursiveBinTree(pBinTree);

        deleteBinTree(pBinTree);
    }

    return 0;
} 

//52번째
void preorderTraversalRecursiveBinTreeNode(BinTree *pNode) 
{
    if (pRootNode != NULL) {
        printf("%c", pRootNode->data);
        preorderTraversalRecursiveBinTree(pNode->pLeftChild);
        preorderTraversalRecursiveBinTree(pNode->pRightChild);
    }
}
void preorderTraversalRecursiveBinTree(BinTree *pBinTree) 
{
    if (pBinTree != NULL) {
        preorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}
void inorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode)
{
    if (pNode != NULL) {
        inorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);
        printf("%c ", pRootNode->data);
        inorderTraversalRecursiveBinTreeNode(pNode->pRightChild);
    }
}
void inorderTraversalRecursiveBinTree(BinTree *pBinTree)
{
    if (pBinTree != NULL) {
        inorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}
void postorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode)
{
    if (pNode != NULL) {
        postorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);
        postorderTraversalRecursiveBinTreeNode(pNode->pRightChild);
        printf("%c ", pRootNode->data);

    }
}
void postorderTraversalRecursiveBinTree(BinTreeNode *pBinTree)
{
    if (pBinTree != NULL) {
        postorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}