# Battle Mode Specs
The assembler for the Machine.   
Pikachu can unserstand the move names directly, therefore the assembler will contains pokemon move list.

## Register Names
|Register     | Names         |
|-------------|---------------|
|Accumulator  |ELECTRIFY      |
|B            |ELECTROWEB     |
|C            |NUZZLE         |
|D            |OVERDRIVE      |
|E            |SPARK          |
|F            |THUNDER        |
|M            |CATASTROPIKA   |


## Move List
|Instruction Name | Functionality                     | Example                                     |       |
|-----------------|-----------------------------------|---------------------------------------------|-------|
|CHARGE           |move value between 2 registers     |CHARGE ELECTRIFY ELECTROWEB                  | -12   |
|CHARGE_BEAM      |copy immediate value to a reg      |CHARGE_BEAM ELECTRIFY ASD                    | -11   |
|DISCHARGE        |display a register                 |DISCHARGE ELECTRIFY                          |  -2   |
|THUNDER_FANG     |jump to input location             |THUNDER_FANG AVF                             |  1    |
|THUNDER_PUNCH    |jump if flag register is 0         |THUNDER_PUNCH AVF                            |  2    |
|THUNDER_SHOCK    |jump if flag register is +         |THUNDER_SHOCK AVG                            |  4    |
|THUNDER_WAVE     |jump if flag register is -         |THUNDER_WAVE FFF                             |  3    |
|ION_DELUGE       |and with accumulator               |WILD_CHARGE NUZZLE                           | -11   |
|WILD_CHARGE      |or with accumulator                |BOLT_BEAK SPARK                              | -10   |
|BOLT_STRIKE      |increment a register               |BOLT_STRIKE THUNDER                          | -9    |
|BOLT_BEAK        |decrememt a register               |ION_DELUGE THUDER                            | -8    |
|VOLT_TACKLE      |compare two registers              |VOLT_TACKLE NUZZLE SPARK                     | -7    |
|ZIPPY_ZAP        |halt the machine                   |ZIPPY_ZAP                                    |  0    |
|MAGNET_RISE      |                                   |                                             |       |
|MAX_LIGHTENING   |                                   |                                             |       |
|ZING_ZAP         |                                   |                                             |       |
|AURA_WHEEL       |                                   |                                             |       |
|BUZZY_BUZZ       |                                   |                                             |       |
|EERIE_IMPULSE    |                                   |                                             |       |
|VOLT_SWITCH      |                                   |                                             |       |

## Labels
1. labels can only have small letter english alphabets or '_'
2. 'i_choose_you' the is starting label

## Literals
3 trits is represented with one alphabet starting from A(-13) to M(-1), N(12), O(0), P(1) to Z(11), _(13)

## Comments
 comments start with '-' and end with newline

## Examples

### Hello World

```
i_choose_you:
  CHARGE_BEAM ELECTRIFY H_W -copies -6*9 + 13*3 + 8
  DISCHARGE ELECTRIFY       -print the value of the register
  ZIPPY_ZAP                 -halt the machine
```
