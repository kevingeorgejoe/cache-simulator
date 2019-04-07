// temp.c
// to understand how to go about command line args
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	float hit-ratio_srrip;
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
	
	hit-ratio_srrip=SRRIP(sets,ways);
	return 0;
}

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

  FILE* fptr = fopen("d3-16-final.txt", "r");
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
                     set[index][i].valid=2;
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
                     set[index][i].valid=2;
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
                        set[index][i].valid=0;
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
	//printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}

