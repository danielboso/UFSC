#include <string>
#include <cstring>
#include <stdio.h>
#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include "./data_structures/linked_list.h"
//#include "./data_structures/avl_tree.h"
#include <dirent.h>

typedef struct ManPage {
  char command;
  char content;
} ManPage;

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
  free(dp);
  free(dir);
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
  std::string content_file;
  std::ifstream file_stream (filename, std::ifstream::binary);
  if (file_stream) {
    // get length of file:
    file_stream.seekg(0, file_stream.end);
    int length = file_stream.tellg();

    file_stream.seekg(0, file_stream.beg);

    char * buffer = new char [length];

    file_stream.read(buffer, length); // read data as a block:
    file_stream.close();
    content_file = std::string(buffer);
    content_file.append("\0");

    delete[] buffer;
  }
  return content_file;
}

std::string return_directory_file(std::string directory_, std::string file) {
  std::string directory = directory_;
  directory.append("/" + file);
  return directory;
}

structures::LinkedList<std::string> collect_words(std::string text) {
  structures::LinkedList<std::string> list_words = structures::LinkedList<std::string>();
  int lenght_of_text = text.size()+1;
  char str[lenght_of_text];
  for (int i = 0; i < lenght_of_text; i++) {
    str[i] = text[i];
  }

  char * pch;
  pch = std::strtok (str," ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
  while (pch != NULL) {
    list_words.push_back(std::string(pch));
    pch = strtok (NULL, " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
  }
  free(pch);
  return list_words;
}

structures::LinkedList<std::string> remove_words_ignored(structures::LinkedList<std::string> list_words_, structures::LinkedList<std::string> list_words_to_ignore) {
  structures::LinkedList<std::string> list_words = list_words_;
  std::cout << "list_words_to_ignore.size(): "  << list_words_to_ignore.size() << "\n";

  int i = 0;
  int size_of_list_words = list_words.size();
  std::cout << "size_of_list_words: " << size_of_list_words << "\n";

  while(i < size_of_list_words) {
    //bool removeu = false;
    std::cout << "i: " << i << "\n";
    for(int j = 0; j < list_words_to_ignore.size(); j++) {
      //std::cout << "list_words_to_ignore: " << list_words_to_ignore.at(j) << "\n";
      /*
      if(list_words.at(i) == list_words_to_ignore.at(j)) {
        std::cout << "encontrou.\n";
        list_words.pop(i);
        size_of_list_words--;
        removeu |= true;
        break;
      }
      */
    }
    /*
    if (removeu == false) {
      i++;
    }*/
    i++;
  }

  for(int i = 0; i < list_words_to_ignore.size()-180 ; i++) {
    std::cout << "i: " << i << "\n";
    bool contains_word = list_words.contains(list_words_to_ignore.at(i));
    std::cout << "contains__word: " << contains_word   << "\n\n";
    int index_to_remove = list_words.find(list_words_to_ignore.at(i));
    while (contains_word) {
      std::cout << "index_to_remove: " << index_to_remove << "\n";
      list_words.pop(index_to_remove);
      contains_word = list_words.contains(list_words_to_ignore.at(i));
      std::cout << "contains__word: " << contains_word << "\n";
    }
  }
  return list_words;
}

long int bigger_length_command(structures::LinkedList<std::string> list_name_files) {
  long int bigger_lenght_command = 0;
  //for(int i = 0; i < list_name_files.size(); i++) {
    //std::string name_file = remove_extension_txt(list_name_files.at(i));
    //if (bigger_lenght_command > name_file.length()) {
    //  bigger_lenght_command = name_file.length();
    //}
  //}
  return bigger_lenght_command;
}

long int bigger_length_text(structures::LinkedList<std::string> list_name_files, char* argv) {
  long int bigger_length_text = 0;
  std::string directory = argv;
  for(int i = 0; i < list_name_files.size(); i++) {
    std::string directory_file = return_directory_file(directory, list_name_files.at(i));
    std::string content_text = read_file(directory_file);
    if (bigger_length_text > content_text.length()+1) {
      bigger_length_text = content_text.length()+1;
    }
  }
  return bigger_length_text;
}

void generate_indexing_primary_key(char* argv) {
  structures::LinkedList<std::string> name_files = read_files_name(argv);

  long int bigger_length_command;
  long int bigger_length_text;


  FILE * manpage_dat = fopen("manpage.dat", "w");
}
int main(int argc, char* argv[]) {

  // Leitura de palavras do arquivo de ManPage
  // ---------------------------------------------------------------------------
  std::string directory = std::string(argv[1]);
  structures::LinkedList<std::string> list = read_files_name(argv[1]);
  std::cout << bigger_length_command(list);
  //std::cout << bigger_length_text(list, argv[1]);
  //std::string directory_file = return_directory_file(directory, list.at(0));
  //std::string content_file = read_file(directory_file);
  //structures::LinkedList<std::string> list_words = collect_words(content_file);
  //for (int i = 0; i < list_words.size(); i++) {
  //  std::cout << list_words.at(i) << "\n";
  //}
  // ---------------------------------------------------------------------------

  // Leitura de palavras a serem ignoradas
  //---------------------------------------------------------------------------
  //std::string content_file_ignore_lexical = read_file("./lexicalIgnored.txt");
  //structures::LinkedList<std::string> list_lexical_words = collect_words(content_file_ignore_lexical);
  //std::cout << "\n";
  //for (int i = 0; i < list_lexical_words.size(); i++) {
  //  std::cout << list_lexical_words.at(i) << "\n";
  //}

  // Remove palavras ignoradas
  // ---------------------------------------------------------------------------
  // - Diretorio
  //std::string directory = argv[1];
  // - Lista de nomes de arquivo
  //structures::LinkedList<std::string> list_files_name = read_files_name(argv[1]);
  // - Diretório de arquivo
  //std::string directory_file = return_directory_file(directory, list_files_name.at(0));
  // - Conteúdo de arquivo
  //std::string content_file = read_file(directory_file);
  // - Palavras do arquivo
  //structures::LinkedList<std::string> list_words = collect_words(content_file);
  // - Conteúdo do arquivo de palavras para serem ignoradas
  //std::string words_ignore =  read_file("./lexicalIgnored.txt");
  // - Lista de palavras a serem ignoradas
  //std::cout << "content_file: " << content_file << "\n";
  //std::cout << "words_ignore: " << words_ignore << "\n";
  //structures::LinkedList<std::string> list_ignore_words = collect_words(words_ignore);
  //std::cout << "file_read: " << words_ignore << "\n";
  //std::cout << "list_ignore_words.size(): " << list_ignore_words.size() << "\n";
  //for(int i = 0; i < list_ignore_words.size(); i++) {
  //  std::cout << list_ignore_words.at(i) << "\n";
  //}
  //structures::LinkedList<std::string> new_list_words = remove_words_ignored(list_words, list_ignore_words);
  //for (int i = 0; i < new_list_words.size(); i++) {
  //  std::cout << new_list_words.at(i) << "\n";
  //}

  // Menu
  // ---------------------------------------------------------------------------
  /*
  int option;
  std::cout << "Digite a opção desejada:\n";
  std::cout << "[0] Sair.\n";
  std::cout << "[1] Gerar indexação por chave primária (nome ManPage).\n";
  std::cout << "[2] Busca por chave primária.\n";
  std::cout << "[3] Busca por chave secundária.\n";
  std::cout << "[4] Busca conjuntiva com 2 chaves secundárias.\n";
  std::cin >> option;
  do {
    switch (option) {
      case 0:
        exit(0);
        break;
      case 1:

        std::cout << "Disponível apena busca por chave primária.";
        std::cin >> option;
        break;
      case 2:

        std::cin >> option;
        break;
      case 3:

        std::cin >> option;
        break;
    }
  } while(option != 0);
  */
  // ---------------------------------------------------------------------------

  return 0;
}
