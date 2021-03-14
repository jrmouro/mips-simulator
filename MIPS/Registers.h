/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Registers.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 07:06
 */

#ifndef REGISTERS_H
#define REGISTERS_H

#include "Memory.h"
#include "ToJson.h"
#include "Register.h"
#include "Resettable.h"

class Registers : public ToJson, public Resettable {
    
public:
    Registers();
    Registers(const Registers& other);
    virtual ~Registers();
    void write(UINT32 address, UINT32 value);
    UINT32 read(UINT32 address)const;
    void reset();    
    virtual std::string getJson() const;
    friend std::ostream& operator<<(std::ostream& os, const Registers& obj);

private:

    Register regs[32];

};

#endif /* REGISTERS_H */

