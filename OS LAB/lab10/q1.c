#include <stdio.h>
#include <stdlib.h>

struct mab {
    int ofs;
    int size;
    int alctd;
    struct mab *next;
};
typedef struct mab Mab;
typedef Mab *MabPtr;

MabPtr createBlock(int ofs, int size, int alctd) {
    MabPtr block = (MabPtr)malloc(sizeof(Mab));
    block->ofs = ofs;
    block->size = size;
    block->alctd = alctd;
    block->next = NULL;
    return block;
}

MabPtr memChkFirstFit(MabPtr m, int size) {
    while (m != NULL) {
        if (!m->alctd && m->size >= size) return m;
        m = m->next;
    }
    return NULL;
}

MabPtr memChkBestFit(MabPtr m, int size) {
    MabPtr bestFit = NULL;
    while (m != NULL) {
        if (!m->alctd && m->size >= size) {
            if (bestFit == NULL || m->size < bestFit->size) {
                bestFit = m;
            }
        }
        m = m->next;
    }
    return bestFit;
}

MabPtr memChkWorstFit(MabPtr m, int size) {
    MabPtr worstFit = NULL;
    while (m != NULL) {
        if (!m->alctd && m->size >= size) {
            if (worstFit == NULL || m->size > worstFit->size) {
                worstFit = m;
            }
        }
        m = m->next;
    }
    return worstFit;
}

MabPtr memChkNextFit(MabPtr m, int size, MabPtr *lastAllocated) {
    MabPtr current = *lastAllocated;
    if (current == NULL) current = m;

    while (current != NULL) {
        if (!current->alctd && current->size >= size) {
            *lastAllocated = current; // Update last allocated
            return current;
        }
        current = current->next;
    }

    current = m;
    while (current != *lastAllocated) {
        if (!current->alctd && current->size >= size) {
            *lastAllocated = current; // Update last allocated
            return current;
        }
        current = current->next;
    }
    return NULL;
}

MabPtr memSplit(MabPtr block, int size) {
    MabPtr newBlock = createBlock(block->ofs + size, block->size - size, 0);
    newBlock->next = block->next;
    block->next = newBlock;
    block->size = size;
    return block;
}

MabPtr memAlloc(MabPtr head, int size, int type, MabPtr *lastAllocated) {
    MabPtr block;

    switch (type) {
        case 1:
            block = memChkFirstFit(head, size);
            break;
        case 2:
            block = memChkBestFit(head, size);
            break;
        case 3:
            block = memChkWorstFit(head, size);
            break;
        case 4:
            block = memChkNextFit(head, size, lastAllocated);
            break;
        default:
            printf("Invalid type selected.\n");
            return NULL;
    }

    if (block == NULL) {
        printf("Allocation failed. No suitable block found.\n");
        return NULL;
    }

    block->alctd = 1;
    if (block->size > size) memSplit(block, size);
    printf("Allocated %d bytes at offset %d.\n", size, block->ofs);
    return block;
}

void memFree(MabPtr block) {
    block->alctd = 0;
    printf("Freed block at offset %d.\n", block->ofs);
}

void memMerge(MabPtr head) {
    MabPtr current = head;
    while (current && current->next) {
        if (!current->alctd && !current->next->alctd) {
            current->size += current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void displayMemory(MabPtr head) {
    MabPtr current = head;
    printf("Memory Blocks:\n");
    while (current) {
        printf("Offset: %d, Size: %d, %s\n", 
               current->ofs, current->size, 
               current->alctd ? "Allocated" : "Free");
        current = current->next;
    }
}

int main() {
    printf("Created total block size of 500 ");
    printf("with block 1 of size 300 and 2 ");
    printf("of size 200 with offsets 0 and 300 respectively\n");
    MabPtr head = createBlock(0, 300, 0); 
    head->next = createBlock(300, 200, 0);
    MabPtr lastAllocated = NULL;
    printf("\n");

    printf("Displaying memory:\n");
    displayMemory(head);
    printf("\n");

    printf("First fit:\n");
    memAlloc(head, 50, 1, &lastAllocated); // First Fit
    displayMemory(head);
    printf("\n");
    
    printf("Best fit:\n");
    memAlloc(head, 30, 2, &lastAllocated); // Best Fit
    displayMemory(head);
    printf("\n");
    
    printf("Worst fit:\n");
    memAlloc(head, 100, 3, &lastAllocated); // Worst Fit
    displayMemory(head);
    printf("\n");
    
    printf("Next fit:\n");
    memAlloc(head, 50, 4, &lastAllocated); // Next Fit
    displayMemory(head);
    printf("\n");

    memFree(head->next);
    memMerge(head);
    displayMemory(head);

    return 0;
}
