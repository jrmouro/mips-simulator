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
#include "Program.h"

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

            unsigned int i = 0;

            for (; i < this->output_json.size() - 1; i++)
                os << this->output_json[i] << ", ";

            os << this->output_json[i];

        } else {

            os << this->mach.getJson();

        }

        os << " ]";

        return buffer.str();

    }

    void loadAndRun(const Program &prog, UINT32 address = 0, unsigned max_clock = 100) {

        this->output.clear();
        this->output_json.clear();
        this->mach.reset();
        this->mach.loadProgram(address, prog);

        while (mach.clock(max_clock)) {

            this->output_json.push_back(mach.getJson());


            std::stringbuf buffer;
            std::ostream os(&buffer);
            os << this->mach;

            this->output.push_back(buffer.str());

        }

    }

    void load(const Program &prog, UINT32 address = 0, unsigned max_clock = 100) {
        this->output.clear();
        this->output_json.clear();
        this->mach.reset();
        this->mach.loadProgram(address, prog);
    }

    void exec(unsigned max_clock) {
        while (mach.clock(max_clock)) {

            this->output_json.push_back(mach.getJson());


            std::stringbuf buffer;
            std::stringbuf fullbuffer;

            std::ostream os(&buffer);
            std::ostream fullos(&fullbuffer);

            os << this->mach;
            this->mach.exportMachine(fullos);

            this->output.push_back(buffer.str());
            this->output_file.push_back(fullbuffer.str());

        }
    }

    void reset() {
        this->mach.reset();
        std::stringbuf buffer;
        std::stringbuf fullbuffer;
        std::ostream os(&buffer);
        std::ostream fullos(&fullbuffer);
        os << this->mach;
        this->mach.exportMachine(fullos);
        this->output.clear();
        this->output_file.clear();
        this->output.push_back(buffer.str());
        this->output_file.push_back(fullbuffer.str());
    }

    bool clock(unsigned max_clock) {
        if (mach.clock(max_clock)) {
            this->output_json.push_back(mach.getJson());
            std::stringbuf buffer;
            std::stringbuf fullbuffer;
            std::ostream os(&buffer);
            std::ostream fullos(&fullbuffer);
            os << this->mach;
            this->mach.exportMachine(fullos);
            this->output.clear();
            this->output_file.clear();
            this->output.push_back(buffer.str());
            this->output_file.push_back(fullbuffer.str());
            return true;
        }
        return false;
    }

    const std::vector<std::string>& getOutput() {
        return output;
    }

    const std::vector<std::string>& getFileOutput() {
        return output_file;
    }

    Machine getMach() const {
        return mach;
    }


private:

    Machine mach;
    std::vector<std::string> output, output_json, output_file;

};

#endif /* LOADER_H */

