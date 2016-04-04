/* 
 * Administrator.cpp
 * 
 * Authors: Denesh Parthipan, Luisa Rojas, Truyen Truong
 */

#include "Administrator.h"

// Administrator implementation of withdrawal.
void Administrator::Withdrawal() {

  string padded_acc_holder;
  string padded_acc_num;
  string padded_amount;
  string padded_new_balance;
  string acc_holder;
  string temp_acc_num;
  string temp_amount;
  stringstream stream;
  float amount;
  float new_balance = 0.0;
  int acc_num;

  // Notify user that withdrawal transaction was selected.
  cout << "\nWithdrawal transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Checks if the account holder exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;

  // Checks if user is END_OF_FILE.
  } else if (acc_holder.compare("END_OF_FILE") == 0) {
    cerr << "\n>>> ERROR: You may not withdraw funds from this account.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check format of account number.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // Check if account holder name and account number match.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Checks if the account is disabled.
    if (transactions.is_Disabled(acc_num)) {
      cerr << "\n>>> ERROR: Disabled accounts may not withdraw funds.\n" << endl;
      return;

    // Checks if the account was created during the current day.
    } else if (transactions.is_New(acc_num)) {
      cerr << "\n>>> ERROR: Newly created accounts may not withdraw funds. Please try again in 24 hours.\n" << endl;
      return;
    }

    // Prompt and get the amount to withdraw.
    cout << "Enter amount to withdraw: ";
    cin >> temp_amount;

    // Check if the amount format is valid.
    if (transactions.is_Amount_Valid(temp_amount)) {
      amount = stof(temp_amount);
    } else {
      cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
      return;
    }

    // Pad all the variables with necessary spaces.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    padded_amount = temp_amount;
    while (padded_amount.length() < 8) {
      padded_amount = "0" + padded_amount;
    }

    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num) {

        if ((users.at(i).GetBalance() - users.at(i).GetDeposited()) < amount) {
          cerr << "\n>>> ERROR: You may not withdraw recently deposited funds.\n" << endl;
          return;
        }

        // Checks if the amount is valid. based on the balance and amount.
        if (amount <= users.at(i).GetBalance() && (amount > 0.0) && fmod(amount, 5.0) == 0) {
          new_balance = users.at(i).GetBalance() - amount;
          users.at(i).SetBalance(new_balance);
          break;
        } else {
          cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
          return;
        }
      }
    }

    // Pads the balance to have 2 decimal points.
    stream << fixed << setprecision(2) << new_balance;
    padded_new_balance = stream.str();
    while (padded_new_balance.length() < 8) {
      padded_new_balance = "0" + padded_new_balance;
    }
  
    // Print out success notification.
    cout << "\nFunds have been successfully withdrawn from the account " << padded_acc_num << "." << endl;
    cout << "New balance: $" + padded_new_balance << endl;

    // Saves a log for the transaction file.
    string transaction_line = "01 " + padded_acc_holder + " " + padded_acc_num + " " + padded_amount + "   ";
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;

  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator implementation of transfer.
