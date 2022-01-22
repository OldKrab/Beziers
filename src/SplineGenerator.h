#pragma once
#include "Timer.h"

class SplineGenerator
{
public:
	SplineGenerator(float firstGenerateTime, float generateTime);
	void Update(float dt);
	bool IsTimeToGenerate();
	void Reset();
private:
	Timer _firstGenerateTimer;
	Timer _generateTimer;
	bool isFirstGenerate;
};
