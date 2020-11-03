#include "Time.h"

void Time::init()
{
	_targetFrame = 60;

	QueryPerformanceFrequency(&_frameInfo);
	QueryPerformanceCounter(&_prevFrameCounter);

	// fps 60 ����.
	_perFrame = _frameInfo.QuadPart / (double)_targetFrame;
	fprintf(stdout, "Target Frame : %d", _targetFrame);
}

bool Time::isUpdateTiming()
{
	QueryPerformanceCounter(&_nowFrameCounter);

	//���� ī��Ʈ - ���� ī��Ʈ
	double time_distance = _nowFrameCounter.QuadPart - _prevFrameCounter.QuadPart;

	//������ Ÿ�̹�
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