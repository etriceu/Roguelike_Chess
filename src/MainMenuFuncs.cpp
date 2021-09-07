#include "MainMenu.hpp"

void MainMenu::functions()
{
	funcs = {
		{
			[](MainMenu* it, int){log(it->swapped ? "M6\n" : "M1\n"); return 0;},
			[](MainMenu* it, int){log("M2\n"); return 0;},
			[](MainMenu* it, int)
			{
				if(!it->swapped)
				{
					it->swapped = true;
					it->menu[MAIN][0] = sf::Text(it->TEXT[MAIN][5],
										*fonts(string(it->FONT_PATH)), it->TEXT_SIZE);
					it->menu[MAIN][0].setFillColor(it->IN_ACT_COLOR);
					it->resize();
				}
				it->current = 0;
				return (int)NEW;
			},
			[](MainMenu* it, int)
			{
				it->current = 0;
				it->state = SETTINGS;
				it->tmpSett = *it->settings;
				for(size_t n = 0; n < it->menu[SETTINGS].size()-2; n++)
					it->funcs[SETTINGS][n](it, NONE);
				return 0;
			},
			[](MainMenu*, int){exit(0); return 0;}
		},
		{
			[](MainMenu* it, int n)
			{
				if(n != NONE)
					it->tmpSett.fullScreen = !it->tmpSett.fullScreen;

				it->menu[SETTINGS][0].setString(it->TEXT[SETTINGS][0] +
					(it->tmpSett.fullScreen ? "true" : "false"));
				it->resize();
				return 0;
			},
			[](MainMenu* it, int n)
			{
				if(n != NONE)
					it->tmpSett.vsync = !it->tmpSett.vsync;

				it->menu[SETTINGS][1].setString(it->TEXT[SETTINGS][1] +
					(it->tmpSett.vsync ? "true" : "false"));
				it->resize();
				return 0;
			},
			[](MainMenu* it, int n)
			{
				if(n == NEXT)
					it->tmpSett.maxFPS += 10;
				else if(n == PREVIOUS)
					it->tmpSett.maxFPS -= 10;

				if(it->tmpSett.maxFPS <= 0)
				{
					it->tmpSett.maxFPS = 0;
					it->menu[SETTINGS][2].setString(it->TEXT[SETTINGS][2] + "unlimited");
				}
				else
					it->menu[SETTINGS][2].setString(it->TEXT[SETTINGS][2] +
						to_string(it->tmpSett.maxFPS));

				it->resize();
				return 0;
			},
			[](MainMenu* it, int n)
			{
				if(n == NEXT && it->mode < it->tmpSett.modes.size()-1)
					it->mode++;
				else if(n == PREVIOUS && it->mode > 0)
					it->mode--;

				if(n != NONE)
					it->tmpSett.mode = it->tmpSett.modes[it->mode];

				it->menu[SETTINGS][3].setString(it->TEXT[SETTINGS][3] +
					to_string(it->tmpSett.mode.width) + "x" +
					to_string(it->tmpSett.mode.height));
				it->resize();
				return 0;
			},
			[](MainMenu* it, int)
			{
				*it->settings = it->tmpSett;
				it->settings->apply();
				it->settings->save();
				return 0;
			},
			[](MainMenu* it, int){it->current = 0; it->state = MAIN; return 0;}
		}
	};
}
