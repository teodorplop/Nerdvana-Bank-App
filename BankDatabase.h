#pragma once

#include "includes.h"

class BankAccountReadOnly;
class BankAccount;

class BankDatabase {
private:
  static const string FILENAME;

  vector<BankAccount*> bankAccounts;
  int lastBankAccountId;

  void readFromDisk();
  void writeToDisk();

public:
  BankDatabase();
  ~BankDatabase();

  BankAccountReadOnly* createAccount(int ownerId);

  vector<BankAccountReadOnly*> getAccounts(int ownerId);

  bool deleteAccount(int ownerId, int accountId);

  bool deposit(BankAccountReadOnly* bankAccount, int value);
  bool withdraw(BankAccountReadOnly* bankAccount, int value);
};
