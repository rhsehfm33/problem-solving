#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <sys/stat.h>

using namespace std;
using namespace std::filesystem;

const int LANGUAGES = 4;
const int DIR_EXISTS = 1;

const string GATHERING_SPOT = "./codes_all_in_one";


// reference : https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
int is_dir_exists(const char* path) {
    struct stat info;

    int statRC = stat( path, &info );
    if (statRC != 0) {

        // something along the path does not exist
        if (errno == ENOENT) {
            return 0;
        } 

        // something in path prefix is not a dir
        if (errno == ENOTDIR) {
            return 0;
        }

        return -1;

    }

    return (info.st_mode & S_IFDIR) ? DIR_EXISTS : 0;
}


int main() {

    if (is_dir_exists(GATHERING_SPOT.c_str()) != DIR_EXISTS) {
        system(("mkdir " + GATHERING_SPOT).c_str());
    }

    vector<string> paths = {"./c++/algorithm-assignment", "./c", "./java", "./python"};
    vector<string> codes = {"sol.cpp","sol.c", "Main.java", "sol.py"};

    for (const auto & entry : directory_iterator(paths[2])) {

        string problem_name = entry.path().filename();
        if (problem_name[0] == '.') {
            continue;
        }

        string target_dir_path = GATHERING_SPOT + "/" + problem_name;
        if (is_dir_exists(target_dir_path.c_str()) != DIR_EXISTS) {
            system(("mkdir " + target_dir_path).c_str());
        }

        for (int language_index = 0; language_index < LANGUAGES; ++language_index) {
            string source_code_path = paths[language_index] + "/" + problem_name + "/" + codes[language_index];
            system(("cp " + source_code_path + " " + target_dir_path).c_str());
        }

    }

    return 0;

}