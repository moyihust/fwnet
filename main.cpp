#include "paint.h"
int main() {
    FILE* jz1=fopen("jz001.txt","r");       //读入文件指针
    FILE* jz2=fopen("jz002.txt","r");
    char t[10];
    memset(t,0,sizeof(t));
    fscanf(jz1,"%s",t);
    fscanf(jz2,"%s",t);
    printf("%s\n",t);
    int num;
    char type[10];
    double force,posx,posy;
    double xmax=0,ymax=0,xmin=99999,ymin=99999;
    char tycity[8]="城区",tyvill[8]="乡镇",tyheigh[8]="高速";
    while (fscanf(jz1,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
        if(posx<xmin)xmin=posx;
        if(posy<ymin)ymin=posy;
    }
    while (fscanf(jz2,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
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
    Qt tree= createTree(bt,4);
    Qt citytree=createTree(bt, 4);
    Qt countryTree=createTree(bt, 4);
    Qt highway=createTree(bt, 4);
    rewind(jz1);
    rewind(jz2);
    fscanf(jz1,"%s",t);
    printf("正在读取%s001\n",t);
    while (fscanf(jz1,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        point ins=pointCreate(posx,posy,type,num,force);
        Qtinsert(tree,ins);
        if(!strcmp("\xb3\xc7\xc7\xf8",type))
            Qtinsert(citytree, ins);
        else if(!strcmp("\xcf\xe7\xd5\xf2",type))
            Qtinsert(countryTree, ins);
        else if(!strcmp("\xb8\xdf\xcb\xd9",type))
            Qtinsert(highway, ins);
    }
    fscanf(jz2,"%s",t);
    printf("正在读取%s002\n",t);
    while (fscanf(jz2,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        point ins= pointCreate(posx,posy,type,num,force);
        Qtinsert(tree,ins);
        if(!strcmp("\xb3\xc7\xc7\xf8",type))
            Qtinsert(citytree, ins);
    }
    //查找西北的节点
    findmaxnw(tree);
    //查找东南的节点
    findmaxse(tree);
    receiver move[30];//存储接收器移动的路径
//对wz001文件的处理
    reInit(move,30);
    ydinput(move);
    Qt c=countryTree;
    Qt high=highway;
    movingWithoutfake(citytree, c, high, move);
    getc(stdin);
    return 0;
}
