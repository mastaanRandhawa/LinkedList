Linked List Implementation in C
This project is a C-based implementation of a dynamic linked list, designed for handling lists of data with efficient memory management and customizable functionality. It includes essential operations like insertion, deletion, traversal, and searching. The project is structured to allow users to build, test, and extend linked list features easily.

Key Components:
list.c and list.h: These files contain the core implementation of linked list operations, including:

Adding nodes to the beginning or end of the list.
Removing nodes by value or position.
Searching for specific data within the list.
Traversing and printing list contents.
Freeing memory to prevent leaks.
test_list.c: This file provides a suite of tests to validate the linked list’s functionality. It includes test cases for each major function, helping ensure reliability and correctness in typical use scenarios.

Makefile: This file automates the compilation process. Run make to compile all necessary files and generate an executable for testing the linked list. It simplifies building and linking by handling dependencies and flags.

Usage:
Compilation: Use the command make in the project directory. This will:

Compile list.c and test_list.c into object files.
Link them to create an executable named test_list.
Running Tests: Execute ./test_list to run the included tests. The output will display results for each operation, indicating whether each function behaves as expected.

Customization: The modular design allows you to expand functionality or adapt it to handle specific data types by modifying list.h and implementing additional functions in list.c.

Technologies Used:
C Language: Provides low-level control and memory management, allowing efficient data structure manipulation.
Makefile: Ensures seamless compilation, linking, and rebuilding, making it easy to manage dependencies in the project.
Example Use Cases:
This linked list implementation can serve as a foundation for more complex data structures or can be integrated into other C projects that require flexible, dynamic list management. The test suite demonstrates how to extend the functionality to suit different applications.
