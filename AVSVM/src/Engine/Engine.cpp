#include "stdafx.h"
#include "Engine.h"


Engine::Engine( )
{
}


Engine::~Engine( )
{
}


//取得方法区中指定位置的整数值
int VM::GetParameterIntFromCS( int nIndex )
{
	return ( int ) ( *( CS + nIndex ) );
}
double VM::GetParameterFloatFromCS( int nIndex )
{
	return ( double ) ( *( CS + nIndex ) );
}

int VM::GetParameterIntFromDS( int nIndex )
{
	return ( int ) ( *( DS + nIndex ) );
}

double VM::GetParameterFloatFromDS( int nIndex )
{
	return ( double ) ( *( DS + nIndex ) );
}


/*
执行引擎
字节码之前已经被装载到方法区中
*/
int VM::Run( )
{
	BP = 0;
	SP = 0;
	PC = 0;

	m_bResult = false;

	int nParameter = 0;
	double dParameter = 0;

	for ( ;; )
	{
		//获得指令
		char op = *( CS + PC );

		switch ( op )
		{
		case PUSH:
			PC++;
			dParameter = GetParameterFloatFromCS( PC );
			PC += sizeof( double );

			if ( m_nStackLength<SP + 1 )
				malloc_stack( SP + 1 );
			stack[ SP ] = dParameter;
			SP++;
			break;

		case DUP:
			PC++;
			if ( SP >= 0 )
			{
				if ( m_nStackLength<SP + 1 )
					malloc_stack( SP + 1 );

				stack[ SP ] = stack[ SP - 1 ];
				SP++;
			}

			break;

		case SWAP:
			PC++;
			if ( SP >= 1 && SP<m_nStackLength )
			{
				int temp = stack[ SP ];
				stack[ SP ] = stack[ SP - 1 ];
				stack[ SP - 1 ] = temp;
			}
			break;

		case POP:
			PC++;
			if ( SP >= 0 )
				SP--;
			break;


		case ADD:
			PC++;
			if ( SP >= 1 )
			{
				stack[ SP - 2 ] = stack[ SP - 1 ] + stack[ SP - 2 ];
				SP--;
			}
			break;

		case SUB:
			PC++;
			if ( SP >= 1 )
			{

				stack[ SP - 2 ] = stack[ SP - 2 ] - stack[ SP - 1 ];
				SP--;
			}
			break;

		case MUL:
			PC++;
			if ( SP >= 1 )
			{

				stack[ SP - 2 ] = stack[ SP - 2 ] * stack[ SP - 1 ];
				SP--;
			}
			break;

		case DIV:
		{
			PC++;
			if ( SP >= 1 )
			{

				stack[ SP - 2 ] = stack[ SP - 2 ] / stack[ SP - 1 ];
				SP--;
			}
		}
		break;

		case MOD:
		{
		}
		break;


		case IFEQ:
		{
			PC++;

			nParameter = GetParameterIntFromCS( PC );
			PC += 4;

			int nSPValue = stack[ SP ];
			if ( nSPValue == 0 )
				PC += nParameter;
		}
		break;
		case IFNE:
		{
			PC++;

			nParameter = GetParameterIntFromCS( PC );
			PC += 4;

			int nSPValue = stack[ SP ];
			if ( nSPValue != 0 )
				PC += nParameter;
		}
		break;

		case LOAD_LOCAL:		//局部变量	
		{
		}
		break;

		case LOAD_STATIC:	//局部变量
		{
			PC++;


			//得到索引
			nParameter = GetParameterIntFromCS( PC );
			dParameter = GetParameterFloatFromDS( nParameter );
			PC += sizeof( int );

			if ( m_nStackLength<SP + 1 )
				malloc_stack( SP + 1 );
			stack[ SP ] = dParameter;
			SP++;
		}
		break;

		case STORE_STATIC:	//静态变量
		{
		}
		break;

		case STORE_LOCAL:	//静态变量
		{
		}
		break;

		case NOP:
			PC++;
			break;

		case SYS_CALL:
		{
			PC++;
			int n = GetParameterIntFromCS( PC );
			PC += sizeof( int );

			switch ( n )
			{

			case SYSFUNC_abs:
				//(double x) 
				//返回整型参数i的绝对值
				break;

			case SYSFUNC_exp:
				//(double x)			
				//返回指数函数ex的值
				break;

			case SYSFUNC_frexp:
				//(double value,int *eptr)	
				//返回value=x*2n中x的值,n存贮在eptr中
				break;

			case SYSFUNC_ldexp:
				//(double value,int exp)	
				//返回value*2exp的值
				break;

			case SYSFUNC_log:
				//(double x)				
				//返回logex的值
				break;

			case SYSFUNC_log10:
				//(double x)				
				//返回log10x的值
				break;

			case SYSFUNC_pow:
				//(double x,double y)		
				//返回xy的值
			{
				double dParameter1 = stack[ SP-- ];
				double dParameter2 = stack[ SP ];
				stack[ SP ] = pow( dParameter2, dParameter1 );
			}
			break;

			case SYSFUNC_pow10:
				//(int p)					
				//返回10p的值
				break;

			case SYSFUNC_sqrt:
				//(double x)			
				//返回+√x的值
				break;

			case SYSFUNC_acos:
				//(double x)			
				//返回x的反余弦cos-1(x)值,x为弧度
				break;

			case SYSFUNC_asin:
				//(double x)			
				//返回x的反正弦sin-1(x)值,x为弧度
				break;

			case SYSFUNC_atan:
				//(double x)			
				//返回x的反正切tan-1(x)值,x为弧度
				break;

			case SYSFUNC_atan2:
				//(double y,double x)	
				//返回y/x的反正切tan-1(x)值,y的x为弧度
				break;

			case SYSFUNC_cos:
				//(double x)			
				//返回x的余弦cos(x)值,x为弧度
				stack[ SP ] = sin( stack[ SP ] );
				break;

			case SYSFUNC_sin:
				//(double x)			
				//返回x的正弦sin(x)值,x为弧度
				stack[ SP ] = sin( stack[ SP ] );
				break;

			case SYSFUNC_tan:
				//(double x)			
				//返回x的正切tan(x)值,x为弧度
				break;

			case SYSFUNC_cosh:
				//(double x)			
				//返回x的双曲余弦cosh(x)值,x为弧度
				break;

			case SYSFUNC_sinh:
				//(double x)			
				//返回x的双曲正弦sinh(x)值,x为弧度
				break;

			case SYSFUNC_tanh:
				//(double x)			
				//返回x的双曲正切tanh(x)值,x为弧度
				break;

			case SYSFUNC_hypot:
				//(double x,double y)	
				//返回直角三角形斜边的长度(z),x和y为直角边的长度,z2=x2+y2
				break;

			case SYSFUNC_ceil:
				//(double x)			
				//返回不小于x的最小整数
				break;

			case SYSFUNC_floor:
				//(double x)			
				//返回不大于x的最大整数
				break;

			case SYSFUNC_rand:
				//()					
				//产生一个随机数并返回这个数
				break;

			case SYSFUNC_fmod:
				//(double x,double y)	
				//返回x/y的余数
				break;

			case SYSFUNC_UNKNOWN:
			default:

				break;
			}
		}

		break;

		case HALT:
		{
			if ( SP == 1 )
			{
				m_dVal = stack[ 0 ];
				m_bResult = true;
				goto engine_success;

			}
			else
			{
				goto engine_error_failed;
			}


		}
		break;


		default:
			goto engine_error_unknown_instruction;
		}
	}

engine_success:


	return VM_SUCCESS;

engine_error_unknown_instruction:
	return VM_E_INSTRUCTION;

engine_error_failed:

	return VM_E_RESULT_STACK;
}


bool VM::GetResult( double &dVal )
{
	dVal = m_dVal;
	return m_bResult;
}