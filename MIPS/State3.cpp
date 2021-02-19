/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State3.cpp
 * Author: ronaldo
 * 
 * Created on 15 de Fevereiro de 2021, 04:34
 */

#include "State3.h"
#include "State4.h"
#include "Machine.h"

State3::State3():State("State 3: Acesso à memória(leitura)")  {}

State3::State3(const State3& orig):State(orig) {}

State3::~State3() {}

State* State3::getNext(Machine *machine)const{
    machine->set_ctrl_state_3();
    machine->mdr_recebe_mem_aluout();    
    return new State4();
}


