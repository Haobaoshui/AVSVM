#pragma once
#include "../ISA/instructions.h"
using namespace AVSVM_ISA;

//ֵջ���ֵ
#define STACK_MAX 256


//���������ֵ
#define MethodBufferMax 32

//���������ֵ
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

		//��ʼ�������
		int InitVM( );

		void malloc_CS( int new_size );
		void malloc_DS( int new_size );
		void malloc_stack( int new_size );

	public:
		///////////////////////////////////////////////////////////////
		//��������
		void Gen_OP( INSTRUCTIONS op );
		void Gen_OP( INSTRUCTIONS op, int n );
		void Gen_OP( INSTRUCTIONS op, double f );
	private:
		//��������
		int m_nGenCSIndex;
		int m_nGenDSIndex;

		//������
	public:
		void SetVar( double f, int nIndex );

		//����
#ifdef _DEBUG
	public:
		void DumpBin( );
#endif

		///////////////////////////////////////////////////////////////
		//����У��
		bool Check( const char *pstrBytecodesFileName );
		bool Check( );

		//ȡ�÷�������ָ��λ�õ�����ֵ
		int GetParameterIntFromCS( int nIndex );
		double GetParameterFloatFromCS( int nIndex );
		int GetParameterIntFromDS( int nIndex );
		double GetParameterFloatFromDS( int nIndex );



		

		

	protected:
		int PC;		//PC�Ĵ���
		int BP;		//BP�Ĵ���
		unsigned int SP;				//SP�Ĵ���

		double *DS;	//DS��������
		char *CS;		//CS,����ֽ���
		int m_nCSLength;
		int m_nDSLength;

		double *stack;			//ջ
		int m_nStackLength;

	public:
		bool GetResult( double &dVal );
	private:
		double m_dVal;	//���
		bool m_bResult;	//����Ƿ���ȷ
	};


}