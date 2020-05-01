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
#include <x86Lib.h>
namespace x86Lib{
using namespace std;






void x86CPU::op16_mov_r8_imm8(){ //0xB0+r
	//I suppose the first real instruction is the hardest...
	*regs8[op_cache[0]-0xB0]=op_cache[1];
	eip++;
}

void x86CPU::op16_mov_r16_imm16(){ //0xB8+r
	*regs16[op_cache[0]-0xB8]=*(uint16_t*)&op_cache[1];
	eip+=2;
}

void x86CPU::op16_mov_sr_rm16(){ //0x8E
	eip++;
	ModRM16 rm16(this);
	if(rm16.GetExtra()==cSS){ //if a mov into SS, then disable interrupts for 1 instruction.
		cli_count=2;
		freg._if=0;
	}
	seg[rm16.GetExtra()]=rm16.ReadWordr();
}

void x86CPU::op16_mov_rm16_sr(){ //0x8C
	eip++;
	ModRM16 rm16(this);
	rm16.WriteWordr(seg[rm16.GetExtra()]);
}



void x86CPU::op16_mov_r16_rm16(){
	eip++;
	ModRM16 rm16(this);
	*regs16[rm16.GetExtra()]=rm16.ReadWordr();
}

void x86CPU::op16_mov_rm16_r16(){
	eip++;
	ModRM16 rm16(this);
	rm16.WriteWordr(*regs16[rm16.GetExtra()]);
}

void x86CPU::op16_mov_al_off8(){
	*regs8[AL]=ReadByte(DS,*(uint16_t*)&op_cache[1]);
	eip++;
	eip++;
}
void x86CPU::op16_mov_ax_off16(){
	*regs16[AX]=ReadWord(DS,*(uint16_t*)&op_cache[1]);
	eip++;
	eip++;
}

void x86CPU::op16_mov_rm8_r8(){
	eip++;
	ModRM16 rm(this);
	rm.WriteByter(*regs8[rm.GetExtra()]);
}

void x86CPU::op16_mov_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	*regs8[rm.GetExtra()]=rm.ReadByter();
}
void x86CPU::op16_mov_off8_al(){
	WriteByte(DS,*(uint16_t*)&op_cache[1],*regs8[AL]);
	eip++;
	eip++;
}

void x86CPU::op16_mov_off16_ax(){
	WriteWord(DS,*(uint16_t*)&op_cache[1],*regs16[AX]);
	eip++;eip++;
}

void x86CPU::op16_mov_m8_imm8(){
	eip++;
	ModRM16 rm(this);
	
	//eventually fix this so that if r is used, then invalid opcode...
	rm.WriteByter(ReadByte(cCS,eip+rm.GetLength()));
	eip++;
}

void x86CPU::op16_mov_m16_imm16(){
	eip++;
	ModRM16 rm(this);
	rm.WriteWordr(ReadWord(cCS,eip+rm.GetLength()));
	eip++;
	eip++;
}

void x86CPU::op16_lds(){
	eip++;
	ModRM16 rm(this);
	uint32_t tmp=rm.ReadDword(stop);
	CATCH;
	seg[cDS]=(tmp&0xFFFF0000)>>16;
	*regs16[rm.GetExtra()]=(tmp&0xFFFF);
}

void x86CPU::op16_les(){
	eip++;
	ModRM16 rm(this);
	uint32_t tmp=rm.ReadDword(stop);
	CATCH;
	seg[cES]=(tmp&0xFFFF0000)>>16;
	*regs16[rm.GetExtra()]=(tmp&0xFFFF);
}

void x86CPU::op16_lea(){ //wtf is the point of this instruction! why not just mov reg,immediate! seriously frikkin crazy designers of x86
	eip++;
	ModRM16 rm(this);
	uint16_t tmp=rm.ReadOffset(stop);
	CATCH;
	*regs16[rm.GetExtra()]=tmp;
}



void x86CPU::op16_push_imm8(){
	eip++;
	Push16(op_cache[1]);
}
void x86CPU::op16_push_m16(ModRM16 &rm){
	Push16(rm.ReadWordr());
}

void x86CPU::op16_push_imm16(){ //0x68
	eip++;
	Push16(*(uint16_t*)&op_cache[1]);
	eip++;
}


void x86CPU::op16_push_r16(){ //0x50+reg
	Push16(*regs16[op_cache[0]-0x50]);
}

void x86CPU::op16_push_es(){
	Push16(seg[ES]);
}

void x86CPU::op16_push_cs(){
	Push16(seg[CS]);
}

void x86CPU::op16_push_ds(){
	Push16(seg[DS]);
}


void x86CPU::op16_push_ss(){
	Push16(seg[SS]);
}



void x86CPU::op16_pop_m16(ModRM16 &rm){
	rm.WriteWordr(Pop16());
}

void x86CPU::op16_pop_r16(){ //0x58+reg
	*regs16[op_cache[0]-0x58]=Pop16();
}


void x86CPU::op16_pop_es(){
	seg[ES]=Pop16();
}

void x86CPU::op16_pop_ss(){
	cli_count=2;
	freg._if=0;
	seg[SS]=Pop16();
}

void x86CPU::op16_pop_ds(){
	seg[DS]=Pop16();
}



void x86CPU::op16_out_imm8_al(){
	Ports->Write(op_cache[1],1,(void*)regs8[AL]);
	eip++;
}

void x86CPU::op16_out_imm8_ax(){
	Ports->Write(op_cache[1],2,(void*)regs16[AX]);
	eip++;
}

void x86CPU::op16_out_dx_al(){
	Ports->Write(*regs16[DX],1,(void*)regs8[AL]);
}

void x86CPU::op16_out_dx_ax(){
	Ports->Write(*regs16[DX],2,(void*)regs16[AX]);
}


void x86CPU::op16_in_al_imm8(){
	Ports->Read(op_cache[1],1,(void*)regs8[AL]);
	eip++;
}

void x86CPU::op16_in_ax_imm8(){
	Ports->Read(op_cache[1],2,(void*)regs16[AX]);
	eip++;
}

void x86CPU::op16_in_al_dx(){
	Ports->Read(*regs16[DX],1,(void*)regs8[AL]);
}

void x86CPU::op16_in_ax_dx(){
	Ports->Read(*regs16[DX],2,(void*)regs16[AX]);
}



void x86CPU::op16_xchg_rm8_r8(){
	#ifndef X86_MULTITHREADING
	if(IsLocked()==1){
		eip--;
		return;
	}
	#endif
	Lock();
	eip++;
	ModRM16 rm(this);
	uint8_t tmp=*regs8[rm.GetExtra()];
	*regs8[rm.GetExtra()]=rm.ReadByter();
	rm.WriteByter(tmp);
	Unlock();
}
void x86CPU::op16_xchg_rm16_r16(){
	#ifndef X86_MULTITHREADING
	if(IsLocked()==1){
		eip--;
		return;
	}
	#endif
	Lock();
	eip++;
	ModRM16 rm(this);
	uint16_t tmp=*regs16[rm.GetExtra()];
	*regs16[rm.GetExtra()]=rm.ReadWordr();
	rm.WriteWordr(tmp);
	Unlock();
}

void x86CPU::op16_xchg_ax_r16(){ //0x90+r
	uint16_t tmp=*regs16[AX];
	*regs16[AX]=*regs16[op_cache[0]-0x90];
	*regs16[op_cache[0]-0x90]=tmp;
}


void x86CPU::op16_xlatb(){
	*regs8[AL]=ReadByte(DS,(*regs16[BX])+(*regs8[AL]));
}






};



