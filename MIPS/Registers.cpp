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

Registers::Registers() {}

Registers::Registers(const Registers& other) {
    for (int i = 0; i < 32; i++)
        this->regs[i] = other.regs[i];
}

Registers::~Registers() {}