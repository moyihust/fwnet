#include <iostream>
#include "stdio.h"
#include "string.h"
int main() {
    FILE* jz1=fopen("jz001.txt","r");
    char t[10];
    memset(t,0,sizeof(t));
    fscanf(jz1,"%s",t);
    printf("%s",t);
    return 0;
}
