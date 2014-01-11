import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class LongestIncreasingSubsequence{
	
	//This is a standard version of binary search done iteratively

	//The input is array A[] on which the search is made; help array M[]
	// with indexes of last members of each sub array of length l, where l
	// is in range of 0 to M.length()-1; variable position which indicates
	// which member of array A[] to observe and variable length which 
	// indicates the length of currently longest found subsequence

	static int binary_search(int A[], int[] M, int position, int length)
	{
		// variable initialisation, x must be nonnegative number
		int x = 0;
		int y = length;
		int middle;
		
		// binary search is done within boundaries x and y
		while (x <= y){
			middle = (x+y)/2;
			// comparing all last members of known sub sequences with
			// current number on which the search is done
			if (A[M[middle]]<A[position]){
				x=middle+1;
			}
			else{
				y = middle-1;
			}
		}
		return y;
	}
	// A function that finds the longest sub sequence of given input array

	private static int[] findLongestSubsequence(int[] inputArray){

		// Initialising variables		
		int L = 0;
		int j;
		int[] M = new int[inputArray.length];
		int[] P = new int[inputArray.length];
		M[0]=0;
		P[0]=-1;
		
		// The main loop goes through all the elements of input array
		for (int i=0; i<inputArray.length; i++){

			// First the binary search is done to find where to put
			// the new element
			j = binary_search(inputArray, M, i, L);

			// For all situations but the first element inspection
			// remember the position of the predecessor 
			if ( j !=-1){
				P[i]=M[j];
			}
			
			// If the conditions are met, remember the new sub sequence
			// and if necessary discard all existing sub sequences of
			// the same length
			if (j==L || (inputArray[i]<inputArray[M[j+1]])){
				M[j+1]=i;

				// Also remember the new largest length if necessary
				if (j+1>L){
					L = j+1;
				}
			}
		}
		
		// Make new array LIS in which the solution will be
		int[] LIS = new int[L+1];

		// Start reading backwards using help arrays P and M
        	int p = M[L];
        	for (int i=L; i>=0; i--){
            		LIS[i] = inputArray[p];
            		p = P[p];
        	}
		
		return LIS;		
	}
	
	// The main function
	public static void main(String[] args) throws IOException{

		// Start measuring time
		long startTime = System.currentTimeMillis();
		// Use string builder and buffer to read input file
		StringBuilder stringBuilder;
		
		// File opening
		BufferedReader bufferedReader = new BufferedReader(new
                                             FileReader("u.txt"));
		try{ // File reading
			stringBuilder = new StringBuilder();
			String line = bufferedReader.readLine();
						
			while (line != null){
				stringBuilder.append(line);
				stringBuilder.append(",");
				line = bufferedReader.readLine();
			}
		}
		finally{
			bufferedReader.close();
		}
		
		// Input data transforming (String -> Integer)	
		String s = stringBuilder.toString();
		String[] help = s.split(",");
		int[] input = new int[help.length];
		
		for (int i=0; i<help.length; i++){
			if (help[i].length()>0){
				input[i]=Integer.parseInt(help[i]);
			}
		}
		
		// Call the function to find LIS
		int[] subsequence = findLongestSubsequence(input);
		
		// Print out the LIS
		BufferedWriter outputWriter = null;
		outputWriter = new BufferedWriter(new FileWriter("out.txt"));
		for (int i = 0; i < subsequence.length; i++) {
		    outputWriter.write(subsequence[i]+", ");
      }
		outputWriter.flush();  
		outputWriter.close();
		
	    	// Finish estimating time
	    	long estimatedTime = System.currentTimeMillis() - startTime;
	    	System.out.println("Time [s]: " + (float)estimatedTime/1000);
	    
          	// Estimate used memory
	    	Runtime runtime = Runtime.getRuntime();
	    	runtime.gc();
	    	long total = Runtime.getRuntime().totalMemory();
	    	long free = Runtime.getRuntime().freeMemory();
	    	long used = total - free;
	    	System.out.println("Memory [B]: " + used);
	}
}
