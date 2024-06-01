#include <stdio.h>
#include <math.h>
//I attest to the originality of this code
int main() {
    //initialize variables: initialCost, annuity, interestRate, lifeSpan, yearsPast
    double initialCost;
    double annuity;
    double interestRate;
    int lifeSpan;
    int yearsPast = 1;

    //print statements to provoke the user for input, the scan and apply to the according variables
    printf("Enter the initial cost of the project: $");
    scanf("%lf", &initialCost);
    printf("\nEnter the annuity of the project: $");
    scanf("%lf", &annuity);
    printf("\nEnter the interest rate in %: ");
    scanf("%lf", &interestRate);
    interestRate /= 100;//divide by 100 because the intrest rate is provided in percentage
    printf("\nEnter the lifespan of the project in years: \n");
    scanf("%d", &lifeSpan);

    //initialize variable relevant to the while loop: finalPresentValue, PresentValue
    float presentValue = annuity;
    float finalPresentValue;

    //while loop which runs until the years past is greater than or equal to the years past.
    while ( yearsPast <= lifeSpan)
    {
        //use equation to determine the annuity
        presentValue = (annuity/pow((1+interestRate), yearsPast));
        //add the annuity to the final value for an overall sum of the income
        finalPresentValue +=presentValue;
        //increase in years by 1
        yearsPast++;
    }
    //initialize the present worth variable, and set it to the final-initialCost
    double presentWorth = finalPresentValue-initialCost;

    //if statement to determine if the project is financially viable - output result to user
    if (presentWorth > 0)
    {
        printf("Present worth of the project = $%.2lf\n", presentWorth);
        printf("The project is economically feasible.\n");
    }
    //else statement to determine if the project is financially viable - output result to user
    else
    {
        printf("The project is not economically feasible.\n");
        printf("Present worth of the project = -$%.2lf\n", -1*presentWorth);
    }
    //reset the years past variable to zero and recalculate, set present worth to negative initial cost
    yearsPast = 0;
    presentWorth = -initialCost;

    //while loop to run while present worth is greater than zero, determines the payback period by subtracting initial from the annuity
    //must increase the years past each time the loop is run to store for output to user
    while(presentWorth < 0)
    {
        yearsPast++;
        presentWorth = presentWorth + (annuity/pow((1+interestRate), yearsPast));

    }
    //output the results to the user
    printf("The payback period for this project is %d years.", yearsPast);
    return 0;
}
