#include <string>
#include <cstring>
#include <stdio.h>
#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include "./data_structures/linked_list.h"
#include <dirent.h>

structures::LinkedList<std::string> read_files_name(char* argv) {
  structures::LinkedList<std::string> list = structures::LinkedList<std::string>();
  std::string diretorio = argv;
  DIR *dp;
  struct dirent *dir;

  if ((dp = opendir(diretorio.c_str())) == NULL) {
    std::cout << "ERRO! \n";
  }

  while ((dir = readdir(dp)) != NULL) {
    if(std::string(dir->d_name) != "." && std::string(dir->d_name) != "..") {
      list.push_back(dir->d_name);
    }
  }

  return list;
}

std::string remove_extension_txt(std::string name_of_file) {
  std::string name_without_extension;
  name_without_extension = name_of_file.erase(name_of_file.size()-4, name_of_file.size());
  return name_without_extension;
}

int generating_key_word(std::string word) {
  int key = 0;

  for (int i = 0; i < word.size(); i++) {
    char letter = word[i];
    int value_of_letter = letter;
    key += (i + 1) * value_of_letter;
  }

  return key;
}

std::string read_file(std::string filename) {
  std::string buffers;
  std::ifstream file_stream (filename, std::ifstream::binary);
  if (file_stream) {
    // get length of file:
    file_stream.seekg (0, file_stream.end);
    int length = file_stream.tellg();
    file_stream.seekg (0, file_stream.beg);

    char * buffer = new char [length];

    file_stream.read (buffer, length); // read data as a block:

    buffers = std::string(buffer);

    file_stream.close();
    delete[] buffer;
  }
  return buffers;
}

std::string return_directory_file(std::string directory_, std::string file) {
  std::string directory = directory_;
  directory.append("/" + file);
  return directory;
}

structures::LinkedList<std::string> collect_words(std::string text) {
  structures::LinkedList<std::string> list_words = structures::LinkedList<std::string>();
  int lenght_of_text = text.size();
  char str[lenght_of_text];
  for (int i = 0; i < lenght_of_text; i++) {
    str[i] = text[i];
  }

  char * pch;
  pch = strtok (str," ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
  while (pch != NULL)
  {
    pch = strtok (NULL, " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
    if (pch != NULL && pch != nullptr) {
      std::cout << pch << "\n";
      list_words.push_back(pch);
    }
  }
  return list_words;
}

int main(int argc, char* argv[]) {
  std::string directory = argv[1];
  structures::LinkedList<std::string> list = read_files_name(argv[1]);

  std::string directory_file = return_directory_file(directory, list.at(0));
  std::string content_file = read_file(directory_file);

  structures::LinkedList<std::string> list_words = collect_words(content_file);
  for (int i = 0; i < list_words.size(); i++) {
    std::cout << list_words.at(i) << "\n";
  }



  return 0;
}
