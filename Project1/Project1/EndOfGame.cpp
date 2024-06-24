#include "EndOfGame.h"

void EndOfGame(bool islose)
{
	Sprite textEOG;
	int k = 0;
	bool textur = false;
	while (win.isOpen())
	{
		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) win.close();
		}

		Texture textur1;
		Texture textur2;
		if (islose)
		{
			textur1.loadFromFile("images/lose1.png");
			textur2.loadFromFile("images/lose2.png");
		}
		else
		{
			textur1.loadFromFile("images/win1.png");
			textur2.loadFromFile("images/win2.png");
		}

		textEOG.setOrigin(0, 0);
		textEOG.setPosition(0, 300);
		k++;
		if (k == 10)
		{
			if (textur) textEOG.setTexture(textur1);
			else textEOG.setTexture(textur2);
			k = 0;
			textur = !textur;
		}
		textur = !textur;

		win.clear(Color::Black);
		win.draw(textEOG);
		win.display();
	}
}
