#pragma once

#include "includes.h"

class Screen {
private:
  string name;
  vector<string> options;

  bool refreshRequested;

protected:
  void showTitle();
  void showOptions();
  const string& waitForInput();

  bool isRefreshRequested();
  void refresh();

public:
  Screen(const string& name, const vector<string>& options);

  virtual void show();
};
