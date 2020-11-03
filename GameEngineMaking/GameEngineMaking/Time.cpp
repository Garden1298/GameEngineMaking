#include "Time.h"

void Time::init()
{
	_targetFrame = 60;

	QueryPerformanceFrequency(&_frameInfo);
	QueryPerformanceCounter(&_prevFrameCounter);

	// fps 60 고정.
	_perFrame = _frameInfo.QuadPart / (double)_targetFrame;
	fprintf(stdout, "Target Frame : %d", _targetFrame);
}

bool Time::isUpdateTiming()
{
	QueryPerformanceCounter(&_nowFrameCounter);

	//현재 카운트 - 직전 카운트
	double time_distance = _nowFrameCounter.QuadPart - _prevFrameCounter.QuadPart;

	//렌더링 타이밍
	if (time_distance > _perFrame)
	{
		_prevFrameCounter = _nowFrameCounter;

		static int count = 0;

		if (count++ > _targetFrame)
		{
			fprintf(stdout, "1 second \n");

			count = 0;
		}

		return true;
	}
	return true;
}