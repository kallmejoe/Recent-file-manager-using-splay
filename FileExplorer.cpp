#include "MainFileManager.h"
#include <fstream>
#include <iostream>

// Destructor to clean up the linked list
FileExplorer::~FileExplorer() {
    FolderNode* current = head;
    while (current != nullptr) {
        FolderNode* next = current->next;
        delete current;
        current = next;
    }
}

// Add a new folder to the linked list
void FileExplorer::addFolder(const std::string& folderName) {
    FolderNode* newNode = new FolderNode(folderName);
    newNode->next = head;
    head = newNode;
}

// Remove a folder from the linked list
void FileExplorer::removeFolder(const std::string& folderName) {
    FolderNode* current = head;
    FolderNode* prev = nullptr;

    while (current != nullptr && current->folderName != folderName) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return; // Folder not found

    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
}

// Display all folders in the linked list
void FileExplorer::displayFolders(std::ostream& out) const {
    FolderNode* current = head;
    while (current != nullptr) {
        out << current->folderName << std::endl;
        current = current->next;
    }
}

void FileExplorer::moveToHead(FolderNode* folder){
    FolderNode* current = head;
    FolderNode* prev = nullptr;
    while (current != nullptr && current != folder) {
        prev = current;
        current = current->next;
    }
    if (prev == nullptr) return;
    prev->next = current->next;
    current->next = head;
    head = current;
}

FileManager* FileExplorer::getFolderfiles(const std::string& folderName) {
    FolderNode* current = head;
    while (current != nullptr) {
        if (current->folderName == folderName) {
            moveToHead(current);
            return &current->fileManager;
        }
        current = current->next;
    }
    return nullptr; // Folder not found
}

// Generate DOT file for a single folder's tree
void generateDotFile(SplayTree<std::string>::Node* root, std::ofstream& out, const std::string& prefix) {
    if (!root) return;

    // Write the node itself
    if (root->left) {
        out << "    \"" << prefix << root->key << "\" -> \"" << prefix << root->left->key << "\";\n";
        generateDotFile(root->left, out, prefix);
    }
    if (root->right) {
        out << "    \"" << prefix << root->key << "\" -> \"" << prefix << root->right->key << "\";\n";
        generateDotFile(root->right, out, prefix);
    }
}

// Export the entire FileExplorer structure to a DOT file
void FileExplorer::exportToDot(const std::string& filename) const {
    std::ofstream out(filename);
    out << "digraph FileExplorer {\n";
    out << "    node [shape=folder];\n"; // Optional: Set node style for folders

    FolderNode* current = head;
    while (current != nullptr) {
        out << "    subgraph cluster_" << current->folderName << " {\n";
        out << "        label = \"" << current->folderName << "\";\n";
        out << "        node [shape=circle];\n"; // Optional: Set node style for files
        generateDotFile(current->fileManager.getRoot(), out, current->folderName + "_");
        out << "    }\n";
        current = current->next;
    }

    out << "}\n";
    out.close();
    std::cout << "DOT file exported to " << filename << std::endl;
}
