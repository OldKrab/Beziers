#include "Timer.h"

Timer::Timer(float time):_time(time), _timeSum(0)
{
}

void Timer::Update(float dt)
{
	_timeSum += dt;
}

bool Timer::IsEnd() const
{
	return _timeSum > _time;
}

void Timer::Reset()
{
	_timeSum = 0;
}
