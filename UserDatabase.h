#pragma once

#include "includes.h"

class User;

class UserDatabase {
private:
  static const string FILENAME;

  vector<User*> users;
  int lastUserId;

  User* fetchUser(const string& username);

  void readFromDisk();
  void writeToDisk();

public:
  UserDatabase();
  ~UserDatabase();

  User* createUser(const string& username, const string& password);
  User* login(const string& username, const string& password);
};
