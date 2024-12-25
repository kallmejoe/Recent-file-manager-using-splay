#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// #include <windows.h>
// #include <commdlg.h>
#include <iostream>
#include <fstream>
#include "splay.h"
#include <string>
#include "FileManager.cpp" // Include user-defined headers last
#include "FileExplorer.cpp" // Include FileExplorer
using namespace std;

// bool openFile(std::wstring& fullPath, std::wstring& fileName) {
//     OPENFILENAMEW ofn;               // Structure to configure the dialog box
//     wchar_t fileBuffer[MAX_PATH] = L""; // Buffer to store the selected file path

//     // Initialize the OPENFILENAME structure
//     ZeroMemory(&ofn, sizeof(ofn));
//     ofn.lStructSize = sizeof(ofn);
//     ofn.hwndOwnser = NULL;               // No parent window
//     ofn.lpstrFile = fileBuffer;         // Buffer to store the full file path
//     ofn.nMaxFile = MAX_PATH;            // Buffer size
//     ofn.lpstrFilter = L"All Files\0*.\0Text Files\0.TXT\0"; // File filters
//     ofn.nFilterIndex = 1;               // Default filter index
//     ofn.lpstrFileTitle = NULL;          // Will fetch file name separately
//     ofn.nMaxFileTitle = 0;
//     ofn.lpstrInitialDir = NULL;         // Default directory
//     ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

//     // Show the Open File Dialog
//     if (GetOpenFileNameW(&ofn)) {
//         // Save the full path
//         fullPath = fileBuffer;

//         // Extract the file name from the full path
//         std::wstring tempPath(fileBuffer);
//         size_t pos = tempPath.find_last_of(L"\\/");
//         if (pos != std::wstring::npos) {
//             fileName = tempPath.substr(pos + 1); // File name only
//         }
//         else {
//             fileName = tempPath; // If no directory separator found
//         }

//         return true; // File selection succeeded
//     }
//     else {
//         return false;
//     }
// }

void FolderDashboard(FileManager* fm,FileExplorer& fileExplorer);

// Export the tree to a DOT file
void exportTreeToDot(SplayTree<std::string>::Node* root, const string& filename, const string& prefix) {
    ofstream out(filename);
    out << "digraph BST {\n";
    out << "    node [shape=circle];\n"; // Optional: Set node style
    generateDotFile(root, out, prefix);
    out << "}\n";
    out.close();
    cout << "DOT file exported to " << filename << endl;
}


void mainDashboard(FileExplorer& fileExplorer) {
    fileExplorer.exportToDot("fileManager.dot");
    system("dot -Tpng fileManager.dot -o tree.png");
    while (true) {
        system("clear");
        cout << "Your Current Folders and Files" << endl;
        fileExplorer.displayFolders(cout);
        cout << "\t Dashboard \t" << endl;
        cout << "\t 1 - Insert a folder \t" << endl;
        cout << "\t 2 - Delete a folder \t" << endl;
        cout << "\t 3 - Access a folder \t" << endl;
        cout << "\t 4 - Add a file to a folder \t" << endl;
        cout << "\t 5 - Remove a file from a folder \t" << endl;
        cout << "\t 6 - Export to DOT file \t" << endl;
        cout << "\t 7 - Exit \t" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        string s;
        FileManager* fm = nullptr;
        switch (choice) {
            case 1:
                cout << "Enter the name of the folder to insert: ";
                cin >> s;
                fileExplorer.addFolder(s);
                break;
            case 2:
                cout << "Enter the name of the folder to delete: ";
                cin >> s;
                fileExplorer.removeFolder(s);
                break;
            case 3:
                cout << "Enter the name of the folder to access: ";
                cin >> s;
                fm = fileExplorer.getFolderfiles(s);
                if (fm) {
                    FolderDashboard(fm,fileExplorer);
                } else {
                    cout << "Folder not found." << endl;
                }
                break;
            case 4:
                cout << "Enter the name of the folder: ";
                cin >> s;
                fm = fileExplorer.getFolderfiles(s);
                if (fm) {
                    cout << "Enter the name of the file to add: ";
                    cin >> s;
                    fm->addFile(s);
                } else {
                    cout << "Folder not found." << endl;
                }
                break;
            case 5:
                cout << "Enter the name of the folder: ";
                cin >> s;
                fm = fileExplorer.getFolderfiles(s);
                if (fm) {
                    cout << "Enter the name of the file to remove: ";
                    cin >> s;
                    fm->removeFile(s);
                } else {
                    cout << "Folder not found." << endl;
                }
                break;
            case 6:
                fileExplorer.exportToDot("fileExplorer.dot");
                break;
            case 7:
                cout << "Exiting the program. Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please select an option between 1 and 7." << endl;
                break;
        }
        system("pause");
    }
}

