/*
******************************ALL CODE HAS BEEN PAIR PROGRAMMED******************************
*----------------------------------------Taylor Smith---------------------------------------*
*-------------------------------------Alexandar Mihaylov------------------------------------*
*-----------------------------------------Talha Zia-----------------------------------------*
*********************************************************************************************

Program Intention:
The Back End of a Command Line User Interface for a Banking System that can handle different
types of transactions and account management.

Input Files: old.mbaf trans-files/*.tf

Output Files: new.mbaf new.cbaf (trans-files/mergedTransactions.tf)

How Program is Intended to run:
make -> This is a Command Line user interface where commands are entered in
the terminal and output is displayed to the terminal. The program can be
executed with the makefile provided.
*/

import java.io.*;
import java.util.ArrayList;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-16
 */

//The back end of the banking system that contains the main function. Takes in two arguments in the form  <old-mbaf>  <list-of-transaction-files> and is responsible for creating instances of other classes that read in the master bank accounts file and all the transaction files. It then Iterates through all the transactions and calls their respective handlers 
public class backEnd{
    public static void main(String[] args){
	//check how many arguments are given
	if (args.length < 2){
	    //invalid number of arguments
	    System.out.println("Usage: <old-mbaf> <list-of-transaction-files>");
	    System.exit(0);
	}
	//read in the Master Bank Accounts File
	BankAccounts bankAccounts = new BankAccounts(args[0]);
	
	//read in all the transaction files
	ArrayList<Transaction> transactionsList = TransFileReader.read(args);
  
	//while transactions still esits, process them	
	int numTransactions = transactionsList.size();
	for(int i = 0; i < numTransactions; i++){
	    Transaction currTransaction = transactionsList.get(i);
	    //Figure out the type of the current transaction 
	    switch (currTransaction.transactionType) {
	    case LOGOUT: 
		TransactionHandler.logout(currTransaction, bankAccounts);
		break;
	    case WITHDRAWAL:
		TransactionHandler.withdrawal(currTransaction, bankAccounts);
		break;
	    case TRANSFER:
		Transaction nextTransaction = transactionsList.get(++i);
		TransactionHandler.transfer(currTransaction, nextTransaction, bankAccounts);
		break;
	    case PAYBILL:
		TransactionHandler.paybill(currTransaction, bankAccounts);
		break;
	    case DEPOSIT:
		TransactionHandler.deposit(currTransaction, bankAccounts);
		break;
	    case CREATE:
		TransactionHandler.create(currTransaction, bankAccounts);
		break;
	    case DELETE:
		TransactionHandler.delete(currTransaction, bankAccounts);
		break;
	    case DISABLE: 
		TransactionHandler.disable(currTransaction, bankAccounts);
		break;
	    case CHANGEPLAN: 
		TransactionHandler.changeplan(currTransaction, bankAccounts);
		break;
	    case ENABLE:
		TransactionHandler.enable(currTransaction, bankAccounts);
		break;
	    case LOGIN: 
		TransactionHandler.login(currTransaction, bankAccounts);
		break; 
	    }
	}
  
	//MBAF - write the end result of all the transactions being applied to new mbaf
	String newMbafFileName = "new.mbaf";
	bankAccounts.writeToFile(newMbafFileName,true);

	//CBAF - write the end result of all the transactions being applied to new mbaf
	String newCbafFileName = "new.cbaf";
	bankAccounts.writeToFile(newCbafFileName,false);
    }
}
