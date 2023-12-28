#define _CRT_SECURE_NO_WARNINGS 
#define MAXCHAR 10000 
#define MAX_NAMES 10
#define MAX_NAME_LENGTH 15
#include <stdio.h> 
#include <string.h> 
#include <SDL.h> 
#include <stdbool.h> 
#include <SDL_ttf.h>
#include "FileCounter.h"


struct DataPoint
{
    int x;
    int y;
    struct DataPoint* next;
};
struct DataSerial
{
    char name[16];
    struct DataPoint* points;
    struct DataSerial* next;
};

struct Plot
{
    int max_x, min_x;
    int max_y, min_y;
    struct DataSerial* serials;
};

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 500;


void drawGraph(SDL_Renderer* renderer, struct DataSerial* serials, struct DataSerial* points, struct Plot * max_x, struct Plot* min_x, struct Plot* max_y, struct Plot* min_y,int counter) {

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
        SDL_RenderDrawLine(renderer, 50, rangeY, SCREEN_WIDTH - 350, rangeY + 0);
        rangeY += 40;
    }

    // Отрисовать график 
    // Цвет
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Отрисовать горизонтальную ось 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 350, SCREEN_HEIGHT - 50);

    // Отрисовать вертикальную ось 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, 50, 50);

    int* XCoordinates = (int*)malloc(counter * sizeof(int));
    int* YCoordinates = (int*)malloc(counter * sizeof(int));
    int CountColor = 0;
    int graphWidth = SCREEN_WIDTH - 400;
    int graphHeight = SCREEN_HEIGHT - 100;
    int maxX = max_x;
    int maxY = max_y;

    for (int i = 0; i < sizeof(serials);i++) {
        int Count = 0;
        while (points != NULL) {
            //for (int i = 0; i < counter; i++) {
            XCoordinates[Count] = 50 + (int)((serials[i].points[i].x / (float)maxX) * graphWidth);
            XCoordinates[Count] = SCREEN_HEIGHT - 50 - (int)((serials[i].points[i].y / (float)maxY) * graphHeight);
            Count++;
            //}
        }
        CountColor++;
        switch (CountColor)
        {
        case 1:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //  красный 
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //  синий 
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }
            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 3:
            SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); //  зеленый 
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 4:
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); //  желтый
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 5:
            SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); //  фиолетовый
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
        case 6:
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //  белый
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 7:
            SDL_SetRenderDrawColor(renderer, 165, 42, 42, 255); //  коричневый
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 165, 42, 42, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 8:
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); //  оранжевый 
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 9:
            SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255); //  розовый
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        case 10:
            SDL_SetRenderDrawColor(renderer, 127, 255, 212, 255); //  аквамариновый
            for (int i = 1; i < Count; i++) {
                SDL_RenderDrawLine(renderer, XCoordinates[i - 1], YCoordinates[i - 1], XCoordinates[i], YCoordinates[i]);
            }

            for (int i = 0; i < Count; i++) {
                SDL_SetRenderDrawColor(renderer, 127, 255, 212, 255);
                SDL_Rect pointRect = { XCoordinates[i] - 3, YCoordinates[i] - 3, 6, 6 };
                SDL_RenderFillRect(renderer, &pointRect);
            }
            break;
        default:
            break;
        }
    }

    // TTF
    if (TTF_Init() == -1)
    {
        printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
    }
    // Message
    TTF_Font* Sans = TTF_OpenFont("TimesNewRomanRegular.ttf", 36);
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, "Data(Y)", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 55;
    Message_rect.y = 15;
    Message_rect.w = 80;
    Message_rect.h = 30;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // legend
    TTF_Font* SansTest = TTF_OpenFont("TimesNewRomanRegular.ttf", 36);
    SDL_Color WhiteTest = { 255, 255, 255 };
    SDL_Surface* surfaceMessageTest =
        TTF_RenderText_Solid(Sans, "Legend", White);
    SDL_Texture* MessageTest = SDL_CreateTextureFromSurface(renderer, surfaceMessageTest);
    SDL_Rect Message_rectTest;
    Message_rectTest.x = 890;
    Message_rectTest.y = 15;
    Message_rectTest.w = 80;
    Message_rectTest.h = 30;
    SDL_RenderCopy(renderer, MessageTest, NULL, &Message_rectTest);

    char Colors[][20] = { "red","blue","green", "yellow","purple","white","brown","orange","pink","aquamarine" };

    // LegendList
    int L = 0;
    for (int i = 0; i < sizeof(serials);i++) {
        char result[70];
        TTF_Font* SansL = TTF_OpenFont("TimesNewRomanRegular.ttf", 36);
        SDL_Color WhiteL = { 255, 255, 255 };
        strcpy(result, serials->name[i]);
        strcat(result, " - ");
        strcat(result, Colors[i]);

        SDL_Surface* surfaceMessageTestL =
            TTF_RenderText_Solid(SansL, result, WhiteL);
        SDL_Texture* MessageTestL = SDL_CreateTextureFromSurface(renderer, surfaceMessageTestL);
        SDL_Rect Message_rectTestL;
        Message_rectTestL.x = 800;
        Message_rectTestL.y = 50 + L;
        Message_rectTestL.w = 80;
        Message_rectTestL.h = 40;
        L += 35;
        SDL_RenderCopy(renderer, MessageTestL, NULL, &Message_rectTestL);

        SDL_FreeSurface(surfaceMessageTestL);
        SDL_DestroyTexture(MessageTestL);
    }

    // Message 1
    TTF_Font* Sans1 = TTF_OpenFont("TimesNewRomanRegular.ttf", 36);
    SDL_Color White1 = { 255, 255, 255 };
    SDL_Surface* surfaceMessage1 =
        TTF_RenderText_Solid(Sans1, "Time(X)", White1);
    SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage1);
    SDL_Rect Message_rect1;
    Message_rect1.x = 350;
    Message_rect1.y = 470;
    Message_rect1.w = 85;
    Message_rect1.h = 30;
    SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);

    //Значения
    //Х
    int maximumX = max_x;
    int minimumX = max_y;
    int ratio = (maximumX - minimumX)/ 10;
    int h = 0;
    int MassRatios[10];
    for (int i = 0; i < 10; i++) {
        MassRatios[i] = maximumX - ratio * i;
        char str[10];
        sprintf(str, "%d", MassRatios[i]);

        //
        TTF_Font* SansR = TTF_OpenFont("TimesNewRomanRegular.ttf", 16);
        SDL_Color WhiteR = { 255, 255, 255 };
        sprintf(str, "%d", MassRatios[i]);
        SDL_Surface* surfaceMessageR =
            TTF_RenderText_Solid(SansR, str, WhiteR);

        SDL_Texture* MessageR = SDL_CreateTextureFromSurface(renderer, surfaceMessageR);
        SDL_Rect Message_rectR;


        Message_rectR.x = 740 - h;
        Message_rectR.y = 455;
        Message_rectR.w = 25;
        Message_rectR.h = 20;
        h += 70;

        SDL_RenderCopy(renderer, MessageR, NULL, &Message_rectR);

        SDL_FreeSurface(surfaceMessageR);
        SDL_DestroyTexture(MessageR);
    };
    //Значения
    //Y
    int maximumY = max_y;
    int minimumY = min_y;
    int ratio2 = (maximumY - minimumY) / 10;
    int h2 = 0;
    int MassRatios2[10];
    for (int i = 0; i < 10; i++) {
        MassRatios2[i] = maximumY - ratio2 * i;
        char str2[10];
        sprintf(str2, "%d", MassRatios2[i]);

        //
        TTF_Font* SansR2 = TTF_OpenFont("TimesNewRomanRegular.ttf", 16);
        SDL_Color WhiteR2 = { 255, 255, 255 };
        sprintf(str2, "%d", MassRatios2[i]);
        SDL_Surface* surfaceMessageR2 =
            TTF_RenderText_Solid(SansR2, str2, WhiteR2);

        SDL_Texture* MessageR2 = SDL_CreateTextureFromSurface(renderer, surfaceMessageR2);
        SDL_Rect Message_rectR2;

        Message_rectR2.x = 20;
        Message_rectR2.y = 30 + h2;
        Message_rectR2.w = 25;
        Message_rectR2.h = 20;
        h2 += 42;

        SDL_RenderCopy(renderer, MessageR2, NULL, &Message_rectR2);

        SDL_FreeSurface(surfaceMessageR2);
        SDL_DestroyTexture(MessageR2);
    };
    SDL_FreeSurface(surfaceMessageTest);
    SDL_DestroyTexture(MessageTest);
    SDL_FreeSurface(surfaceMessage1);
    SDL_DestroyTexture(Message1);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    SDL_RenderPresent(renderer);
};


