#include "MainFileManager.h"
#include "splay.h"
#include <iostream>
using namespace std;
void FileManager::accessFile(const std::string& fileName) {

    files.access(fileName);
}

void FileManager::removeFile(const std::string& fileName) {
    files.remove(fileName);
}



void FileManager::addFile(const std::string& fileName) {
    system("pause");
    files.insert(fileName);
}

void FileManager::display(std::ostream& out, int maxDepth) const {
    files.inorder(std::cout,maxDepth);
}
