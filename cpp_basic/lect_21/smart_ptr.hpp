// Smart pointer implementation example

#pragma once

#include <utility>

template <typename T>
class SmartPtr {
 public:
  SmartPtr() noexcept = default;

  SmartPtr(T *ptr) noexcept : m_ptr{ptr} {}

  ~SmartPtr() {  // destructors are noexcept by default
    reset();
  }

  // Non copyable
  SmartPtr(const SmartPtr<T> &) = delete;
  SmartPtr &operator=(const SmartPtr<T> &) = delete;

  // Movable
  SmartPtr(SmartPtr<T> &&other) noexcept { std::swap(m_ptr, other.m_ptr); }

  SmartPtr &operator=(SmartPtr<T> &&other) noexcept {
    // prevent bugs then mote to self, like p = std::move(p)
    if (this == &other) {
      return *this;
    }

    reset();
    std::swap(m_ptr, other.m_ptr);

    return *this;
  }

  [[nodiscard]] bool empty() const noexcept { return m_ptr == nullptr; }

  // conversion to bool operator overloading to support code like
  // if (!p) {}
  operator bool() const noexcept { return empty(); }

  void reset(T *ptr = nullptr) noexcept {
    delete m_ptr;  // it is save to delete nullptr;
    m_ptr = ptr;
  }

  [[nodiscard]] const T *get() const noexcept { return m_ptr; }

  [[nodiscard]] T *get() noexcept { return m_ptr; }

  // operator * overloading to support code like this
  // SmartPtr<Object> p{new Object};
  // *p = Object{};
  const T &operator*() const noexcept { return get(); }

  T &operator*() noexcept { return get(); }

  // -> operator overloading to support code like this
  // SmartPtr<Object> p{new Object};
  // p->object_method();
  const T *operator->() const noexcept { return get(); }

  T *operator->() noexcept { return get(); }

 private:
  T *m_ptr = nullptr;
};
