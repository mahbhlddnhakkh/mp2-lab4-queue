// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
//
//
//

#ifndef __TJobStream_H__
#define __TJobStream_H__

#include <cstdlib>

class TJobStream
{
private:
	double JobIntense;
	size_t LastJobId;
public:
	TJobStream(double JobIntens);
	double GetJobIntens(void) const noexcept;
	size_t GetNewJob(void);
	size_t GetLastJobId(void) const noexcept;
};

#endif