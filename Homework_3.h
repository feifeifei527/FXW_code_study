#ifndef _HOMEWORk_3
#define _HOMEWORK_3

typedef int ElemType;
enum Status
{
    OK,
    ERROR
};

typedef struct LNode
{
    ElemType data;      // 数据域
    ElemType exp;       // 指数
    ElemType coef;      // 系数
    struct LNode *next; // 指向下一个节点
    struct LNode *pri;  // 指向上一个节点
} *LinkList;

//modified
#endif _HOMEWORK_3