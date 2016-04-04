/* 
 * TransactionHelper.h
 * 
 * Authors: Denesh Parthipan, Luisa Rojas, Truyen Truong
 */

#ifndef TRANSACTIONHELPER_H
#define TRANSACTIONHELPER_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <iomanip>
#include "Standard.h"

using namespace std;

class Standard;
class TransactionHelper;

extern Standard curr_user;
extern vector<Standard> users;
extern vector<Standard> new_users;
extern vector<string> transaction_file;
extern string mode;
extern string acc_holder;
extern bool is_logged;
extern TransactionHelper transactions;

class TransactionHelper {
 public:

  /* To compare user input - should accept variations
   * (e.g. "Standard", "standard", "STANDARD", etc)
   */
  string to_Lower(string str);

  // Check if the curret user is an administrator
  bool is_Admin();

  // Check if the account holder name inputed exists in the "database"
  bool HolderExists(string name);

  // Check if the account number inputed exists in the "database"
  bool NumExists(int acc_num);

  bool FileExists(string file_name);

  /* Check that the new account holder name entered follows the
   * required constraints. Done using regex.
   */
  bool is_Name_Valid(string name);

  // Checks that both arguments correspond to eachother
  bool Matches(string name, int acc_num);

  /* Checks that the amound of funds entered is valid
   * (e.g. formatting). Done using regex.
   */
  bool is_Amount_Valid(string amount);

  // Checks if the account provided is active or disabled
  bool is_Disabled(int acc_num);

  /* Checks if the user's transaction payment plan
   * (student or non-student)
   */
  bool is_Student(int acc_num);

  bool is_New(int acc_num);

  // Outputs the transaction_file vector into a file
  void WriteTransactionFile();

  /* Loads all accounts' information from the
   * current_bank_accounts_file.txt file (provided by the back end)
   */
  void LoadAccounts(string file_name);

  // Prints out the welcome message.
  void PrintWelcomeMessage();

  // Allows the users to log in as a STANDARD user
  void Login();

  // Logs user out from either account - administrator or standard
  void Logout();

  // Prints the help menu.
  void PrintHelp();
};

#endif