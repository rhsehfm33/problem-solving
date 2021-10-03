#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include "tool_languages_info.h";
#include "tool_filesystem.h";

using namespace std;
using namespace tool_language_info;
using namespace filesystem;
using namespace tool_filesystem;


int main() {

    make_directory(GATHERING_SPOT);

    for (const auto & entry : directory_iterator(paths[2])) {

        string problem_name = entry.path().filename();
        if (problem_name[0] == '.') {
            continue;
        }

        string target_dir_path = GATHERING_SPOT + "/" + problem_name;
        make_directory(target_dir_path);

        for (int language_index = 0; language_index < LANGUAGES; ++language_index) {
            string source_code_path = paths[language_index] + "/" + problem_name + "/" + codes[language_index];
            system(("cp " + source_code_path + " " + target_dir_path).c_str());
        }

    }

    return 0;

}