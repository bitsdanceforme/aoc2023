// https://code.visualstudio.com/docs/cpp/config-mingw
// https://www.tutorialspoint.com/c_standard_library/string_h.htm


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int WINRED = 12;       
const int WINGREEN = 13;
const int WINBLUE = 14;


struct tuple {
    int red;
    int green;
    int blue;
};

int winningGames[100];
int allGames[100];

int numWinningGames()
{
    int total = 0;

    for(int i = 0; i < 100; i++)
    {
        if (winningGames[i] = 1)
        {
            total +=1;
        }
    }
    return total;
}

int findRed(char* str)
{
    char* startPtr = str;
    char* endPtr;
    int retVal = 0;

    endPtr = strstr(str, "red");
    if(endPtr == NULL)
        retVal = 0;
    else
    {
        endPtr--;
        *endPtr = '\n';
        startPtr = --endPtr;
        while( (startPtr[0]  != ' ') && (startPtr >= str) )
        {
            startPtr--;
        }
        startPtr++;        
        retVal = atoi(startPtr);
        *endPtr = ' ';
    }
    return retVal;
}

int findGreen(char* str)
{
    char* startPtr = str;
    char* endPtr;
    int retVal = 0;

    endPtr = strstr(str, "green");
    if(endPtr == NULL)
        retVal = 0;
    else
    {
        endPtr--;
        *endPtr = '\n';
        startPtr = --endPtr;
        while( (startPtr[0]  != ' ') && (startPtr >= str) )
        {
            startPtr--;
        }
        startPtr++;
        retVal = atoi(startPtr);
        *endPtr = ' ';
    }
    return retVal;
}

int findBlue(char* str)
{
    char* startPtr = str;
    char* endPtr;
    int retVal = 0;

    endPtr = strstr(str, "blue");
    if(endPtr == NULL)
        retVal = 0;
    else
    {
        endPtr--;
        *endPtr = '\n';
        startPtr = --endPtr;
        while( (startPtr[0] != ' ') && (startPtr >= str) )
        {
            startPtr--;
        }
        startPtr++;
        retVal = atoi(startPtr);
        *endPtr = ' ';
    }
    return retVal;
}


int power(char* inputString, int lineNumber)
{
    struct tuple tup;

    // extract game number
    char* startPtr;
    char* endPtr;
    int minRed, minGreen, minBlue = 0;

    inputString = strchr(inputString, ':');
    if(inputString == NULL)
    {
        printf("error with input format");
        return 0;
    }

    inputString +=2; //skip space

    // find tuple
    startPtr = strtok(inputString, ";");

    while(startPtr!= NULL)
    { 
        tup.red = findRed(startPtr);
        tup.green = findGreen(startPtr);
        tup.blue = findBlue(startPtr);

        // find minimum cubes needed
        if (tup.red > minRed)
            minRed = tup.red;
        if (tup.green > minGreen) 
            minGreen = tup.green;
        if (tup.blue > minBlue)
            minBlue = tup.blue;

        startPtr = strtok(NULL, ";");
    }
    return minRed * minGreen * minBlue;
}

int main(int argc, void* argv) 
{
    int totalValue = 0;
    int gameNumber = 1;
    int gamePower = 0;

    // Open and read the file
    const char inputFileName[] = "day2_input.txt";

    FILE* input = fopen(inputFileName, "r");
  
    if(input == NULL)
    {
        printf("Error opening file %s\n", input);
        return -1;
    }
    
    while(1)
    {
        printf("Game Number: %d\t", gameNumber);
    
        char inputString[2048];
        inputString[0] = '\n';

        char* result = fgets(inputString, sizeof(inputString), input);
        if(result == NULL)
        {
            printf("Done!\n");
            break;
        }

        gamePower = power(inputString, gameNumber);
        printf("gamePower %d\n", gamePower);

        totalValue += gamePower;

        gameNumber++;
    }
    printf("totalValue: %d\n", totalValue);

    return totalValue;
}