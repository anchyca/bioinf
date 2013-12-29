import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.NumberFormat;

public class NajduljiRastuciPodniz{
	
	static int binary_search(int A[], int[] M, int position, int length)
	{
		int x = 0;
		int y = length;
		int middle;
		
		while (x <= y){
			middle = (x+y)/2;
			
			if (A[M[middle]]<A[position]){
				x=middle+1;
			}
			else{
				y = middle-1;
			}
		}
		return y;
	}
	
	private static int[] findLongestSubsequence(int[] inputArray){		
		int L = 0;
		int j;
		int[] M = new int[inputArray.length];
		int[] P = new int[inputArray.length];
		M[0]=0;
		P[0]=-1;
		
		for (int i=0; i<inputArray.length; i++){
			j = binary_search(inputArray, M, i, L);
			//System.out.println("i "+i);
			//System.out.println("j "+j);
			
			if ( j==-1){
				P[i] = -1;
			}
			else{
				P[i]=M[j];
			}
			if (j==L || (inputArray[i]<inputArray[M[j+1]])){
				M[j+1]=i;
				if (j+1>L){
					L = j+1;
				}
			}
		}
		//System.out.println("L "+L);
		
		int[] LIS = new int[L+1];
        int p = M[L];
        for (int i=L; i>=0; i--){
        	//System.out.println("p: "+p+" arr: "+inputArray[p]);
            LIS[i] = inputArray[p];
            p = P[p];
        }
		
		return LIS;		
	}
	
	
	public static void main(String[] args) throws IOException{
		long startTime = System.currentTimeMillis();

		StringBuilder stringBuilder;
		
		// file opening
		BufferedReader bufferedReader = new BufferedReader(new FileReader("u.txt"));
		try{
			// file reading
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
		
		// input data transforming (String -> Integer)	
		String s = stringBuilder.toString();
		String[] help = s.split(",");
		int[] input = new int[help.length];
		
		for (int i=0; i<help.length; i++){
			if (help[i].length()>0){
				input[i]=Integer.parseInt(help[i]);
			}
		}
		
		int[] subsequence = findLongestSubsequence(input);
		
		for (int i=0; i<subsequence.length; i++){
			System.out.print(subsequence[i]+" ");
		}
		System.out.println();
		
	    long estimatedTime = System.currentTimeMillis() - startTime;
	    System.out.println("vrijeme " + (float)estimatedTime/1000);
	    
	    Runtime runtime = Runtime.getRuntime();
	    // Run the garbage collector
	    runtime.gc();
	 // get the total memory for my app
	    long total = Runtime.getRuntime().totalMemory();
	    // get the free memory available
	    long free = Runtime.getRuntime().freeMemory();

	    // some simple arithmetic to see how much i use
	    long used = total - free;

	    System.out.println("Used memory in bytes: " + used);
	}
}