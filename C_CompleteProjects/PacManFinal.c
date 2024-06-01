//Addison Wiens and Joshua Westlake - we attest to the originality of the code

/*Please note that the code has been written with the understanding that the provided file will have walls
 * so their may be issues with the results should the map differ from the one provided.
 * along the outside we understand that the wincheck() and losecheck() function don't work 100% of the time.
 * The wincheck() doesn't work as the ghost fails to replace the characters it passes over whilst moving
 * causing the locations of the dots to be difficult to locate and as such the game cannot be won in
 * its current state. The method used to attempt to replace these spots is shown within the code, however
 * and through external tests in a secondary file the method of replacement works - but we could not implement
 * it into the code successfully, causing the game to be unwinnable. Through additional testing, with non-moving
 * ghosts, the implemented win condition is successful. Similarely, the loose condition is often does not 100%
 * for unexpected reasons. The provided lose condition has been proven to be an effective method with stationary ghosts
 * as well. However, The game often ends without showcasing the final map print which a solution could
 * not be found for.
 * */

// Relevant Libraries
#include <stdio.h>
#include "colours.h"
#include <stdlib.h>

// Global Variables
char **mapChar = (char **) malloc(32 * 12 * sizeof(char));
int pacmanXLocation;
int pacmanYLocation;
int ghostXLocation;
int ghostYLocation;
int ghost2XLocation;
int ghost2YLocation;
int dot;
char temp;
char tempB;
int Value1;
int Value2;

// Defined variables for improved readability
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

// Function Declarations
// Reads Map / Opens .txt file
char **readMap(char *mapFile);

// Prints out the map / updates the map when characters move
void printMap(char **map);

// Checks if character is going to hit a wall
int isWall(int YLocation, int XLocation);

// Checks for win, end condition
int winCheck();

// Checks for loss, end condition
int loseCheck();

// Gives random number for ghost movement, checks if it works
int ghostRandom(int ghostY, int ghostX, int value);

// Ghost function, AI, chases pacman
void ghost(int YLocation, int XLocation, char direction);

// Function Definitions
// Read Map Function - opens .txt file
char **readMap(char *mapFile) {
    FILE *map = fopen(mapFile, "r");
    int GhostNUM = 1;
    if (map == NULL) {
        printf("File Not Found");
    } else {
        for (int i = 0; i < 11; i++) {
            mapChar[i] = (char *) malloc(32 * sizeof(char *));
            for (int j = 0; j < 32; j++) {
                fscanf(map, "%c", &mapChar[i][j]);
                // Reads Pacman as 'P' and stores location relative to the map
                if (mapChar[i][j] == PACMAN) {
                    pacmanYLocation = i;
                    pacmanXLocation = j;
                }
                    // Reads dots as '.' and counts them out
                else if (mapChar[i][j] == DOT) {
                    dot += 1;
                }
                    // Reads Ghost1 as 'G' and stores location relative to the map
                else if (mapChar[i][j] == GHOST && GhostNUM == 1) {
                    ghostYLocation = i;
                    ghostXLocation = j;
                    GhostNUM++;
                }
                    // Reads Ghost2 as 'G' and stores location relative to the map
                else if (mapChar[i][j] == GHOST && GhostNUM == 2) {
                    ghost2YLocation = i;
                    ghost2XLocation = j;
                }
            }
        }
        return mapChar;
    }
    //close map
    fclose(map);
    return 0;

}

// Print Map Function
void printMap(char **map) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 32; j++) {
            // Colour Pacman yellow
            if (mapChar[i][j] == PACMAN) {
                colourChange(6);
                // Colour ghosts pink
            } else if (mapChar[i][j] == GHOST) {
                colourChange(13);
                // Colour walls blue
            } else if (mapChar[i][j] == WALL) {
                colourChange(1);
                // Everything else is white
            } else {
                colourChange(15);
            }
            printf("%c", map[i][j]);
        }
    }
    printf("\n");
}

//Check For Win Function, if no dots remaining then win
int winCheck() {
    if (dot == 0) {
        printf("Congratulations! You win! Press any key to exit the game");
        return 1;
    }
    return 0;
}

