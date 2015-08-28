#include "stdafx.h"
#include "Engine.h"


Engine::Engine( )
{
}


Engine::~Engine( )
{
}


//ȡ�÷�������ָ��λ�õ�����ֵ
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
ִ������
�ֽ���֮ǰ�Ѿ���װ�ص���������
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
		//���ָ��
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

		case LOAD_LOCAL:		//�ֲ�����	
		{
		}
		break;

		case LOAD_STATIC:	//�ֲ�����
		{
			PC++;


			//�õ�����
			nParameter = GetParameterIntFromCS( PC );
			dParameter = GetParameterFloatFromDS( nParameter );
			PC += sizeof( int );

			if ( m_nStackLength<SP + 1 )
				malloc_stack( SP + 1 );
			stack[ SP ] = dParameter;
			SP++;
		}
		break;

		case STORE_STATIC:	//��̬����
		{
		}
		break;

		case STORE_LOCAL:	//��̬����
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
				//�������Ͳ���i�ľ���ֵ
				break;

			case SYSFUNC_exp:
				//(double x)			
				//����ָ������ex��ֵ
				break;

			case SYSFUNC_frexp:
				//(double value,int *eptr)	
				//����value=x*2n��x��ֵ,n������eptr��
				break;

			case SYSFUNC_ldexp:
				//(double value,int exp)	
				//����value*2exp��ֵ
				break;

			case SYSFUNC_log:
				//(double x)				
				//����logex��ֵ
				break;

			case SYSFUNC_log10:
				//(double x)				
				//����log10x��ֵ
				break;

			case SYSFUNC_pow:
				//(double x,double y)		
				//����xy��ֵ
			{
				double dParameter1 = stack[ SP-- ];
				double dParameter2 = stack[ SP ];
				stack[ SP ] = pow( dParameter2, dParameter1 );
			}
			break;

			case SYSFUNC_pow10:
				//(int p)					
				//����10p��ֵ
				break;

			case SYSFUNC_sqrt:
				//(double x)			
				//����+��x��ֵ
				break;

			case SYSFUNC_acos:
				//(double x)			
				//����x�ķ�����cos-1(x)ֵ,xΪ����
				break;

			case SYSFUNC_asin:
				//(double x)			
				//����x�ķ�����sin-1(x)ֵ,xΪ����
				break;

			case SYSFUNC_atan:
				//(double x)			
				//����x�ķ�����tan-1(x)ֵ,xΪ����
				break;

			case SYSFUNC_atan2:
				//(double y,double x)	
				//����y/x�ķ�����tan-1(x)ֵ,y��xΪ����
				break;

			case SYSFUNC_cos:
				//(double x)			
				//����x������cos(x)ֵ,xΪ����
				stack[ SP ] = sin( stack[ SP ] );
				break;

			case SYSFUNC_sin:
				//(double x)			
				//����x������sin(x)ֵ,xΪ����
				stack[ SP ] = sin( stack[ SP ] );
				break;

			case SYSFUNC_tan:
				//(double x)			
				//����x������tan(x)ֵ,xΪ����
				break;

			case SYSFUNC_cosh:
				//(double x)			
				//����x��˫������cosh(x)ֵ,xΪ����
				break;

			case SYSFUNC_sinh:
				//(double x)			
				//����x��˫������sinh(x)ֵ,xΪ����
				break;

			case SYSFUNC_tanh:
				//(double x)			
				//����x��˫������tanh(x)ֵ,xΪ����
				break;

			case SYSFUNC_hypot:
				//(double x,double y)	
				//����ֱ��������б�ߵĳ���(z),x��yΪֱ�Ǳߵĳ���,z2=x2+y2
				break;

			case SYSFUNC_ceil:
				//(double x)			
				//���ز�С��x����С����
				break;

			case SYSFUNC_floor:
				//(double x)			
				//���ز�����x���������
				break;

			case SYSFUNC_rand:
				//()					
				//����һ������������������
				break;

			case SYSFUNC_fmod:
				//(double x,double y)	
				//����x/y������
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