/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State9.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 19:22
 */

#include "State9.h"
#include "State0.h"
#include "Machine.h"

State9::State9() : State("State 9: Conclusão do salto") {}

State9::State9(const State9 &orig) : State(orig) {}

State9::State9(Machine *mach) : State("State 9: Conclusão do salto")
{
    mach->set_ctrl_state_9();
    mach->pc_recebe_address();
}

State9::~State9() {}

State *State9::getNext(Machine *machine) const
{
    return new State0(machine);
}
