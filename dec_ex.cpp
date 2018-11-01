/**
   Skeleton code for a simple MIPS simulator of the following course:

   CSE301: Computer Architecture
   Fall 2018
   UNIST

   Author: Jongeun Lee, jlee@unist.ac.kr
 */

/**
 * Erkin Matkaziev
 * 20152032
 * erkin97@unist.ac.kr
 */

#include "msim.h"
//////////////* core functions *///////////////////
// convert to the binary string
string get_binary(uint32_t inst) {
  string s = "";
  while (inst > 0) {
    int k = inst % 2;
    s = char(k + 48) + s;
    inst /= 2;
  }
  while (s.length() < 32) {
    int k = 0;
    s = char(k + 48) + s;
    inst /= 2;
  }
  return s;
}
// get opcode
string get_opcode(string &binary) { return binary.substr(0, 6); }
// get func
string get_funct(string &binary) { return binary.substr(26, 6); }
// get source register
string get_rs(string &binary) { return binary.substr(6, 5); }
// get target register
string get_rt(string binary) { return binary.substr(11, 5); }
// get immediate 16 bits
string get_immediate16(string binary) { return binary.substr(16, 16); }
// get immediate 26 bits
string get_immediate26(string binary) { return binary.substr(6, 26); }
// get shift amount
string get_sa(string binary) { return binary.substr(21, 5); }
// get rd register
string get_rd(string binary) { return binary.substr(16, 5); }
// convert back my string binaries to the 64 bit number to fit skeleton
uint64_t bin_to_int(string binary) {
  uint64_t base = 2, decimal = 0, mult = 1;
  for (int i = binary.length() - 1; i >= 0; i--) {
    uint64_t k = binary[i] - 48;
    decimal += k * mult;
    mult *= base;
  }
  return decimal;
}
////////////////////////////////////////
///////////* instruction functions *///////////////////

