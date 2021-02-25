/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State10.h
 * Author: Vitor
 *
 * Created on 23 de Fevereiro de 2021, 18:09
 */

#ifndef STATE10_H
#define STATE10_H

#include "State.h"

class State10 : public State
{
public:
    State10();
    State10(const State10 &orig);
    State10(Machine*);
    virtual ~State10();
    virtual State *getNext(Machine *machine) const;
};

#endif /* STATE10_H */
