// VM.cpp : �������̨Ӧ�ó������ڵ㡣
//




#include <stdio.h>
#include <string.h>
#include <malloc.h>


#include "vm.h"


using namespace AVSVM_VM;

VM::VM()
{
	m_nCSLength = 0;
	CS = nullptr;

	m_nDSLength = 0;
	DS = nullptr;

	m_nSSLength = 0;
	SS = nullptr;
	

	m_nGenCSIndex = 0;
	m_nGenDSIndex = 0;

	m_bResult = false;

	InitVM();
}

VM::~VM()
{
	if (CS)
		free(CS);

	if (DS)
		free(DS);

	if (SS)
		free(SS);
}



//�ͷ�
int VM::DeleteVM()
{

	return VM_SUCCESS;
}

//��ʼ�������
int VM::InitVM()
{
	BP = 0;
	SP = 0;
	PC = 0;

	return VM_SUCCESS;
}

void VM::malloc_CS(int new_size)
{
	if (new_size < m_nCSLength)return;

	unsigned long size = m_nDSLength;
	if (size == 0)
		size = 1;

	while (size < new_size)
		size = size * 2;

	if (NULL == CS)
		CS = (unsigned char*)malloc(sizeof(char) * size);
	else
		CS = (unsigned char*)realloc(CS, sizeof(char) * size);

	m_nCSLength = size;
}


/*
new_size:DS��С��ÿ��Ԫ�ش�СΪsizeof(double)����ע��ô�С������ʵ���ڴ��С
*/
void VM::malloc_DS(int new_size)
{
	if (new_size < m_nDSLength)return;

	unsigned long size = m_nDSLength;
	if (size == 0)
		size = 1;

	while (size < new_size)
		size = size * 2;

	if (NULL == CS)
		DS = (unsigned char*)malloc(sizeof(char) * size);
	else
		DS = (unsigned char*)realloc(DS, sizeof(char) * size);

	m_nDSLength = size;
}

void AVSVM_VM::VM::malloc_SS(int new_size)
{
	if (new_size < m_nSSLength)return;

	unsigned long size = m_nSSLength;
	if (size == 0)
		size = 1;

	while (size < new_size)
		size = size * 2;

	if (NULL == CS)
		SS = (unsigned char*)malloc(sizeof(char) * size);
	else
		SS = (unsigned char*)realloc(SS, sizeof(char) * size);

	m_nSSLength = size;
}




void VM::Gen_OP(INSTRUCTIONS op)
{
	if (m_nCSLength < m_nGenCSIndex + 1)
		malloc_CS(m_nGenCSIndex + 1);

	CS[m_nGenCSIndex] = op;
	m_nGenCSIndex++;
}

void VM::Gen_OP(INSTRUCTIONS op, int n)
{
	if (m_nCSLength < m_nGenCSIndex + sizeof(int) + 1)
		malloc_CS(m_nGenCSIndex + sizeof(int) + 1);

	CS[m_nGenCSIndex] = op;
	m_nGenCSIndex++;

	*(CS + m_nGenCSIndex) = n;
	m_nGenCSIndex += sizeof(int);

}

void VM::Gen_OP(INSTRUCTIONS op, double f)
{
	if (m_nCSLength < m_nGenCSIndex + sizeof(double) + 1)
		malloc_CS(m_nGenCSIndex + sizeof(double) + 1);

	CS[m_nGenCSIndex] = op;
	m_nGenCSIndex++;

	*(CS + m_nGenCSIndex) = f;
	m_nGenCSIndex += sizeof(double);

}
bool AVSVM_VM::VM::Validator(const wstring pstrBytecodesFileName)
{
	return false;
}
bool AVSVM_VM::VM::Validator()
{
	return false;
}
void VM::SetVar(double f, int nIndex)
{
	if (nIndex < 0)
		return;

	if (m_nDSLength < nIndex + 1)
		malloc_DS(nIndex + 1);

	DS[nIndex] = f;
}