void Administrator::Transfer() {

  string padded_acc_holder_f;
  string padded_acc_holder_t;
  string padded_acc_num_f;
  string padded_acc_num_t;
  string padded_amount;
  string padded_new_balance_f;
  string padded_new_balance_t;
  string acc_holder_f;
  string acc_holder_t;
  string temp_acc_num_f;
  string temp_acc_num_t;
  string temp_amount;
  stringstream stream;
  float amount;
  float new_balance_f = 0.0;
  float new_balance_t = 0.0;
  int acc_num_f;
  int acc_num_t;

  // Notify user that transfer transaction was selected.
  cout << "\nTransfer transaction selected.\n" << endl;

  // Prompt and get origin account holder's name.
  cout << "Enter the origin account holder's name: ";
  cin >> acc_holder_f;

  // Check if origin account holder's name is valid.
  if (!transactions.HolderExists(acc_holder_f)) {
    cerr << "\n>>> ERROR: The origin account holder's name is invalid.\n" << endl;
    return;

  // Check if origin account holder's name is END_OF_FILE.
  } else if (acc_holder_f.compare("END_OF_FILE") == 0) {
    cerr << "\n>>> ERROR: You may not transfer funds from this account.\n" << endl;
    return;
  }

  // Prompt and get origin account number.
  cout << "Enter origin account number: ";
  cin >> temp_acc_num_f;

  // Check if format for account number is valid.
  regex re_f("[0-9]{0,5}");
  if (regex_match(temp_acc_num_f, re_f)) {
    acc_num_f = stoi(temp_acc_num_f);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // Check if origin account holder's name matches origin account number.
  if (transactions.Matches(acc_holder_f, acc_num_f)) {

    // Check if origin account is disabled.
    if (transactions.is_Disabled(acc_num_f)) {
      cerr << "\n>>> ERROR: Disabled accounts may not send funds.\n" << endl;
      return;

    // Check if origin account was created on the current day.
    } else if (transactions.is_New(acc_num_f)) {
      cerr << "\n>>> ERROR: Newly created accounts may not send funds. Please try again in 24 hours.\n" << endl;
      return;
    }

    // Prompt and get destination account number.
    cout << "Enter destination account number: ";
    cin >> temp_acc_num_t;

    // Check format for destination account number is valid.
    regex re_t("[0-9]{0,5}");
    if (regex_match(temp_acc_num_t, re_t)) {
      acc_num_t = stoi(temp_acc_num_t);
    } else {
      cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
      return;
    }

    // Check if the destination account number exists and is not END_OF_FILE.
    if (!transactions.NumExists(acc_num_t) || acc_num_t == 99999) {
      cerr << "\n >>> ERROR: The destination account number entered is invalid.\n" << endl;
      return;
    }

    // Check if the destination account is disabled.
    if (transactions.is_Disabled(acc_num_t)) {
      cerr << "\n>>> ERROR: Disabled accounts may not receive funds.\n" << endl;
      return;

    // Check if the destination account was created on the current day.
    } else if (transactions.is_New(acc_num_t)) {
      cerr << "\n>>> ERROR: Newly created accounts may not receive funds. Please try again in 24 hours.\n" << endl;
      return;
    }

    // Prompt and get the amount to transfer.
    cout << "Enter amount to transfer: ";
    cin >> temp_amount;

    // Check if the format of amount is valid.
    if (transactions.is_Amount_Valid(temp_amount)) {
      amount = stof(temp_amount);
    } else {
      cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
      return;
    }

    // Get the account holder's name for the destination account.
    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num_t) {
        acc_holder_t = users.at(i).GetName();
      }
    }

    // Pad with spaces to fit the formats.
    padded_acc_holder_f = acc_holder_f;
    while (padded_acc_holder_f.length() < 20) {
      padded_acc_holder_f = padded_acc_holder_f + " ";
    }

    padded_acc_holder_t = acc_holder_t;
    while (padded_acc_holder_t.length() < 20) {
      padded_acc_holder_t = padded_acc_holder_t + " ";
    }

    padded_acc_num_f = temp_acc_num_f;
    while (padded_acc_num_f.length() < 5) {
      padded_acc_num_f = "0" + padded_acc_num_f;
    }

    padded_acc_num_t = temp_acc_num_t;
    while (padded_acc_num_t.length() < 5) {
      padded_acc_num_t = "0" + padded_acc_num_t;
    }

    padded_amount = temp_amount;
    while (padded_amount.length() < 8) {
      padded_amount = "0" + padded_amount;
    }

    for (int i = 0; i < users.size(); i++) {
    
      for (int j = 0; j < users.size(); j++) {
        if (users.at(i).GetNum() == acc_num_f && users.at(j).GetNum() == acc_num_t) {

          // Check if the amount has been recently deposited.
          if ((users.at(i).GetBalance() - users.at(i).GetDeposited()) < amount) {
            cerr << "\n>>> ERROR: You may not transfer recently deposited funds.\n" << endl;
            return;
          }

          // Check if the sender can send that amount, and the receiver can receive that amount,
          if (amount <= users.at(i).GetBalance() && (amount > 0.0) && (amount + users.at(j).GetBalance()) < 100000.00) {
            new_balance_f = users.at(i).GetBalance() - amount;
            new_balance_t = users.at(j).GetBalance() + amount;
            users.at(i).SetBalance(new_balance_f);
            users.at(j).SetBalance(new_balance_t);
            users.at(j).SetDeposited(users.at(j).GetDeposited() + amount);
            break;
          } else {
            cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
            return;
          }
        }
      }
    }

    // Sets the balance to have precision of 2.
    stream << fixed << setprecision(2) << new_balance_f;
    padded_new_balance_f = stream.str();
    while (padded_new_balance_f.length() < 8) {
      padded_new_balance_f = "0" + padded_new_balance_f;
    }
  
    // Notifies the user of success of transfer.
    cout << "\nFunds have been successfully transfered from account " << padded_acc_num_f << " to account " << padded_acc_num_t << "." << endl;
    cout << "New balance: $" + padded_new_balance_f << endl;

    // Logs the transfer for the transaction file.
    string transaction_line = "02 " + padded_acc_holder_f + " " + padded_acc_num_f + " " + padded_amount + "   ";
    transaction_file.push_back(transaction_line);
    transaction_line = "02 " + padded_acc_holder_t + " " + padded_acc_num_t + " " + padded_amount + "   ";
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;

  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator implementation of paybill.
void Administrator::Paybill() {

  string padded_acc_holder;
  string padded_acc_num;
  string padded_amount;
  string padded_new_balance;
  string acc_holder;
  string temp_acc_num;
  string temp_amount;
  string company;
  stringstream stream;
  float amount;
  float new_balance = 0.0;
  int acc_num;

  // Notify user that paybill transaction was selected.
  cout << "\nPay bill transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Checks if the account holder exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;

  // Check if the account holder's name is END_OF_FILE.
  } else if (acc_holder.compare("END_OF_FILE") == 0) {
    cerr << "\n>>> ERROR: You may not withdraw funds from this account.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check format for the account number.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // Check if account holder's name and account number match.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Check if the account is disabled.
    if (transactions.is_Disabled(acc_num)) {
      cerr << "\n>>> ERROR: Disabled accounts may not withdraw funds.\n" << endl;
      return;

    // Check if the account has been created recently.
    } else if (transactions.is_New(acc_num)) {
      cerr << "\n>>> ERROR: Newly created accounts may not withdraw funds. Please try again in 24 hours.\n" << endl;
      return;
    }

    // Prompt and get company.
    cout << "Enter company: ";
    cin >> company;

    // Check if the company is valid.
    if (company.compare("EC") != 0 && company.compare("CQ") != 0 && company.compare("TV") != 0) {
      cerr << "\n>>> ERROR: The company name is invalid. Must be one of the following: EC, CQ or TV.\n" << endl;
      return;
    }

    // Prompt and get the amount to pay.
    cout << "Enter amount to pay: ";
    cin >> temp_amount;

    // Check if the format for amount is valid.
    if (transactions.is_Amount_Valid(temp_amount)) {
      amount = stof(temp_amount);
    } else {
      cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
      return;
    }

    // Pad with spaces to have proper format.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    padded_amount = temp_amount;
    while (padded_amount.length() < 8) {
      padded_amount = "0" + padded_amount;
    }

    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num) {

        // Check if not using recently deposited funds.
        if ((users.at(i).GetBalance() - users.at(i).GetDeposited()) < amount) {
          cerr << "\n>>> ERROR: You may not pay bills using recently deposited funds.\n" << endl;
          return;
        }

        // Check if user can pay the amount.
        if (amount <= users.at(i).GetBalance() && amount > 0.0) {
          new_balance = users.at(i).GetBalance() - amount;
          users.at(i).SetBalance(new_balance);
          break;
        } else {
          cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
          return;
        }
      }
    }

    // Set precision for balance to have a precision of 2.
    stream << fixed << setprecision(2) << new_balance;
    padded_new_balance = stream.str();
    while (padded_new_balance.length() < 8) {
      padded_new_balance = "0" + padded_new_balance;
    }
  
    // Notify user of success of bill being paid.
    cout << "\nYou have successfully paid a bill of " << padded_amount << " from account " << padded_acc_num << " to " << company << "." << endl;
    cout << "New balance: $" + padded_new_balance << endl;

    // Log paybill for transaction file.
    string transaction_line = "03 " + padded_acc_holder + " " + padded_acc_num + " " + padded_amount + " " + company;
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;

  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator implementation of deposit.
