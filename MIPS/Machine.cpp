/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Machine.cpp
 * Author: ronaldo
 * 
 * Created on 13 de Fevereiro de 2021, 08:36
 */

#include <iostream>
#include "Machine.h"
#include "Programm.h"
#include "State.h"
#include "State0.h"
#include "Programm.h"

Machine::Machine(UINT32 mem_size) : mem(mem_size * 4), prog(new Programm()) {}

Machine::Machine(const Machine& other) :
        A(other.A), 
        B(other.B), 
        PC(other.PC), 
        MDR(other.MDR), 
        aluout(other.aluout), 
        inst_count(other.inst_count), 
        clock_count(other.clock_count), 
        ctrl(other.ctrl), 
        mem(other.mem), 
        regs(other.regs), 
        ir(other.ir), 
        state(other.state),
        prog(new Programm(*other.prog)){    }

Machine::~Machine() {
    if (this->state)
        delete this->state;
    
    if(this->prog)
        delete this->prog;
}

bool Machine::clock(/*const std::function<void(const Machine&)> fun*/) {

    if (this->inst_count > 0) {

        if (this->state) {

            State *aux = this->state->getNext(this);
            delete this->state;
            this->state = aux;

        } else {
            this->state = new State0(this);
        }

        if ((*this->state) == State0() && this->clock_count > 0) {
            
            this->inst_count--;
        }
        
        this->clock_count++;
    
        //fun(*this);
        
        return true;

    } 
    
    return false;
    
}

void Machine::loadProgramm(UINT32 address, const Programm &prog){
    
    std::vector<UINT32> code = prog.getCode();
    
    if(this->prog)
        delete this->prog;
    
    this->prog = new Programm(prog);

    //this->reset();

    this->PC.setValue(address);
    this->inst_count = code.size();
    
    
    for (unsigned int i = 0; i < code.size(); i++) {
        this->mem.write(address + (i * 4), code[i]);
    }
}



void Machine::loadProgram(
        UINT32 address, 
        std::string filename, const std::function<void(const Machine&)> fun
) {
    
    std::vector<UINT32> code = Programm::read(filename);
    
    if(this->prog)
        delete this->prog;
    
    this->prog = new Programm(code);

    this->PC.setValue(address);
    this->inst_count = code.size();
    
    
    for (unsigned int i = 0; i < code.size(); i++) {
        this->mem.write(address + (i * 4), code[i]);
    }

}

void Machine::ir_recebe_mem_pc() {
    this->ir.setValue(this->mem.read(this->PC.getValue()));
}

void Machine::pc_recebe_pc_mais_4() {
    this->PC.setValue(PC.getValue() + 4);
}

void Machine::a_recebe_reg_data_1() {
    this->A.setValue(regs.read(this->ir.getRS()));
}

void Machine::b_recebe_reg_data_2() {
    this->B.setValue(regs.read(this->ir.getRT()));
}

void Machine::aluout_recebe_pc_mais_ext_2() {
    this->aluout.setValue(this->PC.getValue() + (this->ir.getImmediateExt() << 2));
}

BYTE Machine::getOp() {
    return this->ir.getOP();
}

void Machine::address_memory_calc() {
    this->aluout.setValue(this->A.getValue() + this->ir.getImmediateExt());
}

void Machine::mdr_recebe_mem_aluout() {
    this->MDR.setValue(this->mem.read(this->aluout.getValue()));
}

void Machine::reg_recebe_mdr() {
    this->regs.write(this->ir.getRT(), this->MDR.getValue());
}

void Machine::mem_aluout_recebe_b() {
    this->mem.write(this->aluout.getValue(), this->B.getValue());
}

