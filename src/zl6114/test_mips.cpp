#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "mips.h"
using namespace std;

mips_error SetRInstruction(uint32_t source1,uint32_t source2,uint32_t dest,uint32_t shift,uint32_t function,mips_mem_h mem,mips_cpu_h cpu);
mips_error SetIInstruction(uint32_t opcode,uint32_t source1,uint32_t source2,int32_t ImConstant,mips_mem_h mem,mips_cpu_h cpu);
mips_error SetJInstruction(uint32_t opcode,uint32_t Address,mips_mem_h mem,mips_cpu_h cpu);
int main(){
	mips_mem_h mem = mips_mem_create_ram(4096);
	mips_cpu_h cpu = mips_cpu_create(mem);
	mips_test_begin_suite();
//---------------------------------------------------------------------------------------------------
	//ADDU  r3 = r1 + r2;
	
	string name = "addu";
	
	int testId = mips_test_begin_test("addu");
	
	//unsigned int function = 0x21;
	uint32_t source1 = 1;
	uint32_t source2 = 2;
	uint32_t dest = 3;
	uint32_t shift = 0; 
	uint32_t function = 0x21;

	mips_error err;
	
	mips_error e = mips_cpu_set_register(cpu, source1, 40);
	
	if (e != mips_Success){
		return mips_ErrorNotImplemented;
	}
	
	uint32_t r1;
	e = mips_cpu_get_register(cpu, source1, &r1);
	
	cout << "the r1 is " << r1 << endl;
	
	e = mips_cpu_set_register(cpu, 2, 50);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	uint32_t got;
	cout << "the answer before get is " << got << endl;

	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	int passed = 0;
	if(got == 90){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing addu = r1 = r1 + r2 = 40 +50 = 90");
		cout << "test ended" << endl << endl << endl;

//---------------------------------------------------------------------------------------------------
	
	//ADDU  r3 = r1 + r2;
	
	
	testId = mips_test_begin_test("addu");
	
	//unsigned int function = 0x21;
	source1 = 1;
	source2 = 2;
	dest = 3;
	shift = 0; 
	function = 0x21;
	e = mips_cpu_set_register(cpu, source1, 0xFFFFFFFF);
	
	if (e != mips_Success){
		return mips_ErrorNotImplemented;
	}
	e = mips_cpu_get_register(cpu, source1, &r1);
	
	cout << "the r1 is " << r1 << endl;
	
	e = mips_cpu_set_register(cpu, 2, 1);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing addu = r1 = r1 + r2 = 40 +50 = 90");
	
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//ADD  r3 = r1 + r2;
	
	name = "add";
	
	testId = mips_test_begin_test("add");
	
	//unsigned int function = 0x20;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x20;
	
	e = mips_cpu_set_register(cpu, 1, 1);
	
	e = mips_cpu_set_register(cpu, 2, 1);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 2 && err != mips_ExceptionArithmeticOverflow){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing add = r3 = r1 + r2 = 2147483647 +2147483647 = 2147483647*2");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//ADD  r3 = r1 + r2;
	
	name = "add";
	
	testId = mips_test_begin_test("add");
	
	//unsigned int function = 0x20;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x20;
	
	e = mips_cpu_set_register(cpu, 1, -1);
	
	e = mips_cpu_set_register(cpu, 2, 1);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0 && err != mips_ExceptionArithmeticOverflow){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing add = r3 = r1 + r2");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//ADD  r3 = r1 + r2;
	
	name = "add";
	
	testId = mips_test_begin_test("add");
	
	//unsigned int function = 0x20;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x20;
	
	e = mips_cpu_set_register(cpu, 1, -1);
	
	e = mips_cpu_set_register(cpu, 2, -1);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(int32_t(got) == -2 && err == mips_ExceptionArithmeticOverflow){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing add = r3 = r1 + r2 ");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//AND  r3 = r1 & r2;
	
	name = "and";
	
	testId = mips_test_begin_test("and");
	
	//unsigned int function = 0x20;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x24;
	
	e = mips_cpu_set_register(cpu, 1, 0xF0F0F0F0);
	
	e = mips_cpu_set_register(cpu, 2, 0xF0F0F0F0);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0xF0F0F0F0){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing and");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//OR  r3 = r1 | r2;
	
	name = "or";
	
	testId = mips_test_begin_test("or");
	
	//unsigned int function = 0x25;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x25;
	
	e = mips_cpu_set_register(cpu, 1, 0x0F0F0F0F);
	
	e = mips_cpu_set_register(cpu, 2, 0x0FFFFFFF);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0x0FFFFFFF){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing or = r3 = 0x0FFFFFFF");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SUBU  r3 = r1 - r2 = r3 =r1 + -r2;
	
	name = "subu";
	
	testId = mips_test_begin_test("subu");
	
	//unsigned int function = 0x23;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x23;
	
	e = mips_cpu_set_register(cpu, 1, 40);
	
	e = mips_cpu_set_register(cpu, 2, 90);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(int32_t(got) == -50){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing subu = r3 = r1 - r2 = 50");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//XOR  r3 = r1 ^ r2;
	
	name = "xor";
	
	testId = mips_test_begin_test("xor");
	
	//unsigned int function = 0x26;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x26;
	
	e = mips_cpu_set_register(cpu, 1, 0x00000000);
	
	e = mips_cpu_set_register(cpu, 2, 0x0000000F);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0x0000000F){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing xor = r3 = r1 ^ r2");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SLTU  r3 = r1 , r2;If r1 is less than r2, dest is set to one.
	//It gets zero otherwise. 
	
	
	name = "sltu";
	
	testId = mips_test_begin_test("sltu");
	
	//unsigned int function = 43;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x2B;
	
	e = mips_cpu_set_register(cpu, 1, 2);
	
	e = mips_cpu_set_register(cpu, 2, 2);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing sltu = r3 = bool(r1 < r2)");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SRA -- Shift right arithmetic
	//Shifts a register value right by the shift amount (shamt) 
	//and places the value in the destination register. The sign bit is shifted in. 
	
	
	name = "sra";
	
	testId = mips_test_begin_test("sra");
	
	//unsigned int function = 0x3;
	source1 = 0;
	source2 = 2;	
	dest = 3;
	shift = 4; 
	function = 0x3;
	
	e = mips_cpu_set_register(cpu, 2, 0xFF000000);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0xFFF00000){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing sra = r3 = r2 >> 4");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SRL -- Shift right logical
	//Shifts a register value right by the shift amount (shamt) 
	//and places the value in the destination register. Zeroes are shifted in
	name = "srl";
	
	testId = mips_test_begin_test("srl");
	
	//unsigned int function = 0x2;
	source1 = 0;
	source2 = 2;	
	dest = 3;
	shift = 8; 
	function = 0x2;
	
	e = mips_cpu_set_register(cpu, 2, 0xFF000000);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0x00FF0000){
		passed = 1;
	}

	
	mips_test_end_test(testId,passed, "testing srl = r3 = r2 >> 8");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SRLV -- Shift right logical variable
	//Shifts a register value right by the shift amount (shamt) 
	//and places the value in the destination register. Zeroes are shifted in
	name = "srlv";
	
	testId = mips_test_begin_test("srlv");
	
	//unsigned int function = 0x6;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x6;
	
	e = mips_cpu_set_register(cpu, 1, 8);
	e = mips_cpu_set_register(cpu, 2, 0xFF000000);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0x00FF0000){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing srlv = r3 = r2 >> r1");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SRAV -- Shift right Arithmatic variable
	//Shifts a register value right by the shift amount (shamt) 
	//and places the value in the destination register. Zeroes are shifted in
	name = "srav";
	
	testId = mips_test_begin_test("srav");
	
	//unsigned int function = 0x7;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x7;
	
	e = mips_cpu_set_register(cpu, 1, 8);
	e = mips_cpu_set_register(cpu, 2, 0xFF000000);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0xFFFF0000){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing srav");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SUB -- Subtracts two registers and stores the result in a register

	name = "sub";
	
	testId = mips_test_begin_test("sub");
	
	//unsigned int function = 0x22;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x22;
	
	e = mips_cpu_set_register(cpu, 1, 40);
	e = mips_cpu_set_register(cpu, 2, 90);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(int32_t(got) == -50){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing subu = r3 = r1 ^ r2 = 0");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SLL -- Shift left logical
	//Shifts a register value left by the shift amount listed in the instruction 
	//and places the result in a third register. Zeroes are shifted in.

	name = "sll";
	
	testId = mips_test_begin_test("sll");
	
	//unsigned int function = 0x0;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 8; 
	function = 0x0;
	
	e = mips_cpu_set_register(cpu, 2, 0x000000FF);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0x0000FF00){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sll r3 = r2 << shift");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//SLLV -- Shift left logical variable
	//Shifts a register value left by the shift amount listed in the register 
	//and places the result in a third register. Zeroes are shifted in.

	name = "sllv";
	
	testId = mips_test_begin_test("sllv");
	
	//unsigned int function = 0x4;
	source1 = 1;
	source2 = 2;	
	dest = 3;
	shift = 0; 
	function = 0x4;
	e = mips_cpu_set_register(cpu, 2, 8);
	e = mips_cpu_set_register(cpu, 2, 0x0000FF00);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, dest, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0x00FF0000){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sllv r3 = r2 << shift");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//MTHI -- Move To HI
	//Description:
	//The contents of the specified register are moved to the HI register.
	name = "mthi";
	
	testId = mips_test_begin_test("mthi");
	//unsigned int function = 0x11;
	//uint32_t LO = 33;
	source1 = 0;
	source2 = 0;	
	dest = 3;
	shift = 0; 
	function = 0x11;
	e = mips_cpu_set_register(cpu, dest, 100);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	cout << "the answer is " << got << endl;
	
	passed = 1;
	
	mips_test_end_test(testId,passed, "testing mthi = r3");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//MFLO -- Move from LO
	//Description:
	//The contents of register LO are moved to the specified register.
	name = "mflo";
	
	testId = mips_test_begin_test("mflo");
	
	//unsigned int function = 0x12;
	source1 = 0;
	source2 = 0;	
	dest = 24;
	shift = 0; 
	function = 0x12;
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, dest, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 0){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing mflo = r3");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//MTLO -- Move to LO
	//Description:
	//The contents of a register are moved to the LO register.
	name = "mtlo";
	
	testId = mips_test_begin_test("mtlo");
	
	//unsigned int function = 0x10;
	//uint32_t LO = 34;
	source1 = 0;
	source2 = 0;	
	dest = 24;
	shift = 0; 
	function = 0x13;
	e = mips_cpu_set_register(cpu, dest, 1000);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	cout << "the answer is " << got << endl;
	
	passed = 1;
	
	mips_test_end_test(testId,passed, "testing mtlo");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//MFHI -- Move From HI
	//Description:
	//The contents of the HI register are moved to the specified register.
	name = "mfhi";
	
	testId = mips_test_begin_test("mfhi");
	//unsigned int function = 0x10;
	source1 = 0;
	source2 = 0;	
	dest = 3;
	shift = 0; 
	function = 0x10;
	e = mips_cpu_set_register(cpu, dest, 8);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, dest, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 100){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing mfhi");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//MFLO -- Move from LO
	//Description:
	//The contents of register LO are moved to the specified register.
	name = "mflo";
	
	testId = mips_test_begin_test("mflo");
	
	//unsigned int function = 0x12;
	source1 = 0;
	source2 = 0;	
	dest = 24;
	shift = 0; 
	function = 0x12;
	
	e = mips_cpu_set_register(cpu, dest, 8);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, dest, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 1000){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing mflo");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//multu	011001	f $s, $t	hi:lo = $s * $t
	name = "multu";
	
	testId = mips_test_begin_test("multu");
	
	//unsigned int function = 0x19;
	source1 = 10;
	source2 = 11;	
	dest = 0;
	shift = 0; 
	function = 0x19;
	
	e = mips_cpu_set_register(cpu, source1, 8);
	e = mips_cpu_set_register(cpu, source2, 8);	
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	err = SetRInstruction(0,0,3,0,0x12, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if(got == 64){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing multu");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//mult	011000	f $s, $t	hi:lo = $s * $t
	name = "mult";
	
	testId = mips_test_begin_test("mult");
	
	//unsigned int function = 0x18;
	source1 = 30;
	source2 = 31;	
	dest = 0;
	shift = 0; 
	function = 0x18;
	
	e = mips_cpu_set_register(cpu, source1, 1);
	e = mips_cpu_set_register(cpu, source2, 0xFFFFFFFF);	
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	err = SetRInstruction(0,0,3,0,0x12, mem, cpu);
	uint32_t mult = 0;
	err = SetRInstruction(0,0,4,0,0x10, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);//answer in LO
	e = mips_cpu_get_register(cpu, 4, &mult);//answer in HI
	
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if((got == 0xFFFFFFFF) &&(mult == 0xFFFFFFFF)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing mult");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//divu	011011	f $s, $t	lo = $s / $t; hi = $s % $t
	name = "divu";
	
	testId = mips_test_begin_test("divu");
	
	source1 = 7;
	source2 = 9;	
	dest = 0;
	shift = 0; 
	function = 0x1B;
	
	e = mips_cpu_set_register(cpu, source1, 10);
	e = mips_cpu_set_register(cpu, source2, 4);	
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	err = SetRInstruction(0,0,3,0,0x12, mem, cpu);
	uint32_t div = 0;
	err = SetRInstruction(0,0,4,0,0x10, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);//answer in LO remainder
	e = mips_cpu_get_register(cpu, 4, &div);//answer in HI main
	
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if((got == 2) &&(div == 2)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing divu");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//div	011010	f $s, $t	lo = $s / $t; hi = $s % $t
	name = "div";
	
	testId = mips_test_begin_test("div");
	
	//unsigned int function = 0x1A;
	source1 = 7;
	source2 = 9;	
	dest = 0;
	shift = 0; 
	function = 0x1A;
	
	e = mips_cpu_set_register(cpu, source1, -5);
	e = mips_cpu_set_register(cpu, source2, 2);	
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	err = SetRInstruction(0,0,3,0,0x12, mem, cpu);
	div = 0;
	err = SetRInstruction(0,0,4,0,0x10, mem, cpu);
	
	cout << "the answer before get is " << got << endl;
	
	e = mips_cpu_get_register(cpu, 3, &got);//answer in LO remainder
	e = mips_cpu_get_register(cpu, 4, &div);//answer in HI main
	
	
	cout << "the answer is " << got << endl;
	
	passed = 0;
	if((int32_t(got) == -1) &&(int32_t(div) == -2)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing div");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BEQ 	
      //if $s == $t advance_pc (offset << 2)); else advance_pc (4);
	name = "beq";
	
	testId = mips_test_begin_test("beq");
	
	uint32_t opcode = 4;
	source1 = 7;
	source2 = 9;	
	int32_t ImConstant = 5;
	uint32_t pctemp; 
	uint32_t pcnow;
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 4096);
	e = mips_cpu_set_register(cpu, source2, 4096);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing beq");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BEQ 	
      //if $s == $t advance_pc (offset << 2)); else advance_pc (4);
	name = "beq";
	
	testId = mips_test_begin_test("beq");
	
	opcode = 4;
	source1 = 7;
	source2 = 9;	
	ImConstant = -5;
	//pctemp; 
	//pcnow;
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 4096);
	e = mips_cpu_set_register(cpu, source2, 4096);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing beq");
	cout << "test ended" << endl << endl << endl;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BGEZ -- Branch on greater than or equal to zero
      //if $s >= 0 advance_pc (offset << 2)); else advance_pc (4)
	name = "bgez";
	
	testId = mips_test_begin_test("bgez");
	
	opcode = 1;
	source1 = 7;
	source2 = 1;	
	ImConstant = -7;
	//pctemp; 
	//pcnow;
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 1);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing bgez");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BGEZAL	Branch on non-negative (>=0) and link	4 XXXX
    //if $s >= 0 $31 = PC + 8 (or nextPC + 4); advance_pc (offset << 2)); else advance_pc (4);
	name = "bgezal";
	
	testId = mips_test_begin_test("bgezal");
	
	opcode = 1;
	source1 = 7;
	source2 = 17;	
	ImConstant = -7;
	//pctemp; 
	//pcnow;
	uint32_t pcreturn;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 1);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	e = mips_cpu_get_register(cpu, 31, &pcreturn);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if(((pctemp + ImConstant*4) == pcnow)&&(pcreturn == pctemp + 8)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing bgezal");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BGTZ	Branch on greater than zero	3 XXX
    //if $s > 0 advance_pc (offset << 2)); else advance_pc (4)
	name = "bgtz";
	
	testId = mips_test_begin_test("bgtz");
	
	opcode = 7;
	source1 = 7;
	source2 = 0;	
	ImConstant = 7;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 1);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing bgtz");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BLEZ	Branch on less than or equal to zero	3 XXX
    //if $s <= 0 advance_pc (offset << 2)); else advance_pc (4)
	name = "blez";
	
	testId = mips_test_begin_test("blez");
	
	opcode = 6;
	source1 = 7;
	source2 = 0;	
	ImConstant = 6;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 0);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing blez");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BLEZ	Branch on less than or equal to zero	3 XXX
    //if $s <= 0 advance_pc (offset << 2)); else advance_pc (4)
	name = "blez";
	
	testId = mips_test_begin_test("blez");
	
	opcode = 6;
	source1 = 7;
	source2 = 0;	
	ImConstant = 6;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 0);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing blez");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BLTZ  |  Branch on less than zero  
    //if $s < 0 advance_pc (offset << 2)); else advance_pc (4)
	name = "bltz";
	
	testId = mips_test_begin_test("bltz");
	
	opcode = 1;
	source1 = 7;
	source2 = 0;	
	ImConstant = 6;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 0);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if(pctemp + 4 == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing bltz");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BLTZAL|  Branch on less than zero and link       
      //if $s < 0 $31 = PC + 8 (or nPC + 4); advance_pc (offset << 2)); else advance_pc (4)
	name = "bltzal";
	
	testId = mips_test_begin_test("bltzal");
	
	opcode = 1;
	source1 = 7;
	source2 = 16;	
	ImConstant = 6;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, -8998788);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	e = mips_cpu_get_register(cpu, 31, &pcreturn);
	
	passed = 0;
	if(((pctemp + ImConstant*4) == pcnow)&&(pcreturn == pctemp + 8)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing bltzal");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//BNE   |  Branch on not equal   
     //if $s != 0 advance_pc (offset << 2)); else advance_pc (4)
	name = "bne";
	
	testId = mips_test_begin_test("bne");
	
	opcode = 5;
	source1 = 7;
	source2 = 8;	
	ImConstant = 6;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 0);	
	e = mips_cpu_set_register(cpu, source2, 10000);	


	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before branch is " << pctemp << endl;
	
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after branch is " << pcnow << endl;
	
	passed = 0;
	if((pctemp + ImConstant*4) == pcnow){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing bne");
	cout << "test ended" << endl << endl << endl;	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//ADDI  |  Add immediate (with overflow)           
      //source2 = source1 + imm; advance_pc (4);
	name = "addi";
	
	testId = mips_test_begin_test("addi");
	
	opcode = 8;
	source1 = 7;
	source2 = 9;	
	ImConstant = -7;
	//pctemp; 
	//pcnow;
	
	mips_cpu_get_pc(cpu, &pctemp);
	
	e = mips_cpu_set_register(cpu, source1, 100);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before addi is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 93){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing addi");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//ADDIU |  Add immediate unsigned (no overflow)           
      //source2 = source1 + imm; advance_pc (4);
	name = "addiu";
	
	testId = mips_test_begin_test("addiu");
	
	opcode = 9;
	source1 = 7;
	source2 = 9;	
	ImConstant = 7;
	
	e = mips_cpu_set_register(cpu, source1, 200);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before addi is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 207){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing addiu");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//ANDI  |  Bitwise and immediate                             
      //source2 = source1 & imm; advance_pc (4);
	name = "andi";
	
	testId = mips_test_begin_test("andi");
	
	opcode = 12;
	source1 = 7;
	source2 = 9;	
	ImConstant = 0xFFFFFFFF;
	
	e = mips_cpu_set_register(cpu, source1, 0xFFFFFFFF);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before addi is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 0x0000FFFF){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing andi");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//XORI  |  Bitwise exclusive or immediate                                     
      //source2 = source1 ^ imm; advance_pc (4);
	name = "xori";
	
	testId = mips_test_begin_test("xori");
	
	opcode = 14;
	source1 = 16;
	source2 = 17;	
	ImConstant = 0xFFFF0000;
	
	e = mips_cpu_set_register(cpu, source1, 0);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before addi is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 0){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing xori");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//ORI   |  Bitwise or immediate                                                         
      //source2 = source1 | imm; advance_pc (4);
	name = "ori";
	
	testId = mips_test_begin_test("ori");
	
	opcode = 13;
	source1 = 16;
	source2 = 17;	
	ImConstant = 0xFFFF0000;
	
	e = mips_cpu_set_register(cpu, source1, 0xFF);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before addi is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 0xFF){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing ori");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SLT   |  Set on less than (signed)               
      //if $s < $t $d = 1; advance_pc (4); else $d = 0; advance_pc (4);
	name = "slt";
	
	testId = mips_test_begin_test("slt");
	
	opcode = 0;
	source1 = 16;
	source2 = 17;
	dest = 5;
	shift = 0;
	function = 0x2A; 
	
	e = mips_cpu_set_register(cpu, source1, 0xFFFFFFFF);
	e = mips_cpu_set_register(cpu, source2, 0xFFFFFFFF);

	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	
	cout << "the answer before slt is " << got << endl;
	
	mips_cpu_get_register(cpu, dest, &got);
	
	cout << "the answer after slt is " << got << endl;
	
	passed = 247983;
	if(got == 0){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing slt");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SLTI  |  Set on less than immediate (signed)                                                               
      //if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
	name = "slti";
	
	testId = mips_test_begin_test("slti");
	
	opcode = 10;
	source1 = 1;
	source2 = 2;	
	ImConstant = 0xFFFF0000;
	
	e = mips_cpu_set_register(cpu, source1, 0xF0000000);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 1){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing slti");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SLTIU  |  Set on less than immediate (unsigned)                                                               
      //if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
	name = "sltiu";
	
	testId = mips_test_begin_test("sltiu");
	
	opcode = 11;
	source1 = 1;
	source2 = 2;	
	ImConstant = 0x0FFFF000;
	
	e = mips_cpu_set_register(cpu, source1, 0x0F000000);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 0){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sltiu");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SLTIU  |  Set on less than immediate (unsigned)                                                               
      //if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
	name = "sltiu";
	
	testId = mips_test_begin_test("sltiu");
	
	opcode = 11;
	source1 = 1;
	source2 = 2;	
	ImConstant = 0xF000;
	
	e = mips_cpu_set_register(cpu, source1, 0);	

	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	mips_cpu_get_register(cpu, source2, &got);
	
	cout << "the answer after addi is " << got << endl;
	
	passed = 0;
	if(got == 1){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sltiu");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SW    |  Store word                                                                                             
      //MEM[source1 + offset] = source2; advance_pc (4);
	name = "sw";
	
	testId = mips_test_begin_test("sw");
	
	opcode = 0x2B;
	source1 = 1;
	source2 = 2;	
	ImConstant = -4;
	
	e = mips_cpu_set_register(cpu, source1, 24);	
	e = mips_cpu_set_register(cpu, source2, 0xabcdefff);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	uint8_t data[4];
	mips_mem_read(
		mem,		//!< Handle to target memory
		24 + -4,	//!< Byte address to start transaction at
		4,	//!< Number of bytes to transfer
		data	//!< Receives the target bytes
	);
	  got = (((uint32_t)data[0])<<24)
        |
        (((uint32_t)data[1])<<16)
        |
        (((uint32_t)data[2])<<8)
        |
        (((uint32_t)data[3])<<0);
	
	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if((got == 0xabcdefff )&&(err != mips_ExceptionInvalidAddress)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sw");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SB    |  Store byte                                                                                             
      //MEM[source1 + offset] = source2; advance_pc (4);
	name = "sb";
	
	testId = mips_test_begin_test("sb");
	
	opcode = 0x28;
	source1 = 1;
	source2 = 2;	
	ImConstant = 1;
	
	e = mips_cpu_set_register(cpu, source1, 66);	
	e = mips_cpu_set_register(cpu, source2, 0xFF123456);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	uint8_t onebyteData[1];

	mips_mem_read(
		mem,		//!< Handle to target memory
		66+1,	//!< Byte address to start transaction at
		1,	//!< Number of bytes to transfer
		onebyteData	//!< Receives the target bytes
	);
	  got = uint32_t (onebyteData[0]);
	
	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0x56){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sb");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SB    |  Store byte                                                                                             
      //MEM[source1 + offset] = source2; advance_pc (4);
	name = "sb";
	
	testId = mips_test_begin_test("sb");
	
	opcode = 0x28;
	source1 = 1;
	source2 = 2;	
	ImConstant = 1;
	
	e = mips_cpu_set_register(cpu, source1, 66);	
	e = mips_cpu_set_register(cpu, source2, 0xFF123456);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;

	mips_mem_read(
		mem,		//!< Handle to target memory
		66+1,	//!< Byte address to start transaction at
		1,	//!< Number of bytes to transfer
		onebyteData	//!< Receives the target bytes
	);
	  got = uint32_t (onebyteData[0]);
	
	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0x56){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sb");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//SH    |  Store half word                                                                                            
      //MEM[source1 + offset] = source2; advance_pc (4);
	name = "sh";
	
	testId = mips_test_begin_test("sh");
	
	opcode = 0x29;
	source1 = 1;
	source2 = 2;	
	ImConstant = 2;
	
	e = mips_cpu_set_register(cpu, source1, 66);	
	e = mips_cpu_set_register(cpu, source2, 0xFFFFFFFF);	
	
	err = SetIInstruction(opcode, source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	uint8_t halfwordData[2];

	mips_mem_read(
		mem,		//!< Handle to target memory
		66 + ImConstant,	//!< Byte address to start transaction at
		2,	//!< Number of bytes to transfer
		halfwordData //!< Receives the target bytes
	);
	got = (((uint32_t)halfwordData[0])<<8)
        |
        (((uint32_t)halfwordData[1])<<0);
	
	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xFFFF){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing sh");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LW , A word is loaded into a register from the specified address                                                                                           
      //source2 = MEM[source1 + offset]; advance_pc (4);
	name = "lw";
	
	testId = mips_test_begin_test("lw");
	
	opcode = 0x23;
	source1 = 1;
	source2 = 2;	
	ImConstant = 4;
	
	e = mips_cpu_set_register(cpu, source1, 76);	
	e = mips_cpu_set_register(cpu, source2, 0xFFFFFFFF);	
	
	//data[4];
	
	data[0] = 0xAB;
	data[1] = 0xBC;
	data[2] = 0xDE;
	data[3] = 0xFF;

	mips_mem_write(mem, (76+ImConstant), 4, data);

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xABBCDEFF){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lw");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LB , A byte is loaded into a register from the specified address                                                                                           
      //source2 = MEM[source1 + offset]; advance_pc (4);
	name = "lb";
	
	testId = mips_test_begin_test("lb");
	
	opcode = 32;
	source1 = 1;
	source2 = 2;	
	ImConstant = 1;
	
	e = mips_cpu_set_register(cpu, source1, 76);	
	e = mips_cpu_set_register(cpu, source2, 0);	
	
	//data[4];
	
	onebyteData[0] = 0x45;

	mips_mem_write(mem, (76+ImConstant), 1, onebyteData);

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0x45){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lb");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LBU , A byte is loaded into a register from the specified address                                                                                           
      //source2 = MEM[source1 + offset]; advance_pc (4);
	name = "lbu";
	
	testId = mips_test_begin_test("lbu");
	
	opcode = 36;
	source1 = 1;
	source2 = 2;	
	ImConstant = 1;
	
	e = mips_cpu_set_register(cpu, source1, 76);	
	e = mips_cpu_set_register(cpu, source2, 0);	
	
	//data[4];
	
	onebyteData[0] = 0x00;

	mips_mem_write(mem, (76+ImConstant), 1, onebyteData);

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0x00){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lbu");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LH To load a halfword from memory as a signed value                                                                                          
      //rt ← memory[base+offset]
	name = "lh";
	
	testId = mips_test_begin_test("lh");
	
	opcode = 33;
	source1 = 2;
	source2 = 17;	
	ImConstant = 2;
	
	e = mips_cpu_set_register(cpu, source1, 76);	
	e = mips_cpu_set_register(cpu, source2, 0);	
	
	//data[4];
	
	halfwordData[0] = 0xFF;
	halfwordData[1] = 0xAB;

	mips_mem_write(mem, (76+ImConstant), 2, halfwordData);

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xFFFFFFAB){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lh");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LHU To load a halfword from memory as a unsigned value                                                                                          
      //rt ← memory[base+offset]
	name = "lhu";
	
	testId = mips_test_begin_test("lhu");
	
	opcode = 37;
	source1 = 2;
	source2 = 17;	
	ImConstant = 2;
	
	e = mips_cpu_set_register(cpu, source1, 76);	
	e = mips_cpu_set_register(cpu, source2, 0);	
	
	//data[4];
	
	halfwordData[0] = 0xFF;
	halfwordData[1] = 0xAB;

	mips_mem_write(mem, (76+ImConstant), 1, halfwordData);

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xFFAB){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lhu");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LUI 
	//The immediate value is shifted left 16 bits 
	//and stored in the register. The lower 16 bits are zeroes  	
	name = "lui";
	
	testId = mips_test_begin_test("lui");
	
	opcode = 15;
	source1 = 0;
	source2 = 17;	
	ImConstant = 0xFFFA;
		
	e = mips_cpu_set_register(cpu, source2, 0);	

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xFFFA0000){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lui");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LWL LWL rt, offset(base)                                                                                         
      //To load the most-significant part of a word as a signed value from an
	//unaligned memory address.
	name = "lwl";
	
	testId = mips_test_begin_test("lwl");
	
	opcode = 34;
	source1 = 2;
	source2 = 17;	
	ImConstant = 2;
	
	e = mips_cpu_set_register(cpu, source1, 10);	
	e = mips_cpu_set_register(cpu, source2, 0xFFFFFFFF);	
	
	//data[4];
	
	data[0] = 0xCD;
	data[1] = 0xAB;
	data[2] = 0x67;
	data[3] = 0x89;

	mips_mem_write(mem, 12, 4, data);

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xCDABFFFF){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lwl");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	//LWR rt, offset(base)                                                                                        
      //To load the least-significant part of a word from an unaligned memory
	//address as a signed value
	name = "lwr";
	
	testId = mips_test_begin_test("lwr");
	
	opcode = 38;
	source1 = 2;
	source2 = 17;	
	ImConstant = 1;
	
	e = mips_cpu_set_register(cpu, source1, 14);	

	err = SetIInstruction(opcode,source1,source2,ImConstant,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	e = mips_cpu_get_register(cpu, source2, &got);

	cout << "the answer after instruction is " << got << endl;
	
	passed = 0;
	if(got == 0xCDAB6789){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing lwr");
	cout << "test ended" << endl << endl << endl;
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	// J Jumps to the calculated address                                                              
      //PC = nPC; nPC = (PC & 0xf0000000) | (target << 2);
	name = "j";
	
	testId = mips_test_begin_test("j");
	
	opcode = 2;
	uint32_t Address = 3;

	err = SetJInstruction(opcode,Address,mem,cpu);
	
	cout << "the answer before instruction is " << got << endl;
	
	mips_cpu_get_pc(cpu, &pctemp);
	//mips_cpu_step(cpu);
	mips_cpu_get_pc(cpu, &pctemp);
	
	cout << "the answer after addi is " << pctemp << endl;
	
	passed = 0;
	if(pctemp == 3*4){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing j");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	// JAL -- Jump and link                                                            
      //$31 = PC + 8 (or nPC + 4); PC = nPC; nPC = (PC & 0xf0000000) | (target << 2)
	name = "jal";
	
	testId = mips_test_begin_test("jal");
	
	opcode = 3;
	Address = 10;
	mips_cpu_get_pc(cpu, &pctemp);
	err = SetJInstruction(opcode,Address,mem,cpu);
	
	cout << "the pc before jump is " << pctemp << endl;
	//mips_cpu_step(cpu);
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after jump is " << pcnow << endl;
	mips_cpu_get_register(cpu, 31, &got);
	cout << "the pc stored in pctemp is " << got << endl;
	
	passed = 0;
	if((pcnow == 10*4) && (got == pctemp + 8)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing jal");
	cout << "test ended" << endl << endl << endl;
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	// JR -- Jump register                                                            
      //PC = nPC; nPC = $s;
	name = "jr";
	
	testId = mips_test_begin_test("jr");
	
	opcode = 0;
	source1 = 0;
	source2 = 0;
	dest = 0;
	shift = 0;
	function = 0x8;
	mips_cpu_get_pc(cpu, &pctemp);
	
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	cout << "the pc before jump is " << pctemp << endl;
	//mips_cpu_step(cpu);
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after jump is " << pcnow << endl;
	mips_cpu_get_register(cpu, 0, &got);
	cout << "the pc stored in pctemp is " << got << endl;
	
	passed = 0;
	if((pcnow == 0) && (got == 0)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing jr");
	cout << "test ended" << endl << endl << endl;	
//--------------------------------------------------------------------------------------------------------------------------------------------------------
	// JRLR -- : To procedure call to an instruction address in a register.                                                           
      //rd ← return_addr, PC ← rs
	name = "jalr";
	
	testId = mips_test_begin_test("jalr");
	
	opcode = 0;
	source1 = 4;
	source2 = 0;
	dest = 8;
	shift = 0;
	function = 0x9;
	mips_cpu_get_pc(cpu, &pctemp);
	mips_cpu_set_register(cpu, source1,50);
	err = SetRInstruction(source1, source2, dest, shift,function, mem, cpu);
	cout << "the pc before jump is " << pctemp << endl;
	mips_cpu_get_pc(cpu, &pcnow);
	
	cout << "the answer after jump is " << pcnow << endl;
	mips_cpu_get_register(cpu, dest, &got);
	cout << "the pc stored in dest is " << got << endl;
	
	passed = 0;
	if((pcnow == 50) && (got == pctemp)){
		passed = 1;
	}
	
	mips_test_end_test(testId,passed, "testing jalr");
	cout << "test ended" << endl << endl << endl;
	
	
	mips_test_end_suite();
	
	return 0;
}

mips_error SetRInstruction(uint32_t source1,uint32_t source2,uint32_t dest,uint32_t shift,uint32_t function,mips_mem_h mem,mips_cpu_h cpu){
	
	uint32_t instruction = 0;
	         instruction = 
	((source1 & 0x1F) << 21) | ((source2 & 0x1F) << 16) |
	((dest & 0x1F) << 11) | ((shift &0x1f) << 6) | ((function & 0x3F) << 0);
	

	uint32_t pc;
	
	mips_error e = mips_cpu_get_pc(cpu, &pc);
	
	if(e != 0){
		return e;
	}
	
	cout << "the instruction test is " << instruction << endl;
	
	uint8_t Byte[4];
	Byte[0] = (instruction >> 24) & 0xFF;
	Byte[1] = (instruction >> 16) & 0xFF;
	Byte[2] = (instruction >> 8) & 0xFF;
	Byte[3] = (instruction >> 0) & 0xFF;
	
	uint32_t test =  (((uint32_t)Byte[0])<<24)
        |
        (((uint32_t)Byte[1])<<16)
        |
        (((uint32_t)Byte[2])<<8)
        |
        (((uint32_t)Byte[3])<<0);
	  
	cout << test << endl;
	
	mips_error err = mips_mem_write(mem, pc, 4, Byte);
	
	if (err != 0){
		return err;
	}
	
	err = mips_cpu_step(cpu);
	
	return err;
}

mips_error SetIInstruction(uint32_t opcode,uint32_t source1,uint32_t source2,int32_t ImConstant,mips_mem_h mem,mips_cpu_h cpu){
	
	uint32_t instruction = 0;
	         instruction = 
	(opcode << 26) | (source1 << 21) | (source2 << 16) |
	((ImConstant << 0) & (0x0000FFFF));
	
	uint32_t pc;
	
	mips_error e = mips_cpu_get_pc(cpu, &pc);
	
	if(e != 0){
		return e;
	}
	
	cout << "the instruction test is " << instruction << endl;
	
	uint8_t Byte[4];
	Byte[0] = (instruction >> 24) & 0xFF;
	Byte[1] = (instruction >> 16) & 0xFF;
	Byte[2] = (instruction >> 8) & 0xFF;
	Byte[3] = (instruction >> 0) & 0xFF;
	
	uint32_t test =  (((uint32_t)Byte[0])<<24)
        |
        (((uint32_t)Byte[1])<<16)
        |
        (((uint32_t)Byte[2])<<8)
        |
        (((uint32_t)Byte[3])<<0);
	  
	cout << test << endl;
	
	mips_error err = mips_mem_write(mem, pc, 4, Byte);
	
	if (err != 0){
		return err;
	}
	
	err = mips_cpu_step(cpu);
	
	return err;
}

mips_error SetJInstruction(uint32_t opcode,uint32_t Address,mips_mem_h mem,mips_cpu_h cpu){
	
	uint32_t instruction = 0;
	         instruction = 
	(opcode << 26) |
	((Address << 0) & (0x03FFFFFF));
	
	uint32_t pc;
	
	mips_error e = mips_cpu_get_pc(cpu, &pc);
	
	if(e != 0){
		return e;
	}
	
	cout << "the instruction test is " << instruction << endl;
	
	uint8_t Byte[4];
	Byte[0] = (instruction >> 24) & 0xFF;
	Byte[1] = (instruction >> 16) & 0xFF;
	Byte[2] = (instruction >> 8) & 0xFF;
	Byte[3] = (instruction >> 0) & 0xFF;
	
	uint32_t test =  (((uint32_t)Byte[0])<<24)
        |
        (((uint32_t)Byte[1])<<16)
        |
        (((uint32_t)Byte[2])<<8)
        |
        (((uint32_t)Byte[3])<<0);
	  
	cout << test << endl;
	
	mips_error err = mips_mem_write(mem, pc, 4, Byte);
	
	if (err != 0){
		return err;
	}
	
	err = mips_cpu_step(cpu);
	
	return err;
}		