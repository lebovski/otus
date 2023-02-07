// Dynamic memory usage example
#include "strategy.hpp"

#include <iostream>
#include <memory>

void test() {
  Selection selection;

  // auto == std::unique_ptr<Soldier>
  auto soldier = std::make_unique<Soldier>(0, 0);
  selection.set(soldier.get());

  soldier.reset();  // !!!!

  std::cout << "Going to click..." << std::endl;
  selection.click(100, 100);
  std::cout << "Clicked." << std::endl;
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
