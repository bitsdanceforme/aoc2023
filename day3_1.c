#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int findNumbers(char* row, int offset, int center)
{
    char* onePosition;
    char* twoPosition;
    char* threePosition;

    char* endOne, endTwo, endThree;
    char* numberOne, *numberTwo, *numberThree;

    int sum =0;

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

    if(center == 0)
    {    
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
        return *symbolPtr -row;
    else 
        return -1;
}


// returns the number of rows filled in.

int populateNextRows(char** map, FILE* input, int firstIteration)
{
    int rowsRead = 0;
    char* result;

    if(firstIteration)
    {
         result = fgets( *map, 2048, input);
        if(result == NULL)
        {
            rowsRead = 0;            
        }
        else 
        {
            result = fgets(*(map++), 2048, input);
            if(result == NULL)
            {
                rowsRead = 1;
            }
            else
            {
                result = fgets( *(map++), 2048, input);                
                rowsRead = 3;
            }
        }
    }
    else
    {
        map[0] = map[1];
        map[1] = map[2];
        result = fgets(*(map+2), 2048, input);
        if(result == NULL)
        {
            rowsRead = 2;
        }
        else
            rowsRead = 3;
    }
    return rowsRead;
}

// Looks like no two symbols are next to each other.
// a part number must be within the 1-9 square
// 1 2 3 
// 4 X 6
// 7 8 9
int main(int argc, void* argv)
{
    
   /* char map[3][11] = { "..413.5...",
                    ".1.23*.*9.",
                    "1234567890"};
     */              

    //char symbol = '*';
    char* symbol = "!\"#$%&'()*+'-/:;<=>?@[\\]^_`{|}~";
    char* symbolPtr;
    symbolPtr = 0; //"deadbeef";
    unsigned long totalSum = 0;
    unsigned long rowSum = 0;


    const char inputFileName[] = "day3_input.txt";

    FILE* input = fopen(inputFileName, "r");
  
    if(input == NULL)
    {
        printf("Error opening file %s\n", input);
        return -1;
    }
    
    int fileRowNumber = 0;
    int firstIteration = 1;

    while(1)
    {
        #if 0
        char map[3][2048];
        map[0][0] = '\n';
        map[1][0] = '\n';
        map[2][0] = '\n';
        #endif

        char** map;
        map = (char**) malloc(3* sizeof(char*));
        for(int i = 0; i < 3; i++)
        {
            map[i] = (char*) malloc(2048 * sizeof(char));
            map[i][0] = '\n';
        }
        
        sprintf(map[0], "%s", "311...672...34...391.....591......828.......................738....................223....803..472..................................714.840.");
        sprintf(map[1], "%s", ".......*...........*.....*...........*........631%...703.......*..12....652.................*.$............368.769*148.................*....");
        sprintf(map[2], "%s", "....411...........2....837.121........511.745...........*.48.422.@.........@.............311........887......*................457........595");
        
 
        //populateNextRows(map, input, firstIteration);        

        printf("%p\n", &symbolPtr);
        int i = 0;
        for(i = 0; i < strlen(symbol); i++)
        {
            int offset = findSymbol(map[1], symbol[i], &symbolPtr);
            char* starting = map[1];

            while (offset > 0)
            {   
                offset = findSymbol(starting, symbol[i], &symbolPtr);

                if(symbolPtr != NULL)
                {
                    rowSum = findNumbers(map[0], offset, 0);
                    printf("symbol: %c,  row 0 sum %d\n", symbol[i], rowSum);
                    totalSum += rowSum;
                    if(map[1][0] != '\n')
                    {
                        rowSum = findNumbers(map[1], offset, 1);
                        printf("symbol: %c,  row 1 sum %d\n", symbol[i], rowSum);
                        totalSum += rowSum;
                    }
                    else
                        break;
                    
                    if(map[2][0] != '\n')
                    {
                        rowSum = findNumbers(map[2], offset,0 );
                        printf("symbol: %c,  row 2 sum %d\n", symbol[i], rowSum);

                        totalSum += rowSum;
                    }
                    else 
                        break;
                }

                starting = symbolPtr +1;
            }
        }

        printf("total sum: %d\n", totalSum);
        firstIteration = 0;
    }
                        
}