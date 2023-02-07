// Dynamic memory usage example
#include "strategy.hpp"

#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

class Tank : public Unit {
 public:
  using Unit::Unit;

  Tank(Tank &) = delete;
  Tank(Tank &&) = default;

  ~Tank() override { std::cout << "Tank object destroyed." << std::endl; }

  Tank &operator=(const Tank &) = delete;
  Tank &operator=(Tank &&) = default;

  void setDriver(std::shared_ptr<Soldier> driver) {
    m_driver = std::move(driver);
  }

  void attack() override {
    if (!m_driver) {
      return;
    }

    std::cout << "Baba-ba-hhhh!" << std::endl;
  }

  void start() {}

  void setFuelLevel(const size_t level) {
    if (level > 0 || !m_driver) {
      return;
    }

    m_driver->sleep();
  }

 private:
  std::shared_ptr<Soldier> m_driver;
};

////////////////////////////////////////////////////////////////////////////////

class TankDriver : public Soldier {
 public:
  using Soldier::Soldier;

  TankDriver(TankDriver &) = delete;
  TankDriver(TankDriver &&) = default;

  ~TankDriver() override {
    std::cout << "TankDriver object destroyed." << std::endl;
  }

  TankDriver &operator=(const TankDriver &) = delete;
  TankDriver &operator=(TankDriver &&) = default;

  void attack() override {
    if (m_tank.expired()) {
      std::cout << "Tank is expired" << std::endl;
    }

    // auto == std::shared_ptr<Tank>
    if (const auto tank = m_tank.lock(); tank) {
      tank->attack();
    }

    Soldier::attack();
  }

  void setTank(const std::shared_ptr<Tank> &tank) { m_tank = tank; }

  void startTank() {
    // auto == std::shared_ptr<Tank>
    const auto tank = m_tank.lock();
    if (!tank) {
      return;
    }
    tank->start();
  }

 private:
  std::weak_ptr<Tank> m_tank;
};

////////////////////////////////////////////////////////////////////////////////

void test() {
  const auto driver = std::make_shared<TankDriver>(0, 0);
  {
    const auto tank = std::make_shared<Tank>(0, 0);

    driver->setTank(tank);
    tank->setDriver(driver);

    driver->startTank();
    driver->attack();

    // Tank object will be destroyed at the next line
  }

  std::cout << std::endl;
  std::cout << "==============================" << std::endl;
  std::cout << "Repeating without tank object:" << std::endl;

  driver->attack();
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
