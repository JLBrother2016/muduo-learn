#include <stdio.h>

void foo(int x)
{
}

class B
{
public:
	virtual void foo()
	{
	}
};

class D : public B
{
public:
	void foo(int x)
	{
	}
};

template<typename To, typename From>
inline To implicit_cast(From const &f) { 	//隐式转换 
  return f;
}

int main(void)
{
	int n;
	double d = 1.23;
	n = d;

	B* pb;
	D* pd = NULL;

	pb = pd;
	pb = implicit_cast<B*, D*>(pd);  		//从D类(继承类转换为基类)B类
	return 0;
}
