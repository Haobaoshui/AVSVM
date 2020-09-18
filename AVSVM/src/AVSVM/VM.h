#pragma once
#include "../ISA/instructions.h"
using namespace AVSVM_ISA;

#include <string>
#include <vector>
using namespace std;

#include "VMStack.h"

//值栈最大值
#define STACK_MAX 256


//方法区最大值
#define MethodBufferMax 32

//数据区最大值
#define StaticDataBufferMax 256

namespace AVSVM_VM
{
	const int VM_SUCCESS = 0;//执行成功

		//失败
	const int VM_E_INSTRUCTION = -1;
	const int VM_E_RESULT_STACK = -2;
	const int VM_E_FILE_NOTEXIST = -3;
	const int VM_E_OPEN_FILENAME = -4;


	class VM
	{
	public:
		VM();
		~VM();

	protected:
		int DeleteVM();

		//初始化虚拟机
		int InitVM();

		void malloc_CS(int new_size);
		void malloc_DS(int new_size);
		void malloc_stack(int new_size);

	

	private:
		//代码索引
		int m_nGenCSIndex;
		int m_nGenDSIndex;

		//数据区
	public:
		void SetVar(double f, int nIndex);


		

		//取得方法区中指定位置的整数值
		int GetParameterIntFromCS(int nIndex);
		double GetParameterFloatFromCS(int nIndex);
		int GetParameterIntFromDS(int nIndex);
		double GetParameterFloatFromDS(int nIndex);

		///////////////////////////////////////////////////////////////
		//加载
	public:		
		int LoadBytecodes(const wstring strBytecodesFileName/*字节码文件名*/);

	private:		
		void Gen_OP(INSTRUCTIONS op);
		void Gen_OP(INSTRUCTIONS op, int n);
		void Gen_OP(INSTRUCTIONS op, double f);

		///////////////////////////////////////////////////////////////
		//程序校验
	public:		
		bool Check(const char* pstrBytecodesFileName);
		bool Check();


		///////////////////////////////////////////////////////////////
		//执行引擎
	public:
		int Run();

	private:
		//无操作
		int runNOP();				//无操作

		//加载局部变量
		int RunLOCALLOAD();		//加载局部变量,后跟局部变量索引
		int RunLOCALLOAD0();		//加载局部变量0
		int RunLOCALLOAD1();		//加载局部变量1

		//保存到局部变量
		int RunLOCALSTORE();		//保存到局部变量,后跟局部变量索引
		int RunLOCALSTORE0();		//保存到局部变量0
		int RunLOCALSTORE1();		//保存到局部变量1

		//全局变量加载与保存
		int RunGLOBALLOAD();		//全局/静态变量
		int RunGLOBALSTORE();		//全局静态变量

		//栈操作
		int RunPUSH();			//压栈
		int RunPOP();				//弹栈
		int RunDUP();			//复制栈顶
		int RunSWAP();			//交换栈顶和次栈顶

		int RunADD();			//整数加
		int RunSUB();			//整数减
		int RunMUL();			//整数乘
		int RunDIV();			//整数除
		int RunMOD();			//整数模


		//条件分支指令
		int RunIFEQ();			//如果相等
		int RunIFNE();			//如果不等


		//对象
		int RunNEW();			//新建对象

		//函数调用
		int RunRETURN();			//函数返回
		int RunCALL();			//函数调用	
		int RunSYS_CALL();		//系统调用
		int RunHALT();			//停机




	protected:
		int PC;		//PC寄存器
		int BP;		//BP寄存器
		unsigned int SP;				//SP寄存器

		unsigned char* DS;	//DS，数据区
		unsigned char* CS;	//CS,存放字节码
		int m_nCSLength;
		int m_nDSLength;

		vector<VMStack> stack;			//栈
		int m_nStackLength;

	public:
		bool GetResult(double& dVal);
	private:
		double m_dVal;	//结果
		bool m_bResult;	//结果是否正确
	};


}