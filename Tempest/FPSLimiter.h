#pragma once

namespace Tempest {
	class FPSLimiter {

	public:
		FPSLimiter();
		~FPSLimiter();

		// init the fps manager
		void init(float maxFPS);

		// grab the start ticks
		void beginFrame();

		// returns the fps
		float end();

		// setters
		void setMaxFPS(float maxFPS);

	private:

		// calculate the fps
		void calculateFPS();

		// current fps
		float m_fps;

		// time difference between current/previous frame ticks
		float m_frameTime;

		// max fps for game (used to limit fps)
		float m_maxFPS;

		// ticks since SDL initialization
		unsigned int m_startTicks;

	};

}