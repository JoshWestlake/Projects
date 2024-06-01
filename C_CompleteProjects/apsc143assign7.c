#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//This program is designed to intake information from a txt file, print it, sort it, and then output to another txt file the results

int main()
{
//attest to the originality of this Code
//access the outsourced data from the files - initialize as a pointer
FILE* fp;
FILE* oresFP;

//Set the varibled equual to pointers to each file - w is a writing file, r is reading
oresFP = fopen("ores.txt", "w");
fp = fopen("payloads.txt", "r");

//intitialize varibles
int rows;
int column=2;
int unitPrice = 8500;

//concider the possibility for the file to not be accessed and have a failure message
if(fp == NULL)
{
printf("File not found ");
}
//else - the file can be accessed
else {
    //gather input from the first integer in the txt file - so we know the size of the pointer array - than initialize the pointer
        fscanf(fp, "%d", &rows);
        float **ores = (float **) malloc(rows * column * sizeof(int));//should be making array of [rows][columbs]

        //for loop to loop through each of the rows,and intitialize the size of each row
        for (int i = 0; i < rows; i++) {
                ores[i] = (float*)malloc(3*sizeof(float));

            }
        //runs through the file and gathers the data, setting it to locations within the pointer array
        for(int j = 0; j<rows;j++)
        {
        fscanf(fp, "%f %f", &ores[j][0], &ores[j][1]);

        ores[j][2] = (unitPrice*ores[j][0]*ores[j][1]);//fills the third colum with the ore value
        }

        //print the gathered data to the user
        printf("Payload Data:\nTotal Mass / Grade / Ore Value\n");
        for(int k = 0; k<rows; k++) {
             printf("   %.0f      %.2f    $%.0f\n", ores[k][0], ores[k][1], ores[k][2]);
        }
//sorting the file - using bubble sort from smallest values of the third colum to largest

//for loops to run through the code
for(int i = 0; i < rows-1; i++)
{

    for (int j = 0; j< rows-i-1; j++)
    {
        //if the ore[j] is less than the ore below it, the ores will swap locations
        if (ores[j][2] < ores[j+1][2])
        {
            //create a temporary float which will save the data within ore[j] to be trasfered to the other row
            float bubble[3] = {ores[j][0],ores[j][1],ores[j][2]};

                ores[j][2] = ores[j+1][2];
            //ore[j+1] becomes equal to the original values for ore[j]
            for(int n = 0; n<3; n++) {
                ores[j + 1][n] = bubble[n];

            }
        }
    }
}
//print to the output file - ores.txt
fprintf(oresFP, "Sorted Payload Data:\nTotal Mass / Grade / Ore Value\n");
for( int i = 0; i < rows; i++)
{
    fprintf(oresFP,"   %.0f      %.2f    $%.0f\n", ores[i][0], ores[i][1], ores[i][2]);
}
}

}






