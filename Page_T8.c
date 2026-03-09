//ATy.s

#include <stdio.h>
#include <stdlib.h>
#define PAGE_SIZE 1024
#define NUM_FRAMES 16

int main (void){
    //one process, 4 pages
    const int number_page=4;

    //Hardcode page -> frame
    int page_table[]={5,2,9,1};

    //Print page table (messages)
    printf("Page config: \n");
    printf("PAGE_SIZE= %d bytes \n", PAGE_SIZE);
    printf("NUM_FRAME= %d (Physical memory= %d bytes) \n", NUM_FRAMES, NUM_FRAMES*PAGE_SIZE);
    printf("Page table: \n");
    for (int p=0;p<number_page;p++){
        printf("Page %d -> frame %d\n", p, page_table[p]);
    }
    printf("\n")    ;

    int n;
    
    printf("Enter number of logical address (N): \n");
    if (scanf("%d", &n) !=1 || n<0){ 
        fprintf(stderr, "Invalid N\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d logical address, one/line : \n", n);

    for (int i=0;i<n;i++){
        long logical;
        
        //check for Invalid logical address input
        if (scanf("%ld", &logical) !=1){
            fprintf(stderr, "Invalid logical address input\n");
            return EXIT_FAILURE;
        }

        //check for negative address
        if (logical <0){
            printf("[#%d] logical =%ld -> INVALID (negative  address) \n", i, logical);
            continue;
        }

        long page   = logical /PAGE_SIZE;
        long offset = logical % PAGE_SIZE;

        printf("[#%d] logical =%ld -> page=%ld, offset= %ld \n", i, logical, page, offset);

        //Check page validity: Address out of range for this process
        if (page >= number_page){
            printf("-> INVALID (page %ld out of range; valid page %d)\n", page, number_page-1);
            continue;
        }
        int frame = page_table[page];
        if (frame <0){
            printf("-> Page %ld INVALID \n", page);
            continue;
        }

        long physical =(long) frame * PAGE_SIZE +offset; 

        printf("-> frame = %d -> physical = %ld \n", frame, physical);
         

    }
    printf("\n")    ;
    return EXIT_SUCCESS;



}