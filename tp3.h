typedef struct Client{
    char* last_name;
    char* first_name;
    int age;
    int num_room;
    struct Client* next;
} T_Client;

typedef struct Site{
    char* city;
    int number_clients;
    struct Client* first;
    struct Site* next;
} T_Site;

typedef struct Hotel{
    char* name;
    struct Site* first;
} T_Hotel;