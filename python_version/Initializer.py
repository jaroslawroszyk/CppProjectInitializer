import os


def is_exist(path_to_problems, path_to_headers, path_to_tests):
    return os.path.exists(path_to_problems) or os.path.exists(
        path_to_headers) or os.path.exists(path_to_tests)


def create_file(path, content="1"):
    with open(path, "w") as file:
        file.write(content)


def write_content_to_file(path_to_template):
    header_content = ""
    with open(path_to_template, "r") as template:
        header_content = template.read()
    return header_content


def write_file_name_to_Cmake(file_name):
    cmake_content = ""
    with open("CMakeLists.txt", "r") as cmake_file:
        cmake_content = cmake_file.readlines()

    with open("CMakeLists.txt", "w") as cmake_file:
        for line in cmake_content:
            cmake_file.write(line)
            if line.startswith("set(HEADERS"):
                cmake_file.write(f"\tinclude/{file_name}.hpp\n")
            elif line.startswith("set(SOURCES"):
                cmake_file.write(f"\tproblems/{file_name}.cpp\n")
            elif line.startswith("set(UTS"):
                cmake_file.write(f"\tuts/{file_name}_tests.cpp\n")


print("The script creates files with the name entered by the user. (file_name.hpp, file_name.cpp, file_name_test.cpp), and save to CMakeList")
file_name = input("Enter file name: ")

path_to_problems = os.path.join("problems", f"{file_name}.cpp")
path_to_headers = os.path.join("include", f"{file_name}.hpp")
path_to_tests = os.path.join("uts", f"{file_name}_test.cpp")

if is_exist(path_to_problems, path_to_headers, path_to_tests):
    print("File exist!")
else:

    create_file(path_to_problems, write_content_to_file(
        "templates_for_script/for_cpp.txt"))
    create_file(path_to_headers,  write_content_to_file(
        "templates_for_script/for_headers.txt"))
    create_file(path_to_tests,  write_content_to_file(
        "templates_for_script/for_tests.txt"))
    print(f"Files {file_name}.cpp, {file_name}.hpp, {file_name}_tests.hpp ave been added to src/, include/ and uts/ folders")
    write_file_name_to_Cmake(file_name)
