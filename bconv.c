//Atticus Nafziger
//Assignment 3 - CSCI 304 - Computer Organization Spring 2024
//
//A simple base convertion program to switch between hex, octal, and decimal
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> //to exit program
#include <string.h>




short get_operand (char mode)// read in numeric value in mode; return value
{
    short value;

    switch (mode) {
        case 'O':
            printf("Enter octal value: ");
            break;
        case 'H':
            printf("Enter hex value: ");
            break;
        case 'D':
        default:
            printf("Enter decimal value: ");
            break;
    }
    int scanned;

    if (mode == 'H') {//Convert to decimal before doing anything else, makes everything more easy
        scanned = scanf("%hx", &value);
        printf("%hX\n", value);
    } else if (mode == 'O') {
        scanned = scanf("%ho", &value);
        printf("%ho\n", value);
    } else {
        scanned = scanf("%hd", &value);
        printf("%hd\n", value);
    }
    printf("\n");
    return value;
}

void print_bases (short val, char mode)// print out base values and str for mode
{
    printf("****************************************\n");
    char mode_string[10];//extra space in case
    switch(mode){
        case 'H':
            strcpy(mode_string, "Hex");
            break;
        case 'O':
            strcpy(mode_string, "Oct");
            break;
        case 'D':
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
    printf("%s\n", option);
    
    if (strlen(option) != 1) {//this checks if the length of the input is longer than 1 so I can automatically get rid of them
        printf("\nInvalid option: %s\n\n", option);
        return print_menu();
    }

    //option[0] = toupper(option[0]);
    return option[0];
}

int main(void)
{   
    short val; 
    char mode; 
    char option;
    char start_opt = 'D';

    short start_val = 0;
    
    val = start_val;
    mode = start_opt;
    printf("\n");
    print_bases(start_val, start_opt);
    



do {
    option = print_menu();

    switch (option) {
        case 'C':
        case 'c':
            printf("\n");
            int zero = 0;
            val = zero;
            print_bases(zero, mode);
            continue;

        case 'S':
        case 's':
            val = get_operand(mode);
            print_bases(val, mode);
            break;

        case 'Q':
        case 'q':
            break;

        case 'O':
        case 'o':
            mode = 'O';
            printf("Mode: Octal\n\n");
            print_bases(val, toupper(option));
            break;

        case 'H':
        case 'h':
            mode = 'H';
            printf("Mode: Hexadecimal\n\n");
            print_bases(val, toupper(option));
            break;

        case 'D':
        case 'd':
            mode = 'D';
            printf("Mode: Decimal\n\n");
            print_bases(val, toupper(option));
            break;

        default:
            printf("\nInvalid option: %c\n\n", option);
            continue;
        }

    } while (option != 'Q' && option != 'q');
    return(0);
}
