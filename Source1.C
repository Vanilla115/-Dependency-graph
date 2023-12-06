#define _CRT_SECURE_NO_WARNINGS 
#define MAXCHAR 1000 
#include <stdio.h> 
#include <string.h> 
#include <SDL.h> 
#include <stdbool.h> 

struct DataFile {
    int time;
    char name[2];
    int date;
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;


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

    // Отрисовать график 
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Отрисовать горизонтальную ось 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);

    // Отрисовать вертикальную ось 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, 50, 50);


    int graphWidth = SCREEN_WIDTH - 100;
    int graphHeight = SCREEN_HEIGHT - 100;

    int xCoordinates[5000];
    int yCoordinates[5000];
    int xCount = 0, yCount = 0;

    for (int i = 0; i < counter; i++) {
        if (strcmp(DataMass[i].name, "X") == 0) {
            xCoordinates[xCount] = 50 + (int)((DataMass[i].time / (float)maxX) * graphWidth);
            yCoordinates[xCount] = SCREEN_HEIGHT - 50 - (int)((DataMass[i].date / (float)maxY) * graphHeight);
            xCount++;
        }
        else if (strcmp(DataMass[i].name, "Y") == 0) {
            xCoordinates[yCount] = 50 + (int)((DataMass[i].time / (float)maxX) * graphWidth);
            yCoordinates[yCount] = SCREEN_HEIGHT - 50 - (int)((DataMass[i].date / (float)maxY) * graphHeight);
            yCount++;
        }
    }

    //  циклы отрисовки 

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //  синий 
    for (int i = 1; i < xCount; i++) {
        SDL_RenderDrawLine(renderer, xCoordinates[i - 1], yCoordinates[i - 1], xCoordinates[i], yCoordinates[i]);
    }


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //  красный 
    for (int i = 1; i < yCount; i++) {
        SDL_RenderDrawLine(renderer, xCoordinates[i - 1], yCoordinates[i - 1], xCoordinates[i], yCoordinates[i]);
    }

    // Точки
    for (int i = 0; i < xCount; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect pointRect = { xCoordinates[i] - 3, yCoordinates[i] - 3, 6, 6 };
        SDL_RenderFillRect(renderer, &pointRect);
    }


    for (int i = 0; i < yCount; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect pointRect = { xCoordinates[i] - 3, yCoordinates[i] - 3, 6, 6 };
        SDL_RenderFillRect(renderer, &pointRect);
    }
    SDL_RenderPresent(renderer);
}

int main() {
    struct DataFile DataMass[5000];
    FILE* fp;
    char row[MAXCHAR];
    char* token;

    int counter = 0;

    fp = fopen("Data.csv", "r");

    if (fp == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    while (fgets(row, MAXCHAR, fp) && counter <= 5000) {
        token = strtok(row, ";");
        if (token != NULL) {
            DataMass[counter].time = atoi(token);
            token = strtok(NULL, ";");

            if (token != NULL) {
                strncpy(DataMass[counter].name, token, sizeof(DataMass[counter].name));
                token = strtok(NULL, ";");

                if (token != NULL) {
                    DataMass[counter].date = atoi(token);
                    counter++;
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