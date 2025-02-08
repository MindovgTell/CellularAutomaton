#include "CellularAutomaton.hpp"

std::string CellularAutomaton::convert_to_ternary(unsigned long long N, int size_of_string)
{
    std::string str;
    while(N != 0)
    {
        int x = N % 3;
        N /= 3;
        std::string s = std::to_string(x);
        str.append(s);
        convert_to_ternary(N, size_of_string);
    }

    int length = str.length();
    while(length < size_of_string)
    {
        str.append("0");
        length++;
    }
    
    std::reverse(str.begin(), str.end());
    
    return str;
}

int CellularAutomaton::converte_to_decimal(std::string& str)
{
    int res = 0;
    int length = str.length() - 1;
    for(int i = length; i >=0; --i)
    {
        res += (str[i] - 48)*std::pow(3,length-i);
    }
    return res;
}

void CellularAutomaton::init_state(std::string& str)
{
    this->state = str;
    for(int i = 0, length = this->state.length(); i != length; ++i)
    {
        this->state[i]--;
    }
}

void CellularAutomaton::init_wolfram_code()
{
    for(int i = 26; i >= 0; --i)
    {
        std::string mystr = convert_to_ternary(i,3);
        this->Wolfram_code.push_back(std::vector<std::string>{mystr, ""});
    }

    std::string function_ternary_number = convert_to_ternary(this->function_number, 27);

    for (int i = 0; i != 27; ++i)
    {
        this->Wolfram_code[i][1] = function_ternary_number[i];
    }
}

CellularAutomaton::CellularAutomaton(unsigned long long evolution, std::string state): function_number(evolution)
{
    this->init_state(state);
    this->init_wolfram_code();
}

CellularAutomaton::CellularAutomaton()
{
    for(int i = 0; i != 240; ++i)
    {
        char st = rand()%3 + 48;
        this->state.push_back(st);
    }

    this->function_number = rand()%1000000;

    this->init_wolfram_code();
}

CellularAutomaton::~CellularAutomaton()
{
}

void CellularAutomaton::print_wolfram_code()
{
    for(int i = 0; i != 27; i++)
    {
        std::cout << this->Wolfram_code[i][0] << ' ' << this->Wolfram_code[i][1] << '\n';
    }
}

void CellularAutomaton::print_state()
{
    for(int i = 0, length = this->state.length(); i != length; ++i)
    {
        std::cout << static_cast<int>(this->state[i]) - 47 << ' ';
    }
    std::cout << '\n';
}

std::string CellularAutomaton::get_cell_state(int i)
{
    int length = this->state.length();
    if(i < 0 || i > length)
        return "";
    std::string cell_state;
    char L,R;
    if(i == 0)
    {
        L = state[length - 1];
        R = state[1];
    }
    else if(i == length - 1)
    {
        R = state[0];
        L = state[i - 1];
    }
    else if(i > 0 && i < (length - 1))
    {
        L = state[i-1];
        R = state[i+1];
    }

    cell_state.push_back(L);
    cell_state.push_back(state[i]);
    cell_state.push_back(R);
        
    return cell_state;
}

void CellularAutomaton::next_generation()
{
    std::string new_state = this->state;

    for(int i = 0, length = this->state.length(); i != length; ++i)
    {
        std::string cell_state = get_cell_state(i);

        int num_next_gen_state = converte_to_decimal(cell_state);
        
        std::string st = this->Wolfram_code[26 - num_next_gen_state][1];

        new_state[i] = st.front();
    }
    this->state = new_state;
}

void CellularAutomaton::operator()()
{
    this->next_generation();
}

std::string CellularAutomaton::get_state()
{
    return this->state;
}

const std::string CellularAutomaton::get_state() const
{
    return this->state;
}

std::ostream &operator<<(std::ostream & out, CellularAutomaton & cel)
{
    for(int i = 0, length = cel.get_state().length(); i != length; ++i)
    {
       out << cel.get_state()[i] - 47 << ' ';
    }
    cel.next_generation();
    return out;
}

void CellularAutomaton::random_state()
{
    for(int i = 0, length = this->state.length(); i != length; ++i)
    {
        char s = rand()%3 + 48;
        this->state[i] = s;
    }
}

void CellularAutomaton::random_function()
{
    this->function_number = rand()%1000000;
}

unsigned long CellularAutomaton::get_function_number()
{
    return this->function_number;
}

void CellularAutomaton::set_function_number(unsigned long num)
{
    this->function_number = num;
}

void CellularAutomaton::reinit_wolfram_code()
{
    this->init_wolfram_code();
}

void CellularAutomaton::corn_state(int i)
{
    for(int i = 0, length = this->state.length(); i != length; ++i)
    {
        char s = 48;
        this->state[i] = s;
    }
    this->state[this->state.length()/2] = 48 + i;
}