//
// Created by 14413 on 2023/2/2
#include <graphics.h>
#include "quadtree.h"
void button(int x, int y, int w, int h,const char* text)
{

    setbkmode(TRANSPARENT);//�������屳��͸��
    setfillcolor(BROWN);//���������ɫ
    fillroundrect(x,y,x+w,y+h,10,10);//���ð�ť

    char text_[50] = {0};//��ť������
    strcpy(text_,text);//����
    settextstyle(40,0,"����");
    int tx = x + (w-textwidth(text_))/2;
    int ty = y + (h-textheight(text_))/2;
    outtextxy(tx,ty,text_);
}
void makestartmenu()
{
    initgraph(480,640,SHOWCONSOLE);
    setbkcolor(RGB(255,228,181));

    cleardevice();
    button(0,0,40,40,"hello");

}