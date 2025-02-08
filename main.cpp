//#include "CellularAutomaton.hpp"
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "DrawAutomaton.hpp" // Work with SFML and contain CellularAutomaton.hpp

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned>(time(0)));

    if(argc != 4)
    {
        std::cout << "ERROR: Podana niepoprawna liczba argumentow" << '\n';
        exit(1);
    }

    std::stringstream f_num(argv[1]);
    int fun_num;
    if(!(f_num >> fun_num))
        fun_num = 0;

    std::string start_state = argv[2];
    for(int i = 0, length = start_state.length(); i != length; ++i)
    {
        if(start_state[i] != '1' && start_state[i] != '2' && start_state[i] != '3')
        {
            std::cout << "ERROR: Niemozliwe wartosci stanow, moga byc tylko 1,2 lub 3" << '\n';
            exit(1);
        }
    }

    std::stringstream g_num(argv[3]);
    int generation_num;
    if(!(g_num >> generation_num))
        generation_num = 0;

    std::string file_path = "./";
    std::string arg1(argv[1]);
    std::string arg3(argv[3]);

    arg1 += "_";
    std::string arg2 = start_state + "_";

    file_path.append(arg1);
    file_path.append(arg2);
    file_path.append(arg3);
    file_path.append(".txt");

    std::ofstream outf(file_path);

    if (!outf)
	{
		std::cerr << "ERROR: " + file_path + " nie moze byc otwarty " << '\n';
		exit(1);
	}


    // CellularAutomaton ca(fun_num, start_state);

    // for (int i = 0; i <= generation_num; ++i)
    // {
    //     outf << ca << '\n';
    //     std::cout << ca << '\n';
    // }

    // std::cout << ca.get_function_number() << '\n';

    //OBSLUGA DRAWAUTOMATON

    //Podana liczba generacji 160 dla lepszego wyświetlenia obrazku

    CellularAutomaton ca;
    ca.random_state();
    ca.set_function_number(565493);
    DrawAutomaton da(ca, 160, ca.get_state().length());

    while(da.running())
    {
        da.render();

        da.update();
    }

    return 0;
}