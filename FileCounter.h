#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#define MAXCHAR 1000 
#include <stdio.h> 
#include <string.h> 
#include <stdbool.h> 


int cntLines() {
    int lines = 0;
    int any;
    FILE* f = fopen("Data.csv", "r");
    if (f == NULL) {
        return -1;
    }
    do {
        any = fgetc(f);
        //printf("%c", any);//debug
        if (any == '\n') {
            lines++;
        }
    } while (any != EOF);
    fclose(f);
    return lines;
}