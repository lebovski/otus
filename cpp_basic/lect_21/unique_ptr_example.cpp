// Dynamic memory usage example
#include "strategy.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

const size_t max_units = 1'000'000;

std::unique_ptr<Unit> make_unit_and_select(Selection &selection) {
  // auto == std::unique_ptr<Soldier>
  auto soldier = std::make_unique<Soldier>(0, 0);  // why not "new Solder"?
  selection.set(soldier.get());

  // try const auto soldier = ...
  return soldier;
}

void testWithDefaultDeleter() {
  Selection selection;

  std::vector<std::unique_ptr<Unit>> units;
  units.reserve(max_units);

  for (size_t i = 0; i < max_units; ++i) {
    units.push_back(make_unit_and_select(selection));
    selection.click(100, 100);
    selection.unset();
  }
}

void testWithCustomDeleter() {
  const auto reportAndDelete = [](const Unit *unit) {
    std::cout << "Deleting unit..." << std::endl;
    delete unit;
  };

  std::unique_ptr<Unit, decltype(reportAndDelete)> soldier1(new Soldier{0, 0},
                                                            reportAndDelete);
  soldier1->attack();

  std::unique_ptr<Unit, decltype(reportAndDelete)> soldier2(new Soldier{0, 0},
                                                            reportAndDelete);
  soldier2->attack();
  soldier2.reset();

  std::unique_ptr<Unit, decltype(reportAndDelete)> soldier3(new Soldier{0, 0},
                                                            reportAndDelete);
  soldier3->attack();
  auto *soldier3Ptr = soldier3.release();  // auto == Unit *
  delete soldier3Ptr;
}

////////////////////////////////////////////////////////////////////////////////

int main(const int, char *[]) {
  try {
    testWithDefaultDeleter();
    testWithCustomDeleter();
  } catch (const std::exception &ex) {
    std::cout << "Error: \"" << ex.what() << "\"" << std::endl;
    return 1;
  } catch (...) {
    std::cout << "Unknown error" << std::endl;
    return 1;
  }

  return 0;
}
