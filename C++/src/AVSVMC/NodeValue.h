#pragma once

#include "TokenValue.h"

#include <string>
using namespace std;


namespace AVSVM_Compiler
{
	const double  Epsilon = 0.00001;

	enum NodeOP
	{
		NodeOP_Plus,
		NodeOP_Sub,
		NodeOP_Mul,
		NodeOP_Div,
		NodeOP_Mod
	};

	enum NodeValueType
	{
		NodeValueType_OP,	//运算符
		NodeValueType_Var,	//变量

		NodeValueType_int_Val,	//常量
		NodeValueType_float_Val,	//常量		
		NodeValueType_string_Val,	//常量	


		NodeValueType_Unkonwn
	};

	class NodeValue
	{
	public:

	public:
		NodeValue( )
		{
			m_nType = NodeValueType_Unkonwn;
		}

		NodeValue( NodeOP op )
		{
			nOP = op;
			m_nType = NodeValueType_OP;
		}


		NodeValue( int n )
		{
			nValue = n;
			m_nType = NodeValueType_int_Val;
		}

		NodeValue( double d )
		{
			dValue = d;
			m_nType = NodeValueType_float_Val;
		}

		NodeValue( wstring str )
		{
			psValue = new wstring( str );
			m_nType = NodeValueType_string_Val;
		}

		NodeValue( const NodeValue  &r )
		{
			m_nType = r.m_nType;

			switch ( r.m_nType )
			{
			case NodeValueType_OP:
				nOP = r.nOP;
				break;

			case NodeValueType_Var:
				nOP = r.nOP;
				break;

			case NodeValueType_int_Val:
				nValue = r.nValue;
				break;
			case NodeValueType_float_Val:
				dValue = r.dValue;
				break;
			case NodeValueType_string_Val:
				psValue = new wstring( *r.psValue );
				break;

			case NodeValueType_Unkonwn:
				break;
			}
		}

		~NodeValue( )
		{
			Clean( );
		}

	public:
		void Clean( )
		{
			if ( NodeValueType_string_Val == m_nType && psValue )
				delete psValue;
		}
	public:

		void Set( NodeOP op )
		{
			Clean( );

			nOP = op;
			m_nType = NodeValueType_OP;
		}

		void Set( int n )
		{
			Clean( );

			nValue = n;
			m_nType = NodeValueType_int_Val;
		}

		void Set( double d )
		{
			Clean( );

			dValue = d;
			m_nType = NodeValueType_float_Val;
		}

		void Set( wstring str )
		{
			Clean( );

			psValue = new wstring( str );
			m_nType = NodeValueType_string_Val;
		}

		void Set( NodeValue &v )
		{
			Clean( );
			switch ( v.m_nType )
			{
			case NodeValueType_OP:	//运算符
				Set( v.nOP );
				break;

			case NodeValueType_Var:	//变量
				Set( v.nValue );
				break;

			case NodeValueType_int_Val:	//常量
				Set( v.nValue );
				break;

			case NodeValueType_float_Val:	//常量		
				Set( v.dValue );
				break;

			case NodeValueType_string_Val:	//常量	
				Set( *v.psValue );
				break;

			case NodeValueType_Unkonwn:
				break;
			}

			m_nType = v.m_nType;
		}

		void Set( TokenValue &tv )
		{
			switch ( tv.nTokenValueType )
			{
			case TokenValueType_Int:
				Set( tv.nValue );
				break;
			case TokenValueType_Double:
				Set( tv.dValue );
				break;
			case TokenValueType_Char:
				Set( tv.cValue );
				break;
			case TokenValueType_String:
				Set( *tv.pstr );
				break;
			case TokenValueType_Unknown:
			default:
				break;
			}
		}

	public:
		NodeValue operator+( const NodeValue &r )
		{
			NodeValue v;
			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					v.Set( nValue + r.nValue );
				else if ( NodeValueType_float_Val == m_nType )
					v.Set( dValue + r.dValue );
				else if ( NodeValueType_float_Val == m_nType )
					v.Set( *psValue + *r.psValue );
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				v.Set( nValue + r.dValue );
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				v.Set( dValue + r.nValue );
			}

			return v;
		}

		NodeValue operator-( const NodeValue &r )
		{
			NodeValue v;

			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					v.Set( nValue - r.nValue );
				else if ( NodeValueType_float_Val == m_nType )
					v.Set( dValue - r.dValue );
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				v.Set( nValue - r.dValue );
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				v.Set( dValue - r.nValue );
			}
			return v;
		}

		NodeValue operator*( const NodeValue &r )
		{
			NodeValue v;

			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					v.Set( nValue * r.nValue );
				else if ( NodeValueType_float_Val == m_nType )
					v.Set( dValue * r.dValue );
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				v.Set( nValue * r.dValue );
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				v.Set( dValue * r.nValue );
			}
			return v;
		}

		NodeValue operator/( const NodeValue &r )
		{
			NodeValue v;

			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					v.Set( nValue / r.nValue );
				else if ( NodeValueType_float_Val == m_nType )
					v.Set( dValue / r.dValue );
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				v.Set( nValue / r.dValue );
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				v.Set( dValue / r.nValue );
			}
			return v;
		}

		NodeValue operator%( const NodeValue &r )
		{
			NodeValue v;
			
			if ( NodeValueType_int_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				v.Set( nValue % r.nValue );
			}
			
			return v;
		}

		bool operator<( const NodeValue &r )
		{

			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					return  nValue - r.nValue < 0;
				else if ( NodeValueType_float_Val == m_nType )
					return  dValue - r.dValue < 0;
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				return nValue - r.dValue < 0;
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				return dValue - r.nValue <0;
			}
			return false;
		}

		bool operator>( const NodeValue &r )
		{

			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					return  nValue - r.nValue < 0;
				else if ( NodeValueType_float_Val == m_nType )
					return  dValue - r.dValue < 0;
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				return nValue - r.dValue < 0;
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				return dValue - r.nValue <0;
			}
			return false;
		}

		bool operator>=( const NodeValue &r )
		{
			return *this>r || *this == r;
		}

		bool operator<=( const NodeValue &r )
		{
			return *this < r || *this == r;
		}

		bool operator==( const NodeValue &r )
		{

			if ( r.m_nType == m_nType )
			{
				if ( NodeValueType_int_Val == m_nType )
					return  nValue == r.nValue;
				else if ( NodeValueType_float_Val == m_nType )
					return  fabs( dValue - r.dValue ) < Epsilon;
			}
			else if ( NodeValueType_int_Val == m_nType && NodeValueType_float_Val == r.m_nType )
			{
				return fabs( nValue - r.dValue ) < Epsilon;
			}
			else if ( NodeValueType_float_Val == m_nType && NodeValueType_int_Val == r.m_nType )
			{
				return fabs( dValue - r.nValue ) < Epsilon;
			}
			return false;
		}

	public:
		union
		{
			NodeOP	nOP;
			int nValue;
			double dValue;
			wstring *psValue;

		};

		NodeValueType m_nType;

	};

}