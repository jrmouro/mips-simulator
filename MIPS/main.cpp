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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
//    std::string programm_filename = "programm.txt";
//    std::string programm_out_filename = "out.txt";
//    
//    if(argc > 1){
//        programm_filename = argv[1];
//        if(argc > 2){
//            programm_out_filename = argv[2];
//        }
//    }
//
    Machine mach(16);
//    
//    std::ofstream outfile;
//    outfile.open(programm_out_filename);
//    
//    mach.loadProgram(
//        0, 
//        programm_filename,
//        [&outfile](const Machine& mach){
//            outfile << mach << std::endl;
//            std::cout << mach << std::endl;
//        });
//    
//    outfile.close();
    
    Ctrl ctrl;
    Registers regs;
    
    std::cout << mach.getJson();


    return 0;
}

