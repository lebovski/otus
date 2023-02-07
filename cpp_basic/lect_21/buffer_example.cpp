
#include <fstream>
#include <iostream>
#include <vector>

const size_t buff_size = 4096;

void testRaw(const char *source_file, const char *destination_file) {
  std::ifstream source{source_file};
  if (!source.is_open()) {
    throw std::runtime_error{"Failed to open source file"};
  }

  std::ofstream destination{destination_file};
  if (!destination.is_open()) {
    throw std::runtime_error{"Failed to open destination file"};
  }

  ///

  char *const buffer = new char[buff_size];

  try {
    do {
      source.read(buffer, buff_size);
      destination.write(buffer, source.gcount());
    } while (source);

  } catch (...) {
    delete[] buffer;

    throw;
  }

  delete[] buffer;
}

void testUniquePtr(const char *source_file, const char *destination_file) {
  std::ifstream source{source_file};
  if (!source.is_open()) {
    throw std::runtime_error{"Failed to open source file"};
  }

  std::ofstream destination{destination_file};
  if (!destination.is_open()) {
    throw std::runtime_error{"Failed to open destination file"};
  }

  ///

  const std::unique_ptr<char[]> buffer{new char[buff_size]};

  do {
    source.read(buffer.get(), buff_size);
    destination.write(buffer.get(), source.gcount());
  } while (source);
}

void testVector(const char *source_file, const char *destination_file) {
  std::ifstream source{source_file};
  if (!source.is_open()) {
    throw std::runtime_error{"Failed to open source file"};
  }

  std::ofstream destination{destination_file};
  if (!destination.is_open()) {
    throw std::runtime_error{"Failed to open destination file"};
  }

  ///

  std::vector<char> buffer(buff_size);

  do {
    source.read(buffer.data(), buff_size);
    destination.write(buffer.data(), source.gcount());
  } while (source);
}

////////////////////////////////////////////////////////////////////////////////

int main(const int argc, char *argv[]) {
  try {
    if (argc < 3) {
      std::cout << "Usage: copy <source> <destination>" << std::endl;

      return 1;
    }

    testRaw(argv[1], argv[2]);
    testUniquePtr(argv[1], argv[2]);
    testVector(argv[1], argv[2]);
  } catch (const std::exception &ex) {
    std::cout << "Error: \"" << ex.what() << "\"" << std::endl;
    return 1;
  } catch (...) {
    std::cout << "Unknown error" << std::endl;
    return 1;
  }

  return 0;
}