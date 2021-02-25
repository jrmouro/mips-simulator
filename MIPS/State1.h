/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State1.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 09:08
 */

#ifndef STATE1_H
#define STATE1_H

#include "State.h"

class State1 : public State{
public:
    State1();
    State1(const State1& orig);
    State1(Machine*);
    virtual ~State1();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE1_H */

