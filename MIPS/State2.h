/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State2.h
 * Author: ronaldo
 *
 * Created on 15 de Fevereiro de 2021, 03:51
 */

#ifndef STATE2_H
#define STATE2_H

#include "State.h"

class State2 : public State {
public:
    State2();
    State2(const State2& orig);
    State2(Machine*);
    virtual ~State2();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE2_H */

