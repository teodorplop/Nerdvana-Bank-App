#pragma once

#include "Screen.h"

class User;
class UserDatabase;
class BankDatabase;

class LoginScreen : public Screen {
private:
  BankDatabase* bankDb;
  UserDatabase* userDb;

  void login();
  void createUser();

  void waitForUsernameAndPassword(string& username, string& password);
  void onLoginSuccessful(User* user);

public:
  LoginScreen(UserDatabase* userDb, BankDatabase* bankDb);
  void show();
};
