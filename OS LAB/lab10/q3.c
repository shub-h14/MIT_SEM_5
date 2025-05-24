#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int base;
    int limit;
} SegTE;

void initSegT(SegTE table[]) {
    table[0].base = 1400; table[0].limit = 1000;
    table[1].base = 3200; table[1].limit = 1100;
    table[2].base = 4300; table[2].limit = 400;
    table[3].base = 4700; table[3].limit = 1000;
    table[4].base = 6300; table[4].limit = 400;
}

int logiToPhy(SegTE table[], int segment, int offset) {
    if (offset >= table[segment].limit) {
        printf("Error: Offset %d is out of bounds for segment %d\n", offset, segment);
        return -1;
    }
    return table[segment].base + offset;
}

int main() {
    SegTE segmentTable[5];
    initSegT(segmentTable);

    printf("Physical address for 53 byte of segment 2: %d\n", 
           logiToPhy(segmentTable, 2, 53));
    printf("Physical address for 852 byte of segment 3: %d\n", 
           logiToPhy(segmentTable, 3, 852));
    printf("Physical address for 1222 byte of segment 0: %d\n", 
           logiToPhy(segmentTable, 0, 1222));

    return 0;
}

// SAMPLE INPUT - OUTPUT

// Physical address for 53 byte of segment 2: 4753
// Physical address for 852 byte of segment 3: 4252
// Error: Offset 1222 is out of bounds for segment 0
// Physical address for 1222 byte of segment 0: -1
