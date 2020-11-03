#pragma once

#include <Windows.h>
#include <iostream>


class Time
{
private:

	int _targetFrame;
	float _perFrame;

	LARGE_INTEGER _frameInfo;
	LARGE_INTEGER _prevFrameCounter;
	LARGE_INTEGER _nowFrameCounter;

public:

	static Time* instance()
	{
		static Time instance;
		return &instance;
	}

	void init();
	bool isUpdateTiming();
};

