#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> //to exit program
#include <string.h>
//global variables
short val; 
char mode; 

short get_operand (char mode)// read in numeric value in mode; return value
{
    short value;

    switch (mode) {
        case 'o':
            printf("Enter octal value: ");
            break;
        case 'h':
            printf("Enter hex value: ");
            break;
        case 'd':
            printf("Enter decimal value: ");
            break;
    }
    int scanned;

    if (mode == 'h') {//Convert to decimal before doing anything else, makes everything more easy
        
        scanned = scanf("%hx", &value);
    } else if (mode == 'o') {
        scanned = scanf("%ho", &value);
    } else {
        scanned = scanf("%hd", &value);
    }
    printf("\n");
    return value;
}

void print_bases (short val, char mode)// print out base values and str for mode
{
    printf("****************************************\n");
    char mode_string[10];//extra space in case
    switch(mode){
        case 'h':
            strcpy(mode_string, "Hex");
            break;
        case 'o':
            strcpy(mode_string, "Oct");
            break;
        case 'd':
            strcpy(mode_string, "Dec");
            break;
    }
    //Need for formatting of decimal, there is prob an easier way of doing this
    int decimal_width = 1;
    short temp = val;
    while (temp /= 10) {//this finds out how "wide" the number is
        decimal_width++;
    }

    // Calculate the number of spaces, guessed and checked
    int spaces = 23 - decimal_width;

    printf("* Base Values:         Input Mode: %s *\n", mode_string);
    if (val < 0) {//for negative nums
        printf("*   Hex     :  %04X                    *\n", val & 0xFFFF);//the 0xFFFF gets the lower 16 bits so it isnt all weird looking and wrong
        printf("*   Octal   :  %06o                  *\n", val & 0xFFFF);
        printf("*   Decimal :  %*d%*s*\n", decimal_width, val, spaces, "");//included in the if statement bc I needed to remove another space for alignment bc of minus
    } else {
        printf("*   Hex     :  %04X                    *\n", val);
        printf("*   Octal   :  %06o                  *\n", val);
        printf("*   Decimal :  %*d%*s *\n", decimal_width, val, spaces, "");
    }
    printf("****************************************\n\n");
}


char print_menu (void)//// print menu; get option until valid; return option
{
    printf("Please select one of the following options: \n\nO  Octal Mode\nH  Hexadecimal Mode\nD  Decimal Mode\n\nC  Clear Value\nS  Set Value\n\nQ  Quit\n");
    char option[30];

    printf("\n");
    printf("Option: ");
    scanf(" %s", option);
    
    if (strlen(option) != 1) {//this checks if the length of the input is longer than 1 so I can automatically get rid of them
        printf("\nInvalid option: %s\n\n", option);
        return print_menu();
    }

    option[0] = tolower(option[0]);

    switch (option[0]) {
        case 'c':

            printf("\n");
            int zero = 0;
            val = zero;
            print_bases(zero, 'd');
            return print_menu();

        case 's':

            val = get_operand(mode);
            print_bases(val, 'd');
            break;

        case 'q':

            //exit(0);//done
            break;

        case 'o':

            mode = 'o';
            printf("Mode: Octal\n\n");
            print_bases(val, option[0]);
            break;

        case 'h':

            mode = 'h';
            printf("Mode: Hexidecimal\n\n");
            print_bases(val, option[0]);
            break;

        case 'd':

            mode = 'd';
            printf("Mode: Decimal\n\n");
            print_bases(val, option[0]);
            break;

        default:

            printf("\nInvalid option: %s\n\n", option);
            return print_menu();
    }


    return option[0];
}

int main(void)
{   
    char start_opt = 'd';

    short start_val = 0;
    
    val = start_val;
    mode = start_opt;
    printf("\n");
    print_bases(start_val, start_opt);
    char option;
    do
    {
        option = print_menu();
    } while (option != 'q');

    //printf("%c\n", option);
    //printf("Did not exit");
    return(0);
}
