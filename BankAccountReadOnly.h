#pragma once

#include "includes.h"

class BankAccountReadOnly {
protected:
  int id;
  int ownerId;
  int balance;

public:
  int getId() { return id; }
  int getOwnerId() { return ownerId; }
  int getBalance() { return balance; }
};
