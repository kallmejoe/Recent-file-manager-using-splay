# SplayTree and FileManager Documentation

## Introduction
This documentation provides an overview of the `SplayTree` and `FileManager` classes implemented in C++.  
The `SplayTree` is a self-adjusting binary search tree with basic operations like insert, remove, and splay.  
The `FileManager` class uses the `SplayTree` to manage files efficiently.

---

## SplayTree Class

The `SplayTree` class is a templated data structure that provides the following functionalities:

### Public Functions:

1. **`insert(const T& key)`**
   - **Description**: Inserts a new key into the tree, splaying it to the root.
   - **Input**: A key of type `T` to be inserted.

2. **`remove(const T& key)`**
   - **Description**: Removes a key from the tree if it exists, splaying the tree around the key during the process.
   - **Input**: A key of type `T` to be removed.

3. **`splay(const T& key)`**
   - **Description**: Splays the tree around the given key, making it the root if it exists.
   - **Input**: A key of type `T` to splay around.

4. **`access(const T& key)`**
   - **Description**: Accesses a key in the tree, splaying it to the root and updating its timestamp.
   - **Input**: A key of type `T` to access.

5. **`inorder(std::ostream& out)`**
   - **Description**: Prints the keys in the tree in sorted order using full inorder traversal.
   - **Input**: An output stream (`std::ostream&`) for printing.

6. **`inorder(std::ostream& out, int maxDepth)`**
   - **Description**: Prints keys in sorted order up to a specified depth using depth-limited inorder traversal.
   - **Input**: An output stream (`std::ostream&`) and a maximum depth (`int`).

---

### Private Helper Functions:

1. **`rightRotate(Node* x)`**
   - **Description**: Performs a right rotation on the given subtree.
   - **Input**: A pointer to the root of the subtree (`Node*`).
   - **Output**: A pointer to the new root of the subtree (`Node*`).

2. **`leftRotate(Node* x)`**
   - **Description**: Performs a left rotation on the given subtree.
   - **Input**: A pointer to the root of the subtree (`Node*`).
   - **Output**: A pointer to the new root of the subtree (`Node*`).

3. **`splayHelper(Node* subtreeRoot, const T& key)`**
   - **Description**: Recursively splay the tree around the given key.
   - **Input**: A pointer to the subtree root (`Node*`) and the key to splay around (`T&`).
   - **Output**: A pointer to the new root of the splayed subtree (`Node*`).

4. **`deleteTree(Node* subtreeRoot)`**
   - **Description**: Recursively deletes all nodes in the subtree.
   - **Input**: A pointer to the subtree root (`Node*`).

---

## FileManager Class

The `FileManager` class utilizes a `SplayTree` to manage file access. It provides the following operations:

1. **`addFile(const std::string& fileName)`**
   - **Description**: Adds a file to the tree by its name.
   - **Input**: A string (`std::string&`) representing the file name.

2. **`accessFile(const std::string& fileName)`**
   - **Description**: Accesses a file, splaying it to the root and updating its timestamp.
   - **Input**: A string (`std::string&`) representing the file name.

3. **`removeFile(const std::string& fileName)`**
   - **Description**: Removes a file by its name if it exists in the tree.
   - **Input**: A string (`std::string&`) representing the file name.

4. **`displayAll(std::ostream& out)`**
   - **Description**: Displays all file names in the tree using full inorder traversal.
   - **Input**: An output stream (`std::ostream&`) for printing.

5. **`display(std::ostream& out, int maxDepth)`**
   - **Description**: Displays file names up to a specified depth in the tree.
   - **Input**: An output stream (`std::ostream&`) for printing and a maximum depth (`int`).

---

## Depth-aware Inorder Traversal

The `SplayTree` class supports a depth-aware inorder traversal through the `inorder` method, which can be called with or without a depth limit.  
This is useful for applications that require partial views of the tree.

---

## Conclusion

This implementation combines the efficiency of Splay Trees with a practical use case for file management.  
It provides a robust framework for managing and accessing data with a focus on recently used items.
