#pragma once
#include "../ISA/instructions.h"
using namespace AVSVM_ISA;

#include <string>
#include <vector>
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

		void malloc_CS(int new_size);
		void malloc_DS(int new_size);
		void malloc_stack(int new_size);

	

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
		bool Check(const char* pstrBytecodesFileName);
		bool Check();


		///////////////////////////////////////////////////////////////
		//ִ������
	public:
		int Run();

	private:
		//�޲���
		int runNOP();				//�޲���

		//���ؾֲ�����
		int RunLOCALLOAD();		//���ؾֲ�����,����ֲ���������
		int RunLOCALLOAD0();		//���ؾֲ�����0
		int RunLOCALLOAD1();		//���ؾֲ�����1

		//���浽�ֲ�����
		int RunLOCALSTORE();		//���浽�ֲ�����,����ֲ���������
		int RunLOCALSTORE0();		//���浽�ֲ�����0
		int RunLOCALSTORE1();		//���浽�ֲ�����1

		//ȫ�ֱ��������뱣��
		int RunGLOBALLOAD();		//ȫ��/��̬����
		int RunGLOBALSTORE();		//ȫ�־�̬����

		//ջ����
		int RunPUSH();			//ѹջ
		int RunPOP();				//��ջ
		int RunDUP();			//����ջ��
		int RunSWAP();			//����ջ���ʹ�ջ��

		int RunADD();			//������
		int RunSUB();			//������
		int RunMUL();			//������
		int RunDIV();			//������
		int RunMOD();			//����ģ


		//������ָ֧��
		int RunIFEQ();			//������
		int RunIFNE();			//�������


		//����
		int RunNEW();			//�½�����

		//��������
		int RunRETURN();			//��������
		int RunCALL();			//��������	
		int RunSYS_CALL();		//ϵͳ����
		int RunHALT();			//ͣ��




	protected:
		int PC;		//PC�Ĵ���
		int BP;		//BP�Ĵ���
		unsigned int SP;				//SP�Ĵ���

		unsigned char* DS;	//DS��������
		unsigned char* CS;	//CS,����ֽ���
		int m_nCSLength;
		int m_nDSLength;

		vector<VMStack> stack;			//ջ
		int m_nStackLength;

	public:
		bool GetResult(double& dVal);
	private:
		double m_dVal;	//���
		bool m_bResult;	//����Ƿ���ȷ
	};


}