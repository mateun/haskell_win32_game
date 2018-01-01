

extern "C" {

int hswinmain(int width, int height);
void clearScreen();
void pumpMessages();
int isKeyDown(char* key);

// Haskell functions
void gameUpdate();

}