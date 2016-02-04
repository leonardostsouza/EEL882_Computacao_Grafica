#include "lib/Screen.h"
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
	bool fs = false;
    // check for execution flags
    #ifdef DEBUG
    printf("DEBUG === Entering flag parse loop\n");
    #endif
    for (int iterator = 1; iterator < argc; iterator++)
    {
        if (strcmp(argv[1],"-f") == 0)
        {
			fs = true;
            #ifdef DEBUG
            printf("DEBUG === fullscreen set to %d\n", fs);
            #endif
		}
    }

	Screen screen(fs);

   return EXIT_SUCCESS;
}
