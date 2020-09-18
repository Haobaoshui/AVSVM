// VM.cpp : 定义控制台应用程序的入口点。
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



//释放
int VM::DeleteVM()
{




	return VM_SUCCESS;
}

//初始化虚拟机
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
new_size:DS大小（每个元素大小为sizeof(double)），注意该大小并不是实际内存大小
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
new_size:栈大小（每个元素大小为sizeof(double)），注意该大小并不是实际内存大小
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







//取得方法区中指定位置的整数值
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
执行引擎
字节码之前已经被装载到方法区中
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
		//获得指令
		INSTRUCTIONS op = *(CS + PC);

		switch (op)
		{
		case  NOP:				//无操作
			runNOP();
			break;

			
		case  LOCALLOAD:		//加载局部变量0
			PC++;

			//得到索引
			nParameter = GetParameterIntFromCS(PC);
			dParameter = GetParameterFloatFromDS(nParameter);
			PC += sizeof(int);

			if (m_nStackLength < SP + 1)
				malloc_stack(SP + 1);
			stack[SP] = dParameter;
			SP++;
			break;
		case  LOCALLOAD0:		//加载局部变量1
			break;
		case  LOCALLOAD1:		//加载局部变量2
			break;

		case  LOCALSTORE:		//保存到局部变量0
			break;
		case  LOCALSTORE0:		//保存到局部变量1
			break;
		case  LOCALSTORE1:		//保存到局部变量2
			break;

			case GLOBALLOAD :		//全局/静态变量
				break;
			case  GLOBALSTORE:		//全局静态变量
				break;

				//栈操作
			case  PUSH:		//压栈
				PC++;
				dParameter = GetParameterFloatFromCS(PC);
				PC += sizeof(double);

				if (m_nStackLength < SP + 1)
					malloc_stack(SP + 1);
				stack[SP] = dParameter;
				SP++;				
				break;

			case  POP:				//弹栈
				PC++;
				if (SP >= 0)
					SP--;
				break;
			case  DUP:		//复制栈顶
				PC++;
				if (SP >= 0)
				{
					if (m_nStackLength < SP + 1)
						malloc_stack(SP + 1);

					stack[SP] = stack[SP - 1];
					SP++;
				}
				break;
			case  SWAP:			//交换栈顶和次栈顶
				PC++;
				if (SP >= 1 && SP < m_nStackLength)
				{
					int temp = stack[SP];
					stack[SP] = stack[SP - 1];
					stack[SP - 1] = temp;
				}
				break;

			case  ADD:		//整数加
				PC++;
				if (SP >= 1)
				{
					stack[SP - 2] = stack[SP - 1] + stack[SP - 2];
					SP--;
				}
				break;
			case  SUB:			//整数减
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] - stack[SP - 1];
					SP--;
				}
				break;
			case  MUL:		//整数乘
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] * stack[SP - 1];
					SP--;
				}
				break;
			case  DIV:			//整数除
				PC++;
				if (SP >= 1)
				{

					stack[SP - 2] = stack[SP - 2] / stack[SP - 1];
					SP--;
				}
				break;
			case  MOD:			//整数模
				break;

		

				//条件分支指令
			case  IFEQ:			//如果相等
				PC++;

				nParameter = GetParameterIntFromCS(PC);
				PC += 4;

				int nSPValue = stack[SP];
				if (nSPValue == 0)
					PC += nParameter;
				break;
			case  IFNE:			//如果不等
				PC++;

				nParameter = GetParameterIntFromCS(PC);
				PC += 4;

				int nSPValue = stack[SP];
				if (nSPValue != 0)
					PC += nParameter;
				break;


				//对象
			case  NEW:		//新建对象
				break;

				//函数调用
			case  RETURN:			//函数返回
				break;
			case  CALL:			//函数调用
				break;

				/*
				系统函数调用，例如sin,cos,...
				形式：
				Parameter
				SYSCALL nType(4bytes)
				注意：函数参数在SYSCALL指令前面
				*/
			case  SYS_CALL :		//系统调用
				PC++;
				int n = GetParameterIntFromCS(PC);
				PC += sizeof(int);

				switch (n)
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
					double dParameter1 = stack[SP--];
					double dParameter2 = stack[SP];
					stack[SP] = pow(dParameter2, dParameter1);
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
					stack[SP] = sin(stack[SP]);
					break;

				case SYSFUNC_sin:
					//(double x)			
					//返回x的正弦sin(x)值,x为弧度
					stack[SP] = sin(stack[SP]);
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
				break;

				
				case  HALT :			//停机
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

	//执行成功
engine_success:
	return VM_SUCCESS;

	//非法指令
engine_error_unknown_instruction:
	return VM_E_INSTRUCTION;

	//执行失败
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
* 加载字节码文件
*/
int VM::LoadBytecodes(const wstring strBytecodesFileName/*字节码文件名*/)
{
	if (strBytecodesFileName.empty())
		return VM_E_FILE_NOTEXIST;


	//1.打开字节码文件
	FILE* pFileByteCode = fopen(strBytecodesFileName.c_str(), "rb");
	if (NULL == pFileByteCode)
		return VM_E_OPEN_FILENAME;

	//2.读入文件,并装载到方法区中。
	if (fread(CS, sizeof(char), MethodBufferMax, pFileByteCode) == 0)
		goto error_read_bytecode;

	//3.关闭文件
	fclose(pFileByteCode);
	return VM_SUCCESS;

error_read_bytecode:
	fclose(pFileByteCode);
	return VM_E_OPEN_FILENAME;
}