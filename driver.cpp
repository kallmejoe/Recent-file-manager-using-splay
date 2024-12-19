#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <string>
#include "FileManager.cpp" // Include user-defined headers last
using namespace std;

bool openFile(std::wstring& fullPath, std::wstring& fileName) {
    OPENFILENAMEW ofn;               // Structure to configure the dialog box
    wchar_t fileBuffer[MAX_PATH] = L""; // Buffer to store the selected file path

    // Initialize the OPENFILENAME structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;               // No parent window
    ofn.lpstrFile = fileBuffer;         // Buffer to store the full file path
    ofn.nMaxFile = MAX_PATH;            // Buffer size
    ofn.lpstrFilter = L"All Files\0*.\0Text Files\0.TXT\0"; // File filters
    ofn.nFilterIndex = 1;               // Default filter index
    ofn.lpstrFileTitle = NULL;          // Will fetch file name separately
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;         // Default directory
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Show the Open File Dialog
    if (GetOpenFileNameW(&ofn)) {
        // Save the full path
        fullPath = fileBuffer;

        // Extract the file name from the full path
        std::wstring tempPath(fileBuffer);
        size_t pos = tempPath.find_last_of(L"\\/");
        if (pos != std::wstring::npos) {
            fileName = tempPath.substr(pos + 1); // File name only
        }
        else {
            fileName = tempPath; // If no directory separator found
        }

        return true; // File selection succeeded
    }
    else {
        return false;
    }
}


int main() {
    FileManager fileManager;
    fileManager.addFile("file1");
    fileManager.addFile("file2");
    fileManager.addFile("file3");
    fileManager.addFile("file4");
    fileManager.addFile("file5");
    fileManager.display(cout, 5);
    fileManager.removeFile("file1");
    fileManager.display(cout, 5);
    cout << endl;

    while (true) {
        system("cls"); // Use "cls" for Windows
        cout<<"Your Current Files"<<endl;
        fileManager.display(cout,5);
        cout << "\t Dashboard \t" << endl;
        cout << "\t 1 - Insert a file \t" << endl;
        cout << "\t 2 - Delete a file \t" << endl;
        cout << "\t 3 - Access a file \t" << endl;
        cout << "\t 4 - Recently Accesed Files \t" << endl;
        cout << "\t 5 - Exit \t" << endl;
        cout<<endl;
        cout << "Enter your choice: ";


        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number." << endl;
            system("pause");
            continue;
        }

        switch (choice) {
        case 1: {
            string newFile;
            cout << "Enter the name of the file to insert: ";
            cin>>newFile;
            fileManager.addFile(newFile);
            fileManager.display(cout, 5);
            break;
        }
        case 2: {
            string fileToDelete;
            cout << "Enter the name of the file to delete: ";
            cin >> fileToDelete;
            fileManager.removeFile(fileToDelete);
            fileManager.display(cout, 5);
            break;
        }
        case 3: {
            string fileToAccess;
            cout << "Enter the name of the file to access: ";
            cin >> fileToAccess;
            fileManager.accessFile(fileToAccess); // Assuming FileManager has this function
            fileManager.display(cout, 5);
            break;
        }
        case 4: {
            fileManager.display(cout,3);
        }
        case 5:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice. Please select an option between 1 and 4." << endl;
            break;
        }
        system("pause");
    }

    return 0;
}
