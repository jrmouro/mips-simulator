/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State5.h
 * Author: ronaldo
 *
 * Created on 15 de Fevereiro de 2021, 04:43
 */

#ifndef STATE5_H
#define STATE5_H

#include "State.h"

class State5 : public State{
public:
    State5();
    State5(const State5& orig);
    virtual ~State5();
    virtual State* getNext(Machine *machine) const;
};

#endif /* STATE5_H */

