#include <stdio.h>
#include <string>
#include <iostream>

int generating_key_word(std::string word) {
  int key = 0;

  for (int i = 0; i < word.size(); i++) {
    char letter = word[i];
    int value_of_letter = letter;
    key += (i + 1) * value_of_letter;
  }

  return key;
}

int main (int argc, char* argv[]) {

  std::string string_test0 = "teste";
  std::string string_test1 = "teste_arquivo";
  std::string string_test2 = "teste_arquivo.teste";

  int value_of_test0 = generating_key_word(string_test0);
  int value_of_test1 = generating_key_word(string_test1);
  int value_of_test2 = generating_key_word(string_test2);

  std::cout << "valor do primeiro teste: " << value_of_test0 << "\n";
  std::cout << "valor do segundo teste: " << value_of_test1 << "\n";
  std::cout << "valor do terceiro teste: " << value_of_test2 << "\n";
}
