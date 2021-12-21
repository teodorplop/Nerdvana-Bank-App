#include "Screen.h"

Screen::Screen(const string& name, const vector<string>& options) {
  this->name = name;
  this->options = options;
}

void Screen::showTitle() {
  cout << LINE << name << '\n' << LINE;
}

void Screen::showOptions() {
  unsigned int i;

  for (i = 0; i < options.size(); ++i)
    cout << i << " - " << options[i] << '\n';

  cout << LINE;
}

bool Screen::isRefreshRequested() {
  return refreshRequested;
}

void Screen::refresh() {
  refreshRequested = true;
  show();
}

void Screen::show() {
  system("cls");

  refreshRequested = false;
  showTitle();
  showOptions();
}

const string& Screen::waitForInput() {
  unsigned int option;

  do {
    cin >> option;
    cin.get();
  } while (option >= options.size());

  return options[option];
}
