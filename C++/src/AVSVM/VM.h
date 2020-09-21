#pragma once
#include "../ISA/instructions.h"
using namespace AVSVM_ISA;

#include <string>

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
		bool Validator(const wstring pstrBytecodesFileName);
		bool Validator();


		///////////////////////////////////////////////////////////////
		//执行引擎
	public:
		int Run();

	




	protected:
		uint32_t PC;		//PC寄存器
		uint32_t BP;		//BP寄存器
		uint32_t SP;		//SP寄存器

		unsigned char* DS;	//DS，数据区
		unsigned char* CS;	//CS,存放字节码
		unsigned char* SS;	//SS,存放栈
		
		uint32_t m_nCSLength;
		uint32_t m_nDSLength;
		uint32_t m_nSSLength;


		void malloc_CS(uint32_t new_size);
		void malloc_DS(uint32_t new_size);
		void malloc_SS(uint32_t new_size);
		

	
		

	public:
		bool GetResult(double& dVal);
	private:
		double m_dVal;	//结果
		bool m_bResult;	//结果是否正确
	};


}