void Machine::execute_alu_op() {

    if (this->ir.getOP() == IR::OPCODE::I_Type_ADDI) {

        int i = (int) this->ir.getImmediateExt();
        this->aluout.setValue((int) this->A.getValue() + i);

    } else {

        switch (this->ir.getfunct()) {

            case IR::ADD:
                this->aluout.setValue((int) this->A.getValue() + (int) this->B.getValue());
                break;
            case IR::SUB:
                this->aluout.setValue((int) this->A.getValue() - (int) this->B.getValue());
                break;
            case IR::AND:
                this->aluout.setValue(this->A.getValue() & this->B.getValue());
                break;
            case IR::OR:
                this->aluout.setValue(this->A.getValue() | this->B.getValue());
                break;
            case IR::SLT:
                if (this->A.getValue() < this->B.getValue())
                    this->aluout.setValue(1);
                else
                    this->aluout.setValue(0);
                break;
            case IR::SLL:
                this->aluout.setValue(this->A.getValue() << this->B.getValue());
                break;
            case IR::SRL:
                this->aluout.setValue(this->A.getValue() >> this->B.getValue());
                break;
            case IR::JR:
                this->aluout.setValue(this->A.getValue());
                break;
        }

    }

}

void Machine::completion_TypeR() {
    this->regs.write(this->ir.getRD(), this->aluout.getValue());
}

void Machine::completion_TypeI() {
    this->regs.write(this->ir.getRT(), this->aluout.getValue());
}

void Machine::pc_recebe_aluout_desvio_cond_equal() {
    if (this->A.getValue() == this->B.getValue())
        this->PC.setValue(aluout.getValue());
}

void Machine::pc_recebe_aluout_desvio_cond_not_equal() {
    if (this->A.getValue() != this->B.getValue())
        this->PC.setValue(aluout.getValue());
}

void Machine::pc_recebe_address() {

    UINT32 pc4_right_bits = (PC.getValue() >> 28) << 28;
    UINT32 address_left2 = ir.getAddress() << 2;

    this->PC.setValue(pc4_right_bits | address_left2);
    if (this->ir.getOP() == IR::OPCODE::I_Type_JAL) {
        this->regs.write(31, this->PC.getValue());
    }

}

std::ostream& operator<<(std::ostream& os, const Machine& obj) {

    if (obj.state)
        os << "State: " << *obj.state << std::endl << std::endl;

    os << "Inst_count: " << obj.inst_count << std::endl << std::endl;

    os << "Clock_count: " << obj.clock_count << std::endl << std::endl;

    os << "Ctrl:" << std::endl << obj.ctrl << std::endl << std::endl;

    os << "    PC: " << obj.PC << std::endl << std::endl;
    os << "   MDR: " << obj.MDR << std::endl << std::endl;
    os << "     A: " << obj.A << std::endl << std::endl;
    os << "     B: " << obj.B << std::endl << std::endl;
    os << "ALUOUT: " << obj.aluout << std::endl << std::endl;
    os << "    IR: " << obj.ir << std::endl << std::endl;

    os << "Registers:" << std::endl << obj.regs << std::endl << std::endl;
    os << "Memory:" << std::endl << obj.mem << std::endl << std::endl;


    return os;
}

std::string Machine::getJson() const {

        std::stringbuf buffer;
        std::ostream os(&buffer);
        
        os << "{ ";
        
        if(this->prog){
            
            os << "\"program\":" << this->prog->getJson() << ", ";
            
        } else {
            
            os << "\"program\":null, ";
            
        }
        
        
        
        if(this->state){
            
            os << "\"state\":" << state->getJson() << ", ";
            
        } else {
            
            os << "\"state\":null, ";
            
        }
        
        os << "\"inst_count\":" << inst_count << ", ";
        os << "\"clock_count\":" << clock_count << ", ";
        os << "\"A\":" << A.getJson() << ", ";
        os << "\"B\":" << B.getJson() << ", ";
        os << "\"PC\":" << PC.getJson() << ", ";
        os << "\"MDR\":" << MDR.getJson() << ", ";
        os << "\"aluout\":" << aluout.getJson() << ", ";
        os << "\"IR\":" << ir.getJson() << ", ";
        os << "\"ctrl\":" << ctrl.getJson() << ", ";
        os << "\"regs\":" << regs.getJson() << ", ";
        os << "\"mem\":" << mem.getJson();
        
        os << " }";

        return buffer.str();

    }