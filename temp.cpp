#include <iostream>
#include "LinkedList.hpp"

using namespace std;

int main() {
  LinkedList<int> a({19, 17, 54, 55, 1999, 2002, 1965, 1964});
  for(auto it = a.begin(); it != a.end(); ++it)
    cout << *it << endl;
}