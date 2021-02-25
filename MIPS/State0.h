/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State0.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 09:04
 */

#ifndef STATE0_H
#define STATE0_H
#include "State.h"
#include "State1.h"

class State0 : public State{
public:
    State0();
    State0(const State0& orig);
    State0(Machine*);
    virtual ~State0();    
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE0_H */

