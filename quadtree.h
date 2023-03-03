//
// Created by 14413 on 2023/1/25.
//
#ifndef quadtree
#define quadtree
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
int lengthofse=0,lenthofnw=0;
int n_ans;
typedef struct point {
    int x, y;
    double sign;
    char type[8];
    int num;
} point;

void setPoint(point *t,int num)
{
    for(int i=0;i<num;i++)
    {
        t[i].x=-1;t[i].y=-1;t[i].num=-1;t[i].sign=0;
    }
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

typedef struct Quadtree {
    bool divided;       //�Ƿ���    
    boundary bj;
    point points[4];     //��ǰ����Ľڵ�
    int length;     //��ǰ��վ
    int captical;   //��ǰ�ڵ���������
    char type[5];
    struct Quadtree *father;
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
    t->father= nullptr;
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
    tree->northWest->father=tree;
    boundary neb = createBoundary(x + w, y + h, w, h);
    tree->northEast = createTree(neb, n);
    tree->northEast->father=tree;
    boundary swb = createBoundary(x - w, y - h, w, h);
    tree->southWest = createTree(swb, n);
    tree->southWest->father=tree;
    boundary seb = createBoundary(x + w, y - h, w, h);
    tree->southEast = createTree(seb, n);
    tree->southEast->father=tree;
    tree->divided = true;

}
//�жϻ�վ�ڵ�ǰ�ڵ���ĸ��ӽڵ�
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
//��ֽڵ㲢��ɢ���ӽڵ���
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
    tree->length=-1;
}
//��������ӽڵ�
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
    int t=0;
    while(temp->northWest)
    {
        for(int i=0;i<temp->length;i++)
        {
            pointprintf(temp->points[i]);
        }
        temp=temp->northWest;
    }
    printf("������������Ҷ�Ľڵ�\n");
    for(int i=0;i<temp->length;i++)
    {
        pointprintf(temp->points[i]);
    }
    if(temp->father->northEast->length<0)
        t=4+temp->father->northEast->length;
    else
        t=temp->father->northEast->length;
    printf("������������Ҷ������Ҷ\n");
    for(int i=0;i<t;i++)
    {
        pointprintf(temp->father->northEast->points[i]);
    }
    if(temp->father->southWest->length<0)
        t=4+temp->father->southWest->length;
    else
        t=temp->father->southWest->length;
    printf("������������Ҷ�ϲ���Ҷ��Ľڵ�\n");
    for(int i=0;i<t;i++)
    {
        pointprintf(temp->father->southWest->points[i]);
    }
}

