// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <execution>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <thread>
#include <vector>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::istream &stream, Counter &);

void print_topk(std::ostream &stream, const Counter &, const size_t k);

Counter join_map(const Counter &counter1, const Counter &counter2);

Counter get_file_and_count(const std::string &filepath);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: topk_words [FILES...]\n";
    return EXIT_FAILURE;
  }

  auto start = std::chrono::high_resolution_clock::now();
  Counter freq_dict;
  std::vector<std::future<Counter>> tasks;

  for (int i = 1; i < argc; ++i) {
    tasks.push_back(std::async(get_file_and_count, argv[i]));
  }

  for (size_t i = 0; i < tasks.size(); ++i) {
    try {
      freq_dict = join_map(freq_dict, tasks[i].get());
    } catch (std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }

  print_topk(std::cout, freq_dict, TOPK);
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

Counter get_file_and_count(const std::string &filepath) {
  std::ifstream input{filepath};
  if (!input.is_open()) {
    throw std::runtime_error{"Failed to open file '" + filepath + "'"};
  }

  Counter freq_dict;
  count_words(input, freq_dict);

  return freq_dict;
}

Counter join_map(const Counter &counter1, const Counter &counter2) {
  Counter joined_counter;
  for (const auto &[word, freq] : counter2) {
    joined_counter[word] += freq;
  }
  for (const auto &[word, freq] : counter1) {
    joined_counter[word] += freq;
  }
  return joined_counter;
}

std::string tolower(const std::string &str) {
  std::string lower_str;
  std::transform(std::cbegin(str), std::cend(str),
                 std::back_inserter(lower_str),
                 [](unsigned char ch) { return std::tolower(ch); });
  return lower_str;
};

void count_words(std::istream &stream, Counter &counter) {
  std::for_each(std::istream_iterator<std::string>(stream),
                std::istream_iterator<std::string>(),
                [&counter](const std::string &s) { ++counter[tolower(s)]; });
}

void print_topk(std::ostream &stream, const Counter &counter, const size_t k) {
  std::vector<Counter::const_iterator> words;
  words.reserve(counter.size());
  for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
    words.push_back(it);
  }

  std::partial_sort(
      std::begin(words), std::begin(words) + k, std::end(words),
      [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

  std::for_each(std::begin(words), std::begin(words) + k,
                [&stream](const Counter::const_iterator &pair) {
                  stream << std::setw(4) << pair->second << " " << pair->first
                         << '\n';
                });
}
