#include <unordered_map>

namespace Animation
{
	class InputManager
	{
	public:
		InputManager() = default;
		~InputManager() = default;

		void Update();

		bool IsKeyPressed(char p_key);
		bool IsKeyPressedEventOccured(char p_key);
		bool IsKeyReleasedEventOccured(char p_key);

	private:
		std::unordered_map<char, bool> m_keyPressedEvents;
		std::unordered_map<char, bool> m_keyReleasedEvents;
		std::unordered_map<char, bool> m_keyStates;
	};
}