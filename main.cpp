#include "Debug.h"

#include "UserDatabase.h"
#include "BankDatabase.h"

#include "LoginScreen.h"
#include "ScreenStack.h"

int main() {
  Debug* debug = new Debug();

  UserDatabase* userDb = new UserDatabase();
  BankDatabase* bankDb = new BankDatabase();

  ScreenStack screenStack;
  LoginScreen loginScreen(userDb, bankDb);
  screenStack.push(&loginScreen);

  delete userDb;
  delete bankDb;

  delete debug;

  return 0;
}
