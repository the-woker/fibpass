#include <cctype>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#if __linux__
#include <crypt.h>
#endif

int wordToIntScore(const std::string &word) {
  int totalScore = 0;
  for (char ch : word) {
    if (std::isalpha(ch)) {
      totalScore += (std::tolower(ch) - 'a' + 1);
    }
  }
  return totalScore;
}

uint64_t fib(int terms) {
  if (terms <= 0)
    return 0;
  std::vector<uint64_t> seq;
  seq.reserve(terms);
  for (int i = 0; i < terms; ++i) {
    if (i < 2) {
      seq.push_back(1);
    } else {
      seq.push_back(seq[i - 1] + seq[i - 2]);
    }
  }
  return seq[seq.size()];
}

int main(int argc, char *argv[]) {
  std::string word{};

  if (argc > 1) {
    word = argv[1];
  } else {
    std::cerr << "Usage: " << argv[0] << " <word>" << std::endl;
    return 1;
  }

  int terms = wordToIntScore(word);
  uint64_t fib_result = fib(terms);
  std::string password_input = std::to_string(fib_result);

  char salt_buffer[CRYPT_GENSALT_OUTPUT_SIZE];
  char *generated_salt = crypt_gensalt(nullptr, 0, nullptr, 0);

  char *password_hash = crypt(password_input.c_str(), generated_salt);

  if (password_hash != nullptr) {
    std::cout << fib_result << std::endl;
    std::cout << password_hash << std::endl;
  } else {
    std::cerr << "Error: Encryption failed." << std::endl;
    return 1;
  }

  return 0;
}
