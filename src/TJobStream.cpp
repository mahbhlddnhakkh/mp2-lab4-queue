#include "TJobStream.h"

TJobStream::TJobStream(double JobIntense)
{
	if (JobIntense >= 0.0 && JobIntense <= 1.0)
	{
		this->JobIntense = JobIntense;
		LastJobId = 0;
	}
	else
		throw "Job Intens must be between 0.0 and 1.0";
}

double TJobStream::GetJobIntens(void) const noexcept
{
	return JobIntense;
}

size_t TJobStream::GetNewJob(void)
{
	if (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) <= JobIntense)
	{
		LastJobId++;
		return LastJobId;
	}
	else
		return 0;
}

size_t TJobStream::GetLastJobId(void) const noexcept
{
	return LastJobId;
}
