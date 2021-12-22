#include "User.h"

using namespace std;

User::User() {
}

User::User(int id, const string& username, const string& password) : User() {
  this->id = id;
  this->username = username;
  this->password = password;
}

int User::getId() {
  return id;
}

const string& User::getUsername() {
  return username;
}

bool User::checkPassword(const string& password) {
  return this->password == password;
}

string User::serialize() {
  stringstream stream;
  stream << id << ' ' << username << ' ' << password;
  return stream.str();
}

void User::deserialize(const string& text) {
  istringstream stream(text);
  stream >> id >> username >> password;
}