void FolderDashboard(FileManager* fm,FileExplorer& fileExplorer) {
    exportTreeToDot(fm->getRoot(), "fileManager.dot", "fileManager_");
    system("dot -Tpng fileManager.dot -o tree.png");
    while (true) {

        system("clear");
        cout << "\t Dashboard  \t" << endl;
        cout << "\t 1 - Insert a file \t" << endl;
        cout << "\t 2 - Delete a file \t" << endl;
        cout << "\t 3 - Access a file \t" << endl;
        cout << "\t 4 - Remove a file from a folder \t" << endl;
        cout << "\t 5 - Move to another folder \t" << endl;
        cout << "\t 6 - Display all files \t" << endl;
        cout << "\t 7 - Return \t" << endl;
        cout << "\t 8 - Exit \t" << endl;
        cout << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        string s;
        FileManager* fm2 = nullptr;
        switch (choice) {
            case 1:
                cout << "Enter the name of the file to insert: ";
                cin >> s;
                fm->addFile(s);
                exportTreeToDot(fm->getRoot(), "fileManager.dot", "fileManager_");
                system("dot -Tpng fileManager.dot -o tree.png");
                break;
            case 2:
                cout << "Enter the name of the file to delete: ";
                cin >> s;
                fm->removeFile(s);
                exportTreeToDot(fm->getRoot(), "fileManager.dot", "fileManager_");
                system("dot -Tpng fileManager.dot -o tree.png");
                break;
            case 3:
                cout << "Enter the name of the file to access: ";
                cin >> s;
                fm->accessFile(s);
                exportTreeToDot(fm->getRoot(), "fileManager.dot", "fileManager_");
                system("dot -Tpng fileManager.dot -o tree.png");
                break;
            case 4:
                cout << "Enter the name of the file to remove: ";
                cin >> s;
                fm->removeFile(s);
                break;
            case 5:
                cout<<"Enter the name of the folder to move to: ";
                cin>>s;
                fm2 = fileExplorer.getFolderfiles(s);

                cout<<"Enter the name of the file to move: ";
                cin>>s;
                if (fm2) {
                    fm2->addFile(s);
                } else {
                    cout << "Folder not found." << endl;
                }
                fm->removeFile(s);
                FolderDashboard(fm2,fileExplorer);
                break;
            case 6:
                fm->displayAll(cout);
                break;
            case 7:
                mainDashboard(fileExplorer);
                return;
            case 8:
                cout << "Exiting the program. Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please select an option between 1 and 8." << endl;
                break;
        }
        system("pause");
    }
}



int main() {
    FileExplorer fileExplorer;
    fileExplorer.addFolder("Folder1");
    fileExplorer.addFolder("Folder2");

    FileManager* fm1 = fileExplorer.getFolderfiles("Folder1");
    FileManager* fm2 = fileExplorer.getFolderfiles("Folder2");

    if (fm1) {
        fm1->addFile("file1");
        fm1->addFile("file2");
    }

    if (fm2) {
        fm2->addFile("file3");
        fm2->addFile("file4");
    }

    mainDashboard(fileExplorer);

    return 0;
}
