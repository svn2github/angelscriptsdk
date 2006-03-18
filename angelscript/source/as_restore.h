/*
   AngelCode Scripting Library
   Copyright (c) 2003-2004 Andreas J�nsson

   This software is provided 'as-is', without any express or implied 
   warranty. In no event will the authors be held liable for any 
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any 
   purpose, including commercial applications, and to alter it and 
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you 
      must not claim that you wrote the original software. If you use
	  this software in a product, an acknowledgment in the product 
	  documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and 
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source 
      distribution.

   The original version of this library can be located at:
   http://www.angelcode.com/angelscript/

   Andreas J�nsson
   andreas@angelcode.com
*/


//
// as_restore.h
//
// Functions for saving and restoring module bytecode
// asCRestore was originally written by Dennis Bollyn, dennis@gyrbo.be


#ifndef AS_RESTORE_H
#define AS_RESTORE_H

#include "as_scriptengine.h"
#include "as_context.h"
#include "as_map.h"

class asCRestore {
public:
	asCRestore(asCModule* module, asIBinaryStream* stream, asCScriptEngine* engine);

	int Save();
	int Restore();

protected:
	asCModule* module;
	asIBinaryStream* stream;
	asCScriptEngine* engine;

	void WriteString(asCString* str);
	void WriteFunction(asCScriptFunction* func);
	void WriteProperty(asCProperty* prop);
	void WriteBSTR(asBSTR* str);
	void WriteDataType(asCDataType* dt);
	void WriteObjectType(asCObjectType* ot);

	void ReadString(asCString* str);
	void ReadFunction(asCScriptFunction* func);
	void ReadProperty(asCProperty* prop);
	asBSTR ReadBSTR();
	void ReadDataType(asCDataType* dt);
	asCObjectType* ReadObjectType();

	void WriteByteCode(asBYTE *bc, int length);
	void ReadByteCode(asBYTE *bc, int length);
#ifdef USE_ASM_VM
	asBYTE FindByteCode(asDWORD relocation);

	asCMap relocToBC;
#endif
};

#endif //AS_RESTORE_H
