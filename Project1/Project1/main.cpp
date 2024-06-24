#include <SFML/Graphics.hpp>
//#include <SFMl/Audio.hpp>
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
#define KILL 3
#define HURT 1

using namespace sf;

const int sizeX = 600;
const int sizeY = 900;
int numEnemy;
const int numShot = 5;
RenderWindow win(VideoMode(sizeX, sizeY), "SpaceBattle", Style::None);

//class Sounds
//{
//private:
//	Sound shot;
//	Sounds() 
//	{
//		SoundBuffer shotBuffer;
//		shotBuffer.loadFromFile("sounds/shot.mp3");
//		shot.setBuffer(shotBuffer);
//	}
//	~Sounds() {}
//	Sounds(const Sounds&) = delete;
//	Sounds& operator=(const Sounds&) = delete;
//public:
//	static Sounds& getInstance() 
//	{
//		static Sounds instance;
//		return instance;
//	}
//	void Shot()
//	{
//		shot.play();
//	}
//};

int main()
{
	srand(time(0));
	win.setFramerateLimit(60);

	//Sounds& sound = Sounds::getInstance();

	Texture textureBackground;
	textureBackground.loadFromFile("images/starsky3.jpg");

	Texture textureEnemy;
	textureEnemy.loadFromFile("images/enemy.png");

	Sprite background;
	background.setTexture(textureBackground);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	bool level = StartOfGame();

	int health;
	int m=1;
	if (!level)
	{
		numEnemy = 40;
		health = 1;
	}
	else
	{
		numEnemy = 70;
		health = 2;
		m = 2;
	}

	Score score(m);


	Texture textureSpaceSheep;
	textureSpaceSheep.loadFromFile("images/spacesheep.png");

	Bullet shots[numShot];

	Enemy** enemies=new Enemy*[numEnemy];
	for (int i = 0; i < numEnemy; i++)
	{
		enemies[i]=new Enemy(health);
		enemies[i]->setTexture(textureEnemy);
	}

	SpaseShep sheep;
	sheep.setTexture(textureSpaceSheep);
	
	Clock clk;

	auto begin = std::chrono::high_resolution_clock::now();
	int enIterator{ 0 };

	bool islose = false;
	while(win.isOpen())
	{
		double elapsed = clk.restart().asMilliseconds();
		Event ev;
		while(win.pollEvent(ev))
		{
			if(ev.type==Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) win.close();
		}

		for (int i = 0; i < numShot; i++)
		{
			if (!shots[i].visible) shots[i].setPosition(sheep.getPosition());
			else shots[i].fly(elapsed);
		}

		if(Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) sheep.goRight(elapsed);
		if(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) sheep.goLeft(elapsed);
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (!shots[0].visible && !shots[numShot - 1].visible)
			{
				shots[0].visible = true;
				//sound.Shot();
			}
			else if (!shots[0].visible && shots[0].getPosition().y < sizeY / numShot) shots[0].visible = true;

			for (int i = 1; i < numShot; i++)
			{
				if (shots[i - 1].visible && shots[i - 1].getPosition().y < sizeY / numShot)
				{
					shots[i].visible = true;
					//sound.Shot();
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
			if(shots[i].getPosition().y <= 0) shots[i].visible = false;
		}

		Vector2f pos = sheep.getPosition();
		if (pos.x > sizeX-50) sheep.setPosition(sizeX-50, pos.y);
		else if (pos.x < 60) sheep.setPosition(60, pos.y);


		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
		if (duration.count() >= 700 && enIterator<numEnemy)
		{
			enemies[enIterator]->visible = true;
			int x;
			x = 60 + rand() % (sizeX-120);
			enemies[enIterator]->setPosition(x, 30);
			enIterator++;
			begin = now;
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
					if (enemies[j]->Wound()) score.Add(KILL);
					else score.Add(HURT);
					break;
				}
			}
		}

		for (int i = 0; i < numEnemy; i++)
		{
			if (std::abs(enemies[i]->getPosition().y - sheep.getPosition().y)<=10)
			{
				islose = true;
				break;
			}
		}
		if (islose) break;
		if (enIterator == numEnemy)
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
			if(isallkilled) break;
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

	EndOfGame(islose, score.getScore());
}