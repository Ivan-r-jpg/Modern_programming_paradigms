#include "User.h"

// Ініціалізація статичних змінних класу User
int User::totalUsers = 0;
int User::nextID = 1;
std::vector<std::string> User::accessLevels = { "User","Moderator","Admin" };