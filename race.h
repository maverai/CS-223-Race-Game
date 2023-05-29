#ifndef __RACE_H__
#define __RACE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX 30
#define MAXCARS 4
#define MAXLINE 120

typedef struct car{
    char name[MAX];
    char model[MAX];
    int carNumber;
    char color[MAX];
}Car;


/**
 * @brief This function reads the file passed in parameters and store cars informations in a table of cars
 * 
 * @param fileName the name of the file where cars informations are stored
 * @param cars a table of cars where the new cars should be stored
 * @return int 1 if sucess, 0 otherwise
 */
int readFile(char *fileName, Car cars[MAXCARS]);


/**
 * @brief This function prints information about cars
 * 
 * @param cars cars  
 */
void printCars(Car cars[MAXCARS]);

/**
 * @brief This function print the car specs of the player i
 * 
 * @param cars cars
 * @param i player
 */
void printPlayerCar(Car cars[MAXCARS], int i);

/**
 * @brief Get a Random Distance object
 * 
 * @return int 
 */
int getRandomDistance();


/**
 * @brief This function tells when a race is finished
 * 
 * @param distances all the distances of all the cars
 * @return int 1 if race is finished, 0 otherwise
 */
int isRaceFinished(int distances[MAXCARS]);


/**
 * @brief this function returns the minimum value between a and b
 * 
 * @param a 
 * @param b 
 * @return int the minimum
 */
int min(int a, int b);

/**
 * @brief This function clears the screen after a race iteration
 * 
 */
void clearScreen();


/**
 * @brief This function displays the race between 4 automatic cars
 * 
 * @param cars 
 */
void displayRace(Car cars[MAXCARS]);


/**
 * @brief This function prompt to the user so he can make his choice
 * 
 * @return int 
 */
int makeChoice();


/**
 * @brief This function prompt to the user so he can chooses a car
 * 
 * @param cars all available cars
 * @param id the number of the player( 1 or 2)
 * @return int the index of the car he has chosen
 */
int chooseCar(Car cars[MAXCARS], int id);


/**
 * @brief This function treats the two player mode
 * 
 * @param id the number of the player (1 or 2)
 * @param player the index of the player's car in cars
 * @param cars available cars
 * @return int 1 if sucess, 0 otherwise
 */
int twoPlayerMode(int id, int player, Car cars[MAXCARS]);



/**
 * @brief This function starts the race between two players
 * 
 * @param player1 
 * @param player2 
 * @param cars available cars
 */
void startRace(int player1, int player2, Car cars[MAXCARS]);



/**
 * @brief This function prompts to the user so he can choose 
 * to modify any spec of a car
 * 
 * @param cars available cars
 */
void modifyCar(Car cars[MAXCARS]);

#endif


