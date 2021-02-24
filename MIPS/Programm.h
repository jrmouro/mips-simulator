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
#include "ToJson.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

class Programm : public ToJson {
public:

    Programm() {
    }

    Programm(std::vector<UINT32> code) : code(code) {
    }

    Programm(std::vector<std::string> code) : code(read(code)) {
    }

    Programm(std::string filename) : code(read(filename)) {
    }

    Programm(const Programm& other) : code(other.code) {
    }

    virtual ~Programm() {
    }

    static std::vector<UINT32> read(std::vector<std::string> code) {

        std::vector<UINT32> ret;

        for (auto elem : code) {

            for (unsigned i = 0; i < elem.length(); ++i) {

                if (elem.at(i) != '0' && elem.at(i) != '1') {

                    throw std::invalid_argument("invalid binary code: " + elem);

                    return ret;

                }

            }

            UINT32 c = (UINT32) std::stoi(elem, 0, 2);

            ret.push_back(c);

        }

        return ret;

    }

    static std::vector<UINT32> read(std::string filename) {

        std::vector<UINT32> code;

        std::string linecode;

        std::ifstream readFile(filename);

        if (readFile.is_open()) {

            while (getline(readFile, linecode)) {

                char chars[] = " \n\r";

                for (unsigned int i = 0; i < std::strlen(chars); ++i) {
                    linecode.erase(std::remove(linecode.begin(), linecode.end(), chars[i]), linecode.end());
                }

                for (unsigned i = 0; i < linecode.length(); ++i) {

                    if (linecode.at(i) != '0' && linecode.at(i) != '1') {

                        throw std::invalid_argument("invalid binary code: " + linecode);

                    }

                }

                UINT32 c = (UINT32) std::stoi(linecode, 0, 2);

                code.push_back(c);

            }

            readFile.close();

        } else {

            throw std::invalid_argument("invalid programm filename: " + filename);

        }

        return code;

    }

    std::vector<UINT32> getCode() const {
        return code;
    }

    virtual std::string getJson() const {

        std::stringbuf buffer;
        std::ostream os(&buffer);

        os << "{ \"code\":[";

        if (this->code.size()) {

            unsigned int i = 0;
            for (; i < this->code.size() - 1; i++) {

                os << "\"" << std::bitset<32>(this->code[i]) << "\", ";

            }

            os << "\"" << std::bitset<32>(this->code[i]) << "\"";

        }

        os << "] }";


        return buffer.str();

    }

private:

    std::vector<UINT32> code;

};

#endif /* PROGRAMM_H */

