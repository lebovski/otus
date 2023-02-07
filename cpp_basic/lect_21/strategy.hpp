#pragma once

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class Unit {
 public:
  Unit(const int x, const int y) : m_x{x}, m_y{y} {}

  Unit(Unit &) = delete;
  Unit(Unit &&) = default;

  virtual ~Unit() = default;

  Unit &operator=(const Unit &) = delete;
  Unit &operator=(Unit &&) = default;

  void move(const int x, const int y) {
    m_x = x;
    m_y = y;
  }

  virtual void attack() = 0;

  [[nodiscard]] int health() const { return m_health; }

 private:
  int m_x;
  int m_y;
  int m_health = 100;
};

////////////////////////////////////////////////////////////////////////////////

class Soldier : public Unit {
 public:
  using Unit::Unit;

  void attack() override { std::cout << "Tra-ta-ta-ta!" << std::endl; }

  void sleep() {}
};

////////////////////////////////////////////////////////////////////////////////

class Selection {
 public:
  void set(Unit *const unit) { m_current = unit; }

  void unset() { m_current = nullptr; }

  void click(const int x, const int y) {
    if (m_current == nullptr) {
      return;
    }

    m_current->move(x, y);
  }

 private:
  Unit *m_current = nullptr;
};

////////////////////////////////////////////////////////////////////////////////