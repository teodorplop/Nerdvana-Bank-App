#pragma once

#include "includes.h"

#include "BankAccountReadOnly.h"

class BankAccount : public BankAccountReadOnly {
public:
  BankAccount();
  BankAccount(int id, int ownerId);

  void deposit(int value);
  bool withdraw(int value);

  string serialize();
  void deserialize(const string& text);
};
