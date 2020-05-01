/**
Copyright (c) 2007 - 2010 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This file is part of the x86Lib project.
**/

#ifndef X86LIB
#define X86LIB
#include <iostream>
#include <vector>
#include <stdint.h>
#include <string>

//! The main namespace of x86Lib
namespace x86Lib{

#ifdef X86LIB_BUILD
#include <config.h>
#endif

//!	8086 CPU level
static const uint32_t CPU086=1;
//!	186 CPU level
static const uint32_t CPU186=2|CPU086;
//!	286 real mode only CPU level
static const uint32_t CPU286_REAL=4|CPU186; //Only support real mode instructions
//!	286 CPU level
static const uint32_t CPU286=8|CPU286_REAL;
//!	386 real mode only CPU level
static const uint32_t CPU386_REAL=16|CPU286_REAL; //Only Support real mode instructions
//!	386 CPU level
static const uint32_t CPU386=32|CPU386_REAL|CPU286;
//!	486 CPU level
static const uint32_t CPU486=64|CPU386;
//!	Pentium(586) CPU level
static const uint32_t CPU_PENTIUM=128|CPU486;
//!	Pentium Pro CPU level
static const uint32_t CPU_PPRO=256|CPU_PENTIUM;
//!	Default CPU level
/*!	CPU_DEFAULT will use the CPU with the most complete emulation
*/
static const uint32_t CPU_DEFAULT=0; //this is actually changed internally..



#define CATCH if(stop.stop){ return; }


/**Exceptions...**/
//!	Exception code for an infinite halt
static const uint32_t CLIHLT_EXCP=1; //cli/hlt...nothing to do
//!	Exception code for memory access exception
static const uint32_t MEM_ACCESS_EXCP=3; //Memory Access Error...(can actually be page fault, or GPF, or stack fault...
//!	Exception code for triple fault
/*!	This code is always OR'd with another code
	so that you can tell what caused the triple fault.
*/
static const uint32_t TRIPLE_FAULT_EXCP=0x10000; //Triple fault...This should be ORd with the last exception

struct StopInfo
{
	bool stop;
	bool error;
	bool invalidOpcode;
	bool invalidMemory;
	bool interrupt;
	uint32_t code;
	int interruptNumber;
	uint32_t memoryAddress;
	std::string message;
};

//!	A debug exception
/*!	This exception should really only be used when debugging.
	It should be used as throw(Default_excp(__FILE__,__FUNCTION__,__LINE__));
*/
class Default_excp{ //Internal only...these should never happen when released...

	public:
	/*!
	\param file_ The file name in which the exception occured(use __FILE__)
	\param func_ The function in which the exception occured(use __FUNCTION__)
	\param line_ The line number which the excption occured on(use __LINE__)
	*/
	Default_excp(std::string file_,std::string func_,int line_){
		file=file_;
		func=func_;
		line=line_;
	}
	//! The file which the exception was thrown from
	std::string file;
	//! The function which the exception was thrown from
	std::string func;
	//! The line which the exception was thrown from
	int line;
};

//! CPU Panic exception
/*!	This exception is thrown out of x86CPU if a fatal CPU error occurs,
	such as a triple fault.
*/
class CpuPanic_excp{ //used for fatal CPU errors, such as triple fault..

