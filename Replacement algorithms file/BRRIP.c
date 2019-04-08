#include<stdio.h>
#include<stdlib.h>


//structures

    struct cacheline {

        int pos;
        int valid;
        long tag;
    };

    struct cacheset {
        struct cacheline line[4];
    }set[1024*1024*1024];


//global variables

    long long indexx[1024*1024*1024],tag[1024*1024*1024];


//function to find hits and misses

float BRRIP (int number_of_ways, int brrip_factor) {


    //reading file

    FILE* fptr = fopen("file_name","r");
    long long l=0;
    int brrip_miss = 0;
    int brrip_hit = 0;
    int cache_sets;
    long long i,j,k,current_tag,current_index;
    int check = 0;
    long long iteration = 0;
    int flag = 0;
    for(; fscanf(fptr, "%lld", &iteration) && !feof(fptr); ){

        if(flag == 0){

            flag = 1;
            indexx[l] = iteration;
            // printf("\nindex = %lld",indexx[l]);
            continue;

        }

        else if(flag == 1){

            flag = 0;
            tag[l] = iteration;
            l++;
            // printf("   tag = %lld",tag[l-1]);
            continue;

        }

    }

    fclose(fptr);

    long long size = l;

        //setting all the cache lines in third category

        for(j=0;j<size;j++){

            for(i=0;i<number_of_ways;i++){

                set[i].line[j].pos = 3;
                set[i].line[j].valid = 0;

            }

        }

        //iterating through the addresses

        for(j=0;j<size;j++){

            current_index = indexx[j];
            current_tag = tag[j];
            // printf("\nCurrent tag = %lld, current index = %lld",current_tag,current_index);
            check = 0;

            for(i=0;i<number_of_ways;i++){

                //hit

                if(set[current_index].line[i].valid == 1 && set[current_index].line[i].tag == current_tag){

                    brrip_hit++;
                    check = 1;
                    if(set[current_index].line[i].pos != 0){

                        for(k=0;k<number_of_ways;k++)

                            if(k==i)
                                set[current_index].line[i].pos = 0;

                            else if(set[current_index].line[i].pos<3)
                                set[current_index].line[i].pos++;
                            
                    // printf("Cache hit at set %lld and cache line %lld valid : %d Tag : %ld\n", current_index, i, set[current_index].line[i].valid, set[current_index].line[i].tag);
                    break;

                    }

                }

                //cold miss

                else if(set[current_index].line[i].valid == 0){

                    brrip_miss++;
                    check = 1;
                    set[current_index].line[i].valid = 1;
                    set[current_index].line[i].pos = 3;
                    set[current_index].line[i].tag = current_tag;
                    // printf(" i= %lld, j= %lld, Cache cold miss placed at set %lld and cache line %lld valid : %d Tag : %ld\n", i,j,current_index, i, set[current_index].line[i].valid, set[current_index].line[i].tag);
                    break;

                }

            }

            //regular miss

            if(check == 0){

                brrip_miss++;

                if(rand()%brrip_factor == 0){

                    for(k=0;k<number_of_ways;k++)

                        if(set[current_index].line[k].pos == 3)

                            set[current_index].line[k].tag = current_tag;

                }

                else{

                    for(k=0;k<number_of_ways;k++){

                        if(set[current_index].line[k].pos == 3){

                            set[current_index].line[k].tag = current_tag;
                            set[current_index].line[k].pos = 2;

                        }

                        else if(set[current_index].line[k].pos == 2)

                            set[current_index].line[k].pos = 3;

                    }

                }

            }

    }

    printf("\n\nHits = %d\nMisses = %d",brrip_hit,brrip_miss);

    printf("\n\nHit ratio = %f",(((float)brrip_hit)*100)/size);

    return 0;

}


//main function

int main(){

    BRRIP(4,8);

}
