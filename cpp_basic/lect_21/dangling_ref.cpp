#include "strategy.hpp"

#include <array>
#include <iostream>

void make_unit_and_select(Selection &selection) {
  Soldier soldier{0, 0};
  selection.set(&soldier);  // NOLINT
}

void move_home(Selection &selection) {
  std::array numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15};
  for (auto &num : numbers) {
    num += 1;
  }

  selection.click(100, 100);

  for (const auto &num : numbers) {
    std::cout << num << ' ';
  }

  selection.click(200, 200);

  std::cout << std::endl;
}

void test() {
  Selection selection;
  make_unit_and_select(selection);
  move_home(selection);
  selection.unset();
}

////////////////////////////////////////////////////////////////////////////////

int main(const int, char *[]) {
  try {
    test();
  } catch (const std::exception &ex) {
    std::cout << "Error: \"" << ex.what() << "\"" << std::endl;
    return 1;
  } catch (...) {
    std::cout << "Unknown error" << std::endl;
    return 1;
  }

  return 0;
}
