#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "Resources.hpp"
#include "Settings.hpp"

class MainMenu : public sf::Drawable
{
	typedef void (*func)(MainMenu*, int);

	const string FONT_PATH = "Fonts/uni0553.ttf";
	const sf::Color IN_ACT_COLOR = {127, 127, 127};
	const sf::Color ACT_COLOR = {255, 255, 255};
	const int TITLE_SIZE = 64;
	const int TEXT_SIZE = 24;

	enum State {MAIN, SETTINGS, SAVES};
	enum {NONE, NEXT, PREVIOUS};

	const vector <vector<string>> TEXT = {
		{"Continue", "Load Game", "New Game", "Settings", "Exit", "Save Game"},
		{"Full Screen: ", "VSync: ", "FPS Limit: ", "Resolution: ", "Apply", "Back"}
	};

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
