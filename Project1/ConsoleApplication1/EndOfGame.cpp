#include "EndOfGame.h"

bool EndOfGame(bool islose, Score score)
{
	Sprite WinOrLose;
	Sprite scores;
	Sprite again;

	Texture scoreTexture;
	scoreTexture.loadFromFile("images/score.png");
	scores.setTexture(scoreTexture);
	scores.setOrigin(0, 0);
	scores.setPosition(150, 400);

	Texture againTexture;
	againTexture.loadFromFile("images/again.png");

	again.setOrigin(0, 0);
	again.setTexture(againTexture);
	again.setPosition(100, 700);

	Sound sound;
	SoundBuffer buffer;

	bool isagain = false;

	const int x = 200, y = 450;
	const int num = 10;
	Sprite numbers[num];
	Texture texturnum[num];

	for (int i = 0; i < num; i++)
	{
		std::string file{ "images/" };
		file.push_back('0' + i);
		file += ".png";
		texturnum[i].loadFromFile(file);
		numbers[i].setTexture(texturnum[i]);
		numbers[i].setOrigin(0, 0);
	}

	std::vector<int> digits = score.GetNumbers();

	for (int i = 0; i < digits.size(); i++)
	{
		numbers[digits[i]].setPosition(i * 40 + x, y);
	}

	Texture textur1;
	Texture textur2;

	if (islose)
	{
		textur1.loadFromFile("images/lose1.png");
		textur2.loadFromFile("images/lose2.png");
		buffer.loadFromFile("sounds/losemusic.wav");
	}
	else
	{
		textur1.loadFromFile("images/win1.png");
		textur2.loadFromFile("images/win2.png");
		buffer.loadFromFile("sounds/winmusic.wav");
	}
	sound.setBuffer(buffer);
	sound.play();
	int k = 0;
	bool textur = false;
	while (win.isOpen())
	{
		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				win.close();
				sound.stop();
				return false;
			}
		}
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				int x = ev.mouseButton.x;
				int y = ev.mouseButton.y;
				if (x >= 100 && x <= 500 && y >= 700 && y <= 800)
				{
					return true;
				}
			}
		}

		WinOrLose.setOrigin(0, 0);
		WinOrLose.setPosition(0, 200);
		k++;
		if (k == 10)
		{
			if (textur) WinOrLose.setTexture(textur1);
			else WinOrLose.setTexture(textur2);
			k = 0;
			textur = !textur;
		}
		textur = !textur;

		win.clear(Color::Black);
		win.draw(WinOrLose);
		win.draw(scores);
		win.draw(again);
		for (int i = 0; i < digits.size(); i++)
		{
			win.draw(numbers[digits[i]]);
		}
		win.display();
	}
}
