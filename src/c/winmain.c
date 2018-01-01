#include "winfuncs.h"

int main(int argc, char** args) 
{

		hswinmain(1000, 500);
		while (true) 
		{
			pumpMessages();
			
		}
		
		return 0;
}