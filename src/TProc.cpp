#include "TProc.h"

TProc::TProc(double Rate, size_t MaxJobs) : Jobs(MaxJobs)
{
	if (Rate >= 0.0 && Rate <= 1.0)
	{
		ProcRate = Rate;
		JobsDone = 0;
		OverflowTimes = 0;
		NoJobsTimes = 0;
	}
	else
		throw "Proc rate must be between 0.0 and 1.0";
}

double TProc::GetRate(void) const noexcept
{
	return ProcRate;
}

size_t TProc::IsProcBusy(void) const noexcept
{
	if (Jobs.IsEmpty())
		return 0;
	else
		return Jobs.Top();
}

bool TProc::IsProcFull(void) const noexcept
{
	return Jobs.IsFull();
}

size_t TProc::RunNewJob(size_t JobId)
{

	if (JobId > 0)
	{
		if (IsProcFull())
		{
			OverflowTimes++;
			return 0;
		}
		else
		{
			Jobs.Push(JobId);
			return JobId;
		}
	}
	else
		return ~0;
}

size_t TProc::DoJob(void)
{
	if (!IsProcBusy())
	{
		NoJobsTimes++;
		return 0;
	}
	else if (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) <= ProcRate && IsProcBusy())
	{
		size_t LastJob = Jobs.TopPop();
		JobsDone++;
		return LastJob;
	}
	else
		return Jobs.Top();
}

size_t TProc::GetJobsDone(void) const noexcept
{
	return JobsDone;
}

size_t TProc::GetOverflowTimes(void) const noexcept
{
	return OverflowTimes;
}

size_t TProc::GetNoJobsTimes(void) const noexcept
{
	return NoJobsTimes;
}
