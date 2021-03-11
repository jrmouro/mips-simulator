/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State1.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 09:04
 */

#include "State0.h"
#include "State1.h"
#include "Machine.h"
#include "IR.h"

State0::State0() : State("State 0: Busca da Instrução") {}

State0::State0(const State0 &orig) : State(orig) {}

State0::State0(Machine *mach) : State("State 0: Busca da Instrução")
{
    mach->set_ctrl_state_0();
    mach->ir_recebe_mem_pc();
};

State0::~State0() {}

State *State0::getNext(Machine *machine) const
{
    if(machine->getOp() != IR::OPCODE::Exit)
        return new State1(machine);
    return new State0(machine);
}
