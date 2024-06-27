#include "StartOfGame.h"

int StartOfGame()
{
	Texture textureEasy;
	textureEasy.loadFromFile("images/easy.png");

	Texture textureHard;
	textureHard.loadFromFile("images/hard.png");

	Texture textureEndless;
	textureEndless.loadFromFile("images/endlessmode.png");

	Texture textureStart;
	textureStart.loadFromFile("images/start.png");

	Sprite easy, hard, start,mode;
	easy.setOrigin(0, 0);
	easy.setTexture(textureEasy);
	easy.setPosition(75, 115);

	hard.setOrigin(0, 0);
	hard.setTexture(textureHard);
	hard.setPosition(75, 300);

	start.setOrigin(0, 0);
	start.setTexture(textureStart);
	start.setPosition(50, 700);

	mode.setOrigin(0, 0);
	mode.setTexture(textureEndless);
	mode.setPosition(50, 525);

	Vector2f size{ 495,195 };
	RectangleShape choice,moderec;
	choice.setSize(size);
	choice.setFillColor(Color::Green);
	choice.setOrigin(0, 0);
	choice.setPosition(50, 100);

	size.x += 50;
	moderec.setSize(size);
	moderec.setFillColor(Color::Blue);
	moderec.setOrigin(0, 0);
	moderec.setPosition(25, 500);
	bool level = false;
	bool endlessmode = false;
	while (win.isOpen())
	{
		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) win.close();
		}
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				int x = ev.mouseButton.x;
				int y = ev.mouseButton.y;
				if (x >= 75 && x <= 525 && y >= 115 && y <= 265)
				{
					level = false;
					choice.setFillColor(Color::Green);
					choice.setPosition(50, 100);
				}
				else if (x >= 75 && x <= 525 && y >= 300 && y <= 450)
				{
					level = true;
					choice.setFillColor(Color::Red);
					choice.setPosition(50, 275);
				}
				else if (x >= 75 && x <= 525 && y >= 525 && y <= 675)
				{
					endlessmode = !endlessmode;
				}
				else if (x >= 50 && x <= 550 && y >= 700 && y <= 900)
				{
					break;
				}
			}
		}


		win.clear(Color::Black);

		win.draw(choice);
		if (endlessmode)
		{
			win.draw(moderec);
		}
		win.draw(easy);
		win.draw(hard);
		win.draw(start);
		win.draw(mode);

		win.display();
	}
	int x = 0;
	if (level) x += 10;
	if (endlessmode) x += 1;
	return x;
}