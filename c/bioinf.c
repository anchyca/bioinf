#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int binary_replace(int *lis, int left, int right, int key) {
        int mid;

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
        clock_t begin, end;
        double time_spent;
        int i=0, tmp,lis_length = -1,storage=0;
        int *answer;
        int *A = (int*) malloc(1*sizeof(int));
        /*int *LIS = (int*) malloc(100*sizeof(int));
        int *index = (int*) malloc(100*sizeof(int));*/

        FILE *fp = fopen("u.txt","r");
        while(fscanf(fp,"%d, ",&tmp)>0)
         {
             A[i]=tmp;
             //printf("%d\n",A[i]);
             i++;
             A=(int*)realloc(A,(i+1)*sizeof(int));
         }
        fclose(fp);

        begin = clock();
        int size=i;
        int *LIS = (int*) malloc(i*sizeof(int));
        int *index = (int*) malloc(i*sizeof(int));
        storage =5*sizeof(int)+4*sizeof(int*)+i*3*sizeof(int);
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
        fp = fopen("output.txt","w");
        fprintf(fp,"[");
        for (i = 0; i < lis_length; ++i) {
                fprintf(fp,"%d, ", answer[i]);
        }
        fprintf(fp,"%d]",answer[lis_length]);
        fclose(fp);

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Vrijeme izvodenja: %f s\n",time_spent);
        printf("Zauzece memorije: %d B\n",storage);
        return 0;
}
