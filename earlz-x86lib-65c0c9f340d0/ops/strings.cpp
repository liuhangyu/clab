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



void x86CPU::op16_movsb(){
	WriteByte(cES,*regs16[DI],ReadByte(DS,*regs16[SI]));
	SetIndex8();
}

void x86CPU::op16_movsw(){
	WriteWord(cES,*regs16[DI],ReadWord(DS,*regs16[SI]));
	SetIndex16();
}

void x86CPU::op16_cmpsb(){
	string_compares=1;
	Sub8(ReadByte(DS,*regs16[SI]),ReadByte(cES,*regs16[DI]));
	SetIndex8();
}

void x86CPU::op16_cmpsw(){
	string_compares=1;
	Sub16(ReadWord(DS,*regs16[SI]),ReadWord(cES,*regs16[DI]));
	SetIndex16();
}

void x86CPU::op16_lodsb(){
	*regs8[AL]=ReadByte(DS,*regs16[SI]);
	SetIndex8();
}
void x86CPU::op16_lodsw(){
	*regs16[AX]=ReadWord(DS,*regs16[SI]);
	SetIndex16();
}

void x86CPU::op16_scasb(){
	string_compares=1;
	Sub8(*regs8[AL],ReadByte(cES,*regs16[DI]));
	SetIndex8();
}
void x86CPU::op16_scasw(){
	string_compares=1;
	Sub16(*regs16[AX],ReadWord(cES,*regs16[DI]));
	SetIndex16();
}
void x86CPU::op16_stosb(){
	WriteByte(ES,*regs16[DI],*regs8[AL]);
	SetIndex8();
}
void x86CPU::op16_stosw(){
	WriteWord(ES,*regs16[DI],*regs16[AX]);
	SetIndex16();
}



};



