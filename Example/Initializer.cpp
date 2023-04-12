#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

auto is_exist(const std::string &path_to_problems, const std::string &path_to_headers, const std::string &path_to_tests) -> bool
{
    return std::ifstream(path_to_problems).good() || std::ifstream(path_to_headers).good() || std::ifstream(path_to_tests).good();
}

auto create_file(const std::string &path, const std::string &content = "foo") -> void
{
    std::ofstream file(path);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}

auto read_content_from_file(const std::string &path_to_template) -> std::string 
{
    std::ifstream template_file(path_to_template);
    if(not template_file)
    {
        std::cerr << "ops failed to open file: " << path_to_template << '\n';
        return "";
    }
    std::stringstream buffer;
    buffer << template_file.rdbuf();
    template_file.close();
    return buffer.str();
}

auto write_content_from_file_to_Cmake(const std::string &file_name) -> void
{
    std::ifstream cmake_file("CMakeLists.txt");
    std::string cmake_content((std::istreambuf_iterator<char>(cmake_file)),
                              (std::istreambuf_iterator<char>()));
    cmake_file.close();

    std::ofstream cmake_file_out("CMakeLists.txt");
    if (cmake_file_out.is_open())
    {
        std::istringstream iss(cmake_content);
        std::string line;
        while (std::getline(iss, line))
        {
            cmake_file_out << line << std::endl;
            if (line.find("set(HEADERS") != std::string::npos)
            {
                cmake_file_out << "\tinclude/" << file_name << ".hpp" << std::endl;
            }
            else if (line.find("set(SOURCES") != std::string::npos)
            {
                cmake_file_out << "\tproblems/" << file_name << ".cpp" << std::endl;
            }
            else if (line.find("set(UTS") != std::string::npos)
            {
                cmake_file_out << "\tuts/" << file_name << "_tests.cpp" << std::endl;
            }
        }
        cmake_file_out.close();
    }
}

int main()
{
    std::cout << "The script creates files with the name entered by the user (file_name.hpp, file_name.cpp, file_name_test.cpp), and saves them to CMakeLists.txt" << std::endl;
    std::string file_name{};
    std::cout << "Enter file name: ";
    std::cin >> file_name;

    std::string path_to_problems = "problems/" + file_name + ".cpp";
    std::string path_to_headers = "include/" + file_name + ".hpp";
    auto path_to_tests = "uts/" + file_name + "_tests.cpp";

    if (is_exist(path_to_problems, path_to_headers, path_to_tests))
    {
        std::cout << "File already exists!" << std::endl;
    }
    else
    {
        create_file(path_to_problems, read_content_from_file("templates_for_script/for_cpp.txt"));
        create_file(path_to_headers, read_content_from_file("templates_for_script/for_hpp.txt"));
        create_file(path_to_tests, read_content_from_file("templates_for_script/for_tests.txt"));
        std::cout << "Files " << file_name << ".cpp, " << file_name << ".hpp, " << file_name << "_tests.hpp have been added to src/, include/ and uts/ folders";
        write_content_from_file_to_Cmake(file_name); 
    }
}