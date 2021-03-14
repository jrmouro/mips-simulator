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
#include <limits>
#include "Machine.h"
#include "Program.h"
#include "State.h"
#include "StateException.h"
#include "State0.h"
#include "Program.h"

Machine::Machine(UINT32 mem_size) : mem(mem_size * 4), prog(new Program()) {
}

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
prog(new Program(*other.prog)) {
}

Machine::~Machine() {
    if (this->state)
        delete this->state;

    if (this->prog)
        delete this->prog;
}

void Machine::reset() {
    this->mem.reset();
    this->regs.reset();
    this->ir.setValue(0);
    this->PC.reset();
    this->A.reset();
    this->B.reset();
    this->MDR.reset();
    this->aluout.reset();
    this->clock_count = this->inst_count = 0;
    this->regs.write(29, this->mem.getSize()); // $sp   
    if (this->state)
        delete state;
    this->state = nullptr;
}

bool Machine::clock(unsigned max_clock = std::numeric_limits<unsigned int>::max()) {

    if (this->getOp() != IR::OPCODE::Exit) {

        if (this->clock_count < max_clock) {

            if (this->state) {

                State *aux = this->state->getNext(this);
                delete this->state;
                this->state = aux;

            } else {
                this->state = new State0(this);
            }

            this->inst_count = this->PC.getValue() / 4;

            this->clock_count++;

            return true;

        } else {

            this->state = new StateException("maximum number of clocks reached");

        }

    }

    return false;

}

//bool Machine::clock() {
//
//    if (this->inst_count > 0) {
//
//        if (this->state) {
//
//            State *aux = this->state->getNext(this);
//            delete this->state;
//            this->state = aux;
//
//        } else {
//            this->state = new State0(this);
//        }
//
//        if ((*this->state) == State0() && this->clock_count > 0) {
//            
//            this->inst_count--;
//        }
//        
//        this->clock_count++;
//        
//        return true;
//
//    } 
//    
//    return false;
//    
//}

void Machine::loadProgram(UINT32 address, const Program &prog) {

    std::vector<UINT32> code = prog.getCode();

    if (this->prog)
        delete this->prog;

    this->prog = new Program(prog);

    this->PC.setValue(address);
    this->inst_count = code.size();

    unsigned int i = 0;
    for (; i < code.size(); i++) {
        this->mem.write(address + (i * 4), code[i]);
    }

    this->mem.write(address + (i * 4), 0xffffffff);

}

void Machine::loadProgram(
        UINT32 address,
        std::string filename, const std::function<void(const Machine&) > fun
        ) {

    std::vector<UINT32> code = Program::read(filename);

    if (this->prog)
        delete this->prog;

    this->prog = new Program(code);

    this->PC.setValue(address);
    this->inst_count = code.size();


    unsigned int i = 0;
    for (; i < code.size(); i++) {
        this->mem.write(address + (i * 4), code[i]);
    }

    this->mem.write(address + (i * 4), 0xffffffff);

}

void Machine::set_ctrl_state_0() {
    this->ctrl.set_MemRead(1);
    this->ctrl.set_IRWrite(1);
    this->ctrl.set_IorD(0);
    this->ctrl.set_ALUSrcA(0);
    this->ctrl.set_ALUSrcB(1);
    this->ctrl.set_ALUOp(0);
    this->ctrl.set_PCSource(0);
    this->ctrl.set_PcWrite(1);
}

void Machine::set_ctrl_state_1() {
    this->ctrl.set_ALUSrcA(0);
    this->ctrl.set_ALUSrcB(3);
    this->ctrl.set_ALUOp(0);
}

void Machine::set_ctrl_state_2() {
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(2);
        this->ctrl.set_ALUOp(0);
    }


    void Machine::set_ctrl_state_3() {
        this->ctrl.set_MemRead(1);
        this->ctrl.set_IorD(1);
    }


    void Machine::set_ctrl_state_4() {
        this->ctrl.set_RegDst(0);
        this->ctrl.set_RegWrite(1);
        this->ctrl.set_MemToReg(1);
    }


    void Machine::set_ctrl_state_5() {
        this->ctrl.set_MemWrite(1);
        this->ctrl.set_IorD(1);
    }


    void Machine::set_ctrl_state_6() {
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(0);
        this->ctrl.set_ALUOp(2);
    }


    void Machine::set_ctrl_state_10() {
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(2);
        this->ctrl.set_ALUOp(2);
    }


    void Machine::set_ctrl_state_7() {
        this->ctrl.set_RegDst(1);
        this->ctrl.set_RegWrite(1);
        this->ctrl.set_MemToReg(0);
    }

    void Machine::set_ctrl_state_8() {
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(00);
        this->ctrl.set_ALUOp(1);
        this->ctrl.set_PcWriteCond(1);
        this->ctrl.set_PCSource(1);
    }


    void Machine::set_ctrl_state_9() {
        this->ctrl.set_PcWrite(1);
        this->ctrl.set_PCSource(2);
    }


    void Machine::exportMachine(std::ostream& os) {
        if (this->state)
            os << *this->state << std::endl << std::endl;

        os << "Inst_count: " << this->inst_count << std::endl << std::endl;

        os << "Clock_count: " << this->clock_count << std::endl << std::endl;

        os << "Ctrl:" << std::endl << this->ctrl << std::endl << std::endl;

        os << "    PC: " << this->PC << std::endl << std::endl;
        os << "   MDR: " << this->MDR << std::endl << std::endl;
        os << "     A: " << this->A << std::endl << std::endl;
        os << "     B: " << this->B << std::endl << std::endl;
        os << "ALUOUT: " << this->aluout << std::endl << std::endl;
        os << "    IR: " << this->ir << std::endl << std::endl;

        os << "Registers:" << std::endl << this->regs << std::endl << std::endl;
        os << "Memory:" << std::endl << this->mem << std::endl << std::endl;

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

BYTE Machine::getFunct() {
    return this->ir.getfunct();
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
                this->aluout.setValue(this->B.getValue() << this->ir.getShamt());
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

    if (this->ir.getOP() == IR::OPCODE::I_Type_JAL) {
        this->regs.write(31, this->PC.getValue());
    } else if (this->ir.getOP() == IR::OPCODE::R_Type) {
        this->PC.setValue(this->regs.read(31));
        return;
    }
    this->PC.setValue(pc4_right_bits | address_left2);


}

std::ostream& operator<<(std::ostream& os, const Machine& obj) {

    if (obj.state)
        os << *obj.state << std::endl << std::endl;

    //os << "Inst_count: " << obj.inst_count << std::endl << std::endl;

    //os << "Clock_count: " << obj.clock_count << std::endl << std::endl;

    //os << "Ctrl:" << std::endl << obj.ctrl << std::endl << std::endl;

    os << "    PC: " << obj.PC << std::endl << std::endl;
    //os << "   MDR: " << obj.MDR << std::endl << std::endl;
    //os << "     A: " << obj.A << std::endl << std::endl;
    //os << "     B: " << obj.B << std::endl << std::endl;
    //os << "ALUOUT: " << obj.aluout << std::endl << std::endl;
    os << "    IR: " << obj.ir << std::endl << std::endl;

    os << "Registers:" << std::endl << obj.regs << std::endl << std::endl;
    //os << "Memory:" << std::endl << obj.mem << std::endl << std::endl;


    return os;
}

std::string Machine::getJson() const {

    std::stringbuf buffer;
    std::ostream os(&buffer);

    os << "{ ";

    if (this->prog) {

        os << "\"program\":" << this->prog->getJson() << ", ";

    } else {

        os << "\"program\":null, ";

    }



    if (this->state) {

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