#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "Resources.hpp"
#include "Settings.hpp"

class MainMenu : public sf::Drawable
{
	typedef void (*func)(MainMenu*, int);

	const string fontPath = "Fonts/uni0553.ttf";

	const sf::Color inactiveColor = {127, 127, 127};
	const sf::Color activeColor = {255, 255, 255};

	enum State {MAIN, SETTINGS, SAVES};
	enum {NONE, NEXT, PREVIOUS};
	const vector <vector<string>> text = {
		{"Continue", "Load Game", "New Game", "Settings", "Exit", "Save Game"},
		{"Full Screen: ", "VSync: ", "FPS Limit: ", "Resolution: ", "Apply", "Back"}
	};

	const int titleSize = 64;
	const int textSize = 24;

public:
	MainMenu(Settings *settings, string title);
	void resize();
	void event(sf::Event e);

private:
	void functions();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Settings *settings, tmpSett;
	sf::Text title;
	vector <vector<sf::Text>> menu;

	int current = 0;
	size_t mode = 0;
	bool swapped = false;
	State state = MAIN;
	vector <vector<func>> funcs;
};
#endif // MAINMENU_HPP_INCLUDED
