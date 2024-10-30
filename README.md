# Linked List Implementation in C

A dynamic linked list implementation in C, designed for efficient memory management and customizable functionality. This project includes core linked list operations, a test suite, and a Makefile for easy compilation.

## Project Structure

- **`list.c`** and **`list.h`**: Core files containing linked list functions:
  - **Insertion**: Add nodes at the beginning or end of the list.
  - **Deletion**: Remove nodes by value or position.
  - **Search**: Locate specific data within the list.
  - **Traversal**: Print or process each node in the list.
  - **Memory Management**: Free nodes to prevent memory leaks.

- **`test_list.c`**: A test suite that verifies the functionality of each list operation with example use cases.

- **`Makefile`**: Automates compilation. Running `make` compiles all files and creates an executable for testing.

## Getting Started

### Prerequisites
- **C Compiler**: Ensure you have GCC or another C compiler installed.

### Compilation
In the project directory, run:
```bash
make
```
This will:
  - Compile `list.c` and `test_list.c` into object files.
  - Link them to create an executable named `test_list`.

### Running Tests
To run the test suite and validate the linked list operations:
```bash
./test_list
```
The output will show results for each operation, verifying that each function works as expected.

## Usage

- The linked list can be expanded or adapted by modifying `list.h` for different data types or by adding new functions in `list.c`.
- Integrate it into other C projects that require dynamic list management or further customize it for specific needs.

## Technologies Used

- **C Language**: Efficient, low-level programming for direct memory management.
- **Makefile**: Simplifies build process and dependency management.

## Example Use Cases

This linked list can serve as a foundational data structure or be integrated into projects that need flexible, dynamic list management. The included tests provide examples for common operations, and the modular design makes it easy to extend or adapt.
