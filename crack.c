#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.

    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    

    
    // CHALLENGE1: Sort the hashes using qsort.
    
    // TODO
    // Open the password file for reading.
    FILE *dict = fopen(argv[2], "r");
	if (!dict)
	{
	    perror("Can't open file");
	    exit(1);
	}

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    char line[HASH_LEN];
    char *foundHash;
    int found = 0;
    int lineNum = 1;
    while(fgets(line, sizeof(line), dict) != NULL)
    {   
        // Trim \n
        char *nl = strchr(line, '\n'); 
        if(nl) *nl = '\0';
        
        char *hashedPass = md5(line,strlen(line));

        if(stringSearchAA(hashedPass, hashes, size) != NULL)
        {
            printf("Password: %s Hash: %s\n", line, hashedPass);
            found++;
        }
    }


    // CHALLENGE1: Use binary search instead of linear search.

    // TODO
    // When done with the file:
    //   Close the file
    fclose(dict);
    //   Display the number of hashes found.
    printf("%d hashes found!\n", found);
    //   Free up memory.

}
