#include "race.h"

int readFile(char *fileName, Car cars[MAXCARS]){
    FILE *file;
    if (!(file = fopen(fileName, "r"))){
        fprintf(stderr, "Can't open the file %s \n", fileName);
        return 0;
    }    

    char line[MAXLINE];
    int carIndex = 0;
    while (fgets(line, sizeof(line), file)) {        
        //printf("%s", line);
        int k = 0;
        char *dup = strdup(line);
        char *found;
        int counter = 1;
        while((found = strsep(&dup, " ")) != NULL){            
            switch (counter){
                case 1:                    
                    strcpy(cars[carIndex].name, found);                    
                    break;
                case 2:
                    strcpy(cars[carIndex].model, found);                    
                    break;
                case 3:
                    cars[carIndex].carNumber = atoi(found);                               
                    break;
                case 4:
                    strcpy(cars[carIndex].color, found);                    
                    break;
                default:
                    break;
            }
            counter++;            
        }
        carIndex++;
    }
    return 1;

}

void printCars(Car cars[MAXCARS]){
    for(int i = 0; i < MAXCARS; i++){
        printf("%d - %s %s %d %s", i + 1, cars[i].name,
            cars[i].model, cars[i].carNumber, 
            cars[i].color);
    }
    printf("\n");
}

void printPlayerCar(Car cars[MAXCARS], int i){
    printf("%s %s %d %s\n", cars[i].name,
        cars[i].model, cars[i].carNumber, 
        cars[i].color);
}

int getRandomDistance(){    
    int r = (rand() % 10) + 1;
    return r;
}

int isRaceFinished(int distances[MAXCARS]){
    for(int i = 0; i < MAXCARS; i++){
        if (distances[i] < 90)                    
            return 0;
    }
    return 1;
}


int min(int a, int b){
    if (a < b)
        return a;
    return b;
}

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}


void displayRace(Car cars[MAXCARS]){
    FILE *fileResult = fopen("raceresult.txt", "a+");
    clearScreen();
    int distances[MAXCARS];
    for(int i = 0; i < MAXCARS; i++){
        distances[i] = 0;
    }
    int finished;
    int rank = 1;
    int arrived[MAXCARS];
    for(int i = 0; i < MAXCARS; i++)
        arrived[i] = 0;

    fprintf(fileResult, "New Race\n");
    srand(time(NULL));
    while(! (finished = isRaceFinished(distances)) ){
        for(int i = 0; i < MAXCARS; i++){            
            printf("#%d ", cars[i].carNumber);            
            int distance = getRandomDistance(); 
            distances[i] = min(90, distances[i] + distance);
            if (distances[i] == 90 && !arrived[i]){
                arrived[i] = 1;
                fprintf(fileResult, "#%d - %s\n", rank ,cars[i].name);                
                rank++;
            }
            for(int j = 0; j < distances[i]; j++){
                printf("*");
            }
            printf("\n");            
        }             
        sleep(1);
        clearScreen();
    }    
    fprintf(fileResult, "\n\n");
    fclose(fileResult);
}

int makeChoice(){
    int choice;    
    printf("1 - Start a race with manual mode\n");
    printf("2 - Start a race with autmatic mode\n");
    printf("3 - Modify a car\n");
    printf("4 - Quit\n");
    do {
        printf("choose an option : ");
        scanf("%d", &choice);
    }while(choice < 1 || choice > 4);
    return choice;    
}

int chooseCar(Car cars[MAXCARS], int id){
    printf("\n");
    printCars(cars);
    int choice;
    do {
        printf("Player %d, please choose a car : ", id);
        scanf("%d", &choice);
    }while(choice < 1 || choice > MAXCARS);
    return choice;
}


int twoPlayerMode(int id, int player, Car cars[MAXCARS]){
    FILE *changes = fopen("changes.txt", "a+");
    int choice;
    printf("\nPlayer %d\n", id);
    printf("1 - Ready\n");
    printf("2 - Modify car\n");    
    do{
        printf("\nPlease choose : ");
        scanf("%d", &choice);
    }while(choice != 1 && choice != 2);
    
    if (choice == 1)
        return 1;
    else{
        int modify;
        printPlayerCar(cars, player);
        int ready = 0;
        while(!ready){
            printf("Modifying player %d's car ...\n", id);
            printf("1 - Modify name of the driver\n");
            printf("2 - Modify model\n");
            printf("3 - Modify the color\n");
            printf("4 - ready\n");
            do{
                printf("\nPlease choose : ");
                scanf("%d", &modify);
            }while(modify < 1 || modify > 4);

            char name[MAX];
            char model[MAX];
            char color[MAX];
            switch (modify){
            case 1:            
                printf("Enter the new name : ");
                scanf("%s", name);
                fprintf(changes, "%s changed to %s\n", cars[player].name, name);
                strcpy(cars[player].name, name);
                break;

            case 2:            
                printf("Enter the new model : ");
                scanf("%s", model);
                fprintf(changes, "%s changed to %s\n", cars[player].model, model);
                strcpy(cars[player].model, model);
                break;

            case 3:            
                printf("Enter the new color : ");
                scanf("%s", color);
                fprintf(changes, "%s changed to %s\n", cars[player].color, color);
                strcpy(cars[player].color, color);
                break;

            case 4:
                ready = 1;
                break;

            default:
                break;
            }
        }
        printf("\n The new car specs : \n");
        printPlayerCar(cars, player);
    }
    fclose(changes);
    return 1;    
}

