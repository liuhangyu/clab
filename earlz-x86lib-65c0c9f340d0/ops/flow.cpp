/**
Copyright (c) 2007 - 2009 Jordan "Earlz/hckr83" Earls  <http://www.Earlz.biz.tm>
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
#include <x86Lib.h>
namespace x86Lib{
using namespace std;










void x86CPU::op16_jmp_rel8(){
	eip++;
	Jmp16_near8(op_cache[1]);
}

void x86CPU::op16_jmp_rel16(){
	eip+=2; //get to last byte of address so jmp works right
	Jmp16_near16(*(uint16_t*)&op_cache[1]);
}

void x86CPU::op16_jmp_imm16_imm16(){ //far jmp
	*(uint32_t*)&op_cache=ReadDword(cCS,eip+1);
	seg[cCS]=*(uint16_t*)&op_cache[2]; //I always forget that they are reversed...
	eip=*(uint16_t*)&op_cache[0];
	eip--; //eip will be incremented in Cycle
}

void x86CPU::op16_jmp_rm16(ModRM16 &rm){
	eip=rm.ReadWordr(); //absolute address...
	eip--;
}

void x86CPU::op16_jmp_m16_m16(ModRM16 &rm){
	*(uint32_t*)&op_cache=rm.ReadDword(stop); //quicker to use op_cache, than dynamic variables...
	CATCH;
	seg[cCS]=*(uint16_t*)&op_cache[2];
	eip=*(uint16_t*)&op_cache[0];
	eip--;
}



void x86CPU::op16_jcxz_rel8(){
	if(*regs16[CX]==0){
		Jmp16_near8(op_cache[1]);
	}
}






void x86CPU::op16_call_rel16(){

	Push16(eip+2);
	if(*(uint16_t*)&op_cache[1]<0x8000){
		//eip++;
	}
	eip+=2;
	Jmp16_near16(*(uint16_t*)&op_cache[1]);
}
void x86CPU::op16_retn(){
	eip=Pop16();
	//eip--; //because in Cycle, we increment..
}

void x86CPU::op16_loop_rel8(){
	(*regs16[CX])--;
	eip++;
	if(*regs16[CX]!=0){
		Jmp16_near8(op_cache[1]);
	}
}

void x86CPU::op16_loope_rel8(){
	(*regs16[CX])--;
	eip++;
	if((*regs16[CX]!=0) && (freg.zf==1)){
		Jmp16_near8(op_cache[1]);
	}
}

void x86CPU::op16_loopne_rel8(){
	(*regs16[CX])--;
	eip++;
	if((*regs16[CX]!=0) && (freg.zf==0)){
		Jmp16_near8(op_cache[1]);
	}
}


void x86CPU::op16_call_imm16_imm16(){ //far call
	Push16(seg[cCS]);
	Push16(eip+4);
	*(uint32_t*)&op_cache=ReadDword(cCS,eip+1);
	seg[cCS]=*(uint16_t*)&op_cache[2]; //I always forget that they are reversed...
	eip=*(uint16_t*)&op_cache[0];
	eip--; //eip will be incremented in Cycle
}

void x86CPU::op16_retf(){
	eip=Pop16();
	seg[cCS]=Pop16();
}

void x86CPU::op16_int_imm8(){
	eip++;
	Int16(op_cache[1]);
}

void x86CPU::op16_iret(){
	eip=Pop16();
	seg[cCS]=Pop16();
	*(uint16_t*)&freg=Pop16();
}

void x86CPU::op16_int3(){
	Int16(3);
}

void x86CPU::op16_into(){
	if(freg.of==1){
		Int16(4);
	}
}
void x86CPU::op16_call_rm16(ModRM16 &rm){ //far call
	Push16(eip+rm.GetLength()+1);
	eip=rm.ReadWordr();
	eip--; //eip will be incremented in Cycle
}

void x86CPU::op16_call_rm16_rm16(ModRM16 &rm){ //far call
	Push16(seg[cCS]);
	Push16(eip+rm.GetLength()+1);
	uint32_t tmp=rm.ReadDword(stop);
	CATCH;
	*(uint32_t*)&op_cache=ReadDword(DS,tmp);
	seg[cCS]=*(uint16_t*)&op_cache[2]; //I always forget that they are reversed...
	eip=*(uint16_t*)&op_cache[0];
	eip--; //eip will be incremented in Cycle
}



};


