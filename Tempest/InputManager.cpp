#include "InputManager.h"

namespace Tempest {

	InputManager::InputManager() : m_mouseCoords(0.0f) {
		// empty
	}


	InputManager::~InputManager() {
		// empty
	}

	void InputManager::update() {

		// iterate through current keymap
		for (auto& it : m_keyMap) {

			// set previous key map equal to current key map ready to check against next frame
			m_previousKeyMap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyID) {

		// set KV pair value to true for pressed key
		m_keyMap[keyID] = true;

	}

	void InputManager::releaseKey(unsigned int keyID) {

		// set KV pair value to false for released key
		m_keyMap[keyID] = false;

	}

	void InputManager::setMouseCoords(float x, float y) {

		// set previous mousecoords
		m_previousMouseCoords = m_mouseCoords;

		// once previous coords set, update the current coords
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;

	}

	bool InputManager::isKeyDown(unsigned int keyID) {

		// create iterator to find keyID in map
		auto it = m_keyMap.find(keyID);

		// if found (iterator not equal to end of map (nullptr))
		if (it != m_keyMap.end()) {
			// return value of key, value pair
			// if found => key is pressed
			return it->second;
		}
		else {
			// if not found => key not pressed
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {

		// check if key is down this frame but not last frame
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}

		// if conditions not met, key was not pressed this frame
		return false;
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {

		// create iterator to find keyID in map
		auto it = m_previousKeyMap.find(keyID);

		// if found (iterator not equal to end of map (nullptr))
		if (it != m_previousKeyMap.end()) {
			// return value of key, value pair
			// if found => key was down last frame
			return it->second;
		}
		else {
			// if not found => key not pressed
			return false;
		}
	}
}