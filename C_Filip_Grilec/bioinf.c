#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>





int binary_rep(int *arr, int left, int right, int key) {
        //Standard binary search and insertion of number into the result array
        int mid=(left+right)/2;
        for (mid; left <= right; mid = (left+right)/2)
        {
                if (arr[mid] > key)
                        right = mid - 1;
                else if (arr[mid] == key)
                        return mid;
                else if (mid+1 <= right && arr[mid+1] >= key)
                    {
                        arr[mid+1] = key;
                        return mid+1;
                    }
                else
                        left = mid + 1;
        }
        if (mid == left)
        {
            arr[mid] = key;
            return mid;
        }
        arr[mid+1] = key;
        return mid+1;
}

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

int main(void) {
        //Variables for time measurement
        clock_t begin, end;
        begin = clock();
        double time_spent;

        int i=0, tmp,length = -1;
        //Allocation of memory for the array(first member)
        int *arr_0 =(int*) malloc(1*sizeof(int));

        //Reading input file
        FILE *fp = fopen("u.txt","r");
        if(fp==NULL)
        {
            printf("Gre¨ka!");
            return 0;
        }
        while(fscanf(fp,"%d, ",&tmp)>0)
         {
             arr_0[i]=tmp;
             i++;
             //Reallocation for every new member added, uknown input size
             arr_0=(int*)realloc(arr_0,(i+1)*sizeof(int));
         }
        fclose(fp);
        // after reading the input is done, i represents number of members in the array
        // memory allocation follows accordingly
        int size=i;
        int *arr_n = (int*) malloc(i*sizeof(int));    //lista brojeva
        int *index = (int*) malloc(i*sizeof(int));  //lista indeksa


        for (i = 0; i < size; i++)
        {
                //for every member, do a binary search and replacement
                index[i] = binary_rep(arr_n, 0, i, arr_0[i]);
                if (length < index[i])
                {
                    length = index[i];
                }
        }
        //reading output array backwards to recieve the longest increasing substring
        int *res = (int*) malloc((length+1) * sizeof(int));
        for (i = size-1, tmp = length; i >= 0; i--)
        {
                if (index[i] == tmp)
                {
                     res[tmp] = arr_0[i];
                     tmp--;
                }
        }
        //writing in output file

        fp = fopen("output.txt","w");
        //if it fails
        if(fp==NULL)
        {
            printf("Greška!");
            return 0;
        }
        //output formatting
        fprintf(fp,"[");
        for (i = 0; i < length; ++i) {
                fprintf(fp,"%d, ", res[i]);
        }
        fprintf(fp,"%d]",res[length]);
        fclose(fp);

        //Calculate required time
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time [s]: %f\n",time_spent);
	//Memory allocation calculation in function
        printf("Memory [B]: %d\n",getValue()*1024);

        return 0;
}
