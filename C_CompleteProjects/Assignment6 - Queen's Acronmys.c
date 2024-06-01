#include <stdio.h>
#include <string.h>
//I attest to the originality of this code
int main() {
//initialze the variablees
int number;
int counter = 0;


//gather input from user - using scanf
printf("Enter number of acronyms to add to the database: ");
scanf("%d", &number);
char Acronym[number][50];//initialize the userAcronym
char String[number][50];//initialize the userString

    //clear the arrays
    for (int a = 0; a <= number; a++) {

        for (int b = 0; b <= 50; b++) {
            String[a][b] = '\0';
            Acronym[a][b] = '\0';
        }
    }
    //sacrificial array accounting for the error between fgets and scanf code
    char null[10];
    fgets(null, 10, stdin);


    //for loop which runs until the chosen number of inputs have been reached
    for (int j = 0; j < number; j++) {

        //gather userinput - using fgets
        printf("Enter the string to convert into an acronym: ");
        fgets(String[j], 50, stdin);

        //for loop to sort through the string and find capitialized letters
        for (int i = 0; i < strlen(String[j]); i++) {

            //if the letter is between the ASII of A and Z
            if (String[j][i] >= 'A' && String[j][i] <= 'Z') {
                Acronym[j][counter] = String[j][i];//stores the letter as a part of the acronym array
                counter++;//counter increase by 1 so next letter goes to next part of array
            }

        }
        counter = 0;//reset the counter
        printf("Acronym of \"%s\" is \"%s\"\n", String[j], Acronym[j]);//display to user
    }


    char fixedString[50];//initialize secondaryString
  
    //clear the arrays
        for (int c = 0; c <= 50; c++) {
            fixedString[c] = '\0';

        }
        //do while loop which endlessly runs until told to break
    do {
        //gather input from user
        printf("Enter the acronym of the string you would like to see, or enter 0 to exit: ");
        fgets(fixedString, 50, stdin);//gather input

        //check if user input is 0 for exit measures
        if(fixedString[0]=='0')
        {
            break;
        }

        //"Purify the Strings"
        for(int d = 0; d<=50; d++)
        if(fixedString[d] >= 'A' && fixedString[d] <= 'Z')
        {}
        else
        {
            fixedString[d] = '\0';
        }
        for(int e = 0; e<number; e++) {
            for(int f = 0; f<50; f++) {
                if (Acronym[e][f] >= 'A' && Acronym[e][f] <= 'Z') {}
                else {
                    Acronym[e][f] = '\0';
                }
            }
        }

        //For loop indicating in increase in k value - representative of the array number for each stored acronym
        for (int k = 0; k < number; k++) {

            int comparison = strcmp(fixedString, Acronym[k]);


            //the acronym is the same as the inputed string
            if (comparison==0) {
                printf("The corresponding string to \"%s\" is \"%s\".\n", fixedString, String[k]);
            }
            //if not a valid input
            else
            {
                printf("No match found.");
            }
        }
    }

        while (1);


        if (number == 0) {
            return 0;
        }


    return 0;

}