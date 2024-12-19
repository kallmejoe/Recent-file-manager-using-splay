#include "MainFileManager.h"
#include "splay.h"
#include <iostream>
using namespace std;

void FileManager::accessFile(const std::string& fileName) {
    files.access(fileName); // Assuming SplayTree has an 'access' function
}

void FileManager::removeFile(const std::string& fileName) {
    files.remove(fileName); // Assuming SplayTree has a 'remove' function
}

void FileManager::displayAll(std::ostream& out) const {
    files.inorder(out); // Assuming SplayTree has an 'inorder' function
}

void FileManager::addFile(const std::string& fileName) {
    files.insert(fileName); // Assuming SplayTree has an 'insert' function
}

void FileManager::display(std::ostream& out, int maxDepth) const {
    files.inorder(out, maxDepth); // Assuming SplayTree supports depth-based traversal
}
