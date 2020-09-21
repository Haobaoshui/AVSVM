#pragma once
#include "../ISA/instructions.h"
using namespace AVSVM_ISA;

#include <string>

using namespace std;

#include "VMStack.h"

//ֵջ���ֵ
#define STACK_MAX 256


//���������ֵ
#define MethodBufferMax 32

//���������ֵ
#define StaticDataBufferMax 256

namespace AVSVM_VM
{
	const int VM_SUCCESS = 0;//ִ�гɹ�

		//ʧ��
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

		//��ʼ�������
		int InitVM();

		
	

	

	private:
		//��������
		int m_nGenCSIndex;
		int m_nGenDSIndex;

		//������
	public:
		void SetVar(double f, int nIndex);


		

		//ȡ�÷�������ָ��λ�õ�����ֵ
		int GetParameterIntFromCS(int nIndex);
		double GetParameterFloatFromCS(int nIndex);
		int GetParameterIntFromDS(int nIndex);
		double GetParameterFloatFromDS(int nIndex);

		///////////////////////////////////////////////////////////////
		//����
	public:		
		int LoadBytecodes(const wstring strBytecodesFileName/*�ֽ����ļ���*/);

	private:		
		void Gen_OP(INSTRUCTIONS op);
		void Gen_OP(INSTRUCTIONS op, int n);
		void Gen_OP(INSTRUCTIONS op, double f);

		///////////////////////////////////////////////////////////////
		//����У��
	public:		
		bool Validator(const wstring pstrBytecodesFileName);
		bool Validator();


		///////////////////////////////////////////////////////////////
		//ִ������
	public:
		int Run();

	




	protected:
		uint32_t PC;		//PC�Ĵ���
		uint32_t BP;		//BP�Ĵ���
		uint32_t SP;		//SP�Ĵ���

		unsigned char* DS;	//DS��������
		unsigned char* CS;	//CS,����ֽ���
		unsigned char* SS;	//SS,���ջ
		
		uint32_t m_nCSLength;
		uint32_t m_nDSLength;
		uint32_t m_nSSLength;


		void malloc_CS(uint32_t new_size);
		void malloc_DS(uint32_t new_size);
		void malloc_SS(uint32_t new_size);
		

	
		

	public:
		bool GetResult(double& dVal);
	private:
		double m_dVal;	//���
		bool m_bResult;	//����Ƿ���ȷ
	};


}