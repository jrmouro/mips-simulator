/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State5.cpp
 * Author: ronaldo
 * 
 * Created on 15 de Fevereiro de 2021, 04:43
 */

#include "State5.h"
#include "State0.h"
#include "Machine.h"

State5::State5() : State("State 5: Acesso à memória(escrita)") {}

State5::State5(const State5 &orig) : State(orig) {}

State5::State5(Machine *mach) : State("State 5: Acesso à memória(escrita)")
{
    mach->set_ctrl_state_5();
    mach->mem_aluout_recebe_b();
}

State5::~State5() {}

State *State5::getNext(Machine *machine) const
{
    return new State0(machine);
}
