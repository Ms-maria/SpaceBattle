#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Bullet.h"
#include "Enemy.h"
#include "SpaseSheep.h"
#include "EndOfGame.h"
#include "StartOfGame.h"
#include "Score.h"

using namespace sf;

const int sizeX = 600;
const int sizeY = 900;
int numEnemy;
const int numShot = 5;
RenderWindow win(VideoMode(sizeX, sizeY), "SpaceBattle", Style::None);




int main()
{
	srand(time(0));
	win.setFramerateLimit(60);

	Sound shot;
	Music backMusic;
	SoundBuffer shotbuf;
	
	shotbuf.loadFromFile("sounds/shot2.wav");
	shot.setBuffer(shotbuf);
	backMusic.openFromFile("sounds/spacemusic.wav");

	Texture textureBackground;
	textureBackground.loadFromFile("images/starsky3.jpg");

	Texture textureEnemy;
	textureEnemy.loadFromFile("images/enemy.png");

	Sprite background;
	background.setTexture(textureBackground);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	Texture textureSpaceSheep;
	textureSpaceSheep.loadFromFile("images/spacesheep.png");

	Bullet shots[numShot];

	SpaseShep sheep;
	sheep.setTexture(textureSpaceSheep);

	bool again = true;

	while (again)
	{
		backMusic.play();
		backMusic.setLoop(true);

		int x = StartOfGame();
		bool level = false, endlessmode = false;
		if (x == 10)
		{
			level = true;
		}
		else if (x == 11)
		{
			level = true;
			endlessmode = true;
		}
		else if (x == 1)
		{
			endlessmode = true;
		}
		else if (x == -1)
		{
			break;
		}

		int health, mult;
		if (level)
		{
			numEnemy = 70;
			health = 2;
			mult = 3;
		}
		else
		{
			numEnemy = 40;
			health = 1;
			mult = 1;
		}

		Score score(mult);

		Enemy** enemies = new Enemy * [numEnemy];
		for (int i = 0; i < numEnemy; i++)
		{
			enemies[i] = new Enemy(health);
			enemies[i]->setTexture(textureEnemy);
		}

		Clock clk;

		auto begin = std::chrono::high_resolution_clock::now();
		int enIterator{ 0 };

		auto beginmusic = std::chrono::high_resolution_clock::now();

		bool islose = false;
		while (win.isOpen())
		{
			double elapsed = clk.restart().asMilliseconds();
			Event ev;
			while (win.pollEvent(ev))
			{
				if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					backMusic.stop();
					win.close();
					return 0;
				}
			}

			for (int i = 0; i < numShot; i++)
			{
				if (!shots[i].visible) shots[i].setPosition(sheep.getPosition());
				else shots[i].fly(elapsed);
			}

			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) sheep.goRight(elapsed);
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) sheep.goLeft(elapsed);
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (!shots[0].visible && !shots[numShot - 1].visible)
				{
					shots[0].visible = true;
					shot.play();
					beginmusic = std::chrono::high_resolution_clock::now();
				}
				else if (!shots[0].visible && shots[0].getPosition().y < sizeY / numShot) shots[0].visible = true;

				for (int i = 1; i < numShot; i++)
				{
					if (shots[i - 1].visible && shots[i - 1].getPosition().y < sizeY / numShot)
					{
						shots[i].visible = true;
						auto nowmusic = std::chrono::high_resolution_clock::now();
						auto durat = nowmusic - beginmusic;
						auto durat_ms = std::chrono::duration_cast<std::chrono::milliseconds>(durat).count();
						if (durat_ms >= 60)
						{
							beginmusic = std::chrono::high_resolution_clock::now();
							shot.play();
						}
					}
				}
			}

			for (int i = 0; i < numEnemy; i++)
			{
				if (enemies[i]->visible) enemies[i]->Move(elapsed);
				if (enemies[i]->getPosition().y <= 0) enemies[i]->visible = false;
			}

			for (int i = 0; i < numShot; i++)
			{
				if (shots[i].getPosition().y <= 0) shots[i].visible = false;
			}

			Vector2f pos = sheep.getPosition();
			if (pos.x > sizeX - 50) sheep.setPosition(sizeX - 50, pos.y);
			else if (pos.x < 60) sheep.setPosition(60, pos.y);


			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
			if (duration.count() >= 700 && enIterator < numEnemy)
			{
				if (enemies[enIterator]->visible == false)
				{
					enemies[enIterator]->visible = true;
					int x;
					x = 60 + rand() % (sizeX - 120);
					enemies[enIterator]->setPosition(x, 30);
					enIterator++;
					begin = now;
				}
			}


			for (int i = 0; i < numShot; i++)
			{
				if (!shots[i].visible) continue;
				for (int j = 0; j < numEnemy; j++)
				{
					if (!enemies[j]->visible) continue;
					double x1, x2, y1, y2;
					x1 = shots[i].getPosition().x;
					y1 = shots[i].getPosition().y;
					x2 = enemies[j]->getPosition().x;
					y2 = enemies[j]->getPosition().y;
					double d = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
					if (d < 45 * 45)
					{
						shots[i].visible = false;
						enemies[j]->Wound();
						int x = 1;
						if (!enemies[j]->visible)
						{
							x++;
						}
						score.Add(x);
						break;
					}
				}
			}

			for (int i = 0; i < numEnemy; i++)
			{
				if (std::abs(enemies[i]->getPosition().y - sheep.getPosition().y) <= 10)
				{
					islose = true;
					break;
				}
			}
			if (islose) break;
			if (endlessmode && enIterator == numEnemy)
			{
				enIterator = 0;
			}
			else if (!endlessmode && enIterator == numEnemy)
			{
				bool isallkilled = true;
				for (int i = 0; i < numEnemy; i++)
				{
					if (enemies[i]->visible == true)
					{
						isallkilled = false;
						break;
					}
				}
				if (isallkilled)
				{
					break;
				}
			}

			win.draw(background);
			for (int i = 0; i < numShot; i++)
			{
				win.draw(shots[i]);
			}
			for (int i = 0; i < numEnemy; i++)
			{
				if (enemies[i]->visible) win.draw(*enemies[i]);
			}
			win.draw(sheep);

			win.display();

		}

		for (int i = 0; i < numEnemy; ++i)
		{
			delete enemies[i];
		}

		delete[] enemies;
		backMusic.stop();
		again = EndOfGame(islose, score);
	}


}