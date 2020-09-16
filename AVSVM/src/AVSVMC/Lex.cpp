
#include "Lex.h"

using namespace AVSVM_Compiler;

Lex::Lex( )
{
	m_pstrProgram = NULL;//��ʼ���������ַ���
	m_nCurrentRow = 0;//��ʼ����ǰλ�����ڵ���
	m_nCurrentCol = 0;//��ʼ����ǰλ�����ڵ���
}


Lex::~Lex( )
{
}



Token Lex::GetNextToken( )
{
	int c = 0;
	unsigned int nChar = 0;
	while ( !IsParseStringEnd( ) )
	{
		SkipSpace( );
		nChar = GetChar( );
		switch ( nChar )
		{

		case ' ':
			IncCol( );
			continue;

		case '\t':
			IncCol( );
			IncCol( );
			IncCol( );
			IncCol( );
			MoveToNextChar( );
			continue;


		case '\r':
			IncRow( );
			MoveToNextChar( );
			continue;

		case '\n':
			IncRow( );
			MoveToNextChar( );
			continue;

		case '=':
			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_Equal;	//==
			}
			return '=';


		case '^':
		case '(':
		case ')':
		case ',':
		case ';':
		case '?':
		case '[':
		case ']':
		case '{':
		case '}':
			MoveToNextChar( );
			IncCol( );
			return nChar;

		case '!':
			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_NotEqual;	//��ϵ�����!=
			}
			return '!';

		case '&':
			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '&' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_And;	//�߼������&&
			}

			return '&';

		case '|':
			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '|' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_Or;	//�߼������||
			}

			return '|';


			/*
			ͬ'+'������������+,++,+=��
			*/
		case '+':


			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_AddAssignment;	//+=
			}
			else if ( GetChar( ) == '+' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_Inc;
			}

			return '+';


			/*
			ͬ'-'������������-,--,-=��
			*/
		case '-':


			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_SubAssignment;	// ���������-=
			}
			else if ( GetChar( ) == '-' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_Deinc;//�Լ������
			}

			return '-';

			/*
			ͬ'*'������������*,*=��
			*/
		case '*':
			MoveToNextChar( );
			IncCol( );			
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_MulAssignment;	//���������*=
			}


			return '*';

			/*
			ͬ'/'������������/,/=��
			*/
		case '/':


			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_DivAssignment;	//���������/=
			}


			return '/';

			/*
			ͬ'%'������������%,%=��
			*/
		case '%':

			MoveToNextChar( );
			IncCol( );

			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_ModAssignment;	//���������%=
			}

			return '%';


		case ':':
			MoveToNextChar( );
			IncCol( );
			return ':';


		case '>'://����			
			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_GreatOrEqual;
			}
			return '>';

		case '<'://С��

			MoveToNextChar( );
			IncCol( );
			if ( GetChar( ) == '=' )
			{
				MoveToNextChar( );
				IncCol( );
				return Token_Op_LessOrEqual;
			}
			return '<';


			//�ַ�������
		case '\'':
			ParseChar( );
			return Token_Char;

		case '\"':
			ParseString( );
			return Token_String;

			//�������֣����ֵĺϷ���ʽΪ[0-9]+('.'[0-9]+)?,��Ҫô��������Ҫô��С��
		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
		case '.':
			ParseNumber( );
			return Token_Num;



		case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':
		case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':
		case 'q':case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':
		case 'y':case 'z':
		case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
		case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':
		case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
		case 'Y':case 'Z':
		case '_':
			return ParserID( );


		default:
			break;
		}
	}

	return Token_Unknown;
}

void Lex::ResetTokenValue( )
{
	m_tokenvalue.Reset( );
}

bool Lex::ParseNumber( )
{
	ResetTokenValue( );

	wchar_t  buf[ 1024 ];
	bool bFlagPoint = ( '.' == GetChar( ) ? true : false );

	

	wchar_t*p = buf;
	for ( ;; )
	{
		*p++ = GetChar( );
		MoveToNextChar( );

		//���������ֻ���С�������1λ��ֹͣ����
		if ( !IsNum( GetChar( ) ) || ( bFlagPoint && GetChar( ) == '.' ) )
			break;
	}

	*p = '\0';

	if ( bFlagPoint )
		m_tokenvalue.Set( _wtof( buf ) );
	else
		m_tokenvalue.Set( _wtoi( buf ) );

	return true;
}



bool Lex::ParseChar( )
{
	ResetTokenValue( );
	wchar_t   buf[ 1024 ];

	wchar_t*p = buf;
	for ( ; GetChar( )!='\''; )
	{
		*p++ = GetChar( );
		MoveToNextChar( );		
	}

	*p = '\0';

	EscapeCharacter( buf );

	m_tokenvalue.Set( buf[ 0 ] );

	return true;
}

bool Lex::ParseString( )
{
	ResetTokenValue( );
	wchar_t  buf[ 1024 ];

	wchar_t*p = buf;
	for ( ; GetChar( ) != '"'; )
	{
		*p++ = GetChar( );
		MoveToNextChar( );
	}

	*p = '\0';

	EscapeCharacter( buf );
	m_tokenvalue.Set( buf );

	return true;
}

bool Lex::EscapeCharacter( const wchar_t*p )
{
	if ( NULL == p )
		return  false;

	wchar_t  buf[ MAX_ID_LENGTH ];
	wchar_t*d = buf;
	while ( *p )
	{
		if ( *p++ == '\\' )
		{
			switch ( *p )
			{
			case '\\':
				*d++ = '\\';
			case 'n':
				*d++ = '\n';
			case 'r':
				*d++ = '\r';
			case 't':
				*d++ = '\t';
				break;

			default:
				return false;				
			}

		}
		*d++ = *p++;
	}
	return true;
}

int Lex::ParserID( )
{
	SetPosBegin( );
	ResetTokenValue( );


	wchar_t  buf[ MAX_ID_LENGTH ];
	int i = 0;
	do
	{
		buf[ i++ ] = GetChar( );
		MoveToNextChar( );
		IncCol( );//����λ��
		SetPosEnd( );
	} while ( IsID( GetChar( ) ) );

	return GetTokenByString( buf );
}



int Lex::GetTokenByString( const wchar_t*p )
{
	if ( NULL == p )
		return Token_Unknown;

	for ( int i = 0; i < sizeof( gKeyWords ) / sizeof( KeyWord ); i++ )
	{
		if ( !wcscmp( gKeyWords[ i ].pKeyWord, p ) )
			return gKeyWords[ i ].nToken;
	}


	return Token_Unknown;
}

void Lex::SetPosBegin( )
{
}

void Lex::SetPosEnd( )
{
}