	public:
	/*!
	\param desc_ A text description of the error
	\param code_ An exception code
	*/
	CpuPanic_excp(std::string desc_,uint32_t code_){
		desc=desc_;
		code=code_;
	}
	//!A text description of the error
	std::string desc;
	//!An exception code
	uint32_t code;
};

//!	Memory error exception
/*!	This should only be thrown out of the PhysMemory class
	It is thrown out to tell x86CPU a memory exception has occured.
	This does not always result in a triple fault.
	/sa PhysMemory
*/
class Mem_excp{ //Exclusively for the Memory Classes, these are caught and then a more appropriate excp is thrown
	public:
	/*!
	\param address_ The address at which had problems being read or written
	*/
	Mem_excp(uint32_t address_){
		address=address_;
	}
	uint32_t address;
};

class System_excp{
	public:
	System_excp(){}
};

class x86CPU;
/**This will be used for memory mapped devices(including memory itself)**/
class MemoryDevice{
	public:
	virtual void Read(uint32_t address,int count,void *buffer)=0;
	virtual void Write(uint32_t address,int count,void *data)=0;
	virtual int Readable(uint32_t address,int count){
		return 1;
		//This is optional. It is currently not used in the CPU code
	}
	virtual int Writeable(uint32_t address,int count){
		return 1;
		//This is optional. It is currently not used in the CPU code
	}
	virtual inline ~MemoryDevice()=0;
};

inline MemoryDevice::~MemoryDevice(){}


class PortDevice{
	public:
	virtual void Read(uint16_t address,int count,void *buffer)=0;
	virtual void Write(uint16_t address,int count,void *data)=0;
	virtual inline ~PortDevice()=0;
};

inline PortDevice::~PortDevice(){}

typedef struct DeviceRange
{
	union
	{
		class MemoryDevice *memdev;
		class PortDevice *portdev;
	};
	uint32_t high;
	uint32_t low;
}DeviceRange_t;
/*Myk I hate you. This is going to be harder to implement than I thought. lol */
class MemorySystem{
	std::vector<DeviceRange_t> memorySystemVector;
	protected:
	//! Intended to be used to mark if the address space is locked.
	volatile uint32_t locked; 
	public:
	MemorySystem();
	void Add(uint32_t low,uint32_t high,MemoryDevice *memdev);
	void Remove(uint32_t low,uint32_t high);
	void Remove(MemoryDevice *memdev);
	int RangeFree(uint32_t low,uint32_t high);
	void Read(uint32_t address,int count,void *buffer);
	void Write(uint32_t address,int count,void *data);
	//! Tells if memory is locked
	/*!
	\return 1 if memory is locked, 0 if not locked.
	*/
	bool IsLocked(){return locked;}
	//!	Locks the address space
	void Lock(){
		while(locked==1){}
		locked=1;
	}
	//! Unlocks the address space
	void Unlock(){
		locked=0;
	}
	void WaitLock(int haslock){
		if(haslock==0){
			while(locked>0){}
		}
	}
};

class PortSystem{
	DeviceRange_t *list;
	int count;
	public:
	PortSystem();

	void Add(uint16_t low,uint16_t high,PortDevice *portdev);
	void Remove(uint16_t low,uint16_t high);
	void Remove(PortDevice *portdev);
	int RangeFree(uint32_t low,uint32_t high);
	void Read(uint16_t address,int count,void *buffer);
	void Write(uint16_t address,int count,void *data);
};



//! The struct used to save the current state of x86CPU
struct x86SaveData{
	//! General registers
	uint32_t reg32[8];
	//! Segment registers
	uint16_t seg[7];
	//! Segment register routing(in case of segment overrides)
	uint8_t seg_route[7];
	//! Instruction pointer
	uint32_t eip;
	//! Which opcode map is currently in use
	uint32_t opcode_mode;
	//! Flags register
	uint16_t freg;
	//! CPU level
	uint32_t cpu_level;
};

};

#ifdef X86LIB_BUILD

#include <x86Lib_internal.h>
#endif



namespace x86Lib{

typedef void (x86Lib::x86CPU::*opcode)();
typedef struct{
     unsigned char rm:3;
     unsigned char extra:3;
     unsigned char mod:2;
}
__attribute__((packed))mod_rm16; //this struct is a described mod r/m byte..

//Note, this will re-cache op_cache, so do not use op_cache afterward
//Also, eip should be on the modrm byte!
//On return, it is on the last byte of the modrm block, so no advancement needed unelss there is an immediate
//Also, this will advance EIP upon exiting the opcode(deconstruction)
class ModRM16{ //This is the best thing I have ever done...
	//I love this class so much...am I cheating on her? lol
	protected:
	bool use_ss;
	bool op_specific;
	x86CPU *this_cpu;
	private:
	mod_rm16 modrm;
	inline uint16_t GetRegD(); //This returns the register displacement value
	inline uint16_t GetDisp();
	public:

