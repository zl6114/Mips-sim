#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "mips.h"

using namespace std;


struct mips_cpu_impl{
	uint32_t pc;
	uint32_t pcNext;
	uint32_t reg[32];
	uint32_t HI;
	uint32_t LO;
	mips_mem_h mem;
};

mips_cpu_h mips_cpu_create(mips_mem_h mem){
	mips_cpu_impl *state = new mips_cpu_impl;
	
	state -> pc = 0;
	state -> pcNext = 4;
	for (unsigned int i=0;i<32;i++){
		state -> reg[i] = 0;
	}
	state -> mem = mem;
	state -> HI = 0;
	state -> LO = 0;
	
	return state;
}

mips_error mips_cpu_reset(mips_cpu_h state){
	
	state -> pc = 0;
	for (unsigned int i=0;i<32;i++){
		state -> reg[i] = 0;
	}
	state -> HI = 0;
	state -> LO = 0;
	return mips_Success;	
}

/*! Returns the current value of one of the 32 general purpose MIPS registers */
mips_error mips_cpu_get_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t *value		//!< Where to write the value to
	){
		if(state == 0){
			return mips_ErrorInvalidHandle;
		}if(index > 33){
			return mips_ErrorInvalidArgument;
		}
			*value = state -> reg[index];
		return mips_Success;		
	}
	
/*! Modifies one of the 32 general purpose MIPS registers. */
mips_error mips_cpu_set_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t value		//!< New value to write into register file
	){

			state -> reg[index] = value;

		return mips_Success;
		
	}
	

/*! Sets the program counter for the next instruction to the specified byte address.*/
mips_error mips_cpu_set_pc(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	uint32_t pc			//!< Address of the next instruction to exectute.
	){
		state -> pc = pc;
		return mips_Success;
	}
	
/*! Gets the pc for the next instruction.*/
mips_error mips_cpu_get_pc(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	uint32_t *pc		//!< Where to write the byte address too
	){
		*pc = state -> pc;
		return mips_Success;
	}
	
struct Instruction{
	uint32_t Instruct;
	char type;	// R I J
	
};

uint32_t SignToUnsign(uint32_t a){
	if(a > 0x7FFFFFFF){
		a = ~a + 1;
	}
	return a;
}

mips_error R(uint32_t function, uint32_t source1,uint32_t source2,uint32_t dest, uint32_t shift, mips_cpu_h state);
mips_error IJ(uint32_t UnsignImConstant, uint32_t opcode,uint32_t source1,uint32_t source2,int32_t ImConstant,uint32_t Address, mips_cpu_h state);

uint32_t to_big(const uint8_t *pData)
{
    return
        (((uint32_t)pData[0])<<24)
        |
        (((uint32_t)pData[1])<<16)
        |
        (((uint32_t)pData[2])<<8)
        |
        (((uint32_t)pData[3])<<0);
}


mips_error mips_cpu_step(
	mips_cpu_h state	//! Valid (non-empty) handle to a CPU
	){
		cout << "enter cpu step state" << endl;
		uint8_t buffer[4];
		mips_error e;
    
		mips_error err=mips_mem_read(
			state->mem,		//!< Handle to target memory
			state->pc,	//!< Byte address to start transaction at
			4,	//!< Number of bytes to transfer
			buffer	//!< Receives the target bytes
		);
    
		if(err!=0) {
			return err;
		}
		
		Instruction a;
    
		a.Instruct = to_big(buffer);
		
		uint32_t opcode = (a.Instruct >> 26) & 0x3F;
		uint32_t source1 = (a.Instruct >> 21) & 0x1F;
		uint32_t source2 = (a.Instruct >> 16) & 0x1F;
		
		cout << "pc is equals to " << state -> pc <<endl;
		cout << "the instruction set is  " << a.Instruct << endl;
		
		if(opcode == 0){
			uint32_t dest = (a.Instruct >> 11) & 0x1F;
			uint32_t shift = (a.Instruct >> 6) & 0x1F;
			uint32_t function = (a.Instruct >> 0)& 0x3F;
			e = R(function,source1,source2,dest,shift,state);//do addu
			
		}else{
			int32_t ImConstant = (a.Instruct >> 0)& 0xFFFF;
			if((a.Instruct & 0x8000)== 0x8000){
				ImConstant = (0xFFFF0000 | (ImConstant));
				cout << "ImConstant is  " << ImConstant << endl; 
			}
			uint32_t UnsignImConstant = (a.Instruct >> 0)& 0xFFFF;
			uint32_t Address = (a.Instruct >> 0) & 0x03FFFFFF;
			e =  IJ(UnsignImConstant,opcode,source1,source2,ImConstant,Address,state);
		}
		
		state -> pc = state -> pcNext;
		
		cout << state-> pc << endl;
		
		state -> pcNext = state -> pcNext + 4;
		
		state -> reg[0] = 0;
		
		return e;
		
	}

	
