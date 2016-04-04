 /* 
 * Standard.cpp
 * 
 * Authors: Denesh Parthipan, Luisa Rojas, Truyen Truong
 */

#include "Standard.h"

void Standard::Withdrawal() {

  string padded_acc_holder;
  string padded_acc_num;
  string padded_amount;
  string padded_new_balance;
  string temp_acc_num;
  string temp_amount;
  stringstream stream;
  float amount;
  float new_balance;
  int acc_num;

  cout << "\nWithdrawal transaction selected.\n" << endl;

  cout << "Enter your account number: ";
  cin >> temp_acc_num;

  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  if (curr_user.GetNum() != acc_num) {
    cerr << "\n>>> ERROR: The account number does not match your account.\n" << endl;
    return;
  }

  if (transactions.is_Disabled(curr_user.GetNum())) {
      cerr << "\n>>> ERROR: The account is disabled; you may not withdraw funds.\n" << endl;
      return;
  }

  if (transactions.is_New(curr_user.GetNum())) {
    cerr << "\n>>> ERROR: Newly created accounts may not withdraw funds. Please try again in 24 hours.\n" << endl;
    return;
  }

  cout << "Enter amount to withdraw: ";
  cin >> temp_amount;

  if (transactions.is_Amount_Valid(temp_amount)) {
    amount = stof(temp_amount);
  } else {
    cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
    return;
  }

  if (curr_user.GetPlan() == 'S') {
    if (amount <= 0.05 + curr_user.GetBalance() && (500.00 >= amount > 0.0) && (fmod(amount, 5.0) == 0)) {

      new_balance = curr_user.GetBalance() - amount;
      curr_user.SetBalance(new_balance);
  
    } else {
      cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
      return;
    }

    if ((curr_user.GetBalance() - 0.05 - curr_user.GetDeposited()) < amount) {
      cerr << "\n>>> ERROR: You may not withdraw recently deposited funds.\n" << endl;
      return;
    }
  } else if (curr_user.GetPlan() == 'N') {
    if (amount <= 0.10 + curr_user.GetBalance() && (500.00 >= amount > 0.0) && (fmod(amount, 5.0) == 0)) {

      new_balance = curr_user.GetBalance() - amount;
      curr_user.SetBalance(new_balance);
  
    } else {
      cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
      return;
    }

    if ((curr_user.GetBalance() - 0.10 - curr_user.GetDeposited()) < amount) {
      cerr << "\n>>> ERROR: You may not withdraw recently deposited funds.\n" << endl;
      return;
    }
  } else {
    cerr << "\n>>> ERROR: Unable to retrieve transaction payment plan information.\n" << endl;
    return;
  }

  padded_acc_holder = curr_user.GetName();
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

  stream << fixed << setprecision(2) << new_balance;
  padded_new_balance = stream.str();
  while (padded_new_balance.length() < 8) {
    padded_new_balance = "0" + padded_new_balance;
  }

  cout << "\nFunds have been successfully withdrawn from your account." << endl;
  cout << "New balance: $" + padded_new_balance << endl;

  string transaction_line = "01 " + padded_acc_holder + " " + padded_acc_num + " " + padded_amount + "   ";
  cout << "Transaction line: " << transaction_line << endl;
  transaction_file.push_back(transaction_line);
  cout << "\nEnter a command.\n" << endl;
}

