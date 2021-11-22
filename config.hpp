#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <map>

#ifndef CONFIG_
#define CONFIG_

class Config
{
public:
    Config();

    void set_key_delimiters(char il, char fl);
    void set_val_delimiters(char il, char fl);
    void set_comment_leader(char cl);
    void set_equal_symbol(char eql);
    void load(std::string file_name);

    template<typename T>
    void bind(T &v, std::string s)
    {
        std::string line = keyval[s];

        if (!line.empty())
        {
            if constexpr(std::is_same_v<T, std::string>)
            {
                auto ini_pos = line.find(ini_val_leader);
                auto fin_pos = line.substr(ini_pos + 1).find(fin_val_leader);

                if (fin_pos != std::string::npos)
                {
                    v = line.substr(ini_pos + 1, fin_pos);
                }
                else
                {
                    std::cerr << "No value attributed to key '" << s << "'." << std::endl;
                }
            }
            else
            {
                std::istringstream value (line);
                value >> std::ws >> v >> std::ws;
            }
        }
    }

private:
    std::map<std::string, std::string> keyval;

    std::fstream config_file;
    std::string file_name;
    std::string line;
    std::string key;

    char comment_leader = '#';
    char ini_key_leader = '[';
    char fin_key_leader = ']';
    char ini_val_leader = '"';
    char fin_val_leader = '"';
    char equal_symbol = '=';
};

#endif
