/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State8.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 19:22
 */

#include "State8.h"
#include "State0.h"
#include "Machine.h"

State8::State8():State( "State 8: Conclusão do desvio"){}

State8::State8(const State8& orig):State(orig) {}

State8::~State8() {}

State* State8::getNext(Machine *machine)const{
    
    machine->set_ctrl_state_8();
    
    switch(machine->getOp()){
        case IR::OPCODE::I_Type_BEQ:
            machine->pc_recebe_aluout_desvio_cond_equal();
            break;
        case IR::OPCODE::I_Type_BNE:
            machine->pc_recebe_aluout_desvio_cond_not_equal();        
    }
    
    return new State0();
    
}

