/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State4.cpp
 * Author: ronaldo
 * 
 * Created on 15 de Fevereiro de 2021, 04:49
 */

#include "State4.h"
#include "State0.h"
#include "Machine.h"

State4::State4() : State("State 4: conclusão da leitura da memória") {}

State4::State4(const State4 &orig) : State(orig) {}

State4::State4(Machine *mach) : State("State 4: conclusão da leitura da memória")
{
    mach->set_ctrl_state_4();
    mach->reg_recebe_mdr();
}

State4::~State4() {}

State *State4::getNext(Machine *machine) const
{
    return new State0(machine);
}
