/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Programm.h
 * Author: ronaldo
 *
 * Created on 17 de Fevereiro de 2021, 16:20
 */

#ifndef PROGRAMM_H
#define PROGRAMM_H

#include "Memory.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

class Programm {
public:

    static std::vector<UINT32> read(std::string filename) {

        std::vector<UINT32> code;

        std::string linecode;

        std::ifstream readFile(filename);

        if (readFile.is_open()) {

            while (getline(readFile, linecode)) {

                char chars[] = " \n";

                for (unsigned int i = 0; i < std::strlen(chars); ++i) {
                    linecode.erase(std::remove(linecode.begin(), linecode.end(), chars[i]), linecode.end());
                }

                for (unsigned i = 0; i < linecode.length(); ++i) {

                    if (linecode.at(i) != '0' && linecode.at(i) != '1') {

                        throw std::invalid_argument("invalid binary code");

                    }

                }

                UINT32 c = (UINT32) std::stoi(linecode, 0, 2);

                code.push_back(c);

            }

            readFile.close();

        }

        return code;

    }

};

#endif /* PROGRAMM_H */

