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




// TODO (Jordan#4#): Get AF stuff working in this!!
uint8_t x86CPU::Sub8(uint8_t base,uint8_t subt){
    int8_t result;
    if(subt>base){freg.cf=1;}else{freg.cf=0;}
    if((int16_t)base-subt>127 || (int16_t)base-subt<-127){
            freg.of=1;
        }else{
            freg.of=0;
        }
    result=base-subt;
    if(result==0){freg.zf=1;}else{freg.zf=0;}
    CalculatePF8(result); //do pf
    CalculateSF8(result); //do sf
	base&=0xF;
	subt&=0xF; 
    freg.af = (((base-subt) & ~0xf) != 0); //thank you http://stackoverflow.com/questions/4513746/explain-how-the-af-flag-works-in-an-x86-instructions
    return result;
}

uint16_t x86CPU::Sub16(uint16_t base,uint16_t subt){
    int16_t result;
    uint16_t mirror;
    if(subt>base){freg.cf=1;}else{freg.cf=0;}
    if((int32_t)base-subt>32767 || (int32_t)base-subt<-32767){
            freg.of=1;
        }else{
            freg.of=0;
        }
    mirror=base-subt;
    result=mirror;
    if(result==0){freg.zf=1;}else{freg.zf=0;}
    CalculatePF16(result); //do pf
    CalculateSF16(result); //do sf
	base&=0xF;
	subt&=0xF; 
    freg.af = (((base-subt) & ~0xf) != 0); 
    return mirror;
}

uint8_t x86CPU::Add8(uint8_t base,uint8_t adder){
    int8_t result;
    if(adder+base>255){freg.cf=1;}else{freg.cf=0;}
    if((int16_t)base+adder>127 || (int16_t)base+adder<-127){
            freg.of=1;
        }else{
            freg.of=0;
        }
    result=base+adder;
    if(result==0){freg.zf=1;}else{freg.zf=0;}
    CalculatePF8(result); //do pf
    CalculateSF8(result); //do sf
	base&=0x0F;
	adder&=0x0F;
    freg.af = ((int16_t)base+adder > 15);
    return result;
}

uint16_t x86CPU::Add16(uint16_t base,uint16_t adder){
    int16_t result;
    if((uint32_t)adder+base>(uint32_t)65535){freg.cf=1;}else{freg.cf=0;}
    if((int32_t)base+adder>32767 || (int32_t)base+adder<-32767){
            freg.of=1;
        }else{
            freg.of=0;
        }
    result=base+adder;
    if(result==0){freg.zf=1;}else{freg.zf=0;}
    CalculatePF16(result); //do pf
    CalculateSF16(result); //do sf
	base&=0x0F;
	adder&=0x0F;
    freg.af = ((int16_t)base+adder > 15);
    return result;
}