void init_serial(struct DataSerial** serial, char* name)
{
    *serial = malloc(sizeof(struct DataSerial));
    if (*serial == NULL) {
        fprintf(stderr, "not aloc serial");
        exit(1);
    }
    (*serial)->next = NULL;
    (*serial)->points = NULL;
    strcpy((*serial)->name, name);
}

void init_point(struct DataPoint** point, int x, int y)
{
    *point = malloc(sizeof(struct DataPoint));
    if (*point == NULL) {
        fprintf(stderr, "not aloc point");
        exit(2);
    }
    (*point)->next = NULL;
    (*point)->x = x;
    (*point)->y = y;
}


void prosses_file(char* file_name, struct Plot* plot)
{
    struct DataSerial* serial;
    struct DataPoint* point;

    FILE* f = fopen(file_name, "r");
    char filestring[0xff] = { 0, };
    if (f == NULL) { fprintf(stderr, "not open file"); return; }

    memset(plot, 0, sizeof(plot));
    plot->serials = NULL;
    plot->min_x = 0xffff;
    plot->min_y = 0xffff;

    while (fscanf(f, "%s\n", filestring) == 1)
    {
        
        char* serial_x = strtok(filestring, ";");
        char* serial_name = strtok(NULL, ";");
        char* serial_y = strtok(NULL, ";");
        printf("parse point %s %s %s\n", serial_x, serial_name, serial_y);

        int x = atoi(serial_x);
        int y = atoi(serial_y);

        if (plot->max_x < x) plot->max_x = x;
        if (plot->max_y < y) plot->max_y = y;

        if (plot->min_x > x) plot->min_x = x;
        if (plot->min_y > y) plot->min_y = y;

        if (plot->serials == NULL)
        {
            printf("init start serial %s\n", serial_name);
            init_serial(&(plot->serials), serial_name);
        }
        serial = plot->serials;

        while (serial != NULL)
        {
            if (strcmp(serial->name, serial_name) == 0)
            {
                printf("serial found\n");
                if (serial->points == NULL)
                {
                    init_point(&(serial->points), x, y);
                }
                point = serial->points;
                while (point->next != NULL)
                {
                    point = point->next;
                }
                init_point(&(point->next), x, y);
                break;
            }
            else
            {
                if (serial->next == NULL)
                {
                    printf("init serial %s after %s\n", serial_name, serial->name);
                    init_serial(&(serial->next), serial_name);
                }
                serial = serial->next;
            }
        }
    }
    
    printf("X min/max: %d/%d\n", plot->min_x, plot->max_x);
    printf("Y min/max: %d/%d\n", plot->min_y, plot->max_y);
}

int main() {
    struct Plot plot;
    int counter = cntLines("Data.csv");

    prosses_file("Data.csv", &plot);

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

                drawGraph(renderer, serials, points, max_x, min_x, max_y, min_y, counter);
            }
            // Очистка ресурсов SDL 
            SDL_DestroyRenderer(renderer);
        }
        return 0;
    }
}

int main2()
{
    struct Plot plot;
    prosses_file("Data.csv", &plot);

    void init_serial(struct DataSerial** serial, char* name);

    void init_point(struct DataPoint** point, int x, int y);

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
            //drawGraph(renderer, DataMass, counter, names, uniqueCount);
        }
        // Очистка ресурсов SDL 
        SDL_DestroyRenderer(renderer);
    }
    return 0;
}
