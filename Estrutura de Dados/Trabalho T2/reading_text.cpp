
int main(int argc, char* argv[]) {

  structures::LinkedList<std::string> list = structures::LinkedList<std::string>();
  std::string dir = argv[1];

  DIR *dp;
  struct dirent *dir;

  if ((dp = opendir(diretorio.c_str())) == NULL) {
    std::cout << "ERRO! \n";
  }

  while ((dir = readdir(dp)) != NULL) {
    std::string name_file = std::string(dir->d_name);
    if(name_file != "." && name_file != "..") {
      list.push_back(name_file);
    }
  }

}