//ȡ�÷�������ָ��λ�õ�����ֵ
int VM::GetParameterIntFromCS(int nIndex)
{
	return (int)(*(CS + nIndex));
}
double VM::GetParameterFloatFromCS(int nIndex)
{
	return (double)(*(CS + nIndex));
}

int VM::GetParameterIntFromDS(int nIndex)
{
	return (int)(*(DS + nIndex));
}

double VM::GetParameterFloatFromDS(int nIndex)
{
	return (double)(*(DS + nIndex));
}




/*
ִ������
�ֽ���֮ǰ�Ѿ���װ�ص���������
*/
int VM::Run()
{
	BP = 0;
	SP = 0;
	PC = 0;

	m_bResult = false;

	int nParameter = 0;
	double dParameter = 0;

	for (;; )
	{
		//���ָ��
		INSTRUCTIONS op = *(CS + PC);

		switch (op)
		{
		case  NOP:				//�޲���
			PC++;
			break;

			//�����������͵ľֲ�������ջ��
		case  LOCAL_INT_LOAD:		//���ؾֲ�������ջ��,����ֲ���������
			PC++;

			//�õ�����
			nParameter = GetParameterIntFromCS(PC);
		//	dParameter = GetParameterFloatFromDS(nParameter);
			PC += PARAMETER_SIZE;//����Ϊ4���ֽ�

			
			malloc_SS(BP+SP);
			stack[SP] = dParameter;
			SP++;
			break;
		case  LOCAL_INT_LOAD_0:		//���ؾֲ�����1
			break;
		case  LOCAL_INT_LOAD_1:		//���ؾֲ�����2
			break;



			//���������͵�ջ��ֵ���浽�ֲ�����
			case LOCAL_INT_STORE:break;	//���浽�ֲ�����,����ֲ���������
			case LOCAL_INT_STORE_0:break;	//���浽�ֲ�����0��ջ��
			case LOCAL_INT_STORE_1:break;	//���浽�ֲ�����1��ջ��

			//�����������͵�ջ��ֵ���浽�ֲ�����
			case LOCAL_FLOAT_STORE:break;	//���浽�ֲ�����,����ֲ���������
			case LOCAL_FLOAT_STORE_0:break;	//��ջ��ֵ���浽�ֲ�����0
			case LOCAL_FLOAT_STORE_1:break;	//��ջ��ֵ���浽�ֲ�����1

			//���������͵�ȫ�ֱ������ص�ջ�����෴
			case LOAD_INT:break;	//ȫ��/��̬����
			case STORE_INT:break;	//��ջ��ֵ���浽ȫ�־�̬����

			//�����������͵�ȫ�ֱ������ص�ջ�����෴
			case LOAD_FLOAT:break;	//ȫ��/��̬����
			case STORE_FLOAT:break;	//��ջ��ֵ���浽ȫ�־�̬����

				//ջ����
			case  PUSH_INT:		//ѹջ
				PC++;
				dParameter = GetParameterFloatFromCS(PC);
				PC += sizeof(double);

				if (m_nStackLength < SP + 1)
					malloc_stack(SP + 1);
				stack[SP] = dParameter;
				SP++;				
				break;

			case  POP_INT:				//��ջ
				PC++;
				if (SP >= 0)
					SP--;
				break;


			case PUSH_FLOAT:break;	//������ѹջ�����4�ֽ���������
			case POP_FLOAT:break;	//��ջ���ĸ���ֵ��ջ

			case  DUP:		//����ջ��
				PC++;
				if (SP >= 0)
				{
					if (m_nStackLength < SP + 1)
						malloc_stack(SP + 1);

					stack[SP] = stack[SP - 1];
					SP++;
				}
				break;
			case  SWAP:			//����ջ���ʹ�ջ��
				PC++;
				if (SP >= 1 && SP < m_nStackLength)
				{
					int temp = stack[SP];
					stack[SP] = stack[SP - 1];
					stack[SP - 1] = temp;
				}
				break;

			case  INT_ADD:		//������
				PC++;
				if (SP >= 1)
				{
					stack[SP - 2] = stack[SP - 1] + stack[SP - 2];
					SP--;
				}
				break;
			case  INT_SUB:			//������
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] - stack[SP - 1];
					SP--;
				}
				break;
			case  INT_MUL:		//������
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] * stack[SP - 1];
					SP--;
				}
				break;
			case  INT_DIV:			//������
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] / stack[SP - 1];
					SP--;
				}
				break;
			case  INT_MOD:			//����ģ
				break;

			case FLOAT_ADD:break;	//��������
			case FLOAT_SUB:break;	//��������
			case FLOAT_MUL:break;	//��������
			case FLOAT_DIV:break;;	//��������

		

				//������ָ֧��
			case  IFEQ:			//������
				PC++;

				nParameter = GetParameterIntFromCS(PC);
				PC += 4;

				int nSPValue = stack[SP];
				if (nSPValue == 0)
					PC += nParameter;
				break;
			case  IFNE:			//�������
				PC++;

				nParameter = GetParameterIntFromCS(PC);
				PC += 4;

				int nSPValue = stack[SP];
				if (nSPValue != 0)
					PC += nParameter;
				break;


				//����
			case  NEW:		//�½�����
				break;

				//��������
			case  RETURN:			//��������
				break;
			case  CALL:			//��������
				break;

				/*
				ϵͳ�������ã�����sin,cos,...
				��ʽ��
				Parameter
				SYSCALL nType(4bytes)
				ע�⣺����������SYSCALLָ��ǰ��
				*/
			case  SYS_CALL :		//ϵͳ����
				PC++;
				int n = GetParameterIntFromCS(PC);
				PC += sizeof(int);

				switch (n)
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
					double dParameter1 = stack[SP--];
					double dParameter2 = stack[SP];
					stack[SP] = pow(dParameter2, dParameter1);
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
					stack[SP] = sin(stack[SP]);
					break;

				case SYSFUNC_sin:
					//(double x)			
					//����x������sin(x)ֵ,xΪ����
					stack[SP] = sin(stack[SP]);
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
				break;

				
				case  HALT :			//ͣ��
				if (SP == 1)
				{
					m_dVal = stack[0];
					m_bResult = true;
					goto engine_success;

				}
				else
				{
					goto engine_error_failed;
				}
				break;

			default:
				goto engine_error_unknown_instruction;
		}
	}

	//ִ�гɹ�
engine_success:
	return VM_SUCCESS;

	//�Ƿ�ָ��
engine_error_unknown_instruction:
	return VM_E_INSTRUCTION;

	//ִ��ʧ��
engine_error_failed:

	return VM_E_RESULT_STACK;
}


bool VM::GetResult(double& dVal)
{
	dVal = m_dVal;
	return m_bResult;
}


/*
* �����ֽ����ļ�
*/
int VM::LoadBytecodes(const wstring strBytecodesFileName/*�ֽ����ļ���*/)
{
	if (strBytecodesFileName.empty())
		return VM_E_FILE_NOTEXIST;


	//1.���ֽ����ļ�
	FILE* pFileByteCode = fopen(strBytecodesFileName.c_str(), "rb");
	if (NULL == pFileByteCode)
		return VM_E_OPEN_FILENAME;

	//2.�����ļ�,��װ�ص��������С�
	if (fread(CS, sizeof(char), MethodBufferMax, pFileByteCode) == 0)
		goto error_read_bytecode;

	//3.�ر��ļ�
	fclose(pFileByteCode);
	return VM_SUCCESS;

error_read_bytecode:
	fclose(pFileByteCode);
	return VM_E_OPEN_FILENAME;
}