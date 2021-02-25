/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ctrl.h
 * Author: ronaldo
 *
 * Created on 16 de Fevereiro de 2021, 16:24
 */

#ifndef CTRL_H
#define CTRL_H

#include "Memory.h"
#include "ToJson.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>

class Ctrl : public ToJson
{
public:
    Ctrl();
    Ctrl(const Ctrl &orig);
    virtual ~Ctrl();

    virtual std::string getJson() const
    {

        std::stringbuf buffer;
        std::ostream os(&buffer);

        os << "{ ";

        os << "\"PcWriteCond\":\"" << std::bitset<1>(this->get_PcWriteCond()) << "\", ";
        os << "\"PcWrite\":\"" << std::bitset<1>(this->get_PcWrite()) << "\", ";
        os << "\"IorD\":\"" << std::bitset<1>(this->get_IorD()) << "\", ";
        os << "\"MemRead\":\"" << std::bitset<1>(this->get_MemRead()) << "\", ";
        os << "\"MemWrite\":\"" << std::bitset<1>(this->get_MemWrite()) << "\", ";
        os << "\"MemToReg\":\"" << std::bitset<1>(this->get_MemToReg()) << "\", ";
        os << "\"IRWrite\":\"" << std::bitset<1>(this->get_IRWrite()) << "\", ";
        os << "\"CauseWrite\":\"" << std::bitset<1>(this->get_CauseWrite()) << "\", ";
        os << "\"IntCause\":\"" << std::bitset<1>(this->get_IntCause()) << "\", ";
        os << "\"EPCWrite\":\"" << std::bitset<1>(this->get_EPCWrite()) << "\", ";
        os << "\"PCSource\":\"" << std::bitset<2>(this->get_PCSource()) << "\", ";
        os << "\"ALUOp\":\"" << std::bitset<2>(this->get_ALUOp()) << "\", ";
        os << "\"ALUSrcB\":\"" << std::bitset<2>(this->get_ALUSrcB()) << "\", ";
        os << "\"ALUSrcA\":\"" << std::bitset<1>(this->get_ALUSrcA()) << "\", ";
        os << "\"RegWrite\":\"" << std::bitset<1>(this->get_RegWrite()) << "\", ";
        os << "\"RegDst\":\"" << std::bitset<1>(this->get_RegDst()) << "\"";

        os << " }";

        return buffer.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const Ctrl &obj)
    {

        os << "PcWriteCond: " << std::bitset<1>(obj.get_PcWriteCond()) << std::endl;
        os << "    PcWrite: " << std::bitset<1>(obj.get_PcWrite()) << std::endl;
        os << "       IorD: " << std::bitset<1>(obj.get_IorD()) << std::endl;
        os << "    MemRead: " << std::bitset<1>(obj.get_MemRead()) << std::endl;
        os << "   MemWrite: " << std::bitset<1>(obj.get_MemWrite()) << std::endl;
        os << "   MemToReg: " << std::bitset<1>(obj.get_MemToReg()) << std::endl;
        os << "    IRWrite: " << std::bitset<1>(obj.get_IRWrite()) << std::endl;
        os << " CauseWrite: " << std::bitset<1>(obj.get_CauseWrite()) << std::endl;
        os << "   IntCause: " << std::bitset<1>(obj.get_IntCause()) << std::endl;
        os << "   EPCWrite: " << std::bitset<1>(obj.get_EPCWrite()) << std::endl;
        os << "   PCSource: " << std::bitset<2>(obj.get_PCSource()) << std::endl;
        os << "      ALUOp: " << std::bitset<2>(obj.get_ALUOp()) << std::endl;
        os << "    ALUSrcB: " << std::bitset<2>(obj.get_ALUSrcB()) << std::endl;
        os << "    ALUSrcA: " << std::bitset<1>(obj.get_ALUSrcA()) << std::endl;
        os << "   RegWrite: " << std::bitset<1>(obj.get_RegWrite()) << std::endl;
        os << "     RegDst: " << std::bitset<1>(obj.get_RegDst()) << std::endl;

        return os;
    }

