#pragma once
#include "../ISA/instructions.h"
using namespace AVSVM_ISA;

//值栈最大值
#define STACK_MAX 256


//方法区最大值
#define MethodBufferMax 32

//数据区最大值
#define StaticDataBufferMax 256

namespace AVSVM_VM
{
	class VM
	{
	public:
		VM( );
		~VM( );

	protected:
		int DeleteVM( );

		//初始化虚拟机
		int InitVM( );

		void malloc_CS( int new_size );
		void malloc_DS( int new_size );
		void malloc_stack( int new_size );

	public:
		///////////////////////////////////////////////////////////////
		//产生代码
		void Gen_OP( INSTRUCTIONS op );
		void Gen_OP( INSTRUCTIONS op, int n );
		void Gen_OP( INSTRUCTIONS op, double f );
	private:
		//代码索引
		int m_nGenCSIndex;
		int m_nGenDSIndex;

		//数据区
	public:
		void SetVar( double f, int nIndex );

		//调试
#ifdef _DEBUG
	public:
		void DumpBin( );
#endif

		///////////////////////////////////////////////////////////////
		//程序校验
		bool Check( const char *pstrBytecodesFileName );
		bool Check( );

		//取得方法区中指定位置的整数值
		int GetParameterIntFromCS( int nIndex );
		double GetParameterFloatFromCS( int nIndex );
		int GetParameterIntFromDS( int nIndex );
		double GetParameterFloatFromDS( int nIndex );



		

		

	protected:
		int PC;		//PC寄存器
		int BP;		//BP寄存器
		unsigned int SP;				//SP寄存器

		double *DS;	//DS，数据区
		char *CS;		//CS,存放字节码
		int m_nCSLength;
		int m_nDSLength;

		double *stack;			//栈
		int m_nStackLength;

	public:
		bool GetResult( double &dVal );
	private:
		double m_dVal;	//结果
		bool m_bResult;	//结果是否正确
	};


}