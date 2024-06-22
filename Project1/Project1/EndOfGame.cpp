#include "EndOfGame.h"

void EndOfGame(bool islose,const std::vector<int> score)
{
	const int x{ 140 }, y{ 650 };
	const int n = score.size();

	Sprite  numbers[10];
	Texture textureNumbers[10];
	for (int i = 0; i < 10; i++)
	{
		char c = i + '0';
		std::string path = "images/";
		path.push_back(c);
		path+=".png";
		textureNumbers[i].loadFromFile(path);
		numbers[i].setOrigin(0, 0);
		numbers[i].setPosition(x, y);
		numbers[i].setTexture(textureNumbers[i]);
	}

	Texture textureScore;
	textureScore.loadFromFile("images/score.png");

	Sprite spriteScore;
	spriteScore.setTexture(textureScore);
	spriteScore.setOrigin(0, 0);
	spriteScore.setPosition(125,550);
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
		win.draw(spriteScore);
		for (int i = n-1; i >=0; i--)
		{
			numbers[score[i]].setPosition(x+((n-i)*70), y);
			win.draw(numbers[score[i]]);
		}
		if (n == 0)
		{
			win.draw(numbers[0]);
		}
		win.display();
	}
}
