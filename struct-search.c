#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
        char name[20];
        int account;
        double balance;
}customer;
void search_name(char* , customer [], int);
int main() {
        char filename[100];
        int size;
                char cont[3] = "y";
                char name[10];
                //Getting user input
        printf("Enter an input file: ");
        scanf("%s", filename);
                //opening the file
        FILE* fp = fopen(filename, "r");
        if(fp == NULL) {
                printf("File not found!\n");
                return 1;
                }
                fscanf(fp, "%d", &size);
                customer user[size];
                // Get in the data and scan it
                for (int i = 0; i < size; i++) {
                        fscanf(fp, "%s", user[i].name);
                        fscanf(fp, "%d", &user[i].account);
                        fscanf(fp, "%lf", &user[i].balance);
                }
                fclose(fp);
                //Asking user for the name they are looking for
                while (strcmp("y", cont) == 0) {
                        printf("------------------------------------------------\n");
                        printf("Record Finder - Enter a customer name: ");
                        scanf("%s", name);
                        printf("------------------------------------------------\n");
                        //Searching for the name
                        search_name(name, user, size);
                        printf("------------------------------------------------\n");
                        printf("\nDo you want to continue? (y/n) ");
                        scanf("%s", cont);
                        printf("\n");
                }
        return 0;
}
void search_name(char* name, customer arr[], int size) {
        bool x = false;
        for(int i = 0; i < size; i++) {
                if(strcmp(arr[i].name, name) == 0) {
                        printf("Name: %s\nAccount: %d\nBalance: %.2lf\n", arr[i].name, arr[i].account, arr[i].balance);
                        x = true;
                }
        }
        if (x == false) {
                printf("Fail. %s doesn't exist.\n", name);
        }
}
