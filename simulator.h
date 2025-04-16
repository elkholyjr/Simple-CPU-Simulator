#ifndef TASK_3_SIMULATOR_H
#define TASK_3_SIMULATOR_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Instruction class to represent individual instructions
class Instruction {
public:
    int opcode;
    int operand1;
    int operand2;

    Instruction(int op, int op1, int op2);
};

// Memory class to handle memory operations
class Memory {
public:
    vector<int> main_memory;
    vector<int> memory;

    Memory(int size);

    void load_memory(int address, int value);
};

// CPU class to handle CPU operations
class CPU {
public:
    vector<int> registers;
    int program_counter;
    bool is_halted;

    CPU();

    void load_register(int register_num, int value);
    void store(int register_num, int address, Memory& memory);
    void move(int source, int destination);
    void add(int destination, int source1, int source2);
    void jump(int register_num, int address);
    void halt();
};

// Simulator class to coordinate the entire simulation
class Simulator {
private:
    Memory memory;
    CPU cpu;

public:
    Simulator();
    void read_instructions_from_file(const std::string& filename);
    void execute_program();
    int single_step();
    void clear();
    void print();
};

#endif //TASK_3_SIMULATOR_H