mips_error R(uint32_t function, uint32_t source1,uint32_t source2,uint32_t dest, uint32_t shift, mips_cpu_h state){

	mips_error e;
	if ((source1 > 31) || (source2 > 31) || (dest > 31)){
		return mips_ErrorInvalidArgument;
	}
	uint32_t firstReg = state -> reg[source1];
	int32_t SignFirstReg = state -> reg[source1];
	int32_t SignSecondReg = state -> reg[source2];
	int64_t mult;
	cout << "the firstReg contains  " << SignFirstReg << endl;
	uint32_t SecondReg = state -> reg[source2];
	cout << "the SecondReg contains  " << SignSecondReg << endl;
	uint32_t DestReg = 0;
	cout << "the dest is " << dest << endl;
	if(function == 0x21){
		DestReg = firstReg + SecondReg;
		e = mips_Success;
	}else if(function == 0x20){
		DestReg = SignFirstReg + SignSecondReg;
		if(DestReg > 0x7FFFFFFF){
			e = mips_ExceptionArithmeticOverflow;
		}else{
			e = mips_Success;
		}
	}else if(function == 0x24){
		DestReg = firstReg & SecondReg;
	}else if(function == 0x25){
		DestReg = firstReg | SecondReg;
	}else if(function == 0x23){
		DestReg = firstReg - SecondReg;
	}else if(function == 0x26){
		DestReg = firstReg ^ SecondReg;
	}
	else if(function == 0x2B){
		if(firstReg < SecondReg){
			DestReg = 1;
		}else{
			DestReg = 0;
		}
	}else if(function == 0x3){
		if((SecondReg & 0x80000000) == 0x80000000){
			DestReg = ~((~SecondReg + 1) >> shift)+1;
		}else{
			DestReg = ((SecondReg) >> shift);
		}	
	}else if(function == 0x2){
		DestReg = (SecondReg) >> shift;
	}else if(function == 0x6){
		DestReg = (SecondReg) >> firstReg;
	}else if(function == 0x22){
		firstReg = SignToUnsign(firstReg);
		SecondReg = SignToUnsign(SecondReg);
		DestReg = firstReg - SecondReg;
		if(DestReg > 0x7FFFFFFF){
			e = mips_ExceptionArithmeticOverflow;
		}else{
			e = mips_Success;
		}
		
	}else if(function == 0x0){
		DestReg = SecondReg << shift;
	}else if(function == 0x4){
		DestReg = SecondReg << firstReg;
	}else if(function == 0x7){
		if((SecondReg & 0x80000000) == 0x80000000){
			DestReg = ~((~SecondReg + 1) >> firstReg)+1;
		}else{
			DestReg = ((SecondReg) >> firstReg);
		}			
	}else if(function == 0x11){
		DestReg = state -> reg[dest];
		state -> HI = DestReg;
	}else if(function == 0x10){
		DestReg = state -> HI;
	}else if(function == 0x12){
		DestReg = state -> LO;	
	}else if(function == 0x13){
		DestReg = state -> reg[dest];
		state -> LO = DestReg;		
	}else if(function == 0x19){
		mult = firstReg * SecondReg;
		state -> LO = (mult & 0XFFFFFFFF);
		state -> HI = (mult >> 32);	
	}else if(function == 0x18){
		if(((firstReg & 0x80000000) == 0x80000000)&&
		   ((SecondReg & 0x80000000) == 0x80000000)){
			firstReg = SignToUnsign(firstReg);
			SecondReg = SignToUnsign(SecondReg);
			mult = firstReg * SecondReg;
		}else if((((firstReg & 0x80000000) != 0x80000000)&&
		   ((SecondReg & 0x80000000) != 0x80000000))){
			 mult = firstReg * SecondReg;  
		}else{
			firstReg = SignToUnsign(firstReg);
			SecondReg = SignToUnsign(SecondReg);
			mult = firstReg * SecondReg;
			mult = (~mult) + 1;
		}
		state -> LO = (mult & 0XFFFFFFFF);
		state -> HI = (mult >> 32);	
	}else if(function == 0x1B){
		state -> LO = firstReg % SecondReg;
		cout << "LO is " << state->LO << endl;
		state -> HI = firstReg / SecondReg;
		cout << "HI is " << state -> HI << endl;
	}else if(function == 0x1A){
		if(((firstReg & 0x80000000) == 0x80000000)&&
		   ((SecondReg & 0x80000000) == 0x80000000)){
			firstReg = SignToUnsign(firstReg);
			SecondReg = SignToUnsign(SecondReg);
			state -> LO = firstReg % SecondReg;
			state -> HI = firstReg / SecondReg;
		}else if((((firstReg & 0x80000000) != 0x80000000)&&
		   ((SecondReg & 0x80000000) != 0x80000000))){
			state -> LO = firstReg % SecondReg;
			state -> HI = firstReg / SecondReg;
		}else{
			firstReg = SignToUnsign(firstReg);
			SecondReg = SignToUnsign(SecondReg);
			state -> LO = ~(firstReg % SecondReg) + 1;
			state -> HI = ~(firstReg / SecondReg) + 1;
		}
	}else if(function == 0x2A){
		if(SignFirstReg < SignSecondReg){
			DestReg = 1;
		}else{
			DestReg = 0;
		}
	}else if(function == 0x8){
		state -> pc = state -> pcNext;
		state -> pcNext = firstReg;
	}else if(function == 0x9){
		DestReg = state -> pc;
		state -> pc = state -> pcNext;
		state -> pcNext = firstReg;
	}
	
	
	state -> reg[dest] = DestReg;
	cout << "the answer calculated in cpu is  " << DestReg << endl;
	return e;

	
}

