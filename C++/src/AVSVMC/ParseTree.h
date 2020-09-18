/*
* 语法树
*/
#pragma once

#include "Parser.h"
#include "Node.h"


namespace AVSVM_Compiler
{
	class ParseTree :public Parser
	{
	public:
		ParseTree( );
		~ParseTree( );

	public:
		bool Parse( const wstring strSrcFileName, const wstring strDestFileNam );
	protected:
		bool GenByteCodes( );
	protected:
		Node *m_pRoot;//语法树根节点
	};

}