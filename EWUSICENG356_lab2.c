
/*
 ============================================================================
 Name        : Lab2.c
 Author      : Austin Tian
 Version     :
 Copyright   : Copyright 2020
 Description : Signed number and unsigned numbers, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 32   // maximum size of the binary number is 32 bit.
#define number1 "11000001010010000000000000000000"
#define number2 "01000001010101000000000000000000"
void convert_binary_to_signed(const char *binary);
void convert_binary_to_float(const char *binary);
char *menu =    "\n" \
                "\n" \
                "===================================================================\n" \
                "************Please select the following options********************\n" \
                " *    1. Binary number to signed decimal number conversion.(Lab 2) *\n" \
                " *    2. Binary number to Floating number conversion (Lab 2)       *\n" \
                " *******************************************************************\n" \
                " *    e. To Exit, Type 'e'                                         *\n" \
                " *******************************************************************\n";

int main(void) {
	    char options;  // the option should only be a byte
        char inputs[33] = {0};  // 32-bit string plus a ending indicator.
        do{
            puts(menu); /* prints Memory Simulation */
            fflush(stdin);  // clear the input buffer before getchar.
            options = getchar();
            fflush(stdin);  // clear the input buffer after getchar.
            switch (options)
            {
                case '1': /* lab 2. Convert binary number into a SIGNED decimal
                           number and display */
                    puts("Please input your BINARY number, "\
                            "I will convert it to signed decimal:");
                    scanf("%s", &inputs[0]);  // Input must be a string with 0/1
                    // Finish function convert_binary_to_signed to convert the 8-bit binary inputs to signed decimal number.
                    convert_binary_to_signed(inputs);
                    continue;
                case '2':/* lab 2. Convert 32-bit binary number into a floating
                          *  point number number and display */
                    puts("Please input your 32-bit floating point number " \
                            "in binary, I will convert it to decimal");
                    scanf("%s", &inputs[0]);  // Input must be a string with 0/1
                    // Finish function convert_binary_to_float to convert the 32-bit binary inputs to floating point number.
                    convert_binary_to_float(inputs);
                    continue;
                case 'e':
                    puts("Code finished, exit now");
                    return EXIT_SUCCESS;
                default:
                    puts("Not a valid entry, exit now");
                    continue;
            }
        }while (1);
}



void convert_binary_to_signed(const char *binary) {
    // checking to see that the binary number is 8 bits long
    if (strlen(binary) != 8) {
        puts("The number should be 8 bits long!");
        return;
    }

    // looping through the binary string to checks that all the digits are valid
    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] != '1' && binary[i] != '0') {
            puts("This is not a valid binary number!\n"\
                 "The number should only contain 1s and 0s");
            return;
        }
    }

    // Convert binary to signed decimal
    int decimal = 0;
    int weight = 1; // start from the least significant bit
    for (int i = 7; i > 0; i--) {
        decimal += (binary[i] - '0') * weight;
        // subracting the binary digit by the ascii character '0' to get the associated decimal value
        // multiplying the decimal by thee weights factor
        weight *= 2; // incrementally increasing the weight factor by the multiple of 2
    }

    // If the most significant bit is 1, it's a negative number
    if (binary[0] == '1') {
        decimal = decimal - 128; // subtract 2^7 to get the negative value
    }

    printf("The signed decimal: %d\n", decimal);

}


void convert_binary_to_float(const char *binary){
    // checking to see that the binary number is atleast 8 bits long
    if (strlen(binary) < 8) {
        puts("The number should be 8 bits long!");
        return;
    }

    // looping through the binary string to checks that all the digits are valid
    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] != '1' && binary[i] != '0') {
            puts("This is not a valid binary number!\n"\
                 "The number should only contain 1s and 0s");
            return;
        }
    }

    // Getting the Sign Bit
    int sign = (binary[0] == '1') ? -1 : 1; // using the ternary operator to determine sign

    // Using the exponent
    int exponent = 0;
    // converting the next 8 bits to a decimal number
    for (int i = 1; i <= 8; i++) {
        exponent = exponent * 2 + (binary[i] - '0');
    }

    // Unbias the Exponent
    exponent -= 127;

    // Convert the Mantissa into Decimal
    float mantissa = 1.0;
    // Start with 1.0 and adding the value of each bit divided by its positional value
    for (int i = 9; i < 32; i++) {
        mantissa += (binary[i] - '0') * pow(2, 8 - i);
    }

    // Calculate the Magnitude of the Overall Value
    float magnitude = pow(2, exponent) * mantissa;
    // multiplying the mantissa by 2 raised to the power of the exponent

    // Factor in the Sign Bit
    float number = sign * magnitude;

    printf("The floating-point decimal: %f\n", number);
}
