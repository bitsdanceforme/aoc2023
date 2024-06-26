// https://code.visualstudio.com/docs/cpp/config-mingw
// https://www.tutorialspoint.com/c_standard_library/string_h.htm


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, void* argv[])
{
    int currentValue = 0;
    int totalValue = currentValue;

    const char inputFileName[] = "input.txt";

    FILE* input = fopen(inputFileName, "r");
    int lineCount = 0;

    
    if(input == NULL)
    {
        printf("Error opening file %s\n", input);
        return -1;
    }
    const char possibleChars[] = "0123456789";
    
    //while(input !=NULL)
    while(1)
    {
        printf("line count: %d\n", lineCount);
    
        char inputString[2048];
        inputString[0] = '\n';

        char* result = fgets(inputString, sizeof(inputString), input);
        if(result == NULL)
        {
            printf("Done!\n");
            break;
        }
        else
            lineCount++;

        // Find pointers to 0-9
        // Find pointers to zero-nine
        // Take the smallest and largest pointers
        // convert zero-nine to number, if needed

        char digits[3];
        digits[0] = '\n';

        

        char* ptr = strpbrk(inputString, possibleChars); //find first digit
        digits[0] = ptr[0];

        // no easy way to find last so keep track of previous
        ptr = strpbrk(ptr, possibleChars);
        while(ptr != NULL)
        {
            digits[1] = ptr[0];
            ptr = strpbrk(++ptr, possibleChars);
        }    
        //printf("digits[1] = %c", digits[1]);
        printf("digits = %s\n", digits);

        currentValue = atoi(digits);
        totalValue+=currentValue;
    }

     fclose(input);
    
    printf("Value %d\n", totalValue);
   
}