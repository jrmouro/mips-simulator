/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 06:04
 */

#include <iostream>
#include<limits>
#include <fstream>
#include "Machine.h"
#include "Registers.h"
#include "Ctrl.h"
#include "Program.h"
#include "Loader.h"

using namespace std;

/*
 * 
 */

int main(int argc, char **argv)
{

    std::string program_filename = "program.txt";
    std::string program_out_filename = "out.json";
    unsigned mem_size = 16, 
            address = 0, 
            max_clock = std::numeric_limits<unsigned int>::max();

    if (argc > 1)
    {
        program_filename = argv[1];
        if (argc > 2)
        {
            program_out_filename = argv[2];
            if (argc > 3)
            {
                mem_size = std::stoi(argv[3]);
                if (argc > 4)
                {
                    address = std::stoi(argv[4]);
                    if(argc > 5){                        
                        max_clock = std::stoi(argv[5]);
                        
                    }
                }
            }
        }
    }

    Machine mach(mem_size);
    Program prog(program_filename);
    Loader loader(mach);

    loader.loadAndRun(prog, address, max_clock);

    std::ofstream outfile;
    outfile.open(program_out_filename, std::ofstream::out | std::ofstream::trunc);

    if (outfile.is_open())
    {

        outfile << loader.getJson();
        outfile.close();
    }
    else
    {

        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    for (auto elem : loader.getOutput())
    {

        std::cout << elem << std::endl;
    }


    return 0;
}