uint8_t x86CPU::And8(uint8_t base,uint8_t mask){
	freg.of=0;
	freg.cf=0;
	base=base&mask;
	CalculatePF8(base);
	CalculateSF8(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

uint16_t x86CPU::And16(uint16_t base,uint16_t mask){
	freg.of=0;
	freg.cf=0;
	base=base&mask;
	CalculatePF16(base);
	CalculateSF16(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

//Not affects no flags, so just use ~


uint8_t x86CPU::Or8(uint8_t base,uint8_t mask){
	freg.of=0;
	freg.cf=0;
	base=base|mask;
	CalculatePF8(base);
	CalculateSF8(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

uint16_t x86CPU::Or16(uint16_t base,uint16_t mask){
	freg.of=0;
	freg.cf=0;
	base=base|mask;
	CalculatePF16(base);
	CalculateSF16(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

uint8_t x86CPU::Xor8(uint8_t base,uint8_t mask){
	freg.of=0;
	freg.cf=0;
	base=base^mask;
	CalculatePF8(base);
	CalculateSF8(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

uint16_t x86CPU::Xor16(uint16_t base,uint16_t mask){
	freg.of=0;
	freg.cf=0;
	base=base^mask;
	CalculatePF16(base);
	CalculateSF16(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

uint8_t x86CPU::ShiftLogicalRight8(uint8_t base,uint8_t count){
	count&=0x1F; //only use bottom 5 bits
	if(count==0){
		CalculatePF8(base);
		CalculateSF8(base);
		freg.zf=1;
		return base;
	}
	freg.of=(base&0x80)>>7;
	freg.cf=(base>>(count-1))&1;
	base=base>>count;
	freg.of=freg.of^((base&0x80)>>7); //if the sign bit changed, then set it to 1
	CalculatePF8(base);
	CalculateSF8(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	freg.of=0;
	return base;
}

uint16_t x86CPU::ShiftLogicalRight16(uint16_t base,uint8_t count){
	count&=0x1F; //only use bottom 5 bits
	if(count==0){
		CalculatePF16(base);
		CalculateSF16(base);
		freg.zf=1;
		return base;
	}
	freg.of=(base&0x8000)>>15;
	freg.cf=(base>>(count-1))&1;
	base=base>>count;
	freg.of=freg.of^((base&0x8000)>>15); //if the sign bit changed, then set it to 1
	CalculatePF16(base);
	CalculateSF16(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	freg.of=0;
	return base;
}
uint8_t x86CPU::ShiftArithmeticRight8(uint8_t base,uint8_t count){
	count&=0x1F; //only use bottom 5 bits
	if(count==0){
		CalculatePF8(base);
		CalculateSF8(base);
		freg.zf=1;
		return base;
	}
	freg.cf=(base>>(count-1))&1;
	if((base&0x80)!=0){
		base=(base>>count)|(~(0xFF>>count)); //this replaces displaced zero bits with the sign bit
	}else{
		base=(base>>count);
	}
	freg.of=0;
	CalculatePF8(base);
	CalculateSF8(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	freg.of=0;
	return base;
}
uint16_t x86CPU::ShiftArithmeticRight16(uint16_t base,uint8_t count){
	count&=0x1F; //only use bottom 5 bits
	if(count==0){
		CalculatePF16(base);
		CalculateSF16(base);
		freg.zf=1;
		return base;
	}
	freg.cf=(base>>(count-1))&1;
	if((base&0x8000)!=0){
		base=(base>>count)|(~(0xFFFF>>count)); //this replaces displaced zero bits with the sign bit
	}else{
		base=(base>>count);
	}
	freg.of=0;
	CalculatePF16(base);
	CalculateSF16(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	freg.of=0;
	return base;
}

uint8_t x86CPU::ShiftLogicalLeft8(uint8_t base,uint8_t count){
	count&=0x1F; //only use bottom 5 bits
	if(count==0){
		CalculatePF8(base);
		CalculateSF8(base);
		freg.zf=1;
		return base;
	}
	freg.of=(base&0x80)>>7;
	freg.cf=((base<<(count-1))&0x80)>>7;
	base=base<<count;
	freg.of=freg.of^((base&0x80)>>7); //if the sign bit changed, then set it to 1
	CalculatePF8(base);
	CalculateSF8(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	freg.of=0;
	return base;
}

uint16_t x86CPU::ShiftLogicalLeft16(uint16_t base,uint8_t count){
	count&=0x1F; //only use bottom 5 bits
	if(count==0){
		CalculatePF16(base);
		CalculateSF16(base);
		freg.zf=1;
		return base;
	}
	freg.of=(base&0x8000)>>15;
	freg.cf=((base<<(count-1))&0x8000)>>15;
	base=base<<count;
	freg.of=freg.of^((base&0x8000)>>15); //if the sign bit changed, then set it to 1
	CalculatePF16(base);
	CalculateSF16(base);
	if(base==0){
		freg.zf=1;
	}else{
		freg.zf=0;
	}
	return base;
}

/**ToDo: Possibly adapt BOCHS source so that we avoid this loop crap...**/
uint8_t x86CPU::RotateRight8(uint8_t base,uint8_t count){
	freg.of=(base&0x80)>>7;
	while(count>0){
		freg.cf=(base&0x01);
		base=(freg.cf<<7)|(base>>1);
		count--;
	}
	freg.of=freg.of^((base&0x80)>>7);
	return base;
}

uint16_t x86CPU::RotateRight16(uint16_t base,uint8_t count){
	freg.of=(base&0x8000)>>15;
	while(count>0){
		freg.cf=(base&0x01);
		base=(freg.cf<<15)|(base>>1);
		count--;
	}
	freg.of=freg.of^((base&0x80)>>15);
	return base;
}

uint8_t x86CPU::RotateLeft8(uint8_t base,uint8_t count){
	freg.of=(base&0x80)>>7;
	while(count>0){
		freg.cf=(base&0x80)>>7;
		base=(freg.cf)|(base<<1);
		count--;
	}
	freg.of=freg.of^((base&0x80)>>7);
	return base;
}

uint16_t x86CPU::RotateLeft16(uint16_t base,uint8_t count){
	freg.of=(base&0x8000)>>15;
	while(count>0){
		freg.cf=(base&0x8000)>>15;
		base=(freg.cf)|(base<<1);
		count--;
	}
	freg.of=freg.of^((base&0x8000)>>15);
	return base;
}

uint8_t x86CPU::RotateCarryLeft8(uint8_t base,uint8_t count){
   freg.of=(base&0x80)>>7;
   while(count>0){
      freg.r0=freg.cf; //reserved bit as a temp variable...
      freg.cf=(base&0x80)>>7;
      base=(base<<1);
      base|=freg.r0; //puts (old)CF in it's place
      count--;
   }
   freg.of=freg.of^((base&0x80)>>7);
   return base;
}

uint16_t x86CPU::RotateCarryLeft16(uint16_t base,uint8_t count){
	freg.of=(base&0x8000)>>15;
	while(count>0){
		freg.r0=freg.cf; //reserved bit as a temp variable...
		freg.cf=(base&0x8000)>>15;
		base=(base<<1);
		base=(base&0xFFFE)|freg.r0; //zeros the 0 bit and puts (old)CF in it's place
		count--;
	}
	freg.of=freg.of^((base&0x8000)>>15);
	return base;
}

uint8_t x86CPU::RotateCarryRight8(uint8_t base,uint8_t count){
	freg.of=(base&0x80)>>7;
	while(count>0){
		freg.r0=freg.cf;
		freg.cf=(base&0x01);
		base=(freg.r0<<7)|(base>>1);
		count--;
	}
	freg.of=freg.of^((base&0x80)>>7);
	return base;
}

uint16_t x86CPU::RotateCarryRight16(uint16_t base,uint8_t count){
	freg.of=(base&0x8000)>>15;
	while(count>0){
		freg.r0=freg.cf;
		freg.cf=(base&0x01);
		base=(freg.r0<<15)|(base>>1);
		count--;
	}
	freg.of=freg.of^((base&0x8000)>>15);
	return base;
}









void x86CPU::op16_sub_al_imm8(){ //0x2C
	*regs8[AL]=Sub8(*regs8[AL],op_cache[1]);
	eip++;
}

void x86CPU::op16_sub_ax_imm16(){ //0x2D..yay! 2D and not 3!
	*regs16[AX]=Sub16(*regs16[AX],*(uint16_t*)&op_cache[1]);
	eip+=2;
}

void x86CPU::op16_sub_rm8_r8(){
	eip++;
	ModRM16 rm8(this);
	rm8.WriteByter(Sub8(rm8.ReadByter(),*regs8[rm8.GetExtra()]));
	//finally learning the power of deconstructors!
}

void x86CPU::op16_sub_rm16_r16(){
	eip++;
	ModRM16 rm16(this);
	rm16.WriteWordr(Sub16(rm16.ReadWordr(),*regs16[rm16.GetExtra()]));
}
void x86CPU::op16_sub_r8_rm8(){
	eip++;
	ModRM16 rm8(this);
	*regs8[rm8.GetExtra()]=Sub8(*regs8[rm8.GetExtra()],rm8.ReadByter());
}

void x86CPU::op16_sub_r16_rm16(){
	eip++;
	ModRM16 rm16(this);
	*regs16[rm16.GetExtra()]=Sub16(*regs16[rm16.GetExtra()],rm16.ReadWordr());
}

void x86CPU::op16_sub_rm8_imm8(ModRM16 &rm8){ //group 0x80 /5
	rm8.WriteByter(Sub8(rm8.ReadByter(),ReadByte(cCS,eip+rm8.GetLength())));
}

void x86CPU::op16_sub_rm16_imm16(ModRM16 &rm){ //Group 0x81 /5
	rm.WriteWordr(Sub16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_sub_rm16_imm8(ModRM16 &rm){ //group 0x83 /5
	rm.WriteWordr(Sub16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength()))));
}

/****/
void x86CPU::op16_sbb_al_imm8(){
	*regs8[AL]=Sub8(*regs8[AL],op_cache[1]-freg.cf);
	eip++;
}

void x86CPU::op16_sbb_ax_imm16(){
	*regs16[AX]=Sub16(*regs16[AX],*(uint16_t*)&op_cache[1]-freg.cf);
	eip++;
	eip++;
}

void x86CPU::op16_sbb_rm8_r8(){
	eip++;
	ModRM16 rm8(this);
	rm8.WriteByter(Sub8(rm8.ReadByter(),*regs8[rm8.GetExtra()]-freg.cf));
}

void x86CPU::op16_sbb_rm16_r16(){
	eip++;
	ModRM16 rm16(this);
	rm16.WriteWordr(Sub16(rm16.ReadWordr(),*regs16[rm16.GetExtra()]-freg.cf));
}
void x86CPU::op16_sbb_r8_rm8(){
	eip++;
	ModRM16 rm8(this);
	*regs8[rm8.GetExtra()]=Sub8(*regs8[rm8.GetExtra()],rm8.ReadByter()-freg.cf);
}

void x86CPU::op16_sbb_r16_rm16(){
	eip++;
	ModRM16 rm16(this);
	*regs16[rm16.GetExtra()]=Sub16(*regs16[rm16.GetExtra()],rm16.ReadWordr()-freg.cf);
}

void x86CPU::op16_sbb_rm8_imm8(ModRM16 &rm8){ //group 0x80
	rm8.WriteByter(Sub8(rm8.ReadByter(),ReadByte(cCS,eip+rm8.GetLength())-freg.cf));
}

void x86CPU::op16_sbb_rm16_imm16(ModRM16 &rm){ //Group 0x81
	rm.WriteWordr(Sub16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())-freg.cf));
}

void x86CPU::op16_sbb_rm16_imm8(ModRM16 &rm){ //group 0x83
	rm.WriteWordr(Sub16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength())-freg.cf)));
}


void x86CPU::op16_dec_r16(){ //0x48+r
	freg.r0=freg.cf;
	*regs16[(op_cache[0]-0x48)]=Sub16(*regs16[(op_cache[0]-0x48)],1);
	freg.cf=freg.r0;
}

void x86CPU::op16_dec_rm8(ModRM16& rm){
	freg.r0=freg.cf;
	rm.WriteByter(Sub8(rm.ReadByter(),1));
	freg.cf=freg.r0;
}

void x86CPU::op16_dec_rm16(ModRM16& rm){
	freg.r0=freg.cf;
	rm.WriteWordr(Sub16(rm.ReadWordr(),1));
	freg.cf=freg.r0;
}






//cmp and sub are so similar, that they are both going in here...
void x86CPU::op16_cmp_al_imm8(){
	Sub8(*regs8[AL],op_cache[1]);
	eip++;
}

void x86CPU::op16_cmp_ax_imm16(){
	Sub16(*regs16[AX],*(uint16_t*)&op_cache[1]);
	eip+=2;
}

void x86CPU::op16_cmp_rm8_r8(){
	eip++;
	ModRM16 rm(this);
	Sub8(rm.ReadByter(),*regs8[rm.GetExtra()]);
}

void x86CPU::op16_cmp_rm16_r16(){
	eip++;
	ModRM16 rm(this);
	Sub16(rm.ReadWordr(),*regs16[rm.GetExtra()]);
}

void x86CPU::op16_cmp_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	Sub8(*regs16[rm.GetExtra()],rm.ReadByter());
}

void x86CPU::op16_cmp_r16_rm16(){
	eip++;
	ModRM16 rm(this);
	Sub16(*regs16[rm.GetExtra()],rm.ReadWordr());
}

void x86CPU::op16_cmp_rm8_imm8(ModRM16 &rm){ //group 80 /7
	Sub8(rm.ReadByter(),ReadByte(cCS,eip+rm.GetLength()));
}

void x86CPU::op16_cmp_rm16_imm16(ModRM16 &rm){ //group 81 /7
	Sub16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength()));
}

void x86CPU::op16_cmp_rm16_imm8(ModRM16 &rm){ //group 83 /7
	Sub16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength())));
}






void x86CPU::op16_add_al_imm8(){
	*regs8[AL]=Add8(*regs8[AL],op_cache[1]);
	eip++;
}

void x86CPU::op16_add_ax_imm8(){
	*regs16[AX]=Add16(*regs16[AX],*(uint16_t*)&op_cache[1]);
	eip++;
	eip++;
}

void x86CPU::op16_add_rm8_r8(){
	eip++;
	ModRM16 rm8(this);
	rm8.WriteByter(Add8(rm8.ReadByter(),*regs8[rm8.GetExtra()]));
}

void x86CPU::op16_add_rm16_r16(){
	eip++;
	ModRM16 rm16(this);
	rm16.WriteWordr(Add16(rm16.ReadWordr(),*regs16[rm16.GetExtra()]));
}

void x86CPU::op16_add_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	*regs8[rm.GetExtra()]=Add8(*regs8[rm.GetExtra()],rm.ReadByter());
}

void x86CPU::op16_add_r16_rm16(){
	eip++;
	ModRM16 rm(this);
	*regs16[rm.GetExtra()]=Add16(*regs16[rm.GetExtra()],rm.ReadWordr());
}

void x86CPU::op16_add_rm8_imm8(ModRM16 &rm){ //Group 0x80 /0
	rm.WriteByter(Add8(rm.ReadWordr(),ReadByte(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_add_rm16_imm16(ModRM16 &rm){ //Group 0x81 /0
	rm.WriteWordr(Add16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_add_rm16_imm8(ModRM16 &rm){ //group 0x83 /0
	rm.WriteWordr(Add16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength()))));
}


/****/
void x86CPU::op16_adc_al_imm8(){
	*regs8[AL]=Add8(*regs8[AL],op_cache[1]+freg.cf);
	eip++;
}

void x86CPU::op16_adc_ax_imm8(){
	*regs16[AX]=Add16(*regs16[AX],*(uint16_t*)&op_cache[1]+freg.cf);
	eip++;
	eip++;
}

void x86CPU::op16_adc_rm8_r8(){
	eip++;
	ModRM16 rm8(this);
	rm8.WriteByter(Add8(rm8.ReadByter(),*regs8[rm8.GetExtra()]+freg.cf));
}

void x86CPU::op16_adc_rm16_r16(){
	eip++;
	ModRM16 rm16(this);
	rm16.WriteWordr(Add16(rm16.ReadWordr(),*regs16[rm16.GetExtra()]+freg.cf));
}

void x86CPU::op16_adc_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	*regs8[rm.GetExtra()]=Add8(*regs8[rm.GetExtra()],rm.ReadByter()+freg.cf);
}

void x86CPU::op16_adc_r16_rm16(){
	eip++;
	ModRM16 rm(this);
	*regs16[rm.GetExtra()]=Add16(*regs16[rm.GetExtra()],rm.ReadWordr()+freg.cf);
}

void x86CPU::op16_adc_rm8_imm8(ModRM16 &rm){ //Group 0x80 /2
	rm.WriteByter(Add8(rm.ReadWordr(),ReadByte(cCS,eip+rm.GetLength())+freg.cf));
}

void x86CPU::op16_adc_rm16_imm16(ModRM16 &rm){ //Group 0x81 /2
	rm.WriteWordr(Add16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())+freg.cf));
}

void x86CPU::op16_adc_rm16_imm8(ModRM16 &rm){ //group 0x83 /2
	rm.WriteWordr(Add16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength()))+freg.cf));
}



void x86CPU::op16_inc_r16(){ //0x40+r
	freg.r0=freg.cf;
	*regs16[(op_cache[0]-0x40)]=Add16(*regs16[(op_cache[0]-0x40)],1);
	freg.cf=freg.r0;
}

void x86CPU::op16_inc_rm8(ModRM16 &rm){
	freg.r0=freg.cf; //yay for reserved flags!
	rm.WriteByter(Add8(rm.ReadByter(),1));
	freg.cf=freg.r0;
}

void x86CPU::op16_inc_rm16(ModRM16 &rm){
	freg.r0=freg.cf;
	rm.WriteWordr(Add16(rm.ReadWordr(),1));
	freg.cf=freg.r0;
}

void x86CPU::op16_neg_rm8(ModRM16 &rm){
	uint8_t tmp=rm.ReadByter();
	if(tmp==0xFF){
		freg.of=1;
		return;
	}
	rm.WriteByter(Sub8(0,tmp));
	if(tmp==0){
		freg.cf=0;
	}else{
		freg.cf=1;
	}
}
void x86CPU::op16_neg_rm16(ModRM16 &rm){
	uint16_t tmp=rm.ReadWordr();
	if(tmp==0xFFFF){
		freg.of=1;
		return;
	}
	rm.WriteWordr(Sub16(0,tmp));
	if(tmp==0){
		freg.cf=0;
	}else{
		freg.cf=1;
	}
}



void x86CPU::op16_div_rm8(ModRM16 &rm){
	if(rm.ReadByter()==0){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;
	}
	if(((*regs16[AX])/rm.ReadByter())>0xFF){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}
	*regs8[AL]=(*regs16[AX])/rm.ReadByter();
	*regs8[AH]=(*regs16[AX])%rm.ReadByter();
}

void x86CPU::op16_div_rm16(ModRM16 &rm){
	if(rm.ReadWordr()==0){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}
	if((((*regs16[DX]<<16)|(*regs16[AX]))/rm.ReadWordr())>0xFFFF){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}
	*regs8[AX]=((*regs16[DX]<<16)|(*regs16[AX]))/rm.ReadWordr();
	*regs8[DX]=((*regs16[DX]<<16)|(*regs16[AX]))%rm.ReadWordr();
}


void x86CPU::op16_idiv_rm8(ModRM16 &rm){ //This WORKS! both signed, and unsigned!
	//grrr...who the crap does signed division anyway!?
	if(rm.ReadByter()==0){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}
	uint8_t tmp=rm.ReadByter();
	bool store1,store2;

	tmp=Unsign8(tmp,store1);
	*regs16[AX]=Unsign16(*regs16[AX],store2);
	if(((*regs16[AX])/tmp)>0xFF){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}

	*regs8[AL]=(*regs16[AX])/tmp;
	*regs8[AH]=(*regs16[AX])%tmp;

	*regs8[AL]=Resign8(*regs8[AL],store1^store2);
}

void x86CPU::op16_idiv_rm16(ModRM16 &rm){
	if(rm.ReadWordr()==0){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}
	uint16_t tmp=rm.ReadWordr();
	bool store1,store2;
	tmp=Unsign16(tmp,store1);
	static uint32_t tmp2=Unsign32(((*regs16[DX])<<16)|(*regs16[AX]),store2);

	if((tmp2/tmp)>0xFFFF){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;	
	}
	*regs16[AX]=tmp2/tmp;
	*regs16[DX]=tmp2%tmp;

	*regs16[AX]=Resign16(*regs16[AX],store1^store2);
}



void x86CPU::op16_mul_rm8(ModRM16 &rm){
    *regs16[AX]=(*regs8[AL])*rm.ReadByter();
    if((*regs8[AH])>0){ //if tophalf of result has anything in it
        freg.cf=1;
        freg.of=1;
    }else{
        freg.cf=0;
        freg.of=0;
    }
}


void x86CPU::op16_mul_rm16(ModRM16 &rm){
	uint32_t result;
    result=(*regs16[AX])*rm.ReadWordr();
    *regs16[AX]=result&0x0000FFFF;
    *regs16[DX]=(result&0xFFFF0000)>>16;
    if((*regs16[DX])>0){ //if tophalf of result has anything in it
        freg.cf=1;
        freg.of=1;
    }else{
        freg.cf=0;
        freg.of=0;
    }
}

void x86CPU::op16_imul_rm8(ModRM16 &rm){
	bool store1,store2;
	*regs16[AX]=Unsign8(*regs8[AL],store1)*Unsign8(rm.ReadByter(),store2);
	if(*regs8[AX]>0){
		freg.of=1;
		freg.cf=1;
	}else{
		freg.of=0;
		freg.cf=0;
	}
	*regs16[AX]=Resign16(*regs16[AX],store1^store2);
}

void x86CPU::op16_imul_rm16(ModRM16 &rm){
	bool store1,store2;
	uint32_t result=Unsign16(*regs16[AX],store1)*Unsign16(rm.ReadWordr(),store2);
	if((result&0xFFFF0000)>0){
		freg.of=1;
		freg.cf=1;
	}else{
		freg.of=0;
		freg.cf=0;
	}
	result=Resign32(result,store1^store2);
	*regs16[DX]=(result&0xFFFF0000)>>16;
	*regs16[AX]=(result&0xFFFF);
}



void x86CPU::op16_and_rm8_r8(){
	eip++;
	ModRM16 rm(this);
	rm.WriteByter(And8(rm.ReadByter(),*regs8[rm.GetExtra()]));
}

void x86CPU::op16_and_rm16_r16(){
	eip++;
	ModRM16 rm(this);
	rm.WriteWordr(And16(rm.ReadWordr(),*regs16[rm.GetExtra()]));
}

void x86CPU::op16_and_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	*regs8[rm.GetExtra()]=And8(*regs8[rm.GetExtra()],rm.ReadByter());
}

