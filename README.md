<div align="left">
  <img title="CppProjectInitializer" src="./assets/icon.svg" alt="icon" align="left" width="100" style="padding-right: 1ch">
  <h1>CppProjectInitializer</h1>
   <p><strong>CppFilesGeneratorWithCMake is a simple C++ script that generates source (.cpp) files, header (.hpp) files, and test (.cpp) files in their respective folders, and updates the CMakeLists.txt file to automatically add the generated files to the CMake project.</strong></p>
</div>

## Introduction

This project is an example tool for generating C++ source and header files along with test files to quickly create new problems or development tasks. Allows you to automatically add generated files to the CMakeLists.txt file, allowing you to easily manage your projects in CMake.

## An example of the project structure that is used:
```
include/
    file.hpp
problems/
    file.cpp
uts/
    file_tests.cpp
templates_for_script/
    for_cpp.txt
    for_hpp.txt
    for_tests.txt
CMakeLists.txt
```

## Requirements

The cmake file should contain:
```
set(HEADERS ..)

set(SOURCES ..)

set(UTS ..)
```

## There is a demonstration version in the "example" folder!

## How to compile?

``` 
g++ Initializer.cpp -o initializer
and run:
./initialzier
```

