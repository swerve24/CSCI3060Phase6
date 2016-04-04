import java.text.*;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-16
 */

//Holds all information relating to a single transaction. This includes holding information like the transaction code/type, the account name, number and funds involved in the transaction, and also if the transaction was done by an admin or regular user. The constructor of this class is able to take in a raw string read in from a transaction (.tf) file, parse it and populate all the internal respective fields. The class is also able to convert the current transaction object into the same raw string format that it originally read it in.
public class Transaction{
   
    final int TRANSACTION_CODE_START = 0;
    final int TRANSACTION_CODE_END = 2;

    final int ACCOUNT_NAME_START = 3;
    final int ACCOUNT_NAME_END = 23;

    final int ACCOUNT_NUMBER_START = 24;
    final int ACCOUNT_NUMBER_END = 29;

    final int FUNDS_INVOLVED_START = 30;
    final int FUNDS_INVOLVED_END = 38;

    final int MISC_START = 39;
    final int MISC_END = 41;

    /**
     * Transaction Constructor
     * <p>
     * Takes in a raw string transaction in the form:
     * 10 ADMIN                00000 00000.00 A 
     * parses it and populates the internal member variables of the
     * Transaction class accordingly
     * <p>
     * @param withTransactionNum a transaction in a raw string format:
     * 10 ADMIN                00000 00000.00
     * which is passed in and parsed
     * number should be included in the final string being returned
     */
    public Transaction(String transactionFileLine){      
	this.transactionCode = transactionFileLine.substring(TRANSACTION_CODE_START,
							     TRANSACTION_CODE_END);
	this.transactionType = TransactionName.values()[Integer.parseInt(transactionCode)];
	this.accountName = transactionFileLine.substring(ACCOUNT_NAME_START,
							 ACCOUNT_NAME_END);
	this.accountNumber = transactionFileLine.substring(ACCOUNT_NUMBER_START,
							   ACCOUNT_NUMBER_END);
	this.fundsInvolved = Float.parseFloat(transactionFileLine.substring(FUNDS_INVOLVED_START,
									    FUNDS_INVOLVED_END));
	this.misc = transactionFileLine.substring(MISC_START,
						  MISC_END);      
    }
    
    String transactionCode;
    TransactionName transactionType; //enum representing what transaction is being refered to
    String accountName;
    String accountNumber;
    float fundsInvolved; 
    String misc; //Holds information regarding if the account is an admin or standard "A" or "S"

    /**
     * toString Converts a transaction object into a string
     * <p>
     * COnverts a transaction object into a string in the following format
     * 10 ADMIN                00000 00000.00 A 
     * <p>
     * @return returnString a string containing the raw form of a transaction
     */    
    @Override
    public String toString(){
	//Set the format of how the transaction balance will be read
	DecimalFormat df = new DecimalFormat("#.00");
	String returnString = "";
      
	String paddedFundsInvolved = df.format(this.fundsInvolved);
      
	while(paddedFundsInvolved.length() < 8){
	    paddedFundsInvolved = "0" + paddedFundsInvolved;
	}
      
	returnString += this.transactionCode + " ";
	returnString += this.accountName + " ";
	returnString += this.accountNumber + " ";
	returnString += paddedFundsInvolved + " ";
	returnString += this.misc;
      
	return returnString;
    }
}
