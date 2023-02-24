#include "quadtree.h"
int main() {
    FILE* jz1=fopen("jz001.txt","r");       //读入文件指针
    FILE* jz2=fopen("jz002.txt","r");
    FILE* wz= fopen("wz001.txt","r");
    FILE* yd=fopen("yd001.txt","r");
    char t[10];
    memset(t,0,sizeof(t));
    fscanf(jz1,"%s",t);
    fscanf(jz2,"%s",t);
    printf("%s\n",t);
    int num;
    char type[10];
    double force,posx,posy;
    double xmax=0,ymax=0;
    while (fscanf(jz1,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
    }
    while (fscanf(jz2,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
    }
    double bx=(0+xmax)/2;
    double by=(0+ymax)/2;
    double w=xmax/2+2;
    double h=ymax/2+2;
    boundary bt=createBoundary(bx,by,w,h);
    Qt tree= createTree(bt,2);
    Qt city=createTree(bt,2);
    Qt country=createTree(bt,2);
    Qt heighway=createTree(bt,2);
    rewind(jz1);
    rewind(jz2);
    fscanf(jz1,"%s",t);
    printf("正在读取%s001\n",t);
    while (fscanf(jz1,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF&&posx>0)
    {
        point ins=pointCreate(posx,posy,type,num,force);
        Qtinsert(tree,ins);
        if(!strcmp("城区",type))
            Qtinsert(city,ins);
        else if(!strcmp("乡镇",type))
            Qtinsert(country,ins);
        else if(!strcmp(type,"高速"))
            Qtinsert(heighway,ins);
    }
    fscanf(jz2,"%s",t);
    printf("正在读取%s002\n",t);
    while (fscanf(jz2,"%lf %lf %s %lf %d",&posx,&posy,type,&force,&num)!=EOF&&posx>0)
    {
        point ins= pointCreate(posx,posy,type,num,force);
        Qtinsert(tree,ins);
        if(!strcmp("城区",type))
            Qtinsert(city,ins);
        else if(!strcmp("乡镇",type))
            Qtinsert(country,ins);
        else if(!strcmp(type,"高速"))
            Qtinsert(heighway,ins);
    }
    //查找西北的节点
    findmaxnw(tree);
    //查找东南的节点
    findmaxse(tree);
    double xs,ys,xe,ye,speed;
    int sh,sm,times;
    receiver re[10];
//对wz001文件的处理

    getc(stdin);
    return 0;
}
