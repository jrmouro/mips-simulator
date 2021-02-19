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

State7::State7():State("State 7: Conclusão de Tipo R") {}

State7::State7(const State7& orig):State(orig){}

State7::~State7() {}

State* State7::getNext(Machine *machine)const{    
    machine->set_ctrl_state_7();
    machine->completion_TypeR();    
    return new State0();
}

