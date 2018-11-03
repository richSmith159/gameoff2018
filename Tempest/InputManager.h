#pragma once

#include <glm\glm\glm.hpp>
#include <unordered_map>

namespace Tempest {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		// update key maps
		void update();

		// handle key down (add to active key map)
		void pressKey(unsigned int keyID);

		// handle key up (remove from active key map)
		void releaseKey(unsigned int keyID);

		// true if key is being held down
		bool isKeyDown(unsigned int keyID);

		// true if key is pressed during the current frame
		bool isKeyPressed(unsigned int keyID);

		// setters
		void setMouseCoords(float x, float y);

		// getters
		glm::vec2 getMouseCoords() const { return m_mouseCoords; }
		glm::vec2 getPreviousMouseCoords() const { return m_previousMouseCoords; }

	private:

		// private function to check if key was down last frame
		bool wasKeyDown(unsigned int keyID);

		// map to store bool values keeping track of which keys are pressed
		// map used as this will be dynamically resized
		// map will only be as big as number of keys used (instead of large array of all possible keys)
		std::unordered_map<unsigned int, bool> m_keyMap;

		// as before, but for last frame
		// used for checking if a key has been pressed during the current frame
		std::unordered_map<unsigned int, bool> m_previousKeyMap;

		// vector to store mouse coords (x, y)
		glm::vec2 m_mouseCoords;

		// vector to store mouse coords from last frame
		glm::vec2 m_previousMouseCoords;

	};

}