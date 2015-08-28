#pragma once

#include "TokenValue.h"

namespace AVSVM_Compiler
{
	typedef int Token;

	const Token	Token_Eof = -1;	//结束

	const Token TokenBegin = 1000;

	const Token	Token_ID = TokenBegin + 10;
	const Token	Token_Num = TokenBegin + 20;
	const Token	Token_String = TokenBegin + 30;
	const Token	Token_Char = TokenBegin + 40;




	//自增, 自减
	const Token	Token_Op_Inc = TokenBegin + 50;		//自增
	const Token	Token_Op_Deinc = TokenBegin + 60;		//自减


	//逻辑运算符
	const Token	Token_Op_And = TokenBegin + 70;		//与
	const Token	Token_Op_Or = TokenBegin + 80;			//或

	//复合赋值运算符
	const Token	Token_Op_AddAssignment = TokenBegin + 90;			//-=
	const Token	Token_Op_SubAssignment = TokenBegin + 100;			//+=
	const Token	Token_Op_MulAssignment = TokenBegin + 110;			//*=
	const Token	Token_Op_DivAssignment = TokenBegin + 120;			///=
	const Token	Token_Op_ModAssignment = TokenBegin + 130;			//%=

	//关系运算符,包括等于(==)、不等于(!=)、小于(<)、小于等于(<=)、大于(>)、大于等于(>=)等几种
	const Token	Token_Op_Equal = TokenBegin + 140;		//等于
	const Token	Token_Op_NotEqual = TokenBegin + 150;		//不等于
	const Token	Token_Op_LessorEqual = TokenBegin + 160;		//小于等于
	const Token	Token_Op_GreatorEqual = TokenBegin + 170;		//大于等于


	//关键字
	const Token	Token_type_int = TokenBegin + 180;
	const Token	Token_type_float = TokenBegin + 190;
	const Token	Token_type_char = TokenBegin + 200;
	const Token	Token_type_string = TokenBegin + 210;

	const Token	Token_if = TokenBegin + 220;
	const Token	Token_else = TokenBegin + 230;
	const Token	Token_switch = TokenBegin + 240;
	const Token	Token_case = TokenBegin + 250;
	const Token	Token_default = TokenBegin + 260;
	const Token	Token_continue = TokenBegin + 270;
	const Token	Token_break = TokenBegin + 280;
	const Token	Token_while = TokenBegin + 290;
	const Token	Token_for = TokenBegin + 300;
	const Token	Token_foreach = TokenBegin + 310;

	const Token	Token_Unknown = TokenBegin + 320;


	//关键字字符串
	const TCHAR * const cst_KeyWord_int = _T("int");
	const TCHAR * const cst_KeyWord_float = _T("float");
	const TCHAR * const cst_KeyWord_char = _T("char");
	const TCHAR * const cst_KeyWord_string = _T("string");

	const TCHAR * const cst_KeyWord_if = _T("if");
	const TCHAR * const cst_KeyWord_else = _T("else");
	const TCHAR * const cst_KeyWord_switch = _T("switch");
	const TCHAR * const cst_KeyWord_case = _T("case");
	const TCHAR * const cst_KeyWord_default = _T("default");
	const TCHAR * const cst_KeyWord_continue = _T("continue");
	const TCHAR * const cst_KeyWord_break = _T("break");
	const TCHAR * const cst_KeyWord_while = _T("while");
	const TCHAR * const cst_KeyWord_for = _T("for");
	const TCHAR * const cst_KeyWord_foreach = _T("foreach");


	const unsigned int MAX_ID_LENGTH = 1024;

	struct KeyWord
	{
		const TCHAR *pKeyWord;
		int nToken;
	};

	const KeyWord gKeyWords[] =
	{
		{ cst_KeyWord_int, Token_type_int },
		{ cst_KeyWord_float, Token_type_float },
		{ cst_KeyWord_float, Token_type_char },
		{ cst_KeyWord_string, Token_type_string },

		{ cst_KeyWord_if, Token_if },
		{ cst_KeyWord_else, Token_else },
		{ cst_KeyWord_switch, Token_switch },
		{ cst_KeyWord_case, Token_case },
		{ cst_KeyWord_default, Token_case },
		{ cst_KeyWord_continue, Token_continue },
		{ cst_KeyWord_break, Token_break },
		{ cst_KeyWord_while, Token_while },
		{ cst_KeyWord_for, Token_for },
		{ cst_KeyWord_foreach, Token_foreach }
	};

	

	


	class Lex
	{
	public:
		Lex();
		~Lex();

	public:
		inline bool SetProgram(const TCHAR *pstr);
	protected:
		const TCHAR *m_pstrProgram;

	public:
		Token GetNextToken();
		TokenValue m_tokenvalue;
	protected:
		void ResetTokenValue();
		
		Token m_nToken;

	protected:
		inline bool IsParseStringEnd();
		inline void MoveToNextChar();
		inline void SkipSpace();
		inline TCHAR GetChar();
		inline TCHAR GetNextChar();
		int ParserID();
		bool ParseString();
		bool ParseChar();
		bool EscapeCharacter(const TCHAR *p);
		bool ParseNumber();
		inline bool IsID(TCHAR c);
		inline bool IsNum(TCHAR c);
		int GetTokenByString(const TCHAR *p);

	protected:
		inline void IncCol();
		inline void IncRow();
		void SetPosBegin();
		void SetPosEnd();
	private:
		int m_nCurrentRow;
		int m_nCurrentCol;
	};

	bool Lex::SetProgram(const TCHAR *pstr)
	{
		m_pstrProgram = pstr;
		return NULL != pstr && NULL != *pstr;
	}

	void Lex::IncCol()
	{
		m_nCurrentCol++;
	}

	void Lex::IncRow()
	{
		m_nCurrentRow++;
		m_nCurrentCol = 0;
	}

	void Lex::MoveToNextChar()
	{
		if (m_pstrProgram && *m_pstrProgram)
		{
			IncCol();
			m_pstrProgram++;
		}
	}


	//得到当前字符
	TCHAR Lex::GetChar()
	{
		if (m_pstrProgram)
			return *m_pstrProgram;
		return 0;
	}

	//得到下一个字符
	inline TCHAR Lex::GetNextChar()
	{
		if (m_pstrProgram && *m_pstrProgram)
			return *(m_pstrProgram + 1);
		return 0;
	}

	bool Lex::IsID(TCHAR c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'a' && c <= 'z') || c == '_';
	}

	bool Lex::IsNum(TCHAR c)
	{
		return  c >= '0' && c <= '9';
	}


	/*
	是否到了解析字符串的末尾
	*/
	bool Lex::IsParseStringEnd()
	{
		if (NULL == m_pstrProgram || NULL == *m_pstrProgram)

			return true;
		return false;
	}
	inline void Lex::SkipSpace()
	{
		while (m_pstrProgram && *m_pstrProgram == ' ')
		{
			IncCol();
			MoveToNextChar();
		}
	}
}