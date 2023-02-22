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
bool Qtinsert(Qt tree, point ins);
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

bool contain(boundary t, int x ,int y) {
    return (x > t.x - t.w && x < t.x + t.w && y > t.y - t.h && y < t.y + t.h);
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
    if(contain(tree->southWest->bj,ins.x,ins.y))
        return 0;
    else if(contain(tree->northWest->bj,ins.x,ins.y))
        return 1;
    else if(contain(tree->southEast->bj,ins.x,ins.y))
        return 2;
    else if(contain(tree->northEast->bj,ins.x,ins.y))
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
    if (!contain(tree->bj, ins.x,ins.y)) {
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
void pointprintf(point out)         //打印基站信息
{
    printf("坐标x=%d,y=%d,编号%d,类型为%s，信号功率为%lf\n",out.x,out.y,out.num,out.type,out.sign);
}
void findmaxnw(Qt tree)             //找到最西北的节点
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

void findmaxse(Qt tree)             //找到最东南边的节点
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
//max of four double number
/*double maxoffour(double a,double b,double c,double e)
{
    if(a<b)a=b;
    if(a<c)a=c;
    if(a<e)a=e;
    return a;
}
typedef  struct receiver        //接收器数据
{
    double xs,ys,xe,ye;         //开始位置和终止位置
    int sh,sm,num;      //开始小时，开始分钟 编号
    double speed;
}receiver;
receiver receiverInit(double xs, double ys , double xe, double ye , int sh, int sm, double speed,int num) //初始化接收器
{
    receiver time;
    time.xs=xs;
    time.ys=ys;
    time.xe=xe;
    time.ye=ye;
    time.sh=sh;
    time.sm=sm;
    time.speed=speed;
    time.num=num;
    return  time;
}
double getCitySign(double x,double y,point sou)
{
    return sou.sign*(90000/(pow(sou.x-x,2)+pow(sou.y-y,2)));
}
double getHighroad(double x,double y,point sou)
{
    return sou.sign*(25000000/(pow(sou.x-x,2)+pow(sou.y-y,2)));
}
double getvilliage(double x,double y,point sou)
{
    return sou.sign*(1000000/(pow(sou.x-x,2)+pow(sou.y-y,2)));
}
Qt searchtree(Qt tree,double x,double y)
{
    if (tree->southEast->southEast== nullptr)
        return tree;
    if(contain(tree->southEast->bj,x,y))
        searchtree(tree->southEast,x,y);
    else if(contain(tree->southWest->bj,x,y))
        searchtree(tree->southWest,x,y);
    else if(contain(tree->northWest->bj,x,y))
        searchtree(tree->northWest,x,y);
    else if(contain(tree->northEast->bj,x,y))
        searchtree(tree->northEast,x,y);
}*/

#endif