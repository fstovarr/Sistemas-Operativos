#define FILE_NAME "dataDogs.dat"

FILE *file;

bool initFile();
void closeFile();
int deleteFile(char *name);

long calcNodePosition(long nodePos);
long calcHashItemPosition(long hashItemPos);

void updateKeyInNode(int newKey, long position);

void recordNode(struct Node* node, long position);
void recordNodeInCurrentPosition(struct Node* node);
bool getNodeByEntryOrder(struct Node* node, long position);
bool getNode(struct Node* node, long position);

void recordHashItem(struct HashItem* item, long position);
void recordHashItemInCurrentPosition(void* item);

void recordTable(struct HashItem* hashArray, int hashSize);
void getHashItem(struct HashItem* item, long position);

void resetFileIndicator();
void setFileIndicator(long position);
void setFileIndicatorAtEnd();
long getCurrentPosition();

void loadFirstRecord();
void loadLastRecord();
void recordFirstRecord();
void recordLastRecord();
