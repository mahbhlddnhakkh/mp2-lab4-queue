// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
//
//
//

#ifndef __TQueue_H__
#define __TQueue_H__

#include <iostream>

const size_t MAX_QUEUE_SIZE = 100000000;

template <typename T>
class TQueue
{
protected:
	T* pMem;
	size_t MemSize;
	size_t Hi;
	size_t Li;
	size_t DataCount;
	const static size_t unzero = ~0;
public:
	TQueue(size_t sz = 10);
	TQueue(const TQueue& q);
	TQueue(TQueue&& q) noexcept;
	TQueue& operator=(const TQueue& q);
	TQueue& operator=(TQueue&& q) noexcept;
	~TQueue();

	bool IsEmpty(void) const noexcept;
	bool IsFull(void) const noexcept;

	void Free(void) noexcept;
	void Push(const T& e);
	T Top(void) const;
	void Pop(void);
	T TopPop(void);

	bool operator==(const TQueue& q) const noexcept;
	bool operator!=(const TQueue& q) const noexcept;
};

template<typename T>
inline TQueue<T>::TQueue(size_t sz) : Hi(0), Li(0), pMem(nullptr), DataCount(0)
{
	if (sz == 0)
		throw std::out_of_range("Queue size should be greater than zero");
	if (sz > MAX_QUEUE_SIZE)
		throw std::out_of_range("Queue size should be less than MAX_QUEUE_SIZE");
	MemSize = sz;
	pMem = new T[MemSize];
}

template<typename T>
inline TQueue<T>::TQueue(const TQueue<T>& q)
{
	if (q.pMem == nullptr)
	{
		MemSize = 0;
		pMem = nullptr;
		Free();
	}
	else
	{
		MemSize = q.MemSize;
		Hi = q.Hi;
		Li = q.Li;
		DataCount = q.DataCount;
		pMem = new T[MemSize];
		if (!(q.IsEmpty()))
		{
			size_t j = Hi;
			for (size_t i = 0; i < DataCount; i++)
			{
				pMem[j] = q.pMem[j];
				j--;
				if (j == unzero)
					j = MemSize - 1;
			}
		}
	}
}

template<typename T>
inline TQueue<T>::TQueue(TQueue<T>&& q) noexcept
{
	this->operator=(q);
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
	if (this == &q)
		return *this;
	if (MemSize != q.MemSize)
	{
		T* tmp = new T[q.MemSize];
		delete[] pMem;
		MemSize = q.MemSize;
		pMem = tmp;
	}
	Hi = q.Hi;
	Li = q.Li;
	DataCount = q.DataCount;
	if (!(q.IsEmpty()))
	{
		size_t j = Hi;
		for (size_t i = 0; i < DataCount; i++)
		{
			pMem[j] = q.pMem[j];
			j--;
			if (j == unzero)
				j = MemSize - 1;
		}
	}
	return *this;
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(TQueue<T>&& q) noexcept
{
	pMem = nullptr;
	MemSize = 0;
	Free();
	std::swap(pMem, q.pMem);
	std::swap(MemSize, q.MemSize);
	std::swap(Hi, q.Hi);
	std::swap(Li, q.Li);
	std::swap(DataCount, q.DataCount);
	return *this;
}

template<typename T>
inline TQueue<T>::~TQueue()
{
	delete[] pMem;
	MemSize = 0;
	Free();
}

template<typename T>
inline bool TQueue<T>::IsEmpty(void) const noexcept
{
	return DataCount == 0;
}

template<typename T>
inline bool TQueue<T>::IsFull(void) const noexcept
{
	return DataCount == MemSize;
}

template<typename T>
inline void TQueue<T>::Free(void) noexcept
{
	Hi = 0;
	Li = 0;
	DataCount = 0;
}

template<typename T>
inline void TQueue<T>::Push(const T& e)
{
	if (IsFull())
		throw std::out_of_range("Queue is full");
	pMem[Li] = e;
	//Li = (Li + 1) % MemSize;
	Li++;
	Li = (Li < MemSize) ? Li : 0; // : Li - MemSize; // Но Li - MemSize всегда 0.
	DataCount++;
}

template<typename T>
inline T TQueue<T>::Top(void) const
{
	if (IsEmpty())
		throw "Queue is empty";
	return pMem[Hi];
}

template<typename T>
inline void TQueue<T>::Pop(void)
{
	if (IsEmpty())
		throw "Queue is empty";
	//Hi = (Hi + 1) % MemSize;
	Hi++;
	Hi = (Hi < MemSize) ? Hi : 0; // : Hi - MemSize; // Но Hi - MemSize всегда 0.
	DataCount--;
}

template<typename T>
inline T TQueue<T>::TopPop(void)
{
	T tmp = Top();
	Pop();
	return tmp;
}

template<typename T>
inline bool TQueue<T>::operator==(const TQueue& q) const noexcept
{
	if (DataCount != q.DataCount)
		return false;
	size_t j = Hi, k = q.Hi;
	for (size_t i = 0; i < DataCount; i++)
	{
		if (pMem[j] != q.pMem[k])
			return false;
		j--;
		if (j == unzero)
			j = MemSize - 1;
		k--;
		if (k == unzero)
			k = q.MemSize - 1;
	}
	return true;
}

template<typename T>
inline bool TQueue<T>::operator!=(const TQueue& q) const noexcept
{
	return !(this->operator==(q));
}

#endif