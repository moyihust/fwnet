#include "paint.h"
int main() {
    FILE* jz1=fopen("src/befordata/jz001.txt","r");       //�����ļ�ָ��
    FILE* jz2=fopen("src/befordata/jz002.txt","r");
    boundary bt= initMaxBoundary(jz1,jz2);
    Qt tree= createTree(bt,4);
    Qt citytree=createTree(bt, 4);
    Qt countryTree=createTree(bt, 4);
    Qt highway=createTree(bt, 4);
    initInput(jz1,jz2,tree,citytree,countryTree,highway);
    //���������Ľڵ�
    findmaxnw(tree);
    //���Ҷ��ϵĽڵ�
    findmaxse(tree);
    receiver move[30];//�洢�������ƶ���·��
//��wz001�ļ��Ĵ���
    reInit(move,30);
    ydinput(move);
    Qt c=countryTree;
    Qt high=highway;
    movingWithoutfake(citytree, c, high, move);
    makestartmenu();
    getc(stdin);
    return 0;
}
