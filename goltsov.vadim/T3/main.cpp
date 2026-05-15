#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "structs.hpp"

int main()
{
  goltsov::Point p;
  std::cin >> p;
  goltsov::Polygon pp;
  std::cin >> pp;
  std::cout << p << '\n' << pp << '\n';
}
