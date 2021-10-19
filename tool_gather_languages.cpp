#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include "tool_languages_info.hpp"
#include "tool_filesystem.hpp"

using namespace std;
using namespace tool_language_info;
using namespace filesystem;
using namespace tool_filesystem;

int main()
{
    make_directory(GATHERING_SPOT);

    for (const auto &entry : directory_iterator(PATHS[CPP]))
    {
        string problem_name = entry.path().filename();
        if (problem_name[0] == '.' or problem_name == CODES[CPP])
        {
            continue;
        }

        string target_dir_path = GATHERING_SPOT + "/" + problem_name;
        make_directory(target_dir_path);

        for (int language_index = 0; language_index < LANGUAGES; ++language_index)
        {
            string source_code_path = PATHS[language_index] + "/" + problem_name + "/" + CODES[language_index];
            string dest_code_path = target_dir_path + "/" + CODES[language_index];
            copy_file(source_code_path, dest_code_path);
        }
    }

    return 0;
}