#include "BankAccount.h"

#include "Debug.h"

BankAccount::BankAccount(int id) {
  this->id = id;
  balance = 0;
}

BankAccount::BankAccount(int id, int ownerId) : BankAccount(id) {
  this->ownerId = ownerId;
}

void BankAccount::deposit(int value) {
  balance += value;
  Debug::Log("[BankAccount] Deposited %d into account with id %d", value, id);
}

bool BankAccount::withdraw(int value) {
  if (balance >= value) {
    Debug::Log("[BankAccount] Successfully withdrawn %d from account with id %d", value, id);

    balance -= value;
    return true;
  }

  Debug::Log("[BankAccount] Failed to withdraw %d from account with id %d", value, id);

  return false;
}

string BankAccount::serialize() {
  stringstream stream;
  stream << id << ' ' << ownerId << ' ' << balance;
  return stream.str();
}

void BankAccount::deserialize(const string& text) {
  istringstream stream(text);
  stream >> id >> ownerId >> balance;
}
