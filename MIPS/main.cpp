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
#include <fstream>
#include "Machine.h"
#include "Registers.h"
#include "Ctrl.h"
#include "Programm.h"
#include "Loader.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    std::string programm_filename = "programm_empty.txt";
    std::string programm_out_filename = "out.json";
    unsigned mem_size = 16, address = 0;

    if (argc > 1) {
        programm_filename = argv[1];
        if (argc > 2) {
            programm_out_filename = argv[2];
            if (argc > 3) {
                mem_size = std::stoi(argv[3]);
                if (argc > 4) {
                    address = std::stoi(argv[4]);
                }
            }
        }
    }

    Machine mach(mem_size);
    Programm prog(programm_filename);
    Loader loader(mach);

    loader.loadAndRun(prog, address);

    std::ofstream outfile;
    outfile.open(programm_out_filename, std::ofstream::out | std::ofstream::trunc);

    if (outfile.is_open()) {

        outfile << loader.getJson();
        outfile.close();

    } else {

        std::cout << "Error opening output file" << std::endl;

    }

    for (auto elem : loader.getOutput()) {

        std::cout << elem << std::endl;

    }

    return 0;
}

