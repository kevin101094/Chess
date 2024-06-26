#ifndef _CSMVIEW_H_
#define _CSMVIEW_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Tooltip.h"

const int BeginblankX = 150;
const int BeginblankY = 350;
const int blankgap = 50;
const int blankamount = 14;
class csmView {
private:
	sf::RenderWindow& csmwindow;
	Tooltip* tooltip;
	sf::Font font;
	sf::RectangleShape csmFileList;
	sf::RectangleShape csmListBlank[blankamount];
	sf::RectangleShape csmListBlankframe[blankamount];
	sf::CircleShape UpButton, DownButton;
	sf::Text csmListtxt[blankamount];
	
public:
	csmView(sf::RenderWindow& window);
	void Draw(int fakeChosen, int X, int Y, bool isPressed);
	bool inFileList(int X, int Y);
	bool inUpButton(int X, int Y);
	bool inDownButton(int X, int Y);
	int inFileBlank(int X, int Y, int size, int scrollcnt);
	void UpdateFileList(std::vector<std::string> filename, int scrollcnt);
	void End();
};







#endif