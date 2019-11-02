# Pikachu Specifications
Pikachu uses balanced ternary number system.   
(The specifications can be modified with requirements in future)

## Architectural Specifications

|        Description            |
|-------------------------------|
| Word Size     | 9 trits       |
| Adress Space  | 3^9           |
| Registers     | 9             |
| Instrunction  |               |
| Length        | 9 trits       |
| Opcode Length | 3 trits       |

Supports keyboard and monitor for input output

### Registers
1 accumulator (A)
6 registers are all purpose (B-G)
1 carry register / condition check register register(X)
1 counter(I)

## Instrunction set
Not enough reasearch done, so I will add the basic instructions for now    
and add more in future

### MOV
transfer data between registers and memory
opcode: -1-1-1

### MVI
transer 3 trits to register or memory
opcode: -1-10

### AND
Logical and with the accumulator
opcode: -1-11

### OR
Logical or with accumulator
opcode: -10-1

### INC
Increment a register
opcode: -100

### DCR
Decrement a register
opcode: -101

### CMP
CMP two register(1 if first is greater, 0 if equal and -1 otherwise)
opcode: -11-1

### ROTL
Bitwise rotation of trits(left 1->0, 0->-1, -1->1)
opcode: -110

### ROTR
Complement of ROTL
opcode: -111

### PUSH
Push value of current registers on stack
opcode: 1-1-1

### POP
POP value of current registers on stack
opcode: 1-10

## Interrupts

1. Display contents of a register to monitor
### INT 1
opcode: 1-11

2. Input from keyboard to buffer
### INT 2
opcode: 10-1

3. Stop
### INT 3
opcode: 100
