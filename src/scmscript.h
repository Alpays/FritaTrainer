#pragma once

#include "trainer.h"

#define MAX_SCRIPT_VARIABLE 16
#define MAX_SCRIPT_SIZE 255

struct SCRIPT
{
	void* pNext;			
	void* pPrev;			
	char strName[8];		
	DWORD dwScriptIP;		
	DWORD dwReturnStack[6];	
	DWORD dwStackPointer;	
	DWORD dwLocalVar[18];	
	BYTE bStartNewScript;	
	BYTE bJumpFlag;			
	BYTE bWorky;			
	BYTE bAwake;			
	DWORD dwWakeTime;		
	WORD wIfParam;			
	BYTE bNotFlag;			
	BYTE bWastedBustedCheck;
	BYTE bWastedBustedFlag;
	BYTE bMissionThread;	
	BYTE pad[2];			
};

struct SCM_COMMAND
{
	WORD opcode;
	char args[13];
};

/* SCM Opcodes used in this Trainer */

const SCM_COMMAND request_model = { 0x0247, "i" };
const SCM_COMMAND load_reqmodels = { 0x038B, "" };
const SCM_COMMAND is_model_available = { 0x0248, "i" };
const SCM_COMMAND release_model = { 0x0249, "i" };

const SCM_COMMAND create_vehicle = { 0x00A5, "ifffv" };
const SCM_COMMAND delete_vehicle = { 0x00A6, "v" };

const SCM_COMMAND create_player = { 0x053, "ifffv" };
const SCM_COMMAND get_player_char = { 0x01F5, "vv" };
const SCM_COMMAND set_player_ammo = { 0x017A, "vii" };
const SCM_COMMAND set_player_health = { 0x0222, "vi" };


// Our function to call SCM opcodes with parameters.
int scmScript(const SCM_COMMAND* command, ...);