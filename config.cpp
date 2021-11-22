#include "config.hpp"

void Config::set_key_delimiters(char il, char fl)
{
    ini_key_leader = il;
    fin_key_leader = fl;
}

void Config::set_val_delimiters(char il, char fl)
{
    ini_val_leader = il;
    fin_val_leader = fl;
}

void Config::set_comment_leader(char cl)
{
    comment_leader = cl;    
}

void Config::set_equal_symbol(char eql)
{
    equal_symbol = eql;
}

Config::Config(){}

void Config::load(std::string file_name)
{
    config_file.open(file_name, std::ios::in);

    keyval.clear();

    if(config_file.fail())
    {
        std::cerr << "Error while oppening '" << file_name << "'." << std::endl;
    }

    while(std::getline(config_file, line))
    {
        line = line.substr(0,line.find(comment_leader));

        auto ini_pos = line.find(ini_key_leader);
        auto fin_pos = line.substr(ini_pos + 1).find(fin_key_leader);
        auto eq_pos = line.find(equal_symbol);
        auto s = line.substr(eq_pos + 1);

        if (fin_pos != std::string::npos) 
        {
            key = line.substr(ini_pos + 1, fin_pos);
            if (eq_pos != std::string::npos)
            { 
                if (!std::all_of(s.begin(), s.end(), [](char c){return std::isspace(c);}))
                {
                    keyval.insert({key, line.substr(eq_pos + 1)});
                }
                else
                {
                    std::cerr << "No value attributed to key '" << key << "'." << std::endl; 
                }
            }
            else
            {
                std::cerr << "No equal sign in key '" << key << "'." << std::endl;
            }
        }
    }
    config_file.close();
}
