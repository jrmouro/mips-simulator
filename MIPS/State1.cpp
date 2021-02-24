/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State2.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 09:08
 */

#include "State1.h"
#include "State2.h"
#include "State6.h"
#include "State8.h"
#include "State9.h"
#include "State10.h"
#include "IR.h"
#include "StateException.h"
#include "Machine.h"

State1::State1():State("State 1: Decodifica Instrução / Busca Registradores") {}

State1::State1(const State1& orig):State(orig){}

State1::~State1() {}

State* State1::getNext(Machine *machine)const{   
    
    machine->pc_recebe_pc_mais_4();
    machine->a_recebe_reg_data_1();    
    machine->b_recebe_reg_data_2();    
    machine->aluout_recebe_pc_mais_ext_2();
    machine->set_ctrl_state_1();

    switch(machine->getOp()){
        
        case IR::OPCODE::R_Type:
            return new State6();
        case IR::OPCODE::I_Type_ADDI:
            return new State10();
        case IR::OPCODE::I_Type_LW:
            return new State2();
        case IR::OPCODE::I_Type_SW:
            return new State2();
        case IR::OPCODE::I_Type_BEQ:
            return new State8();
        case IR::OPCODE::I_Type_BNE:
            return new State8();
        case IR::OPCODE::I_Type_J:            
            return new State9();
        case IR::OPCODE::I_Type_JAL:            
            return new State9();
    }
    
    return new StateException();

}

