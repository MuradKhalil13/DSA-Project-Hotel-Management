#include "tp3.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

T_Client* createClient(char* last_name, char* first_name, int age, int num_room){
    T_Client* client;

    client = (T_Client*)malloc(sizeof(T_Client));

    client->last_name = (char*)malloc(strlen(last_name) + 1);
    client->first_name = (char*)malloc(strlen(first_name) + 1);

    if (client == NULL || client->last_name == NULL || client->first_name == NULL){
        return NULL;
    }

    strcpy(client->last_name, last_name);
    strcpy(client->first_name, first_name);

    client->age = age;
    client->num_room = num_room;
    client->next = NULL;

    return client;
}

T_Site* createSite(char* city){
    T_Site* site;

    site = (T_Site*)malloc(sizeof(T_Site));

    site->city = (char*)malloc(strlen(city) + 1);

    if (site == NULL || site->city == NULL){
        return NULL;
    }

    strcpy(site->city, city);

    site->number_clients = 0;
    site->first = NULL;
    site->next = NULL;

    return site;
}

T_Hotel* createHotel(char* name){
    T_Hotel* hotel;

    hotel = (T_Hotel*)malloc(sizeof(T_Hotel));

    hotel->name = (char*)malloc(strlen(name) + 1);

    if (hotel == NULL || hotel->name == NULL){
        return NULL;
    }

    strcpy(hotel->name, name);

    hotel->first = NULL;

    return hotel;
}

int addClient(T_Site* site, T_Client* client){

    if (site->first == NULL){
        site->first = client;
        site->number_clients++;
        return 1;
    }

    T_Client* current = site->first;
    T_Client* previous = NULL;

    int compare;

    for (int i = 0; i < site->number_clients; i++){
        compare = strcmp(client->last_name, current->last_name);

        if (compare == 0){
            compare = strcmp(client->first_name, current->first_name);

            if (compare == 0){
                if (previous == NULL){
                    site->first = client;
                    client->next = current;
                    site->number_clients++;
                    return 1;
                }
                else{
                    previous->next = client;
                    client->next = current;
                    site->number_clients++;
                    return 1;
                }
            }
        }
        if (compare > 0){
            if (current->next == NULL){
                current->next = client;
                site->number_clients++;
                return 1;
            }
        }
        else if (previous == NULL){
            site->first = client;
            client->next = current;
            site->number_clients++;
            return 1;
        }
        else{
            previous->next = client;
            client->next = current;
            site->number_clients++;
            return 1;
        }

        previous = current;
        current = current->next;
    }
    
    return 0;
}

int addSite(T_Hotel* hotel, T_Site* site){
    if (hotel->first == NULL){
        hotel->first = site;
        return 1;
    }

    T_Site* current = hotel->first;
    T_Site* previous = NULL;

    int compare;

    while (1){
        compare = strcmp(site->city, current->city);

        if (compare == 0){
            return 0;
        }
        else if (compare > 0 && current->next == NULL){
            current->next = site;
            return 1;
        }
        else if (compare < 0 && previous == NULL){
            hotel->first = site;
            site->next = current;
            return 1;
        }
        else if (compare < 0){
            previous->next = site;
            site->next = current;
            return 1;
        }

        previous = current;
        current = current->next;
    }
}

void displayHotel(T_Hotel* hotel){
    printf("City                 Number of customers\n\n");

    if (hotel->first == NULL){
        return;
    }

    T_Site* site = hotel->first;
    
    while (1){
        printf("%s                 %d\n", site->city, site->number_clients);
        if (site->next == NULL){
            return;
        }
        site = site->next;
    }
}

void displaySite(T_Site* site){
    printf("Last name                 First name                 Age     Room\n\n");

    if (site->first == NULL){
        return;
    }

    T_Client* client = site->first;

    while (1){
        printf("%s                 %s                 %d     %d\n", client->last_name, client->first_name, client->age, client->num_room);
        if (client->next == NULL){
            return;
        }
        client = client->next;
    }
}


int deleteClient(T_Site *site, char *last_name, char *first_name){
    if(site==NULL || site->first==NULL){
        return 0;
    }

    T_Client* current=site->first;
    T_Client* previous=NULL;

    while(current!=NULL){
        if(strcmp(current->last_name, last_name)==0 && strcmp(current->first_name, first_name)==0){
            if(previous==NULL){
                site->first = current->next;
            }
            else{
                previous->next=current->next;
        }

            free(current->last_name);
            free(current->first_name);
            free(current);

            site->number_clients--;
            return 1;
    }
        previous=current;
        current=current->next;
}
    return 0;
}

