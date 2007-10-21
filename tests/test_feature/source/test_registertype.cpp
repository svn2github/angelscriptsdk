#include "utils.h"

namespace TestRegisterType
{

#define TESTNAME "TestRegisterType"

bool Test()
{
	bool fail = false;
	int r = 0;
	COutStream out;
 	asIScriptEngine *engine;

	// A type registered with asOBJ_REF must not register destructor
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	engine->SetMessageCallback(asMETHOD(COutStream,Callback), &out, asCALL_THISCALL);
	r = engine->RegisterObjectType("ref", 4, asOBJ_REF); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ref", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(0), asCALL_GENERIC);
	if( r != asILLEGAL_BEHAVIOUR_FOR_TYPE )
		fail = true;
	engine->Release();

	// A type registered with asOBJ_GC must register all gc behaviours
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	engine->SetMessageCallback(asMETHOD(COutStream,Callback), &out, asCALL_THISCALL);
	r = engine->RegisterObjectType("gc", 4, asOBJ_REF | asOBJ_GC); assert( r >= 0 );
	r = engine->ExecuteString(0, "");
	if( r >= 0 )
		fail = true;
	engine->Release();

	// A type registered with asOBJ_VALUE must not register addref, release, and gc behaviours
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	engine->SetMessageCallback(asMETHOD(COutStream,Callback), &out, asCALL_THISCALL);
	r = engine->RegisterObjectType("val", 4, asOBJ_VALUE | asOBJ_APP_PRIMITIVE); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("val", asBEHAVE_ADDREF, "void f()", asFUNCTION(0), asCALL_GENERIC);
	if( r != asILLEGAL_BEHAVIOUR_FOR_TYPE )
		fail = true;
	r = engine->RegisterObjectBehaviour("val", asBEHAVE_RELEASE, "void f()", asFUNCTION(0), asCALL_GENERIC);
	if( r != asILLEGAL_BEHAVIOUR_FOR_TYPE )
		fail = true;
	r = engine->RegisterObjectBehaviour("val", asBEHAVE_GETREFCOUNT, "int f()", asFUNCTION(0), asCALL_GENERIC);
	if( r != asILLEGAL_BEHAVIOUR_FOR_TYPE )
		fail = true;
	engine->Release();

	// Object types registered as ref must not be allowed to be
	// passed by value to registered functions, nor returned by value
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	engine->SetMessageCallback(asMETHOD(COutStream,Callback), &out, asCALL_THISCALL);
	r = engine->RegisterObjectType("ref", 4, asOBJ_REF); assert( r >= 0 );
	r = engine->RegisterGlobalFunction("void f(ref)", asFUNCTION(0), asCALL_GENERIC);
	if( r >= 0 )
		fail = true;
	r = engine->RegisterGlobalFunction("ref f()", asFUNCTION(0), asCALL_GENERIC);
	if( r >= 0 )
		fail = true;
	engine->Release();

	// Ref type without registered assignment behaviour won't allow the assignment
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	engine->SetMessageCallback(asMETHOD(COutStream,Callback), &out, asCALL_THISCALL);
	r = engine->RegisterObjectType("ref", 0, asOBJ_REF); assert( r >= 0 ); 
	r = engine->RegisterObjectBehaviour("ref", asBEHAVE_FACTORY, "ref@ f()", asFUNCTION(0), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ref", asBEHAVE_ADDREF, "void f()", asFUNCTION(0), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ref", asBEHAVE_RELEASE, "void f()", asFUNCTION(0), asCALL_GENERIC); assert( r >= 0 );
	r = engine->ExecuteString(0, "ref r1, r2; r1 = r2;");
	if( r >= 0 )
		fail = true;
	engine->Release();


	// Ref type must register addref and release

	// Value type without registered assignment behaviour should allow bitwise copy

    // Only types registered with asOBJ_POD (plain-old-data) should allow
    // initialization and assignment with registered constructor and assignment behaviour

	// Value types without asOBJ_POD must have the constructor and destructor registered

	// Ref type must register ADDREF and RELEASE

	// Ref types without default factory must not be allowed to be initialized

	// Ref types with asOBJ_NOHANDLE is allowed and must not register ADDREF, RELEASE, or FACTORY behaviours (used for singletons)
	// It must not be possible to register functions that take handles of types with asOBJ_HANDLE

    // Validate if the same behaviour is registered twice, e.g. if index
    // behaviour is registered twice with signature 'int f(int)' and error should be given

	// Success
 	return fail;
}

} // namespace
