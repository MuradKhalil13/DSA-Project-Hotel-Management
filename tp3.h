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

T_Client* createClient(char* last_name, char* first_name, int age, int num_room);

T_Site* createSite(char* city);

T_Hotel* createHotel(char* name);

int addClient(T_Site* site, T_Client* client);

int addSite(T_Hotel* hotel, T_Site* site);

void displayHotel(T_Hotel* hotel);

void displaySite(T_Site* site);