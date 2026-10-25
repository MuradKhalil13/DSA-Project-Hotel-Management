#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main() {
    T_Hotel *hotel = NULL;
    int choice;
    char input_name[100];
    char first_name[50];
    char last_name[50];
    int age, room;

    do {
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

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");

            while (getchar() != '\n') {
            }

            continue;
        }

        switch (choice) {

            case 1: {
                if (hotel != NULL) {
                    printf("Hotel already exists!\n");
                } else {
                    printf("Enter hotel name: ");
                    scanf("%99s", input_name);

                    hotel = createHotel(input_name);

                    if (hotel != NULL) {
                        printf("Hotel created successfully!\n");
                    } else {
                        printf("Error creating hotel.\n");
                    }
                }

                break;
            }

            case 2: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    printf("Enter city name: ");
                    scanf("%99s", input_name);

                    T_Site *site = createSite(input_name);

                    if (site == NULL) {
                        printf("Error creating location.\n");
                    } else {
                        if (addSite(hotel, site)) {
                            printf("Location added successfully!\n");
                        } else {
                            printf("Location already exists!\n");
                            free(site->city);
                            free(site);
                        }
                    }
                }

                break;
            }

            case 3: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    printf("Enter city name: ");
                    scanf("%99s", input_name);

                    T_Site *site = hotel->first;

                    while (site != NULL &&
                           strcmp(site->city, input_name) != 0) {
                        site = site->next;
                    }

                    if (site == NULL) {
                        printf("Location not found!\n");
                    } else {
                        printf("Enter last name: ");
                        scanf("%49s", last_name);

                        printf("Enter first name: ");
                        scanf("%49s", first_name);

                        printf("Enter age: ");
                        scanf("%d", &age);

                        printf("Enter room number: ");
                        scanf("%d", &room);

                        T_Client *client =
                            createClient(last_name, first_name, age, room);

                        if (client == NULL) {
                            printf("Error creating booking.\n");
                        } else {
                            if (addClient(site, client)) {
                                printf("Booking added successfully!\n");
                            } else {
                                printf("Could not add booking.\n");

                                free(client->last_name);
                                free(client->first_name);
                                free(client);
                            }
                        }
                    }
                }

                break;
            }

            case 4: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    displayHotel(hotel);
                }

                break;
            }

            case 5: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    printf("Enter city name: ");
                    scanf("%99s", input_name);

                    T_Site *site = hotel->first;

                    while (site != NULL &&
                           strcmp(site->city, input_name) != 0) {
                        site = site->next;
                    }

                    if (site == NULL) {
                        printf("Location not found!\n");
                    } else {
                        displaySite(site);
                    }
                }

                break;
            }

            case 6: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    printf("Enter city name: ");
                    scanf("%99s", input_name);

                    T_Site *site = hotel->first;

                    while (site != NULL &&
                           strcmp(site->city, input_name) != 0) {
                        site = site->next;
                    }

                    if (site == NULL) {
                        printf("Location not found!\n");
                    } else {
                        printf("Enter last name: ");
                        scanf("%49s", last_name);

                        printf("Enter first name: ");
                        scanf("%49s", first_name);

                        if (deleteClient(site, last_name, first_name)) {
                            printf("Booking deleted successfully!\n");
                        } else {
                            printf("Customer not found!\n");
                        }
                    }
                }

                break;
            }

            case 7: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    printf("Enter city name to delete: ");
                    scanf("%99s", input_name);

                    if (deleteSite(hotel, input_name)) {
                        printf("Location deleted successfully!\n");
                    } else {
                        printf("Location not found!\n");
                    }
                }

                break;
            }

            case 8: {
                if (hotel == NULL) {
                    printf("Create a hotel first!\n");
                } else {
                    printf("Enter the beginning of the last name: ");
                    scanf("%99s", input_name);

                    searchClients(hotel, input_name);
                }

                break;
            }

            case 9: {
                printf("Goodbye!\n");
                break;
            }

            default: {
                printf("Invalid choice!\n");
                break;
            }
        }

    } while (choice != 9);

    if (hotel != NULL) {
        T_Site *site = hotel->first;

        while (site != NULL) {
            T_Site *next = site->next;

            freeClients(site->first);
            free(site->city);
            free(site);

            site = next;
        }

        free(hotel->name);
        free(hotel);
    }

    return 0;
}