void Administrator::Deposit() {

  string padded_acc_holder;
  string padded_acc_num;
  string padded_amount;
  string padded_new_balance;
  string acc_holder;
  string temp_acc_num;
  string temp_amount;
  stringstream stream;
  float amount;
  float new_balance = 0.0;
  int acc_num;

  // Notify user that deposit transaction has been selected.
  cout << "\nDeposit transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Check if account holder exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;

  // Check if account holder's name is END_OF_FILE.
  } else if (acc_holder.compare("END_OF_FILE") == 0) {
    cerr << "\n>>> ERROR: You may not withdraw funds from this account.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check format of account number.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // check if account holder's name matches account number.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Check if account is disabled.
    if (transactions.is_Disabled(acc_num)) {
      cerr << "\n>>> ERROR: Disabled accounts may not deposit funds.\n" << endl;
      return;

    // check if account has been created on the current day.
    } else if (transactions.is_New(acc_num)) {
      cerr << "\n>>> ERROR: Newly created accounts may not deposit funds. Please try again in 24 hours.\n" << endl;
      return;
    }

    // Prompt and get amount to deposit.
    cout << "Enter amount to deposit: ";
    cin >> temp_amount;

    // Check if amount format is valid.
    if (transactions.is_Amount_Valid(temp_amount)) {
      amount = stof(temp_amount);
    } else {
      cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
      return;
    }

    // Pad with spaces to get correct format.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    padded_amount = temp_amount;
    while (padded_amount.length() < 8) {
      padded_amount = "0" + padded_amount;
    }

    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num) {

        // Check if amount is valid to deposit.
        if (((amount + users.at(i).GetBalance()) < 100000.00) && (amount > 0.0)) {
          new_balance = users.at(i).GetBalance() + amount;
          users.at(i).SetBalance(new_balance);
          users.at(i).SetDeposited(users.at(i).GetDeposited() + amount);
          break;
        } else {
          cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
          return;
        }
      }
    }

    // Set precision of balance to be 2.
    stream << fixed << setprecision(2) << new_balance;
    padded_new_balance = stream.str();
    while (padded_new_balance.length() < 8) {
      padded_new_balance = "0" + padded_new_balance;
    }
  
    // Notify user of success of deposit.
    cout << "\nFunds have been successfully added to the account " << padded_acc_num << "." << endl;
    cout << "New balance: $" + padded_new_balance << endl;

    // Log deposit for transaction file.
    string transaction_line = "01 " + padded_acc_holder + " " + padded_acc_num + " " + padded_amount + "   ";
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;

  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator create method.
