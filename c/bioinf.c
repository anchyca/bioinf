#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int binary_replace(int *lis, int left, int right, int key) {
        int mid;
        //Standard binary search
        for (mid = (left+right)/2; left <= right; mid = (left+right)/2) {
                if (lis[mid] > key) {
                        right = mid - 1;
                } else if (lis[mid] == key) {
                        return mid;
                } else if (mid+1 <= right && lis[mid+1] >= key) {
                        lis[mid+1] = key;
                        return mid+1;
                } else {
                        left = mid + 1;
                }
        }
        if (mid == left) {
                lis[mid] = key;
                return mid;
        }
        lis[mid+1] = key;
        return mid+1;
}

int main(void) {
        //Variables for time measurement
        clock_t begin, end;
        begin = clock();
        double time_spent;

        int i=0, tmp,lis_length = -1,storage=0;
        int *answer;
        int *A = (int*) malloc(1*sizeof(int));

        //Reading the input file
        FILE *fp = fopen("u.txt","r");
        while(fscanf(fp,"%d, ",&tmp)>0)
         {
             A[i]=tmp;
             i++;
             //Reallocate memory because of unknown list size
             A=(int*)realloc(A,(i+1)*sizeof(int));
         }
        fclose(fp);


        int size=i; //Last index shows the size of the list
        int *LIS = (int*) malloc(i*sizeof(int));
        int *index = (int*) malloc(i*sizeof(int));

        //Manual memory allocation calclulation
        storage =5*sizeof(int)+4*sizeof(int*)+size*3*sizeof(int);
        for (i = 0; i < size; i++)
        {
                index[i] = binary_replace(LIS, 0, i, A[i]);
                if (lis_length < index[i])
                {
                    lis_length = index[i];
                }
        }

        answer = (int*) malloc((lis_length+1) * sizeof(int));
        for (i = size-1, tmp = lis_length; i >= 0; i--)
        {
                if (index[i] == tmp)
                {
                     answer[tmp] = A[i];
                     tmp--;
                }
        }

        //Open and write the list into the output file
        fp = fopen("output.txt","w");
        fprintf(fp,"[");
        for (i = 0; i < lis_length; ++i) {
                fprintf(fp,"%d, ", answer[i]);
        }
        fprintf(fp,"%d]",answer[lis_length]);
        fclose(fp);

        //Calculate required time
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time [s]: %f\n",time_spent);
        printf("Memory [B]: %d\n",storage);
        return 0;
}
