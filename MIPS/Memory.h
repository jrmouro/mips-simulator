/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 06:05
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "ToJson.h"
#include <iostream>
#include <sstream> 
#include <iomanip>
#include "Resettable.h"

typedef unsigned UINT32;
typedef int INT32;
typedef unsigned char BYTE;

class Memory : public ToJson, public Resettable{
    
public:
       
    Memory(UINT32 size);
    Memory(const Memory& orig);
    virtual ~Memory();    
    void write(UINT32 address, UINT32 value);    
    UINT32 read(UINT32 address)const;  
    virtual void reset();
    UINT32 getSize() const;
    
    virtual std::string getJson() const {

        std::stringbuf buffer;
        std::ostream os(&buffer);
        
        os << "{ \"self\":\"" << *this << "\" }";

        return buffer.str();

    }
        
    friend std::ostream& operator<<(std::ostream& os, const Memory& obj);

    
private:
    BYTE *self = 0;
    UINT32 size;
};

#endif /* MEMORY_H */

