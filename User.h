#pragma once

#include "includes.h"

class BankAccount;

class User {
private:
  int id;
  string username;
  string password;

public:
  User();
  User(int id, const string& username, const string& password);

  int getId();
  const string& getUsername();
  bool checkPassword(const string& password);

  string serialize();
  void deserialize(const string& text);
};
