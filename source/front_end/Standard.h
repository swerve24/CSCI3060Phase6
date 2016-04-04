/* 
 * Standard.h
 * 
 * Authors: Denesh Parthipan, Luisa Rojas, Truyen Truong
 */

#ifndef STANDARD_H
#define STANDARD_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <regex>
#include <math.h>
#include "IAccount.h"
#include "TransactionHelper.h"

/*
 * Standard is for standard accounts. Has variables for the current
 * standard account. Has functions to access the current standard account's
 * data. Has implementations of the transaction functions.
 */
class Standard: public virtual IAccount {

 private:
  string acc_holder_;
  int acc_num_;
  float acc_balance_;
  float acc_newly_deposited_;
  char acc_status_;
  char acc_plan_;
  float EC_count_;
  float CQ_count_;
  float TV_count_;

 public:
  Standard() {};
  //	Standard(int acc_num, float acc_balance, char acc_status, char acc_plan);
  ~Standard() {}
		
  // Get account holder name.
  string GetName() {return acc_holder_;}
  // Get the account number.
  int GetNum() {return acc_num_;}
  // Get the account balance.
  float GetBalance() {return acc_balance_;}
  // Get the account status.
  char GetStatus() {return acc_status_;}
  // Get the account plan.
  char GetPlan() {return acc_plan_;}
  // Get the funds that were deposited in this day
  float GetDeposited() {return acc_newly_deposited_;}
  // Keep track of the limit of payments per company
  float GetECCount() {return EC_count_;}
  float GetCQCount() {return CQ_count_;}
  float GetTVCount() {return TV_count_;}

  // Set account holder name.
  void SetName(string name) {acc_holder_ = name;}
  // Change the account number.
  void SetNum(int num) {acc_num_ = num;}
  // Change the account balance.
  void SetBalance(float balance) {acc_balance_ = balance;}
  // Change the account status.
  void SetStatus(char status) {acc_status_ = status;}
  // Change the account plan.
  void SetPlan(char plan) {acc_plan_ = plan;}
  // Change the value for recently deposited funds
  void SetDeposited(float deposited) {acc_newly_deposited_ = deposited;}
  // Keep track of the limit of payments per company
  void SetECCount(float amount) {EC_count_ = amount;}
  void SetCQCount(float amount) {CQ_count_ = amount;}
  void SetTVCount(float amount) {TV_count_ = amount;}

  // void login(string acc_holder);
  // Withdraw from the current user account.
  void Withdrawal();
  // Transfer from the current user account to another user account.
  void Transfer();
  // Pay a bill to a company from the current user account.
  void Paybill();
  // Deposit money into the current user account.
  void Deposit();
  //	bool logout();
};

#endif