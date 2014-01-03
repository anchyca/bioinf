import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class GenerateArray{
	
	@SuppressWarnings("resource")
	public static void main(String[] args) throws IOException{
		int len = 1000;
		int[] array = new int[len];
	
		for (int i=0; i<1000; i++){
			array[i]=1 + (int)(Math.random() * ((10000 - 1) + 1));
			System.out.println(array[i]);
		}
		
		BufferedWriter outputWriter = null;
		  outputWriter = new BufferedWriter(new FileWriter("u.txt"));
		  for (int i = 0; i < array.length; i++) {
		    // Maybe:
			if (i != 999){
		    outputWriter.write(array[i]+",");
			}
			else{
				outputWriter.write(array[i]+"");
			}
		    // Or:
		    //outputWriter.write(Integer.toString(array[i]));
		    //outputWriter.newLine();
		  }
		  outputWriter.flush();  
		  outputWriter.close();
	}
}