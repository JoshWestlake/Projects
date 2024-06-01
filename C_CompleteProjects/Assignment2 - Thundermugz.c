#include <stdio.h>
#include <math.h>
//i acknologe the faact that this is all my own work, and none of the code has been sourced directly from another location
    int main(){

     //initialize the variable students
     float boxMass, throneMass, totalMass;//initialize the float variables
     int students, minutes,seconds, time;//initailize integer variables
     int maxMass = 300;//initialize the maximum wieght each personn can carry
     double gravity = 9.81;//initialize the variable gravity, setting it equal t0 9.81 as it's a constant

        //provoking the user for the information, and scanning for boxMass
        printf ("Enter the mass of the box spring in kg: ");
        scanf("%f",&boxMass);

        //provoking the user for information, and scanning for throneMass
        printf ("Enter the mass of the throne in kg: ");
        scanf("%f",&throneMass );

        //generating the empty line
        printf("\n");
        //add the throne and box masses to get an overall total mass
        totalMass = throneMass + boxMass;

        //calculate for the amount of students required to hold the thundermugz, and using ceil function to round to next whole number
     students  = ceil((boxMass+throneMass)*gravity/maxMass);

     //calculate for time and use the quotient to find the minutes and seconds of the time
     time = (boxMass+throneMass)* (4-exp(0.1*students));

     minutes = time/60;
     seconds = time % 60;
     //print the results to the user
     printf("The ThunderMugz will need a minimum of %d students to carry it.\nIt will take %d minutes and %d seconds to complete the ThunderMugz challenge.", students, minutes, seconds);

    }
