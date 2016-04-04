import java.io.*;
import java.util.ArrayList;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-16
 */


//Take in all the transaction files, and merges them into a single transaction file. Then an internal datastructure of transactions.
public class TransFileReader{
      
    public static ArrayList<Transaction> read(String[] trans_file_names){

	//Reads in a list of transaction file names and produces a mergedTransactions.tf containing all the transactions from every file provided. The constructor takes in an array of strings, with the first element being omitted (the old.mbaf file) and the rest of the strings in the array being names of transaction files. 
	ArrayList<Transaction> transactions_list = new ArrayList<Transaction>();

	try {
	    //Create a writer for the merged transaction file
	    String merged_trans_file = "mergedTransactions.tf";
	    File outFile = new File(merged_trans_file);
	    Writer writer = new BufferedWriter(
					       new OutputStreamWriter(
								      new FileOutputStream(outFile)));
	    
	    //Iterate through all the transaction files - ignore 1st since it is mbaf
	    for (int i = 1; i < trans_file_names.length; i++) {
		//System.out.println(trans_file_names[i]); //temp
		//read in the current transaction file
		InputStream in = new FileInputStream(trans_file_names[i]);
		Reader reader = new InputStreamReader(in, "UTF8");
		BufferedReader trans_file = new BufferedReader(reader);

		//variable that reads in every line from the transaction file
		String curr_trans_line = trans_file.readLine();

		//read the rest of the transaction file
		while(curr_trans_line != null){
		    //System.out.println(curr_trans_line); //temp
		    //push the transaction string onto the arraylist
		    transactions_list.add((new Transaction(curr_trans_line)));
		    writer.write(curr_trans_line + "\n");
		    //read the next line in the file
		    curr_trans_line = trans_file.readLine();
		}
		//close the current file being read in
		trans_file.close();
	    }
	    //close the outfile
	    writer.close();
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}	 
	return transactions_list;
    }
}
