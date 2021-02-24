/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State10.cpp
 * Author: Vitor
 * 
 * Created on 23 de Fevereiro de 2021, 18:09
 */

#include "State10.h"
#include "State7.h"
#include "Machine.h"

State10::State10():State( "State 10: Execução (Tipo I)") {}

State10::State10(const State10& orig):State(orig) {}

State10::~State10() {}

State* State10::getNext(Machine *machine)const{    
    machine->execute_alu_op(); 
    machine->set_ctrl_state_10();
    return new State7();
}