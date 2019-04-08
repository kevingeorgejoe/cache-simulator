// @authors: Niwedita(171co227), Sanjana P(171co139), Rujuta Kelkar(171co137), Ranjana K(171co134), Nakul Suresh(171co125), Chetlur Krishna(171co213), Meghna Savit(171co222), Kevin George(171co220)
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float SRRIP(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int valid;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
		//printf("%d %d\n",i,ways_filled[index]);
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].valid=0;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].valid=3;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].valid=0;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].valid==3)
                     {
                        set[index][i].tag=iter;
                        set[index][i].valid=2;
                        i=0;
                        break;
                     }
                  }
                  if(i==ways)
                  {
                     for(j=0;j<ways;j++)
                        set[index][j].valid++;
                  }
               }
            }
            flag=0;
         }
      }
  fclose(fptr);
	return (float)(hit)/(hit+miss);
}

float fifo(long long sets,int ways)
{
   int ti=0;
   struct data
   {
      long long tag;
      int time;
   }set[sets][ways];
   int flag=0,i,j=0;
   long long hit=0,miss=0,index=0;
   int ways_filled[sets];
   FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
         index=iter;
         flag=1;
         }
         else if(flag==1)
         {
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].time=ti;
                  ways_filled[index]++;
               }
            }
            else
            {
               int minti=1e9;
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
                  //so basically this loop finds maximum time , just change it to minimum time and you should be sett
                  for(i=0;i<ways;i++)
                  {
                     if(minti>=set[index][i].time)
                     {
                        minti=set[index][i].time;
                     }
                  }
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].time==minti)
                     {
                        set[index][i].tag=iter;
                        set[index][i].time=ti;
                        i=0;
                        break;
                     }
                  }
               }
            }
            flag=0;
         }
         ti++;
      }
   fclose(fptr);
   // printf("no of hits=%lld\t no of misses=%lld\n",hit,miss);
   float hitr;
   hitr=(float)hit/(float)(hit+miss);
   // hitr=hitr*100;
   //printf("Hitratio : %f\n",hitr);
   return hitr;
}


//BRRIP structures

    struct cacheline {

        int pos;
        int valid;
         long long tag;
    };

    struct cacheset {
        struct cacheline line[4];
    }set[1024*1024*1024];


//BBRIP variables

    long long indexx[1024*1024*1024],tag[1024*1024*1024];



float BRRIP (int number_of_ways, int brrip_factor) {
  
    //reading file

    FILE* fptr = fopen("d1-final.txt","r");
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

    //printf("\n\nHits = %d\nMisses = %d",brrip_hit,brrip_miss);

    //printf("\n\nHit ratio = %f",(((float)brrip_hit)*100)/size);

    return (((float)brrip_hit))/size;
    // return 123;
}


float lifo(long long sets,int ways)
{
   int ti=0;
   struct data
   {
      long long tag;
      int time;
   }set[sets][ways];

   int flag=0,i,j=0;
   long long hit=0,miss=0,index=0;
   int ways_filled[sets];
   FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
         index=iter;
         flag=1;
         }
         else if(flag==1)
         {
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].time=ti;
                  ways_filled[index]++;
               }
            }
            else 
            {
               int maxti=0;
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
                  for(i=0;i<ways;i++)
                  {
                     if(maxti<set[index][i].time)
                     {
                        maxti=set[index][i].time;
                     }
                  }
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].time==maxti)
                     {
                        set[index][i].tag=iter;
                        set[index][i].time=ti;
                        i=0;
                        break;
                     }
                  }
               }
            }
            flag=0;
         }
         ti++;
      }
   fclose(fptr);
   float hitr;
   hitr=(float)hit/(float)(hit+miss);
   // hitr=hitr*100;
   return hitr;
}

