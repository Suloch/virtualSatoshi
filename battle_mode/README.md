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
|Instruction Name | Functionality                     | Example                                     |
|-----------------|-----------------------------------|---------------------------------------------|
|CHARGE           |move value between 2 registers     |CHARGE ELECTRIFY ELECTROWEB                  |
|CHARGE_BEAM      |copy immediate value to a reg      |CHARGE_BEAM ELECTRIFY ASD                    |
|DISCHARGE        |display a register                 |DISCHARGE ELECTRIFY                          |
|THUNDER_FANG     |jump to input location             |THUNDER_FANG AVF                             |
|THUNDER_PUNCH    |jump if flag register is 0         |THUNDER_PUNCH AVF                            |  
|THUNDER_SHOCK    |jump if flag register is +         |THUNDER_SHOCK AVG                            |
|THUNDER_WAVE     |jump if flag register is -         |THUNDER_WAVE FFF                             |
|ION_DELUGE       |and with accumulator               |WILD_CHARGE NUZZLE                           |
|WILD_CHARGE      |or with accumulator                |BOLT_BEAK SPARK                              |
|BOLT_STRIKE      |increment a register               |BOLT_STRIKE THUNDER                          |
|BOLT_BEAK        |decrememt a register               |ION_DELUGE THUDER                            |
|VOLT_TACKLE      |compare two registers              |VOLT_TACKLE NUZZLE SPARK                     |
|ZIPPY_ZAP        |halt the machine                   |ZIPPY_ZAP                                    |
|MAGNET_RISE      |                                   |                                             |
|MAX_LIGHTENING   |                                   |                                             |
|ZING_ZAP         |                                   |                                             |
|AURA_WHEEL       |                                   |                                             |
|BUZZY_BUZZ       |                                   |                                             |
|EERIE_IMPULSE    |                                   |                                             |
|VOLT_SWITCH      |                                   |                                             |
