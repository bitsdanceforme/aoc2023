#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void findNumbers(char* row, int offset)
{
    char* onePosition;
    char* twoPosition;
    char* threePosition;

    char* endOne, endTwo, endThree;

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
            if( (onePosition)[0] == '.')
             break;
        }
        ++onePosition;
        // find end of string
        char* temp = (char*)malloc(sizeof(char)*(sizeof(onePosition)+1));
        temp[0] = '\n';

        memcpy(temp, onePosition, sizeof(onePosition));

        char* number = strtok(temp, ".");

        number = strtok(NULL, ".");
        if(number > threePosition)
            return;

        number = strtok(NULL, ".");    
        if(number > threePosition)
            return;
    }
        
    else if(twoPosition[0] != '.')
    {
        printf("found number");

        while(1)
        {
            if( (--twoPosition)[0] == '.')
             break;
        }
        ++twoPosition;
        // find end of string
        char* number = strtok(twoPosition, ".");

        number = strtok(NULL, ".");
        if(number > threePosition)
            return;

    }

    if(threePosition[0] != '.')
    {
        printf("found number");
        
        while(1)
        {
            if( (--threePosition)[0] == '.')
             break;
        }
        ++threePosition;
        // find end of string
        char* number = strtok(threePosition, ".");
    }

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
                    ".1.23*.#9."};

    char symbol = '*';
    char* symbolPtr;
    symbolPtr = "deadbeef";
printf("%p\n", &symbolPtr);
    int offset = findSymbol(map[1], symbol, &symbolPtr);
    if(symbolPtr != NULL)
        findNumbers(map[0], offset);
                     
}