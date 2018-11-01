/**
   Skeleton code for a simple MIPS simulator of the following course:

   CSE301: Computer Architecture
   Fall 2018
   UNIST

   Author: Jongeun Lee, jlee@unist.ac.kr
 */

#include "msim.h"
// register file and PC
struct regs_t regs;

static const int INST_MEM_SIZE = 1024; // bytes
static const int DATA_MEM_SIZE = 1024; // bytes
static const int INST_INDEX_END = INST_MEM_SIZE >> 2;
static const int DATA_INDEX_END = DATA_MEM_SIZE >> 3;

static uint32_t inst_mem[INST_INDEX_END];
static int64_t data_mem[DATA_INDEX_END];

// a: byte address
int64_t memread_dword(unsigned int a) {
  unsigned int i = a >> 3;
  assert( i < DATA_INDEX_END );
  printf("R %04x\n", a);
  return data_mem[i];
}

// a: byte address
// v: dword data
void memwrite_dword(unsigned int a, int64_t v) {
  unsigned int i = a >> 3;
  assert( i < DATA_INDEX_END );
  printf("W %04x %016" PRIx64 "\n", a, v);
  data_mem[i] = v;
}

// Example:  hex2uint("10") -> 16
template <typename T, size_t N>
T hex2uint(const char* pstr)
{
  T val = 0;
  for ( size_t i = 0; i < N; i++ ) {
    T n = pstr[N - 1 - i] - '0';
    if ( n > 9 )
      n -= 'a' - '0' - 10;
    val |= n << (4 * i);
  }
  return val;
}

// load from .cod file
static void load_instr(const string& fn)
{
  ifstream is(fn.c_str());
  if ( ! is ) {
    cout << "error: instruction file not found: " << fn << endl;
    exit(-1);
  }
  cout << "reading " << fn << endl;
  string a;
  int i;
  for ( i = 0; is >> a; i++ ) {
    uint32_t inst = hex2uint<uint32_t, 8>(a.c_str());
    // for debug
    printf("%s -> %08x\n", a.c_str(), inst);

    if ( i < INST_INDEX_END )
      inst_mem[i] = inst;
    else {
      cout << "error: too many instructions\n";
      exit(-1);
    }
  }
  if ( i < INST_INDEX_END )
    inst_mem[i] = HALT_INST;
}

// load from .dat file
static void load_data(const string& fn)
{
  ifstream is(fn.c_str());
  if ( ! is ) {
    cout << "warning: data file not found: " << fn << "\n";
    return;
  }
  cout << "reading " << fn << endl;
  string a;
  for ( int i = 0; is >> a; i++ ) {
    int64_t dval = hex2uint<int64_t, 16>(a.c_str());

    // for debug
    printf("%s -> %016" PRIx64 "\n", a.c_str(), dval);

    if ( i < DATA_INDEX_END )
      data_mem[i] = dval;
    else {
      cout << "error: too many data items\n";
      exit(-1);
    }
  }
}

// load program from .cod & .dat files
static void load_program(string prog)
{
  // create a instruction memory
  // create a data memory
  // populate the memories with data
  
  load_instr(prog + ".cod");
  load_data(prog + ".dat");
}

// fetch one instruction from inst_mem
static uint32_t fetch_instr(uint32_t pc)
{
  // the last two bits of a PC must be "00"
  assert((pc & 0x03) == 0);

  unsigned int index = pc >> 2;
  assert(index < INST_INDEX_END);
  return inst_mem[index];
}

// print the state of the processor
static void print_proc_state(int dcount)
{
  for ( int i = 1; i < 32; i++ ) {
    printf("$%02d    %016" PRIx64 "\n", i, regs.reg[i]);
  }
  printf("PC     %04x\n", regs.pc);
  for ( int i = 0; i < dcount && i < DATA_INDEX_END; i++ ) {
    printf("M[%03d] %016" PRIx64 "\n", i, data_mem[i]);
  }
}

// main simulator driver
int main(int argc, const char** argv)
{
  if ( argc < 2 ) {
    cout << "Usage: " << argv[0] << "   program      # without extension\n";
    exit(-1);
  }
  load_program(argv[1]);

  cout << "Starting simulation.\n";
  unsigned long ninstr = 0;          // counts # of instructions executed
  while ( regs.pc < INST_MEM_SIZE ) {
    uint32_t inst = fetch_instr(regs.pc);
    printf("I %04x %08x %lu\n", regs.pc, inst, ninstr);
    regs.pc += 4;
    if ( decode_execute(inst) != 0 )
      break;
    ninstr++;
  }
  
  cout << "\n#instrs_executed: " << ninstr << "\n";

  int dcount = (argc >= 3) ? atoi(argv[2]) : 10;
  print_proc_state(dcount);
  return 0;
}
