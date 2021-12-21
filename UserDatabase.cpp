#include "UserDatabase.h"

#include "Debug.h"
#include "User.h"

const string UserDatabase::FILENAME = "users.txt";

UserDatabase::UserDatabase() {
  readFromDisk();
}

UserDatabase::~UserDatabase() {
  writeToDisk();
}

User* UserDatabase::fetchUser(const string& username) {
  unsigned int index;

  index = 0;
  while (index < users.size() && users[index]->getUsername() != username)
    ++index;

  return index < users.size() ? users[index] : NULL;
}

User* UserDatabase::login(const string& username, const string& password) {
  Debug::Log("[UserDatabase] Trying to login user {%s} with password {%s}", username.c_str(), password.c_str());

  User* user = fetchUser(username);

  if (user != NULL && !user->checkPassword(password)) {
    user = NULL;
    Debug::Log("[UserDatabase] Login failed");
  } else
    Debug::Log("[UserDatabase] Login successful");

  return user;
}

User* UserDatabase::createUser(const string& username, const string& password) {
  Debug::Log("[UserDatabase] Trying to register user {%s}", username.c_str());

  User* user = fetchUser(username);

  if (user == NULL) {
    user = new User(users.size(), username, password);
    users.push_back(user);

    Debug::Log("[UserDatabase] Register successful {%s}", username.c_str());
  } else {
    user = NULL;
    Debug::Log("[UserDatabase] Register failed");
  }

  return user;
}

void UserDatabase::readFromDisk() {
  ifstream fin(FILENAME);

  string line;
  User* user;
  while (getline(fin, line))
    if (line.size() > 0) {
      user = new User(users.size());
      user->deserialize(line);
      users.push_back(user);
    }

  fin.close();

  Debug::Log("[UserDatabase] Read %d users from database.", users.size());
}

void UserDatabase::writeToDisk() {
  ofstream fout(FILENAME);

  for (User*& user : users) {
    fout << user->serialize() << '\n';
    delete user;
  }

  fout.close();

  Debug::Log("[UserDatabase] Saved %d users to database.", users.size());
}
