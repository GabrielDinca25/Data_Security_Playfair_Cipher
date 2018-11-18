#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 25
#define ROWS 5
#define COLUMNS 5

char* alphabet = "abcdefghijklmnopqrstuvwxyz";
char* neutralCharacter = "x";
char table[ROWS][COLUMNS];

void DisplayArray(char* array)
{
    int arraySize = strlen(array);
    int i;
    for(i = 0; i<arraySize; i++)
    {
        printf("%c", array[i]);
    }
    printf("\n");
}

void DisplayTable()
{
    int i,j;

    for(i=0; i<ROWS;i++)
    {
        for(j=0; j<COLUMNS;j++)
        {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

char* RemoveDuplicates(char* array)
{

   int index = 0;
   int i;
   int arraySize = strlen(array);

   for (int i=0; i<arraySize; i++) {
    int j;
    for (j=0; j<i; j++)
        if (array[i] == array[j])
            break;

    if (j == i)
        array[index++] = array[i];
   }
   array[index] = '\0';
   return array;
}

void BuildTable(char* password)
{
    char* rearrangedAlphabet = strcat(password, alphabet);
    int rearrangedAlphabetSize = strlen(rearrangedAlphabet);
    int i;

    for(i = 0; i < rearrangedAlphabetSize; i++)
    {
        if(rearrangedAlphabet[i] == 'j')
        {
            rearrangedAlphabet[i] = 'i';
        }
    }
    
    rearrangedAlphabet = RemoveDuplicates(password);

    int j,k;

    for(i = 0, k = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLUMNS; j++)
        {
            table[i][j] = rearrangedAlphabet[k];
            k++;
        }
    }

    DisplayTable();

    DisplayArray(rearrangedAlphabet);

}

void Encrypt(char* plainText)
{
    char cipherText[50];
    int plainTextSize = strlen(plainText);
    if(plainTextSize % 2 != 0)
    {
        strcat(plainText, neutralCharacter);
        plainTextSize++;
    }
    
    int i;
    for(i = 0; i < plainTextSize; i+=2)
    {
        if(plainText[i] == plainText[i+1])
        {
            plainText[i+1] = 'x';
        }
    }
    
    for(i = 0; i < plainTextSize; i+=2)
    {   

        int j,k;
        int firstLetterRow = 0;
        int firstLetterCol = 0;
        int secondLetterRow = 0;
        int secondLetterCol = 0;

        for(j = 0; j < ROWS; j++)
        {
            for(k = 0; k < COLUMNS; k++)
            {
                if(table[j][k] == plainText[i])
                {
                    firstLetterRow = j;
                    firstLetterCol = k;
                }

                if(table[j][k] == plainText[i+1])
                {

                    secondLetterRow = j;
                    secondLetterCol = k;
                }
            }
        }

        if(firstLetterRow == secondLetterRow)
        {
            cipherText[i] = table[firstLetterRow][(firstLetterCol+1) % COLUMNS];
            cipherText[i+1] = table[secondLetterRow][(secondLetterCol+1) % COLUMNS];
        }
        else if(firstLetterCol == secondLetterCol)
        {
            cipherText[i] = table[(firstLetterRow+1) % ROWS][firstLetterCol];
            cipherText[i+1] = table[(secondLetterRow+1) % ROWS][secondLetterCol];
        }
        else{
            cipherText[i] = table[firstLetterRow][secondLetterCol];
            cipherText[i+1] = table[secondLetterRow][firstLetterCol];
        }
    }

    printf("\nPlain Text: ");
    DisplayArray(plainText);
    printf("\nCipher Text: ");
    DisplayArray(cipherText);

}

void Decrypt(char* cipherText)
{
    char plainText[50];
    int cipherTextSize = strlen(cipherText);

    
    int i;
    for(i = 0; i < cipherTextSize; i+=2)
    {   

        int j,k;
        int firstLetterRow = 0;
        int firstLetterCol = 0;
        int secondLetterRow = 0;
        int secondLetterCol = 0;

        for(j = 0; j < ROWS; j++)
        {
            for(k = 0; k < COLUMNS; k++)
            {
                if(table[j][k] == cipherText[i])
                {
                    firstLetterRow = j;
                    firstLetterCol = k;
                }

                if(table[j][k] == cipherText[i+1])
                {

                    secondLetterRow = j;
                    secondLetterCol = k;
                }
            }
        }

        if(firstLetterRow == secondLetterRow)
        {
            plainText[i] = table[firstLetterRow][(firstLetterCol-1) % COLUMNS];
            plainText[i+1] = table[secondLetterRow][(secondLetterCol-1) % COLUMNS];
        }
        else if(firstLetterCol == secondLetterCol)
        {
            plainText[i] = table[(firstLetterRow-1) % ROWS][firstLetterCol];
            plainText[i+1] = table[(secondLetterRow-1) % ROWS][secondLetterCol];
        }
        else{
            plainText[i] = table[firstLetterRow][secondLetterCol];
            plainText[i+1] = table[secondLetterRow][firstLetterCol];
        }
    }

    printf("\nCipher Text: ");
    DisplayArray(cipherText);
    printf("\nPlain Text: ");
    DisplayArray(plainText);

}

int main()
{
    char password[50];
    strcpy(password, "craciun");

    BuildTable(password);

    char plainText[50];
    strcpy(plainText, "anaaremereverzi");
    Encrypt(plainText);

    char cipherText[50];
    strcpy(cipherText, "cddaiblfibynuway");
    Decrypt(cipherText);

}
