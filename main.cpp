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
/*    double xs,ys,xe,ye,speed;
    int sh,sm,times;
    receiver re[10];
//对wz001文件的处理
    fscanf(wz,"%s",t);
    printf("正在读取%s",t);
    int i=0;
    while(fscanf(wz,"%lf %lf %lf %lf %lf %d %d %d",&xs,&ys,&xe,&ye,&speed,&sh,&sm,&times)!=EOF&&xs>0)
    {
        re[i]= receiverInit(xs,ys,xe,ye,sh,sm,speed,times);
        i++;
    }*/
//   初始化位置
   /* xs=re[0].xs;
    ys=re[0].ys;
    sh=re[0].sh;
    sm=re[0].sm;
    speed=re[0].speed;
    double dx=speed*sqrt(pow(re[0].xe-re[0].xs,2)/(pow(re[0].xe-re[0].xs,2)+pow(re[0].ye-re[0].ys,2)))/3.6;
    double dy=speed*sqrt(pow(re[0].ye-re[0].ys,2)/(pow(re[0].xe-re[0].xs,2)+pow(re[0].ye-re[0].ys,2)))/3.6;
    int tick=0;
    int tag=1;
    while (1)
    {
        if(tag>i)break;
        if(tick>60)sm++;
        if(sm>60)sh++;
        if(sh>=re[tag].sh&&sm>=re[tag].sm)
        {
            dx=speed*sqrt(pow(re[tag].xe-re[tag].xs,2)/(pow(re[tag].xe-re[tag].xs,2)+pow(re[tag].ye-re[tag].ys,2)));
            dy=speed*sqrt(pow(re[tag].ye-re[tag].ys,2)/(pow(re[tag].xe-re[tag].xs,2)+pow(re[tag].ye-re[tag].ys,2)));
            tag++;
        }

        tick++;
    }*/
    return 0;
}
