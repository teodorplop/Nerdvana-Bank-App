#pragma once

#include "Screen.h"

class User;
class BankDatabase;
class BankAccountReadOnly;

class MainScreen : public Screen {
private:
  static const int MIN_VALUE;
  static const int MAX_VALUE;

  BankDatabase* bankDb;
  User* user;

  vector<BankAccountReadOnly*> bankAccounts;

  void createAccount();
  void deleteAccount();
  void deposit();
  void withdraw();
  void logout();

  BankAccountReadOnly* getBankAccount(int accountId);
  int waitForAccountId();
  int waitForValue(int minValue = MIN_VALUE, int maxValue = MAX_VALUE);

protected:
  void showInternal();
  void handleUserAction(const string& action);

public:
  MainScreen(BankDatabase* bankDb, User* user);
};
