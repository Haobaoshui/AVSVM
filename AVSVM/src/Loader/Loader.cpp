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


//װ�س���
int Loader::LoadBytecodes(VM &vm, const wstring strBytecodesFileName/*�ֽ����ļ���*/)
{
	if (strBytecodesFileName.empty())
		return VM_E_FILE_NOTEXIST;


	//1.���ֽ����ļ�
	FILE *pFileByteCode = fopen(strBytecodesFileName.c_str(), "rb");
	if ( NULL == pFileByteCode )
		return VM_E_OPEN_FILENAME;

	//2.�����ļ�,��װ�ص��������С�
	if ( fread( CS, sizeof( char ), MethodBufferMax, pFileByteCode ) == 0 )
		goto error_read_bytecode;

	//3.�ر��ļ�
	fclose( pFileByteCode );
	return VM_SUCCESS;

error_read_bytecode:
	fclose( pFileByteCode );
	return VM_E_OPEN_FILENAME;
}