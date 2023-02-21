//
// Created by 14413 on 2023/1/25.
//
#ifndef quadtree
#define quadtree
#include "stdio.h"
#include "math.h"
#include "string.h"

typedef struct point {
    int x, y;
    double sign;
    char type[8];
    int num;
} point;

void Pointcopy(point &a, point &b)  //将b付给a
{
    a.x = b.x;
    a.y = b.y;
    return;
}

point pointCreate(int x, int y,char t[8],int num,double power)  //创建节点坐标
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
    double x;   //中心横坐标
    double y;   //中心纵坐标
    double w;   //宽度
    double h;   //长度
} boundary;

boundary createBoundary(double x, double y, double w, double h)        //创建边界
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
    bool divided;       //是否拆分    
    boundary bj;
    point points[4];     //当前区域的节点
    int length;     //当前基站
    int captical;   //当前节点的最大数量
    char type[5];
    struct Quadtree *southWest;     //西南的子节点
    struct Quadtree *southEast;     //东南的子节点
    struct Quadtree *northWest;     //西北的子节点
    struct Quadtree *northEast;     //东北的子节点
} Quadtree, *Qt;

Qt createTree(boundary boundary1, int n) // 创建节点,根据边界和承载量建立节点
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

bool Qtinsert(Qt tree, point ins) {
    if (!contain(tree->bj, ins)) {
        return false;
    }
    if (tree->length < tree->captical) {
        tree->points[tree->length] = ins;
        tree->length++;
        return true;
    }else {
        if (!tree->divided) {
            subdivide(tree);
        }
        if (Qtinsert(tree->northEast, ins) || Qtinsert(tree->southEast, ins) || Qtinsert(tree->northWest, ins) ||
            Qtinsert(tree->southWest, ins)) {
            return true;
        }
    }
    return false;
}



#endif