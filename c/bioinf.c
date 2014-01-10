#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int binary_rep(int *arr, int left, int right, int key) {
        //Vrši se standardna binarna pretraga i ubacuje se broj u rezultatni niz.

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

int main(void) {
        //Varijable za mjerenje vremena
        clock_t begin, end;
        begin = clock();
        double time_spent;

        int i=0, tmp,length = -1,storage=0;
        //Alokacija memorije za prvi clan niza
        int *arr_0 =(int*) malloc(1*sizeof(int));

        //Citanje iz ulazne datoteke
        FILE *fp = fopen("u.txt","r");
        if(fp==NULL)
        {
            printf("Greška!");
            return 0;
        }
        while(fscanf(fp,"%d, ",&tmp)>0)
         {
             arr_0[i]=tmp;
             i++;
             //Realokacija za dodatak svakog novog clana
             arr_0=(int*)realloc(arr_0,(i+1)*sizeof(int));
         }
        fclose(fp);

        // i iz for petlje sluzio za zapis duljine ulaznog niza
        // te alokaciju memorije sukladno toj velicini
        int size=i;
        int *arr_n = (int*) malloc(i*sizeof(int));    //lista brojeva
        int *index = (int*) malloc(i*sizeof(int));  //lista indeksa


        for (i = 0; i < size; i++)
        {
                //vrsi binarnu pretragu u danom intervalu te vrši zamjenu
                index[i] = binary_rep(arr_n, 0, i, arr_0[i]);
                if (length < index[i])
                {
                    length = index[i];
                }
        }
        //dodjelji
        int *res = (int*) malloc((length+1) * sizeof(int));
        for (i = size-1, tmp = length; i >= 0; i--)
        {
                if (index[i] == tmp)
                {
                     res[tmp] = arr_0[i];
                     tmp--;
                }
        }
        //Zapis u izlaznu datoteku
        //Za promjenu ulaza+izlaza iz hardkodirane verzije treba samo koristiti cmd argumente :)

        fp = fopen("output.txt","w");
        //if it fails
        if(fp==NULL)
        {
            printf("Greška!");
            return 0;
        }
        //format izlaza
        fprintf(fp,"[");
        for (i = 0; i < length; ++i) {
                fprintf(fp,"%d, ", res[i]);
        }
        fprintf(fp,"%d]",res[length]);
        fclose(fp);
        //Racunanje potrebne memorije
        //not sure if better way
        storage =5*sizeof(int)+4*sizeof(int*)+size*3*sizeof(int);
        //Calculate required time
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time [s]: %f\n",time_spent);
        printf("Memory [B]: %d\n",storage);
        return 0;
}
