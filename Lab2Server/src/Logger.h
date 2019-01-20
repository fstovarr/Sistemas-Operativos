#define LOGGER_FILE_NAME "serverDogs.dat"

#define INSERTION 0
#define READING 1
#define WRITING 2
#define DELETION 3

struct Log {
    char date[14];
    char ip[16];
    short operation;
    char input[50];
};

FILE *logger;
struct Log *dummyLog;

char tmp[50];

time_t t;
struct tm* tim;

size_t result;

void initLogger();
void registerOperation(char *ip, short operation, char *input, size_t sizeInput);
void registerIntOperation(char *ip, short operation, int input);
void printLog(struct Log *log);


