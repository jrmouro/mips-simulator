/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Machine.h
 * Author: ronaldo
 *
 * Created on 13 de Fevereiro de 2021, 08:36
 */

#ifndef MACHINE_H
#define MACHINE_H

#include "Resettable.h"
#include "Memory.h"
#include "ToJson.h"
#include "Registers.h"
#include "IR.h"
#include "Ctrl.h"
#include "State.h"
#include <iostream>
#include <functional>

class State;
class Programm;
class Machine : public ToJson, public Resettable{
public:
    
    Machine(UINT32 mem_size);
    
    Machine(const Machine& other);
    
    virtual ~Machine();
    
    virtual void reset(){
        this->mem.reset();
        this->regs.reset();
        this->ir.setValue(0);
        this->PC.reset();
        this->A.reset();
        this->B.reset();
        this->MDR.reset();
        this->aluout.reset();
        this->clock_count = this->inst_count = 0;
        this->regs.write(29, this->mem.getSize() - 1);  // $sp      
    }
    
    bool clock(
        /*const std::function<void(const Machine&)> fun = 
            [](const Machine& mach){ std::cout << mach << std::endl; }*/);
        
    void loadProgramm(UINT32 address, const Programm &prog);
            
    void loadProgram(
        UINT32 address, 
        std::string filename,
        const std::function<void(const Machine&)> fun = 
            [](const Machine& mach){ std::cout << mach << std::endl; }
            );
    
    //state0: Busca da Instrução
    void ir_recebe_mem_pc();    
    void pc_recebe_pc_mais_4();
    void set_ctrl_state_0(){
        this->ctrl.set_MemRead(1);
        this->ctrl.set_IRWrite(1);
        this->ctrl.set_IorD(0);
        this->ctrl.set_ALUSrcA(0);
        this->ctrl.set_ALUSrcB(1);
        this->ctrl.set_ALUOp(0);
        this->ctrl.set_PCSource(0);
        this->ctrl.set_PcWrite(1);
    }
    
    //state1: Decodifica Instrução / Busca Registradores
    void a_recebe_reg_data_1();    
    void b_recebe_reg_data_2();    
    void aluout_recebe_pc_mais_ext_2();   
    BYTE getOp();
    void set_ctrl_state_1(){
        this->ctrl.set_ALUSrcA(0);
        this->ctrl.set_ALUSrcB(3);
        this->ctrl.set_ALUOp(0);
    }
    
    //State 2: Cálculo do endereço de memória
    void address_memory_calc();
    void set_ctrl_state_2(){
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(2);
        this->ctrl.set_ALUOp(0);
    }
    
    //State 3: Acesso à memória(leitura)
    void mdr_recebe_mem_aluout();
    void set_ctrl_state_3(){
        this->ctrl.set_MemRead(1);
        this->ctrl.set_IorD(1);
    }
    
    //State 4: Conclusão da leitura de memória
    void reg_recebe_mdr();
    void set_ctrl_state_4(){
        this->ctrl.set_RegDst(0);
        this->ctrl.set_RegWrite(1);
        this->ctrl.set_MemToReg(1);
    }
    
    //State 5: Acesso à memória(escrita)
    void mem_aluout_recebe_b();
    void set_ctrl_state_5(){
        this->ctrl.set_MemWrite(1);
        this->ctrl.set_IorD(1);
    }
        
    //state6: execução
    void execute_alu_op();
    void set_ctrl_state_6(){
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(0);
        this->ctrl.set_ALUOp(2);
    }
    void set_ctrl_state_10(){
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(2);
        this->ctrl.set_ALUOp(2);
    }
    
    //state7: Conclusão de Tipo R    
    void completion_TypeR();
    void set_ctrl_state_7(){
        this->ctrl.set_RegDst(1);
        this->ctrl.set_RegWrite(1);
        this->ctrl.set_MemToReg(0);
    }
    
    //state8: Conclusão do desvio    
    void pc_recebe_aluout_desvio_cond_equal();    
    void pc_recebe_aluout_desvio_cond_not_equal();
    void set_ctrl_state_8(){
        this->ctrl.set_ALUSrcA(1);
        this->ctrl.set_ALUSrcB(00);
        this->ctrl.set_ALUOp(1);
        this->ctrl.set_PcWriteCond(1);
        this->ctrl.set_PCSource(1);
    }
    
    //state9: Conclusão do salto    
    void pc_recebe_address();
    void set_ctrl_state_9(){
        this->ctrl.set_PcWrite(1);
        this->ctrl.set_PCSource(2);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Machine& obj);

    
    virtual std::string getJson() const;
       
    
private:
    
    Register  A, B, PC, MDR, aluout;
    
    unsigned  inst_count = 0, clock_count = 0; 
    
    Ctrl ctrl;
    Memory mem;
    Registers regs;
    IR ir;
    State *state = 0;
    
    Programm *prog;
    
};

#endif /* MACHINE_H */

