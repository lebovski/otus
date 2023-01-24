#include <cstring>
#include <exception>
#include <new>

class Person {
public:
  Person(const char *firstname, const char *lastname) {
    firstname_ = nullptr;
    lastname_ = nullptr;

    try {
      firstname_ = new char[std::strlen(firstname) + 1];
      std::strcpy(firstname_, firstname);
      lastname_ = new char[std::strlen(lastname) + 1];
      std::strcpy(lastname_, lastname);
    } catch (...) {
      delete firstname_;
      throw;
    }
  }

  ~Person() {
    delete firstname_;
    delete lastname_;
  }

  Person &operator=(const Person &other) {
    delete firstname_;
    delete lastname_;
    firstname_ = new char[std::strlen(other.firstname_) + 1];
    std::strcpy(firstname_, other.firstname_);
    lastname_ = new char[std::strlen(other.lastname_) + 1];
    std::strcpy(lastname_, other.lastname_);
    return *this;
  }

private:
  char *firstname_;
  char *lastname_;
};

int main() {
  try {
    Person john{"John", "Smith"};
    Person mary{"Mary", "Boile"};

    john = mary;
  } catch (...) {
  }
}