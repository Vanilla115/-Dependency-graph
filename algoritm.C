#define _CRT_SECURE_NO_WARNINGS 
#define MAXCHAR 1000 
#include <stdio.h> 
#include <string.h> 
#include <stdbool.h> 

struct DataFile {
    int time;
    char name[2];
    int date;
};


struct Name {
    char new_name[20];
};

int main() {
    struct DataFile DataMass[5000];
    struct Name MassParameters[5000];
    FILE* fp;
    char row[MAXCHAR];
    char* token;

    int counter = 0;

    fp = fopen("Data.csv", "r");

    if (fp == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    while (fgets(row, MAXCHAR, fp) && counter < 5000) {
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
    
    char parameter[20];
    for (int i = 0;i <= counter;i++) {
        parameter = DataMass[i].name;
        /*for (int j = 0; j < counter;j++) {
        *   
            if(parameter == MassParameters[i].name){
                continue;
            }
            else{
                MassParameters[i + 1] = DataMass[i].name;
            }
        }*/
    };

    

}
// Массив структур????; //Массмв строк???7
// Динамический массив без размера  для массива структур ????
// безраземерный динамический массив си;