void freeClients(T_Client* head){
    
    while(head!=NULL){
        T_Client* temp=head;
        head=head->next;
        free(temp->last_name);
        free(temp->first_name);
        free(temp);
    }   
}

int deleteSite(T_Hotel *hotel, char *city){
    if (hotel==NULL || hotel->first==NULL){
        return 0;
    }

    T_Site* current=hotel->first;
    T_Site* previous=NULL;

    while (current!=NULL){
        if(strcmp(current->city, city)==0){
            freeClients(current->first);

            if(previous==NULL){
                hotel->first=current->next;
            }else{
                previous->next=current->next;
            }

            free(current->city);
            free(current);
            return 1;
    }
        previous=current;
        current=current->next;
}
    return 0;
}



int startsWithIgnoreCase(char *name, char *prefix){
    while (*prefix != '\0'){
        if (*name == '\0'){
            return 0;
        }
        if (tolower((unsigned char)*name) !=tolower((unsigned char)*prefix)){
            return 0;
        }
        name++;
        prefix++;
    }

    return 1;
}

void searchClients(T_Hotel *hotel, char *critereaName){
    if (hotel == NULL || critereaName == NULL){
        return;
    }
    SearchResult *results = NULL;

    T_Site *site = hotel->first;

    while (site != NULL){
        T_Client *client = site->first;

        while (client != NULL){
            if (startsWithIgnoreCase(client->last_name, critereaName)){
                SearchResult *newResult = malloc(sizeof(SearchResult));

                if (newResult == NULL){
                    printf("Memory allocation failed.\n");

                    while (results != NULL){
                        SearchResult *temp = results;
                        results = results->next;
                        free(temp);
                    }
                    return;
                }
                newResult->client = client;
                newResult->city = site->city;
                newResult->next = NULL;

                SearchResult **position = &results;

                while (*position != NULL){

                    int compare = strcmp(
                        newResult->client->last_name,
                        (*position)->client->last_name);

                    if (compare == 0){
                        compare = strcmp(
                            newResult->client->first_name,
                            (*position)->client->first_name);
                    }

                    if (compare < 0){
                        break;
                    }
                    position = &(*position)->next;
                }
                newResult->next = *position;
                *position = newResult;
            }
            client = client->next;
        }
        site = site->next;
    }

    printf("\nLast name       First name      Age    Room    City\n");
    printf("------------------------------------------------------\n");

    if (results == NULL){
        printf("No matching customers found.\n");
        return;
    }
    while (results != NULL){
        SearchResult *temp = results;

        printf("%-16s%-16s%-7d%-8d%s\n",
               temp->client->last_name,
               temp->client->first_name,
               temp->client->age,
               temp->client->num_room,
               temp->city);

        results = results->next;
        free(temp);
    }
}

void processingfile(T_Hotel *hotel){
    if (hotel == NULL){
        printf("Hotel does not exist.\n");
        return;
    }
    FILE *file = fopen("bookings.txt", "r");

    if (file == NULL){
        printf("Could not open the file.\n");
        return;
    }

    char line[256];
    if (fgets(line, sizeof(line), file) == NULL){
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL){
        char *last_name = strtok(line, ";\r\n");
        char *first_name = strtok(NULL, ";\r\n");
        char *age_text = strtok(NULL, ";\r\n");
        char *room_text = strtok(NULL, ";\r\n");
        char *city = strtok(NULL, ";\r\n");

        if (last_name == NULL ||first_name == NULL ||age_text == NULL || room_text == NULL ||city == NULL){
            printf("Invalid line in the file. Skipping it.\n");
            continue;
        }
        int age = atoi(age_text);
        int room = atoi(room_text);

        T_Site *site = hotel->first;

        while (site != NULL){
            if (strcmp(site->city, city) == 0){
                break;
            }
            site = site->next;
        }
        if (site == NULL){
            site = createSite(city);
            if (site == NULL){
                printf("Could not create the location.\n");
                continue;
            }
            if (addSite(hotel, site) == 0){
                printf("Could not add the location.\n");
                free(site->city);
                free(site);
                continue;
            }
        }
        T_Client *client = createClient(
            last_name,
            first_name,
            age,
            room);
        if (client == NULL){
            printf("Could not create the customer.\n");
            continue;
        }
        if (addClient(site, client) == 0){
            printf("Could not add the customer.\n");
            free(client->last_name);
            free(client->first_name);
            free(client);
        }
    }
    fclose(file);
    printf("File processing finished.\n");
}
