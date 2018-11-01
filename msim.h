/**
   Skeleton code for a simple MIPS simulator of the following course:

   CSE301: Computer Architecture
   Fall 2018
   UNIST

   Author: Jongeun Lee, jlee@unist.ac.kr
 */

#ifndef __MSIM_H
#define __MSIM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <inttypes.h>
using namespace std;

typedef unsigned int uint32_t;

static const uint32_t HALT_INST = 0x0000000c;

extern struct regs_t {
  int64_t reg[32];
  uint32_t pc;                  // pc = instruction address
} regs;

int64_t memread_dword(unsigned int a);
void memwrite_dword(unsigned int a, int64_t v);

int decode_execute(uint32_t inst);

#endif  // ! __MSIM_H
