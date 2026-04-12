#include "scmscript.h"

// This is the function address of ProccessOneCommand() function from GTA: Vice City
// That executes one scm function.
const FARPROC ProcessOneCommand = (FARPROC)0x44FBE0;

DWORD SCRIPT_BASE = 0x821280; // Memory location of Script
SCRIPT script; // Script structure which is 0x88 bytes long
uint8_t ScriptBuf[MAX_SCRIPT_SIZE];
DWORD ScriptVars[MAX_SCRIPT_VARIABLE];

int __declspec(naked) ExecuteScript()
{
	__asm
	{
		mov ecx, OFFSET ScriptBuf
		sub ecx, SCRIPT_BASE
		mov script.dwScriptIP, ecx

		mov ecx, OFFSET script
		call ProcessOneCommand
		xor eax, eax
		mov al, script.bJumpFlag
		ret
	}
}


int scmScript(const SCM_COMMAND* cmd, ...)
{
	va_list ap;
	const char* p = cmd->args;
	va_start(ap, cmd);
	memcpy(&ScriptBuf, &cmd->opcode, 2);
	int buf_pos = 2;
	int var_pos = 0;

	while (*p)
	{
		switch (*p)
		{
		case 'i':
		{
			long i = va_arg(ap, long);	
			if ((i >= -128) && (i <= 127))	// One byte
			{
				char ch = (char)i;		
				ScriptBuf[buf_pos] = 0x04;	// Variable data type = 0x04 (1 byte integer).
				buf_pos++;				
				ScriptBuf[buf_pos] = ch;	
				buf_pos++;					
			}
			else if ((i >= -32768) && (i <= 32767))	// 2 Bytes
			{
				short sh = (short)i;				
				ScriptBuf[buf_pos] = 0x05;			// Variable data type = 0x05 (2 bytes integer).
				buf_pos++;							
				memcpy(&ScriptBuf[buf_pos], &sh, 2);
				buf_pos += 2;						
			}
			else									// If its not one or two bytes, therefore 4 bytes
			{
				ScriptBuf[buf_pos] = 0x01;			
				buf_pos++;;							
				memcpy(&ScriptBuf[buf_pos], &i, 4);	
				buf_pos += 4;					
			}
			break;
		}
		case 'f':
		{
			float f = (float)va_arg(ap, double);	
			ScriptBuf[buf_pos] = 0x06;				// Variable data type = 0x06 (float).
			buf_pos++;								
			memcpy(&ScriptBuf[buf_pos], &f, 4);		
			buf_pos += 4;							// float = 4 bytes
			break;
		}
		case 'v':	// If a pointer
		{
			DWORD* v = va_arg(ap, DWORD*);							
			ScriptBuf[buf_pos] = 0x02;								// Variable data type = 0x02 (Global Var).
			buf_pos++;												
			WORD var_offs = var_pos * 4;							
			DWORD* ScriptVar = (DWORD*)(SCRIPT_BASE + var_offs);	
			ScriptVars[var_pos] = *ScriptVar;						
			*ScriptVar = *v;										
			memcpy(&ScriptBuf[buf_pos], &var_offs, 2);				
			buf_pos += 2;											
			var_pos++;												
			break;
		}
		case 's':
		{
			char* s1 = va_arg(ap, char*);		
			char s2[8];								
			ZeroMemory(s2, 8);						
			strncpy_s(s2, s1, 8);						
			memcpy(&ScriptBuf[buf_pos], s2, 8);		
			buf_pos += 8;							
			break;
		}
		}
		++p;
	}
	va_end(ap);
	if (var_pos)
	{
		int result = ExecuteScript();	

		p = cmd->args;		
		va_start(ap, cmd);	
		var_pos = 0;					
		while (*p)						
		{
			switch (*p)					
			{
			case 'i':				
			{
				va_arg(ap, long);	
				break;
			}
			case 'f':				
			{
				va_arg(ap, double);	
				break;
			}
			case 'v':				
			{
				DWORD* v = va_arg(ap, DWORD*);							
				DWORD* ScriptVar = (DWORD*)(SCRIPT_BASE + (var_pos * 4));	
				*v = *ScriptVar;										
				*ScriptVar = ScriptVars[var_pos];						
				var_pos++;												
				break;
			}
			case 's':				
			{
				va_arg(ap, char*);	
				break;
			}
			}
			++p;	
		}
		va_end(ap);		

		return result;	
	}
	else return ExecuteScript(); // If opcode had no args
}