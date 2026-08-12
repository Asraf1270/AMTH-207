# 📄 C++ File I/O - Complete Reference Notes

## Table of Contents
1. [Introduction to File I/O](#1-introduction-to-file-io)
2. [Header Files & Classes](#2-header-files--classes)
3. [File Opening Modes](#3-file-opening-modes)
4. [Reading from Files](#4-reading-from-files)
5. [Writing to Files](#5-writing-to-files)
6. [File Position Pointers](#6-file-position-pointers)
7. [Error Handling](#7-error-handling)
8. [Binary File Operations](#8-binary-file-operations)
9. [Best Practices](#9-best-practices)
10. [Common Patterns](#10-common-patterns)
11. [Practice Problems](#11-practice-problems)
12. [Quick Reference](#12-quick-reference)

---

## 1. Introduction to File I/O

### What is File I/O?
File I/O (Input/Output) is the mechanism to read data from and write data to files stored on disk. It enables **data persistence** - saving information between program executions.

### Why Use File I/O?
- **Data Storage**: Save user data, settings, configurations
- **Data Processing**: Handle large datasets
- **Data Exchange**: Share information between applications
- **Logging**: Record program activities and errors
- **Backup**: Create backups of important data

### Key Concepts
```
Memory (RAM) ←→ Buffer ←→ File (Disk)
     ↑            ↑           ↑
  Program      Temporary    Permanent
               Storage      Storage
```

---

## 2. Header Files & Classes

### Required Header
```cpp
#include <fstream>  // Main file operations
#include <iostream> // For cin/cout
#include <string>   // For string handling
```

### Three Main Classes

| Class | Purpose | Direction |
|-------|---------|-----------|
| `ifstream` | Input File Stream | File → Program (READ) |
| `ofstream` | Output File Stream | Program → File (WRITE) |
| `fstream` | File Stream | Both READ & WRITE |

### Class Hierarchy
```
ios
 └── istream
 │    └── ifstream
 └── ostream
 │    └── ofstream
 └── iostream
      └── fstream
```

### Basic Object Creation
```cpp
ifstream inputFile;     // For reading
ofstream outputFile;    // For writing
fstream file;           // For both

// Or directly with filename
ifstream inputFile("data.txt");
ofstream outputFile("result.txt");
fstream file("info.txt");
```

---

## 3. File Opening Modes

### Mode Flags

| Flag | Description | Effect |
|------|-------------|--------|
| `ios::in` | Read | Open file for reading |
| `ios::out` | Write | Open file for writing (overwrites) |
| `ios::app` | Append | Write at end of file |
| `ios::ate` | At End | Start at end of file |
| `ios::trunc` | Truncate | Delete existing content |
| `ios::binary` | Binary | Open in binary mode |

### Mode Combinations
```cpp
// Most Common Combinations
ios::out              // Write mode (default for ofstream)
ios::in               // Read mode (default for ifstream)
ios::out | ios::app   // Append mode
ios::out | ios::trunc // Write (clear existing)
ios::in | ios::out    // Read and write
ios::in | ios::binary // Read binary file
ios::out | ios::binary // Write binary file
```

### Opening Files
```cpp
// Method 1: Constructor
ifstream file("data.txt");

// Method 2: Open function
ifstream file;
file.open("data.txt");

// Method 3: With mode
fstream file;
file.open("data.txt", ios::in | ios::out);

// Method 4: With mode and default
ofstream file("data.txt", ios::app);
```

---

## 4. Reading from Files

### Opening and Checking
```cpp
ifstream file("data.txt");

// Check if opened successfully
if (!file.is_open()) {
    cerr << "Error: Could not open file!" << endl;
    return 1;
}

// Alternative check
if (file.fail()) {
    cerr << "Error opening file!" << endl;
    return 1;
}
```

### Reading Methods

#### 1. Read Line by Line (Most Common)
```cpp
string line;
while (getline(file, line)) {
    cout << line << endl;
}
```

#### 2. Read Word by Word
```cpp
string word;
while (file >> word) {
    cout << word << endl;
}
```

#### 3. Read Character by Character
```cpp
char ch;
while (file.get(ch)) {
    cout << ch;
}
```

#### 4. Read Formatted Data
```cpp
// File: "John 25 72.5"
string name;
int age;
double score;
file >> name >> age >> score;
```

#### 5. Read Entire File at Once
```cpp
#include <sstream>
stringstream buffer;
buffer << file.rdbuf();
string content = buffer.str();
```

#### 6. Read Binary Data
```cpp
char buffer[1024];
file.read(buffer, sizeof(buffer));
int bytesRead = file.gcount();  // Actual bytes read
```

### EOF Detection
```cpp
// Method 1: Using eof() (Not recommended alone)
while (!file.eof()) {
    string line;
    getline(file, line);
    // Processing...
}

// Method 2: Check after reading (Recommended)
string line;
while (getline(file, line)) {
    // Process line
}

// Method 3: For formatted input
int num;
while (file >> num) {
    // Process num
}
```

---

## 5. Writing to Files

### Basic Writing
```cpp
ofstream file("output.txt");

if (file.is_open()) {
    file << "Hello World!" << endl;
    file << "Number: " << 42 << endl;
    file << "Pi: " << 3.14159 << endl;
    file.close();
}
```

### Formatted Writing
```cpp
#include <iomanip>

file << setw(10) << left << "Name"
     << setw(5) << "Age"
     << setw(10) << "City" << endl;

file << setw(10) << left << "John"
     << setw(5) << 25
     << setw(10) << "NYC" << endl;
```

### Append Mode
```cpp
ofstream file("log.txt", ios::app);
file << "Log entry at " << time << endl;
file.close();
```

### Writing Multiple Lines
```cpp
file << "Line 1\n"
     << "Line 2\n"
     << "Line 3\n";
```

### Binary Writing
```cpp
struct Student {
    char name[50];
    int roll;
    float marks;
};

Student s = {"Alice", 101, 95.5};
ofstream file("students.dat", ios::binary);
file.write((char*)&s, sizeof(Student));
file.close();
```

### Flushing Buffers
```cpp
file << data;
file.flush();        // Force write to disk
// OR
file << data << flush;
```

---

## 6. File Position Pointers

### Getting Current Position
```cpp
ifstream file("data.txt");

// For reading (get pointer)
streampos readPos = file.tellg();

// For writing (put pointer)
ofstream file2("data.txt");
streampos writePos = file2.tellp();
```

### Setting Position

#### Seek Functions
```cpp
// Seeking in input stream (ifstream)
file.seekg(0, ios::beg);        // Beginning
file.seekg(0, ios::end);        // End
file.seekg(-10, ios::cur);      // 10 bytes back from current

// Seeking in output stream (ofstream)
file.seekp(0, ios::beg);        // Beginning
file.seekp(0, ios::end);        // End
file.seekp(10, ios::cur);       // 10 bytes forward

// Both (fstream)
file.seekg(0, ios::beg);
file.seekp(0, ios::end);
```

### Common Positioning Operations
```cpp
// Get file size
file.seekg(0, ios::end);
streampos fileSize = file.tellg();
file.seekg(0, ios::beg);

// Read from specific position
file.seekg(100, ios::beg);  // Move to byte 100
string line;
getline(file, line);

// Rewind to beginning
file.seekg(0, ios::beg);
```

---

## 7. Error Handling

### Error States
```cpp
ifstream file("data.txt");

if (file.fail()) {
    // File couldn't be opened or operation failed
}

if (file.bad()) {
    // Serious error (e.g., hardware failure)
}

if (file.eof()) {
    // End of file reached
}

if (file.good()) {
    // No errors, file is ready
}
```

### Robust Error Handling
```cpp
#include <exception>

void safeFileOperation(const string& filename) {
    try {
        ifstream file(filename);
        
        if (!file.is_open()) {
            throw runtime_error("Could not open file: " + filename);
        }
        
        string line;
        while (getline(file, line)) {
            // Process line
        }
        
        file.close();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        // Log error or take corrective action
    }
}
```

### Checking File Existence
```cpp
#include <filesystem>  // C++17

if (filesystem::exists("data.txt")) {
    // File exists
    ifstream file("data.txt");
    // Process file
} else {
    cerr << "File not found!" << endl;
}

// Alternative without C++17
ifstream file("data.txt");
if (file.good()) {
    // File exists and is accessible
}
```

---

## 8. Binary File Operations

### Writing Binary Data
```cpp
struct Employee {
    int id;
    char name[50];
    double salary;
};

Employee emp = {101, "John Doe", 55000.0};

ofstream file("employees.dat", ios::binary);
if (file.is_open()) {
    file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    file.close();
}
```

### Reading Binary Data
```cpp
Employee emp;
ifstream file("employees.dat", ios::binary);
if (file.is_open()) {
    file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
    file.close();
    cout << "ID: " << emp.id << endl;
    cout << "Name: " << emp.name << endl;
    cout << "Salary: " << emp.salary << endl;
}
```

### Reading/Writing Arrays
```cpp
int numbers[] = {1, 2, 3, 4, 5};
ofstream file("numbers.dat", ios::binary);
file.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
file.close();

int readNumbers[5];
ifstream readFile("numbers.dat", ios::binary);
readFile.read(reinterpret_cast<char*>(readNumbers), sizeof(readNumbers));
```

### Important Notes for Binary Files
- Use `ios::binary` mode
- Use `reinterpret_cast<char*>` for conversion
- Track bytes read/written with `gcount()`
- Be careful with memory alignment/padding

---

## 9. Best Practices

### ✅ Do's

1. **Always Check File Opening**
```cpp
ifstream file("data.txt");
if (!file) {
    // Handle error
}
```

2. **Close Files Explicitly**
```cpp
file.close();  // Always close when done
```

3. **Use RAII (Resource Acquisition Is Initialization)**
```cpp
{
    ifstream file("data.txt");
    // File automatically closes when out of scope
}
```

4. **Validate Data After Reading**
```cpp
string line;
while (getline(file, line)) {
    if (line.empty()) continue;  // Skip empty lines
    // Process valid data
}
```

5. **Use Appropriate Stream Type**
```cpp
ifstream  // For reading only
ofstream  // For writing only
fstream   // For both (when needed)
```

6. **Handle Exceptions**
```cpp
file.exceptions(ifstream::failbit | ifstream::badbit);
try {
    // File operations
} catch (const ifstream::failure& e) {
    cerr << "File operation failed: " << e.what() << endl;
}
```

### ❌ Don'ts

1. **Don't Assume File Exists**
```cpp
❌ ifstream file("data.txt");
   file >> data;  // May crash if file doesn't exist
```

2. **Don't Use `while(!file.eof())` Alone**
```cpp
❌ while(!file.eof()) {
       getline(file, line);  // May process last line twice
   }
```

3. **Don't Ignore Return Values**
```cpp
❌ file.read(buffer, 100);  // Ignoring actual bytes read
   // Should check: int bytes = file.gcount();
```

4. **Don't Use C-Style File I/O in C++**
```cpp
❌ FILE* fp = fopen("data.txt", "r");
   // Use ifstream instead
```

5. **Don't Forget Error States**
```cpp
❌ file.open("data.txt");
   // Should check: if (file.is_open())
```

---

## 10. Common Patterns

### Pattern 1: Read and Process All Lines
```cpp
ifstream file("input.txt");
string line;

while (getline(file, line)) {
    // Process each line
    cout << "Line: " << line << endl;
}
file.close();
```

### Pattern 2: Read Formatted Data
```cpp
ifstream file("data.txt");
string name;
int age;
double score;

while (file >> name >> age >> score) {
    // Process each record
    cout << name << " " << age << " " << score << endl;
}
```

### Pattern 3: Copy File
```cpp
ifstream source("source.txt");
ofstream dest("destination.txt");
dest << source.rdbuf();  // Efficient copy
source.close();
dest.close();
```

### Pattern 4: Config File Reader
```cpp
map<string, string> readConfig(const string& filename) {
    map<string, string> config;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t pos = line.find('=');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            config[key] = value;
        }
    }
    return config;
}
```

### Pattern 5: CSV Reader
```cpp
vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}
```

### Pattern 6: Logger Class
```cpp
class Logger {
private:
    ofstream logFile;
public:
    Logger(const string& filename) {
        logFile.open(filename, ios::app);
    }
    
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    void log(const string& message) {
        if (logFile.is_open()) {
            logFile << "[" << time(nullptr) << "] " 
                    << message << endl;
        }
    }
};
```

---

## 11. Practice Problems

### 🟢 Beginner Problems

**Problem 1: File Copy**
```cpp
// Copy contents of one file to another
// Input: source.txt, destination.txt
// Output: destination.txt with same content
```

**Problem 2: Line Counter**
```cpp
// Count number of lines in a text file
// Input: filename.txt
// Output: Total lines
```

**Problem 3: Word Counter**
```cpp
// Count words in a text file
// Input: document.txt
// Output: Word count
```

### 🟡 Intermediate Problems

**Problem 4: Student Grades**
```cpp
// File format: Name, Score1, Score2, Score3
// Calculate average for each student
// Write to output file: Name, Average, Grade (A/B/C/D/F)
```

**Problem 5: Phone Book**
```cpp
// Create a phone book application
// Operations: Add, Search, Delete, List All
// Store in file: Name, Phone, Email
```

**Problem 6: Log File Analyzer**
```cpp
// Analyze server log file
// Count: Total requests, by status code
// Find: Most requested URL, IP addresses
// Output: Summary report
```

### 🔴 Advanced Problems

**Problem 7: Database System**
```cpp
// Implement a simple database
// CRUD operations (Create, Read, Update, Delete)
// Index support for fast searching
// Data validation and integrity checks
```

**Problem 8: File Compression**
```cpp
// Implement simple file compression
// Run-length encoding or Huffman coding
// Compress and decompress files
// Track compression ratio
```

**Problem 9: CSV to JSON Converter**
```cpp
// Convert CSV file to JSON format
// Handle nested structures
// Data type detection
// Pretty print output
```

**Problem 10: Encrypted File Storage**
```cpp
// Implement file encryption/decryption
// Caesar cipher or XOR encryption
// Password protection
// Key management
```

---

## 12. Quick Reference

### Include Files
```cpp
#include <fstream>     // File operations
#include <iostream>    // cout, cin
#include <string>      // string
#include <sstream>     // stringstream
#include <iomanip>     // formatting
```

### Class Summary
```cpp
ifstream in;    // Read from file
ofstream out;   // Write to file
fstream both;   // Read and write
```

### Common Methods
```cpp
// Opening
in.open("file.txt");
in.open("file.txt", ios::in);

// Checking
in.is_open()    // Returns bool
in.good()       // No errors
in.fail()       // Operation failed
in.eof()        // End of file

// Reading
getline(in, str)    // Read line
in >> var          // Formatted read
in.get(ch)         // Read char
in.read(buf, size) // Binary read

// Writing
out << data        // Write data
out.put(ch)        // Write char
out.write(buf, size) // Binary write

// Positioning
in.tellg()         // Get read position
in.seekg(pos)      // Set read position
out.tellp()        // Get write position
out.seekp(pos)     // Set write position

// Closing
in.close()
out.close()
```

### File Opening Modes Quick Reference
```cpp
ios::in       // Read
ios::out      // Write
ios::app      // Append
ios::ate      // At end
ios::trunc    // Truncate
ios::binary   // Binary
```

### Error Handling Template
```cpp
ifstream file("data.txt");
if (!file.is_open()) {
    cerr << "Error opening file!" << endl;
    return 1;
}
// Process file
file.close();
```

### File Read/Write Template
```cpp
// Read
ifstream inFile("input.txt");
string line;
while (getline(inFile, line)) {
    // Process line
}
inFile.close();

// Write
ofstream outFile("output.txt");
outFile << "Data" << endl;
outFile.close();
```

### Memory-Efficient Processing
```cpp
// Process line by line (good for large files)
ifstream file("large.txt");
string line;
while (getline(file, line)) {
    // Process one line at a time
}
```

### Common Error Messages
```
"file not found"      → Check path and filename
"permission denied"   → Check file permissions
"device full"        → Check disk space
"bad file descriptor" → File was closed or invalid
"file exists"         → Can't create new with same name
```

---

## Final Checklist ✓

Before submitting file I/O code, verify:

- [ ] Included `<fstream>` header
- [ ] Created appropriate stream object (ifstream/ofstream/fstream)
- [ ] Checked if file opened successfully (`is_open()`)
- [ ] Handled errors appropriately
- [ ] Used correct file modes
- [ ] Performed read/write operations correctly
- [ ] Closed the file after operations
- [ ] Considered edge cases (empty file, large files)
- [ ] Validated data read from file
- [ ] Added comments for clarity
- [ ] Tested with sample files
- [ ] Considered performance for large files

---

**Note**: This reference guide covers the most commonly used file I/O operations in C++. Practice regularly with different file types and operations to build confidence and expertise. Remember that file I/O is a fundamental skill for any C++ programmer!