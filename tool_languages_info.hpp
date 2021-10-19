#include <vector>
#include <string>

namespace tool_language_info
{
    enum Language
    {
        CPP,
        JAVA,
        PYTHON,
        LANGUAGES
    };
    const std::string GATHERING_SPOT = "./codes_all_in_one";
    const std::vector<std::string> PATHS = {"./c++/algorithm-assignment", "./java", "./python"};
    const std::vector<std::string> CODES = {"sol.cpp", "Main.java", "sol.py"};
};