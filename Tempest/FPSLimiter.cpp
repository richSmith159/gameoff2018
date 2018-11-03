#include "FPSLimiter.h"
#include <SDL\SDL.h>

namespace Tempest {

	FPSLimiter::FPSLimiter() {
		// empty
	}


	FPSLimiter::~FPSLimiter() {
		// empty
	}

	void FPSLimiter::setMaxFPS(float maxFPS) { m_maxFPS = maxFPS; }

	// set the start ticks for the frame
	// (the number of ticks since SDL initialization)
	void FPSLimiter::beginFrame() { m_startTicks = SDL_GetTicks(); }


	float FPSLimiter::end() {

		// calc current FPS
		calculateFPS();

		// limit fps to max fps;
		float frameTicks = SDL_GetTicks() - m_startTicks;

		if (1000.0f / m_maxFPS > frameTicks) {
			SDL_Delay(1000.0f / m_maxFPS - frameTicks);
		}

		// return current fps
		return m_fps;

	}

	void FPSLimiter::calculateFPS() {

		// number of frame times to average fps over
		static const int numberOfSamples = 10;
		// static array to hold frame times (treat as circular buffer)
		static float frameTimes[numberOfSamples];

		// keep track of current element in frameTimes
		static int currentFrame = 0;

		// get current and previous ticks
		static float previousTicks = SDL_GetTicks();

		float currentTicks;
		currentTicks = SDL_GetTicks();

		// calculate time difference
		m_frameTime = currentTicks - previousTicks;

		frameTimes[currentFrame % numberOfSamples] = m_frameTime;

		previousTicks = currentTicks;


		int count;

		// increment frame
		currentFrame++;
		if (currentFrame < numberOfSamples) {
			count = currentFrame;
		}
		else {
			count = numberOfSamples;
		}

		// calculate average frametime
		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		// check for divide by 0
		if (frameTimeAverage > 0) {
			m_fps = 1000.0f / frameTimeAverage;
		}
		else {
			m_fps = 60.0f;
		}

	}

}