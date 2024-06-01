#include <stdio.h>
#include<math.h>

//define the k variable as a constant
#define k 0.0965


//Defines the function reaction which simulates the reaction and has recursion to rerun itself when necassary
float reaction(float elapsedTime, float NH3, float O2, float N2, float H2O);

//main function
int main() {
    //initialize user variables for ammonia concentration, oxygen concentration, and the intervals of time to be used
    float ammonia, oxygen;

    //gather data from the user
    printf("Enter initial ammonia and oxygen concentrations: ");
    scanf("%f %f", &ammonia, &oxygen);

    //output the results to the user by calling the recursive reaction function which will print the alternate outputs to the user
    printf("The reaction will take %.2f seconds to reach a rate 0.001 M/s.", reaction (0, ammonia, oxygen, 0 , 0));
    return 0;
}
//reaction function which intakes 5 floats, and outputs the overall elapsed time of the reaction as a float
float reaction(float elapsedTime, float NH3, float O2, float N2, float H2O)
{
   //define variables for rate and totalTIme elapsed - the rate is going to be equal to the k constant times the concentration of ammonia times the concentration of oxygen squared
   float rate =k * NH3 * pow(O2, 2), time = 0.01;

   //an if statement which differs the code from recursion of the rate is less than or equal to 0.001
   if (rate > 0.001) {
       //Changes the concentration of each variable according to the predefined equations for each which dependent on the moles of each substance
       NH3 -= rate*4*time;
       O2 -= rate*3*time;
       N2 += rate*2*time;
       H2O += rate*6*time;

       //adds the time interval to the total elapsed time
       elapsedTime += time;
       //recursion statement to rerun the function with the updated concentration values for each substance
       return reaction(elapsedTime, NH3, O2, N2, H2O);

   }
   //should the if statement not be true the code will output the results to the user
   else
   {
       //print the according results to the user for NH3, O2, N2, H2O and return the elapsed time to the main
       printf("\nFinal Reaction Molarities: \n");
       printf("NH3: %.2f M\n", NH3);
       printf("O2:  %.2f M\n", O2);
       printf("N2:  %.2f M\n", N2);
       printf("H2O: %0.2f M\n", H2O);
       return elapsedTime;
   }

}
