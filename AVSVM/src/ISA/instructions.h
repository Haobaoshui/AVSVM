#pragma once
namespace AVSVM_ISA
{
	typedef unsigned char INSTRUCTIONS;

	const INSTRUCTIONS NOP = 0;				//�޲���

	//���ؾֲ�����
	const INSTRUCTIONS LOCALLOAD = 1;		//���ؾֲ�����,����ֲ���������
	const INSTRUCTIONS LOCALLOAD0 = 2;		//���ؾֲ�����0
	const INSTRUCTIONS LOCALLOAD1 = 3;		//���ؾֲ�����1

	//���浽�ֲ�����
	const INSTRUCTIONS LOCALSTORE = 4;		//���浽�ֲ�����,����ֲ���������
	const INSTRUCTIONS LOCALSTORE0 = 5;		//���浽�ֲ�����0
	const INSTRUCTIONS LOCALSTORE1 = 6;		//���浽�ֲ�����1

	//ȫ�ֱ��������뱣��
	const INSTRUCTIONS GLOBALLOAD = 7;		//ȫ��/��̬����
	const INSTRUCTIONS GLOBALSTORE = 8;		//ȫ�־�̬����

	//ջ����
	const INSTRUCTIONS PUSH = 9;			//ѹջ
	const INSTRUCTIONS POP = 10;				//��ջ
	const INSTRUCTIONS DUP = 11;			//����ջ��
	const INSTRUCTIONS SWAP = 12;			//����ջ���ʹ�ջ��

	const INSTRUCTIONS ADD = 13;			//������
	const INSTRUCTIONS SUB = 14;			//������
	const INSTRUCTIONS MUL = 15;			//������
	const INSTRUCTIONS DIV = 16;			//������
	const INSTRUCTIONS MOD = 17;			//����ģ
		

	//������ָ֧��
	const INSTRUCTIONS IFEQ = 18;			//������
	const INSTRUCTIONS IFNE = 19;			//�������


	//����
	const INSTRUCTIONS NEW = 20;			//�½�����

	//��������
	const INSTRUCTIONS RETURN = 21;			//��������
	const INSTRUCTIONS CALL = 22;			//��������

	/*
	ϵͳ�������ã�����sin,cos,...
	��ʽ��
	Parameter
	SYSCALL nType(4bytes)
	ע�⣺����������SYSCALLָ��ǰ��
	*/
	const INSTRUCTIONS SYS_CALL = 23;		//ϵͳ����

	
	const INSTRUCTIONS HALT = 24;			//ͣ��


	//ϵͳ����
	typedef enum tagVM_SYSFUNC
	{
		SYSFUNC_abs,		//(double x)				�������Ͳ���i�ľ���ֵ
		SYSFUNC_exp,		//(double x)				����ָ������ex��ֵ
		SYSFUNC_frexp,		//(double value,int *eptr)	����value=x*2n��x��ֵ,n������eptr��
		SYSFUNC_ldexp,		//(double value,int exp)	����value*2exp��ֵ
		SYSFUNC_log,		//(double x)				����logex��ֵ
		SYSFUNC_log10,		//(double x)				����log10x��ֵ
		SYSFUNC_pow,		//(double x,double y)		����xy��ֵ
		SYSFUNC_pow10,		//(int p)					����10p��ֵ
		SYSFUNC_sqrt,		//(double x)				����+��x��ֵ
		SYSFUNC_acos,		//(double x)				����x�ķ�����cos-1(x)ֵ,xΪ����
		SYSFUNC_asin,		//(double x)				����x�ķ�����sin-1(x)ֵ,xΪ����
		SYSFUNC_atan,		//(double x)				����x�ķ�����tan-1(x)ֵ,xΪ����
		SYSFUNC_atan2,		//(double y,double x)		����y/x�ķ�����tan-1(x)ֵ,y��xΪ����
		SYSFUNC_cos,		//(double x)				����x������cos(x)ֵ,xΪ����
		SYSFUNC_sin,		//(double x)				����x������sin(x)ֵ,xΪ����
		SYSFUNC_tan,		//(double x)				����x������tan(x)ֵ,xΪ����
		SYSFUNC_cosh,		//(double x)				����x��˫������cosh(x)ֵ,xΪ����
		SYSFUNC_sinh,		//(double x)				����x��˫������sinh(x)ֵ,xΪ����
		SYSFUNC_tanh,		//(double x)				����x��˫������tanh(x)ֵ,xΪ����
		SYSFUNC_hypot,		//(double x,double y)		����ֱ��������б�ߵĳ���(z),x��yΪֱ�Ǳߵĳ���,z2=x2+y2
		SYSFUNC_ceil,		//(double x)				���ز�С��x����С����
		SYSFUNC_floor,		//(double x)				���ز�����x���������
		SYSFUNC_rand,		//()						����һ������������������
		SYSFUNC_fmod,		//(double x,double y)		����x/y������
		SYSFUNC_UNKNOWN

	} VM_SYSFUNC;


}

