// MaxUserMemAlloc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define KB  1024
#define MB  (1024*KB)
#define MAX_TRIES	200

int _tmain(int argc, _TCHAR* argv[])
{
    int totalSize = 0;
    int *p = NULL;
    int size;
	int nTries = 0;
	int maxTries = MAX_TRIES;
    int temp;

	if( argc == 2 )
	{
        errno = 0;
		temp = _wtoi(argv[1]);
        if(temp == 0)
        {
            wprintf(L"Error converting %s to integer\n", argv[1]);
            exit(1);
        }
		if(errno != 0)
        {
            wprintf(L"Error converting %s to integer: %s\n", argv[1], _wcserror(errno));
            exit(1);
        }
        maxTries = temp;
	}

    size = 500 * MB;
    while(nTries++ < maxTries)
    {
        printf("Trying to allocate %d bytes more\n", size);
        if( (p = (int*)malloc(size)) == NULL )
        {
            printf("malloc() failed %s\n", strerror(errno));
            size = size/2;
            if(size <= 0)
                break;
        }
        else
        {
            totalSize += size;
            printf("Allocated %d bytes\n", totalSize);
        }
    }

    printf("Allocated %f MB of memory\n", (float)totalSize/(MB));
    printf("Type x and hit return key to exit program\n");
    while( getchar() != 'x' );

    return 0;
}
