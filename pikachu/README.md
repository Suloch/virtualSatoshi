# Pikachu Specifications
Pikachu uses balanced ternary number system.   
(The specifications can be modified with requirements in future)   
PI = -1     
PIKA = 0   
PIKACHU = 1   

## Architectural Specifications
| Description   | Value         |
| ------------- |:-------------:|
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
opcode: `PI PI PI`   
Usage: opcode register1, register   
Example: `PI PI PI PIKA PIKACHU PI PIKA PIKA PIKACHU`   
this will copy the value from register B to accumulator   
 `PI PI PI` -> opcode   
 `PIKA PIKACHU PI` -> value 2 represents 2nd register   
 `PIKA PIKA PIKACHU` -> value 1 represents 1st register   

### MVI
transer 3 trits to register or memory   
opcode: `PI PI PIKA`   
Usage: opcode register, 3trits   
Example: `PI PI PIKA PIKACHU PIKA PI PI PI PI`   
this will copy -13 to memory location stored using BCD register   
 `PI PI PIKA` -> opcode   
 `PIKACHU PIKA PI` -> value 8 represents memory refrenced using BCD register   
 `PI PI PI` -> random value   
 
### AND
Logical and with the accumulator   
opcode: `PI PI PIKACHU`   

### OR
Logical or with accumulator   
opcode: `PI PIKA PI`   

### INC
Increment a register   
opcode: `PI PIKA PIKA`   

### DCR
Decrement a register   
opcode: `PI PIKA PIKACHU`   

### CMP
CMP two register(PIKACHU  if first is greater, PIKA  if equal and PI  otherwise)   
opcode: `PI PIKACHU PI`   

### ROTL
Bitwise rotation of trits(left PIKACHU ->PIKA , PIKA ->PI , PI ->PIKACHU )   
opcode: `PI PIKACHU PIKA`   

### ROTR
Complement of ROTL   
opcode: `PI PIKACHU PIKACHU`   

### PUSH
Push value of current registers on stack   
opcode: `PIKACHU PI PI`    

### POP
POP value of current registers on stack   
opcode: `PIKACHU PI PIKA`   

## Interrupts

1. Display contents of a register to monitor   
### INT 1
opcode: `PIKACHU PI PIKACHU`   

2. Input from keyboard to buffer   
### INT 2   
opcode: `PIKACHU PIKA PI`   

3. Stop   
### INT 3
opcode: `PIKACHU PIKA PIKA`   