void x86CPU::op16_and_r16_rm16(){
	eip++;
	ModRM16 rm(this);
	*regs16[rm.GetExtra()]=And16(*regs16[rm.GetExtra()],rm.ReadWordr());
}

void x86CPU::op16_and_al_imm8(){
	eip++;
	*regs8[AL]=And8(*regs8[AL],op_cache[1]);
}

void x86CPU::op16_and_ax_imm16(){
	eip++;
	eip++;
	*regs16[AX]=And16(*regs16[AX],*(uint16_t*)&op_cache[1]);
}

void x86CPU::op16_and_rm8_imm8(ModRM16& rm){
	rm.WriteByter(And8(rm.ReadByter(),ReadByte(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_and_rm16_imm16(ModRM16& rm){
	rm.WriteWordr(And16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_and_rm16_imm8(ModRM16& rm){
	rm.WriteWordr(And16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength()))));
	//gotta love parentheses...
}

void x86CPU::op16_or_rm8_r8(){
	eip++;
	ModRM16 rm(this);
	rm.WriteByter(Or8(rm.ReadByter(),*regs8[rm.GetExtra()]));
}

void x86CPU::op16_or_rm16_r16(){
	eip++;
	ModRM16 rm(this);
	rm.WriteWordr(Or16(rm.ReadWordr(),*regs16[rm.GetExtra()]));
}

void x86CPU::op16_or_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	*regs8[rm.GetExtra()]=Or8(*regs8[rm.GetExtra()],rm.ReadByter());
}

void x86CPU::op16_or_r16_rm16(){
	eip++;
	ModRM16 rm(this);
	*regs16[rm.GetExtra()]=Or16(*regs16[rm.GetExtra()],rm.ReadWordr());
}

void x86CPU::op16_or_al_imm8(){
	eip++;
	*regs8[AL]=Or8(*regs8[AL],op_cache[1]);
}

void x86CPU::op16_or_ax_imm16(){
	eip++;
	eip++;
	*regs16[AX]=Or16(*regs16[AX],*(uint16_t*)&op_cache[1]);
}

void x86CPU::op16_or_rm8_imm8(ModRM16& rm){
	rm.WriteByter(Or8(rm.ReadByter(),ReadByte(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_or_rm16_imm16(ModRM16& rm){
	rm.WriteWordr(Or16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_or_rm16_imm8(ModRM16& rm){
	rm.WriteWordr(Or16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength()))));
	//gotta love parentheses...
}



void x86CPU::op16_xor_rm8_r8(){
	eip++;
	ModRM16 rm(this);
	rm.WriteByter(Xor8(rm.ReadByter(),*regs8[rm.GetExtra()]));
}

void x86CPU::op16_xor_rm16_r16(){
	eip++;
	ModRM16 rm(this);
	rm.WriteWordr(Xor16(rm.ReadWordr(),*regs16[rm.GetExtra()]));
}

void x86CPU::op16_xor_r8_rm8(){
	eip++;
	ModRM16 rm(this);
	*regs8[rm.GetExtra()]=Xor8(*regs8[rm.GetExtra()],rm.ReadByter());
}

void x86CPU::op16_xor_r16_rm16(){
	eip++;
	ModRM16 rm(this);
	*regs16[rm.GetExtra()]=Xor16(*regs16[rm.GetExtra()],rm.ReadWordr());
}

void x86CPU::op16_xor_al_imm8(){
	eip++;
	*regs8[AL]=Xor8(*regs8[AL],op_cache[1]);
}

void x86CPU::op16_xor_ax_imm16(){
	eip++;
	eip++;
	*regs16[AX]=Xor16(*regs16[AX],*(uint16_t*)&op_cache[1]);
}

void x86CPU::op16_xor_rm8_imm8(ModRM16& rm){
	rm.WriteByter(Xor8(rm.ReadByter(),ReadByte(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_xor_rm16_imm16(ModRM16& rm){
	rm.WriteWordr(Xor16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength())));
}

void x86CPU::op16_xor_rm16_imm8(ModRM16& rm){
	rm.WriteWordr(Xor16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength()))));
	//gotta love parentheses...
}

void x86CPU::op16_test_rm8_r8(){
	eip++;
	ModRM16 rm(this);
	And8(rm.ReadByter(),*regs8[rm.GetExtra()]);
}

void x86CPU::op16_test_rm16_r16(){
	eip++;
	ModRM16 rm(this);
	And16(rm.ReadWordr(),*regs16[rm.GetExtra()]);
}
void x86CPU::op16_test_al_imm8(){
	eip++;
	And8(*regs8[AL],op_cache[1]);
}
void x86CPU::op16_test_ax_imm16(){
	eip++;
	eip++;
	And16(*regs16[AX],*(uint16_t*)&op_cache[1]);
}

void x86CPU::op16_test_rm8_imm8(ModRM16& rm){
	And8(rm.ReadByter(),ReadByte(cCS,eip+rm.GetLength()));
}

void x86CPU::op16_test_rm16_imm16(ModRM16& rm){
	And16(rm.ReadWordr(),ReadWord(cCS,eip+rm.GetLength()));
}

void x86CPU::op16_test_rm16_imm8(ModRM16& rm){
	And16(rm.ReadWordr(),SignExtend8(ReadByte(cCS,eip+rm.GetLength())));
	//gotta love parentheses...
}


void x86CPU::op16_shr_rm8_cl(ModRM16 &rm){
	rm.WriteByter(ShiftLogicalRight8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_shr_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(ShiftLogicalRight16(rm.ReadWordr(),*regs8[CL]));
}

void x86CPU::op16_shl_rm8_cl(ModRM16 &rm){
	rm.WriteByter(ShiftLogicalLeft8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_shl_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(ShiftLogicalLeft16(rm.ReadWordr(),*regs8[CL]));
}

void x86CPU::op16_sar_rm8_cl(ModRM16 &rm){
	rm.WriteByter(ShiftArithmeticRight8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_sar_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(ShiftArithmeticRight16(rm.ReadWordr(),*regs8[CL]));
}

void x86CPU::op16_rol_rm8_cl(ModRM16 &rm){
	rm.WriteByter(RotateLeft8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_rol_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(RotateLeft16(rm.ReadWordr(),*regs8[CL]));
}

void x86CPU::op16_ror_rm8_cl(ModRM16 &rm){
	rm.WriteByter(RotateRight8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_ror_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(RotateRight16(rm.ReadWordr(),*regs8[CL]));
}


void x86CPU::op16_rcl_rm8_cl(ModRM16 &rm){
	rm.WriteByter(RotateCarryLeft8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_rcl_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(RotateCarryLeft16(rm.ReadWordr(),*regs8[CL]));
}

void x86CPU::op16_rcr_rm8_cl(ModRM16 &rm){
	rm.WriteByter(RotateCarryRight8(rm.ReadByter(),*regs8[CL]));
}
void x86CPU::op16_rcr_rm16_cl(ModRM16 &rm){
	rm.WriteWordr(RotateCarryRight16(rm.ReadWordr(),*regs8[CL]));
}


/****/
void x86CPU::op16_shr_rm8_1(ModRM16 &rm){
	rm.WriteByter(ShiftLogicalRight8(rm.ReadByter(),1));
}
void x86CPU::op16_shr_rm16_1(ModRM16 &rm){
	rm.WriteWordr(ShiftLogicalRight16(rm.ReadWordr(),1));
}

void x86CPU::op16_shl_rm8_1(ModRM16 &rm){
	rm.WriteByter(ShiftLogicalLeft8(rm.ReadByter(),1));
}
void x86CPU::op16_shl_rm16_1(ModRM16 &rm){
	rm.WriteWordr(ShiftLogicalLeft16(rm.ReadWordr(),1));
}

void x86CPU::op16_sar_rm8_1(ModRM16 &rm){
	rm.WriteByter(ShiftArithmeticRight8(rm.ReadByter(),1));
}
void x86CPU::op16_sar_rm16_1(ModRM16 &rm){
	rm.WriteWordr(ShiftArithmeticRight16(rm.ReadWordr(),1));
}

void x86CPU::op16_rol_rm8_1(ModRM16 &rm){
	rm.WriteByter(RotateLeft8(rm.ReadByter(),1));
}
void x86CPU::op16_rol_rm16_1(ModRM16 &rm){
	rm.WriteWordr(RotateLeft16(rm.ReadWordr(),1));
}

void x86CPU::op16_ror_rm8_1(ModRM16 &rm){
	rm.WriteByter(RotateRight8(rm.ReadByter(),1));
}
void x86CPU::op16_ror_rm16_1(ModRM16 &rm){
	rm.WriteWordr(RotateRight16(rm.ReadWordr(),1));
}


void x86CPU::op16_rcl_rm8_1(ModRM16 &rm){
	rm.WriteByter(RotateCarryLeft8(rm.ReadByter(),1));
}
void x86CPU::op16_rcl_rm16_1(ModRM16 &rm){
	rm.WriteWordr(RotateCarryLeft16(rm.ReadWordr(),1));
}

void x86CPU::op16_rcr_rm8_1(ModRM16 &rm){
	rm.WriteByter(RotateCarryRight8(rm.ReadByter(),1));
}
void x86CPU::op16_rcr_rm16_1(ModRM16 &rm){
	rm.WriteWordr(RotateCarryRight16(rm.ReadWordr(),1));
}

void x86CPU::op16_not_rm8(ModRM16 &rm){
	rm.WriteByter(~(rm.ReadByter()));
}

void x86CPU::op16_not_rm16(ModRM16 &rm){
	rm.WriteWordr(~(rm.ReadWordr()));
}




/**
BCD Opcodes for Open86
By: Alboin, 3-16-07
Modified to work with x86Lib by Jordan(hckr83)
**/


/* Opcode: 0x37 */
void x86CPU::op16_aaa() {
	if((*regs8[AL] & 0x0f) > 9 || freg.af == 1) {
		*regs8[AL] += 6;
		*regs8[AH]++;
		freg.af = 1;
		freg.cf = 1;
	}
	else {
		freg.af = 0;
		freg.cf = 0;
	}
	*regs8[AL] = *regs8[AL] & 0x0f;
}


/* Opcode: 0x27 */
void x86CPU::op16_daa() {
	if((*regs8[AL] & 0x0f) > 9 || freg.af == 1) {
		*regs8[AL] += 6;
		*regs8[AH]++;
	}
	else
		freg.af = 0;

	if(*regs8[AL] > 0x9f || freg.cf == 1) {
			*regs8[AL] = *regs8[AL] + 0x60;
			freg.cf = 1;
	}
	else
		freg.cf = 0;
}

/* Opcode: 0x2F */
void x86CPU::op16_das() {
	if((*regs8[AL] & 0x0f) > 9 || freg.af == 1) {
		*regs8[AL] -= 6;
		freg.af = 1;
	}
	else
		freg.af = 0;

	if(*regs8[AL] > 0x9f || freg.cf == 1) {
			*regs8[AL] -= 0x60;
			freg.cf = 1;
	}
	else
		freg.cf = 0;
}

/* Opcode: 0x3F */
void x86CPU::op16_aas() {
	if((*regs8[AL] & 0x0f) > 9 || freg.af == 1) {
		*regs8[AL] -= 6;
		*regs8[AH]--;
		freg.af = 1;
		freg.cf = 1;
	}
	else {
		freg.af = 0;
		freg.cf = 0;
	}
	*regs8[AL] = *regs8[AL] & 0x0f;
}



void x86CPU::op16_aad(){
	//AAD is a weird opcode because it is two bytes
	//for "apparently" no reason. But really, it is just
	//undocumented... the 0x0A in the second byte is for
	//multiplecation...but it can be changed...
	*regs8[AL]=(*regs8[AH])*(op_cache[1])+*regs8[AL];
	*regs8[AH]=0;
}

void x86CPU::op16_aam(){
	//same wiht the 0x0A operand as above..
	if(op_cache[1]==0){
		stop.stop=true;
		stop.error=true;
		stop.interrupt=true;
		stop.interruptNumber=DIV0_IEXCP;
		return;
	}
	*regs8[AH]=(*regs8[AL])/op_cache[1];
	*regs8[AL]=(*regs8[AL])%op_cache[1];
}










};



