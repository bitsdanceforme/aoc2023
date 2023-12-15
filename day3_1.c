#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int findNumbers(char* row, int offset)
{
    char* onePosition;
    char* twoPosition;
    char* threePosition;

    char* endOne, endTwo, endThree;
    char* numberOne, *numberTwo, *numberThree;

    int sum;

    onePosition = row + (offset * sizeof(char)) - 1;
    twoPosition = row + (offset * sizeof(char));
    threePosition = row + (offset * sizeof(char)) + 1;

    if(onePosition[0] != '.')
    {
        printf("found number");

        // do I need to back up?
        while(1)
        {
            onePosition = onePosition - sizeof(char);            
            if( ((onePosition)[0] == '.') || (onePosition < row))
             break;
        }
        ++onePosition;
        // find end of string
        numberOne = strchr(onePosition, '.');
        int length = 0;

        if(numberOne == NULL)
            length = strlen(row);
        else length = numberOne - onePosition;
        
        length = length/(sizeof(char));
        char* tempNumber = malloc(length + 1);
        tempNumber[0] = '\n';
        memcpy(tempNumber, onePosition, length);
        sum = atoi(tempNumber);
        free(tempNumber);
    }
        
    if(twoPosition[0] != '.')
    {
        printf("found number");

        while(1)
        {
            twoPosition = twoPosition - sizeof(char);            

            if(( (twoPosition)[0] == '.') || (twoPosition < row) )
             break;
        }
        ++twoPosition;
        // find end of string
        numberTwo = strchr(twoPosition, '.');

        int length = 0;

        if(numberTwo == NULL)
            length = strlen(row);
        else length = numberTwo - twoPosition;

        // was this part of the previous number?
        if(twoPosition != onePosition)
        {
            length = numberTwo - twoPosition;
            length = length/(sizeof(char));
            char* tempNumber = malloc(length + 1);
            tempNumber[0] = '\n';
            memcpy(tempNumber, twoPosition, length);
            sum += atoi(tempNumber);
            free(tempNumber);
        }
        else ;

    }

    if(threePosition[0] != '.')
    {
        printf("found number");
        
        while(1)
        {
            threePosition = threePosition - sizeof(char);            

            if(( (threePosition)[0] == '.') || (threePosition < row) )
             break;
        }
        ++threePosition;
        // find end of string
        numberThree = strchr(threePosition, '.');

        int length = 0;

        if(numberThree == NULL)
            length = strlen(row);
        else length = numberThree - threePosition;


        // was this part of the previous number?
        if((threePosition != onePosition) && (threePosition != twoPosition))
        {
            length = numberThree - threePosition;
            length = length/(sizeof(char));
            char* tempNumber = malloc(length + 1);
            tempNumber[0] = '\n';
            memcpy(tempNumber, threePosition, length);
            sum += atoi(tempNumber);
            free(tempNumber);
        }
        else ;
    }
    return sum;
}

int findSymbol(char* row, char symbol, char** symbolPtr)
{
    printf("%p\n", &symbolPtr);
    *symbolPtr = strchr(row, symbol);
    if(*symbolPtr != NULL)
        return *symbolPtr-row;
    else 
        return 0;
}

// Looks like no two symbols are next to each other.
// a part number must be within the 1-9 square
// 1 2 3 
// 4 X 6
// 7 8 9
int main(int argc, void* argv)
{
    char* map[] = { "..413.5...",
                    ".1.23*.#9.",
                    "1234567890"};

    char symbol = '*';
    char* symbolPtr;
    symbolPtr = "deadbeef";
    int totalSum = 0;
    int rowSum = 0;

printf("%p\n", &symbolPtr);
    int offset = findSymbol(map[1], symbol, &symbolPtr);
    if(symbolPtr != NULL)
    {
        rowSum = findNumbers(map[0], offset);
        totalSum += rowSum;
        rowSum = findNumbers(map[1], offset);
        totalSum += rowSum;
        rowSum = findNumbers(map[2], offset);
        totalSum += rowSum;
    }

    printf("total sum: %d\n", totalSum);
                     
}