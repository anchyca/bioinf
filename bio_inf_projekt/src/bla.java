	public class bla {
	 
	   public static int binary_search(int A[], int len, int key) {
	        int l = 1, r = len;
	     int m;
	      while (r - l > 1) {
	          m = l + (r - l) / 2;
	            if (A[m] >= key)
	             r = m;
	          else
	                l = m;
	      }
	       return r;
	   }
	 
	   public static int[] LongestIncreasingSubsequenceLength(int array[], int len) {
	        int sz = 1;
	     int c[] = new int[len + 1];
	     int dp[] = new int[len];
	        c[1] = array[0];
	    /* at this point, the minimum value of the last element of the size 1
	    * increasing sequence must be array[0] */
	      dp[0] = 1;
	      for (int i = 1; i < len; i++) {
	          if (array[i] < c[1]) {
	               c[1] = array[i];
	    //you have to update the minimum value right now
	                dp[i] = 1;
	          } else if (array[i] > c[sz]) {
	               c[sz + 1] = array[i];
	               dp[i] = sz + 1;
	             sz++;
	           } else {
	                int k = binary_search(c, sz, array[i]);
	 // you want to find k so that c[k-1]<array[i]<c[k]
	                c[k] = array[i];
	                dp[i] = k;
	          }
	       }
	 
	       return c;
	  }
	 
	   public static void main(String args[]) {
	        int A[] = { 2, 5, 3, 7, 11, 8, 10, 13, 6 };
	     int size = A.length;
	 
	     int x[] = LongestIncreasingSubsequenceLength(A,size);
	     for (int i=0; i<x.length; i++){
	    	 System.out.print(x[i]+" ");
	     }
	     System.out.println();
	     }
	 }
