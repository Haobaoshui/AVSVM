// VM.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <stdio.h>
#include <string.h>
#include <malloc.h>


#include "vm.h"
#include "VMErr.h"

using namespace AVSVM_VM;

VM::VM( )
{
	m_nCSLength = 0;
	CS = NULL;

	m_nDSLength = 0;
	DS = NULL;

	m_nStackLength = 0;
	stack = NULL;

	m_nGenCSIndex = 0;
	m_nGenDSIndex = 0;

	m_bResult = false;
}

VM::~VM( )
{
	if ( CS )
		free( CS );

	if ( DS )
		free( DS );

	if ( stack )
		free( stack );
}



//�ͷ�
int VM::DeleteVM( )
{




	return VM_SUCCESS;
}

//��ʼ�������
int VM::InitVM( )
{
	BP = 0;
	SP = 0;
	PC = 0;

	return VM_SUCCESS;
}

void VM::malloc_CS( int new_size )
{
	unsigned long size = m_nCSLength;
	if ( size == 0 )
		size = 1;
	while ( size < new_size )
		size = size * 2;

	if ( NULL == CS )
		CS = ( char * ) malloc( size );
	else
		CS = ( char * ) realloc( CS, size );

	m_nCSLength = size;
}


/*
new_size:DS��С��ÿ��Ԫ�ش�СΪsizeof(double)����ע��ô�С������ʵ���ڴ��С
*/
void VM::malloc_DS( int new_size )
{
	unsigned long size = m_nDSLength;
	if ( size == 0 )
		size = 1;

	while ( size < new_size )
		size = size * 2;

	if ( NULL == CS )
		DS = ( double * ) malloc( sizeof( double )*size );
	else
		DS = ( double * ) realloc( stack, sizeof( double )*size );

	m_nDSLength = size;
}


/*
new_size:ջ��С��ÿ��Ԫ�ش�СΪsizeof(double)����ע��ô�С������ʵ���ڴ��С
*/
void VM::malloc_stack( int new_size )
{
	unsigned long size = m_nStackLength;
	if ( size == 0 )
		size = 1;

	while ( size < new_size )
		size = size * 2;

	if ( NULL == CS )
		stack = ( double * ) malloc( sizeof( double )*size );
	else
		stack = ( double * ) realloc( stack, sizeof( double )*size );

	m_nStackLength = size;
}

void VM::Gen_OP( VM_INSTRUCTION op )
{
	if ( m_nCSLength<m_nGenCSIndex + 1 )
		malloc_CS( m_nGenCSIndex + 1 );

	CS[ m_nGenCSIndex ] = op;
	m_nGenCSIndex++;
}

void VM::Gen_OP( VM_INSTRUCTION op, int n )
{
	if ( m_nCSLength<m_nGenCSIndex + sizeof( int ) + 1 )
		malloc_CS( m_nGenCSIndex + sizeof( int ) + 1 );

	CS[ m_nGenCSIndex ] = op;
	m_nGenCSIndex++;

	*( CS + m_nGenCSIndex ) = n;
	m_nGenCSIndex += sizeof( int );

}

void VM::Gen_OP( VM_INSTRUCTION op, double f )
{
	if ( m_nCSLength<m_nGenCSIndex + sizeof( double ) + 1 )
		malloc_CS( m_nGenCSIndex + sizeof( double ) + 1 );

	CS[ m_nGenCSIndex ] = op;
	m_nGenCSIndex++;

	*( CS + m_nGenCSIndex ) = f;
	m_nGenCSIndex += sizeof( double );

}
void VM::SetVar( double f, int nIndex )
{
	if ( nIndex<0 )
		return;

	if ( m_nDSLength<nIndex + 1 )
		malloc_DS( nIndex + 1 );

	DS[ nIndex ] = f;
}





#ifdef _DEBUG
void DumpPrint( const TCHAR *s )
{
	::OutputDebugString( s );
}

void DumpPrint( int n )
{
	TCHAR s[ 32 ];
	swprintf( s, _T( "\t%d" ), n );
	::OutputDebugString( s );
}

void DumpPrint( double f )
{
	TCHAR s[ 32 ];
	swprintf( s, _T( "\t%f" ), f );
	::OutputDebugString( s );
}

void DumpPrintEnter( )
{
	::OutputDebugString( _T( "\n" ) );
}

