#ifndef CONTROLS_HPP_INCLUDED
#define CONTROLS_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <map>

namespace Control
{
	enum Action {LEFT, RIGHT, UP, DOWN, ESC, ENTER};

	static std::map <sf::Keyboard::Key, Action> controls = {
		{sf::Keyboard::W, Action::UP}, {sf::Keyboard::Up, Action::UP},
		{sf::Keyboard::S, Action::DOWN}, {sf::Keyboard::Down, Action::DOWN},
		{sf::Keyboard::A, Action::LEFT}, {sf::Keyboard::Left, Action::LEFT},
		{sf::Keyboard::D, Action::RIGHT}, {sf::Keyboard::Right, Action::RIGHT},
		{sf::Keyboard::Escape, Action::ESC},
		{sf::Keyboard::Enter, Action::ENTER}};
};

#endif // CONTROLS_HPP_INCLUDED
