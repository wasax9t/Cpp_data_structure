#pragma once
class Fib {
private:
	int f, g;//fΪǰһ�gΪ��ǰ��
public:
	Fib(int n)
	{
		f = 1; g = 0; while (g < n) next();
	}
	int get() { return g; }
	int next() { g += f; f =g-f; return g; }
	int prev() { f = g - f; g -= g; return g; }
};