void startRace(int player1, int player2, Car cars[MAXCARS]){
    FILE *fileResult = fopen("raceresult.txt", "a+");
    clearScreen();
    int player1Distance = 0;
    int player2Distance = 0;

    int finished;
    int rank = 1;

    int player1Arrived = 0;
    int player2Arrived = 0;


    fprintf(fileResult, "New Manual Race\n");
    srand(time(NULL));
    int key;    
    while(!(player1Distance == 90 && player2Distance == 90)){                                    
        printf("#%d ", cars[player1].carNumber);            
        int distance1 = getRandomDistance(); 
        player1Distance = min(90, player1Distance + distance1);
        for(int j = 0; j < player1Distance; j++){
            printf("*");
        }            
            
        if (player1Distance == 90 && !player1Arrived){
            player1Arrived = 1;
            fprintf(fileResult, "#%d - %s\n", rank, cars[player1].name);
            rank++;
        }
                                                
        printf("\n#%d ", cars[player2].carNumber);                           
        int distance2 = getRandomDistance(); 
        player2Distance = min(90, player2Distance + distance2);

        if (player2Distance == 90 && !player2Arrived){
            player2Arrived = 1;
            fprintf(fileResult, "#%d - %s\n", rank, cars[player2].name);
            rank++;
        }
        for(int j = 0; j < player2Distance; j++){
            printf("*");
        }
        printf("\n");           
        printf("Press any key and enter\n");
        getchar();            
        clearScreen();                    
    }
    fprintf(fileResult, "\n\n");
    fclose(fileResult);
}


void modifyCar(Car cars[MAXCARS]){
    int i;
    printCars(cars);
    do {
        printf("\n Which car do you want to modify : ");
        scanf("%d", &i);
    }while(i < 1 || i > MAXCARS);
    i = i - 1;

    printf("\nModifying car ...\n");
    FILE *changes = fopen("changes.txt", "a+");
    int modify;
    printf("1 - Modify name of the driver\n");
    printf("2 - Modify model\n");
    printf("3 - Modify the color\n");    
    do{
        printf("\nPlease choose : ");
        scanf("%d", &modify);
        }while(modify < 1 || modify > 3);
    
    char name[MAX];
    char model[MAX];
    char color[MAX];
    switch (modify){
    case 1:            
        printf("Enter the new name : ");
        scanf("%s", name);
        fprintf(changes, "%s changed to %s\n", cars[i].name, name);
        strcpy(cars[i].name, name);
        break;
    case 2:            
        printf("Enter the new model : ");
        scanf("%s", model);
        fprintf(changes, "%s changed to %s\n", cars[i].model, model);
        strcpy(cars[i].model, model);
        break;
    case 3:            
        printf("Enter the new color : ");
        scanf("%s", color);
        fprintf(changes, "%s changed to %s\n", cars[i].color, color);
        strcpy(cars[i].color, color);
        break;
    default:
        break;
    }
}


int main(int argc, char *argv[]){
    Car cars[MAXCARS];    
    readFile("cars.txt", cars);
    int run = 1;    
    printf("Welcome to car race\n");
    int player1, player2;
    while(run){      
        int choice = makeChoice();
        switch (choice){
        case 1:            
            player1 = chooseCar(cars, 1) - 1;            
            player2 = chooseCar(cars, 2) - 1;               
            int ready;            
            ready = twoPlayerMode(1, player1, cars);
            ready = twoPlayerMode(2, player2, cars);

            startRace(player1, player2, cars);            

            break;
        case 2:
            displayRace(cars);            
            break;

        case 3:
            modifyCar(cars);
            break;
        case 4:
            run = 0;
            break;
        default:
            break;
        }        
    }
    
    
    return 0;
}