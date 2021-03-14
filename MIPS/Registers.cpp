/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Registers.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 07:06
 */

#include "Registers.h"

Registers::Registers() {
}

Registers::Registers(const Registers& other) {
    for (int i = 0; i < 32; i++)
        this->regs[i] = other.regs[i];
}

Registers::~Registers() {
}

void Registers::write(UINT32 address, UINT32 value) {
    if (address < 32) {
        this->regs[address].setValue(value);
    } else {
        throw std::invalid_argument("invalid memory adress: " + std::to_string(address));
    }
}

UINT32 Registers::read(UINT32 address)const {
    if (address < 32) {
        return this->regs[address].getValue();
    } else {
        throw std::invalid_argument("invalid memory adress: " + std::to_string(address));
    }
    return 0;
}

void Registers::reset() {
    for (int i = 0; i < 32; i++)
        this->regs[i].setValue(0);
}

std::string Registers::getJson() const {

    std::stringbuf buffer;
    std::ostream os(&buffer);

    os << "{ ";

    os << "\"$Ze\":\"" << this->regs[0] << "\", ";
    os << "\"$at\":\"" << this->regs[1] << "\", ";
    for (int i = 0; i < 2; i++) os << "\"$v" << i << "\":\"" << this->regs[2 + i] << "\", ";
    for (int i = 0; i < 4; i++) os << "\"$a" << i << "\":\"" << this->regs[4 + i] << "\", ";
    for (int i = 0; i < 8; i++) os << "\"$t" << i << "\":\"" << this->regs[8 + i] << "\", ";
    for (int i = 0; i < 8; i++) os << "\"$s" << i << "\":\"" << this->regs[16 + i] << "\", ";
    for (int i = 0; i < 2; i++) os << "\"$t" << i + 8 << "\":\"" << this->regs[24 + i] << "\", ";
    for (int i = 0; i < 2; i++) os << "\"$k" << i << "\":\"" << this->regs[26 + i] << "\", ";
    os << "\"$gp\":\"" << this->regs[28] << "\", ";
    os << "\"$sp\":\"" << this->regs[29] << "\", ";
    os << "\"$fp\":\"" << this->regs[30] << "\", ";
    os << "\"$ra\":\"" << this->regs[31] << "\"";

    os << " }";

    return buffer.str();

}

std::ostream& operator<<(std::ostream& os, const Registers& obj) {

    //os << std::setfill('0') << std::setw(4) << std::hex;
    os << "$Ze: " << obj.regs[0] << std::endl;
    os << "$at: " << obj.regs[1] << std::endl;
    for (int i = 0; i < 2; i++) os << "$v" << i << ": " << obj.regs[2 + i] << std::endl;
    for (int i = 0; i < 4; i++) os << "$a" << i << ": " << obj.regs[4 + i] << std::endl;
    for (int i = 0; i < 8; i++) os << "$t" << i << ": " << obj.regs[8 + i] << std::endl;
    for (int i = 0; i < 8; i++) os << "$s" << i << ": " << obj.regs[16 + i] << std::endl;
    for (int i = 0; i < 2; i++) os << "$t" << i + 8 << ": " << obj.regs[24 + i] << std::endl;
    for (int i = 0; i < 2; i++) os << "$k" << i << ": " << obj.regs[26 + i] << std::endl;
    os << "$gp: " << obj.regs[28] << std::endl;
    os << "$sp: " << obj.regs[29] << std::endl;
    os << "$fp: " << obj.regs[30] << std::endl;
    os << "$ra: " << obj.regs[31] << std::endl;

    return os;

}