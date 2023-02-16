//
// Created by 14413 on 2023/1/25.
//
#include "stdio.h"
#include "math.h"
#include "string.h"
struct point//位置
{
    int x;
    int y;
};
typedef struct point point;
typedef struct Node//节点
{
    point pos;//位置变量
    char type[4];       //信号强度
    int num;        //基站编号
    int power;      //基站功率
} Node;
typedef struct Quad
{
    Node *n;
    struct Quad *netree;
    struct Quad *nwtree;
    struct Quad *setree;
    struct Quad *swtree;
}Quad;
typedef Quad * Findtree;
Findtree CreateTree()       //创建根节点
{
    auto t=(Findtree) malloc(sizeof (Quad));
    t->n=nullptr;
    t->netree=nullptr;
    t->nwtree=nullptr;
    t->setree=nullptr;
    t->swtree=nullptr;
    return t;
}
