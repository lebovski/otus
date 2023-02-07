// Dynamic memory usage example
#include "strategy.hpp"

#include <iostream>
#include <vector>

const std::size_t max_units = 1'000'000;

Unit *make_unit_and_select(Selection &selection) {
  Unit *soldier = new Soldier{0, 0};
  selection.set(soldier);

  return soldier;
}

void clean_units(std::vector<Unit *> &units) {
  for (Unit *const unit : units) {
    delete unit;
  }
  units.clear();
}

void make_and_clean() {
  Selection selection;

  std::vector<Unit *> units;
  units.reserve(max_units);

  for (std::size_t i = 0; i < max_units; ++i) {
    units.push_back(make_unit_and_select(selection));
    selection.click(100, 100);
    selection.unset();
  }

  clean_units(units);
}

void test() {
  for (size_t i = 0;; ++i) {
    make_and_clean();

    if ((i % 1000) == 0) {
      std::cout << i << std::endl;
    }
  }
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
