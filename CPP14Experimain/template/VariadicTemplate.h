#pragma once
#include<iostream>
#include<vector>
using namespace std;

//-----�ɱ����ģ��-----------------------------
/*
* ������ԵĽ��ܺ�ʹ��
* 1��ģ�������
* ָ����ģ�������ʹ�� ...name ����ʾ����������
* 2������������
* ��ģ����������ƣ���������Ҳ����ʹ�� ...name ����ʾ����������
*/
void SampleVarFunc()
{
}
template<typename T,typename ...Args>
void SampleVarFunc(T t, Args ...args)
{
	cout<<t<<endl;
	SampleVarFunc(args...);
}
//--------------------------------------------



int main()
{
	SampleVarFunc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}