void Administrator::Create() {

  string padded_acc_num;
  string padded_init_balance;
  string padded_new_name;
  string new_name;
  string init_balance;

  // Notify user that create transaction has been selected.
  cout << "\nCreate transaction selected.\n" << endl;
	
  // Prompt and get account holder's name.
  cout << "Enter new account holder's name: ";
  //cin >> new_name;
  cin.ignore();
  getline(cin, new_name);

  /* If the new account holder name enter happens to be longer
   * than 20 characters, truncate it to fit the requirements
   */
  if (new_name.length() > 20) {
    new_name = new_name.substr(0, 20);
    cout << "The new account holder's name has been truncated to: " << new_name << endl;
  }

  padded_new_name = new_name;
  while (padded_new_name.length() < 20) {
    padded_new_name = padded_new_name + " ";
  }

  /* If the name does not exist (e.g. is unique) then 
   * check if it fits the format required
   */
  if (!(transactions.HolderExists(new_name)) && (new_name.compare("admin") != 0) && (transactions.is_Name_Valid(new_name))) {
    // Get the last element from vector users

    int last_acc_num;
    
    for (int i = 0; i < users.size(); i++) {
      if (i == users.size() - 3) {
        last_acc_num = users.at(i).GetNum();
      }
    }

    // Assigns the next number in the sequence
    int new_acc_num = last_acc_num + 1;

    if (new_acc_num > 99998) {
      cerr << "There are no more bank account numbers available." << endl;
      return;
    } else {
      // Prompt for initial balance and check it's valid
      // Then create new User and add it to the users vector
      cout << "Enter initial balance: ";
      cin >> init_balance;

      // Pad to get proper format.
      padded_init_balance = init_balance;
      while (padded_init_balance.length() < 8) {
        padded_init_balance = "0" + padded_init_balance;
      }

      padded_acc_num = to_string(new_acc_num);
      while (padded_acc_num.length() < 5) {
        padded_acc_num = "0" + padded_acc_num;
      }

      // Check if the initial balance is valid.
      if (!(transactions.is_Amount_Valid(init_balance))) {
        cerr << ">>> ERROR: The initial balance entered is not valid." << endl;
        return;
      }

      // Create the new user.
      Standard new_user;
      new_user.SetName(new_name);
      new_user.SetNum(new_acc_num);
      new_user.SetBalance(stof(init_balance));
      new_user.SetStatus('A');
      new_user.SetPlan('N');
      users.push_back(new_user);
      new_users.push_back(new_user);

      // Notify of success of creating account and display balance number and balance.
      cout << "\nYou have successfully created a new account." << endl;
      cout << "Bank account number: " << padded_acc_num << endl;
      cout << "Balance: $" << padded_init_balance << endl;

      // Print out transaction payment plan.
      if (new_user.GetPlan() == 'S')
        cout << "Transaction payment plan: Student" << endl;
      else if (new_user.GetPlan() == 'N')
        cout << "Transaction payment plan: Non-student" << endl;
      else 
        cerr << ">>> ERROR: Could not get payment plan information." << endl;     
      
      // Print out account status.
      if (new_user.GetStatus() == 'D')
        cout << "Status: Disabled" << endl;
      else if (new_user.GetStatus() == 'A')
        cout << "Status: Active" << endl;
      else
        cerr << ">>> ERROR: Could not get status information." << endl;

      cout << "\nEnter a command.\n" << endl;

      // Log create for transaction file.
      string transaction_line = "04 " + padded_new_name + " " + padded_acc_num + " " + padded_init_balance + "   ";
      transaction_file.push_back(transaction_line);
    }
  } else {
    cerr << ">>> ERROR: The account name entered is already in use. Please pick a different one." << endl;
  }
}

