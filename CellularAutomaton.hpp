#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

class CellularAutomaton
{
private:
    unsigned long long function_number;
    std::string state;
    std::vector< std::vector<std::string> > Wolfram_code;

    void init_wolfram_code();
    void init_state(std::string&);
public:
    CellularAutomaton(unsigned long long evolution, std::string state);
    CellularAutomaton();
    ~CellularAutomaton();

    void random_state();
    void random_function();
    void corn_state(int);

    std::string convert_to_ternary(unsigned long long, int);
    int converte_to_decimal(std::string&);
    std::string get_cell_state(int);

    //void through(std::ostream&);

    void next_generation();
    void operator()();

    void reinit_wolfram_code();

    //Accessors
    void print_wolfram_code();

    void print_state();

    std::string get_state();
    const std::string get_state() const;

    unsigned long get_function_number();
    void set_function_number(unsigned long);

    friend std::ostream& operator<<(std::ostream&, CellularAutomaton& );
};

