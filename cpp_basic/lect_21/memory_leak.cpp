
#include "strategy.hpp"

#include <iostream>

const auto max_units = 600'000'000;

void make_unit_and_select(Selection &selection) {
  Unit *soldier = new Soldier{0, 0};
  selection.set(soldier);
}

void test() {
  Selection selection;

  for (size_t i = 0; i < max_units; ++i) {
    make_unit_and_select(selection);

    selection.click(100, 100);
    selection.unset();

    if ((i % 10000) == 0) {
      std::cout << i << std::endl;
    }
  }

  std::getchar();
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