    void set_PcWriteCond(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 0, 1);
    }

    void set_PcWrite(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 1, 1);
    }

    void set_IorD(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 2, 1);
    }

    void set_MemRead(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 3, 1);
    }

    void set_MemWrite(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 4, 1);
    }

    void set_MemToReg(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 5, 1);
    }

    void set_IRWrite(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 6, 1);
    }

    void set_CauseWrite(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 7, 1);
    }

    void set_IntCause(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 8, 1);
    }

    void set_EPCWrite(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 9, 1);
    }

    void set_PCSource(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 11, 2);
    }

    void set_ALUOp(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 13, 2);
    }

    void set_ALUSrcB(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 15, 2);
    }

    void set_ALUSrcA(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 16, 1);
    }

    void set_RegWrite(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 17, 1);
    }

    void set_RegDst(UINT32 bits)
    {
        this->value = set_bits(this->value, bits, 18, 1);
    }

    UINT32 get_PcWriteCond() const
    {
        return get_bits(this->value, 0, 1);
    }

    UINT32 get_PcWrite() const
    {
        return get_bits(this->value, 1, 1);
    }

    UINT32 get_IorD() const
    {
        return get_bits(this->value, 2, 1);
    }

    UINT32 get_MemRead() const
    {
        return get_bits(this->value, 3, 1);
    }

    UINT32 get_MemWrite() const
    {
        return get_bits(this->value, 4, 1);
    }

    UINT32 get_MemToReg() const
    {
        return get_bits(this->value, 5, 1);
    }

    UINT32 get_IRWrite() const
    {
        return get_bits(this->value, 6, 1);
    }

    UINT32 get_CauseWrite() const
    {
        return get_bits(this->value, 7, 1);
    }

    UINT32 get_IntCause() const
    {
        return get_bits(this->value, 8, 1);
    }

    UINT32 get_EPCWrite() const
    {
        return get_bits(this->value, 9, 1);
    }

    UINT32 get_PCSource() const
    {
        return get_bits(this->value, 11, 2);
    }

    UINT32 get_ALUOp() const
    {
        return get_bits(this->value, 13, 2);
    }

    UINT32 get_ALUSrcB() const
    {
        return get_bits(this->value, 15, 2);
    }

    UINT32 get_ALUSrcA() const
    {
        return get_bits(this->value, 16, 1);
    }

    UINT32 get_RegWrite() const
    {
        return get_bits(this->value, 17, 1);
    }

    UINT32 get_RegDst() const
    {
        return get_bits(this->value, 18, 1);
    }

private:
    UINT32 value = 0;

    static unsigned mask_1_0(unsigned bit_index, unsigned bit_number)
    {

        unsigned max = std::max((unsigned)0, 32 - bit_number);
        return (0xffffffff >> max) << (bit_index - bit_number + 1);
    }

    static unsigned mask_0_1(unsigned bit_index, unsigned bit_number)
    {

        return mask_1_0(bit_index, bit_number) ^ 0xffffffff;
    }

    static unsigned mask_0_bits(unsigned bits, unsigned bit_index, unsigned bit_number)
    {

        unsigned max1 = std::max((unsigned)0, 32 - bit_number);
        unsigned max2 = std::max((unsigned)0, 31 - bit_index);
        return (bits << max1) >> max2;
    }

    static unsigned set_bit_0(unsigned value, unsigned bit_index, unsigned bit_number)
    {

        return value & mask_0_1(bit_index, bit_number);
    }

    static unsigned set_bit_1(unsigned value, unsigned bit_index, unsigned bit_number)
    {

        return value | mask_1_0(bit_index, bit_number);
    }

    static unsigned set_bits(unsigned value, unsigned bits, unsigned bit_index, unsigned bit_number)
    {
        unsigned mask = mask_0_bits(bits, bit_index, bit_number); // Mask com os bits a serem substituidos
        unsigned mask1 = mask_1_0(bit_index, bit_number); // Masks com 1 nas posições a serem substituidas
        unsigned new_value = value & (~mask1); // Zera as posições a serem substituidas
        return new_value | mask; // Aplica a máscara
    }

    static unsigned get_bits(unsigned value, unsigned bit_index, unsigned bit_number)
    {
        unsigned max1 = std::max((unsigned)0, 32 - bit_number);
        unsigned max2 = std::max((unsigned)0, 31 - bit_index);
        return (value << max2) >> max1;
    }
};

#endif /* CTRL_H */
