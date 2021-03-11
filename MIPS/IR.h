/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IR.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 18:46
 */

#ifndef IR_H
#define IR_H

#include "Memory.h"
#include "Register.h"
#include <iostream>
#include <bitset>

class IR : public Register {
public:

    enum OPCODE {
        R_Type = 0,
        I_Type_LW = 35,
        I_Type_SW = 43,
        I_Type_BEQ = 4,
        I_Type_BNE = 5,
        I_Type_ADDI = 8,
        I_Type_J = 2,
        I_Type_JAL = 3,
        Exit = 63
    };

    enum FUNCT {
        ADD = 32,
        SUB = 34,
        AND = 36,
        OR = 37,
        SLT = 42,
        SLL = 0,
        SRL = 2,
        JR = 8,
        BREAK = 13

    };

    IR() : Register() {    }

    IR(const IR& orig) : Register(orig) {    }

    virtual ~IR() {    }
    
    friend std::ostream& operator<<(std::ostream& os, const IR& obj) {
        os << (Register)obj;
        return os;
    }

    BYTE getOP() {
        return getValue() >> 26;
    }

    BYTE getRS() {
        return (getValue() << 6) >> 27;
    }

    BYTE getRT() {
        return (getValue() << 11) >> 27;
    }

    BYTE getRD() {
        
        return (getValue() << 16) >> 27;
    }

    BYTE getShamt() {
        return (getValue() << 21) >> 27;
    }

    BYTE getfunct() {
        return (getValue() << 26) >> 26;
    }

    UINT32 getImmediate() {
        return getValue() & 0x0000ffff;
    }

    UINT32 getImmediateExt() {

        UINT32 aux = getValue() & 0x00008000;

        if (aux == 0)
            return getValue() & 0x0000ffff;

        return getValue() | 0xffff0000;
    }

    UINT32 getAddress() {
        return (getValue() << 6) >> 6;
    }


};

#endif /* IR_H */

