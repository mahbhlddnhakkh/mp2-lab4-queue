// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// ������������ �������

#include <iostream>
#include "tqueue.h"

int main(int argc, char* argv[])
{
	TQueue<int> q(5);
	q.Push(12);
	std::cout << q.TopPop() << std::endl;
	q.Push(12);
	q.Push(13);
	q.Push(14);
	q.Pop();
	q.Push(15);
	std::cout << q.Top() << std::endl;
	q.Pop();
	q.Push(16);
	std::cout << q.Top() << std::endl;
	q.Push(5, 1);
	std::cout << q.Top() << std::endl;
	return 0;
}