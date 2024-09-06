#include "FrameTimer.h"
#include <profileapi.h>

void FrameTimer::Init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	requestedFPS = fps;

	intervalsPerFrame = (float)(timerFreq.QuadPart / requestedFPS);

}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	deltaTime = timeNow.QuadPart - timePrevious.QuadPart;
	framesToUpdate = (int)(deltaTime / intervalsPerFrame);

	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&timePrevious);
	}

	return framesToUpdate;
}

