#include "BankDatabase.h"

#include "BankAccount.h"
#include "Debug.h"

const string BankDatabase::FILENAME = "bank.txt";

BankDatabase::BankDatabase() {
  readFromDisk();
}

BankDatabase::~BankDatabase() {
  writeToDisk();
}

BankAccountReadOnly* BankDatabase::createAccount(int ownerId) {
  BankAccount* bankAccount = new BankAccount(++lastBankAccountId, ownerId);
  bankAccounts.push_back(bankAccount);

  Debug::Log("[BankDatabase] Created account with id %d for ownerId %d", bankAccount->getId(), ownerId);

  return bankAccount;
}

vector<BankAccountReadOnly*> BankDatabase::getAccounts(int ownerId) {
  vector<BankAccountReadOnly*> bankAccounts;

  for (BankAccount* bankAccount : this->bankAccounts)
    if (bankAccount->getOwnerId() == ownerId)
      bankAccounts.push_back(bankAccount);

  return bankAccounts;
}

bool BankDatabase::deleteAccount(int ownerId, int accountId) {
  Debug::Log("[BankDatabase] Trying to delete account with id %d", accountId);

  unsigned int index;

  index = 0;
  while (index < bankAccounts.size() && bankAccounts[index]->getId() != accountId)
    ++index;

  if (index < bankAccounts.size() && ownerId == bankAccounts[index]->getOwnerId()) {
    delete bankAccounts[index];
    bankAccounts.erase(bankAccounts.begin() + index);

    Debug::Log("[BankDatabase] Successfully deleted account with id %d", accountId);
    return true;
  }

  Debug::Log("[BankDatabase] Failed to delete account with id %d", accountId);
  return false;
}

bool BankDatabase::deposit(BankAccountReadOnly* bankAccount, int value) {
  ((BankAccount*)bankAccount)->deposit(value);
  Debug::Log("[BankDatabase] Successfully deposited %d in account with id %d", value, bankAccount->getId());
  return true;
}

bool BankDatabase::withdraw(BankAccountReadOnly* bankAccount, int value) {
  if (((BankAccount*)bankAccount)->withdraw(value)) {
    Debug::Log("[BankDatabase] Successfully withdrawn %d from account with id %d", value, bankAccount->getId());
    return true;
  }
  Debug::Log("[BankDatabase] Failed to withdraw %d from accout with id %d", value, bankAccount->getId());
  return false;
}

void BankDatabase::readFromDisk() {
  ifstream fin(FILENAME);

  lastBankAccountId = 0;

  string line;
  BankAccount* bankAccount;
  while (getline(fin, line))
    if (line.size() > 0) {
      bankAccount = new BankAccount();
      bankAccount->deserialize(line);
      bankAccounts.push_back(bankAccount);

      lastBankAccountId = max(lastBankAccountId, bankAccount->getId());
    }

  fin.close();

  Debug::Log("[BankDatabase] Read %d accounts from database.", bankAccounts.size());
}

void BankDatabase::writeToDisk() {
  ofstream fout(FILENAME);

  for (BankAccount*& bankAccount : bankAccounts) {
    fout << bankAccount->serialize() << '\n';
    delete bankAccount;
  }

  fout.close();

  Debug::Log("[BankDatabase] Saved %d accounts to database.", bankAccounts.size());
}
