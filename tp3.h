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

typedef struct SearchResult{
    T_Client *client;
    char *city;
    struct SearchResult *next;
} SearchResult;

T_Client* createClient(char* last_name, char* first_name, int age, int num_room);

T_Site* createSite(char* city);

T_Hotel* createHotel(char* name);

int addClient(T_Site* site, T_Client* client);

int addSite(T_Hotel* hotel, T_Site* site);

void displayHotel(T_Hotel* hotel);

void displaySite(T_Site* site);

int deleteClient(T_Site *site, char *last_name, char *first_name);

int deleteSite(T_Hotel *hotel, char *city);

int startsWithIgnoreCase(char *name, char *prefix);

void searchClients(T_Hotel *hotel, char *criteriaName);

void processingfile(T_Hotel *hotel);

int uniqueRoom(T_Site* site, int room);

int sameName(T_Site* site, char* last_name, char* first_name);

int deleteClientRoom(T_Site* site, char* last_name, char* first_name, int room);

