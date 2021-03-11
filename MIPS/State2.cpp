/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State2.cpp
 * Author: ronaldo
 * 
 * Created on 15 de Fevereiro de 2021, 03:51
 */

#include "State2.h"
#include "State3.h"
#include "State5.h"
#include "StateException.h"
#include "Machine.h"

State2::State2() : State("State 2: Cálculo do endereço de memória") {}

State2::State2(const State2 &orig) : State(orig) {}

State2::State2(Machine *mach) : State("State 2: Cálculo do endereço de memória")
{
    mach->address_memory_calc();
    mach->set_ctrl_state_2();
}

State2::~State2() {}

State *State2::getNext(Machine *machine) const
{
    switch (machine->getOp())
    {
    case IR::I_Type_LW:
        return new State3(machine);
    case IR::I_Type_SW:
        return new State5(machine);
    }

    return new StateException("opcode does not found");
    
}
