#include "stdafx.h"
#include "Loader.h"

#include "../AVSVM/VMError.h"

using namespace AVSVM_VM;

Loader::Loader( )
{
}


Loader::~Loader( )
{
}


//装载程序
int Loader::LoadBytecodes(VM &vm, const wstring strBytecodesFileName/*字节码文件名*/)
{
	if (strBytecodesFileName.empty())
		return VM_E_FILE_NOTEXIST;


	//1.打开字节码文件
	FILE *pFileByteCode = fopen(strBytecodesFileName.c_str(), "rb");
	if ( NULL == pFileByteCode )
		return VM_E_OPEN_FILENAME;

	//2.读入文件,并装载到方法区中。
	if ( fread( CS, sizeof( char ), MethodBufferMax, pFileByteCode ) == 0 )
		goto error_read_bytecode;

	//3.关闭文件
	fclose( pFileByteCode );
	return VM_SUCCESS;

error_read_bytecode:
	fclose( pFileByteCode );
	return VM_E_OPEN_FILENAME;
}