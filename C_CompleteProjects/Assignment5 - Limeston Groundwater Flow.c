#include <stdio.h>
#include <math.h>
#include <string.h>
//I attest to the originality of this code
int main() {
    //initalize the variables associated, limestone, minimumLimestone, porosity, conductivity, specificGravity, smallestGravity
    int limeStones;
    int minimumLimestone;
    float porosity;
    float conductivity;
    float specificGravity;
    float smallestGravity = 100;

    //provoke the user for the user inputed values, limestone, peroxity hydraulic conductivity, and specific gravity
    printf("Enter the number of limestones to compare: ");
    scanf("%d", &limeStones);
    //create the stoneArrays designed to store the inputed values as a matrix
    float stoneArray [limeStones][3];

    //for loop to store the variables within the array
    for(int i=0;i<=limeStones-1;i++) {
        printf("\nEnter the porosity %, hydraulic conductivity (m/s), and specific gravity for Limestone %d: \n", i + 1);
        scanf("%f %f %f", &porosity, &conductivity, &specificGravity);
        stoneArray[i][1] = porosity;
        stoneArray[i][2] = conductivity;
        stoneArray[i][3] = specificGravity;

        //if statement to determine weather the specific gravity is less than the previously determined value. If yet, the new value becomes the new minimum and is stored to be outputted to the user
        if (stoneArray[i][3] < smallestGravity) {
            smallestGravity = stoneArray[i][3];
            minimumLimestone = i + 1;
        }
    }
    //output the results to the user
        printf("The limestone with the lowest specific gravity is Limestone %d with a specific gravity of %0.4f\n", minimumLimestone, smallestGravity);
        printf("Flow velocities: \n");

        //create a second array capable of storing an additional column of value for the flow
    float flowArray [limeStones][4];

    //nested for loop to assign the variables in the matrix equal to the values stored in stoneArray
    for(int k = 0; k <= limeStones; k++){
        for (int l = 0; l <= 3; l++)
        {
            flowArray[k][l] = stoneArray[k-1][l];
        }
    }
    //initialize variables to track the statues of the nested if statements within the for loop to determine whether large porosity is the same as maximum flow
    float maxPorosity =0;
    int PorosityStone;
    float maxFlow= 0;
    int FlowStone;

    //for loop designed to calculate and store the values for the respective flow rates
    for(int j=1;j<=limeStones;j++) {
        flowArray[j][4] = -1 * 100 * flowArray[j][2] * 12000000 * -0.725;//converted the 1200m^2 to cm^2, and converted the hydraulic conductivity to m from cm then utilize the provided equation
        printf("Limestone %d: %0.2f cm^3/s\n", j, flowArray[j][4]);//output the results to the user

        //nested if statements to determine which limestone has the greatest porosity
        if (maxPorosity < flowArray[j][1]) {
            maxPorosity = flowArray[j][1];
            PorosityStone = j;
        }
        //nested if statements to determine which limestone has the greatest flowrate
        if (maxFlow < flowArray[j][4]) {
            maxFlow = flowArray[j][4];
            FlowStone = j;
        }
    }
    //compare the flow rate to the porosity of the stone and output the results to the user
        if (PorosityStone == FlowStone)
            printf("The rock with the highest porosity has the highest flow velocity.");
        else
            printf("The rock with the highest porosity does not have the highest flow velocity.");



        return 0;
    }


