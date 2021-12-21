#include "LoginScreen.h"

#include "UserDatabase.h"
#include "ScreenStack.h"

#include "MainScreen.h"

LoginScreen::LoginScreen(UserDatabase* userDb, BankDatabase* bankDb) :
  Screen("LoginScreen", {"Login", "Register", "Exit"}) {
  this->userDb = userDb;
  this->bankDb = bankDb;
}

void LoginScreen::show() {
  Screen::show();

  string option;
  string username, password;
  do {
    option = waitForInput();

    if (option == "Login")
      login();
    else if (option == "Register")
      createUser();
    else if (option == "Exit")
      exit();
  } while (!isRefreshRequested() && !isExitRequested());
}

void LoginScreen::login() {
  string username, password;
  waitForUsernameAndPassword(username, password);

  User* user = userDb->login(username, password);
  if (user != NULL)
    onLoginSuccessful(user);
  else
    cout << "Could not login.\n";
}

void LoginScreen::createUser() {
  string username, password;
  waitForUsernameAndPassword(username, password);

  User* user = userDb->createUser(username, password);
  if (user != NULL)
    onLoginSuccessful(user);
  else
    cout << "Could not register.\n";
}

void LoginScreen::waitForUsernameAndPassword(string& username, string& password) {
  cout << "Insert username: ";
  cin >> username;
  cout << "Insert password: ";
  cin >> password;
}

void LoginScreen::onLoginSuccessful(User* user) {
  MainScreen mainScreen(bankDb, user);
  ScreenStack::getInstance()->push(&mainScreen);
}