float LRU(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int lastUsedTime;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0,time=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
		time++;
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
		//printf("hit = %lld\n",hit);
                     set[index][i].lastUsedTime=time;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].lastUsedTime=time;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].lastUsedTime=time;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
		  int min=0;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].lastUsedTime<set[index][min].lastUsedTime)
                     {
                        min=i;
                     }
                  }
                  set[index][min].tag=iter;
                        set[index][min].lastUsedTime=time;
		i=0;
               }
            }
            flag=0;
         }
      }
   fclose(fptr);	
	// printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}

float LFU(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int frequency;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
		//printf("hit = %lld\n",hit);
                     set[index][i].frequency++;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].frequency=0;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].frequency++;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
		  int min=0;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].frequency<set[index][min].frequency)
                     {
                        min=i;
                     }
                  }
                  set[index][min].tag=iter;
                        set[index][min].frequency=0;
		i=0;
               }
            }
            flag=0;
         }
      }
   fclose(fptr);	
	// printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}


float MFU(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int frequency;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
		//printf("hit = %lld\n",hit);
                     set[index][i].frequency++;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].frequency=0;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].frequency++;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
		  int max=0;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].frequency>set[index][max].frequency)
                     {
                        max=i;
                     }
                  }
                  set[index][max].tag=iter;
                        set[index][max].frequency=0;
		i=0;
               }
            }
            flag=0;
         }
      }
   fclose(fptr);	
	// printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}

int main(int argc, char *argv[]) {
	
	//declaring hit-ratio variable for each algorithm
	float hitratio_srrip,hitratio_lifo,hitratio_fifo,hitratio_lfu,hitratio_lru,hitratio_mfu,hitratio_brrip;

	// // // ensure correct number of command line args
	// // if (argc != 5) {
	// // 	printf("usage: ./executable policy sets ways blocksize\n");
	// // 	exit(1);
	// // }

	// // // DEBUG to display the 5 command line args
	// // printf("argc: %d\n", argc);
	// // for(int i = 0; i < 5; i++) {
	// // 	printf("argv[%d]: %s \n", i, argv[i]);
	// // }

	// // to convert character array to int
	// // for easy arguement passing to policy function
	// // int sets, ways, blocksize;
	// // sets = atoi(argv[2]);
	// // ways = atoi(argv[3]);
	// // blocksize = atoi(argv[4]);
	// // printf("%d %d %d\n", sets, ways, blocksize);

	// // // how policy will be called
	// // if (!strcmp(argv[1], "lru")) {
	// // 	printf("call LRU()\n");
	// // 	LRU(sets, ways, blocksize);
	// // }

  int sets = 64, ways = 4;
	
	//calling all the replacement algorithm

    while(1){

        printf("\n1. SRRIP\n2. LIFO\n3. FIFO\n4. LRU\n5. LFU\n6. MFU\n7. BRRIP\n");
        int choice;
        scanf("%d",&choice);

        switch(choice){

        case 1:    hitratio_srrip=SRRIP(sets,ways);
        printf("SRRIP hit ratio: %f\n", hitratio_srrip);
        break;

        case 2:    hitratio_lifo=lifo(sets,ways);
        printf("LIFO hit ratio: %f\n", hitratio_lifo);
        break;

        case 3:    hitratio_fifo=fifo(sets,ways);
        printf("FIFO hit ratio: %f\n", hitratio_fifo);
        break;

        case 4:    hitratio_lru=LRU(sets,ways);
        printf("LFO hit ratio: %f\n", hitratio_lru);
        break;

        case 5:    hitratio_lfu=LFU(sets,ways);
        printf("LFU hit ratio: %f\n", hitratio_lfu);
        break;

        case 6:    hitratio_mfu=MFU(sets,ways);
        printf("MFU hit ratio: %f\n", hitratio_mfu);
        break;
            
        case 7: hitratio_brrip=BRRIP(ways,8);
        printf("BRRIP hit ratio: %f\n", hitratio_brrip);
        break;

        }

    }

	return 0;
}
