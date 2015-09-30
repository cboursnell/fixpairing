#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct entry {
  string seq;
  string quals;
};


class FixPairing
{
public:
  std::vector<entry> array;
  std::unordered_map<std::string, entry> store;
  int load_right(char*);
  int scan_left(char*, char*);
};