/*
ld  reg,imm(reg)
implementation of load instruction
R[rt] = M[R[rs]+Imm]
*/
void ld(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  uint32_t address = immediate + regs.reg[rs];
  regs.reg[rt] = memread_dword(address);
  cout << "running load double-word instruction" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
lw  reg,imm(reg)
implementation of load instruction
R[rt] = M[R[rs]+Imm]
*/
void lw(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  uint32_t address = immediate + regs.reg[rs];
  regs.reg[rt] = memread_dword(address);
  cout << "running load word instruction" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
lwu  reg,imm(reg)
implementation of load instruction
R[rt] = M[R[rs]+Imm]
*/
void lwu(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  uint32_t address = immediate + regs.reg[rs];
  regs.reg[rt] = memread_dword(address);
  cout << "running load word unsigned instruction" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}

/*
lui  reg,imm
implementation of load instruction
R[rt] = M[Imm]
*/
void lui(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  uint32_t address = immediate;
  regs.reg[rt] = memread_dword(address);
  cout << "running load upper half of register immediate" << endl;
  cout << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
sd reg,imm(reg)
implementation of store instruction
M[R[rs]+Imm] = R[rt]
*/
void sd(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  uint32_t address = immediate + regs.reg[rs];
  memwrite_dword(regs.reg[rt], address);
  cout << "running store double-word instruction" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
sw reg,imm(reg)
implementation of store instruction
M[R[rs]+Imm] = R[rt]
*/
void sw(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  uint32_t address = immediate + regs.reg[rs];
  memwrite_dword(regs.reg[rt], address);
  cout << "running store word instruction" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
daddi  reg,reg,imm
implementation of add immediate
R[rt] = R[rs] + Imm
*/
void daddi(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  regs.reg[rt] = regs.reg[rs] + immediate;
  cout << "running add immediate" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
daddui  reg,reg,imm
implementation of add immediate unsigned
R[rt] = R[rs] + Imm
*/
void daddui(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  regs.reg[rt] = regs.reg[rs] + immediate;
  cout << "running add immediate unsigned" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
andi  reg,reg,imm
implementation of bitwise and immediate
R[rt] = R[rs] & Imm
*/
void andi(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  regs.reg[rt] = regs.reg[rs] & immediate;
  cout << "running bitwise and immediate" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
ori reg,reg,imm
implementation of bitwise or immediate
R[rt] = R[rs] | Imm
*/
void ori(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  regs.reg[rt] = regs.reg[rs] | immediate;
  cout << "running bitwise or immediate" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
slti  reg,reg,imm
set if less than immediate
R[rt] = (R[rs] < SignExtImm)? 1 : 0
*/
void slti(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  regs.reg[rt] = int64_t(regs.reg[rs] < immediate);
  cout << "running set if less than immediate" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
sltiu  reg,reg,imm
set if less than immediate
R[rt] = (R[rs] < SignExtImm)? 1 : 0
*/
void sltiu(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  regs.reg[rt] = int64_t(regs.reg[rs] < immediate);
  cout << "running set if less than immediate unsigned" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
beq reg,reg,imm
branch if pair of registers are equal
if(R[rs]==R[rt])
 PC=PC + 4 + 4 *Imm
*/
void beq(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  if (regs.reg[rt] == regs.reg[rs]) {
    regs.pc += 4 + 4 * immediate;
  }
  cout << "running branch if pair of registers are equal" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
beq reg,reg,imm
branch if pair of registers are equal
if(R[rs]!=R[rt])
 PC=PC + 4 + 4 *Imm
*/
void bne(string binary) {
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  int64_t immediate = bin_to_int(get_immediate16(binary));
  if (regs.reg[rt] != regs.reg[rs]) {
    regs.pc += 4 + 4 * immediate;
  }
  cout << "running branch if pair of registers are not eqal" << endl;
  cout << "rs : " << rs << " rt: " << rt << " immediate: " << immediate << endl;
}
/*
j   imm
jump to address
PC = 4 × target
*/
void j(string binary) {
  int64_t immediate = bin_to_int(get_immediate26(binary));
  regs.pc = 4 * immediate;
  cout << "running jump to address" << endl;
  cout << "immediate: " << immediate << endl;
}
/*
jal   imm
jump and link to address
PC = 4 × target
*/
void jal(string binary) {
  int64_t immediate = bin_to_int(get_immediate26(binary));
  regs.reg[31] = regs.pc * 4;
  regs.pc = 4 * immediate;
  cout << "running jump and link to address" << endl;
  cout << "immediate: " << immediate << endl;
}
/*
jr   reg
jump to address in register
PC = R[rs]
*/
void jr(string binary) {
  int64_t rs = bin_to_int(get_rs(binary));
  regs.pc = regs.reg[rs];
  cout << "running jump to address in register" << endl;
  cout << "rs: " << rs << endl;
}
/*
dsll reg,reg,imm

shift left logical
R[rd] = R[rt] << shamt
*/
void dsll(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t sa = bin_to_int(get_sa(binary));
  regs.reg[rd] = regs.reg[rt] << sa;
  cout << "running shift left logical" << endl;
}
/*
dsrl reg,reg,imm

shift right logical
R[rd] = R[rt] >> shamt
*/
void dsrl(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t sa = bin_to_int(get_sa(binary));
  regs.reg[rd] = regs.reg[rt] >> sa;
  cout << "running shift right logical" << endl;
}
/*
dsra reg,reg,imm

shift right arithmetical
R[rd] = R[rt] >> shamt
*/
void dsra(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t sa = bin_to_int(get_sa(binary));
  regs.reg[rd] = regs.reg[rt] >> sa;
  cout << "running shift right arithmetical" << endl;
}
void and_(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  regs.reg[rd] = regs.reg[rt] & regs.reg[rs];
  cout << "running and instruction" << endl;
}
void or_(string binary){
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  regs.reg[rd] = regs.reg[rt] | regs.reg[rs];
  cout << "running or instruction" << endl;
}
void slt(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  regs.reg[rd] = regs.reg[rs] < regs.reg[rt];
  cout << "running slt" << endl;
}
void sltu(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  regs.reg[rd] = regs.reg[rs] < regs.reg[rt];
  cout << "runnning sltu" << endl;
}
void dadd(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  regs.reg[rd] = regs.reg[rs] + regs.reg[rt];
  cout << "runnning dadd" << endl;

}
void dsub(string binary) {
  int64_t rd = bin_to_int(get_rd(binary));
  int64_t rt = bin_to_int(get_rt(binary));
  int64_t rs = bin_to_int(get_rs(binary));
  regs.reg[rd] = regs.reg[rs] + regs.reg[rt];
  cout << "runnning dsub" << endl;

}
// decode the instruction and execute it
int decode_execute(uint32_t inst) {
  // return -1 for halt instruction (or illegal instruction)
  if (inst == HALT_INST || inst == 0x04000000) {
    cout << "Program halted.\n";
    return -1;
  }
  /* convert to the binary string, it's easy for me to work with string */
  string binary_code = get_binary(inst);
  // get opcode and decide which instruction it's
  string opcode = get_opcode(binary_code);
  // get funct we might need it if r format
  string funct = get_funct(binary_code);
  /* debug stdout */
  cout << "binary code: " << binary_code << endl;
  cout << "opcode:" << opcode << endl;
  if (opcode == "110111") {
    ld(binary_code);
  }
  if (opcode == "111111") {
    sd(binary_code);
  }
  if (opcode == "100011") {
    lw(binary_code);
  }
  if (opcode == "100111") {
    lwu(binary_code);
  }
  if (opcode == "101011") {
    sw(binary_code);
  }
  if (opcode == "001111") {
    lui(binary_code);
  }
  if (opcode == "011000") {
    daddi(binary_code);
  }
  if (opcode == "011001") {
    daddui(binary_code);
  }
  if (opcode == "001100") {
    andi(binary_code);
  }
  if (opcode == "001101") {
    ori(binary_code);
  }
  if (opcode == "001010") {
    slti(binary_code);
  }
  if (opcode == "000100") {
    beq(binary_code);
  }
  if (opcode == "001011") {
    sltiu(binary_code);
  }
  if (opcode == "000101") {
    bne(binary_code);
  }
  if (opcode == "000010") {
    j(binary_code);
  }
  if (opcode == "000011") {
    jal(binary_code);
  }
  if (opcode == "001000" && funct == "001000") {
    jr(binary_code);
  }
  if (opcode == "000000") {
    if (opcode == "000000" && funct == "111000") {
      dsll(binary_code);
    }
    if (opcode == "000000" && funct == "111010") {
      dsrl(binary_code);
    }
    if (opcode == "000000" && funct == "111011") {
      dsra(binary_code);
    }
    if (funct == "100100") { // and
      and_(binary_code);
    }
    if (funct == "100101") { // or
      or_(binary_code);
    }
    if (funct == "101010") { // slt
      slt(binary_code);
    }
    if (funct == "101011") {
      sltu(binary_code);
    }// sltu 
    if (funct == "101100") { // dadd
      dadd(binary_code);
    }
    if (funct == "101110") { // dsub
      dsub(binary_code);
    }
  }
  return 0;
}
