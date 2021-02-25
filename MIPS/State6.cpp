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

State6::State6() : State("State 6: Execução (Tipo R)") {}

State6::State6(const State6 &orig) : State(orig) {}

State6::State6(Machine *mach) : State("State 6: Execução (Tipo R)")
{
    mach->execute_alu_op();
    mach->set_ctrl_state_6();
}

State6::~State6() {}

State *State6::getNext(Machine *machine) const
{
    return new State7(machine);
}