// Check For Loss Function, if either Ghost touches Pacman then the game is over
int loseCheck() {
    if (ghostYLocation == pacmanYLocation && ghostXLocation == pacmanXLocation) {
        printf("Sorry, you lose. Press any key to exit the game");
        mapChar[ghostYLocation][ghostXLocation] = GHOST;
        getch();
        return 1;
    } else if (ghost2YLocation == pacmanYLocation && ghost2XLocation == pacmanXLocation) {
        printf("Sorry, you lose. Press any key to exit the game");
        getch();
        return 1;
    } else
        return 0;
}

// Function that randomly generated a number which is dependant on if Wall and previous locations, and return the random value
int ghostRandom(int ghostY, int ghostX, int value) {
    int random = rand() % (4) + 1;
    //if random number causes ghost to go into the wall, or is a previous location the function is recalled to provide a different number to the ghost function
    if (random == 1 && (isWall((ghostY + 1), ghostX) == 0) || random == 1 && 2 == value) {
        return ghostRandom(ghostY, ghostX, value);
    } else if (1 == value && random == 2 || random == 2 && isWall((ghostY - 1), ghostX) == 0) {
        return ghostRandom(ghostY, ghostX, value);
    } else if (4 == value && random == 3 || random == 3 && isWall((ghostY), ghostX - 3) == 0) {
        return ghostRandom(ghostY, ghostX, value);
    } else if (3 == value && random == 4 || random == 4 && isWall((ghostY), ghostX + 3) == 0) {
        return ghostRandom(ghostY, ghostX, value);
    }
    return random;
}

