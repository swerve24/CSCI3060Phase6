import java.io.*;
import java.util.ArrayList;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-16
 */

//Holds all data related to Bank Accounts in an internal list of Accounts. It is also responsible for reading in a Master Bank Accounts File and populate its internal data structure with all the Accounts in the file. Additionally BankAccounts is able to write the new Master Bank Accounts File by taking all the accounts it holds and writing out to a file in the required format. The Class also has a bunch of utility functions relating to interactions with Accounts, since the internal List of Accounts is private and other classes do not have direct access to it. These utility functions allow other classes to add/remove accounts, check if an account exists, and obtain a unique account number that doesn’t yet exist in the “database”.
public class BankAccounts{
    /**
     * List of all the bank accounts that are held internally
     * and used to represent the internal "database" of the backEnd
     */
    private ArrayList<Account> bankAccounts = new ArrayList<Account>();


    /**
     * getBankAccountsDatabase getter for the private bankAccounts ArrayList
     * <p>
     * Getter that returns the bankAccounts ArrayList 
     * <p>
     * @return returns the private member database to anybody calling this function
     */    
    public ArrayList<Account> getBankAccountsDatabase(){
	return this.bankAccounts;
    }


    /**
     * BankAccounts  Constructor
     * <p>
     * Constructor for the BankAccounts class that is able to
     * take in a master bank accounts file name and loads each
     * line into an Account object, which it then stores in
     * the private static bankAccounts variable
     * <p>
     * @param  mbafFilename The filename/path of the master 
     * bank accounts file
     */
    public BankAccounts(String mbafFilename){
	try{
	    //read in the mbaf file
	    InputStream in = new FileInputStream(mbafFilename);
	    Reader reader = new InputStreamReader(in, "UTF8");
	    BufferedReader mbafFile = new BufferedReader(reader);

	    //read the file in line by line
	    String currAccLine = mbafFile.readLine();
	    while (currAccLine != null){
		//Create a new account with the given line read in from mbaf
		Account newAccount = new Account(currAccLine);
		//add the new account to the list of bankAccounts
		this.bankAccounts.add(newAccount);		
		
		//read in the next line
		currAccLine = mbafFile.readLine();
	    }
	    //Catch any exceptions thrown by reading in the mbaf file
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}
    }

    //
    /**
     * getAccount fetches account object from database
     * <p>
     * Given an account number it searches through the private database
     * and if it finds the account it returns it, otherwise an error is shwon
     * <p>
     * @param accNumber A string holding the account number requested by user
     * @return Account The account corresponding to the accNumber from the user
     */
    public Account getAccount(String accNumber){
	//Iterate through the entire database
	for (int i = 0; i < this.bankAccounts.size(); i++){
	    //Look for the account that matches the accNumber
	    if (accNumber.compareTo(this.bankAccounts.get(i).number_) == 0){
		//found the account
		//System.out.println("[FOUND ACCOUNT]!");
		return this.bankAccounts.get(i);
	    }
	}
	//Error Did not find the account
	System.out.println("ERROR: BankAccounts::getAccount Did not find the account!");
	return null;
    }

    /**
     * checkStatus Prints information about a given account
     * <p>
     * Using a given accNumber searches through the account database
     * and prints information relating to the account in question
     * <p>
     * @param accNumber A string holding the account number requested by user
     */
    public String checkStatus(String accNumber){
	//Iterate through the entire database
	for (int i = 0; i < this.bankAccounts.size(); i++){
	    //Look for the account that matches the accNumber
	    if (accNumber.compareTo(this.bankAccounts.get(i).number_) == 0){
		//found the account
		return this.bankAccounts.get(i).toString(true);
	    }
	}
	return "ERROR: BankAccounts::checkStatus did not find the account!";
    }

    /**
     * checkExists check if a given account exists in the database
     * <p>
     * Given an account name, searches through the entire database list and
     * returns true if an account is found with that name, otherwise returns false
     * <p>
     * @param accName A string containing an account name
     * @return boolean Returns
     */
    //Check if a given account name exists in the account database
    public boolean checkExists(String accName){
	for (int i = 0; i < this.bankAccounts.size(); i++){
	    if (accName.compareTo(this.bankAccounts.get(i).name_) == 0){
		//found the account
		return true;
	    }
	}
	//System.out.println("[BankAccounts->checkExists]ERROR: Did not find the account!");
	return false;
    }

