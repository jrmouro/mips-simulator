/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Register.h
 * Author: ronaldo
 *
 * Created on 17 de Fevereiro de 2021, 13:35
 */

#ifndef REGISTER_H
#define REGISTER_H

#include "Resettable.h"
#include "Memory.h"
#include "ToJson.h"
#include <iostream>
#include <sstream> 
#include <bitset>

class Register : public ToJson, public Resettable{
public:
    Register(){}
    Register(const Register& orig):value(orig.value){}
    virtual ~Register(){}
    
    virtual std::string getJson() const {

        std::stringbuf buffer;
        std::ostream os(&buffer);
        
        os << "{ \"value\":\"" << std::bitset<32>(this->value) << "\" }";

        return buffer.str();

    }
    
    friend std::ostream& operator<<(std::ostream& os, const Register& obj) {
        os << std::bitset<32>(obj.value);
        return os;
    }

    UINT32 getValue() const {
        return value;
    }

    void setValue(UINT32 value) {
        this->value = value;
    }
    
    void reset(){
        this->value = 0;
    }
    
    Register& operator=(const Register& right) {
        if (this == &right)
            return *this;
        this->value = right.value;
        return *this;
    }
    
    Register operator+(const Register& right) const {
        Register result(*this); // Fazer uma cópia de mim mesmo.
        result += right; // Reutilizar a designação composta
        return result;
    }

    Register& operator++() {
        this->value++;
        return *this;
    }

    Register operator++(int) {
        Register result(*this); // Fazer uma cópia de mim mesmo.
        operator++(); // Reutilizar o operador de prefixo
        return result;
    }

    Register& operator+=(const Register& right) {
        this->value += right.value;
        return *this;
    }

    Register operator-(const Register& right) const {
        Register result(*this);
        result -= right;
        return result;
    }

    Register& operator--() {
        this->value--;
        return *this;
    }

    Register operator--(int) {
        Register result(*this); // Fazer uma cópia de mim mesmo.
        operator--(); // Reutilizar o operador de prefixo
        return result;
    }

    Register& operator-=(const Register& right) {
        this->value -= right.value;
        return *this;
    }

    Register operator&(const Register& right) const {
        Register result(*this); // Fazer uma cópia de mim mesmo.
        result &= right; // Reutilizar a designação composta
        return result;
    }

    Register& operator&=(const Register& right) {
        this->value &= right.value;
        return *this;
    }

    Register operator ^(const Register& right) const {
        Register result(*this); // Fazer uma cópia de mim mesmo.
        result ^= right; // Reutilizar a designação composta
        return result;
    }

    Register& operator^=(const Register& right) {
        this->value ^= right.value;
        return *this;
    }

    Register operator|(const Register& right) const {
        Register result(*this); // Fazer uma cópia de mim mesmo.
        result |= right; // Reutilizar a designação composta
        return result;
    }

    Register& operator|=(const Register& right) {
        this->value |= right.value;
        return *this;
    }

    Register operator~() const {
        ~this->value;
        return *this;
    }
    
    bool operator!=(const Register& right) const {
        bool result = !(*this == right); // Reusar operador de igualdade
        return result;
    }

    bool operator<(const Register& right) const {
        return right > * this; // Reusar o operador maior que
    }

    bool operator<=(const Register& right) const {
        return !(*this > right); // Reusar o operador maior que
    }

    bool operator==(const Register& right) const {
        bool result = this->value == right.value; // Comparar direito e *this aqui
        return result;
    }

    bool operator>(const Register& right) const {
        return this->value > right.value;
    }

    bool operator>=(const Register& right) const {
        return !(right > * this); // Reusar o operador maior que
    }


private:
    
    UINT32 value = 0;
    
};

#endif /* REGISTER_H */

