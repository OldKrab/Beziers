#pragma once

class Timer
{
public:
	Timer(float time);
	void Update(float dt);
	bool IsEnd() const;
	void Reset();

private:
	float _time;
	float _timeSum;
};
