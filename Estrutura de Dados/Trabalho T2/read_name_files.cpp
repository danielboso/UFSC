#include <stdio.h>
#include <dirent.h>
#include <linked_list.h>
#include <string>
#include <iostream>
#include <sstream>

structures::LinkedList<std::string> read_files_name(char* argv) {

  structures::LinkedList<std::string> list = structures::LinkedList<std::string>();
  std::string diretorio = argv;

  DIR *dp;
  struct dirent *dir;

  if ((dp = opendir(diretorio.c_str())) == NULL) {
    std::cout << "ERRO! \n";
  }

  while ((dir = readdir(dp)) != NULL) {
    std::string name_file = std::string(dir->d_name);
    if(name_file != "." && name_file != "..") {
      int length_name_file = name_file.length();
      name_file = name_file.erase(length_name_file-4, length_name_file-1);
      list.push_back(name_file);
    }
  }

  for(int i = 0; i < list.size(); i++) {
    std::cout << i << ". " << list.at(i) << "\n";
  }

  closedir(dp);

  return list;
}


int main (int argc, char* argv[]) {

  read_files_name(argv[1]);
  return 0;
}
