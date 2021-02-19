/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State4.h
 * Author: ronaldo
 *
 * Created on 15 de Fevereiro de 2021, 04:49
 */

#ifndef STATE4_H
#define STATE4_H

#include "State.h"

class State4 : public State{
public:
    State4();
    State4(const State4& orig);
    virtual ~State4();
    virtual State* getNext(Machine *machine)const;
};

#endif /* STATE4_H */

