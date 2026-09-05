#include <cctype>
#include <crypt.h>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

int wordToIntScore(const std::string &word) {
  int totalScore = 0;
  for (char ch : word) {
    auto u_ch = static_cast<unsigned char>(ch);
    if (std::isalpha(u_ch)) {
      totalScore += (std::tolower(u_ch) - 'a' + 1);
    } else if (std::isdigit(u_ch)) {
      totalScore += ch - '0';
    }
  }
  return totalScore;
}

uint64_t fib(int terms) {
  if (terms <= 0)
    return 0;
  if (terms == 1 || terms == 2)
    return 1;
  uint64_t a = 1;
  uint64_t b = 1;
  uint64_t c = 1;
  for (int i = 3; i <= terms; ++i) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
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

  while (fib_result > 99999999) {
    std::string result_str = std::to_string(fib_result);
    int new_terms = wordToIntScore(result_str);
    fib_result = fib(new_terms);
  }

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
