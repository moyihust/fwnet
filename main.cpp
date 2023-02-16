#include "quadtree.h"
int main() {
    FILE* jz1=fopen("jz001.txt","r");
    char t[10];
    memset(t,0,sizeof(t));
    fscanf(jz1,"%s",t);
    printf("%s",t);
    int posx,posy,num;
    char type[10];
    double force;
    while (fscanf(jz1,"%d %d %s %f %d",&posx,&posy,type,&force,&num)!=EOF)
    {
        printf("%d\n",num);
    }
    return 0;
}
