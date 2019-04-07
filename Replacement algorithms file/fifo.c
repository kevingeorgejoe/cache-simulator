#include <stdio.h>
#include <stdlib.h>

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
   FILE* fptr = fopen("file_name", "r");
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
               int minti=1e99;
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
   printf("no of hits=%lld\t no of misses=%lld\n",hit,miss);
   float hitr;
   hitr=(float)hit/(float)(hit+miss);
   hitr=hitr*100;
   //printf("Hitratio : %f\n",hitr);
   return hitr;
}
int main()
{

   fifo(64,4);
}
