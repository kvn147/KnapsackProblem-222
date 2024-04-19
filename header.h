/* Kevin Nguyen
 * CSE 222
 * 03/15/2024
 * Header.h contains the structures for item used in MV and answer used in MaxItem, and has the function prototype for Max Value MV
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int MV(int capacity, int size);

struct answer MaxItem(int capacity, int size);
struct item {
	char name[50];
	int weight, value;
};

struct answer {
	int value;
	int itemcount[128];
	int initialized;
};
