#pragma once

#include "Position.h"

#include <string>
using namespace std;



namespace AVSVM_Compiler
{
	enum TokenValueType
	{
		TokenValueType_Int,
		TokenValueType_Double,
		TokenValueType_Char,
		TokenValueType_String,
		TokenValueType_Unknown
	};

	struct TokenValue
	{
		TokenValue( )
		{
			nTokenValueType = TokenValueType_Unknown;
			pstr = NULL;
		}
		~TokenValue( )
		{
			Reset( );
		}

		void Reset( )
		{
			if ( ( nTokenValueType == TokenValueType_String ) && pstr )
				delete pstr;
			nTokenValueType = TokenValueType_Unknown;
			pstr = NULL;
		}

		void Set( int n )
		{
			Reset( );
			nTokenValueType = TokenValueType_Int;
			nValue = n;
		}

		void Set(wchar_t c )
		{
			Reset( );
			nTokenValueType = TokenValueType_Char;
			cValue = c;
		}

		void Set( double d )
		{
			Reset( );
			nTokenValueType = TokenValueType_Double;
			dValue = d;
		}

		void Set( const wchar_t*s )
		{
			Reset( );
			nTokenValueType = TokenValueType_String;
			size_t n = wcslen( s );
			pstr = new wstring;
			*pstr = s;

		}

		void Set( wstring &s )
		{
			Reset( );
			nTokenValueType = TokenValueType_String;
			pstr = new wstring;
			*pstr = s;
		}

		TokenPosition pos;	//位置
		TokenValueType nTokenValueType;		//Token值类型

		//value
		union
		{
			int nValue;
			wchar_t cValue;
			double dValue;
			wstring *pstr;
		};
	};
}