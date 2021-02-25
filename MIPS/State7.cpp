/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State7.cpp
 * Author: ronaldo
 * 
 * Created on 14 de Fevereiro de 2021, 17:52
 */

#include "State7.h"
#include "State0.h"
#include "Machine.h"
#include "IR.h"

State7::State7():State("State 7: Conclusão de Tipo R") {}

State7::State7(const State7& orig):State(orig){}

State7::State7(Machine *mach):State("State 7: Conclusão de Tipo R"){
    mach->set_ctrl_state_7();
    switch (mach->getOp())
    {
    case IR::OPCODE::I_Type_ADDI:
        mach->completion_TypeI();
        break;
    case IR::OPCODE::R_Type:
        mach->completion_TypeR();
    default:
        break;
    }
}

State7::~State7() {}

State* State7::getNext(Machine *machine)const{     
    return new State0(machine);
}

