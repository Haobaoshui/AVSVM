#pragma once

namespace AVSVM_Compiler
{
	//������ѡ��
	enum CompilerOptionType
	{
		CompilerOptionType_OutputFileName,	//����ļ�
		CompilerOptionType_Help,			//����
		CompilerOptionType_Unknown			//δ֪����
	};
	struct CompilerOptions
	{
		TCHAR *pstrOption;
		CompilerOptionType nType;
	};

	
	CompilerOptionType GetOptionType( const TCHAR * const pstr );
}


