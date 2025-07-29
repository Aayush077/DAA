/*
`Write a program in C to find GCD of two numbers using recursion. Read all pair of numbers from a file and store the result in a separate file.

Note# Source file name and destination file name taken from command line arguments. The source file must contain at least 20 pairs of numbers.

Give the contents of the input disc file “inGcd.dat” as  8  12  20  45  30  80

Contents of the output disc file “outGcd.dat” as

The GCD of 8 and 12 is 4

The GCD of 20 and 45 is 5

The GCD of 30 and 80 is 10


Terminal Input:

$gcc lab2q2.c -o lab2q2

$./lab2q2 inGcd.dat outGcd.dat

 

Output: Display the gcd stored in the output file outGcd.dat
*/

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int args, char *argv[]){
    
    for(int i = 0; i < args; i++){
        printf("Argument no %d and argument value %s\n", i, argv[i]);
    }
    if (args != 4){
        printf("Error, must be 3 arg.\n");
        return 1;
    }
    int n = atoi(argv[1]);
    char *s_FileName = argv[2];
    char *d_FileName = argv[3];
    
    FILE *s_File = fopen(s_FileName, "r");
    if(s_File == NULL){
        printf("Error opening s_file");
        return 1;
    }

    FILE *d_File = fopen(d_FileName,"w");
    if(d_File == NULL){
        printf("Error opening d_file");
        fclose(s_File);
        return 1;    
    }

    int a, b;
    for(int i = 0; i < n; i++){
        if (fscanf(s_File, "%d %d", &a, &b) != 2) {
            printf("Error pair not found.\n");
            fclose(s_File);
            fclose(d_File);
            return 1;
        }
        int res = gcd(a, b);
        fprintf(d_File, "GCD of %d and %d is %d\n", a, b, res);
    }
    fclose(s_File);
    fclose(d_File);
    return 0;
}


    

