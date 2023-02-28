//
// Created by 14413 on 2023/2/2
#include <graphics.h>
#include "quadtree.h"
void button(int x, int y, int w, int h,const char* text)
{

    setbkmode(TRANSPARENT);//设置字体背景透明
    setfillcolor(BROWN);//设置填充颜色
    fillroundrect(x,y,x+w,y+h,10,10);//设置按钮

    char text_[50] = {0};//按钮内容物
    strcpy(text_,text);//复制
    settextstyle(40,0,"黑体");
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