// Ghost function, determine the actions of the ghosts
void ghost(int YLocation, int XLocation, char direction) {
    temp = ' ';
    tempB = ' ';
    //If the location matches that of the first ghost
    if (YLocation == ghostYLocation && XLocation == ghostXLocation) {
        int status = 0;
        int distance;
        int newYL = YLocation;
        int newXL = XLocation;
        // Depending on direction the distance travelled to closest edge is defined
        if (UP == direction) {
            distance = ghostYLocation;
        } else if (DOWN == direction) {
            distance = 10 * 3 - ghostYLocation;
        } else if (RIGHT == direction) {
            distance = 10 * 3 - ghostXLocation;
        } else if (LEFT == direction) {
            distance = ghostXLocation / 3;
        }
        //for loop to cycle through and check the characters in each of the locations in the specified directions
        for (int i = 1; i <= distance; i++) {
            if (direction == UP) {
                newYL = ghostYLocation - 1;
                YLocation = ghostYLocation - i;
            } else if (direction == DOWN) {
                newYL = ghostYLocation + 1;
                YLocation = ghostYLocation + i;
            } else if (direction == RIGHT) {
                newXL = ghostXLocation + 3;
                XLocation = ghostXLocation + (3 * i);
            } else if (direction == LEFT) {
                newXL = ghostXLocation - 3;
                XLocation = ghostXLocation - (3 * i);
            }
            // If spot is occupied by Pacman the ghost goes towards pacman - X and Y location are updated accordingly
            if (mapChar[YLocation][XLocation] == PACMAN) {
                mapChar[ghostYLocation][ghostXLocation] = temp;
                temp = mapChar[newYL][newXL];
                mapChar[newYL][newXL] = GHOST;
                ghostXLocation = newXL;
                ghostYLocation = newYL;
                break;
                // If spot  occupied by a wall the search ends
            } else if (isWall(YLocation, XLocation) == 0) {
                status = 1;
                break;
            } else
                status = 2;
        }
        // If a wall has been scanned in the current direction search the next direction for pacman using a recursive function
        if (status == 1) {
            if (direction == UP) {
                ghost(ghostYLocation, ghostXLocation, DOWN);
            } else if (direction == DOWN) {
                ghost(ghostYLocation, ghostXLocation, RIGHT);
            } else if (direction == RIGHT) {
                ghost(ghostYLocation, ghostXLocation, LEFT);

            //if all directions fail to find pacman the randomized code is ran to cause the ghost to move
            } else {
                int random = ghostRandom(ghostYLocation, ghostXLocation, Value1);
                // Moves around the map according to the random function
                if (random == 1) {
                    mapChar[ghostYLocation][ghostXLocation] = temp;
                    temp = mapChar[ghostYLocation + 1][ghostXLocation];
                    mapChar[ghostYLocation + 1][ghostXLocation] = GHOST;

                    ghostYLocation += 1;
                    return;
                } else if (random == 2) {
                    mapChar[ghostYLocation][ghostXLocation] = temp;
                    temp = mapChar[ghostYLocation - 1][ghostXLocation];
                    mapChar[ghostYLocation - 1][ghostXLocation] = GHOST;

                    ghostYLocation -= 1;
                    return;
                } else if ((random == 3)) {
                    mapChar[ghostYLocation][ghostXLocation] = temp;
                    temp = mapChar[ghostYLocation][ghostXLocation - 3];
                    mapChar[ghostYLocation][ghostXLocation - 3] = GHOST;


                    ghostXLocation -= 3;
                    return;
                } else if (random == 4) {
                    mapChar[ghostYLocation][ghostXLocation] = temp;
                    temp = mapChar[ghostYLocation][ghostXLocation + 3];
                    mapChar[ghostYLocation][ghostXLocation + 3] = GHOST;

                    ghostXLocation += 3;
                    return;
                }
                Value1 = random;
                return;
            }
            return;
        }
        // Ghost 2
        // //If the location matches that of the second ghost
    } else if (YLocation == ghost2YLocation && XLocation == ghost2XLocation) {
        int status = 0;
        int distance;
        int newYL = YLocation;
        int newXL = XLocation;
        // Depending on direction the distance travelled to closest edge is defined
        if (UP == direction) {
            distance = ghost2YLocation;
        } else if (DOWN == direction) {
            distance = 10 * 3 - ghost2YLocation;
        } else if (RIGHT == direction) {
            distance = 10 * 3 - ghost2XLocation;
        } else if (LEFT == direction) {
            distance = ghost2XLocation / 3;
        }
        //for loop to cycle through and check the characters in each of the locations in the specified directions
        for (int i = 1; i <= distance; i++) {
            if (direction == UP) {
                newYL = ghost2YLocation - 1;
                YLocation = ghost2YLocation - i;
            } else if (direction == DOWN) {
                newYL = ghost2YLocation + 1;
                YLocation = ghost2YLocation + i;
            } else if (direction == RIGHT) {
                newXL = ghost2XLocation + 3;
                XLocation = ghost2XLocation + (3 * i);
            } else if (direction == LEFT) {
                newXL = ghost2XLocation - 3;
                XLocation = ghost2XLocation - (3 * i);
            }
            // If spot is occupied by Pacman the ghost goes towards pacman - X and Y location are updated accordingly
            if (mapChar[YLocation][XLocation] == PACMAN) {
                mapChar[ghost2YLocation][ghost2XLocation] = tempB;
                tempB = mapChar[newYL][newXL];
                mapChar[newYL][newXL] = GHOST;
                ghost2XLocation = newXL;
                ghost2YLocation = newYL;
                break;
            // If spot  occupied by a wall the search ends
            } else if (isWall(YLocation, XLocation) == 0) {
                status = 1;
                break;
            } else
                status = 0;
        }
        // If a wall has been scanned in the current direction search the next direction for pacman using a recursive function
        if (status == 1) {
            if (direction == UP) {
                ghost(ghost2YLocation, ghost2XLocation, DOWN);
            } else if (direction == DOWN) {
                ghost(ghost2YLocation, ghost2XLocation, RIGHT);
            } else if (direction == RIGHT) {
                ghost(ghost2YLocation, ghost2XLocation, LEFT);

            //if all directions fail to find pacman the randomized code is ran to cause the ghost to move
            } else {
                int random2 = ghostRandom(ghost2YLocation, ghost2XLocation, Value2);

                // Moves around the map according to the random function
                if (random2 == 1) {
                    mapChar[ghost2YLocation][ghost2XLocation] = tempB;
                    tempB = mapChar[ghost2YLocation + 1][ghost2XLocation];
                    mapChar[ghost2YLocation + 1][ghost2XLocation] = GHOST;
                    ghost2YLocation += 1;
                    return;
                } else if (random2 == 2) {
                    mapChar[ghost2YLocation][ghost2XLocation] = tempB;
                    tempB = mapChar[ghost2YLocation - 1][ghost2XLocation];
                    mapChar[ghost2YLocation - 1][ghost2XLocation] = GHOST;

                    ghost2YLocation -= 1;
                    return;
                } else if ((random2 == 3)) {
                    mapChar[ghost2YLocation][ghost2XLocation] = tempB;
                    tempB = mapChar[ghost2YLocation][ghost2XLocation - 3];
                    mapChar[ghost2YLocation][ghost2XLocation - 3] = GHOST;
                    ghost2XLocation -= 3;
                    return;
                } else if (random2 == 4) {
                    mapChar[ghost2YLocation][ghost2XLocation] = tempB;
                    tempB = mapChar[ghost2YLocation][ghost2XLocation + 3];
                    mapChar[ghost2YLocation][ghost2XLocation + 3] = GHOST;
                    ghost2XLocation += 3;
                    return;
                }
                Value2 = random2;
                return;
            }
        } else
            return;
    }
}

