#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int parseLine(char* line){
        int i = strlen(line);
        while (*line < '0' || *line > '9') line++;
        line[i-3] = '\0';
        i = atoi(line);
        return i;
    }
    

int getValue(){ 
	//Note: this value is in KB!
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];
    

        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmSize:", 7) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result;
    }



int binary_search(int *A,int *M, int pos,int len)
{
	//Standard binary search algorithm
	//Reduce window size until you find X
	int x=0,y=len,middle;
	while(x<=y)
	{
		middle=(x+y)/2;
		if(A[M[middle]]<A[pos])
		{
			x=middle+1;
		}
		else
		{
			y=middle-1;
		}	
	}
	return y;
}

int main(int argc, char *argv[])
{
	//variables and start for/of time measurement
	clock_t begin, end;
        begin = clock();
        double time_spent;

	int i=0,tmp,length;
	int *input =(int*) malloc(1*sizeof(int));

	//Opening input file
        FILE *fp = fopen(argv[1],"r");
        if(fp==NULL)
        {
            printf("Error!");
            return 0;
        }
        while(fscanf(fp,"%d, ",&tmp)>0)
         {
             input[i]=tmp;
	     //printf("%d, ",input[i]);
             i++;
	     input=(int*)realloc(input,(i+1)*sizeof(int));	
         }
	fclose(fp);
	length = i;

	int L=0,j;
	//Allocating extra arrays needed for the alg.
	//Based on the size of the input array
	int *M = (int*) malloc (length*sizeof(int));
	int *P = (int*) malloc (length*sizeof(int));
	//array of numbers in current longest sequence
	M[0]=0;
	//array of predecessors
	P[0]=-1;
	
	for(i=0;i<length;i++)
	{
		/*for every element of the input array, you finish a 			binary search to find a new element, and remember the 			position of the predecessor

		If the new conditions are met, remember new sequence 			and new length
		*/
		j=binary_search(input,M,i,L);
		if(j!=-1)
			P[i]=M[j];
		if((j==L) || (input[i]<input[M[j+1]]))
			M[j+1]=i;
		if((j+1)>L)
			L=j+1;
	}
	
	int * LIS = (int*) malloc((L+1)*sizeof(int));
	int temp=M[L];
	//Read backwards
	for(i=L;i>=0;i--)
	{
		LIS[i]=input[temp];
		temp=P[temp];
	}
	fp=fopen(argv[2],"w");
        if(fp==NULL)
        {
            printf("Error!");
            return 0;
        }
	for(i=0;i<L;i++)
	{
		fprintf(fp,"%d, ",LIS[i]);
	}
	fprintf(fp,"%d",LIS[L]);
	fclose(fp);


	//Calculate required time and memory
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time [s]: %f\n",time_spent);

	printf("Memory [B]: %d\n",getValue()*1024);

	return 0;
	
}
