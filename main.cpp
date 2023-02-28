#include "paint.h"
int main() {
    FILE* jz1=fopen("src/befordata/jz001.txt","r");       //读入文件指针
    FILE* jz2=fopen("src/befordata/jz002.txt","r");
    boundary bt= initMaxBoundary(jz1,jz2);
    Qt tree= createTree(bt,4);
    Qt citytree=createTree(bt, 4);
    Qt countryTree=createTree(bt, 4);
    Qt highway=createTree(bt, 4);
    initInput(jz1,jz2,tree,citytree,countryTree,highway);
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
    makestartmenu();
    getc(stdin);
    return 0;
}
