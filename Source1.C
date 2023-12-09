#define _CRT_SECURE_NO_WARNINGS 
#define MAXCHAR 10000 
#include <stdio.h> 
#include <string.h> 
#include <SDL.h> 
#include <stdbool.h> 
#include <SDL_ttf.h>
#include "FileCounter.h"

struct DataFile {
    int time;
    char name[2];
    int date;
};

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 500;//500


void drawGraph(SDL_Renderer* renderer, struct DataFile* DataMass, int counter) {
    // Найти максимальные 
    int maxX = 0, maxY = 0;
    for (int i = 0; i < counter; i++) {
        if (DataMass[i].time > maxX) {
            maxX = DataMass[i].time;
        }
        if (DataMass[i].date > maxY) {
            maxY = DataMass[i].date;
        }
    }


    // Разметка X
    int rangeX = 50;
    for (int i = 0; i < 10; i++) {
        SDL_SetRenderDrawColor(renderer, 64, 64, 64, 64);
        SDL_RenderDrawLine(renderer, rangeX + 70, SCREEN_HEIGHT - 50, rangeX + 70, 50);
        rangeX += 70;
    }
    // Разметка Y
    int rangeY = 50;
    for (int i = 0; i < 10; i++) {
        SDL_SetRenderDrawColor(renderer, 64, 64, 64, 64);
        SDL_RenderDrawLine(renderer, 50, rangeY + 40, SCREEN_WIDTH - 350, rangeY + 40);
        rangeY += 40;
    }

    // Отрисовать график 
    // Цвет
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Отрисовать горизонтальную ось 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 350, SCREEN_HEIGHT - 50);

    // Отрисовать вертикальную ось 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, 50, 50);


    int graphWidth = SCREEN_WIDTH - 400;
    int graphHeight = SCREEN_HEIGHT - 100;


    int* XxCoordinates = (int*)malloc(counter * sizeof(int));
    int* XyCoordinates = (int*)malloc(counter * sizeof(int));
    int* YxCoordinates = (int*)malloc(counter * sizeof(int));
    int* YyCoordinates = (int*)malloc(counter * sizeof(int));
    int xCount = 0, yCount = 0;

    for (int i = 0; i < counter; i++) {
        if (strcmp(DataMass[i].name, "X") == 0) {
            XxCoordinates[xCount] = 50 + (int)((DataMass[i].time / (float)maxX) * graphWidth);
            XyCoordinates[xCount] = SCREEN_HEIGHT - 50 - (int)((DataMass[i].date / (float)maxY) * graphHeight);
            xCount++;
        }
        else if (strcmp(DataMass[i].name, "Y") == 0) {
            YxCoordinates[yCount] = 50 + (int)((DataMass[i].time / (float)maxX) * graphWidth);
            YyCoordinates[yCount] = SCREEN_HEIGHT - 50 - (int)((DataMass[i].date / (float)maxY) * graphHeight);
            yCount++;
        }
    }

    //  циклы отрисовки 

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //  синий 
    for (int i = 1; i < xCount; i++) {
        SDL_RenderDrawLine(renderer, XxCoordinates[i - 1], XyCoordinates[i - 1], XxCoordinates[i], XyCoordinates[i]);
    }


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //  красный 
    for (int i = 1; i < yCount; i++) {
        SDL_RenderDrawLine(renderer, YxCoordinates[i - 1], YyCoordinates[i - 1], YxCoordinates[i], YyCoordinates[i]);
    }

    // Точки
    for (int i = 0; i < xCount; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect pointRect = { XxCoordinates[i] - 3, XyCoordinates[i] - 3, 6, 6 };
        SDL_RenderFillRect(renderer, &pointRect);
    }


    for (int i = 0; i < yCount; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect pointRect = { YxCoordinates[i] - 3, YyCoordinates[i] - 3, 6, 6 };
        SDL_RenderFillRect(renderer, &pointRect);
    }



    // TTF
    if (TTF_Init() == -1)
    {
        printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
    }

    //Стиль
    TTF_Font* Sans = TTF_OpenFont("sample.ttf", 36);
    SDL_Color White = { 255, 255, 255 };


    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, "Data(Y)", White);

    // Message
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = 27;
    Message_rect.y = 15;
    Message_rect.w = 80;
    Message_rect.h = 30;


    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);


    // Message 1
    TTF_Font* Sans1 = TTF_OpenFont("sample.ttf", 36);
    SDL_Color White1 = { 255, 255, 255 };


    SDL_Surface* surfaceMessage1 =
        TTF_RenderText_Solid(Sans1, "Time(X)", White1);


    SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage1);

    SDL_Rect Message_rect1;
    Message_rect1.x = 350;
    Message_rect1.y = 452;
    Message_rect1.w = 80;
    Message_rect1.h = 30;

    SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);

    //Значения
    //Х
    //int maximumX = maxX;
    //int ratio = maximumX / 10;
    //int MassRatios[10];
    //char MassStrRatios[100];
    //for (int i = 0; i < 10; i++) {
    //    MassRatios[i] = maximumX - ratio;
    //    ratio += ratio;
    //    char str[10];
    //    sprintf(str, "%d", MassRatios[i]);
    //
    ////
    //TTF_Font* SansR = TTF_OpenFont("sample.ttf", 36);
    //SDL_Color WhiteR = { 255, 255, 255 };

    ////char X = MassStrRatios[0] + "------" + MassStrRatios[1] + "------" + MassStrRatios[2] + "------" + MassStrRatios[3] + "------" + MassStrRatios[4] + "------" + MassStrRatios[5] + "------" + MassStrRatios[6] + "------" + MassStrRatios[7] + "------" + MassStrRatios[8] + "------" + MassStrRatios[9];

    //SDL_Surface* surfaceMessageR =
    //    TTF_RenderText_Solid(SansR, sprintf(str, "%d", MassRatios[i]), WhiteR);

    //SDL_Texture* MessageR = SDL_CreateTextureFromSurface(renderer, surfaceMessageR);
    //SDL_Rect Message_rectR;
    //Message_rectR.x = 300;
    //Message_rectR.y = 440;
    //Message_rectR.w = 80;
    //Message_rectR.h = 30;
    //SDL_RenderCopy(renderer, MessageR, NULL, &Message_rectR);

    //Вывод
    /*SDL_FreeSurface(surfaceMessageR);
    SDL_DestroyTexture(MessageR) };*/
    SDL_FreeSurface(surfaceMessage1);
    SDL_DestroyTexture(Message1);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    SDL_RenderPresent(renderer);
}

int main() {
    FILE* fp;
    char row[MAXCHAR];
    char* token;

    int counter = cntLines("Data.csv");
    struct DataFile* DataMass = (struct DataFile*)malloc(counter * sizeof(struct DataFile));
    fp = fopen("Data.csv", "r");

    if (fp == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    int i = 0;
    while (fgets(row, MAXCHAR, fp) && i <= counter) {
        token = strtok(row, ";");
        if (token != NULL) {
            DataMass[i].time = atoi(token);
            token = strtok(NULL, ";");

            if (token != NULL) {
                strncpy(DataMass[i].name, token, sizeof(DataMass[i].name));
                token = strtok(NULL, ";");

                if (token != NULL) {
                    DataMass[i].date = atoi(token);
                    //counter++
                    i++;
                }
            }
        }
    }

    fclose(fp);

    // Инициализация SDL 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Создание окна 
    SDL_Window* window = SDL_CreateWindow("Dependency Graph", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    // Создание рендерера 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Отрисовать график 
        drawGraph(renderer, DataMass, counter);
    }

    // Очистка ресурсов SDL 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


// Как сделать легенду