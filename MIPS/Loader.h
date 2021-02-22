/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Loader.h
 * Author: ronaldo
 *
 * Created on 19 de Fevereiro de 2021, 15:37
 */

#ifndef LOADER_H
#define LOADER_H



#include <iostream>
#include <sstream> 
#include "ToJson.h"
#include "Memory.h"
#include "Machine.h"
#include "Programm.h"

class Loader : public ToJson {
public:

    Loader() : mach(Machine(16)) {
    }

    Loader(const Machine& mach) : mach(mach) {
    }

    Loader(const Loader& other) : mach(other.mach), output(other.output) {
    }

    virtual ~Loader() {
    }

    virtual std::string getJson() const {

        std::stringbuf buffer;
        std::ostream os(&buffer);

        os << "[ ";

        if (this->output_json.size()) {

            int i = 0;

            for (; i < this->output_json.size() - 1; i++)
                os << this->output_json[i] << ", ";

            os << this->output_json[i];

        } else {

            os << this->mach.getJson();
            
        }

        os << " ]";

        return buffer.str();

    }

    void loadAndRun(const Programm &prog, UINT32 address = 0) {

        this->output.clear();
        this->output_json.clear();
        this->mach.reset();
        this->mach.loadProgramm(address, prog);

        while (mach.clock()) {

            this->output_json.push_back(mach.getJson());


            std::stringbuf buffer;
            std::ostream os(&buffer);
            os << this->mach;

            this->output.push_back(buffer.str());

        }

    }

    const std::vector<std::string>& getOutput() {
        return output;
    }


private:

    Machine mach;
    std::vector<std::string> output, output_json;

};

#endif /* LOADER_H */

