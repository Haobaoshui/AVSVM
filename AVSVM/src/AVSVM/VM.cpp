// VM.cpp : 定义控制台应用程序的入口点。
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



//释放
int VM::DeleteVM( )
{




	return VM_SUCCESS;
}

//初始化虚拟机
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
new_size:DS大小（每个元素大小为sizeof(double)），注意该大小并不是实际内存大小
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
new_size:栈大小（每个元素大小为sizeof(double)），注意该大小并不是实际内存大小
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
		case PUSH:			//将浮点数压栈,目前只支持浮点数
			DumpPrint( _T( "PUSH" ) );
			i++;
			DumpPrint( GetParameterFloatFromCS( i ) );
			i += sizeof( double );
			DumpPrintEnter( );
			break;

		case DUP:			//复制栈顶
		case SWAP:			//交换栈顶元素
		case POP:			//弹栈

			//算术运算
		case ADD:			//加
			DumpPrint( _T( "ADD" ) );
			i++;
			DumpPrintEnter( );
			break;

		case SUB:			//减
			DumpPrint( _T( "SUB" ) );
			i++;
			DumpPrintEnter( );
			break;

		case MUL:			//乘
			DumpPrint( _T( "MUL" ) );
			i++;
			DumpPrintEnter( );
			break;

		case DIV:			//除
			DumpPrint( _T( "DIV" ) );
			i++;
			DumpPrintEnter( );
			break;

		case MOD:			//模
			DumpPrint( _T( "MOD" ) );
			i++;
			DumpPrintEnter( );
			break;

			//条件分支指令
		case IFEQ:			//如果相等
			break;
		case IFNE:			//如果不等
			break;

			//装载和保存
		case LOAD_LOCAL:		//局部变量
		{
			DumpPrint( _T( "LOAD_LOCAL" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;
		case LOAD_STATIC:	//局部变量
		{
			DumpPrint( _T( "LOAD_STATIC" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;
		case STORE_STATIC:	//静态变量
		{
			DumpPrint( _T( "STORE_STATIC" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;
		case STORE_LOCAL:	//静态变量
		{
			DumpPrint( _T( "STORE_LOCAL" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			DumpPrint( n );
			i += sizeof( int );
			DumpPrintEnter( );
		}
		break;

		//函数调用
		case SYS_CALL:		//系统函数调用，例如sin,...
		{
			DumpPrint( _T( "SYS_CALL" ) );
			i++;
			int n = GetParameterIntFromCS( i );
			i += sizeof( int );

			switch ( n )
			{


			case SYSFUNC_abs:		//(double x)			返回整型参数i的绝对值
				DumpPrint( _T( "\tSYSFUNC_abs" ) );
				break;

			case SYSFUNC_exp:		//(double x)			返回指数函数ex的值
				DumpPrint( _T( "\tSYSFUNC_exp" ) );
				break;

			case SYSFUNC_frexp:	//(double value,int *eptr)	返回value=x*2n中x的值,n存贮在eptr中
				DumpPrint( _T( "\tSYSFUNC_frexp" ) );
				break;

			case SYSFUNC_ldexp:	//(double value,int exp)	返回value*2exp的值
				DumpPrint( _T( "\tSYSFUNC_ldexp" ) );
				break;

			case SYSFUNC_log:		//(double x)				返回logex的值
				DumpPrint( _T( "\tSYSFUNC_log" ) );
				break;

			case SYSFUNC_log10:	//(double x)				返回log10x的值
				DumpPrint( _T( "\tSYSFUNC_log10" ) );
				break;

			case SYSFUNC_pow:		//(double x,double y)		返回xy的值
				DumpPrint( _T( "\tSYSFUNC_pow" ) );
				break;

			case SYSFUNC_pow10:	//(int p)					返回10p的值
				DumpPrint( _T( "\tSYSFUNC_pow10" ) );
				break;

			case SYSFUNC_sqrt:		//(double x)			返回+√x的值
				DumpPrint( _T( "\tSYSFUNC_sqrt" ) );
				break;

			case SYSFUNC_acos:		//(double x)			返回x的反余弦cos-1(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_acos" ) );
				break;

			case SYSFUNC_asin:		//(double x)			返回x的反正弦sin-1(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_asin" ) );
				break;

			case SYSFUNC_atan:		//(double x)			返回x的反正切tan-1(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_atan" ) );
				break;

			case SYSFUNC_atan2:	//(double y,double x)	返回y/x的反正切tan-1(x)值,y的x为弧度
				DumpPrint( _T( "\tSYSFUNC_atan2" ) );
				break;

			case SYSFUNC_cos:		//(double x)			返回x的余弦cos(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_cos" ) );
				break;

			case SYSFUNC_sin:		//(double x)			返回x的正弦sin(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_sin" ) );
				break;

			case SYSFUNC_tan:		//(double x)			返回x的正切tan(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_tan" ) );
				break;

			case SYSFUNC_cosh:		//(double x)			返回x的双曲余弦cosh(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_cosh" ) );
				break;

			case SYSFUNC_sinh:		//(double x)			返回x的双曲正弦sinh(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_sinh" ) );
				break;

			case SYSFUNC_tanh:		//(double x)			返回x的双曲正切tanh(x)值,x为弧度
				DumpPrint( _T( "\tSYSFUNC_tanh" ) );
				break;

			case SYSFUNC_hypot:	//(double x,double y)	返回直角三角形斜边的长度(z),x和y为直角边的长度,z2=x2+y2
				DumpPrint( _T( "\tSYSFUNC_hypot" ) );
				break;

			case SYSFUNC_ceil:		//(double x)			返回不小于x的最小整数
				DumpPrint( _T( "\tSYSFUNC_ceil" ) );
				break;

			case SYSFUNC_floor:	//(double x)			返回不大于x的最大整数
				DumpPrint( _T( "\tSYSFUNC_floor" ) );
				break;

			case SYSFUNC_rand:		//()					产生一个随机数并返回这个数
				DumpPrint( _T( "\tSYSFUNC_rand" ) );
				break;

			case SYSFUNC_fmod:		//(double x,double y)	返回x/y的余数
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


		//停机
		case NOP:			//
			i++;
			DumpPrint( _T( "NOP" ) );
			i++;
			DumpPrintEnter( );
			break;
		case HALT:			//停机
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