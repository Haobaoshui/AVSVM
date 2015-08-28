#pragma once
namespace AVSVM_ISA
{
	typedef unsigned char INSTRUCTIONS;

	//ָ��
	const INSTRUCTIONS LOCALLOAD = 0;		//�ֲ�����
	const INSTRUCTIONS LOCALLOAD0 = 1;		//
	const INSTRUCTIONS LOCALLOAD1 = 2;		//

	const INSTRUCTIONS LOCALSTORE = 3;		//�ֲ�����
	const INSTRUCTIONS LOCALSTORE0 = 4;		//
	const INSTRUCTIONS LOCALSTORE1 = 5;		//

	const INSTRUCTIONS GLOBALLOAD = 6;		//ȫ��/��̬����
	const INSTRUCTIONS GLOBALSTORE = 7;	//ȫ�־�̬����

	//ջ����
	const INSTRUCTIONS PUSH = 8;			//
	const INSTRUCTIONS POP = 9;			//
	const INSTRUCTIONS DUP = 10;			//
	const INSTRUCTIONS SWAP = 11;			//

	const INSTRUCTIONS INTADD = 12;			//��
	const INSTRUCTIONS INTSUB = 13;			//��
	const INSTRUCTIONS INTMUL = 14;			//��
	const INSTRUCTIONS INTDIV = 15;			//��
	const INSTRUCTIONS INTMOD = 16;			//ģ

	const INSTRUCTIONS FLOATADD = 17;			//
	const INSTRUCTIONS FLOATSUB = 18;			//
	const INSTRUCTIONS FLOATMUL = 19;			//
	const INSTRUCTIONS FLOATDIV = 20;			//

	//������ָ֧��
	const INSTRUCTIONS IFEQ = 21;			//������
	const INSTRUCTIONS IFNE = 22;			//�������


	const INSTRUCTIONS NEW = 23;			//

	const INSTRUCTIONS RETURN = 24;			//
	const INSTRUCTIONS CALL = 25;			//

	/*
	ϵͳ�������ã�����sin,cos,...
	��ʽ��
	Parameter
	SYSCALL nType(4bytes)
	ע�⣺����������SYSCALLָ��ǰ��
	*/
	const INSTRUCTIONS SYS_CALL = 26;

	const INSTRUCTIONS NOP = 27;			//�޲���
	const INSTRUCTIONS HALT = 28;			//ͣ��


	//ϵͳ����
	typedef enum tagVM_SYSFUNC
	{
		SYSFUNC_abs,		//(double x)			�������Ͳ���i�ľ���ֵ
		SYSFUNC_exp,		//(double x)			����ָ������ex��ֵ
		SYSFUNC_frexp,	//(double value,int *eptr)	����value=x*2n��x��ֵ,n������eptr��
		SYSFUNC_ldexp,	//(double value,int exp)	����value*2exp��ֵ
		SYSFUNC_log,		//(double x)				����logex��ֵ
		SYSFUNC_log10,	//(double x)				����log10x��ֵ
		SYSFUNC_pow,		//(double x,double y)		����xy��ֵ
		SYSFUNC_pow10,	//(int p)					����10p��ֵ
		SYSFUNC_sqrt,		//(double x)			����+��x��ֵ
		SYSFUNC_acos,		//(double x)			����x�ķ�����cos-1(x)ֵ,xΪ����
		SYSFUNC_asin,		//(double x)			����x�ķ�����sin-1(x)ֵ,xΪ����
		SYSFUNC_atan,		//(double x)			����x�ķ�����tan-1(x)ֵ,xΪ����
		SYSFUNC_atan2,	//(double y,double x)	����y/x�ķ�����tan-1(x)ֵ,y��xΪ����
		SYSFUNC_cos,		//(double x)			����x������cos(x)ֵ,xΪ����
		SYSFUNC_sin,		//(double x)			����x������sin(x)ֵ,xΪ����
		SYSFUNC_tan,		//(double x)			����x������tan(x)ֵ,xΪ����
		SYSFUNC_cosh,		//(double x)			����x��˫������cosh(x)ֵ,xΪ����
		SYSFUNC_sinh,		//(double x)			����x��˫������sinh(x)ֵ,xΪ����
		SYSFUNC_tanh,		//(double x)			����x��˫������tanh(x)ֵ,xΪ����
		SYSFUNC_hypot,	//(double x,double y)	����ֱ��������б�ߵĳ���(z),x��yΪֱ�Ǳߵĳ���,z2=x2+y2
		SYSFUNC_ceil,		//(double x)			���ز�С��x����С����
		SYSFUNC_floor,	//(double x)			���ز�����x���������
		SYSFUNC_rand,		//()					����һ������������������
		SYSFUNC_fmod,		//(double x,double y)	����x/y������
		SYSFUNC_UNKNOWN

	} VM_SYSFUNC;


}

