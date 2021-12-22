#include "MainScreen.h"

#include "ScreenStack.h"

#include "User.h"

#include "BankAccountReadOnly.h"
#include "BankDatabase.h"

const int MainScreen::MIN_VALUE = 5;
const int MainScreen::MAX_VALUE = 1000;

MainScreen::MainScreen(BankDatabase* bankDb, User* user) :
  Screen("MainScreen", {"Create new account", "Delete account", "Deposit", "Withdraw", "Logout", "Exit"}) {
  this->bankDb = bankDb;
  this->user = user;
}

void MainScreen::showInternal() {
  bankAccounts = bankDb->getAccounts(user->getId());
  cout << "Number of accounts: " << bankAccounts.size() << '\n';
  cout << LINE;

  for (BankAccountReadOnly* bankAccount : bankAccounts)
    cout << "Account " << bankAccount->getId() << ": " << bankAccount->getBalance() << '\n';
}

void MainScreen::handleUserAction(const string& action) {
  if (action == "Create new account")
    createAccount();
  else if (action == "Delete account")
    deleteAccount();
  else if (action == "Deposit")
    deposit();
  else if (action == "Withdraw")
    withdraw();
  else if (action == "Logout")
    logout();
  else if (action == "Exit")
    exit();
}

void MainScreen::createAccount() {
  bankDb->createAccount(user->getId());
  refresh();
}

void MainScreen::deleteAccount() {
  if (bankDb->deleteAccount(user->getId(), waitForAccountId()))
    refresh();
  else
    cout << "Failed to delete account\n";
}

void MainScreen::deposit() {
  BankAccountReadOnly* bankAccount = getBankAccount(waitForAccountId());
  if (bankAccount != NULL) {
    if (bankDb->deposit(bankAccount, waitForValue()))
      refresh();
    else
      cout << "Failed to deposit\n";
  } else
    cout << "Invalid bank account\n";
}

void MainScreen::withdraw() {
  BankAccountReadOnly* bankAccount = getBankAccount(waitForAccountId());
  int minValue, maxValue;
  if (bankAccount != NULL) {
    minValue = MIN_VALUE;
    maxValue = bankAccount->getBalance();

    if (bankDb->withdraw(bankAccount, waitForValue(minValue, maxValue)))
      refresh();
    else
      cout << "Failed to withdraw\n";
  } else
    cout << "Invalid bank account\n";
}

void MainScreen::logout() {
  ScreenStack::getInstance()->pop();
}

BankAccountReadOnly* MainScreen::getBankAccount(int accountId) {
  unsigned int index;

  index = 0;
  while (index < bankAccounts.size() && bankAccounts[index]->getId() != accountId)
    ++index;

  return index < bankAccounts.size() ? bankAccounts[index] : NULL;
}

int MainScreen::waitForAccountId() {
  int accountId;

  cout << "Insert account id: ";
  cin >> accountId;
  cin.get();

  return accountId;
}

int MainScreen::waitForValue(int minValue, int maxValue) {
  if (minValue > maxValue)
    minValue = maxValue;

  int value;

  cout << "Insert value (min = " << minValue << ", max = " << maxValue << "): ";
  cin >> value;
  cin.get();

  value = clamp(value, minValue, maxValue);

  return value;
}
