#include "quadtree.h"
int main() {
    FILE* jz1=fopen("jz001.txt","r");
    FILE* jz2=fopen("jz002.txt","r");
    char t[10];
    memset(t,0,sizeof(t));
    fscanf(jz1,"%s",t);
    fscanf(jz2,"%s",t);
    printf("%s\n",t);
    int posx,posy,num;
    char type[10];
    double force;
    double xmax=0,ymax=0;
    while (fscanf(jz1,"%d %d %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
    }
    while (fscanf(jz2,"%d %d %s %lf %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        if(posx>xmax)xmax=posx;
        if(posy>ymax)ymax=posy;
    }
    printf("%lf %lf",xmax,ymax);
    return 0;
}
