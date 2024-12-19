#pragma once
#include "splay.h"
#include <string>
#include <iostream>

class FileManager {
private:
    SplayTree<std::string> files;

public:
    void accessFile(const std::string& fileName);
    void removeFile(const std::string& fileName);
    void addFile(const std::string& fileName);
    void displayAll(std::ostream& out) const;
    void display(std::ostream& out, int maxDepth) const;
};
