#include <iostream>
#include <sstream>
#include <string>

using std::istream;
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::istringstream;

istream &read_and_print_until_eof_and_clear_eofbit(istream &is) {
  string str;
  while (is >> str) {
    cout << str << endl;
  }
  is.clear(is.rdstate() & ~is.failbit & ~is.eofbit);
  // refer to Primer p.314
  // EOF will set eofbit and failbit, so I clear these two bits, leaving other
  // bits unchanged
  return is;
}

int main() {
  istringstream is("I really love hsilu");
  read_and_print_until_eof_and_clear_eofbit(is);
  cout << is.rdstate() << endl; // goodbit is guarantee to have value 0
}