Qt findmaxse(Qt tree)             //�ҵ���ϱߵĽڵ�
{
    Qt temp=tree;
    while(temp->southEast)
    {
        temp=temp->southEast;
    }
    printf("���Ƕ��ϵ���Ҷ�ڵ�Ļ�վ\n");
    for(int i=0;i<temp->length;i++)
    {
        pointprintf(temp->points[i]);
    }
    printf("���Ƕ�����Ҷ�ڵ�������Ļ�վ\n");
    for(int i=0;i<temp->father->northWest->length;i++)
    {
        pointprintf(temp->father->northWest->points[i]);
    }
    printf("���Ƕ�����Ҷ�ڵ㱱�Ļ�վ\n");
    for(int i=0;i<temp->father->northEast->length;i++)
    {
        pointprintf(temp->father->northEast->points[i]);
    }
    return temp;
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
double getSignpower(double x,double y,point sou)        //�����ź�ǿ��
{
    if(!strcmp("����",sou.type))
        return sou.sign*pow(300,2)/ distance(x,y,sou.x,sou.y);
    else if(!strcmp("����",sou.type))
        return sou.sign*pow(1000,2)/distance(x,y,sou.x,sou.y);
    else if(!strcmp(sou.type,"����"))
        return sou.sign*pow(5000,2)/distance(x,y,sou.x,sou.y);
    return -1;
}
Qt searchtree(Qt tree,double x,double y)//����λ�������е�λ��
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
boundary findMaxboundary(Qt tree,double x,double y) {
    Qt temp = searchtree(tree, x, y);
    boundary minSquar;
    double min = 999999999999, dt, ax, ay;
    if (temp->length > 0) {
        for (int i = 0; i < temp->length; i++)
        {
        if (min > (dt = distance(temp->points[i].x, temp->points[i].y, x, y)))
        {
            min = dt;
            ax = temp->points[i].x;
            ay = temp->points[i].y;
        }
        }
        minSquar= createBoundary(x,y,sqrt(min), sqrt(min));
    }
    else
    {
        minSquar= createBoundary(temp->bj.x,temp->bj.y,2*temp->bj.w,2*temp->bj.h);
    }

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
//�Խڵ���������
void pointSort(point t[],int length,double x,double y)
{
    for(int i=0;i<length;i++)
    {
        for(int j=i+1;j<length;j++)
        {
            if(getSignpower(x,y,t[i])< getSignpower(x,y,t[j]))
            {
                point temp=t[i];
                t[i]=t[j];
                t[j]=temp;
            }
        }
    }
}
//����jzmax
//�����ź����Ļ�վ���
//���룺��������x,y
point* jzmax(Qt city,Qt village,Qt highway,double x,double y)
{
    point *active=(point *)malloc(5*sizeof(point));
    int alength=0;
    boundary bcity= findMaxboundary(city,x,y);
    point ans[100];
    findPointinside(city, bcity,ans);
    boundary mincountry= findMaxboundary(village,x,y);
    findPointinside(village, mincountry, ans);
    boundary minhighway= findMaxboundary(highway,x,y);
    findPointinside(highway,minhighway,ans);
    double maxSignpower=-1;
    for(int i=0;i<n_ans;i++)
    {
        if(getSignpower(x,y,ans[i])>=1)
        {
            active[alength]=ans[i];
            alength++;
        }
    }
    active[alength].num=-1;
    pointSort(active,alength,x,y);
    if(n_ans==0)
        ans->num=-1;
    n_ans=0;
    if(maxSignpower>=1)return active;
    else return active;
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
    FILE *yd= fopen("src/update2/yd001.txt","r");
    if(yd== nullptr)
    {
        printf("�ļ���ʧ��");
        return -1;
    }
    char t[8];
    fscanf(yd,"%s",t);
    int i=0;
    while(fscanf(yd,"%lf,%lf,%lf,%lf,%lf,%d,%d",&move[i].xs,&move[i].ys,&move[i].xe,&move[i].ye,&move[i].speed,&move[i].sh,&move[i].sm)!=EOF&&move[i].xs>0)
    {
        i++;
    }
    printf("�ļ�����ɹ����ɹ�����%d������\n",i);
    return 1;
}
void display(point *t,int type,double x,double y,int h,int m,int sec)
{
    if(type>0&&t!= nullptr) {
        printf("��%dʱ%d��%d��,λ��(%.2f,%.2f)�������ϱ��Ϊ%d���ź�ǿ��Ϊ%.2f\n", h, m, sec, x, y,t->num,getSignpower(x, y, *t));
    }
    else
        printf("��%dʱ%d��%d��,λ��(%.2f,%.2f)��,����Ч�����ź�\n",h,m,sec,x,y);
}
void inputOver(point a, point b)
{
    printf("������%d��%d��վ���ص���\n",a.num,b.num);
}
void outputOver(int overhs,int overhe,int overms,int overme,double secs,double sece)
{
    double durtime;
    if(overme<overms&&sece>=secs)
        durtime=(overhe-overhs-1)*3600+(overme+60-overms)*60+sece-secs;
    else if(overme<overms&&sece<secs)
        durtime=(overhe-overhs-1)*3600+(overme+60-overms-1)*60+sece+60-secs;
    else if(overme>=overms&&sece>secs)
        durtime=(overhe-overhs)*3600+(overme-overms)*60+sece-secs;
    else durtime=(overhe-overhs)*3600+(overme-overms-1)*60+sece+60-secs;
    printf("����%.2f���뿪�ص���\n",durtime);
}
void outConenectFake(int overhs,int overhe,int overms,int overme,double secs,double sece)       //���������α��վ��ʱ��
{
    double durtime;
    if(overme<overms&&sece>=secs)
        durtime=(overhe-overhs-1)*3600+(overme+60-overms)*60+sece-secs;
    else if(overme<overms&&sece<secs)
        durtime=(overhe-overhs-1)*3600+(overme+60-overms-1)*60+sece+60-secs;
    else if(overme>=overms&&sece>secs)
        durtime=(overhe-overhs)*3600+(overme-overms)*60+sece-secs;
    else durtime=(overhe-overhs)*3600+(overme-overms-1)*60+sece+60-secs;
    printf("����%f����α��վ�Ͽ�����\n",durtime);
}
//�ڲ�����α��վ�������
int movingWithoutfake(Qt city,Qt country,Qt highway,receiver move[]) {
    int i = 0;
    double dx, dy;//ÿ��ʱ����ƶ���x��y�����ϵľ���
    double xnow, ynow;//��ǰʱ��ε�����
    int durmins, dursec;//ÿ�ξ�������ʱ��
    double rangxkm, rangykm;//�����ƽ��
    double ticks;//��ǰ����
    bool overtop=0;//�Ƿ��ص�
    int overhs,overhe,overms,overme;double overt,overte;
    int numbef = 0, numNow;
    int timenowh, timeNowmin;
    if (move[i].speed == 0)printf("δ��������");
    else
        while (move[i].speed != 0) {
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
                if(temp[1].num!=-1&&temp[0].num!=-1)
                {
                    if(overtop!=1)
                    {
                        inputOver(temp[0], temp[1]);
                        overhs=timenowh;overms=timeNowmin;overt=ticks;
                        overtop=true;
                    }
                }
                else
                {
                    if(overtop==1)
                    {
                        overhe=timenowh;overme=timeNowmin;overte=ticks;
                        outputOver(overhs,overhe,overms,overme,overt,overte);
                        overtop=0;
                    }
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
boundary initMaxBoundary(FILE *jz1,FILE*jz2) //��ʼ���߽�
{
    char t[10];
    memset(t,0,sizeof(t));
    fscanf(jz1,"%s",t);     //��ָ�������ļ�ͷ
    fscanf(jz2,"%s",t);
    int num;
    char type[10];
    double force,posx,posy;
    double xmax=0,ymax=0,xmin=99999,ymin=99999;
    char tycity[8]="����",tyvill[8]="����",tyheigh[8]="����";
    while (fscanf(jz1,"%lf,%lf,%s,%lf,%d",&posx,&posy,type,&force,&num)!=EOF)
    {

        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
        if(posx<xmin)xmin=posx;
        if(posy<ymin)ymin=posy;
    }
    while (fscanf(jz2,"%lf,%lf,%s,%lf,%d",&posx,&posy,type,&force,&num)!=EOF)
    {
        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
        if(posx<xmin)xmin=posx;
        if(posy<ymin)ymin=posy;
    }
    double bx=(xmin+xmax)/2;
    double by=(ymin+ymax)/2;
    double w=(xmax-xmin)/2+2;
    double h=(ymax-ymin)/2+2;
    boundary bt=createBoundary(bx,by,w,h);
    rewind(jz1);
    rewind(jz2);
    return bt;
}
void initInput(FILE* jz1,FILE *jz2,Qt tree,Qt citytree,Qt countryTree,Qt highway,point se[30],point nw[30],boundary bse,boundary bnw)//��ʼ�������վλ��
{
    int num;
    char type[10],t[4];
    double force,posx,posy;
    fscanf(jz1,"%s",t);
    printf("���ڶ�ȡ%s001\n",t);
    while (fscanf(jz1,"%lf,%lf,%s %lf,%d",&posx,&posy,type,&force,&num)!=EOF)
    {
        point ins=pointCreate(posx,posy,type,num,force);
        Qtinsert(tree,ins);
        if(!strcmp("\xb3\xc7\xc7\xf8",type))
            Qtinsert(citytree, ins);
        else if(!strcmp("\xcf\xe7\xd5\xf2",type))
            Qtinsert(countryTree, ins);
        else if(!strcmp("\xb8\xdf\xcb\xd9",type))
            Qtinsert(highway, ins);
        if(contain(bse,posx,posy))
        {
            se[lengthofse]= pointCreate(posx,posy,type,num,force);
            lengthofse++;
        }
        if(contain(bnw,posx,posy))
        {
            nw[lenthofnw]= pointCreate(posx,posy,type,num,force);
            lenthofnw++;
        }
    }
    fscanf(jz2,"%s",t);
    printf("���ڶ�ȡ%s002\n",t);
    while (fscanf(jz2,"%lf,%lf,%s %lf,%d",&posx,&posy,type,&force,&num)!=EOF)
    {
        point ins= pointCreate(posx,posy,type,num,force);
        Qtinsert(tree,ins);
        if(!strcmp("\xb3\xc7\xc7\xf8",type))
            Qtinsert(citytree, ins);
        if(contain(bse,posx,posy))
        {
            se[lengthofse]= pointCreate(posx,posy,type,num,force);
            lengthofse++;
        }
        if(contain(bnw,posx,posy))
        {
            nw[lenthofnw]= pointCreate(posx,posy,type,num,force);
            lenthofnw++;
        }
    }
}
//����α�ڵ�����ݽṹ
typedef struct wzjz
{
    double xs,xe,ys,ye,speed;//������꣬�յ����꣬�ٶ�
    int hs,ms,num;//��ʼʱ�䣬��վ���
    double dx,dy;//�н�����
    bool active;
}wzjz;
int wzInput(wzjz fake[])
{
    FILE *wz= fopen("src/update2/wz001.txt","r");
    if(wz== nullptr)
    {
        printf("����ʧ��\n");
        return 0;
    }
    char t[4];
    fscanf(wz,"%s",t);
    printf("���ڶ�ȡ%s001.txt\n",t);
    int i=0;
    while(fscanf(wz,"%lf,%lf,%lf,%lf,%lf,%d,%d,%d",&fake[i].xs,&fake[i].ys,&fake[i].xe,&fake[i].ye,&fake[i].speed,&fake[i].hs,&fake[i].ms,&fake[i].num)!=EOF&&fake[i].xs!=-1)
    {
        fake[i].dx=(fake[i].xe-fake[i].xs)/ sqrt(distance(fake[i].xs,fake[i].ys,fake[i].xe,fake[i].ye))*fake[i].speed/3.6;
        fake[i].dy=(fake[i].ye-fake[i].ys)/ sqrt(distance(fake[i].xs,fake[i].ys,fake[i].xe,fake[i].ye))*fake[i].speed/3.6;
        fake[i].active=true;
        i++;
    }
    printf("һ������%d������\n  ",i+1);
    return i;
}
bool isAfter(int hour ,int min,int hs,int ms)
{
    if(((hour-hs)*60+(min-ms))>=0)return true;
    else return false;
}
double durtime(int hour ,int min,double sec,wzjz t)
{
    double time;
    if(min<t.ms)
        time=(hour-t.hs-1)*3600+(min+60-t.ms)*60+sec;
    else if(min>=t.ms)
        time=(hour-t.hs)*3600+(min-t.ms)*60+sec;
    return time;
}
int IsFake( double x,double y,wzjz fake[],int fnum,int hour,int min,double sec)
{
    int max=-1;
    for(int i=0;i<fnum;i++)
    {
        if(isAfter(hour,min,fake[i].hs,fake[i].ms))
        {
            double xnow=fake[i].xs+fake[i].dx* durtime(hour,min,sec,fake[i]);
            double ynow=fake[i].ys+fake[i].dy*durtime(hour,min,sec,fake[i]);
            if(fabs(xnow-fake[i].xe)<0.5&& fabs(ynow-fake[i].ye)<0.5){fake[i].dx=0;fake[i].dy=0;fake[i].active=false;}
            double t=sqrt(distance(x,y,fake[i].xs+fake[i].dx* durtime(hour,min,sec,fake[i]),fake[i].ys+fake[i].dy*durtime(hour,min,sec,fake[i])));
//          if(i>3)
//           printf("[%d:%d:%f]yd(%f %f)wz(%f,%f)dis=%f\n",hour,min,sec,x,y,xnow,ynow,t);
            if(t<=40)
            {
                max = fake[i].num;
            }
        }
        }
    return max;
}

//�ڿ���α�ڵ�����
int movingWithAll(Qt city,Qt country,Qt highway,receiver move[],wzjz fake[ ],int fnum) {
    int i = 0;
    int overtop=-1;
    int overhs,overhe,overms,overme;double overt,overte;//�ص���ʼ������ʱ��
    int cfhs,cfhe,cfms,cfme;double cfts,cfte;//����α��վʱ��
    double dx, dy;//ÿ��ʱ����ƶ���x��y�����ϵľ���
    double xnow, ynow;//��ǰʱ��ε�����
    int durmins, dursec;//ÿ�ξ�������ʱ��
    double rangxkm, rangykm;//�����ƽ��
    double ticks;//��ǰ����
    int numbef = 0, numNow;
    bool isf= false;
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
            int ht;
            int j = 0, k = 0;
            for (j = 0; j < dursec; j++) {
                if((ht=IsFake(xnow,ynow,fake,fnum,timenowh,timeNowmin,ticks))!=-1)
                {
                    if(!isf)
                    {
                        printf("������α��վ�����Ϊ%d\n",ht);
                        isf=true;
                        cfhs=timenowh;cfms=timeNowmin;cfts=ticks;
                    }

                }
                else
                {
                    if(isf)
                    {
                        outConenectFake(cfhs,timenowh,cfms,timeNowmin,cfms,ticks);
                        isf= false;
                    }
                    isf= false;
                    temp = jzmax(city, country, highway, xnow, ynow);

                    if (temp != nullptr)numNow = temp->num;
                    else numNow = -1;
                    if (numbef != numNow) {
                        display(temp, numNow, xnow, ynow, timenowh, timeNowmin, ticks);
                        numbef = numNow;
                    }
                }
                if(temp[1].num!=-1&&temp[0].num!=-1)
                {
                    if(overtop!=1)
                    {
                        inputOver(temp[0], temp[1]);
                        overhs=timenowh;overms=timeNowmin;overt=ticks;
                        overtop=true;
                    }
                }
                else
                {
                    if(overtop==1)
                    {
                        overhe=timenowh;overme=timeNowmin;overte=ticks;
                        outputOver(overhs,overhe,overms,overme,overt,overte);
                        overtop=0;
                    }
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
                dx=(move[i].xe-move[i].xs)/ sqrt(distance(move[i].xs,move[i].ys,move[i].xe,move[i].ye))*move[i].speed/3.6;
                dy=(move[i].ye-move[i].ys)/ sqrt(distance(move[i].xs,move[i].ys,move[i].xe,move[i].ye))*move[i].speed/3.6;
                while(move[i].xs>move[i].xe) {
                    if ((ht = IsFake(xnow, ynow, fake, fnum, timenowh, timeNowmin, ticks)) != -1) {
                        if (!isf) {
                            printf("������α��վ�����Ϊ%d\n", ht);
                            isf = true;
                            cfhs = timenowh;
                            cfms = timeNowmin;
                            cfts = ticks;
                        }

                    } else {
                        if (isf) {
                            outConenectFake(cfhs, timenowh, cfms, timeNowmin, cfms, ticks);
                            isf = false;
                        }
                        isf = false;
                        temp = jzmax(city, country, highway, xnow, ynow);
                        if (temp != nullptr)numNow = temp->num;
                        else numNow = -1;
                        if (numbef != numNow) {
                            display(temp, numNow, xnow, ynow, timenowh, timeNowmin, ticks);
                            numbef = numNow;
                        }
                    }
                    if(temp[1].num!=-1&&temp[0].num!=-1)
                    {
                        if(overtop!=1)
                        {
                            inputOver(temp[0], temp[1]);
                            overhs=timenowh;overms=timeNowmin;overt=ticks;
                            overtop=true;
                        }
                    }
                    else
                    {
                        if(overtop==1)
                        {
                            overhe=timenowh;overme=timeNowmin;overte=ticks;
                            outputOver(overhs,overhe,overms,overme,overt,overte);
                            overtop=0;
                        }
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
            }
            i++;
        }
    return 0;
}


#endif