	inline ModRM16(x86CPU* this_cpu_);
	inline ~ModRM16();
	//The r suffix means /r, which means for op_specific=1, use general registers
	inline uint8_t ReadByter();
	inline uint16_t ReadWordr();
	inline uint32_t ReadDword(StopInfo& stop);
	inline void WriteByter(uint8_t byte);
	inline void WriteWordr(uint16_t word);
	inline void WriteDword(uint32_t dword, StopInfo& stop);
	inline uint8_t GetLength(); //This returns how many total bytes the modrm block consumes
	inline uint8_t GetExtra(); //Get the extra fied from mod_rm
	inline uint16_t ReadOffset(StopInfo &stop); //This is only used by LEA. It will obtain the offset and not dereference it...

}; //I hope that SIB and ModR/M32 will be this good!
//!	The main CPU control class
/*!	This class is the complete CPU. That being said, it is quite big
	and has many functions. It completely emulates the x86 line of CPUs
*/
class x86CPU{
	friend class ModRM16;
	StopInfo stop;
	volatile uint32_t reg32[8];
	volatile uint16_t *regs16[8];
	volatile uint8_t *regs8[8];
	volatile uint16_t seg[7];
	volatile uint32_t eip;
	#ifdef X86LIB_BUILD
	volatile FLAGS freg;
	#else
	volatile uint16_t freg;
	#endif
	volatile uint8_t op_cache[4];
	volatile uint8_t ES;
	volatile uint8_t CS;
	volatile uint8_t SS;
	volatile uint8_t DS;
	volatile uint8_t FS;
	volatile uint8_t GS;
	volatile bool string_compares;
	volatile uint8_t cli_count; //Whenever this is 1, an STI is done.
	volatile bool int_pending;
	volatile uint8_t int_number;
	uint32_t cpu_level;
	volatile bool busmaster;
	void Init();
	protected:
	//! Do one CPU opcode
	/*! This should be put in the main loop, as this is what makes the CPU work.
	*/
	void Cycle();
	opcode opcodes_16bit[256];
	opcode *Opcodes;
	
	/*!
	\return 0 if no interrupts are pending
	 */
	int CheckInterrupts();
	public:
#ifdef ENABLE_OPCODE_CALLBACK
	void (*EachOpcodeCallback)(x86CPU *thiscpu);
#endif
	MemorySystem *Memory;
	PortSystem *Ports;
	/*!
	\param cpu_level The CPU level to use(default argument is default level)
	\param flags special flags to control CPU (currently, there is none)
	*/
	x86CPU(uint32_t cpu_level=0 ,uint32_t flags=0);
	/*!
	\param save The x86SaveData class to restore the cpu to
	\param flags special flags to control CPU (currently, there is none)
	*/
	x86CPU(x86SaveData &save,uint32_t flags=0);

	//!Runs the CPU for the specified cyclecount.
	StopInfo *Exec(int cyclecount);
	
	//! Dump CPU state
	/*! This will dump cpu state to output. This is mainly used for debugging, as it is not flexible.
	\param output output stream which to use.
	*/
	void DumpState(std::ostream &output);
	//! Cause a CPU interrupt
	/*! This will cause a CPU interrupt(unless interrupt flag is cleared)
		Note! This does not resolve IRQs! This takes normal interrupt numbers(0-255)
	\param num Interrupt number
	*/
	void Int(uint8_t num);
	//! Saves CPU state
	/*! This will completely save the CPU state of the current x86CPU class
	\param save_data_buffer This should be a free memory area the size of x86SaveData
	*/
	void SaveState(x86SaveData *save_data_buffer);
	//!Loads CPU state
	/*! This will completely reset and reload the cpu state.
	\param load_data where the x86SaveData is located
	*/
	void LoadState(x86SaveData &load_data);

	//!Completely resets the CPU
	void Reset();
	//~x86CPU();
	//!Locks the PhysMemory in use, and declares this CPU as busmaster
	void Lock();
	//!Unlocks the PhysMemory in use
	void Unlock();
	//! Tells if PhysMemory in use is locked
	/*!
	\return 1 if PhysMemory in use is locked, otherwise returns 0
	*/
	bool IsLocked();
	/*Added after inital multi-branch switch over*/
	//!Checks if an interrupt is on the stack waiting to be answered.
	/*!
	\return 1 if an interrupt is waiting to be answered by the CPU, else, 0.
	*/
	bool IntPending();
	
	/*End public interface*/
	#ifdef X86LIB_BUILD
	private:
	#include <opcode_def.h>
	#endif

};



#ifdef X86LIB_BUILD
#define X86_POST_CPU
#include <x86Lib_internal.h>
#undef X86_POST_CPU
#endif



















}


#endif

