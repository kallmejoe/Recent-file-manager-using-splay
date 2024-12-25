#pragma once
#include "splay.h"
#include <string>
#include <fstream>
#include <iostream>

class FileManager {
public:
    SplayTree<std::string> files;

public:
    void accessFile(const std::string& fileName);
    void removeFile(const std::string& fileName);
    void addFile(const std::string& fileName);
    void displayAll(std::ostream& out) const;
    void display(std::ostream& out, int maxDepth) const;
    typename SplayTree<std::string>::Node* getRoot() const { return files.root; }
};

class FileExplorer {
public:
    class FolderNode {
        public:
            std::string folderName;
            FolderNode* next;
            FileManager fileManager;
            FolderNode(const std::string& name) : folderName(name), next(nullptr) {}
    };

    FolderNode* head;
    FileExplorer() : head(nullptr) {}
    ~FileExplorer();

    void addFolder(const std::string& folderName);
    void removeFolder(const std::string& folderName);
    void displayFolders(std::ostream& out) const;
    FileManager* getFolderfiles(const std::string& folderName);
    void exportToDot(const std::string& filename) const;
    void moveToHead(FolderNode* folder);
    void solveit(FolderNode* folder);
    
};
