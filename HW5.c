/* Kevin Nguyen
 * CSE 222
 * 03/15/2024
 * Main Program takes in command line argument for capacity and file to read. The program will print the weight, value, and name of each item from the data set. The Max Value Function MV is used to find the maximum value possible from the items of the data set given the capacity constraint. MaxItem is used to find the quantity of each item to get the highest possible max value and runs similar to MV but is a struct.
 */
#include "header.h"

struct item data[128];
int cache[10000] = {0};

struct answer cache_item[10000];

//Take command line argument
void main(int argc, char* argv[]) {

	int capacity;
	int size = 0;
	char *word;
	char buffer[1024];
	
	//Initialize the flag for cache_item[i] to zero
	for (int i = 0; i < 10000; i++) {
		cache_item[i].initialized = 0;
	}

	//If the command line argument had three arguments, looking for HW5 followed by capacity then file name
	if (argc == 3) {
		int result = sscanf(argv[1], "%d", &capacity);
		//If argument one where capacity is, is an integer
		if (result == 1) {
			//Check that the capacity is between 1 and 1024
			if (capacity < 1 || capacity > 1024) {
				printf("Illegal capacity: should be between 1 and 1024\n");
				return;
			}
			FILE *fp;
			fp = fopen(argv[2], "r");
			if (fp == NULL) {
				printf("HW5 capacity itemfile\n");
				return;
			}
			printf(" Weight  Value  Name\n");
			printf(" ------  -----  ----\n");
			
			//While loop using strtok to split the data by item name, value, and weight
			while (NULL != fgets(buffer, 1024, fp)) {
				
				word = strtok(buffer, " ");
				strcpy(data[size].name, word);

				word = strtok(NULL, " ");
				sscanf(word, "%d", &data[size].value);

				word = strtok(NULL, " ");
				sscanf(word, "%d", &data[size].weight);
				
				printf("    %d    %d    %s\n", data[size].weight, data[size].value, data[size].name);
				size++;
			}
			
			printf(" --------------------\n");
			printf("Bag's Capacity = %d\n", capacity);
			printf("Highest Possible Value = %d\n", MV(capacity, size));
			
			//Calls MaxItem to be result
			struct answer result = MaxItem(capacity, size);
			//Go through itemcount and only print the itemcount that were a part of the max value
			for (int i = 0; i < size; i++) {
				if (result.itemcount[i] != 0) {
					printf("Item %i (%s): %d\n", i, data[i].name, result.itemcount[i]);
				}
			}
		}
		else {
			printf("HW5 capacity itemfile\n");
		}
	}
	else {
		printf("HW5 capacity itemfile\n");
	}
}

//Max Value MV finds the Max Value Possible through recursion by calculating the Max Value each item
int MV(int capacity, int size) {
	int current = 0;
	int max = 0;

	if (capacity <= 0) {
		return 0;
	}
	if (cache[capacity] > 0) {
		return cache[capacity];
	}
	for (int i = 0; i < size; i++) {
		if (data[i].weight <= capacity) {
			current = (data[i].value + MV(capacity - data[i].weight, size));
			if (current > max) {
				max = current;
			}
		}
	}
	cache[capacity] = max;
	return max;
}

//MaxItem calculates the item count for each item for the max value
struct answer MaxItem(int capacity, int size) {
	int current = 0;
	struct answer result;
	result.value = 0;

	for (int i = 0; i < size; i++) {
		result.itemcount[i] = 0;
	}
	if (capacity <= 0) {
		return result;
	}
	if (cache_item[capacity].initialized != 0) {
		return cache_item[capacity];
	}
	for (int i = 0; i < size; i++) {
		if (data[i].weight <= capacity) {
			//tempResult temporarily stores recursive calls to MaxItem
			struct answer tempResult = MaxItem(capacity - data[i].weight, size);
			current = (data[i].value + tempResult.value);
			if (current > result.value){
				result.value = current;
				for (int j = 0; j < size; j++) {
					result.itemcount[j] = tempResult.itemcount[j];
				}
				result.itemcount[i]++;
			}
		}
	}
	cache_item[capacity] = result;
	//We flag this so we do not have to recalculate its Max Value
	cache_item[capacity].initialized = 1;
	return result;
}