void Standard::Transfer() {

  string padded_acc_holder_f;
  string padded_acc_holder_t;
  string padded_acc_num_f;
  string padded_acc_num_t;
  string padded_amount;
  string padded_new_balance_f;
  string padded_new_balance_t;
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

  cout << "\nTransfer transaction selected.\n" << endl;

  cout << "Enter you account number: ";
  cin >> temp_acc_num_f;

  regex re_f("[0-9]{0,5}");
  if (regex_match(temp_acc_num_f, re_f) && temp_acc_num_f.compare("99999") != 0) {
    acc_num_f = stoi(temp_acc_num_f);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  if (curr_user.GetNum() != acc_num_f) {
    cerr << "\n>>> ERROR: The account number does not match your account.\n" << endl;
    cout << "Current user: " << curr_user.GetNum() << ", Account Number: " << acc_num_f << endl;
    return;
  }

  if (transactions.is_Disabled(curr_user.GetNum())) {
    cerr << "\n>>> ERROR: The account is disabled; you may not send funds.\n" << endl;
    return;
  }
    
  if (transactions.is_New(curr_user.GetNum())) {
      cerr << "\n>>> ERROR: Newly created accounts may not send funds. Please try again in 24 hours.\n" << endl;
      return;
  }

  cout << "Enter destination account number: ";
  cin >> temp_acc_num_t;

  regex re_t("[0-9]{0,5}");
  if (regex_match(temp_acc_num_t, re_t) && temp_acc_num_t.compare("99999") != 0) {
    acc_num_t = stoi(temp_acc_num_t);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  if (!transactions.NumExists(acc_num_t)) {
    cerr << "\n >>> ERROR: The destination account number entered is invalid.\n" << endl;
    return;
  }

  if (transactions.is_Disabled(acc_num_t)) {
    cerr << "\n>>> ERROR: Disabled accounts may not receive funds.\n" << endl;
    return;
  }

  cout << "Enter amount to transfer: ";
  cin >> temp_amount;

  if (transactions.is_Amount_Valid(temp_amount)) {
    amount = stof(temp_amount);
  } else {
    cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
    return;
  }

  for (int i = 0; i < users.size(); i++) {
    if (users.at(i).GetNum() == acc_num_t) {
      acc_holder_t = users.at(i).GetName();
    }
  }

  padded_acc_holder_f = curr_user.GetName();
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

  if ((curr_user.GetBalance() - curr_user.GetDeposited()) < amount) {
    cerr << "\n>>> ERROR: You may not transfer recently deposited funds.\n" << endl;
    return;
  }


  if (curr_user.GetPlan() == 'S') {
    // STUFF HERE
  } else if (curr_user.GetPlan() == 'N') {
    // STUFF HERE
  } else {
    cerr << "\n>>> ERROR: Unable to retrieve transaction payment plan information.\n" << endl;
    return;
  }

  for (int i = 0; i < users.size(); i++) {
    if (users.at(i).GetNum() == acc_num_t) {

      if (amount <= curr_user.GetBalance() && (1000.00 >= amount > 0.0) && (amount + users.at(i).GetBalance()) < 100000.00) {

        /*
        * Done in the Back End
        * 
        if (curr_user.GetPlan() == 'S')
          new_balance_f = curr_user.GetBalance() - amount - 0.05;
        else if (curr_user.GetPlan() == 'N')
          new_balance_f = curr_user.GetBalance() - amount - 0.10;
        else {
          cerr << "\n>>> ERROR: Unable to retrieve transaction payment plan information.\n" << endl;
          return;
        }
        */
        new_balance_f = curr_user.GetBalance() - amount;
        new_balance_t = users.at(i).GetBalance() + amount;
        curr_user.SetBalance(new_balance_f);
        users.at(i).SetBalance(new_balance_t);
        users.at(i).SetDeposited(users.at(i).GetDeposited() + amount);
        break;

      } else {
        cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
        return;
      }
    }
  }

  stream << fixed << setprecision(2) << new_balance_f;
  padded_new_balance_f = stream.str();
  while (padded_new_balance_f.length() < 8) {
    padded_new_balance_f = "0" + padded_new_balance_f;
  }

  cout << "\nFunds have been successfully transfered from account " << padded_acc_num_f << " to account " << padded_acc_num_t << "." << endl;
  cout << "New balance: $" + padded_new_balance_f << endl;

  string transaction_line = "02 " + padded_acc_holder_f + " " + padded_acc_num_f + " " + padded_amount + "   ";
  transaction_file.push_back(transaction_line);
  transaction_line = "02 " + padded_acc_holder_t + " " + padded_acc_num_t + " " + padded_amount + "   ";
  transaction_file.push_back(transaction_line);
  cout << "\nEnter a command.\n" << endl;
}

void Standard::Paybill() {

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
  float new_balance;
  float company_count;
  int acc_num;

  cout << "\nPay bill transaction selected.\n" << endl;

  cout << "Enter your account number: ";
  cin >> temp_acc_num;

  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re)) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  if (curr_user.GetNum() != acc_num) {
    cerr << "\n>>> ERROR: The account number does not match your account.\n" << endl;
    return;
  }

  if (transactions.is_Disabled(curr_user.GetNum())) {
    cerr << "\n>>> ERROR: The account is disabled; you may not send funds.\n" << endl;
    return;
  }
    
  if (transactions.is_New(curr_user.GetNum())) {
      cerr << "\n>>> ERROR: Newly created accounts may not send funds. Please try again in 24 hours.\n" << endl;
      return;
  }

  cout << "Enter company: ";
  cin >> company;
  company = transactions.to_Lower(company);

  if (company.compare("EC") != 0 || company.compare("CQ") != 0 || company.compare("TV") != 0) {
    cerr << "\n>>> ERROR: The company name is invalid. Must be one of the following: EC, CQ or TV.\n" << endl;
    return;
  }

  cout << "Enter amount to pay: ";
  cin >> temp_amount;

  if (transactions.is_Amount_Valid(temp_amount)) {
    amount = stof(temp_amount);
  } else {
    cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
    return;
  }

  if ((curr_user.GetBalance() - curr_user.GetDeposited()) < amount) {
    cerr << "\n>>> ERROR: You may not pay bills using recently deposited funds.\n" << endl;
    return;
  }

  if (company.compare("EC") == 0) {
    company_count = curr_user.GetECCount() + amount;
    if (company_count > 2000.00) {
      cerr << "\n>>> ERROR: The limit to pay per company per day is $2000.00.\n" << endl;
      return;
    }
    curr_user.SetECCount(company_count);
  } else if (company.compare("TV") == 0) {
    company_count = curr_user.GetTVCount() + amount;
    if (company_count > 2000.00) {
      cerr << "\n>>> ERROR: The limit to pay per company per day is $2000.00.\n" << endl;
      return;
    }
    curr_user.SetTVCount(company_count);
  } else {
    company_count = curr_user.GetCQCount() + amount;
    if (company_count > 2000.00) {
      cerr << "\n>>> ERROR: The limit to pay per company per day is $2000.00.\n" << endl;
      return;
    }
    curr_user.SetCQCount(company_count);
  }

  if (amount <= curr_user.GetBalance() && amount > 0.0) {

   /*
    * Done in the Back End
    * 
    if (curr_user.GetPlan() == 'S')
      new_balance = curr_user.GetBalance() - amount - 0.05;
    else if (curr_user.GetPlan() == 'N')
      new_balance = curr_user.GetBalance() - amount - 0.10;
    else {
      cerr << "\n>>> ERROR: Unable to retrieve transaction payment plan information.\n" << endl;
      return;
    }
    */

    new_balance = curr_user.GetBalance() - amount;
    curr_user.SetBalance(new_balance);
  } else {
    cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
    return;
  }

  padded_acc_holder = curr_user.GetName();
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

  stream << fixed << setprecision(2) << new_balance;
  padded_new_balance = stream.str();
  while (padded_new_balance.length() < 8) {
    padded_new_balance = "0" + padded_new_balance;
  }

  cout << "\nYou have successfully paid a bill of " << padded_amount << " from account " << padded_acc_num << " to " << company << "." << endl;
  cout << "New balance: $" + padded_new_balance << endl;

  string transaction_line = "03 " + padded_acc_holder + " " + padded_acc_num + " " + padded_amount + " " + company;
  transaction_file.push_back(transaction_line);
  cout << "\nEnter a command.\n" << endl;
}

