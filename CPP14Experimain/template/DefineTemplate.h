#pragma once
#include<iostream>
using namespace std;
//-----����ģ��------------------
/*
* �ȽϺ������Ż�
* ���º�������������Ϣ
* 1��������������const������ �����������ô���һ�ǲ������漰����������֧����const����
* 2����ģ��׶� ������Ĭ������ӵ�����в������������ص�<����� ���û�У������ʵ�����׶α���������
*/
template<typename T>
bool Compare(const T& a, const T& b)
{
	return a < b;
}

/*
* ������ģ�����
* 1��ʹ�÷�����ģ�������ʱ�����������һ������
* 2�������ڲ��������������ұ�ʶsize�Ĳ�����ģ�������ʱ��ſ�����ʽת��
*/
template<int a>
void NoTypeTemplate()
{
	cout << a << endl;
}
template<int i>
void NoTypeArrayTemplate(const int (&a)[i])
{
	for (auto val : a)
	{
		cout << val << endl;
	}
}
//------------------------------
//-----ģ����--------------------
/*
* ֵ��ע���������ģ���ʵ������ÿһ��ʵ�����Ƕ�������
* ��ͬʵ��֮�䲢û���κζ����Ȩ�ޣ���������ȫ����������һ���Ĺ�ϵ
* 
* һ����˵ʹ�����ģ�����Ҫ������ģ�����
* ���������Լ�ʹ�ÿ��Ժ��ԣ���reSelfFunc
* ��һ����ģ����������ڣ����ǿ���ֱ��ʹ��ģ����������ָ��ģ��ʵ��
*/
template<typename T>
class SampleTC
{
public:
	typedef T valuetype;
	T value;
	bool memFunc();
	SampleTC& reSelfFunc()
	{
		return *this;
	}
};

/*
* ������Ԫ��ģ���Ҫ����Ȼ�൫�ǲ���
* 1������Ҫ��������Ҫ������Ԫ��ϵ��ģ��
* 2�������ض����͵�ģ�彨����Ԫ Ҳ����ȫ�����Ͷ�������Ԫ��ϵ
* 3����һ��ģ���ÿһ��ʵ����������Ԫ���ж�Ӧ��ģ���������ʵ��ʱ���Բ���Ҫ����
*/
template<typename T>
class FriTF1;
template<typename T>
class FriTF2;

template<typename T>
class FriT
{
	friend class FriTF1<T>;
	friend class FriTF2<string>;
	template<typename X> friend class FriTF3;
private:
	T value;
};

template<typename T>
class FriTF1
{
public:
	void Func()
	{
		FriT<T> f;
		f.value = 10;
		cout << f.value << endl;
	}
};

template<typename T>
class FriTF2
{
public:
	void Func()
	{
		FriT<T> f;
		f.value = 'a';
		cout << f.value << endl;
	}
};
template<typename T>
class FriTF3
{
public:
	void Func()
	{
		FriT<string> f;
		f.value = "Hello World";
		cout << f.value << endl;
	}
};
/*
* �����н��ͣ�ÿ��ʵ�����Ƕ�������԰ɣ���ô���ں���Ҳ��
* ��ʵ�ֱ�������ض���ʵ����������Ҫʹ��template
*/
bool SampleTC<int>::memFunc()
{
	return true;
}
template<typename T>
bool SampleTC<T>::memFunc()
{
	return false;
}
//------------------------------
//-----ģ�����------------------
/*
* 1��ģ����������ֱ��ʾ��Ǹ�ռλ��������ʹ����������
* 2��ģ�������ѭһ����������򣬻������������������֣�����ģ���������Ա�����
* 3��ģ��������������ģ�����
* 4��ģ��ͬ��������Ĭ��ʵ�Σ��ر��ǿ���Ĭ�ϵ�ָ��ģ��ʹ�õ�����
*/
//------------------------------
//-----��Աģ��------------------
/*
* ��ν��Աģ��:һ�����������������ģ��ĳ�Ա���������Ա��������Աģ��
* ���ʲ���
* 1����ģ��������������ʹ��ģ�� ���ⲿ����Ҳֻ��Ҫ����һ��ģ��
* 2��ģ�������ⲿ����ʱ��Ҫ����һ��ģ������ָʾ�࣬����Ҫһ��ģ������ģ���Ա����Ȼ����ֱ��ָ���̶���
*/
//------------------------------
//-----����ʵ����-----------------
/*
* ģ���ڱ�ʹ�õ�ʱ��Ż�ʵ����
* ���Ƕ���ط�ʹ��ģ����ܻ��ж��ʵ����
* Ϊ�˱������ظ�ʵ�������¹�������ʾʵ����
* ��νʵ�����������Ǽ���extern�ؼ��ֱ�ʾ��ĳ���ط����䶨��
* ʹ����ʵ���������ͱ�������ʵ�������� �ڶ���ǰ����template�ؼ��ּ���
* ��ʽ: 
* extern template declaration;
* template declaration;
*/
template<typename T>			
void etFunc();							//�����亯��
extern template void etFunc<int>();		//ʵ��������
template void etFunc<int>();			//��ʾʵ���� ����Ķ����������ʵ���Żᱻ��������
template<typename T>					//���� ���������Ϲ����Ƿֿ��ģ�ȷ���ж��弴��
void etFunc<int>()
{
	cout << "etf" << endl;
}
//------------------------------

int main()
{
	const int ci = 10;
	const int i = 5;
	const int arr[5] = { 1,2,3,4,5 };
	Compare(ci, i);				//��ʽ�ƶ�ģ������

	
	NoTypeTemplate<ci>();		//��ȷ ������ģ����������ǳ���
	//NoTypeTemplate<c>();		//���� ��������Ǳ������ǳ���
	NoTypeArrayTemplate(arr);	//��ȷ ������Ψһ������ʽ�ƶϷ�����ģ������Ĳ���

	SampleTC<int> stci;
	SampleTC<int>::valuetype stcii = 5;
	stci.value = stcii;
	SampleTC<char> stcc;		//������Գ�Ա������ʵ�� ����int�������ģ�崦�� �������Ͷ���false
	cout << "stci:" << stci.memFunc() << "stcc:" << stcc.memFunc() << endl;
	cout << stci.reSelfFunc().value << endl;

	FriTF1<int> f1;				//��ȷ �������ͬ����������Ԫ��ϵ
	f1.Func();					//��������Ҫע����ͬ�����ͣ������ģ���������ض����;ͻ������
	FriTF2<string> f2;			//��ȷ ������������ض���Ԫ
	f2.Func();
	//FriTF2<bool> f3;			//���� ��Ϊֻ��Ԫ��string���͵�
	//f3.Func();
	FriTF3<int> f3;				//��ȷ ��Ȼ������int �ڲ�����string ���������Ԫ���������ʵ����
	f3.Func();					//����FriTF3���Է����������͵�FriT�ڵ�value
	etFunc<int>();
}