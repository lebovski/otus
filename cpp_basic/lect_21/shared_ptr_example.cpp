// Dynamic memory usage example
#include "strategy.hpp"

#include <iostream>
#include <memory>

class SharedSelection {
 public:
  void set(const std::shared_ptr<Unit> &ptr) { m_current = ptr; }

  void set(std::shared_ptr<Unit> &&ptr) { m_current = std::move(ptr); }

  void unset() {
    m_current = nullptr;  //  m_current.reset();
  }

  void click(int x, int y) {
    if (!m_current) {
      return;
    }

    m_current->move(x, y);
  }

 private:
  std::shared_ptr<Unit> m_current;
};

void testWithDefaultDeleter() {
  SharedSelection selection;

  // auto == std::shared_ptr<Soldier>
  auto solder = std::make_shared<Soldier>(0, 0);

  selection.set(solder);
  solder.reset();

  selection.click(100, 100);
}

void testWithCustomDeleter() {
  const auto reportAndDelete = [](const Unit *unit) {
    std::cout << "Deleting shared unit..." << std::endl;
    delete unit;
  };

  const std::shared_ptr<Unit> soldier1(new Soldier{0, 0}, reportAndDelete);
  soldier1->attack();

  std::shared_ptr<Unit> soldier2(new Soldier{0, 0}, reportAndDelete);
  soldier2->attack();
  soldier2.reset();
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