//Check if Wall Function - prevents the characters from entering walls

int isWall(int YLocation, int XLocation) {
    if (mapChar[YLocation][XLocation] == WALL)
        return 0;
    else
        return 1;
}

// Main Function
int main() {
    char input;
    char **map = readMap("map.txt");
    // Loop through the gameplay functions while neither of the win or lose conditions are met
    do {
        printMap(map);
        //get user input
        input = getch();
        ghost(ghostYLocation, ghostXLocation, UP);
        ghost(ghost2YLocation, ghost2XLocation, UP);
        // Move Pacman right
        if (input == RIGHT && isWall(pacmanYLocation, pacmanXLocation + 3) == 1) {
            // If Pacman is touching a dot, eat it
            if (mapChar[pacmanYLocation][pacmanXLocation + 3] == DOT)
                dot -= 1;
            mapChar[pacmanYLocation][pacmanXLocation + 3] = PACMAN;
            mapChar[pacmanYLocation][pacmanXLocation] = EMPTY;
            pacmanXLocation += 3;
            // Move Pacman left
        } else if (input == LEFT && isWall(pacmanYLocation, pacmanXLocation - 3) == 1) {
            // If Pacman is touching a dot, eat it
            if (mapChar[pacmanYLocation][pacmanXLocation - 3] == DOT)
                dot -= 1;
            mapChar[pacmanYLocation][pacmanXLocation - 3] = PACMAN;
            mapChar[pacmanYLocation][pacmanXLocation] = EMPTY;
            pacmanXLocation -= 3;
            // Move Pacman down
        } else if (input == DOWN && isWall(pacmanYLocation + 1, pacmanXLocation) == 1) {
            // If Pacman is touching a dot, eat it
            if (mapChar[pacmanYLocation + 1][pacmanXLocation] == DOT)
                dot -= 1;
            mapChar[pacmanYLocation + 1][pacmanXLocation] = PACMAN;
            mapChar[pacmanYLocation][pacmanXLocation] = EMPTY;
            pacmanYLocation += 1;
            // Move Pacman up
        } else if (input == UP && isWall(pacmanYLocation - 1, pacmanXLocation) == 1) {
            // If Pacman is touching a dot, eat it
            if (mapChar[pacmanYLocation - 1][pacmanXLocation] == DOT)
                dot -= 1;
            mapChar[pacmanYLocation - 1][pacmanXLocation] = PACMAN;
            mapChar[pacmanYLocation][pacmanXLocation] = EMPTY;
            pacmanYLocation -= 1;
        }
    } while (winCheck() == 0 && loseCheck() == 0);
    printMap(map);
}


