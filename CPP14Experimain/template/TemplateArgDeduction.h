#pragma once
#include<iostream>
using namespace std;
//-----类型转换与模板类型参数--------------------
/*
* 函数模板只能有两种情况的隐式转换
* 1、const转换：非const对象的引用或指针可以被转换为const的
* 2、数组与函数：数组可以转换成指向首对象的指针，函数可以转换成函数指针
* 其他类型包括：算数转换、派生类向基类转换、用户定义的转换 都不会发生 主要是你都泛型了这个还有的转吗
* 同理 如果参数不是泛型是正常参数的话 可以执行所有合理的隐式转换
*/
//--------------------------------------------

int main()
{

}