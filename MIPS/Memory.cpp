/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 06:05
 */

#include "Memory.h"

Memory::Memory(UINT32 size) : size(size) {

    this->self = new BYTE[size];
    this->reset();
}

Memory::Memory(const Memory& orig) : size(orig.size) {
    this->self = new BYTE[orig.size];
    for (int i = 0; i < orig.size; i++)
        this->self[i] = orig.self[i];
}

Memory::~Memory() {
    delete [] this->self;
}

UINT32 Memory::getSize() const {
    return size;
}

void Memory::write(UINT32 address, UINT32 value) {

    for (int i = 0; i < 4; i++) {
        INT32 b = (value >> (i * 8)) & 0x000000FF;

        if (address + 1 < this->size)
            this->self[address + i] = (BYTE) b;
        else{
            throw std::invalid_argument("invalid memory adress: " + std::to_string(address));
        }
    }

}

UINT32 Memory::read(UINT32 address) const {

    INT32 ret = 0x00000000;

    for (int i = 0; i < 4; i++) {

        if (address + 1 < this->size) {

            INT32 v = this->self[address + i] << (i * 8);
            ret = ret | v;

        } else {

            throw std::invalid_argument("invalid memory adress: " + std::to_string(address));

        }

    }

    return ret;

}

void Memory::reset() {
    for (int i = 0; i < this->size; i++)
        this->self[i] = 0;
}

std::string Memory::getJson() const {

    std::stringbuf buffer;
    std::ostream os(&buffer);

    os << "{ \"size\":" << this->size << ", \"self\":[";

    int i = 0;
    for (; i < this->size - 4; i += 4) {
        os << "\"" << std::setfill('0') << std::setw(8) << std::hex << i << ": ";
        os << std::setw(2) << (unsigned) this->self[i] << " ";
        os << std::setw(2) << (unsigned) this->self[i + 1] << " ";
        os << std::setw(2) << (unsigned) this->self[i + 2] << " ";
        os << std::setw(2) << (unsigned) this->self[i + 3] << "\", ";
    }
    if (this->size) {
        os << "\"" << std::setfill('0') << std::setw(8) << std::hex << i << ": ";
        os << std::setw(2) << (unsigned) this->self[i] << " ";
        os << std::setw(2) << (unsigned) this->self[i + 1] << " ";
        os << std::setw(2) << (unsigned) this->self[i + 2] << " ";
        os << std::setw(2) << (unsigned) this->self[i + 3] << "\"";
    }

    os << "] }";

    return buffer.str();

}

std::ostream& operator<<(std::ostream& os, const Memory& obj) {
    for (int i = 0; i < obj.size; i += 4) {
        os << std::setfill('0') << std::setw(8) << std::hex << i << ": ";
        os << std::setw(2) << (unsigned) obj.self[i] << " ";
        os << std::setw(2) << (unsigned) obj.self[i + 1] << " ";
        os << std::setw(2) << (unsigned) obj.self[i + 2] << " ";
        os << std::setw(2) << (unsigned) obj.self[i + 3] << std::endl;
    }
    return os;
}
