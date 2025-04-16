# Simple CPU Simulator

A basic CPU simulator implemented in C++. This project simulates a simple computer architecture with a set of instructions, registers, and memory, allowing users to load instructions from a file and execute them step-by-step or all at once.

---

## 🧠 Features

- 16 general-purpose registers
- 256 bytes of memory
- Instruction memory and execution
- Step-by-step execution and full program run
- Register and memory reset (clear)
- Instruction file loading from `instructions.txt`
- Instruction set includes:
  - Load from memory
  - Load immediate
  - Store to memory
  - Move between registers
  - Add
  - Conditional jump
  - Halt

---

## 📁 Project Structure

```
.
├── main.cpp             # Contains the interactive CLI to control the simulator
├── Simulator.h          # Class definitions for Simulator, CPU, Memory, Instruction
├── Simulator.cpp        # Implementation of simulator logic
├── instructions.txt     # Hex instruction file (user-provided)
```

---

## ⚙️ How to Compile

Use any standard C++ compiler like `g++`:

```bash
g++ main.cpp Simulator.cpp -o simulator
```

---

## 🚀 How to Run

```bash
./simulator
```

You will be prompted with the following menu:

```
1. Single Step
2. Clear
3. Load Data
4. Print
5. Run
6. Exit
```

---

## 🔘 Menu Options

| Option | Action                                  |
|--------|-----------------------------------------|
| 1      | Executes the next instruction           |
| 2      | Resets all registers and memory         |
| 3      | Loads instructions from `instructions.txt` |
| 4      | Prints the contents of the registers    |
| 5      | Executes the program fully              |
| 6      | Terminates the simulator                |

---

## 📄 Instruction Format

Instructions should be written in hexadecimal format in `instructions.txt`, with each line representing a single instruction:

```
opcode operand1 operand2
```

Example:
```
01 02 0A   # Load from memory[0A] into R2
02 03 05   # Load immediate value 05 into R3
05 04 32   # Add R2 and R3, store result in R4
0C 00 00   # Halt
```

---

## 🔧 Supported Opcodes

| Opcode | Instruction      | Description                                                             |
|--------|------------------|-------------------------------------------------------------------------|
| 0x1    | LOAD R, [A]      | Load value from memory address `A` into register `R`                    |
| 0x2    | LOADI R, V       | Load immediate value `V` into register `R`                              |
| 0x3    | STORE R, A       | Store value of register `R` into memory at address `A`                  |
| 0x4    | MOVE R1, R2      | Copy value from R1 to R2                                                |
| 0x5    | ADD D, S1, S2    | Add registers `S1` and `S2`, store in `D` (encoded in one byte)         |
| 0xB    | JUMP R, A        | Jump to address `A` if register `R` equals R0                           |
| 0xC    | HALT             | Stop program execution                                                  |

> 🧠 **Note:** During the ADD operation, operand2 is split:
> - Lower 4 bits: source1 register
> - Upper 4 bits: source2 register

---

## 📌 Notes

- Addresses and operands are interpreted in **hexadecimal**.
- Each instruction is encoded in 3 bytes.
- Memory-mapped I/O:
  - Writing to address `0x00` outputs the register value to the screen.

---

## 🧪 Example Usage

Create a file named `instructions.txt` with the following content:

```
02 01 05
02 02 0A
05 03 21
03 03 01
0C 00 00
```

Explanation:
- Load `0x05` into R1
- Load `0x0A` into R2
- Add R1 and R2 → R3
- Store R3 into memory[0x01]
- Halt execution

Run the simulator:
1. Choose option `3` to load instructions.
2. Choose option `5` to run the program.
3. Choose option `4` to print the register states.

---

## 👨‍💻 Author

Developed as a simulation project for low-level systems and architecture exploration.
