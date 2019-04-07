#include<stdio.h>
#include<stdlib.h>
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

  FILE* fptr = fopen("file_name", "r");
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
	printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}
int main()
{
	float t=LRU(64*8,4);
	return 0;
}

