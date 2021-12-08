#include "InputManager.h"

#include <Windows.h>

void Animation::InputManager::Update()
{
	m_keyPressedEvents.clear();
	m_keyReleasedEvents.clear();

	for (uint8_t i = 0; i < 255; ++i)
	{
		bool isKeyDown = GetKeyState(static_cast<int>(i)) & 0x8000; // Check if high-order bit is set to 1 (1 << 15), Equivalent is to check if value is negative

		m_keyPressedEvents[i]  =  isKeyDown && !m_keyStates[i];
		m_keyReleasedEvents[i] = !isKeyDown &&  m_keyStates[i];

		m_keyStates[i] = isKeyDown;
	}
}

bool Animation::InputManager::IsKeyPressed(char p_key)
{
	return m_keyStates[p_key];
}

bool Animation::InputManager::IsKeyPressedEventOccured(char p_key)
{
	return m_keyPressedEvents[p_key];
}

bool Animation::InputManager::IsKeyReleasedEventOccured(char p_key)
{
	return m_keyReleasedEvents[p_key];
}
