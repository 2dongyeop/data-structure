#ifndef _EXPRLINKEDSTACK_
#define _EXPRLINKEDSTACK_

typedef enum PrecedenceType {
    lparen, rparen, multiply, divide, plus, minus, operand
    //여는 괄호, 닫는 괄호, 곱하기, 나누기, 더하기, 빼기, 피연산자
} Precedence;

typedef struct ExprTokenType
{
    double value;
    Precedence type;
} ExprToken;

typedef struct LinkedStackNodeType 
{
    ExprToken data;
    struct LinkedStackNodeType* pLink;
} LinkedStackNode;

typedef struct LinkedStackType
{
    int currentCount;
    LinkedStackNode* pTop;
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, ExprToken data);
int isLinkedStackEmpty(LinkedStack* pStack);
LinkedStackNode* popLS(LinkedStack* pStack);
LinkedStackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
void displayLinkedStack(LinkedStack *pStack);

#endif