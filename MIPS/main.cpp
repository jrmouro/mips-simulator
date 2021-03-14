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
#include "Menu.h"


using namespace std;

int web_main(int argc, char **argv) {

    std::string program_filename = "program.txt";
    std::string program_out_filename = "out.json";
    unsigned mem_size = 16,
            address = 0,
            max_clock = std::numeric_limits<unsigned int>::max();

    if (argc > 1) {
        program_filename = argv[1];
        if (argc > 2) {
            program_out_filename = argv[2];
            if (argc > 3) {
                mem_size = std::stoi(argv[3]);
                if (argc > 4) {
                    address = std::stoi(argv[4]);
                    if (argc > 5) {
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

    if (outfile.is_open()) {
        outfile << loader.getJson();
        outfile.close();
    } else {

        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    for (auto elem : loader.getOutput()) {
        std::cout << elem << std::endl;
    }


    return 0;

}

int blackScreen_main(int argc, char **argv) {

    Machine mach(32);
    Loader loader(mach);
    std::string program_filename, program_out_filename = "out.txt";
    Menu menu("Menu principal");
    Menu submenu("Menu de execução");

    MenuItem input("Digitar o programa", [&submenu, &loader, &program_out_filename, &program_filename]() {
        program_filename = "program.txt";
        program_out_filename = "out." + program_filename;
        Program p = Program::getInput();
        loader.load(p, 0, 1000);
        submenu.start();
        return true;
    });

    MenuItem file("Entrar com arquivo", [&submenu, &loader, &program_out_filename, &program_filename]() {
        std::cout << "Entre com o nome do arquivo: ";
        getline(std::cin, program_filename);
        program_out_filename = "out." + program_filename;
        Program p = Program(program_filename);
        loader.load(p, 0, 1000);
        submenu.start();
        return true;
    });

    MenuItem exec("Executar Programa", [&loader, &program_out_filename]() {

        std::ofstream outfile("exec." + program_out_filename);

        loader.exec(10000);

        for (auto elem : loader.getOutput()) {
            std::cout << elem << std::endl;
        }

        for (auto elem : loader.getFileOutput()) {
            outfile << elem << std::endl;
        }

        outfile.close();

        return true;

    });

    MenuItem reset("Reset", [&loader, &program_out_filename]() {
        
        std::ofstream outfile("reset." + program_out_filename);

        loader.reset();

        for (auto elem : loader.getOutput()) {
            std::cout << elem << std::endl;
        }
        
        for (auto elem : loader.getFileOutput()) {
            outfile << elem << std::endl;
        }

        outfile.close();

        loader.load(*loader.getMach().getProg());
        
        return true;

    });

    MenuItem clock("Clock", [&loader, &program_out_filename]() {

        if (loader.clock(10000)) {

            std::ofstream outfile("clock." + program_out_filename);

            for (auto elem : loader.getOutput()) {
                std::cout << elem << std::endl;
            }

            for (auto elem : loader.getFileOutput()) {
                outfile << elem << std::endl;
            }

            outfile.close();

        }else{
            
            std::cout << std::endl << "Execução chegou ao final!" << std::endl;
            std::cout << "Para reiniciar o programa, escolha a opção \"Reset\"" << std::endl << std::endl;
            
        }

        return true;

    });

    MenuItem exit("Sair", []() {

        return false;

    });

    submenu.addItem(exec);
    submenu.addItem(reset);
    submenu.addItem(clock);
    submenu.addItem(exit);
    menu.addItem(input);
    menu.addItem(file);
    menu.addItem(exit);

    if (argc > 1) {
        if (argc > 2) {
            program_out_filename = argv[2];
        }
        program_filename = argv[1];
        Program p(program_filename);
        loader.load(p, 0, 1000);
        submenu.start();
    }

    menu.start();

    return 0;

}

/*
 * 
 */
int main(int argc, char **argv) {

    if (argc > 3) {
        return web_main(argc, argv);
    }

    return blackScreen_main(argc, argv);

}
