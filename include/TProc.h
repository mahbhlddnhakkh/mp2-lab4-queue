// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
//
//
//

#ifndef __TProc_H__
#define __TProc_H__

#include "tqueue.h"
#include <cstdlib>

class TProc
{
private:
	double ProcRate;
	TQueue<size_t> Jobs;
	size_t JobsDone;
	size_t OverflowTimes;
	size_t NoJobsTimes;
public:
	TProc(double Rate, size_t MaxJobs);
	double GetRate(void) const noexcept;
	size_t IsProcBusy(void) const noexcept;
	bool IsProcFull(void) const noexcept;
	size_t RunNewJob(size_t JobId);
	size_t DoJob(void);
	size_t GetJobsDone(void) const noexcept;
	size_t GetOverflowTimes(void) const noexcept;
	size_t GetNoJobsTimes(void) const noexcept;
};

#endif
