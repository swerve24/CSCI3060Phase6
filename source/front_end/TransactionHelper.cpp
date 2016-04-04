/* 
 * TransactionHelper.cpp
 * 
 * Authors: Denesh Parthipan, Luisa Rojas, Truyen Truong
 */

#include "TransactionHelper.h"
//#include "User.h"

/* To compare user input - should accept variations
 * (e.g. "Standard", "standard", "STANDARD", etc)
 */
string TransactionHelper::to_Lower(string str) {

  for (int i = 0; i < str.length(); i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}

// Check if the curret user is an administrator
bool TransactionHelper::is_Admin() {
  if (mode.compare("admin") == 0)
    return true;
  return false;
}

// Check if the account holder name inputed exists in the "database"
bool TransactionHelper::HolderExists(string name) {

  bool ret = false;

  for (int i = 0; i < users.size(); i++) {
    if (((users.at(i).GetName()).compare(name)) == 0) {			
      ret = true;
      break;
    }
  }
  return ret;
}

// Check if the account number inputed exists in the "database"
bool TransactionHelper::NumExists(int acc_num) {

  bool ret = false;

  for (int i = 0; i < users.size(); i++) {
    if (users.at(i).GetNum() == acc_num) {			
      ret = true;
      break;
    }
  }
  return ret;
}

bool TransactionHelper::FileExists(string file_name) {

  ifstream infile;
  infile.open(file_name);

  if (!infile)
    return false;
  else
    return true;

  infile.close();
}

/* Check that the new account holder name entered follows the
 * required constraints: non-empty.
 */
bool TransactionHelper::is_Name_Valid(string name) {

	if (!name.empty())
    return true;
  else
    return false;
}

// Checks that both arguments correspond to eachother
bool TransactionHelper::Matches(string name, int acc_num) {

  bool ret = false;

  for (int i = 0; i < users.size(); i++) {
    if (((users.at(i).GetName()).compare(name)) == 0) {     
      if (users.at(i).GetNum() == acc_num) {
        ret = true;
        break;
      }
    }
  }
  return ret;
}

/* Checks that the amound of funds entered is valid
 * (e.g. formatting). Done using regex.
 */
bool TransactionHelper::is_Amount_Valid(string amount) {
  
  //Formats to be accepted: 5.50, 0.50, .50. Decimals are mandatory.
  regex re("[0-9]{0,5}\\.[0-9]{2}");

  if (regex_match(amount, re))
    return true;
  else
    return false;
}

// Checks if the account provided is active or disabled
bool TransactionHelper::is_Disabled(int acc_num) {
  
  bool ret = false;

  for (int i = 0; i < users.size(); i++) {
    if (((users.at(i).GetNum()) == acc_num)) {
      string str;    
      if (users.at(i).GetStatus() == 'D') {
        ret = true;
        break;
      }
    }
  }
  return ret;
}

/* Checks if the user's transaction payment plan
 * (student or non-student)
 */
bool TransactionHelper::is_Student(int acc_num) {
  
  bool ret = false;

  for (int i = 0; i < users.size(); i++) {
    if (((users.at(i).GetNum()) == acc_num)) {  
      string str;   
      if (users.at(i).GetPlan() == 'S') {
        ret = true;
        break;
      }
    }
  }
  return ret;
}

/* Checks if the user was created recently
 */
bool TransactionHelper::is_New(int acc_num) {
  
  bool ret = false;

  for (int i = 0; i < new_users.size(); i++) {
    if (new_users.at(i).GetNum() == acc_num) {     
      ret = true;
      break;
    }
  }
  return ret;
}

// Outputs the transaction_file vector into a file
void TransactionHelper::WriteTransactionFile() {
  
  int i = 1;

  string file_name = "transaction_file_" + to_string(i) + ".tra";

  while (FileExists(file_name)) {
    i++;
    file_name = "transaction_file_" + to_string(i) + ".tra";
  }

  ofstream outfile(file_name);

  if (outfile.is_open()) {
    for (int i = 0; i < transaction_file.size(); i++) {
      outfile << transaction_file.at(i) + "\n";
    }
    outfile.close();
  } else {
    cerr << "\n>>> ERROR: Unable to open transaction file\n" << endl;
  }
}

/* Loads all accounts' information from the
 * current_bank_accounts_file.txt file (provided by the back end)
 */
void TransactionHelper::LoadAccounts(string file_name) {

  ifstream infile(file_name);

  string acc_holder;
  char acc_status, acc_plan;
  int acc_num;
  float acc_balance;

  if (infile) {
    while (true) {

      infile >> acc_num >> acc_holder >> acc_status >> acc_balance >> acc_plan;
      Standard u;

      if(infile.eof())
        break;

      u.SetName(acc_holder);
      u.SetNum(acc_num);
      u.SetBalance(acc_balance);
      u.SetStatus(acc_status);
      u.SetPlan(acc_plan);
      users.push_back(u);
    }

    infile.close();
  } else {
    cerr << "\n>>> ERROR: File \"" << file_name << "\" was not found.\n" << endl;
  exit(-1);
  }
}

void TransactionHelper::PrintWelcomeMessage() {

cout << " __    __      _                           _ " << endl;           
cout << "/ / /\\ \\ \\__ _| |_ ___ _ __ _ __ ___   ___| | ___  _ __ " << endl;  
cout << "\\ \\/  \\/ / _` | __/ _ \\ '__| '_ ` _ \\ / _ \\ |/ _ \\| '_ \\" << endl;  
cout << " \\  /\\  / (_| | ||  __/ |  | | | | | |  __/ | (_) | | | |" << endl;  
cout << "  \\/  \\/ \\__,_|\\__\\___|_|  |_| |_| |_|\\___|_|\\___/|_| |_|" << endl;  
                                                              
  cout << "\nWelcome to Watermelon Banking System." << endl;
  cout << "Please log in to begin or enter \"help\" for more information.\n" << endl;
}

// Allows the users to log in as a STANDARD user
void TransactionHelper::Login() {

  if (!is_logged) {
    cout << "\nEnter mode in which you wish to log in as: ";
    cin >> mode;

    if (transactions.to_Lower(mode).compare("admin") == 0) {
      mode = "admin";
      is_logged = true;
      cout << "\nYou are currently logged in as an administrator." << endl;
      cout << "\nEnter a command.\n" << endl;

      transaction_file.push_back("10                                     A ");

    } else if (transactions.to_Lower(mode).compare("standard") == 0) {

      mode = "standard";
      string padded_acc_num;
      stringstream stream;
      string padded_balance;
      string padded_acc_holder;

      // Save the account holder's name
      cout << "Enter account holder's name: ";
      cin.ignore();
      getline(cin, acc_holder);

      /* If the name stored is found in the users vector, then
       * update the curr_user User object with the new curr_user
       * information for future transactions
       */
      if (HolderExists(acc_holder) && acc_holder != "END_OF_FILE") {

        is_logged = true;

        for (int i = 0; i < users.size(); i++) {
          if (users.at(i).GetName().compare(acc_holder) == 0) {
            curr_user = users.at(i);
          }
        }

        padded_acc_holder = acc_holder;
        while(padded_acc_holder.length() < 20) {
          padded_acc_holder = padded_acc_holder + " ";
        }

        padded_acc_num = to_string(curr_user.GetNum());
        while(padded_acc_num.length() < 5) {
          //cout << "[DEBUGGING] In second while loop" << endl;
          padded_acc_num = "0" + padded_acc_num;
        }

        //padded_balance = to_string(curr_user.GetBalance());
        stream << fixed << setprecision(2) << curr_user.GetBalance();
        padded_balance = stream.str();
        while(padded_balance.length() < 8) {
          padded_balance = "0" + padded_balance;
        }

        // Output the accounts' information in a user-friendly/readable way
        cout << "\nYou are currently logged in as " << curr_user.GetName() << "." << endl;
        cout << "Bank account number: " << padded_acc_num << endl;
        cout << "Balance: $" << padded_balance << endl;
        if (curr_user.GetPlan() == 'S')
          cout << "Transaction payment plan: Student" << endl;
        else if (curr_user.GetPlan() == 'N')
          cout << "Transaction payment plan: Non-student" << endl;
        else 
          cerr << "\n>>> ERROR: Could not get payment plan information.\n" << endl;     
        
        if (curr_user.GetStatus() == 'D')
          cout << "Status: Disabled" << endl;
        else if (curr_user.GetStatus() == 'A')
          cout << "Status: Active" << endl;
        else
          cerr << "\n>>> ERROR: Could not get status information.\n" << endl;

        cout << "\nEnter a command.\n" << endl; 

        string transaction_line = "10 " + padded_acc_holder + " " + padded_acc_num + "          S ";
        transaction_file.push_back(transaction_line);

      } else {
        // The name is not found in the "database"
        cerr << "\n>>> ERROR: The account holder entered is invalid.\n" << endl;
      }
    } else {
      cerr << "\n>>> ERROR: Invalid account mode.\n" << endl;
    }
  } else {
    cout << "\n>>> ERROR: There is a session running. Please log out and try again.\n" << endl;
  }
}

// Logs user out from either account - administrator or standard
void TransactionHelper::Logout() {

  string padded_acc_holder;
  string padded_acc_num;
  int acc_num;

  if (is_logged) {

    cout << "\nYou have successfully logged out of your account.\n\nLogin or enter \"help\" for more information.\n" << endl;

    if (is_Admin()) {
      transaction_file.push_back("00                                     A ");
    } else {

      for (int i = 0; i < users.size(); i++) {
        if (users.at(i).GetName().compare(acc_holder) == 0) {
          acc_num = users.at(i).GetNum();
        }
      }

      padded_acc_holder = acc_holder;
      while (padded_acc_holder.length() < 20) {
        padded_acc_holder = padded_acc_holder + " ";
      }

      padded_acc_num = to_string(acc_num);
      while (padded_acc_num.length() < 5) {
        padded_acc_num = "0" + padded_acc_num;
      }

      string transaction_line = "00 " + padded_acc_holder + " " + padded_acc_num + "          S ";
      transaction_file.push_back(transaction_line);
    }

    // Resets all variables for next user
    is_logged = false;
    mode = "";
    acc_holder = "";

    WriteTransactionFile();

  } else {
    // There is no running session to be logged out of
    cerr << "\n>>> ERROR: You are not currently logged into an account.\n" << endl;
  }
}

void TransactionHelper::PrintHelp() {

  string file_name = "help.txt";
  string line;

  ifstream infile(file_name);

  if (infile) {
    while (getline (infile,line)) {
      cout << line << endl;
    }
    infile.close();
    cout << "\nEnter a command.\n" << endl;
  } else {
    cerr << "\n>>>ERROR: File \"" << file_name << "\" was not found.\n" << endl;
    exit(-1);
  }
}