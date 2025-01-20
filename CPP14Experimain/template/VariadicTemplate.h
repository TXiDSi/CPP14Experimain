#pragma once
#include<iostream>
#include<vector>
using namespace std;

//-----可变参数模板-----------------------------
/*
* 这里简略的介绍和使用
* 1、模板参数包
* 指的是模板参数中使用 ...name 来表示多参数的情况
* 2、函数参数包
* 和模板参数包类似，函数参数也可以使用 ...name 来表示多参数的情况
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