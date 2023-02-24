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
    return (x >= t.x - t.w && x <= t.x + t.w && y >= t.y - t.h && y <= t.y + t.h);
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
double maxoffour(double a,double b,double c,double e)
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
double distance(double x1,double y1,double x2,double y2)        //返回距离的平方
{
    return (pow(x1-x2,2)+pow(y1-y2,2));
}
double getSignpower(double x,double y,point sou)
{
    if(!strcmp("城区",sou.type))
        return sou.sign*(90000/ distance(x,y,sou.x,sou.y));
    else if(!strcmp("乡镇",sou.type))
        return sou.sign*(1000000/distance(x,y,sou.x,sou.y));
    else if(!strcmp(sou.type,"高速"))
        return sou.sign*(25000000/distance(x,y,sou.x,sou.y));
}

Qt searchtree(Qt tree,double x,double y)
{
    if (tree->southEast== nullptr)
        return tree;
    if(contain(tree->southEast->bj,x,y))
        searchtree(tree->southEast,x,y);
    else if(contain(tree->southWest->bj,x,y))
        searchtree(tree->southWest,x,y);
    else if(contain(tree->northWest->bj,x,y))
        searchtree(tree->northWest,x,y);
    else searchtree(tree->northEast,x,y);
}
//两个边界是否相交
bool isoverlaps(boundary a,boundary b)
{
    return (fabs(a.x-b.x)< a.w+b.w)&&(fabs(a.y-b.y)<a.h+b.h);
}

//找到当前节点内的最小矩形，
boundary findMaxboundary(Qt tree,double x,double y)
{
    Qt temp=searchtree(tree,x,y);
    double min=999999999999,dt,ax,ay;
    for(int i=0;i<temp->length;i++)
    {
        if(min> (dt=distance(temp->points[i].x,temp->points[i].y,x,y)))
        {
            min=dt;
            ax=temp->points[i].x;
            ay=temp->points[i].y;
        }
    }
    boundary minSquar= createBoundary(ax,ay,sqrt(min), sqrt(min));
    return minSquar;
}
//找到最小矩形中的点
double findMaxpoint(Qt tree,boundary mins,point ans[30],int &n_ans)
{
//   递归结束条件
    if(tree->northWest== nullptr&& isoverlaps(mins,tree->bj))
    {
        for(int i=0;i<tree->length;i++)
        {
            if(contain(mins,tree->points[i].x,tree->points[i].y))
            {
                ans[n_ans]=tree->points[i];
                n_ans++;
            }
        }
        return 0;
    }else if(tree->northWest== nullptr&& !isoverlaps(mins,tree->bj))
    {
        return 0;
    }
    else
    {
        if(isoverlaps(mins,tree->northWest->bj))
            findMaxpoint(tree->northWest,mins,ans,n_ans);
        else if(isoverlaps(mins,tree->northEast->bj))
            findMaxpoint(tree->northEast,mins,ans,n_ans);
        else if(isoverlaps(mins,tree->southWest->bj))
            findMaxpoint(tree->southWest,mins,ans,n_ans);
        else if(isoverlaps(tree->southEast->bj,mins))
            findMaxpoint(tree->southEast,mins,ans,n_ans);
    }
}

/*
读入文件
输入:receiver 类型
*/
int ydinput(receiver move[])
{
    FILE *yd= fopen("yd001.txt","r");
    if(yd== nullptr)
    {
        printf("文件打开失败");
        return -1;
    }
    int i=0;
    while(fscanf(yd,"%lf %lf %lf %lf %lf %d %d %d",&move[i].xs,&move[i].ys,&move[i].xe,&move[i].ye,&move[i].speed,&move[i].sh,&move[i].sm,&move[i].num))
    {
        i++;
    }
    printf("文件读入成功，成功读入%d行数据\n",i);
    return 1;
}
int movingWithoutfake(Qt city,Qt country,Qt highway,receiver move[])
{
    int i=0;
    double dx,dy;//每个时间段移动的x，y方向上的距离
    double xnow,ynow;//当前时间段的坐标
    int durmins,dursec;//每段经历过的时间
    double rangxkm,rangykm;//距离的平方
    double ticks;//当前秒数
    int numbef,num;
    int timenowh,timeNowmin;
    if (move[i].speed==0)printf("未输入数据");
    else while(move[i].speed!=0)
        {
            printf("/********第%d段移动*****/",i+1);
            rangxkm=pow((move[i].xe-move[i].xs)/1000,2);
            rangykm=pow((move[i].ye-move[i].ys)/1000,2);
            durmins=(sqrt(rangykm+rangxkm)/move[i].speed)*60;
            dursec=durmins*60;
            dx=(move[i].xe-move[i].xs)/dursec;
            dy=(move[i].xe-move[i].xs)/dursec;
            timenowh=move[i].sh;timeNowmin=move[i].sm;
            xnow=move[i].xs,ynow=move[i].ys;

        }
}


#endif