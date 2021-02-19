/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State6.cpp
 * Author: ronaldo
 * 
 * Created on 14 de Fevereiro de 2021, 17:42
 */

#include "State6.h"
#include "State7.h"
#include "Machine.h"

State6::State6():State( "State 6: Execução (Tipo R)") {}

State6::State6(const State6& orig):State(orig) {}

State6::~State6() {}

State* State6::getNext(Machine *machine)const{    
    machine->execute_alu_op(); 
    machine->set_ctrl_state_6();
    return new State7();
}