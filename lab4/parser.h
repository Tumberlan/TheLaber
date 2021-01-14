//
// Created by Igor on 10.01.2021.
//

#ifndef LAB4_PARSER_H
#define LAB4_PARSER_H
#include <vector>
#include <fstream>
#include <tuple>
#include "tuple_functions.h"


template<typename... Arguments>

class CSV_parser{
private:
    std::ifstream &file;
    char end_symbol;
    char sep_column_symbol;
    char sep_row_symbol;
    size_t lines_to_skip; // сколько строк игнорировать(на случай если задаем строку объявления)
    int line_counter;
    

    std::string get_row(std::istream &in_stream, size_t amount_of_lines_above){
        std::string str;
        bool is_end_symbol = false;
        char symbol;
        while(in_stream.get(symbol)){
            if (symbol == end_symbol){
                is_end_symbol = true;
            }
            if (symbol == sep_row_symbol && !is_end_symbol){
                break;
            }
            str.push_back(symbol);
        }
        return str;
    }

    void update_line_counter(){
        file.clear();
        file.seekg(0, std::ios::beg); // перемещение в начало файла

        line_counter = 0;
        while (get_row(file, line_counter) != ""){
            line_counter++;
        }

        file.clear();
        file.seekg(0, std::ios::beg);
    }


    std::vector<std::string> row_split(std::string &line){
        std::vector<std::string> result_str;
        std::string tmp_str;

        for(int i = 0; i < line.size(); i++){
            if(line[i] == end_symbol){
                continue;
            }
            if(line[i] == sep_column_symbol){
                result_str.push_back(tmp_str);
                tmp_str.clear();
                continue;
            }
            tmp_str.push_back(line[i]);
        }

        if (!tmp_str.empty()){
            result_str.push_back(tmp_str);
        }
        return result_str;
    }


    std::tuple<Arguments...> row_parse(size_t string_number,std::string &str){
        size_t number_of_arguments = sizeof... (Arguments);

        if(str.empty()){
            throw std::invalid_argument("Line " + std::to_string(string_number) + " is empty");
        }

        std::vector<std::string> parts = row_split(str);

        if(parts.size() != number_of_arguments){
            throw std::invalid_argument("Line " + std::to_string(string_number) + " has incompatible number of fields");

        }

        std::tuple<Arguments...> tuple_of_parts;

        try {
            tuple_of_parts = tuple_parse<Arguments...>(parts);
        }
        catch(std::exception &error){
            throw std::invalid_argument("Line " + std::to_string(string_number) + ", column " + error.what() + " has wrong type");
        }

        return tuple_of_parts;
    }



    class CSV_iterator{
    private:
        std::ifstream &file;
        int idx;
        CSV_parser<Arguments...> *parent;
        std::string value;
        bool is_last;
        bool is_updated;

        void update_value(){
            if (is_last){
                value = "";
            }else{
                file.clear();
                file.seekg(0, std::ios::beg);
                for(int i = 0; i < idx; i++){
                    parent->get_row(file, i);
                }
                value = parent->get_row(file, idx);
            }
        }

    public:
        CSV_iterator(std::ifstream &f, size_t i, CSV_parser<Arguments...> *p): file(f){
            idx = i;
            parent = p;
            is_updated = false;

            if(idx >= parent->line_counter){
                is_last = true;
            }else{
                is_last = false;
            }
        }


        bool operator==(const CSV_iterator &iter)const{
            if(this->parent == iter.parent && (this->is_last == iter.is_last || this->idx == iter.idx)){
                return true;
            }else{
                return false;
            }
        }

        bool operator!= (const CSV_iterator &iter)const{
            return !(*this == iter);
        }

        CSV_iterator& operator++ (){
            is_updated = false;

            if(idx < parent->line_counter){
                idx++;
            }
            if(idx >= parent->line_counter){
                is_last = true;
            }

            return *this;
        }

        std::tuple<Arguments...> operator*(){
            if(!is_updated){
                update_value();
                is_updated = true;
            }
            return parent->row_parse(idx+1, value);
        }

    };

public:
    CSV_parser(std::ifstream& f, size_t l_to_skip): file(f){
        lines_to_skip = l_to_skip;
        sep_column_symbol = ',';
        sep_row_symbol = '\n';
        end_symbol = '\"';

        if(!file.is_open()){
            throw std::invalid_argument("No file");
        }

        line_counter = 0;
        update_line_counter();

        if(lines_to_skip >= line_counter){
            throw std::logic_error("You skipped all lines");
        }

    }

    ~CSV_parser() = default;

    CSV_iterator begin(){
        return CSV_iterator(file, lines_to_skip, this);
    }

    CSV_iterator end(){
        return CSV_iterator(file, line_counter, this);
    }
};

#endif //LAB4_PARSER_H