    /**
     *  getUniqueAccountNumber Finds a unique account number
     * <p>
     * Searches through the entire database and finds the next unique account
     * number that is not already used by another account
     * <p>
     * @return uniqueNumString A string containing a unique account number
     */
    public String getUniqueAccountNumber(){
	/**
	 * Set the Maximum possible number for an account 
	 */
	final int MAX_ACCOUNT_NUM = 99999;
	//Iterate through account 1 to MAX_ACCOUNT_NUM
	for (int uniqueNumber = 1; uniqueNumber < MAX_ACCOUNT_NUM; uniqueNumber++){
	    //Iterate through the entire database to see if there is an account with
	    //the the current uniqueNumber being iterated through
	    for (int i = 0; i < this.bankAccounts.size(); i++){
		if (Integer.parseInt(this.bankAccounts.get(i).number_) == uniqueNumber){
		    //Number exists, need to find another		    
		    break;
		}		
		//The above condition never breaked -> Found a unique number
		if(i == this.bankAccounts.size() - 1){
		    //Get the string version of the uninque number
		    String uniqueNumString = String.valueOf(uniqueNumber);
		    //Pad the unique number to 5 values
		    while(uniqueNumString.length() < 5){
			//Prepend 0s to the unique number string
			uniqueNumString = "0" + uniqueNumString;
		    }
		    //System.out.println("[uniqueNumber]" + uniqueNumString);
		    return uniqueNumString;
		}
	    }
	    
	}
	System.out.println("[BankAccounts->checkExists]ERROR: Did not find the account!");
	return null;
    }

    /**
     * addAccount given an account object, adds it to the account database
     * <p>
     * Takes in an Account object provided as a parameter, and appends it
     * to the end of the "database"/list of accounts 
     * <p>
     * @param  newAccount The Account object being added to the bank account list/database
     */
    public void addAccount(Account newAccount){
	//append the new Account to the bankAccounts/database of accounts
	this.bankAccounts.add(newAccount);
    }
    
    /**
     * removeAccount removes an Account from the database
     * <p>
     * Takes in an account Number and removes it from the database/list of accounts
     * <p>
     * @param accountNumber A string holding the account number requested by user
     */
    public void removeAccount(String accountNumber){
	//Iterate through the entire list of accounts
	for (int i = 0; i < this.bankAccounts.size(); i++){
	    //Look for the acount that matches the account number provided in the parameter
	    if (accountNumber.compareTo(this.bankAccounts.get(i).number_) == 0){
		//found the account - remove it		
		this.bankAccounts.remove(i);		
		return;
	    }
	}
	System.out.println("ERROR: BankAccounts::removeAccount did not find the account!");
	return;
    }

    /**
     * writeToFile Writes all the Accounts in the database to a file provided as an argument
     * <p>
     * Given a filename/path, writes all the database/bank accounts stored internally into
     * the file provided
     * <p>
     * @param filename The name/path to the file the bank accounts should be written to
     * @param withTransactionNum a boolean value indicating if the transactionNumber 
     * number should be included when printing the account information to the file
     */
    public void writeToFile(String filename, boolean withTransactionNum){
	//put the end of file account at the end of the file being written to
	//Since it might be in the middle after accounts have been created
	//Last line should always be: 99999 END OF FILE          A 00000.00 S 0000 
	String eofAccountNum = "99999";
	Account eof = this.getAccount(eofAccountNum); //get the end of file account	
	this.removeAccount(eofAccountNum); //remove the end of file account 
	this.addAccount(eof); //append it to the end of the bank accounts

	//Write to the given filename
	try{
	    //make buffers of bufferedwriters of outputstreamed buffered writers
	    File outFile = new File(filename);
	    Writer writer = new BufferedWriter(
			    new OutputStreamWriter(
			    new FileOutputStream(outFile)));
	    //Iterate through all the accounts 
	    for (int i = 0; i < this.bankAccounts.size(); i++){
		//Write out each account on a separate line in the file
		writer.write(this.bankAccounts.get(i).toString(withTransactionNum) + "\n");
	    }
	    writer.close(); //close the file that was being written to
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}
    }
}






























