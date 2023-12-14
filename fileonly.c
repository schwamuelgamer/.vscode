#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LesData.h"
#define MAX 50

void newData();
void writeData(); 
void ledigeStillinger();

int main(){
    int input;
    do{
     input = lesChar("Velg kommando");
        switch (input)
        {
        case 'N': newData();break;
        case 'S': writeData();break;
        case 'L': ledigeStillinger();break;
        default: break;
        }
    } while(input != 'Q');
}

void newData(){
    char *buffer = (char *)malloc(50 * sizeof(char));

    lesText("Company name", buffer, 50);
    int buffer3 = lesInt("Company Established in", 1000, 2024);
    int buffer2 = lesInt("Company Current Employees", 1, 100); 
    int buffer4 = lesInt("Company Allowed Employees", 1, 100);

    FILE *fhoutput; 
    fhoutput = fopen("filemanage.txt", "a"); 

    fputs(buffer, fhoutput);
    fprintf(fhoutput,"\nCompany Established in: %d\n", buffer3);
    fprintf(fhoutput,"Company Current Emplyees: %d\n", buffer2);
    fprintf(fhoutput,"Company Allowed Employees: %d\n", buffer4);
    fclose(fhoutput);
    free(buffer);
} 

void writeData(){
    FILE *fhoutput;
    fhoutput = fopen("filemanage.txt", "r");
    int line = 0;
    char *buffer = (char *)malloc(256 * sizeof(char));
    while (fgets(buffer, 256, fhoutput) != NULL){
        printf("%s", buffer);
        line++;
    } 
    free(buffer);
    fclose(fhoutput);
}
void ledigeStillinger(){
    FILE *fhoutput = fopen("filemanage.txt", "r");
    char *buffer = (char *)malloc(100 * sizeof(char));
    char *bufferName = (char *)malloc(100 * sizeof(char));
    int buffer1;
    int buffer2;
    int buffer3;
    if(fhoutput == NULL){
        perror("Cannot find file");
    }
    while (fgets(buffer, 100, fhoutput)) {
        // Check for lines with "Company" to distinguish them from the company name line
        if (strstr(buffer, "Company") == NULL) {
            // This line should be the company name
            sscanf(buffer, "%[^\n]", bufferName);  // Reads the entire line as the company name
        } else if (strstr(buffer, "Company Established in:") != NULL) {
            sscanf(buffer, "Company Established in: %d", &buffer1);
        } else if (strstr(buffer, "Company Current Employees:") != NULL) {
            sscanf(buffer, "Company Current Employees: %d", &buffer2);
        } else if (strstr(buffer, "Company Allowed Employees:") != NULL) {
            sscanf(buffer, "Company Allowed Employees: %d", &buffer3);   
        }

        printf("Company name: %s\n", bufferName);
        printf("Company Established in: %d\n", buffer1);
        printf("Company Current Employees: %d\n", buffer2);
        printf("Company Allowed Employees: %d\n", buffer3);
}



    fclose(fhoutput);
    free(buffer);
    free(bufferName);
}
