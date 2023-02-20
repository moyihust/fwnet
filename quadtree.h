//
// Created by 14413 on 2023/1/25.
//
#include "stdio.h"
#include "math.h"
#include "string.h"
typedef struct point
{
    int x,y;
    double sign;
    char type[8];
    int num;
}point;
point Pointcopy(point &a,point &b)  //将b付给a
{
    a.x=b.x;
    a.y=b.y;
}
point pointCreate(int x, int y)  //创建节点坐标
{
    point pos;
    pos.x=x;
    pos.y=y;
}
typedef struct boundary
{
    double x;   //中心横坐标
    double y;   //中心纵坐标
    double w;   //宽度
    double h;   //长度
}boundary;
boundary createBoundary(double x,double y,double w,double h)        //创建边界
{
    boundary bund;
    bund.x=x;
    bund.y=y;
    bund.w=w;
    bund.h=h;
    return bund;
}
void boundarycopy(boundary &dest,boundary &sou)   //sou->dest
{
    dest.x=sou.y;
    dest.y=sou.y;
    dest.w=sou.w;
    dest.h=sou.h;
}
typedef struct Quadtree
{
    bool divided;       //是否拆分    
    boundary bj;
    point points[4];     //当前区域的节点
    int n_point;        //当前节点的数量
    char type[5];
    struct Quadtree *southWest;     //西南的子节点
    struct Quadtree *southEast;     //东南的子节点
    struct Quadtree *northWest;     //西北的子节点
    struct Quadtree *northEast;     //东北的子节点
}Quadtree,*Qt;
Qt CreateTree(boundary boundary1) // 创建节点
{
    auto t = (Qt)malloc(sizeof(Quadtree));
    t->bj=boundary1;
    t->n_point=0;
    t->divided=false;
    t->southWest=nullptr;
    t->southEast=nullptr;
    t->northWest=nullptr;
    t->northEast=nullptr;
}
bool qtcontain(boundary t,point n)
{
    return (n.x > t.x - t.w && n.x < t.x + t.w && n.y > t.y - t.h && n.y < t.y + t.h);
}
// *TODO divided tree
void subdivide(Qt tree) 
{
    double x=tree->bj.x;
    double y=tree->bj.y;
    double w=tree->bj.w/2;
    double h=tree->bj.h/2;

    
    boundary nwb=createBoundary(x-w,y+h,w,h);
    tree->northWest=CreateTree(nwb);
    boundary neb=createBoundary(x+w,y+h,w,h);
    tree->northEast=CreateTree(neb);
    boundary swb=createBoundary(x-w,y-h,w,h);
    tree->southWest=CreateTree(swb);
    boundary seb=createBoundary(x+w,y-h,w,h);
    tree->southEast=CreateTree(seb);
    tree->divided=true;

}
// *TODO Qt_insist