void VM::DumpBin( )
{
	int i = 0;
	while ( i<m_nGenCSIndex )
	{
		VM_INSTRUCTION op = ( VM_INSTRUCTION ) CS[ i ];
		switch ( op )
		{
		case PUSH:			//��������ѹջ,Ŀǰֻ֧�ָ�����
			DumpPrint( _T( "PUSH" ) );
			i++;
			DumpPrint( GetParameterFloatFromCS( i ) );
			i += sizeof( double );
			DumpPrintEnter( );
			break;

		case DUP:			//����ջ��
		case SWAP:			//����ջ��Ԫ��
		case POP:			//��ջ

			//��������
		case ADD:			//��
			DumpPrint( _T( "ADD" ) );
			i++;
			DumpPrintEnter( );
			break;

		case SUB:			//��
			DumpPrint( _T( "SUB" ) );
			i++;
			DumpPrintEnter( );
			break;

		case MUL:			//��
			DumpPrint( _T( "MUL" ) );
			i++;
			DumpPrintEnter( );
			break;

		case DIV:			//��
			DumpPrint( _T( "DIV" ) );
			i++;
			DumpPrintEnter( );
			break;

		case MOD:			//ģ
			DumpPrint( _T( "MOD" ) );
			i++;
			DumpPrintEnter( );
			break;

			//������ָ֧��
		case IFEQ:			//������
			break;
		case IFNE:			//�������
			break;

			//װ�غͱ���
		case LOAD_LOCAL:		//�ֲ�����
		{
			DumpPrint( _T( "LOAD_LOCAL" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;
		case LOAD_STATIC:	//�ֲ�����
		{
			DumpPrint( _T( "LOAD_STATIC" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;
		case STORE_STATIC:	//��̬����
		{
			DumpPrint( _T( "STORE_STATIC" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;
		case STORE_LOCAL:	//��̬����
		{
			DumpPrint( _T( "STORE_LOCAL" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;

		//��������
		case SYS_CALL:		//ϵͳ�������ã�����sin,...
		{
			DumpPrint( _T( "SYS_CALL" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			i += sizeof( int );

			switch ( n )
			{


			case SYSFUNC_abs:		//(double x)			�������Ͳ���i�ľ���ֵ
				DumpPrint( _T( "\tSYSFUNC_abs" ) );
				break;

			case SYSFUNC_exp:		//(double x)			����ָ������ex��ֵ
				DumpPrint( _T( "\tSYSFUNC_exp" ) );
				break;

			case SYSFUNC_frexp:	//(double value,int *eptr)	����value=x*2n��x��ֵ,n������eptr��
				DumpPrint( _T( "\tSYSFUNC_frexp" ) );
				break;

			case SYSFUNC_ldexp:	//(double value,int exp)	����value*2exp��ֵ
				DumpPrint( _T( "\tSYSFUNC_ldexp" ) );
				break;

			case SYSFUNC_log:		//(double x)				����logex��ֵ
				DumpPrint( _T( "\tSYSFUNC_log" ) );
				break;

			case SYSFUNC_log10:	//(double x)				����log10x��ֵ
				DumpPrint( _T( "\tSYSFUNC_log10" ) );
				break;

			case SYSFUNC_pow:		//(double x,double y)		����xy��ֵ
				DumpPrint( _T( "\tSYSFUNC_pow" ) );
				break;

			case SYSFUNC_pow10:	//(int p)					����10p��ֵ
				DumpPrint( _T( "\tSYSFUNC_pow10" ) );
				break;

			case SYSFUNC_sqrt:		//(double x)			����+��x��ֵ
				DumpPrint( _T( "\tSYSFUNC_sqrt" ) );
				break;

			case SYSFUNC_acos:		//(double x)			����x�ķ�����cos-1(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_acos" ) );
				break;

			case SYSFUNC_asin:		//(double x)			����x�ķ�����sin-1(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_asin" ) );
				break;

			case SYSFUNC_atan:		//(double x)			����x�ķ�����tan-1(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_atan" ) );
				break;

			case SYSFUNC_atan2:	//(double y,double x)	����y/x�ķ�����tan-1(x)ֵ,y��xΪ����
				DumpPrint( _T( "\tSYSFUNC_atan2" ) );
				break;

			case SYSFUNC_cos:		//(double x)			����x������cos(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_cos" ) );
				break;

			case SYSFUNC_sin:		//(double x)			����x������sin(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_sin" ) );
				break;

			case SYSFUNC_tan:		//(double x)			����x������tan(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_tan" ) );
				break;

			case SYSFUNC_cosh:		//(double x)			����x��˫������cosh(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_cosh" ) );
				break;

			case SYSFUNC_sinh:		//(double x)			����x��˫������sinh(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_sinh" ) );
				break;

			case SYSFUNC_tanh:		//(double x)			����x��˫������tanh(x)ֵ,xΪ����
				DumpPrint( _T( "\tSYSFUNC_tanh" ) );
				break;

			case SYSFUNC_hypot:	//(double x,double y)	����ֱ��������б�ߵĳ���(z),x��yΪֱ�Ǳߵĳ���,z2=x2+y2
				DumpPrint( _T( "\tSYSFUNC_hypot" ) );
				break;

			case SYSFUNC_ceil:		//(double x)			���ز�С��x����С����
				DumpPrint( _T( "\tSYSFUNC_ceil" ) );
				break;

			case SYSFUNC_floor:	//(double x)			���ز�����x���������
				DumpPrint( _T( "\tSYSFUNC_floor" ) );
				break;

			case SYSFUNC_rand:		//()					����һ������������������
				DumpPrint( _T( "\tSYSFUNC_rand" ) );
				break;

			case SYSFUNC_fmod:		//(double x,double y)	����x/y������
				DumpPrint( _T( "\tSYSFUNC_fmod" ) );
				break;

			case SYSFUNC_UNKNOWN:
			default:
				DumpPrint( _T( "\tSYSFUNC_UNKNOWN" ) );
				break;
			}
			DumpPrintEnter( );
		}
		break;


		//ͣ��
		case NOP:			//
			i++;
			DumpPrint( _T( "NOP" ) );
			i++;
			DumpPrintEnter( );
			break;
		case HALT:			//ͣ��
			i++;
			DumpPrint( _T( "HALT" ) );
			i++;
			DumpPrintEnter( );
			break;
		default:
			i++;
			//	assert(0);
			break;
		}
	}
}
#endif