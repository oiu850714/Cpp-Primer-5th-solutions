#include "12.27.h"
#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;

void runQueries(ifstream &is) {
  TextQuery tq(is);

  while (true) {
    cout << "enter word to look for, or q to quit: ";
    string s;
    if (!(cin >> s) || s == "q")
      break;
    print(cout, tq.query(s));
  }
}

int main() {
  cout << "input file name: ";
  string file_name;
  cin >> file_name;
  ifstream is(file_name);
  if (!is) {
    cout << "open file failed." << endl;
    return 1;
  }

  // tq.print_line_and_map();
  runQueries(is);
}