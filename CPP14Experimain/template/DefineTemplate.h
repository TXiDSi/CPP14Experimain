#pragma once
#include<iostream>
using namespace std;
//-----函数模板------------------
/*
* 比较函数的优化
* 如下函数包含两点信息
* 1、输入参数最好是const的引用 这样有两个好处，一是参数不涉及拷贝、二是支持了const类型
* 2、在模板阶段 编译器默认类型拥有所有操作，比如重载的<运算符 如果没有，则会在实例化阶段被检查出错误
*/
template<typename T>
bool Compare(const T& a, const T& b)
{
	return a < b;
}

/*
* 非类型模板参数
* 1、使用非类型模板参数的时候输入必须是一个常量
* 2、仅有在参数是数组类型且标识size的参数是模板参数的时候才可以隐式转换
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
//-----模板类--------------------
/*
* 值得注意的是在类模板的实例化后，每一个实例都是独立的类
* 不同实例之间并没有任何多余的权限，和两个完全独立的类是一样的关系
* 
* 一般来说使用类的模板必须要声明其模板参数
* 但是类内自己使用可以忽略，看reSelfFunc
* 在一个类模板的作用域内，我们可以直接使用模板名而不必指定模板实参
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
* 关于友元和模板的要点虽然多但是不难
* 1、首先要先声明想要建立友元关系的模板
* 2、可以特定类型的模板建立友元 也可以全部类型都存有友元关系
* 3、当一个模板的每一个实例都可以友元所有对应的模板类的所有实例时可以不需要声明
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
* 如上有解释，每个实例都是独立的类对吧，那么对于函数也是
* 其实现必须针对特定的实例，否则需要使用template
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
//-----模板参数------------------
/*
* 1、模板参数的名字本质就是个占位符，可以使用任意名字
* 2、模板参数遵循一般作用域规则，会隐藏外层作用域的名字，但是模板名不可以被隐藏
* 3、模板的声明必须包含模板参数
* 4、模板同样可以有默认实参，特别是可以默认的指定模板使用的类型
*/
//------------------------------
//-----成员模板------------------
/*
* 所谓成员模板:一个类其包含了自生是模板的成员函数，其成员被称作成员模板
* 本质不难
* 1、非模板类正常在类内使用模板 在外部声明也只需要声明一个模板
* 2、模板类在外部声明时需要声明一个模板用于指示类，还需要一个模板声明模板成员，当然可以直接指定固定类
*/
//------------------------------
//-----控制实例化-----------------
/*
* 模板在被使用的时候才会实例化
* 但是多个地方使用模板可能会有多个实例化
* 为了避免多个重复实例开销新规允许显示实例化
* 所谓实例化声明就是加上extern关键字表示在某个地方有其定义
* 使用了实例化声明就必须有其实例化定义 在定义前加上template关键字即可
* 格式: 
* extern template declaration;
* template declaration;
*/
template<typename T>			
void etFunc();							//声明其函数
extern template void etFunc<int>();		//实例化声明
template void etFunc<int>();			//显示实例化 下面的定义在这里的实例才会被真正定义
template<typename T>					//定义 定义与如上过程是分开的，确保有定义即可
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
	Compare(ci, i);				//隐式推断模板类型

	
	NoTypeTemplate<ci>();		//正确 非类型模板参数必须是常量
	//NoTypeTemplate<c>();		//错误 传入参数是变量不是常量
	NoTypeArrayTemplate(arr);	//正确 数组是唯一可以隐式推断非类型模板参数的参数

	SampleTC<int> stci;
	SampleTC<int>::valuetype stcii = 5;
	stci.value = stcii;
	SampleTC<char> stcc;		//这里测试成员函数的实现 除了int有特殊的模板处理 其余类型都是false
	cout << "stci:" << stci.memFunc() << "stcc:" << stcc.memFunc() << endl;
	cout << stci.reSelfFunc().value << endl;

	FriTF1<int> f1;				//正确 其针对其同等类型有友元关系
	f1.Func();					//但这里需要注意是同等类型，如果在模板内用了特定类型就会出问题
	FriTF2<string> f2;			//正确 针对其类型有特定友元
	f2.Func();
	//FriTF2<bool> f3;			//错误 因为只友元了string类型的
	//f3.Func();
	FriTF3<int> f3;				//正确 虽然这里是int 内部用了string 但是这个友元是针对所有实例的
	f3.Func();					//所以FriTF3可以访问所有类型的FriT内的value
	etFunc<int>();
}