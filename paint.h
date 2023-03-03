//
// Created by 14413 on 2023/2/2
#include <graphics.h>
#include "quadtree.h"
int readfile(FILE *jz1,FILE *jz2,receiver move[30],wzjz fake[30],Qt tree,Qt citytree,Qt country,Qt highway,point se[30],point nw[30],boundary bse,boundary bnw)
{
    if(jz1== nullptr||jz2== nullptr)
        printf("����ʧ��\n");
    else
        printf("����ɹ�\n");
    initInput(jz1,jz2,tree,citytree,country,highway,se,nw,bse,bnw);
    ydinput(move);
    return wzInput(fake);
}
void button(int x, int y, int w, int h,const char* text)
{

    setbkmode(TRANSPARENT);//�������屳��͸��
    setfillcolor(BROWN);//���������ɫ
    fillroundrect(x,y,x+w,y+h,10,10);//���ð�ť

    char text_[50] = {0};//��ť������
    strcpy(text_,text);//����
    settextstyle(24,0,"����");
    int tx = x + (w-textwidth(text_))/2;
    int ty = y + (h-textheight(text_))/2;
    outtextxy(tx,ty,text_);
}
void task2(Qt tree)
{
    findmaxnw(tree);
    findmaxse(tree);
}
void task1(point se[30],point nw[30])
{
    for(int i=0;i<lenthofnw;i++)
    {
        pointprintf(nw[i]);
    }
    for(int i=0;i<lengthofse;i++)
    {
        pointprintf(se[i]);
    }
}
void task3(Qt city ,Qt village,Qt highway)
{
    double x,y;
    printf("����������\n");
    scanf("%lf %lf",&x,&y);
    point *temp= jzmax(city,village,highway,x,y);
    if(temp->num==-1)
        printf("δ����Ч��Χ��");
    else
    {
        printf("�����ϱ��Ϊ%d�Ļ�վ���ź�ǿ��Ϊ%f",temp->num, getSignpower(x,y,*temp));
    }
}

void returnBefore()
{
    system("cls");
}
void finish()
{
    closegraph();
    returnBefore();
}
void paintMenu()
{
    int height =480,width=120;
    initgraph(width,height,SHOWCONSOLE);
    setbkcolor(BLACK);
    cleardevice();
    setfillcolor(RGB(153,255,255));
    settextstyle(24,0,"����");
    setbkmode(TRANSPARENT);
    setbkcolor(BLUE);
    outtextxy(10,20,_T("�����б�"));
    button(10,65,100,25,"�����ļ�");
    button(10,105,100,25,"task1");
    button(10,145,100,25,"task2");
    button(10,185,100,25,"task3");
    button(10,225,100,25,"task5");
    button(10,265,100,25,"��������");
    button(10,305,100,25,"����");
    button(10,345,100,25,"��������");
}
void startProgram()
{
    point se[30];
    point nw[30];
    setPoint(se,30);
    setPoint(nw,30);
    boundary bse;
    boundary bnw;
    FILE* jz1=fopen("src/update2/jz001.txt","r");       //�����ļ�ָ��
    FILE* jz2=fopen("src/update2/jz002.txt","r");
    boundary bt= initMaxBoundary(jz1,jz2);
    bse= createBoundary(bt.x-bt.w+1000,bt.y+bt.h-1000,1000,1000);
    bnw= createBoundary(bt.x+bt.w-1000,bt.y-bt.h+1000,1000,1000);
    Qt tree= createTree(bt,4);
    Qt citytree=createTree(bt, 4);
    Qt countryTree=createTree(bt, 4);
    Qt highway=createTree(bt, 4);
    receiver move[30];//�洢�������ƶ���·��
    wzjz fake[30];//α��վ�ƶ���·��
    int fnum=5;
    paintMenu();
    MOUSEMSG msg;
    while(1)
    {
        if(MouseHit())
        {
            msg=GetMouseMsg();
            if(msg.uMsg==WM_LBUTTONDOWN)
            {
                if(msg.x>10&&msg.x<110&&msg.y>65&&msg.y<90)
                {
                    readfile(jz1,jz2,move,fake,tree,citytree,countryTree,highway,se,nw,bse,bnw);
                }else if(msg.x>10&&msg.x<110&&msg.y>105&&msg.y<130)
                {
                    task1(se,nw);

                }else if(msg.x>10&&msg.x<110&&msg.y>145&&msg.y<170)
                {
                    task2(tree);
                }else if(msg.x>10&&msg.x<110&&msg.y>185&&msg.y<210)
                {
                    task3(citytree,countryTree,highway);
                }else if(msg.x>10&&msg.x<110&&msg.y>225&&msg.y<250)
                {
                    movingWithoutfake(citytree,countryTree,highway,move);
                }
                else if(msg.x>10&&msg.x<110&&msg.y>265&&msg.y<290)
                {
                    movingWithAll(citytree,countryTree,highway,move,fake,fnum);
                }
                else if(msg.x>10&&msg.x<110&&msg.y>305&&msg.y<340)
                {
                    returnBefore();
                }
                else if(msg.x>10&&msg.x<110&&msg.y>345&&msg.y<380)
                {
                    finish();
                }
            }
        }

    }
}