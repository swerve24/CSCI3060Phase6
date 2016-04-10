/* This software is the front-end design of the Watermelon Banking System.
 * It is to be ran as a console application.
 * Input(s): Command line and file input
 * Output(s): Command line prompts and file output.
 *
 * main.cpp
 *
 * Authors: Denesh Parthipan, Luisa Rojas, Truyen Truong
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TransactionHelper.h"
#include "Standard.h"
#include "Administrator.h"

using namespace std;

/* These class objects will be used to refence
 * the different methods as needed.
 */
Standard s;
Administrator a;

/* Second declaration of external global variables.
 * Needed in order to access and edit them from any
 * class.
 */
Standard curr_user;
vector<Standard> users;
vector<Standard> new_users;
vector<string> transaction_file;
string mode;
string acc_holder;
bool is_logged;
TransactionHelper transactions;

int main (int argc, char *argv[]) {

  string file_name;
  string command;
  is_logged = false;

  // For command line input only
  if (argc >= 2) {

    //system("rm transaction_file_*.tra");

    file_name = argv[1];

    transactions.LoadAccounts(file_name);
    cout << "File name: " << file_name << "." << endl;
    transactions.PrintWelcomeMessage();

    // Permanently listening for commands
    while(true) {
      cin >> command;

      // If command is LOGIN
      if (transactions.to_Lower(command).compare("login") == 0)
        transactions.Login();

      // If command is LOGOUT
      else if (transactions.to_Lower(command).compare("logout") == 0)
        transactions.Logout();

      // If command is CREATE (Privileged)
      else if (transactions.to_Lower(command).compare("create") == 0)
        if (is_logged) {
          if (transactions.is_Admin())
            a.Create();
          else
            cerr << "\n>>> ERROR: You need to be an administrator to create a new account.\n" << endl;
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is DELETE (Privileged)
      else if (transactions.to_Lower(command).compare("delete") == 0) {
        if (is_logged) {
          if (transactions.is_Admin())
            a.Deleted();
          else
            cerr << "\n>>> ERROR: You need to be an administrator to delete an account.\n" << endl;
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is DISABLE (Privileged)
      } else if (transactions.to_Lower(command).compare("disable") == 0) {
        if (is_logged) {
          if (transactions.is_Admin())
            a.Disable();
          else
            cerr << "\n>>> ERROR: You need to be an administrator to disable an account.\n" << endl;
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is ENABLE (Privileged)
      } else if (transactions.to_Lower(command).compare("enable") == 0) {
        if (is_logged) {
          if (transactions.is_Admin())
            a.Enable();
          else
            cerr << "\n>>> ERROR: You need to be an administrator to enable an account.\n" << endl;
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is DEPOSIT
      } else if (transactions.to_Lower(command).compare("deposit") == 0) {
        if (is_logged) {
          if (transactions.is_Admin()) {
            a.Deposit();
          } else {
            s.Deposit();
          }
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is WITHDRAWAL
      } else if (transactions.to_Lower(command).compare("withdrawal") == 0) {
        if (is_logged) {
          if (transactions.is_Admin()) {
            a.Withdrawal();
          } else {
            s.Withdrawal();
          }
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is TRANSFER
      } else if (transactions.to_Lower(command).compare("transfer") == 0) {
        if (is_logged) {
          if (transactions.is_Admin()) {
            a.Transfer();
          } else {
            s.Transfer();
          }
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is PAYBILL
      } else if (transactions.to_Lower(command).compare("paybill") == 0) {
        if (is_logged) {
          if (transactions.is_Admin()) {
            a.Paybill();
          } else {
            s.Paybill();
          }
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is CHANGEPLAN
      } else if (transactions.to_Lower(command).compare("changeplan") == 0) {
        if (is_logged) {
          if (transactions.is_Admin())
            a.Changeplan();
          else
            cerr << "\n>>> ERROR: You need to be an administrator to change the plan of an account.\n" << endl;
        } else
          cerr << "\n>>> ERROR: Must be logged in before invoking any other commands.\n" << endl;

      // If command is HELP
      } else if (transactions.to_Lower(command).compare("help") == 0) {
        transactions.PrintHelp();

      // If command is QUIT
      } else if (transactions.to_Lower(command).compare("quit") == 0) {
        if (!is_logged)
          return 0;
        else
          cout << ">>> ERROR: You may not quit while logged in." << endl;
      } else {
        cerr << "\n>>> ERROR: Invalid command.\n" << endl;
      }
    }
  } else {
    cerr << "\n>>> ERROR: Please enter an argument for current users.\n" << endl;
    return -1;
  }
}
