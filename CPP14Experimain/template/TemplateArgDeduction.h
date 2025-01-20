#pragma once
#include<iostream>
#include<vector>
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
//-----函数模板显示实参-------------------------
/*
* 本质就是针对于可以隐式推断时有的部分不能判断的模板
*/
template<typename T1,typename T2,typename T3>
void deduFunc(T2 t1,T3 t2)
{
	cout << t1 << t2 << endl;
}
//--------------------------------------------
//-----尾置返回类型与类型转换--------------------
/*
* 当不能纯靠类型来推导返回类型的时候，可以使用尾置返回类型，这样至少可以用参数推断
*/
template<typename T>
auto rebackFunc(T beg, T end) -> decltype(*beg)
{
	return *beg;
}
//--------------------------------------------
//-----函数指针与实参推断------------------------
template<typename T>
T func(T a, T b)
{
	cout << a << endl;
	return a;
}

const int&(*fptr)(const int&, const int&) = func;
//--------------------------------------------
//-----模板实参推断和引用------------------------
/*
* 两条规则
* 1、当模板参数为右值引用时，如果传入左值会推断其为左值引用
* 2、存在多个引用符时会引用折叠 & &&->& | && &->& | && &&-> &&
*/

//证明其1、2 规则测试函数
template<typename T>
void deduTest(T &&t)
{
	t++;
}
//--------------------------------------------
//-----std::forward---------------------------
/*
* std::forward可以帮助我们保留右值信息
* 比如使用右值模板参数时，其对象本质还是左值，但是可以用forward获取其右值
*/
//接受右值的转发测试函数
void g(int&& t)
{
	cout << t << endl;
}
//模板函数
template<typename T>
void forwardFunc(T&& t)
{
	//g(t);		//错误的，即使传入右值但是t本质是左值
	g(std::forward<T>(t));	//正确
}


//--------------------------------------------
int main()
{
	deduFunc<int>("Hello", "World");					//正确，T1是显示的，T2，T3是隐式推断的

	vector<int> vec{ 1,2,3,4,5 };
	cout<<rebackFunc(vec.begin(), vec.end())<<endl;		//正确 返回类型是尾置推断的

	fptr(5, 6);											//正确 函数指针被模板赋值会自动推断模板
	
	//模板实参推断和引用
	//证明1&2
	int dedui = 5;
	deduTest(dedui);			//如果输出6的话说明这里传入的是引用 并且应用了折叠规则
	cout << dedui << endl;		//输出6

	//forward测试
	forwardFunc(5);


}