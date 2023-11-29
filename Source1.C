
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
    // ����� ������������ �������� ������� � ���� 
    int maxX = 0, maxY = 0;
    for (int i = 0; i < counter; i++) {
        if (strcmp(DataMass[i].name, "X") == 0) {
            if (DataMass[i].time > maxX) {
                maxX = DataMass[i].time;
            }
        }
        else {
            if (DataMass[i].date > maxY) {
                maxY = DataMass[i].date;
            }
        }
    }

    // ���������� ������ 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // ���������� �������������� ��� 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);

    // ���������� ������������ ��� 
    SDL_RenderDrawLine(renderer, 50, SCREEN_HEIGHT - 50, 50, 50);

    // ������� ������� 
    int graphWidth = SCREEN_WIDTH - 100;
    int graphHeight = SCREEN_HEIGHT - 100;

    for (int i = 0; i < counter; i++) {
        int x = 50 + (int)((DataMass[i].time / (float)maxX) * graphWidth);
        int y = SCREEN_HEIGHT - 50 - (int)((DataMass[i].date / (float)maxY) * graphHeight);

        // ������� ���� � ����������� �� ���� ����� (X ��� Y) 
        SDL_SetRenderDrawColor(renderer, (strcmp(DataMass[i].name, "X") == 0) ? 255 : 0, 0, (strcmp(DataMass[i].name, "Y") == 0) ? 255 : 0, 255);

        // ���������� ����� 
        SDL_RenderDrawPoint(renderer, x, y);

        // ��������� ����� ������ (����� ������ �����) 
        if (i > 0) {
            SDL_RenderDrawLine(renderer, x, y, 50 + (int)((DataMass[i - 1].time / (float)maxX) * graphWidth),
                SCREEN_HEIGHT - 50 - (int)((DataMass[i - 1].date / (float)maxY) * graphHeight));
        }
    }

    SDL_RenderPresent(renderer);
}

int main() {
    struct DataFile DataMass[50];
    FILE* fp;
    char row[MAXCHAR];
    char* token;

    int counter = 0;

    fp = fopen("Data.csv", "r");

    if (fp == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    while (fgets(row, MAXCHAR, fp) && counter < 50) {
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

    // ������������� SDL 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // �������� ���� 
    SDL_Window* window = SDL_CreateWindow("Dependency Graph", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    // �������� ��������� 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // �������� ���� 
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // ���������� ������ ��� ������ �������� ��������� ����� 
        drawGraph(renderer, DataMass, counter);
    }

    // ������� �������� SDL 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
