// ????, ?????, ???? "????????? ? ????????? ??????"
//
//
//
// ???????????? ?????????????? ???????

#include <iostream>
#include "TProc.h"
#include "TJobStream.h"


int main(int argc, char* argv[])
{
	std::srand(std::time(nullptr));
	const size_t tests = 3;
	TProc proc[tests] = { TProc(0.5, 3), TProc(0.2, 3), TProc(0.5, 3) };
	TJobStream stream[tests] = { TJobStream(0.5), TJobStream(0.5), TJobStream(0.2) };
	size_t tacts[tests] = { 10, 10, 10 };
	TQueue<size_t> jobsqueue(10);

	for (size_t i = 0; i < tests; i++)
	{
		std::cout << tacts[i] << " tacts, queue size is 3, JobsIntense is " << stream[i].GetJobIntens() << ", proc rate is " << proc[i].GetRate() << '.' << std::endl;
		for (size_t j = 0; j < tacts[i]; j++)
		{
			size_t temp_job = stream[i].GetNewJob();
			if (temp_job > 0)
				jobsqueue.Push(temp_job);
			if (!jobsqueue.IsEmpty())
				if (proc[i].RunNewJob(jobsqueue.Top()))
					jobsqueue.Pop();
			proc[i].DoJob();
		}
		jobsqueue.Free();
		std::cout << "Jobs Generated " << stream[i].GetLastJobId() << ", Proc Jobs Done " << proc[i].GetJobsDone() << ", Proc Jobs Overflow " << proc[i].GetOverflowTimes() << ", Proc No Jobs Tacts " << proc[i].GetNoJobsTimes() << ", average " << (static_cast<double>(tacts[i]) / static_cast<double>(proc[i].GetJobsDone())) << " tacts done per job." << std::endl << std::endl;
	}
	return 0;
}