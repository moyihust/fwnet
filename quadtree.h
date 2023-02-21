//
// Created by 14413 on 2023/1/25.
//
#ifndef quadtree
#define quadtree
#include <cstdio>
#include <cmath>
#include <cstring>

typedef struct point {
    int x, y;
    double sign;
    char type[8];
    int num;
} point;

void Pointcopy(point &a, point &b)  //��b����a
{
    a.x = b.x;
    a.y = b.y;
    return;
}

point pointCreate(int x, int y,char t[8],int num,double power)  //�����ڵ�����
{
    point pos;
    pos.x = x;
    pos.y = y;
    strcpy(pos.type,t);
    pos.num=num;
    pos.sign=power;
    return  pos;
}

typedef struct boundary {
    double x;   //���ĺ�����
    double y;   //����������
    double w;   //���
    double h;   //����
} boundary;

boundary createBoundary(double x, double y, double w, double h)        //�����߽�
{
    boundary bund;
    bund.x = x;
    bund.y = y;
    bund.w = w;
    bund.h = h;
    return bund;
}

void boundarycopy(boundary &dest, boundary &sou)   //sou->dest
{
    dest.x = sou.y;
    dest.y = sou.y;
    dest.w = sou.w;
    dest.h = sou.h;
}

typedef struct Quadtree {
    bool divided;       //�Ƿ���    
    boundary bj;
    point points[4];     //��ǰ����Ľڵ�
    int length;     //��ǰ��վ
    int captical;   //��ǰ�ڵ���������
    char type[5];
    struct Quadtree *southWest;     //���ϵ��ӽڵ�
    struct Quadtree *southEast;     //���ϵ��ӽڵ�
    struct Quadtree *northWest;     //�������ӽڵ�
    struct Quadtree *northEast;     //�������ӽڵ�
} Quadtree, *Qt;
bool Qtinsert(Qt tree, point ins);
Qt createTree(boundary boundary1, int n) // �����ڵ�,���ݱ߽�ͳ����������ڵ�
{
    auto t = (Qt) malloc(sizeof(Quadtree));
    t->bj = boundary1;
    t->length = 0;
    t->captical = n;
    t->divided = false;
    t->southWest = nullptr;
    t->southEast = nullptr;
    t->northWest = nullptr;
    t->northEast = nullptr;
    return t;
}

bool contain(boundary t, point n) {
    return (n.x > t.x - t.w && n.x < t.x + t.w && n.y > t.y - t.h && n.y < t.y + t.h);
}

// *TODO divided tree
void subdivide(Qt tree) {
    int n = tree->captical;
    double x = tree->bj.x;
    double y = tree->bj.y;
    double w = tree->bj.w / 2;
    double h = tree->bj.h / 2;


    boundary nwb = createBoundary(x - w, y + h, w, h);
    tree->northWest = createTree(nwb, n);
    boundary neb = createBoundary(x + w, y + h, w, h);
    tree->northEast = createTree(neb, n);
    boundary swb = createBoundary(x - w, y - h, w, h);
    tree->southWest = createTree(swb, n);
    boundary seb = createBoundary(x + w, y - h, w, h);
    tree->southEast = createTree(seb, n);
    tree->divided = true;

}
int whereis(Qt tree,point ins)
{
    if(contain(tree->southWest->bj,ins))
        return 0;
    else if(contain(tree->northWest->bj,ins))
        return 1;
    else if(contain(tree->southEast->bj,ins))
        return 2;
    else if(contain(tree->northEast->bj,ins))
        return 3;
}
void replace(Qt tree)
{
    for(int i=0;i<tree->length;i++)
    {
        switch(whereis(tree,tree->points[i]))
        {
            case 0:
                Qtinsert(tree->southWest,tree->points[i]);
                break;
            case 1:
                Qtinsert(tree->northWest,tree->points[i]);
                break;
            case 2:
                Qtinsert(tree->southEast,tree->points[i]);
                break;
            case 3:
                Qtinsert(tree->northEast,tree->points[i]);
                break;
        };
    }
    tree->length=0;
}
bool Qtinsert(Qt tree, point ins) {
    if (!contain(tree->bj, ins)) {
        return false;
    }
    if (tree->length < tree->captical&&!tree->divided) {
        tree->points[tree->length] = ins;
        tree->length++;
        return true;
    }else {
        if (!tree->divided) {
            subdivide(tree);
            replace(tree);
        }
        if (Qtinsert(tree->northEast, ins) || Qtinsert(tree->southEast, ins) || Qtinsert(tree->northWest, ins) ||
            Qtinsert(tree->southWest, ins)) {
            return true;
        }
    }
    return false;
}
void pointprintf(point out)         //��ӡ��վ��Ϣ
{
    printf("����x=%d,y=%d,���%d,����Ϊ%s���źŹ���Ϊ%lf\n",out.x,out.y,out.num,out.type,out.sign);
}
void findmaxnw(Qt tree)             //�ҵ��������Ľڵ�
{
    Qt temp=tree;
    while(temp->northWest)
    {
        temp=temp->northWest;
    }
    for(int i=0;i<temp->length;i++)
    {
        pointprintf(temp->points[i]);
    }
}

void findmaxse(Qt tree)             //�ҵ���ϱߵĽڵ�
{
    Qt temp=tree;
    while(temp->southEast)
    {
        temp=temp->southEast;
    }
    for(int i=0;i<temp->length;i++)
    {
        pointprintf(temp->points[i]);
    }
}
#endif