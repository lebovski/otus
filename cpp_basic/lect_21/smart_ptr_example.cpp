// Dynamic memory usage example
#include "smart_ptr.hpp"
#include "strategy.hpp"

#include <array>
#include <iostream>
#include <vector>

const size_t max_units = 1'000'000;

SmartPtr<Unit> make_unit_and_select(Selection &selection) {
  SmartPtr<Unit> soldier{new Soldier{0, 0}};
  selection.set(soldier.get());

  return soldier;
}

void make_and_clean() {
  Selection selection;

  std::vector<SmartPtr<Unit>> units;
  units.reserve(max_units);

  for (size_t i = 0; i < max_units; ++i) {
    units.push_back(make_unit_and_select(selection));
    selection.click(100, 100);
    selection.unset();
  }
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
