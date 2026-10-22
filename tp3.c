#include "tp3.h"
#include <string.h>
#include <stdlib.h>

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


