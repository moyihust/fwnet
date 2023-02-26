//
// Created by 14413 on 2023/1/25.
//
#ifndef quadtree
#define quadtree
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
int n_ans;
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

bool contain(boundary t, double x ,double y) {
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
    return -1;
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

typedef  struct receiver        //����������
{
    double xs,ys,xe,ye;         //��ʼλ�ú���ֹλ��
    int sh,sm,num;      //��ʼСʱ����ʼ���� ���
    double speed;
}receiver;
double distance(double x1,double y1,double x2,double y2)        //���ؾ����ƽ��
{
    return (pow(x1-x2,2)+pow(y1-y2,2));
}
double getSignpower(double x,double y,point sou)
{
    if(!strcmp("����",sou.type))
        return sou.sign*pow(300,2)/ distance(x,y,sou.x,sou.y);
    else if(!strcmp("����",sou.type))
        return sou.sign*pow(1000,2)/distance(x,y,sou.x,sou.y);
    else if(!strcmp(sou.type,"����"))
        return sou.sign*pow(5000,2)/distance(x,y,sou.x,sou.y);
    return -1;
}

Qt searchtree(Qt tree,double x,double y)
{
    if(tree== nullptr)return tree;
    if (tree->southEast== nullptr)
        return tree;
    else if(contain(tree->southEast->bj,x,y))
        searchtree(tree->southEast,x,y);
    else if(contain(tree->southWest->bj,x,y))
        searchtree(tree->southWest,x,y);
    else if(contain(tree->northWest->bj,x,y))
        searchtree(tree->northWest,x,y);
    else searchtree(tree->northEast,x,y);
}
//�����߽��Ƿ��ཻ
bool isoverlaps(boundary a,boundary b)
{
    return (fabs(a.x-b.x)< a.w+b.w)&&(fabs(a.y-b.y)<a.h+b.h);
}

//�ҵ���ǰ�ڵ��ڵ���С���Σ�
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
    boundary minSquar= createBoundary(x,y,sqrt(min), sqrt(min));
    return minSquar;
}
//�ҵ���С�����еĵ�
double findPointinside(Qt tree, boundary mins, point ans[30])
{
//   �ݹ��������
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
            findPointinside(tree->northWest, mins, ans);
        else if(isoverlaps(mins,tree->northEast->bj))
            findPointinside(tree->northEast, mins, ans);
        else if(isoverlaps(mins,tree->southWest->bj))
            findPointinside(tree->southWest, mins, ans);
        else if(isoverlaps(tree->southEast->bj,mins))
            findPointinside(tree->southEast, mins, ans);
    }
}
//����jzmax
//�����ź����Ļ�վ���
//���룺��������x,y
point* jzmax(Qt city,Qt village,Qt highway,double x,double y)
{
    boundary bcity= findMaxboundary(city,x,y);
    point ans[100];
    findPointinside(city, bcity,ans);
    boundary mincountry= findMaxboundary(village,x,y);
    findPointinside(village, mincountry, ans);
    boundary minhighway= findMaxboundary(highway,x,y);
    findPointinside(highway,minhighway,ans);
    double maxSignpower=-1;
    int numMax=-1;
    point *max= nullptr;
    for(int i=0;i<n_ans;i++)
    {
        if(maxSignpower< getSignpower(x,y,ans[i]))
        {
            maxSignpower= getSignpower(x,y,ans[i]);
            numMax=ans[i].num;
            max=ans+i;
        }
    }
    n_ans=0;
    if(maxSignpower>=1)return max;
    else return nullptr;
}

void reInit(receiver *t,int n)
{
    for(int i=0;i<n;i++)
    {
        t[i].speed=0;
    }
}

/*
�����ļ�
����:receiver ����
*/
int ydinput(receiver move[])
{
    FILE *yd= fopen("yd001.txt","r");
    if(yd== nullptr)
    {
        printf("�ļ���ʧ��");
        return -1;
    }
    char t[8];
    fscanf(yd,"%s",t);
    int i=0;
    while(fscanf(yd,"%lf %lf %lf %lf %lf %d %d ",&move[i].xs,&move[i].ys,&move[i].xe,&move[i].ye,&move[i].speed,&move[i].sh,&move[i].sm)!=EOF&&move[i].xs>0)
    {
        i++;
    }
    printf("�ļ�����ɹ����ɹ�����%d������\n",i);
    return 1;
}
void display(point *t,int type,double x,double y,int h,int m,int sec)
{
    if(type>0&&t!= nullptr) {
        printf("��%dʱ%d��%d��,λ��(%f,%f)�������ϱ��Ϊ%d���ź�ǿ��Ϊ%f\n", h, m, sec, x, y,t->num,getSignpower(x, y, *t));
    }
    else
        printf("��%dʱ%d��%d��,λ��(%f,%f)��,����Ч�����ź�\n",h,m,sec,x,y);
}


int movingWithoutfake(Qt city,Qt country,Qt highway,receiver move[]) {
    int i = 0;
    double dx, dy;//ÿ��ʱ����ƶ���x��y�����ϵľ���
    double xnow, ynow;//��ǰʱ��ε�����
    int durmins, dursec;//ÿ�ξ�������ʱ��
    double rangxkm, rangykm;//�����ƽ��
    double ticks;//��ǰ����
    int numbef = 0, numNow;
    int timenowh, timeNowmin;
    if (move[i].speed == 0)printf("δ��������");
    else
        while (move[i].speed != 0) {
            if(i>=2)
                i=i;
            printf("/********��%d���ƶ�*****/\n", i + 1);
            rangxkm = pow((move[i].xe - move[i].xs) / 1000, 2);
            rangykm = pow((move[i].ye - move[i].ys) / 1000, 2);
            durmins = (sqrt(rangykm + rangxkm) / move[i].speed) * 60;
            dursec = durmins * 60;
            dx = (move[i].xe - move[i].xs) / dursec;
            dy = (move[i].ye - move[i].ys) / dursec;
            timenowh = move[i].sh;
            timeNowmin = move[i].sm;
            xnow = move[i].xs, ynow = move[i].ys;
            point *temp = nullptr;
            int j = 0, k = 0;
            for (j = 0; j < dursec; j++) {
                temp = jzmax(city, country, highway, xnow, ynow);
                if (temp != nullptr)numNow = temp->num;
                else numNow = -1;
                if (numbef != numNow) {
                    display(temp, numNow, xnow, ynow, timenowh, timeNowmin, ticks);
                    numbef = numNow;
                }
                ticks++;
                xnow += dx;
                ynow += dy;
                if (ticks >= 60) {
                    timeNowmin++;
                    ticks = 0;
                }
                if (timeNowmin >= 60) {
                    timenowh++;
                    timeNowmin = 0;
                }
            }
                if (move[i + 1].speed == 0)//���һ���ƶ������⴦��
                {
                    xnow = move[i].xe;
                    ynow = move[i].ye;
                    temp = jzmax(city, country, highway, xnow, ynow);
                    if (temp != nullptr)numNow = temp->num;
                    else numbef = -1;
                    display(temp, numNow, xnow, ynow, timenowh, timeNowmin, ticks);
                }
            i++;
            }
    return 0;
}




#endif