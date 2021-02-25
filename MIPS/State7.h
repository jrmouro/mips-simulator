/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State7.h
 * Author: ronaldo
 *
 * Created on 14 de Fevereiro de 2021, 17:52
 */

#ifndef STATE7_H
#define STATE7_H

#include "State.h"

class State7 : public State{
public:
    State7();
    State7(const State7& orig);
    State7(Machine*);
    virtual ~State7();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE7_H */

