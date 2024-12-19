#include "FileManager.cpp"
#include <iostream>



int main() {
    FileManager fileManager;
    fileManager.addFile("file1");
    fileManager.addFile("file2");
    fileManager.addFile("file3");
    fileManager.addFile("file4");
    fileManager.addFile("file5");
    fileManager.display(cout,5);
    fileManager.removeFile("file1");
    fileManager.display(cout,5);
    cout<<endl;
    // fileManager.accessFile("file2");
    // fileManager.display(cout,3);
    // fileManager.display(cout,2);
    // fileManager.accessFile("file1");
    // fileManager.display(cout,2);
    return 0;

    while(true){

    }
}