void Standard::Deposit() {

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

  cout << "\nDeposit transaction selected.\n" << endl;

  cout << "Enter account number: ";
  cin >> temp_acc_num;

  regex re("[0-9]{0,5}");
  if (regex_match(temp_acc_num, re) && temp_acc_num.compare("99999") != 0) {
    acc_num = stoi(temp_acc_num);
  } else {
    cerr << "\n>>> ERROR: The account number entered is invalid.\n" << endl;
    return;
  }

  if (curr_user.GetNum() != acc_num) {
    cerr << "\n>>> ERROR: The account number does not match your account.\n" << endl;
    return;
  }

  if (transactions.is_Disabled(curr_user.GetNum())) {
    cerr << "\n>>> ERROR: The account is disabled; you may not send funds.\n" << endl;
    return;
  }
    
  if (transactions.is_New(curr_user.GetNum())) {
      cerr << "\n>>> ERROR: Newly created accounts may not send funds. Please try again in 24 hours.\n" << endl;
      return;
  }

  cout << "Enter amount to deposit: ";
  cin >> temp_amount;

  if (transactions.is_Amount_Valid(temp_amount)) {
    amount = stof(temp_amount);
  } else {
    cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
    return;
  }

  if (((amount + curr_user.GetBalance()) < 100000.00) && (amount > 0.0)) {

    /*
    * Done in the Back End
    *
    if (curr_user.GetPlan() == 'S')
      new_balance = curr_user.GetBalance() + amount - 0.05;
    else if (curr_user.GetPlan() == 'N')
      new_balance = curr_user.GetBalance() + amount - 0.10;
    else {
      cerr << "\n>>> ERROR: Unable to retrieve transaction payment plan information.\n" << endl;
      return;
    }
    */

    new_balance = curr_user.GetBalance() + amount;
    curr_user.SetBalance(new_balance);
    curr_user.SetDeposited(curr_user.GetDeposited() + amount);
    
  } else {
    cerr << "\n>>> ERROR: The amount entered is invalid.\n" << endl;
    return;
  }

  padded_acc_holder = curr_user.GetName();
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

  stream << fixed << setprecision(2) << new_balance;
  padded_new_balance = stream.str();
  while (padded_new_balance.length() < 8) {
    padded_new_balance = "0" + padded_new_balance;
  }

  cout << "\nFunds have been successfully added to the account " << padded_acc_num << "." << endl;
  cout << "New balance: $" + padded_new_balance << endl;

  string transaction_line = "04 " + padded_acc_holder + " " + padded_acc_num + " " + padded_amount + "   ";
  transaction_file.push_back(transaction_line);
  cout << "\nEnter a command.\n" << endl;

}