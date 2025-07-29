/*
Aim of the program: Write a program in C to convert the first ‘n’ decimal numbers of a disc file to binary using recursion. Store the binary value in a separate disc file.

Note# Read the value of ‘n’, source file name and destination file name from command line arguments. Display the decimal numbers and their equivalent binary numbers from the output file.

Give the contents of the input disc file “inDec.dat” as

30 75   2564 …


Contents of the output disc file “outBin.dat” as

The binary equivalent of 30 is 0000000000011110

The binary equivalent of 75 is 0000000001001011

The binary equivalent of 2564 is 0000101000000100

Terminal Input:

$gcc lab2q1.c -o lab2q1

$./lab2q1 150 inDec.dat outBin.dat
*/

#include <stdio.h>
#include <stdlib.h>

void decToBin(int n, FILE *d_File) {
    if (n > 1) {
        decToBin(n / 2, d_File);
    }
    fprintf(d_File, "%d", n % 2);
}

int main(int args, char *argv[]){

    for(int i = 0; i < args; i++){
        printf("Argument no %d and argument value %s\n", i, argv[i]);
    }

    if (args != 4) {
        printf("error must be 3 arguments.\n");
        return 1;
    }
    int n = atoi(argv[1]);
    char *s_FileName = argv[2];
    char *d_FileName = argv[3];

    FILE *s_File = fopen(s_FileName, "r");
    if (s_File == NULL) {
        printf("Error opening s file %s\n", s_FileName);
        return 1;
    }

    FILE *d_File = fopen(d_FileName, "w");
    if (d_File == NULL) {
        printf("Error opening d file %s\n", d_FileName);
        fclose(s_File);
        return 1;
    }

    int num;
    for (int i = 0;i<n;i++) {
        if (fscanf(s_File, "%d", &num) != 1) {
            printf("Error reading ource file.\n");
            fclose(s_File);
            fclose(d_File);
            return 1;
        }
        fprintf(d_File, "The binary of %d is ", num);
        decToBin(num, d_File);
        fprintf(d_File, "\n");
        
    }

    fclose(s_File);
    fclose(d_File);
    return 0;
}
