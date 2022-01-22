#include "SplineGenerator.h"

SplineGenerator::SplineGenerator(float firstGenerateTime, float generateTime) :
	_firstGenerateTimer(firstGenerateTime),
	_generateTimer(generateTime),
	isFirstGenerate(true)
{}

void SplineGenerator::Update(float dt)
{
	_firstGenerateTimer.Update(dt);
	_generateTimer.Update(dt);
}

bool SplineGenerator::IsTimeToGenerate() 
{
	if(isFirstGenerate)
	{
		isFirstGenerate = false;
		return true;
	}
	if(_firstGenerateTimer.IsEnd() && _generateTimer.IsEnd())
	{
		_generateTimer.Reset();
		return true;
	}
	return false;
}

void SplineGenerator::Reset()
{
	isFirstGenerate = true;
	_firstGenerateTimer.Reset();
	_generateTimer.Reset();
}
