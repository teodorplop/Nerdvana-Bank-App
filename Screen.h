#pragma once

#include "includes.h"

class Screen {
private:
  string name;
  vector<string> userActions;

  bool isRefreshRequested;

  void showTitle();
  void showUserActions();
  const string& waitForInput();

protected:

  void refresh();

  virtual void showInternal();
  virtual void handleUserAction(const string& action);

public:
  Screen(const string& name, const vector<string>& userActions);

  void show();
};
