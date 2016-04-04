import java.text.*;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-16
 */

//Holds all the necessary information relating to an Account like the number, name, status, balance, plan, and the number of transactions. Is able to take in a string from a master bank accounts file, parse it and fill in its internal members of all the required information. Is also able to produce a string in the same format of the current account using its toString() function.
public class Account{
    //CONSTANTS
    //account Number
    private final int kAccNumStart = 0;
    private final int kAccNumEnd = 5;

    //account holder
    private final int kAccNameStart = 6;
    private final int kAccNameEnd = 26;

    //account Status
    private final int kAccStatusStart = 27;
    private final int kAccStatusEnd = 28;

    //account balance
    private final int kAccBalanceStart = 29;
    private final int kAccBalanceEnd = 37;

    //account plan(student/nonstudent)
    private final int kAccPlanStart = 38;
    private final int kAccPlanEnd = 39;

    //number of transactions for an account
    private final int kAccTransNumStart = 40;
    private final int kAccTransNumEnd = 44;
    
    //Members
    String number_; 
    String name_;
    String status_; //If Active or Disactivated
    double balance_;
    String plan_; //If Student or non-Student plan
    int num_trans_; //The number of transactions the account has to date
    
    /**
     * Account Constructor
     * <p>
     * Takes in a raw string in the form of :
     * 00001 TESTUSER1            A 99999.99 N 0000
     * and parses each piece of information in the respective class members
     * <p>
     * @param mbafInputLine A string containing the raw Account String in the format above
     */
    public Account (String mbafInputLine){
	//Parse the raw master bank account file line into the respective members
	this.number_ = mbafInputLine.substring(kAccNumStart, kAccNumEnd);
	this.name_ = mbafInputLine.substring(kAccNameStart, kAccNameEnd);
	this.status_ = mbafInputLine.substring(kAccStatusStart, kAccStatusEnd);
	this.balance_ = Double.parseDouble(mbafInputLine.substring(kAccBalanceStart,
								   kAccBalanceEnd));
	this.plan_ = mbafInputLine.substring(kAccPlanStart, kAccPlanEnd);
	this.num_trans_ = Integer.parseInt(mbafInputLine.substring(kAccTransNumStart,
								     kAccTransNumEnd));
    }

    /**
     * toString converts an account object into a string
     * <p>
     * Returns a string with all the account information in the following format
     * 00001 TESTUSER1            D 99992.69 N. If the boolean passed to this function
     * is true, then the number of transactions are also included at the end of the string
     * <p>
     * @param withTransactionNum a boolean value indicating if the transactionNumber 
     * number should be included in the final string being returned
     * @return Returns a string in for followin format depending on withTransactionNum
     * [true]  00001 TESTUSER1            D 99992.69 N 0003 
     * [false] 00001 TESTUSER1            D 99992.69 N
     */
    public String toString(boolean withTransactionNum){
	//set the format of how account balances will be read
	DecimalFormat df = new DecimalFormat("#.00");
	String returnString = "";
	    returnString += this.number_ + " ";
	    returnString += this.name_ + " ";
	    returnString += this.status_ + " ";
	    //need to pad the balance to 8 characters
	    String balanceString = df.format(this.balance_);	    
	    while(balanceString.length() < 8){
		balanceString = "0" + balanceString;
	    }
	    returnString += balanceString; //update the final string

	    //Check if a transaction number for the account should be printed
	    if (withTransactionNum){
		returnString += " ";
		//obtain the number of transactions from the account		
		String numTransString = String.valueOf(this.num_trans_).trim();
		//pad the transaciton number to 4 characters
		while (numTransString.length() < 4){
		    numTransString = "0" + numTransString;
		}
		returnString += numTransString; //update the final string
	    }
	return returnString;
    }

}





























