#include <bits/stdc++.h>

#include "tool_languages_info.hpp"
#include "tool_filesystem.hpp"

using namespace std;
using namespace tool_language_info;
using namespace filesystem;
using namespace tool_filesystem;


// No need to use this function
// This makes program just more complicated
// int input_problem_count()
// {
//     int problem_count;

//     while (true)
//     {
//         cout << "How many problems you want to added?" << endl;
//         cout << "Press ctrl+c to exit this program" << endl;
//         cin >> problem_count;

//         if (problem_count <= 0)
//         {
//             cout << "Are you kidding me? Input more than 0" << endl;
//         }
//         else if (problem_count >= 100)
//         {
//             cout << "Nah ah. That's too much" << endl;
//         }
//         else
//         {
//             break;
//         }
//     }
//     cout << endl;

//     return problem_count;
// }

void clearGetlineCinBuffer()
{
    string dummy = "";
    getline(cin, dummy);
}

string input_problem_name()
{
    string problem_name = "";

    cout << "Input the name of problem. Only english letters or numbers please." << endl;
    cin >> problem_name;
    cout << endl;

    return problem_name;
}

int input_testcase_count()
{
    int testcase_count;

    while (true)
    {
        cout << "How many testcases x.in you want to create?" << endl;
        cout << "Press ctrl+c to exit this program" << endl;
        cin >> testcase_count;

        if (testcase_count < 0)
        {
            cout << "Are you kidding me? Input 0 or more" << endl;
        }
        else if (testcase_count >= 10000)
        {
            cout << "Nah ah. That's too much" << endl;
        }
        else
        {
            break;
        }
    }
    cout << endl;

    return testcase_count;
}

bool create_default_folder_and_code_for_all_languages(const string &problem_name)
{
    for (int language_index = 0; language_index < LANGUAGES; ++language_index)
    {
        string target_directory = PATHS[language_index] + "/" + problem_name;
        make_directory(target_directory);

        string source_default_code = PATHS[language_index] + "/" + CODES[language_index];
        string dest_default_code = target_directory + "/" + CODES[language_index];

        // Copy the file only when the source file doesn't exist
        if (is_file_exists(dest_default_code) == false)
        {
            copy_file(source_default_code, dest_default_code);
        }
    }

    return true;
}

string input_testcase_content(int testcase_index)
{
    cout << "Testcase index : " << testcase_index << endl;
    cout << "Input the testcase content" << endl;
    cout << "If it's the end of testcase, input the letters \"EOF\"" << endl;

    string testcase_content = "";
    while (true)
    {
        string added_testcase_content = "";
        getline(cin, added_testcase_content);

        if (added_testcase_content == "EOF") 
        {
            break;
        }
        else
        {
            testcase_content += added_testcase_content;
            testcase_content += "\n";
        }
    }
    cout << endl;

    return testcase_content;
}

bool create_testcase_x_in(const string &problem_name, int testcase_index)
{
    string testcase_content = input_testcase_content(testcase_index);

    for (int language_index = 0; language_index < LANGUAGES; ++language_index)
    {
        string inTestcaseFilePath = PATHS[language_index] + "/" + problem_name + "/" + to_string(testcase_index) + ".in";
        if (is_finally_writable(inTestcaseFilePath) == true)
        {
            ofstream inTestcaseFile(inTestcaseFilePath.data());
            inTestcaseFile << testcase_content;
            inTestcaseFile.close();
        }
    }

    return true;
}

int get_last_addable_testcase_index(const string &problem_name)
{
    string target_dir = PATHS[C] + "/" + problem_name;

    int testcase_index = 1;
    while (is_file_exists(target_dir + "/" + to_string(testcase_index) + ".in") == true)
    {
        testcase_index += 1;
    }

    return testcase_index;
}

bool create_testcases(const string &problem_name, int testcase_count)
{
    clearGetlineCinBuffer();    

    for (int i = 0; i < testcase_count; ++i)
    {
        create_testcase_x_in(problem_name, get_last_addable_testcase_index(problem_name));
    }

    return true;
}

int main()
{
    string problem_name = input_problem_name();
    int testcase_count = input_testcase_count();

    create_default_folder_and_code_for_all_languages(problem_name);
    create_testcases(problem_name, testcase_count);

    cout << "successfully done" << endl << endl;

    return 0;
}