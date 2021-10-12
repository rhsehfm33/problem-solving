#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace tool_filesystem
{
    void print_overwrite_warning_message(const std::string &filePath)
    {
        std::cout << filePath << " " << "already exists! It will overwrite!" << std::endl;
    }

    void string_system(const std::string &command)
    {
        system(command.c_str());
    }

    // reference : https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c
    bool is_file_exists(const std::string &string_path)
    {
        std::ifstream f(string_path.c_str());

        return f.good();
    }

    bool make_file(const std::string &string_path)
    {
        if (is_file_exists(string_path) == false)
        {
            string_system("touch " + string_path);
            return true;
        }

        print_overwrite_warning_message(string_path);

        return false;
    }

    bool copy_file(const std::string &source_string_path, const std::string &dest_string_path)
    {
        if (is_file_exists(dest_string_path) == false)
        {
            string_system("cp " + source_string_path + " " + dest_string_path);
        }

        return true;
    }

    void make_directory(const std::string &string_path)
    {
        if (is_file_exists(string_path) == false)
        {
            string_system("mkdir " + string_path);
        }
    }
};