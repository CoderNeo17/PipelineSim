#include<iostream>
#include<queue>
#include<fstream>
#include<cstdint>
using namespace std;

#define ICACHE "./input/ICache.txt"
#define DCACHE "./input/DCache.txt"
#define REG_FILE "./input/RF.txt"
#define OUTPUT "./output/output.txt"
#define DCACHE_OUTPUT "./output/DCACHE.txt"

#define ADD 0
#define SUB 1
#define MUL 2
#define INC 3
#define AND 4
#define OR  5
#define XOR 6
#define NOT 7
#define SLLI 8
#define SRLI 9
#define LI  10
#define LD  11
#define ST  12
#define JMP 13
#define BEQZ 14
#define HLT 15

class IF{
    private:
        queue<int8_t>* IR;
        uint8_t* ICache;
        
    public:
        IF(queue<int8_t>* ir,uint8_t* ic){
            this->IR = ir;
            this->ICache = ic;
        }
        int run(int8_t* PC,int stall){
            //if stall>0, do nothing
            //else push icache[pc] into IR queue;
            //increment PC by 2
            //return stall

            if(stall > 0){} // do nothing
            else{
                IR->push(static_cast<int8_t>(ICache[*PC]));
                *PC += 2;
            }
            return stall;
        }
};
class ID{
    private:
        queue<int16_t>* IR;
        queue<uint8_t>* op;
        queue<uint8_t>* rd;
        queue<int8_t>* operand1;
        queue<int8_t>* operand2;
        queue<int8_t>* imm;
        int8_t* reg_hazard;
        int8_t* DCache;
    public:
        ID(queue<int16_t>* ir,queue<uint8_t>* op,queue<uint8_t>* rd,queue<int8_t>* operand1,queue<int8_t>* operand2,queue<int8_t>* imm,int8_t* DCache,int8_t* reg_hazard){
            this->IR = ir;
            this->op = op;
            this->rd = rd;
            this->operand1 = operand1;
            this->operand2 = operand2;
            this->imm = imm;
            this->DCache = DCache;
            this->reg_hazard = reg_hazard;
        }
        int run(bool stall){
            //
            //if stall is true, do nothing. else pop the queue;
            //get instruction from top of queue
            //check if a source register is in reg_hazard
            //if source register is in hazard, return 1  -----------------------------------------|
            //if no hazard, set reg_hazard[dest reg] = 3 for destination                          |
            ////find the values from source registers and push them into respective queues        |
            //else(if there is a hazard) do nothing                                               |-> if i is a source register , if reg_hazard[i]>0 then there is a hazard
            //in any case return if_stall
            //pc is also a source register
            //for branch instructions it is a dest reg
            //reg_hazard[16] corresponds to pc
            //control hazards are checked using this
            //if control hazard, return 2

            if(stall){} // donothing
            else{
                int16_t instruc = IR->front();
                IR->pop();
                
            }
        }
};
class EX{
    private:
        queue<uint8_t>* rd;
        queue<uint8_t>* op;
        queue<int8_t>* operand1;
        queue<int8_t>* operand2;
        queue<int8_t>* imm;
        queue<int8_t>* ALUout;
        queue<uint8_t>* mem_dest;
        queue<int8_t>* MEMop;
    public:
        EX(queue<uint8_t>* rd,queue<uint8_t>* op,queue<int8_t>* operand1,queue<int8_t>* operand2,queue<int8_t>* imm,queue<int8_t>* ALUout,queue<uint8_t>* mem_dest,queue<int8_t>* MEMop){
            this->rd = rd;
            this->op = op;
            this->operand1 = operand1;
            this->operand2 = operand2;
            this->imm = imm;
            this->ALUout = ALUout;
            this->mem_dest = mem_dest;
            this->MEMop = MEMop;
        }
        void run(){
            //if queue is empty, do nothing
            //else,get inputs from top of input queues and pop()
            //perform required operation
            //push output into respective queues
        }
};
class MEM{
    private:
        queue<int8_t>* ALUout;
        queue<uint8_t>* dest;
        queue<uint8_t>* MEMop;
        queue<uint8_t>* wb_dest;
        queue<int8_t>* MEMout;
        queue<uint8_t>* wb_op;
    public:
        MEM(queue<int8_t>* ALUout,queue<uint8_t>* dest,queue<uint8_t>* MEMop,queue<uint8_t>* wb_dest,queue<int8_t>* MEMout,queue<uint8_t>* wb_op){
            this->ALUout = ALUout;
            this->dest = dest;
            this->MEMop = MEMop;
            this->wb_dest = wb_dest;
            this->MEMout = MEMout;
            this->wb_op = wb_op;
        }
        bool run(bool stall){
            //if input queue empty, do nothing
            //else get inputs from q's
            //if ld/st do needful and push result to MEMout
            //push op to wb_op
            //push rd to wb_dest
        }
};
class WB{
    private:
        queue<int8_t>* MEMout;
        queue<uint8_t>* wb_dest;
        queue<uint8_t>* wb_op;
        uint8_t* PC;
    public:
        WB(queue<int8_t>* MEMout,queue<uint8_t>* wb_dest,queue<uint8_t>* wb_op,uint8_t* PC){
            this->MEMout = MEMout;
            this->wb_dest = wb_dest;
            this->wb_op = wb_op;
            this->PC = PC;
        }
        bool run(bool stall){
            //if queue is empty do nothing
            //else write MEMout into wb_dest if op is like that 
            //if op is for break statement, update pc
            //if op is halt set all stalls to 3
        }
};

class processor{
    public:
        IF* if_stage;
        ID* id_stage;
        EX* ex_stage;
        MEM* mem_stage;
        WB* wb_stage;
        queue<uint16_t>* IR;
        queue<uint8_t>* op;
        queue<uint8_t>* rd;
        queue<int8_t>* operand1;
        queue<int8_t>* operand2;
        queue<int8_t>* imm;
        queue<int8_t>* ALUout;
        queue<uint8_t>* mem_dest;
        queue<int8_t>* MEMout;
        queue<uint8_t>* wb_dest;
        queue<int8_t>* wb_value;
        queue<uint8_t>* wb_op;
        queue<int8_t>* mem_op;
        queue<int8_t>* mem_addr;
        uint8_t* PC;
        uint8_t ICache[256];
        uint8_t DCache[256];
        int8_t RF[16];
        int8_t reg_hazard[17];
        bool stall;
        bool halt;
        int clock;
        int IC;
        int stalls;
        int mem_stalls;
        int con_stalls;

        processor(){
            //initialise all queues
            //load ICache and DCache and RF from files
            //initialise all stages
        }
        void run(){
            ///note: if a state executes properly, it returns true, else it eturns false

            while(!halt){

                ////flag = IF->run(PC,ID->run(EX->run(MEM->run(WB->run()))))
                ////decrement all elements in reg_hazard by 1
                ////increment clock by 1
                ////if flag>0, increment stalls by 1, else increment IC by 1
                ////if flag =1, increment mem_stalls
                ////if flag = 2, increment con_stalls by 1
            }
        }
};


int main(){
    processor* proc = new processor();
    proc->run();
    return 0;
}