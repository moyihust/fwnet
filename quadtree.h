//
// Created by 14413 on 2023/1/25.
//
#include "stdio.h"
#include "math.h"
#include "string.h"
struct point//λ��
{
    int x;
    int y;
};
typedef struct point point;
typedef struct Node//�ڵ�
{
    point pos;//λ�ñ���
    char type[4];       //�ź�ǿ��
    int num;        //��վ���
    int power;      //��վ����
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
Findtree CreateTree()       //�������ڵ�
{
    auto t=(Findtree) malloc(sizeof (Quad));
    t->n=nullptr;
    t->netree=nullptr;
    t->nwtree=nullptr;
    t->setree=nullptr;
    t->swtree=nullptr;
    return t;
}
