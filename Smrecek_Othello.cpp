#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>

/// <summary>
/// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
std::string ltrim(const std::string& s)
{
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

/// <summary>
/// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
std::string rtrim(const std::string& s)
{
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

/// <summary>
/// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
std::string trim(const std::string& s)
{
    return ltrim(rtrim(s));
}

std::vector<std::string> tokenize(std::string& command)
{
    std::string delimiter = " ";
    std::vector<std::string> tokens{};

    int64_t pos = 0;
    command = trim(command);
    while ((pos = command.find(delimiter)) != std::string::npos) {
        tokens.push_back(command.substr(0, pos));
        command.erase(0, pos + delimiter.length());
        command = trim(command);
    }
    tokens.push_back(command);

    return tokens;
}

int check_start(const std::vector<std::string>& command_tokens, bool& started, bool& black, int32_t& time)
{
    if (command_tokens.size() != 3)
    {
        return 1;
    }
    if (command_tokens[0] == "START")
    {
        started = true;
    }
    else
    {
        return 2;
    }

    if (command_tokens[1] == "B")
    {
        black = true;
    }
    else if (command_tokens[1] == "W")
    {
        black = false;
    }
    else
    {
        return 3;
    }

    int32_t N = 0;
    try
    {
        N = std::stol(command_tokens[2]);
    }
    catch (const std::exception&)
    {
        return 4;
    }

    if (N > 0)
    {
        time = N;
    }
    else
    {
        return 5;
    }

    return 0;
}

int check_input_state(const std::string& state)
{
    state;
    return 6; // zly input

    //return 0;
}

int solve(const std::string& state, std::string& result)
{
    state;
    result;

    return 7; // neexistuje riesenie

    //return 0;
}

// O - white, X - black
int main()
{
    //std::string command;

    bool started = false;
    bool black = true;
    int32_t time = 0;
    std::vector<std::string> command_tokens{};

    started;
    black;
    time;
    command_tokens;
    std::vector<std::string> test_commands{"START B 30", "MOVE"};

    //while (std::getline(std::cin, command))
    for (std::string command : test_commands)
    {
        std::string result;
        // process the command and fill result
        command_tokens = tokenize(command);

        //for (const auto& str : command_tokens) {
        //    std::cout << "------ " << str << std::endl;
        //}

        if (!started)
        {
            int return_start = check_start(command_tokens, started, black, time);
            if (return_start != 0)
            {
                return return_start;
            }
            std::cout << 1 << std::endl;
        }
        else
        {
            if (command_tokens[0] == "MOVE" && command_tokens.size() == 2)
            {
                int input_state = check_input_state(command_tokens[1]);
                if (input_state == 0)
                {
                    solve(command_tokens[1], result);
                }
                else
                {
                    return input_state;
                }
            }
            else if (command_tokens[0] == "STOP" && command_tokens.size() == 1)
            {
                return 0;
            }
            else
            {
                return 10;
            }
        }
        std::cout << result << std::endl;  
    }

    return 1000;
}
