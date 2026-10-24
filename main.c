#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
    T_Hotel *hotel = NULL;
    int choice;
    char input_name[100];
    char first_name[50];
    char last_name[50];
    int age, room;

    do{
        printf("\n--- HOTEL MANAGEMENT SYSTEM ---\n");
        printf("1. Create a hotel chain\n");
        printf("2. Add a location to a hotel chain\n");
        printf("3. Add a booking at a location\n");
        printf("4. Display the locations in a hotel chain\n");
        printf("5. Display the customers at a location\n");
        printf("6. Delete a booking at a location\n");
        printf("7. Delete a location\n");
        printf("8. Search for a customer by last name\n");
        printf("9. Quit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1){
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice):{
            case 1:
                
        }
    }
}