// Administrator delete method.
void Administrator::Deleted() {

  string padded_acc_holder;
  string padded_acc_num;
  string acc_holder;
  string temp_acc_num;
  int acc_num;
  string choice;

  // Notify user that delete transaction has been selected.
  cout << "\nDelete transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Check if account holder already exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check account number format.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // check if account holder's name matches account number.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Pad to get proper format.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    // Vertify to delete the account.
    cout << "Are you sure you want to delete " << acc_holder << "'s account " << padded_acc_num << " (yes/no)? ";
    cin >> choice;

    // Check choice.
    if (transactions.to_Lower(choice).compare("yes") == 0) {
      for (int i = 0; i < users.size(); i++) {
        if (users.at(i).GetNum() == acc_num) {
          users.erase(users.begin() + i);
          break;
        }
      }
      
      // Notify user of success of deletion of the account.
      cout << "\nThe account " << padded_acc_num << " has successfully been deleted." << endl;

      // Log delete for transaction file.
      string transaction_line = "06 " + padded_acc_holder + " " + padded_acc_num + "            ";
      transaction_file.push_back(transaction_line);
      cout << "\nEnter a command.\n" << endl;
    }

    else if (transactions.to_Lower(choice).compare("no") == 0) {
      // Notify user of abort of deletion of the account.
      cout << "\nThe deletion of account " << acc_num << " has been aborted." << endl;
      cout << "\nEnter a command.\n" << endl;
    } else
      cerr << "\n>>> ERROR: This is not a valid input.\n" << endl;

  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator disable method.
void Administrator::Disable() {

  string padded_acc_holder;
  string padded_acc_num;
  string acc_holder;
  string temp_acc_num;
  int acc_num;

  // Notify user that disable transaction has been selected.
  cout << "\nDisable transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Check if account holder exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check format of account number.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // Check if account holder's name matches account number.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Pad to get proper format.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num) {

        // Check if account is already disabled.
        if (transactions.is_Disabled(acc_num)) {
          cerr << "\n>>> ERROR: This account is already disabled.\n" << endl;
          return;
        } else {
          // Disable the account.
          users.at(i).SetStatus('D');
          break;
        }
      }
    }
    // Notify success of account disable.
    cout << "\nThe account " << padded_acc_num << " has successfully been disabled." << endl;

    // Log disable for transaction file.
    string transaction_line = "07 " + padded_acc_holder + " " + padded_acc_num + "            ";
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;
    
  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator enable method.
