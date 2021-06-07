/*
 *Mike Zeng
 * CECS 424-5 
 * HW Assignment 2
 * Test file
 */
#include <stdio.h>
#include <stdlib.h>

struct Block {
    int block_size;             //# of bytes in the data section
    struct Block *next_block;   //pointer to the next block
};
//data section
const int overhead_size = sizeof(struct Block);
const int voidptr_size = sizeof(void*);         
struct Block *free_head;                        //only points to first free block in free list

void my_initialize_heap(int size){
    struct Block *buffer = malloc(size*overhead_size);
    free_head = buffer;
    free_head->block_size = overhead_size;  //not sure?
    free_head->next_block = NULL;   //not sure?
}

void* my_malloc(int size){
    struct Block *current = free_head;
    int blk_sz = current->block_size;
    
    if(size <= 0){
        return NULL;
    }
    
    while(current != NULL){
        //first fit: free block && block size >= input size; block size is a multiple of void* size
        if((blk_sz >= size) && (blk_sz % voidptr_size == 0)){   //if current block meets the requirements
            if((blk_sz > size) && ((blk_sz-size) > (overhead_size+voidptr_size))){  //if the block needs to split
                //split            
                struct Block *split_blk;
                current->next_block = split_blk;
                split_blk->block_size = overhead_size+voidptr_size;
                split_blk->next_block = NULL;
                
                current->block_size = size;
            }else{
                //no split
                if(current != free_head){
                    (current-current->block_size)->next_block = current->next_block;
                }
            }
            return (void *)((current+overhead_size));
        }
        
        current = current->next_block;
    }
    return NULL;
}

void my_free(void *data){
    free_head->next_block = (data-overhead_size);
}


int main(int argc, char* argv[]){
    printf("Testing\n\n");
    int a = 5,b = 6,c = 7;
    int arr[100];
    void* aptr;
    void* bptr;
    void* cptr;
    void* dptr;
    void* eptr;
    void* arrptr;

    my_initialize_heap(100);
    
    //#1
    printf("#1\n");
    aptr = my_malloc(sizeof(int));
    printf("First int: %p\n",aptr);
    my_free(aptr);
    bptr = my_malloc(sizeof(int));
    printf("Second int: %p\n",bptr);
    my_free(bptr);
    
    //#2
    printf("#2\n");
    aptr = my_malloc(a);
    bptr = my_malloc(b);
    printf("Int addresses: %p, %p\n", aptr, bptr);
    printf("overhead_size+voidptr_size = %d\n addr1 - addr2 = %d\n", (overhead_size+voidptr_size), (int)(bptr-aptr));
    my_free(aptr);
    my_free(bptr);
    
    //#3
    printf("#3\n");
    aptr = my_malloc(a);
    bptr = my_malloc(b);
    cptr = my_malloc(c);
    printf("Int addr: %p, %p, %p\n", aptr, bptr, cptr);
    my_free(cptr);
    dptr = my_malloc(sizeof(double));
    printf("Double addr: %p\n", dptr);
    my_free(aptr);
    my_free(bptr);
    my_free(dptr);
    
    //#4
    printf("#4\n");
    eptr = my_malloc(sizeof(char));
    aptr = my_malloc(sizeof(int));
    printf("Char addr: %p\nInt addr: %p\n", eptr, aptr);
    printf("overhead_size+voidptr_size = %d\n addr1 - addr2 = %d\n", (overhead_size+voidptr_size), (int)(eptr-aptr));
    my_free(aptr);
    my_free(eptr);
    
    //#5
    printf("#5\n");
    arrptr = my_malloc(sizeof(arr));
    aptr = my_malloc(a);
    printf("Int addr: 100*sizeof(int)+((free_head+arrptr)->block_size+overhead_size) = %p\n", (100*sizeof(int)+(arrptr+overhead_size)));
    my_free(arrptr);
    printf("Int addr: %p\nInt value: %d\n", aptr, a);
    my_free(aptr);

    free(free_head);
}

