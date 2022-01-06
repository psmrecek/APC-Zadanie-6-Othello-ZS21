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
    if (state.length() != 64)
    {
        return 6;
    }
    
    uint64_t found = state.find_first_not_of("-OX");

    if (found != std::string::npos)
    {
        return 7;
    }

    return 0;
}

int solve(const std::string& state, std::string& result)
{
    state;
    result;

    return 8; // neexistuje riesenie

    //return 0;
}

std::vector<std::vector<char>> game_field_2d(const std::string& game_state)
{
    std::vector<std::vector<char>> field;
    field.resize(8);
    for (size_t i = 0; i < field.size(); i++)
    {
        field[i].resize(8);
    }

    for (size_t i = 0; i < game_state.size(); i++)
    {
        field[i / 8][i % 8] = game_state[i];
    }

    return field;
}

void print_game_field(const std::vector<std::vector<char>>& field)
{
    for (size_t i = 0; i < field.size(); i++)
    {
        for (size_t j = 0; j < field.size(); j++)
        {
            std::cout << field[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void apply_result(const bool bot_black, std::vector<std::vector<char>>& field, const std::string& result)
{
    int letter = result[0] - 'A';
    int number = result[1] - '1';

    char bot_symbol = '-';
    char opponent_symbol = '-';

    if (bot_black)
    {
        bot_symbol = 'X';
        opponent_symbol = 'O';
    }
    else
    {
        bot_symbol = 'O';
        opponent_symbol = 'X';
    }

    field[number][letter] = bot_symbol;

    // number + zmena po stlpcoxh
    for (int i = number + 1; i < 8; i++)
    {
        if (field[i][letter] == '-')
        {
            break;
        }
        if (field[i][letter] == bot_symbol)
        {
            for (int j = number + 1; j <= i; j++)
            {
                field[j][letter] = bot_symbol;
            }
            break;
        }
    }

    // number - zmena po stlpcoch
    for (int i = number - 1; i >= 0; i--)
    {
        if (field[i][letter] == '-')
        {
            break;
        }
        if (field[i][letter] == bot_symbol)
        {
            for (int j = number - 1; j >= i; j--)
            {
                field[j][letter] = bot_symbol;
            }
            break;
        }
    }

    // letter + zmena po riadkoch
    for (int i = letter + 1; i < 8; i++)
    {
        if (field[number][i] == '-')
        {
            break;
        }
        if (field[number][i] == bot_symbol)
        {
            for (int j = letter + 1; j <= i; j++)
            {
                field[number][j] = bot_symbol;
            }
            break;
        }
    }

    // letter - zmena po roadkoch
    for (int i = letter - 1; i >= 0; i--)
    {
        if (field[number][i] == '-')
        {
            break;
        }
        if (field[number][i] == bot_symbol)
        {
            for (int j = letter - 1; j >= i; j--)
            {
                field[number][j] = bot_symbol;
            }
        }
    }

    // number + letter +
    for (int i = 1; i < 8; i++)
    {
        int dia_num = number + i;
        int dia_let = letter + i;

        if (dia_num < 8 && dia_let < 8 && dia_num >= 0 && dia_let >=0)
        {
            if (field[dia_num][dia_let] == '-')
            {
                break;
            }
            if (field[dia_num][dia_let] == bot_symbol)
            {
                for (int j = 1; j <= i; j++)
                {
                    field[number + j][letter + j] = bot_symbol;
                }
                break;
            }
        }
    }

    // number + letter -
    for (int i = 1; i < 8; i++)
    {
        int dia_num = number + i;
        int dia_let = letter - i;

        if (dia_num < 8 && dia_let < 8 && dia_num >= 0 && dia_let >= 0)
        {
            if (field[dia_num][dia_let] == '-')
            {
                break;
            }
            if (field[dia_num][dia_let] == bot_symbol)
            {
                for (int j = 1; j <= i; j++)
                {
                    field[number + j][letter - j] = bot_symbol;
                }
                break;
            }
        }
    }

    // number - letter +
    for (int i = 1; i < 8; i++)
    {
        int dia_num = number - i;
        int dia_let = letter + i;

        if (dia_num < 8 && dia_let < 8 && dia_num >= 0 && dia_let >= 0)
        {
            if (field[dia_num][dia_let] == '-')
            {
                break;
            }
            if (field[dia_num][dia_let] == bot_symbol)
            {
                for (int j = 1; j <= i; j++)
                {
                    field[number - j][letter + j] = bot_symbol;
                }
                break;
            }
        }
    }

    // number - letter -
    for (int i = 1; i < 8; i++)
    {
        int dia_num = number - i;
        int dia_let = letter - i;

        if (dia_num < 8 && dia_let < 8 && dia_num >= 0 && dia_let >= 0)
        {
            if (field[dia_num][dia_let] == '-')
            {
                break;
            }
            if (field[dia_num][dia_let] == bot_symbol)
            {
                for (int j = 1; j <= i; j++)
                {
                    field[number - j][letter - j] = bot_symbol;
                }
                break;
            }
        }
    }
}

void test_place_two(const std::string& test_game_state, const bool bot_black, std::string one, std::string two)
{
    std::cout << one << " " << two << std::endl;
    std::vector<std::vector<char>> field = game_field_2d(test_game_state);
    print_game_field(field);
    apply_result(bot_black, field, one);
    print_game_field(field);
    apply_result(bot_black, field, two);
    print_game_field(field);
    std::cout << "+++++++++++++++++++++" << std::endl;
}

bool random_player(std::string& command, bool& random_start, const std::string& result, std::string& random_game_state)
{
    std::string bot_color{ "B" };
    bool bot_black = true;

    std::string random_color{ "W" };
    bool random_black = false;


    std::string random_time_str{ "10" };
    int32_t random_time = 10;

    std::string start_command{ "START" };
    std::string move_command{ "MOVE" };
    std::string delimeter_command{ " " };

    if (!random_start)
    {
        command = start_command + delimeter_command + random_color + delimeter_command + random_time_str;
        random_start = true;
        random_game_state = "----------O------OOO------O-------------------------------------";
        return true;
    }

    // chyba free
    result;
    random_game_state;
    random_black;
    random_color;
    random_time;
    random_time_str;
    start_command;
    move_command;
    delimeter_command;
    //chyba free

    std::vector<std::vector<char>> field = game_field_2d(random_game_state);
    //print_game_field(field);


    //// C1 C5
    //test_place_two(random_game_state, bot_black, "C1", "C5");
    //// C5 C1
    //test_place_two(random_game_state, bot_black, "C5", "C1");
    //// A3 E3
    //test_place_two(random_game_state, bot_black, "A3", "E3");
    //// E3 A3
    //test_place_two(random_game_state, bot_black, "E3", "A3");

    // B2 D4
    test_place_two(random_game_state, bot_black, "B2", "D4");
    // D4 B2
    test_place_two(random_game_state, bot_black, "D4", "B2");
    // B4 D2
    test_place_two(random_game_state, bot_black, "B4", "D2");
    // D2 B4
    test_place_two(random_game_state, bot_black, "D2", "B4");

    // Multiple actions
    test_place_two("------------------XOO-----OOO-----OO----------------------------", bot_black, "E2", "E5");


    return false;
}

// O - white, X - black
int main()
{
    std::string command;
    std::string result;

    bool started = false;
    bool black = true;
    int32_t time = 0;
    std::vector<std::string> command_tokens{};

    started;
    black;
    time;
    command_tokens;
    //std::vector<std::string> test_commands{"START B 30", "MOVE ---------------------------OX------XX-------X-------------------"};
    bool random_start = false;
    std::string random_game_state{ "" };

    //while (std::getline(std::cin, command))
    while (random_player(command, random_start, result, random_game_state))
    //for (std::string command : test_commands)
    {
        //std::string result;
        // process the command and fill result
        command_tokens = tokenize(command);

        for (const auto& str : command_tokens) {
            std::cout << "------ " << str << std::endl;
        }

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
