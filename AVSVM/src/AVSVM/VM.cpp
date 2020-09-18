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
	CS = NULL;

	m_nDSLength = 0;
	DS = NULL;

	m_nStackLength = 0;
	stack = NULL;

	m_nGenCSIndex = 0;
	m_nGenDSIndex = 0;

	m_bResult = false;
}

VM::~VM()
{
	if (CS)
		free(CS);

	if (DS)
		free(DS);

	if (stack)
		free(stack);
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
	unsigned long size = m_nCSLength;
	if (size == 0)
		size = 1;
	while (size < new_size)
		size = size * 2;

	if (NULL == CS)
		CS = (char*)malloc(size);
	else
		CS = (char*)realloc(CS, size);

	m_nCSLength = size;
}


/*
new_size:DS��С��ÿ��Ԫ�ش�СΪsizeof(double)����ע��ô�С������ʵ���ڴ��С
*/
void VM::malloc_DS(int new_size)
{
	unsigned long size = m_nDSLength;
	if (size == 0)
		size = 1;

	while (size < new_size)
		size = size * 2;

	if (NULL == CS)
		DS = (double*)malloc(sizeof(double) * size);
	else
		DS = (double*)realloc(stack, sizeof(double) * size);

	m_nDSLength = size;
}


/*
new_size:ջ��С��ÿ��Ԫ�ش�СΪsizeof(double)����ע��ô�С������ʵ���ڴ��С
*/
void VM::malloc_stack(int new_size)
{
	unsigned long size = m_nStackLength;
	if (size == 0)
		size = 1;

	while (size < new_size)
		size = size * 2;

	if (NULL == CS)
		stack = (double*)malloc(sizeof(double) * size);
	else
		stack = (double*)realloc(stack, sizeof(double) * size);

	m_nStackLength = size;
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
			runNOP();
			break;

			
		case  LOCALLOAD:		//���ؾֲ�����0
			PC++;

			//�õ�����
			nParameter = GetParameterIntFromCS(PC);
			dParameter = GetParameterFloatFromDS(nParameter);
			PC += sizeof(int);

			if (m_nStackLength < SP + 1)
				malloc_stack(SP + 1);
			stack[SP] = dParameter;
			SP++;
			break;
		case  LOCALLOAD0:		//���ؾֲ�����1
			break;
		case  LOCALLOAD1:		//���ؾֲ�����2
			break;

		case  LOCALSTORE:		//���浽�ֲ�����0
			break;
		case  LOCALSTORE0:		//���浽�ֲ�����1
			break;
		case  LOCALSTORE1:		//���浽�ֲ�����2
			break;

			case GLOBALLOAD :		//ȫ��/��̬����
				break;
			case  GLOBALSTORE:		//ȫ�־�̬����
				break;

				//ջ����
			case  PUSH:		//ѹջ
				PC++;
				dParameter = GetParameterFloatFromCS(PC);
				PC += sizeof(double);

				if (m_nStackLength < SP + 1)
					malloc_stack(SP + 1);
				stack[SP] = dParameter;
				SP++;				
				break;

			case  POP:				//��ջ
				PC++;
				if (SP >= 0)
					SP--;
				break;
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

			case  ADD:		//������
				PC++;
				if (SP >= 1)
				{
					stack[SP - 2] = stack[SP - 1] + stack[SP - 2];
					SP--;
				}
				break;
			case  SUB:			//������
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] - stack[SP - 1];
					SP--;
				}
				break;
			case  MUL:		//������
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] * stack[SP - 1];
					SP--;
				}
				break;
			case  DIV:			//������
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] / stack[SP - 1];
					SP--;
				}
				break;
			case  MOD:			//����ģ
				break;

		

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

int AVSVM_VM::VM::runNOP()
{
	PC++;
	return 0;
}

int AVSVM_VM::VM::RunLOCALLOAD()
{
	return 0;
}

int AVSVM_VM::VM::RunLOCALLOAD0()
{
	return 0;
}

int AVSVM_VM::VM::RunLOCALLOAD1()
{
	return 0;
}

int AVSVM_VM::VM::RunLOCALSTORE()
{
	return 0;
}

int AVSVM_VM::VM::RunLOCALSTORE0()
{
	return 0;
}

int AVSVM_VM::VM::RunLOCALSTORE1()
{
	return 0;
}

int AVSVM_VM::VM::RunGLOBALLOAD()
{
	return 0;
}

int AVSVM_VM::VM::RunGLOBALSTORE()
{
	return 0;
}

int AVSVM_VM::VM::RunPUSH()
{
	return 0;
}

int AVSVM_VM::VM::RunPOP()
{
	return 0;
}

int AVSVM_VM::VM::RunDUP()
{
	return 0;
}

int AVSVM_VM::VM::RunSWAP()
{
	return 0;
}

int AVSVM_VM::VM::RunADD()
{
	return 0;
}

int AVSVM_VM::VM::RunSUB()
{
	return 0;
}

int AVSVM_VM::VM::RunMUL()
{
	return 0;
}

int AVSVM_VM::VM::RunDIV()
{
	return 0;
}

int AVSVM_VM::VM::RunMOD()
{
	return 0;
}

int AVSVM_VM::VM::RunIFEQ()
{
	return 0;
}

int AVSVM_VM::VM::RunIFNE()
{
	return 0;
}

int AVSVM_VM::VM::RunNEW()
{
	return 0;
}

int AVSVM_VM::VM::RunRETURN()
{
	return 0;
}

int AVSVM_VM::VM::RunCALL()
{
	return 0;
}


int AVSVM_VM::VM::RunSYS_CALL()
{
	return 0;
}

int AVSVM_VM::VM::RunHALT()
{
	return 0;
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