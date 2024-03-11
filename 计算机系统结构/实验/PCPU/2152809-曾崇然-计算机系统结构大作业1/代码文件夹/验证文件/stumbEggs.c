#include <stdio.h>
#include <stdlib.h>

int main() {
	//初始参数 
    int totalFloors = 10,  fallResistance = 2;
    //要求的 
    int result = 0, count = 0, totalEggs = 0, isBroken = 0, value = 0;
    
    int high = totalFloors, low = 1;
    int stumbFloor = 0;
    while (1) {
    	count++;
    	stumbFloor = (high + low) / 2;
    	value = value + (high - low) / 2;
    	if (stumbFloor <= fallResistance) {
    		isBroken = 0;
    		low = stumbFloor;
		}
		else {
			isBroken = 1;
			totalEggs++;
			high = stumbFloor - 1;
		}
		if ((high - low) < 2) {
			break;
		}
	}
	
	if (high == low) {
		result = high;
	}
	else {
		count++;
		if (high <= fallResistance) {
			isBroken = 0;
			result = high;
		}
		else {
			isBroken = 1;
			totalEggs++;
			result = low;
		}
	}
	
	value = value + totalEggs * 5;
	
	printf("result:%d count:%d totalEggs:%d isBroken:%d value:%d", result, count, totalEggs, isBroken, value);
	
	return 0;
}

