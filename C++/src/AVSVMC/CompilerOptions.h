/*
* ������ѡ��
*/
#pragma once

namespace AVSVM_Compiler
{

	enum CompilerOptionType
	{
		CompilerOptionType_OutputFileName,	//����ļ�
		CompilerOptionType_Help,			//����
		CompilerOptionType_Version,			//�汾
		CompilerOptionType_Unknown			//δ֪����
	};
	struct CompilerOptions
	{
		const wchar_t *pstrOption;
		CompilerOptionType nType;
	};

	
	CompilerOptionType GetOptionType( const wchar_t* const pstr );
}


