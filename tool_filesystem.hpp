#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace tool_filesystem
{
    void print_overwrite_warning_message(const std::string &filePath)
    {
        std::cout << filePath << " " << "already exists!" << std::endl;
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

    bool is_allow_overwrite(const std::string &string_path)
    {
        print_overwrite_warning_message(string_path);
        
        std::cout << "If you don't want to overwrite, input \"n\" or \"no\"" << std::endl;
        std::cout << "Else, input \"y\" or \"yes\" to overwrite" << std::endl;
        std::cout << "Please input without quotes" << std::endl;

        while (true)
        {
            std::string input = "";
            std::cin >> input;
            if (input == "y" or input == "yes")
            {
                std::cout << std::endl;
                return true;
            }
            else if (input == "n" or input == "no")
            {
                std::cout << std::endl;
                return false;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Your input is not one of the options" << std::endl;
                std::cout << "Input one of these: \"y\", \"yes\", \"n\", \"no\"" << std::endl;
                std::cout << "And please input without quotes" << std::endl;
            }
        }
    }

    bool is_finally_writable(const std::string &string_path)
    {
        return (is_file_exists(string_path) == false or is_allow_overwrite(string_path) == true);
    }

    void make_file(const std::string &string_path)
    {
        if (is_finally_writable(string_path) == true)
        {
            string_system("touch " + string_path);
        }
    }

    void copy_file(const std::string &source_string_path, const std::string &dest_string_path)
    {
        if (is_finally_writable(dest_string_path) == true)
        {
            string_system("cp " + source_string_path + " " + dest_string_path);
        }
    }

    void make_directory(const std::string &string_path)
    {
        if (is_file_exists(string_path) == false)
        {
            string_system("mkdir " + string_path);
        }
    }
};