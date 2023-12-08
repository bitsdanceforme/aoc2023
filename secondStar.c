// https://code.visualstudio.com/docs/cpp/config-mingw
// https://www.tutorialspoint.com/c_standard_library/string_h.htm


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Provide the string to search.  
// Find first or last
// TODO: pointer tells position.  Need to return the position AND the string value
struct result {
    char value[12];
    void* prtPosition;
    int iter; // This is the value if != -1
};

void initResult(struct result* res)
{
    res->value[0] = '\n';
    res->iter = -1;
}

void findNumberString(char* string, int findFirst, struct result *res)
{    
    char* digitString[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int size = (sizeof(digitString)/sizeof(char*));
    char* currPtr = NULL;
    char* prevPtr = NULL;
    int iter = 0;
    char* stringToFind;
    
    while(iter < size)
    {
        currPtr = strstr(string, digitString[iter]);
        //if(currPtr != NULL)
        while(currPtr != NULL)
        {
            if(prevPtr == NULL)
            {
                prevPtr = currPtr;
                res->prtPosition = prevPtr;
                res->iter = iter;
            }    

            if(findFirst)
            { 
                if(currPtr < prevPtr) // current string came before anything prior
                {
                    prevPtr = currPtr;
                    res->prtPosition = prevPtr;
                    res->iter = iter;
                }
            }
            else
            {
                if(currPtr > prevPtr)
                {
                    prevPtr = currPtr;
                    res->prtPosition = prevPtr;
                    res->iter = iter;
                }
            }
            currPtr = strstr(++currPtr, digitString[iter]);

        }
        iter++;
    }
    strcpy(res->value, digitString[res->iter]);
}


void findDigitString(char* string, int findFirst, struct result *res)
{   
    char* digitString[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int size = (sizeof(digitString)/sizeof(char*));
    char* currPtr = NULL;
    char* prevPtr = NULL;
    int iter = 0;
    char* stringToFind;
    
    while(iter < size)
    {
        currPtr = strstr(string, digitString[iter]);
        //if(currPtr != NULL)
        while(currPtr != NULL)
        {
            if(prevPtr == NULL)
            {
                prevPtr = currPtr;
                res->prtPosition = prevPtr;
                res->iter = iter;
            }    

            if(findFirst)
            { 
                if(currPtr < prevPtr) // current string came before anything prior
                {
                    prevPtr = currPtr;
                    res->prtPosition = prevPtr;
                    res->iter = iter;
                }
            }
            else
            {
                if(currPtr > prevPtr)
                {
                    prevPtr = currPtr;
                    res->prtPosition = prevPtr;
                    res->iter = iter;
                }
            }
        currPtr = strstr(++currPtr, digitString[iter]);
        }
        iter++;
    }
    strcpy(res->value, digitString[res->iter]);
}


int main(int argc, void* argv[])
{
//    char* testString = "8eight1twofive";
    struct result firstNumString, lastNumString, firstDigit, lastDigit ;
    initResult(&firstNumString);
    initResult(&lastNumString);
    initResult(&firstDigit);
    initResult(&lastDigit);
    
    int currentValue = 0;
    int totalValue = 0;
    int lineCount = 0;

    const char inputFileName[] = "input.txt";

    FILE* input = fopen(inputFileName, "r");
  
    if(input == NULL)
    {
        printf("Error opening file %s\n", input);
        return -1;
    }
    
    while(1)
    {
        printf("line count: %d\n", lineCount);
    
        char inputString[2048];
        inputString[0] = '\n';
        initResult(&firstNumString);
        initResult(&lastNumString);
        initResult(&firstDigit);
        initResult(&lastDigit);

        char* result = fgets(inputString, sizeof(inputString), input);
        if(result == NULL)
        {
            printf("Done!\n");
            break;
        }

        findNumberString(inputString, 1, &firstNumString);
       // printf("found eight %d", strcmp(r1.value, "eight"));
        
        findNumberString(inputString, 0, &lastNumString);
        //printf("found two %d", strcmp(r2.value, "two"));

        findDigitString(inputString, 1, &firstDigit);
        //printf("found 8 %d", strcmp(r1.value, "8"));

        findDigitString(inputString, 0, &lastDigit);
        //printf("found 1 %d", strcmp(r1.value, "1"));

        // Find first value
        if((firstNumString.iter == -1) && (firstDigit.iter == -1))
        {
            currentValue = 0;
        }
        else if((firstNumString.iter == -1) && (firstDigit.iter != -1))
        {
            currentValue = firstDigit.iter*10;
        }
        else if( (firstNumString.iter != -1) && (firstDigit.iter == -1))
        {
            currentValue = firstNumString.iter*10;
        }
        else
        {
            if(firstNumString.prtPosition < firstDigit.prtPosition)
                currentValue = firstNumString.iter*10;
            else
                currentValue = firstDigit.iter*10;
        }

        if((lastNumString.iter == -1) && (lastDigit.iter == -1))
        {
            ;
        }
        else if((lastNumString.iter == -1) && (lastDigit.iter != -1))
        {
            currentValue += lastDigit.iter;
        }
        else if( (lastNumString.iter != -1) && (lastDigit.iter == -1))
        {
            currentValue += lastNumString.iter;
        }
        else
        {
            if(lastNumString.prtPosition > lastDigit.prtPosition)
                currentValue += lastNumString.iter;
            else
                currentValue += lastDigit.iter;
        }

        printf("Current Value: %d\n", currentValue);

        totalValue += currentValue;
        lineCount++;
    }
    fclose(input);
    
    printf("Value %d\n", totalValue);
        
}
