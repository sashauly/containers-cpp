# containers-cpp

> Implementation of the containers.h library.

## Table of Contents

- [containers-cpp](#containers-cpp)
  - [Table of Contents](#table-of-contents)
    - [Introduction](#introduction)
  - [Task](#task)
    - [Part 1. Implementation of the containers.h library](#part-1-implementation-of-the-containersh-library)
    - [Part 2. Bonus. Implementation of the containersplus.h library](#part-2-bonus-implementation-of-the-containersplush-library)
    - [Part 3. Bonus. Implementation of the modified `emplace` methods](#part-3-bonus-implementation-of-the-modified-emplace-methods)

### Introduction

As part of the project you need to write your own library that implements the basic standard C++ container classes: `list`, `map`, `queue`, `set`, `stack` and `vector`. Implementations should provide a full set of standard methods and attributes for element handling, container capacity checking and iteration. As a bonus, you can also implement several other container classes from the C++ container library that are not as commonly used, but differ in their implementation details.

Each type of containers should provide the user with the following methods:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialization list, see materials);

- methods for accessing container elements (e.g. accessing an element with the index i);

- methods for checking if a container is full (e.g. the number of elements in the container, check if the container is empty);

- methods for changing the container (removing and adding new elements, cleaning the container);

- methods for dealing with the container iterator.

There are two main types of containers: sequence and associative containers. To find an element in sequence containers (`list`, `vector`, `array`, `stack`, `queue`), you have to look through the container one by one, while in associative containers (`map`, `set`, `multiset`) you just need to look through the key associated with the value.

## Task

- The program must be developed in C++ language of C++17 standard using gcc compiler
- The program code must be located in the src folder
- When writing code it is necessary to follow the Google style
- Make sure to use iterators
- Classes must be template
- Classes must be implemented within the `s21` namespace
- Prepare full coverage of container classes methods with unit-tests using the GTest library
- Copying of the Standard Template Library (STL) implementation is not allowed
- The logic of the Standard Template Library (STL) must be followed (in terms of checks, memory handling and behaviour in abnormal situations)

### Part 1. Implementation of the containers.h library

You need to implement the `containers.h` library classes (specifications are given in the relevant material sections, see **"Main containers"**). \
List of classes: `list`, `map`, `queue`, `set`, `stack`, `vector`.

- Make it as a header file `containers.h` which includes different header files with implementations of the specified containers (`list.h`, `map.h` and etc.)
- Provide a Makefile for testing the library (with targets clean, test)
- The classical implementation of containers should be considered as a basis, but the final choice of implementations remains free. Except for the list - it should be implemented via the list structure rather than the array

*Tip*: You can move the same implementation of container methods to base classes. For example, for a queue and a stack, or for a list and a vector. There is a UML diagram of the STL library in materials as *one possible example* of hierarchical construction. However, your implementation does not have to be strictly tied to this UML diagram.

### Part 2. Bonus. Implementation of the containersplus.h library

You need to implement the `containersplus.h` library functions (see **"Additional containers"** for specifications). \
List of classes to be implemented additionally: `array`, `multiset`.

- Make it as a header file `containersplus.h` which includes different header files with implementations of the specified containers (`array.h`, `multiset.h`)
- Provide a Makefile for testing the library (with targets clean, test)
- The classical implementation of containers should be considered as a basis, but the final choice of the algorithm remains free.

### Part 3. Bonus. Implementation of the modified `emplace` methods

You need to complete the classes with the appropriate methods, according to the table:

| Modifiers                                                  | Definition                                                    | Containers          |
| ---------------------------------------------------------- | ------------------------------------------------------------- | ------------------- |
| `iterator emplace(const_iterator pos, Args&&... args)`     | inserts new elements into the container directly before `pos` | List, Vector        |
| `void emplace_back(Args&&... args)`                        | appends new elements to the end of the container              | List, Vector, Queue |
| `void emplace_front(Args&&... args)`                       | appends new elements to the top of the container              | List, Stack         |
| `vector<std::pair<iterator,bool>> emplace(Args&&... args)` | inserts new elements into the container                       | Map, Set, Multiset  |

Note: the arguments are the already created elements of the appropriate container that should be inserted into this container.

*Tip 1*: notice that each of these methods uses an Args&&... args - Parameter pack construct. This construct allows a variable number of parameters to be passed to a function or method. So, when calling a method defined as `iterator emplace(const_iterator pos, Args&&... args)`, you can write either `emplace(pos, arg1, arg2)` or `emplace(pos, arg1, arg2, arg3)`.

*Tip 2*: remember to test methods for different cases, including boundary ones.
