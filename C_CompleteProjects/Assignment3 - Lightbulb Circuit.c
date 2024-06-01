#include <stdio.h>
#include <math.h>
//I attest to the originality of this code
//Code to examine the elctrical circuit and access its various components, such as the voltages, current, and switch
int main() {

    float time;//initialize the user inputed time variable
    float voltage;//initialize the voltage variable
    double bulbVoltage;//the bulb voltage calculated using the v = IR
    int Totalresistance = 10;//initiialize the total resistance variables, and set it to 10
    int lampResistance= 8;//initiialize the lamp resistance, and set to 8

    printf("Enter time in seconds: ");//provoke the user for the time
    scanf("%f", &time);//scan for time
    voltage = 8*cos(time*M_PI);//calculate the voltage
    bulbVoltage = (voltage/Totalresistance)*lampResistance;//calculate the bulbVoltage using the voltage

    //access the voltage and determine the resulting output to the user
    if (voltage < 0.1 ){printf("Source voltage is negative\n");}
    else if (voltage == 0){printf("Source voltage is 0\n");}
    else if (voltage > 0.1){printf("Source voltage is positive\n");}


    //if the voltage is less than -0.7 the switch 1 is closed, then update the according info to the user
    if (voltage < -0.7)
    {
        bulbVoltage = 0;
        printf("Switch 1 is closed\n");
        printf("The Voltage of the bulb is %.2f V\n",bulbVoltage);
        printf("The bulb is not on");
         }
    //if the voltage is between 1-6.4 the follwing code runs
    else if(1 < voltage < 6.4)
    {
        //print the voltage, and assess the bulb voltage to determine whether the bulb is activated, or not
        printf("The Voltage of the bulb is %.2f V\n",bulbVoltage);
        if(1< bulbVoltage < 5.2)printf("The bulb is on\n");
        else printf("The bulb is not on");

    }
    //if the voltage is more than 6.4 the switch 2 is closed, then update the according info to the user
    else if (voltage > 6.4)
    {
        bulbVoltage = 0;
        printf("The Voltage of the bulb is %.2f V\n",bulbVoltage);
        printf("Switch 2 is closed");
        printf("The bulb is not on");
    }

    return 0;
}
