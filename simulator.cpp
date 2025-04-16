#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Implementation for Instruction class
Instruction::Instruction(int op, int op1, int op2) : opcode(op), operand1(op1), operand2(op2) {}

// Implementation for Memory class
Memory::Memory(int size) : main_memory(size, 0), memory(size, 0) {}

void Memory::load_memory(int address, int value) {
    memory[address] = value;
    main_memory[address] = value;
}

// Implementation for CPU class
CPU::CPU() : registers(16, 0), program_counter(0), is_halted(false) {}

void CPU::load_register(int register_num, int value) {
    registers[register_num] = value;
}

void CPU::store(int register_num, int address,Memory& memory) {
    if (address == 0x00) {
        // Write to screen
        cout << "Writing to screen: " << hex << registers[register_num] << endl;
    } else {
        memory.memory[address] = registers[register_num];
    }
}

void CPU::move(int source, int destination) {
    registers[destination] = registers[source];
}

void CPU::add(int destination, int source1, int source2) {
    registers[destination] = (registers[source1] + registers[source2]) ; // & 0xFF
}

void CPU::jump(int register_num, int address) {
    if (registers[register_num] == registers[0]) {
        program_counter = address / 2 - 1;
    }
}

void CPU::halt() {
    is_halted = true;
}

// Implementation for Simulator class
Simulator::Simulator() : memory(255), cpu() {}

void Simulator::read_instructions_from_file(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    int address = 0; // Use this variable as the memory address

    while (std::getline(file, line)) {
        istringstream iss(line);
        int opcode, operand1, operand2;

        if (!(iss >> hex >> opcode >> hex >> operand1 >> hex >> operand2)) {
            cerr << "Error processing instruction at address " << address << endl;
            continue;
        }

        // Store instructions in memory at the specified address
        memory.load_memory(address++, (opcode << 16) | (operand1 << 8) | operand2);
    }

    file.close();
}


void Simulator::execute_program() {
    for (cpu.program_counter = 0; cpu.program_counter < memory.memory.size() && !cpu.is_halted; ++cpu.program_counter) {
        int instruction = memory.memory[cpu.program_counter];
        int opcode = (instruction >> 16) & 0xFF;
        int operand1 = (instruction >> 8) & 0xFF;
        int operand2 = instruction & 0xFF;

        // Process instruction (opcode, operand1, operand2)
        switch (opcode) {
            case 0x1:
                // Handle opcode 0x1
                cpu.load_register(operand1, memory.memory[operand2]);
                break;
            case 0x2:
                cpu.load_register(operand1, operand2);
                break;
            case 0x3:
                cpu.store(operand1, operand2, memory);
                break;
            case 0x4:
                cpu.move(operand1, operand2);
                break;
            case 0x5:
                cpu.add(operand1, operand2 & 0x0F, (operand2 & 0xF0) >> 4);
                break;
            case 0xB:
                cpu.jump(operand1, operand2);
                break;
            case 0xC:
                cpu.halt();
                break;
            default:
                cerr << "Unknown opcode: " << opcode << " at instruction " << cpu.program_counter << endl;
        }
    }
}

int Simulator::single_step() {
    if ((cpu.program_counter < memory.memory.size()) && !cpu.is_halted) {
        int instruction = memory.memory[cpu.program_counter];
        int opcode = (instruction >> 16) & 0xFF;
        int operand1 = (instruction >> 8) & 0xFF;
        int operand2 = instruction & 0xFF;

        // Process instruction (opcode, operand1, operand2)
        switch (opcode) {
            case 0x1:
                cpu.load_register(operand1, memory.memory[operand2]);
                break;
            case 0x2:
                cpu.load_register(operand1, operand2);
                break;
            case 0x3:
                cpu.store(operand1, operand2, memory);
                break;
            case 0x4:
                cpu.move(operand1, operand2);
                break;
            case 0x5:
                cpu.add(operand1, operand2 & 0x0F, (operand2 & 0xF0) >> 4);
                break;
            case 0xB:
                cpu.jump(operand1, operand2);
                break;
            case 0xC:
                cpu.halt();
                break;
            default:
                cerr << "Unknown opcode: " << opcode << " at instruction " << cpu.program_counter << endl;
        }
        // Increment the program counter
        ++cpu.program_counter;
        return 1;
    } else {
        return 0;
    }
}

void Simulator::clear() {
    // Reset the registers and memory
    cpu.registers = vector<int>(16, 0);
    memory.memory = vector<int>(256, 0);

    // Reset the program counter
    cpu.program_counter = 0;

    // Reset the halt flag
    cpu.is_halted = false;
}

void Simulator::print() {
    cout << "Registers:\n";
    for (int i = 0; i < cpu.registers.size(); ++i) {
        cout << "R" << i << ": " << hex << cpu.registers[i] << '\n';
    }
    cout << "\n";
}
