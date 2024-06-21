#include "StartOfGame.h"

bool StartOfGame()
{
	Texture textureEasy;
	textureEasy.loadFromFile("images/easy.png");

	Texture textureHard;
	textureHard.loadFromFile("images/hard.png");

	Texture textureStart;
	textureStart.loadFromFile("images/start.png");

	Sprite easy, hard, start;
	easy.setOrigin(0, 0);
	easy.setTexture(textureEasy);
	easy.setPosition(75, 115);

	hard.setOrigin(0, 0);
	hard.setTexture(textureHard);
	hard.setPosition(75, 300);

	start.setOrigin(0, 0);
	start.setTexture(textureStart);
	start.setPosition(50, 700);

	Vector2f size{ 495,195 };
	RectangleShape choice;
	choice.setSize(size);
	choice.setFillColor(Color::Green);
	choice.setOrigin(0, 0);
	choice.setPosition(50, 100);
	bool level = false;

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
				else if (x >= 50 && x <= 550 && y >= 700 && y <= 900)
				{
					break;
				}
			}
		}


		win.clear(Color::Black);

		win.draw(choice);
		win.draw(easy);
		win.draw(hard);
		win.draw(start);

		win.display();
	}
	return level;
}