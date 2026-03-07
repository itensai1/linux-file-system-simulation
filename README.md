# Linux File System Simulation

A **Linux-like File System simulator written in C** that mimics basic shell commands and directory operations using an **in-memory tree structure**.

This project demonstrates how a hierarchical file system works internally by implementing commands such as `mkdir`, `cd`, `ls`, `pwd`, `touch`, and others.

The system maintains a **virtual file tree**, allowing users to navigate directories, create files, remove directories, and save/load the structure from disk.

---

# Features

The simulator supports a set of common file system commands similar to Linux.

| Command           | Description                         |
| ----------------- | ----------------------------------- |
| `mkdir path`      | Create a directory                  |
| `rmdir path`      | Remove an empty directory           |
| `ls path`         | List contents of a directory        |
| `cd path`         | Change current directory            |
| `pwd`             | Print working directory             |
| `touch path`      | Create a file                       |
| `rm path`         | Remove a file                       |
| `save filename`   | Save the file system tree to a file |
| `reload filename` | Reconstruct the tree from a file    |
| `menu`            | Display all commands                |
| `quit`            | Exit the program                    |

---

# How It Works

The virtual file system is implemented using a **tree data structure** where:

* Each **directory or file is a node**
* Directories can contain **multiple children**
* Every node has a **pointer to its parent**

The system begins with a single root directory:

```
/
```

Example virtual structure:

```
/
└── home
    ├── user1
    │   ├── INFO
    │   └── codes
    │       ├── cpp
    │       │   └── proj.cpp
    │       ├── python
    │       │   └── proj.py
    │       └── java
    │           └── proj.java
    │
    └── user2
        └── uni
            ├── sec1
            └── sec2
```

---

# Data Structure

Each file system object is represented using the following structure:

```
struct NODE
{
    char name[64];          // name of file or directory
    char type;              // 'D' = Directory, 'F' = File
    int childrenNum;        // number of children
    struct NODE *children[MAX_CHILDREN];
    struct NODE *parentPtr; // pointer to parent node
};
```

Important pointers:

* `root` → root directory
* `cwd` → current working directory
* `tmp` → temporary traversal pointer

---

# Path Handling

The simulator supports:

### Absolute Paths

```
mkdir /home/user1
touch /home/user1/file.txt
```

### Relative Paths

```
mkdir projects
cd ../codes
```

### Special Path Symbols

| Symbol | Meaning           |
| ------ | ----------------- |
| `.`    | Current directory |
| `..`   | Parent directory  |
| `/`    | Root directory    |

---

# Saving the File System

The file system can be exported to a file using:

```
save sysTree.txt
```

The output file will contain the structure in the following format:

```
type  path
----  ----
D     /
D     /home
D     /home/user1
D     /home/user1/codes
D     /home/user1/codes/cpp
F     /home/user1/codes/cpp/proj.cpp
D     /home/user1/codes/python
F     /home/user1/codes/python/proj.py
D     /home/user1/codes/java
F     /home/user1/codes/java/proj.java
F     /home/user1/INFO
D     /home/user2
D     /home/user2/uni
F     /home/user2/uni/sec1
F     /home/user2/uni/sec2
```

Where:

* `D` represents a **Directory**
* `F` represents a **File**

---

# Reloading a Saved Tree

To reconstruct the file system:

```
reload sysTree.txt
```

The program reads each entry and recreates the directories and files in memory.

---

# Compilation

Compile using **GCC**:

```
gcc main.c -o vfs
```

Run the program:

```
./vfs
```

---

# Example Session

```
input a command line: mkdir home
directory 'home' created!

input a command line: cd home

input a command line: mkdir user1
directory 'user1' created!

input a command line: touch INFO
file 'INFO' created!

input a command line: pwd
>> /home/user1
```

---

# Learning Objectives

This project helps understand:

* Tree data structures
* File system hierarchy
* Path resolution
* Recursive traversal
* Memory management in C
* Basic shell command simulation

---