mips_error IJ(uint32_t UnsignImConstant,uint32_t opcode,uint32_t source1, uint32_t source2,int32_t ImConstant,uint32_t Address,mips_cpu_h state)
{
	if ((source1 > 31) || (source2 > 31)){
		return mips_ErrorInvalidArgument;
	}
	//maybe need to modify the signess
	int32_t Register1 = state -> reg[source1];
	int32_t Register2 = state -> reg[source2];
	uint32_t UnSignRegister1 = state -> reg[source1];
	//uint32_t UnSignRegister2 = state -> reg[source2];
	uint8_t Byte[4];
	uint8_t OneByte[1];
	uint8_t TwoByte[2];
	mips_error e = mips_Success;
	if(opcode == 4){
		if(Register1 == Register2){
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BEQ is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}
	}else if((opcode == 1) && (source2 == 1)){
		if(Register1 >= 0){
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BGE is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}
	}else if((opcode == 1) && (source2 == 17)){
		if(Register1 >= 0){
			state -> reg[31] = state -> pc + 8;
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BGEZAL is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}
	}else if(opcode == 7){
		if(Register1 > 0){
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BGtz is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}		
	}else if(opcode == 6){
		if(Register1 <= 0){
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BLEZ is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}		
	}else if((opcode == 1) && (source2 == 0)){
		if(Register1 < 0){
			state -> reg[31] = state -> pc + 8;
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BLTZ is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}
	}else if((opcode == 1) && (source2 == 16)){
		if(Register1 < 0){
			state -> reg[31] = state -> pc + 8;
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BGEZAL is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}
	}else if(opcode == 5){
		if(Register1 != Register2){
			state -> pc = state -> pc + (ImConstant << 2)-4;
			cout << state -> pc << endl;
			cout << "BLEZ is true, branching  "<<endl;
			state -> pcNext = state -> pcNext + (ImConstant << 2)-4;
			cout << "pcNext is  " << state -> pcNext << endl;
		}		
	}else if(opcode == 8){
		Register2 = Register1 + ImConstant;
		if(Register2 > 0x7FFFFFFF){
			e = mips_ExceptionArithmeticOverflow;
		}
		state -> reg[source2] = Register2;
	}else if(opcode == 9){
		Register2 = Register1 + UnsignImConstant;
		state -> reg[source2] = Register2;
	}else if(opcode == 12){
		Register2 = Register1 & UnsignImConstant;
		state -> reg[source2] = Register2;
	}else if(opcode == 14){
		Register2 = Register1 ^ UnsignImConstant;
		state -> reg[source2] = Register2;
	}else if(opcode == 13){
		Register2 = Register1 | UnsignImConstant;
		state -> reg[source2] = Register2;		
	}else if(opcode == 10){
		if(Register1 < ImConstant){
			state -> reg[source2] = 1;
		}else{
			state -> reg[source2] = 0;
		}
	}else if(opcode == 11){
		if(UnSignRegister1 < UnsignImConstant){
			state -> reg[source2] = 1;
		}else{
			state -> reg[source2] = 0;
		}
	}else if(opcode == 43){
		Byte[0] = (Register2 >> 24) & 0xFF;
		Byte[1] = (Register2 >> 16) & 0xFF;
		Byte[2] = (Register2 >> 8) & 0xFF;
		Byte[3] = (Register2 >> 0) & 0xFF;
		//If either of the two least-significant
		//bits of the address are non-zero, an Address Error exception occurs.
		if(((Register1+ImConstant) & 0x3) != 0){
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			cout << "ExceptionInvalidAddress" << endl;
			e = mips_ExceptionInvalidAddress;
		}else{
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			mips_mem_write(state -> mem, (Register1+ImConstant), 4, Byte);
		}
		
	}else if(opcode == 40){
		OneByte[0] = (Register2) & 0xFF;
		cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
		mips_mem_write(state -> mem, (Register1+ImConstant), 1, OneByte);
	}else if(opcode == 41){
		TwoByte[0] = (Register2 >> 8) & 0xFF;
		TwoByte[1] = (Register2 >> 0) & 0xFF;
		cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
		mips_mem_write(state -> mem, (Register1+ImConstant), 2, TwoByte);
	}else if(opcode == 35){
		//If either of the two least-significant
		//bits of the address are non-zero, an Address Error exception occurs.
		if(((Register1+ImConstant) & 0x1) != 0){
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			cout << "ExceptionInvalidAddress" << endl;
			e = mips_ExceptionInvalidAddress;
		}else{
			mips_mem_read(
				state->mem,		//!< Handle to target memory
				(Register1+ImConstant),//!< Byte address to start transaction at
				4,	//!< Number of bytes to transfer
				Byte	//!< Receives the target bytes
			);
			Register2 = to_big(Byte);
			state -> reg[source2] = Register2;
			e = mips_Success;
		}
	}else if(opcode == 32){
		mips_mem_read(state -> mem, (Register1+ImConstant),1,OneByte);
		cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
		(Register2) = uint32_t (OneByte[0]);
		Register2 = Register2 & 0XFF;
		cout << "the Byte data is " << Register2 << endl;
		state -> reg[source2] = Register2;
	}else if(opcode == 36){
		mips_mem_read(state -> mem, (Register1+ImConstant),1,OneByte);
		cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
		(Register2) = uint32_t (OneByte[0]);
		Register2 = Register2 & 0XFF;
		cout << "the Byte data is " << Register2 << endl;
		state -> reg[source2] = Register2;
	}else if(opcode == 33){
		//If either of the one least-significant
		//bits of the address are non-zero, an Address Error exception occurs.
		if(((Register1+ImConstant) & 0x1) != 0){
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			cout << "ExceptionInvalidAddress" << endl;
			e = mips_ExceptionInvalidAddress;
		}else{
			mips_mem_read(
				state->mem,		//!< Handle to target memory
				(Register1+ImConstant),//!< Byte address to start transaction at
				2,	//!< Number of bytes to transfer
				TwoByte	//!< Receives the target bytes
			);
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			Register2 = uint32_t (TwoByte[0] << 8) | uint32_t(TwoByte[1] << 0);
			//Register2 = uint32_t (TwoByte[1] << 0);
			Register2 = Register2 & 0x0000ffff;
			cout << "Register2 is  "<< Register2 << endl;
			if((Register2 & 0x8000) == 0x8000){
				Register2 = Register2 | 0xFFFF0000;
			}
			cout << "Register2 is  "<< Register2 << endl;
			state -> reg[source2] = Register2;
			e = mips_Success;
		}
	}else if(opcode == 37){
		//If either of the one least-significant
		//bits of the address are non-zero, an Address Error exception occurs.
		if(((Register1+ImConstant) & 0x1) != 0){
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			cout << "ExceptionInvalidAddress" << endl;
			e = mips_ExceptionInvalidAddress;
		}else{
			mips_mem_read(
				state->mem,		//!< Handle to target memory
				(Register1+ImConstant),//!< Byte address to start transaction at
				2,	//!< Number of bytes to transfer
				TwoByte	//!< Receives the target bytes
			);
			Register2 = uint32_t (TwoByte[0] << 8) | uint32_t(TwoByte[1] << 0);
			Register2 = Register2 & 0x0000ffff;
			state -> reg[source2] = Register2;
			e = mips_Success;
		}
	}else if(opcode == 15){
		Register2 = ImConstant << 16;
		Register2 = Register2 & 0xFFFF0000;
		state -> reg[source2] = Register2;
	}else if(opcode == 34){
		//If either of the one least-significant
		//bits of the address are non-zero, an Address Error exception occurs.
		if(((Register1+ImConstant) & 0x1) != 0){
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			cout << "ExceptionInvalidAddress" << endl;
			e = mips_ExceptionInvalidAddress;
		}else{
			mips_mem_read(
				state->mem,		//!< Handle to target memory
				(Register1+ImConstant),//!< Byte address to start transaction at
				4,	//!< Number of bytes to transfer
				Byte	//!< Receives the target bytes
			);
			cout << "Register2 is  "<< Register2 << endl;
			uint32_t Upper =  uint32_t(Byte[0]);
			if(Upper != 0xCD){
				cout << "upper is not equal" << endl<<endl;
				cout << "upper is" << Upper << endl;
			}
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			Register2 = uint32_t (Byte[0] << 24) | uint32_t(Byte[1] << 16)| (Register2 & 0x0000ffff << 0);
		
			cout << "Register2 is  "<< Register2 << endl;
			state -> reg[source2] = Register2;
			e = mips_Success;
		}
	}else if(opcode == 38){
		//If either of the one least-significant
		//bits of the address are non-zero, an Address Error exception occurs.
		if(((Register1+ImConstant+1) & 0x1) != 0){
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			cout << "ExceptionInvalidAddress" << endl;
			e = mips_ExceptionInvalidAddress;
		}else{
			mips_mem_read(
				state->mem,		//!< Handle to target memory
				(Register1+ImConstant+1-4),//!< Byte address to start transaction at
				4,	//!< Number of bytes to transfer
				Byte	//!< Receives the target bytes
			);
			cout << "Register2 is  "<< Register2 << endl;
			uint32_t Upper =  uint32_t(Byte[0]);
			if(Upper != 0xCD){
				cout << "upper is not equal" << endl<<endl;
				cout << "upper is" << Upper << endl;
			}
			cout << "Register1+ImConstant is  " << Register1+ImConstant <<endl;
			Register2 = uint32_t (Byte[2] << 8) | uint32_t(Byte[3] << 0)| (Register2 & 0xffff0000 << 0);
		
			cout << "Register2 is  "<< Register2 << endl;
			state -> reg[source2] = Register2;
			e = mips_Success;
		}
	}else if(opcode == 2){
		cout<< "Operation Jump Instruct" << endl;
		state->pc = state -> pcNext;
		state->pcNext = (state -> pc & 0xf0000000) | (Address << 2);
	}else if(opcode == 3){
		cout<< "Operation Jump Instruct" << endl;
		cout << "current pc is " << state -> pc <<endl<<endl<<endl;
		cout <<"teste"<< endl;
		state-> reg[31] = state -> pc + 8;
		state->pc = state -> pcNext;
		state->pcNext = (state -> pc & 0xf0000000) | (Address << 2);
	}
	return e;
}
	

	
void mips_cpu_free(mips_cpu_h state){
	free (state);
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	