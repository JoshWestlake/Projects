
#include <stdio.h>
#include <math.h>
//initialize the functions used within the code
double riemann(double top, double bottom, double interval);//collect doubles and output data equal to the riemann sum
double TaylorApprox(double x, double terms );//collect doubles and output data equal to the taylor approximation
double factorial(double number);//collect doubles and output factorial of the input
double taylorRiemann(double top, double bottom, double interval);//collect doubles and output data equal to the taylor sum
double compare(double taylor, double riemann);//compares the output of the given values

int main() {
    //get user input
    double top, bottom;
    printf("Enter the bounds to compute the Riemann Sum: ");
    scanf("%lf %lf", &bottom, &top);

    //output the results of the Riemann sum
    printf("Riemann Sum with 5 intervals: %.2lf\n", riemann(top,bottom,5));
    printf("Riemann Sum with 25 intervals: %.2lf\n", riemann(top,bottom,25));
    printf("Riemann Sum with 100 intervals: %.2lf\n", riemann(top,bottom,100));

    printf("--------------------------------------------------------\n");
    //output the results of the Taylor Approximation
    printf("Taylor Series Approximation at x = %.2lf with 3 terms: %.2lf\n", bottom, TaylorApprox(bottom, 3));
    printf("Taylor Series Approximation at x = %.2lf with 5 terms: %.2lf\n", bottom, TaylorApprox(bottom, 5));
    printf("Taylor Series Approximation at x = %.2lf with 10 terms: %.2lf\n", bottom, TaylorApprox(bottom, 10));

    printf("--------------------------------------------------------\n");

    //output the results of the Taylor Riemann Sum
    printf("Taylor Series Riemann Sum with 5 intervals: %.2lf\n", taylorRiemann(top,bottom,5));
    printf("Taylor Series Riemann Sum with 25 intervals: %.2lf\n", taylorRiemann(top,bottom,25));
    printf("Taylor Series Riemann Sum with 100 intervals: %.2lf\n", taylorRiemann(top,bottom,100));

    printf("--------------------------------------------------------\n");
    //Outputs the error between the riemann and taylor riemann sums
    printf("Error in Riemann Sums with 5 intervals: %.2lf%%\n", compare(taylorRiemann(top,bottom,5), riemann(top,bottom,5)));
    printf("Error in Riemann Sums with 25 intervals: %.2lf%%\n", compare(taylorRiemann(top,bottom,25), riemann(top,bottom,25)));
    printf("Error in Riemann Sums with 100 intervals: %.2lf%%\n", compare(taylorRiemann(top,bottom,100), riemann(top,bottom,100)));
    return 0;
}
//Function to generate the riemann sum of the function e^x^2 between the given bound - with a set number of intervals
//Recieves 3 double values - outputs 1
double riemann(double top, double bottom, double intervals)
{
 //initiate variable - resets their values each time the function is run
 double sum = 0;
 double x = bottom;
 double deltaX = (top - bottom)/intervals;
 int i =0;

 //while loop which runs interval amount of times
 while(i< intervals)
 {
            //calculates the area of the value at each x value and adds to the overall sum of the system
             sum += deltaX*pow(M_E,pow(x,2));
             x += deltaX;
             i++;
 }
 //return statement
 return sum;
}
//Function to generate the taylor sum of the function e^x^2 between the given bound - with a set number of intervals
//Receives 2 double values - outputs 1
double TaylorApprox(double x, double terms)
{
//initiate variable sum and  reset it to zero
double sum =0;

//for loop running terms times
for(int n = 0; n<terms; n++)
{
  //calculate the taylor approx and adds to the total sum
  sum += pow(x, 2*n)/factorial(n);
}
//return statement
return sum;
}
//collect doubles and output data equal to the taylor sum
//Receives 3 double values - outputs 1
double taylorRiemann(double top, double bottom, double interval)
{
    //initiate varibles and reset each time the function is run
    double sum = 0;
    double x = bottom;
    double deltaX = (top - bottom)/interval;
    int i=0;

    //while loop runs interval amount of times
    while(i<interval)
    {
        //calculates the area of the space between deltax and the taylor approx at x then adds to the sum
        sum += deltaX*TaylorApprox(x, 10.00);
        x += deltaX;
        i++;
    }
    //return statement
    return sum;
}
//function compares the 2 values inputed
//Recieves 2 double, outputs 1 double
double compare(double taylor, double riemann)
{
    //calculate the difference in the 2 values, transfer it to a percentage and subtract 100 to get the error
    return ((taylor / riemann) * 100) - 100;
}
//Factorial function to calculate the factorial of the given value
//Recieves 1 double, outputs 1 double
double factorial(double number) {
    //since factorial of 1 is 1 set to 1
    double factorial = 1;

    //for loop that runs number times
    for (int i = number; i > 0; i--)
    {
        //get the value of the factorial times the current i value of the for loop adds to the overall sum
        factorial = factorial* i;
    }
    //return statement
    return factorial;
}