void Administrator::Enable() {

  string padded_acc_holder;
  string padded_acc_num;
  string acc_holder;
  string temp_acc_num;
  int acc_num;

  // Notify user that enable transaction has been selected.
  cout << "\nEnable transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Check if account exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check format of account number.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // Check if account holder's name matches account number.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Pad to get proper format.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num) {

        // Check if account is already enabled.
        if (!transactions.is_Disabled(acc_num)) {
          cerr << "\n>>> ERROR: This account is already enabled.\n" << endl;
          return;
        } else {
          // Enable the account.
          users.at(i).SetStatus('A');
          break;
        }
      }
    }

    // Notify success of account enable.
    cout << "\nThe account " << padded_acc_num << " has successfully been enabled." << endl;

    // Log enable for transaction file.
    string transaction_line = "09 " + padded_acc_holder + " " + padded_acc_num + "            ";
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;
    
  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}

// Administrator changeplan method.
void Administrator::Changeplan() {

  string new_plan;
  string padded_acc_holder;
  string padded_acc_num;
  string acc_holder;
  string temp_acc_num;
  int acc_num;

  // Notify user that change plan transaction has been selected.
  cout << "\nChange plan transaction selected.\n" << endl;

  // Prompt and get account holder's name.
  cout << "Enter account holder's name: ";
  cin >> acc_holder;

  // Check if account exists.
  if (!transactions.HolderExists(acc_holder)) {
    cerr << "\n>>> ERROR: The account holder name entered is not valid.\n" << endl;
    return;
  }

  // Prompt and get account number.
  cout << "Enter account number: ";
  cin >> temp_acc_num;

  // Check format of account number.
  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  // Check if account holder's name matches account number.
  if (transactions.Matches(acc_holder, acc_num)) {

    // Check if account is disabled.
    if (transactions.is_Disabled(acc_num)) {
      cerr << "\n>>> ERROR: Disabled accounts can not change transaction payment plans.\n" << endl;
      return;
    }

    // Pad to get proper format.
    padded_acc_holder = acc_holder;
    while (padded_acc_holder.length() < 20) {
      padded_acc_holder = padded_acc_holder + " ";
    }

    padded_acc_num = temp_acc_num;
    while (padded_acc_num.length() < 5) {
      padded_acc_num = "0" + padded_acc_num;
    }

    // Switch the account's transaction payment plan.
    for (int i = 0; i < users.size(); i++) {
      if (users.at(i).GetNum() == acc_num) {
        if (users.at(i).GetPlan() == 'S') {
          users.at(i).SetPlan('N');
          new_plan = "Non-student";
        } else {
          users.at(i).SetPlan('S');
          new_plan = "Student";
        }
      }
    }

    // Notify success of change of account transaction payment plan.
    cout << "\nThe transaction payment plan for account " << padded_acc_num << " has successfully changed to " << new_plan << "."<< endl;

    // Log change plan for transaction file.
    string transaction_line = "08 " + padded_acc_holder + " " + padded_acc_num + "            ";
    transaction_file.push_back(transaction_line);
    cout << "\nEnter a command.\n" << endl;
    
  } else {
      cerr << "\n>>> ERROR: The account number entered does not match the account holder name.\n" << endl;
  }
}