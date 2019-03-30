// temp.c
// to understand how to go about command line args
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void LRU(int sets, int ways, int blocksize);

int main(int argc, char *argv[]) {
	
	// ensure correct number of command line args
	if (argc != 5) {
		printf("usage: ./executable policy sets ways blocksize\n");
		exit(1);
	}

	// // DEBUG to display the 5 command line args
	// printf("argc: %d\n", argc);
	// for(int i = 0; i < 5; i++) {
	// 	printf("argv[%d]: %s \n", i, argv[i]);
	// }

	// to convert character array to int
	// for easy arguement passing to policy function
	int sets, ways, blocksize;
	sets = atoi(argv[2]);
	ways = atoi(argv[3]);
	blocksize = atoi(argv[4]);
	printf("%d %d %d\n", sets, ways, blocksize);

	// how policy will be called
	if (!strcmp(argv[1], "lru")) {
		printf("call LRU()\n");
		LRU(sets, ways, blocksize);
	}

	return 0;
}

void LRU(int sets, int ways, int blocksize) {
	// TODO
	// read contents from file d1.txt and perform operations
	// display relevant details required asked in .pdf file
	
	// repeat same process for d2.txt and d3.txt
	printf("waddup this is LRU()\n");

}