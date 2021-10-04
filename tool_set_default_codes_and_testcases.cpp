#include <bits/stdc++.h>

#include "tool_languages_info.h"
#include "tool_filesystem.h"

using namespace std;
using namespace tool_language_info;
using namespace filesystem;
using namespace tool_filesystem;

const int INPUT_FAIL = -1;

int input_problem_count()
{
    int problem_count;

    while (true)
    {

        cout << "How many problems you want to added?" << endl;
        cout << "Press ctrl+c to exit this program" << endl;
        cin >> problem_count;

        if (problem_count <= 0)
        {
            cout << "Are you kidding me? Input more than 0" << endl;
        }
        else if (problem_count >= 100)
        {
            cout << "Nah ah. That's too much" << endl;
        }
        else
        {
            break;
        }
    }
    cout << endl;

    return problem_count;
}

int input_testcase_count()
{
    int testcase_count;

    while (true)
    {

        cout << "How many testcases x.in you want to create?" << endl;
        cout << "Press ctrl+c to exit this program" << endl;
        cin >> testcase_count;

        if (testcase_count <= 0)
        {
            cout << "Are you kidding me? Input more than 0" << endl;
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

string input_problem_name()
{
    string problem_name = "";

    cout << "Input the name of problem. Only english letters or numbers please." << endl;
    cin >> problem_name;
    cout << endl;

    return problem_name;
}

bool create_default_folder_and_code_for_all_languages(const string &problem_name)
{
    for (int language_index = 0; language_index < LANGUAGES; ++language_index)
    {

        string target_directory = paths[language_index] + "/" + problem_name;
        make_directory(target_directory);

        string source_default_code = paths[language_index] + "/" + codes[language_index];
        copy_file(source_default_code, target_directory);
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
        cin >> added_testcase_content;

        if (added_testcase_content != "EOF")
        {
            testcase_content += added_testcase_content + "\n";
        }
        else
        {
            break;
        }
    }
    cout << endl;

    return testcase_content;
}

void check_file_overwrite(const string &problem_name, int testcase_index)
{
    bool is_overwrite = false;

    for (int language_index = 0; language_index < LANGUAGES; ++language_index)
    {

        string inTestcaseFilePath = paths[language_index] + "/" + problem_name + "/" + to_string(testcase_index) + ".in";
        if (is_file_exists(inTestcaseFilePath) == true)
        {
            print_overwrite_warning_message(inTestcaseFilePath);
            is_overwrite = true;
        }
    }

    if (is_overwrite)
    {
        string input = "";
        cout << "If you don't want to overwrite, press ctrl+c to exit the program" << endl;
        cout << "But if you want to overwrite, input y or any letters" << endl;
        cin >> input;
        if (input.size() != 0)
        {
            cout << endl;
            return;
        }
    }
}

bool create_testcase_x_in(const string &problem_name, int testcase_index)
{
    check_file_overwrite(problem_name, testcase_index);

    string testcase_content = input_testcase_content(testcase_index);

    for (int language_index = 0; language_index < LANGUAGES; ++language_index)
    {

        string inTestcaseFilePath = paths[language_index] + "/" + problem_name + "/" + to_string(testcase_index) + ".in";
        ofstream inTestcaseFile(inTestcaseFilePath.data());

        inTestcaseFile << testcase_content;
        inTestcaseFile.close();
    }

    return true;
}

int get_last_addable_testcase_index(const string &problem_name)
{
    string target_dir = paths[0] + "/" + problem_name;

    int testcase_index = 1;
    while (is_file_exists(target_dir + "/" + to_string(testcase_index) + ".in") == true)
    {
        testcase_index += 1;
    }

    return testcase_index;
}

bool create_testcases(const string &problem_name, int testcase_count)
{
    int testcase_index = get_last_addable_testcase_index(problem_name);

    for (int added_index = 0; added_index < testcase_count; ++added_index)
    {
        create_testcase_x_in(problem_name, testcase_index + added_index);
    }

    return true;
}

int main()
{
    int problem_count = input_problem_count();

    while (problem_count--)
    {

        cout << to_string(problem_count + 1) << " problems left" << endl;
        string problem_name = input_problem_name();
        int testcase_count = input_testcase_count();

        create_default_folder_and_code_for_all_languages(problem_name);
        create_testcases(problem_name, testcase_count);
    }

    cout << "successfully done" << endl;

    return 0;
}