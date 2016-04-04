import java.text.*;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-16
 */

/**
 * Used to handle every single type of transaction in the banking system. 
 * Has functions for every transaction and each handler typically takes in
 * a Transaction object and the current bank account database. With each
 * transaction it modifies the given account database accordingly. 
*/
public class TransactionHandler{    

    //MEMBERS
    
    //keeps track if the transaction being handled is done by an admin
    private static boolean isAdmin = false;
    /**
     * setIsAdmin Sets the value for the isAdmin private member 
     * <p>
     * Used as a setter for the isAdmin variable
     * <p>
     * @param setValue Value used to set isAdmin
     */
    public static void setIsAdmin(boolean setValue){
	isAdmin = setValue;
    }

    /**
     * getIsAdmin gets the value for the isAdmin private member 
     * <p>
     * Used as a getter for the isAdmin variable
     * <p>
     * @return return value for isAdmin
     */
    public static boolean getIsAdmin(){
	return isAdmin;
    }

    /**
     * logout responsible for the logout transaction
     * <p>
     * Does not actually affect the account database, simply sets the admin to false
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void logout(Transaction t, BankAccounts b){
	//System.out.println(t.transactionType);
	//set the admin variable to false
	isAdmin = false;
    }

    /**
     * withdrawal responsible for the withdrawal transaction
     * <p>
     * Ensures that the funds being withdrawn are subtracted from the account's
     * balance and also takes into account the fees depending on the user is
     * a student or if the transaction is performed by an admin. After calculating
     * the actual amount, it updates the database
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void withdrawal(Transaction t, BankAccounts b){
    	//System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	//b.checkStatus(t.accountNumber); //temp
	//remove the withdrawn amount
	double withdrawalAmount = t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		withdrawalAmount += 0.05;
	    }else{
		//Not a student account
		withdrawalAmount += 0.10;
	    }
	}

	//Check if the account balance is less than 0 once amount has been withdrawn
	if (currAccount.balance_ - withdrawalAmount < 0){
	    System.out.println("ERROR: Attempt to withdrawal more funds than possible");
	}else{
	    //finally remove the funds from the account balance
	    currAccount.balance_ -= withdrawalAmount;	    
	    currAccount.balance_ = Math.round(currAccount.balance_ * 100.0) / 100.0; //rounding
	    currAccount.num_trans_++; //increment the transaction number   
	}
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * transfer responsible for the transfer transaction
     * <p>
     * Ensures that the funds being transfered are subtracted from the sender account's
     * balance and added to the receivers account balance. Also takes into account the
     * fees depending on the user is a student or if the transaction is performed by an
     * admin. After calculating the actual amount, it updates the database
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void transfer(Transaction t1, Transaction t2, BankAccounts b){
	//System.out.println(t1.transactionType);
	//b.checkStatus(t1.accountNumber); //temp
	//b.checkStatus(t2.accountNumber); //temp

	//obtain the current account in question
	Account firstAccount = b.getAccount(t1.accountNumber);
	Account secondAccount = b.getAccount(t2.accountNumber);
	//remove the transfer amount
	double transferAmount = t1.fundsInvolved;
	double fee = 0.00;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (firstAccount.plan_.compareTo("S") == 0){
		//is a student account
		fee = 0.05;
	    }else{
		//Not a student account
		fee = 0.10;
	    }
	}
	//add the fee to the transferAmount
	//transferAmount += fee;
	//Check if the account balance is less than 0 once amount has been transfered
	//System.out.println("acc1 balance:" + firstAccount.balance_ +
	//" transfer Amount:" + transferAmount +
	//" fee:" + fee);
	if (firstAccount.balance_ - transferAmount - fee < 0){
	    System.out.println("ERROR: Transaction leaves First account in negative balance");
	}else if(secondAccount.balance_ + transferAmount - fee < 0){
	    System.out.println("ERROR: Transaction leaves Second account in negative balance");
	}else{
	    //finally remove the funds from the accounts balance
	    firstAccount.balance_ -= transferAmount + fee ;
	    firstAccount.balance_ = Math.round(firstAccount.balance_ * 100.0) / 100.0; //rounding
	    secondAccount.balance_ += transferAmount - fee;
	    secondAccount.balance_ = Math.round(secondAccount.balance_ * 100.0) / 100.0; //rounding
	    firstAccount.num_trans_++; //increment the transaction number
	    secondAccount.num_trans_++; //increment the transaction number   
	}
	//b.checkStatus(t1.accountNumber); //temp
	//b.checkStatus(t2.accountNumber); //temp
    }

    /**
     * paybill responsible for the paybill transaction
     * <p>
     * Ensures that the funds being paid are subtracted from the account's
     * balance and also takes into account the fees depending on the user is
     * a student or if the transaction is performed by an admin. After calculating
     * the actual amount, it updates the database
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void paybill(Transaction t, BankAccounts b){
    	//System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	//b.checkStatus(t.accountNumber); //temp
	//remove the paybill amount
	double paybillAmount = t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		paybillAmount += 0.05;
	    }else{
		//Not a student account
		paybillAmount += 0.10;
	    }
	}

	//Check if the account balance is less than 0 once amount has been withdrawn
	if (currAccount.balance_ - paybillAmount < 0){
	    System.out.println("ERROR: Attempt to paybill more funds than possible");
	}else{
	    //finally remove the funds from the account balance
	    currAccount.balance_ -= paybillAmount;
	    currAccount.balance_ = Math.round(currAccount.balance_ * 100.0) / 100.0; //rounding
	    currAccount.num_trans_++; //increment the transaction number   
	}
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * deposit responsible for the deposit transaction
     * <p>
     * Ensures that the funds being deposited are added from the account's
     * balance and also takes into account the fees depending on the user is
     * a student or if the transaction is performed by an admin. After calculating
     * the actual amount, it updates the database
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void deposit(Transaction t, BankAccounts b){
    	//System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	//b.checkStatus(t.accountNumber); //temp
	//remove the deposit amount
	double depositAmount = t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		depositAmount -= 0.05;
	    }else{
		//Not a student account
		depositAmount -= 0.10;
	    }
	}

	//Check if the account balance is less than 0 once amount has been deposit
	if (currAccount.balance_ + depositAmount < 0){
	    System.out.println("ERROR: Deposit will result in negative account balance!");
	}else{
	    //finally add the funds from the account balance
	    currAccount.balance_ += depositAmount;	    
	    currAccount.balance_ = Math.round(currAccount.balance_ * 100.0) / 100.0; //rounding
	    currAccount.num_trans_++; //increment the transaction number   
	}
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * create responsible for the create transaction
     * <p>
     * Ensures that the funds being deposited are added from the account's
     * balance and also takes into account the fees depending on the user is
     * a student or if the transaction is performed by an admin. After calculating
     * the actual amount, it updates the database
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void create(Transaction t, BankAccounts b){
	String newAccountNumber = "";
    	//System.out.println(t.transactionType);
	//b.checkStatus(t.accountNumber); //temp
	if(!b.checkExists(t.accountName)){
	    //accunt does not exist
	    newAccountNumber =  b.getUniqueAccountNumber();
	    String newAccount_string = "";
	    newAccount_string += newAccountNumber;
	    newAccount_string += " ";
	    newAccount_string += t.accountName;
	    newAccount_string += " ";
	    newAccount_string += "A";
	    newAccount_string += " ";
	    DecimalFormat df = new DecimalFormat("#.00");
	    String init_balance = df.format(t.fundsInvolved);
	    while (init_balance.length() < 8){
		init_balance = "0" + init_balance;
	    }
	    newAccount_string += init_balance;
	    newAccount_string += " ";
	    newAccount_string += "N";
	    newAccount_string += " ";
	    newAccount_string += "0000";
	    Account newAccount = new Account(newAccount_string);
	    //System.out.println(newAccount.toString()); //temp
	    b.addAccount(newAccount);//add the account to the database
	};
	//b.checkStatus(newAccountNumber); //temp
    }

    /**
     * delete responsible for the delete transaction
     * <p>
     * Removes the account involved in the transaction from the database
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void delete(Transaction t, BankAccounts b){
    	//System.out.println(t.transactionType);
	//b.checkStatus(t.accountNumber); //temp
	b.removeAccount(t.accountNumber);  //other tests depend on this account
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * disable responsible for the disable transaction
     * <p>
     * Disables the account involved in the transaction by settings it status to "D"
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void disable(Transaction t, BankAccounts b){
    	//System.out.println(t.transactionType);
	//b.checkStatus(t.accountNumber); //temp
	b.getAccount(t.accountNumber).status_ = "D";
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * changeplan responsible for the changeplan transaction
     * <p>
     * Toggles the account plan from Student to Non-Student by setting 
     * its plan to "S" or "N" respectively
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void changeplan(Transaction t, BankAccounts b){	
    	//System.out.println(t.transactionType);
	//b.checkStatus(t.accountNumber); //temp
	String currentPlan = b.getAccount(t.accountNumber).plan_;
	if (currentPlan.compareTo("N") == 0){
	    b.getAccount(t.accountNumber).plan_ = "S";
	}else{
	    b.getAccount(t.accountNumber).plan_ = "N";
	}
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * enable responsible for the enable transaction
     * <p>
     * Enables the account involved in the transaction by settings it status to "E"
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void enable(Transaction t, BankAccounts b){
	//System.out.println(t.transactionType);
	//b.checkStatus(t.accountNumber); //temp
	b.getAccount(t.accountNumber).status_ = "A";
	//b.checkStatus(t.accountNumber); //temp
    }

    /**
     * login responsible for the login transaction
     * <p>
     * Responsible for finding out if the transaction is being performed by an admin
     * <p>
     * @param t A Transaction object that contains all the required information
     * of the current transaction being performed
     * @param b The BankAccounts object that contains the current state of all
     * the bank accounts in the system
     */
    public static void login(Transaction t, BankAccounts b){
    	//System.out.println(t.transactionType);
	//check if it is an admin logging in
	if (t.misc.compareTo("A ") == 0){
	    //is an admin logged in
	    isAdmin = true;
	}else{
	    //not an admin
	    isAdmin = false;
	}
    }
}






























