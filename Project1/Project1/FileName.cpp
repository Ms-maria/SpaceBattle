#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
//#include "Bullet.h"

using namespace sf;

const int sizeX = 600;
const int sizeY = 900;
const int numShot = 5;
const int numEnemy = 50;

class Enemy : public Sprite
{
private:
	const double speed;
	int healthPoints;
public:
	bool visible;
	Enemy() : speed(0.15), healthPoints(2), visible(false) {};
	void Move(double elapsed)
	{
		move(0, speed * elapsed);
	}
	void Wound()
	{
		healthPoints--;
		if (healthPoints == 0)
		{
			visible = false;
			healthPoints = 3;
		}
	}
};

class Bullet : public CircleShape
{
private:
	const double speed;
	const int power;
public:
	bool visible;
	Bullet() : power(10), speed(sizeX*1.2/500), visible(false)
	{
		setRadius(3);
		setFillColor(Color::White);
		setOrigin(10, 10);
	}
	void fly(double elapsed)
	{
		move(0, -speed * elapsed);
	}
};

class SpaseShep : public Sprite
{
private:
	const double speed;
	const int power;
public:
	SpaseShep() : speed(0.5), power(10) {}
	void goLeft(double elapsed)
	{
		this->move(-speed * elapsed, 0);
	}
	void goRight(double elapsed)
	{
		this->move(speed * elapsed, 0);
	}
};

int main()
{
	srand(time(0));
	RenderWindow win(VideoMode(sizeX,sizeY),"SpaceBattle", Style::None);
	win.setFramerateLimit(60);

	Texture textureBackground;
	textureBackground.loadFromFile("images/starsky3.jpg");

	Texture textureSpaceSheep;
	textureSpaceSheep.loadFromFile("images/spacesheep.png");

	Texture textureEnemy;
	textureEnemy.loadFromFile("images/enemy.png");

	Sprite background;
	background.setTexture(textureBackground);
	background.setOrigin(0, 0);
	background.setPosition(0, 0);

	Bullet shots[numShot];

	Enemy enemies[numEnemy];
	for (int i = 0; i < numEnemy; i++)
	{
		enemies[i].setTexture(textureEnemy);
		enemies[i].setOrigin(25, 25);
	}

	SpaseShep sheep;
	sheep.setTexture(textureSpaceSheep);
	sheep.setPosition(sizeX/2, sizeY-60);
	sheep.setOrigin(60,50);
	
	Clock clk;

	auto start= std::chrono::high_resolution_clock::now();
	int enIterator{ 0 };
	
	bool victory = false;
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
			if (!shots[0].visible && !shots[numShot - 1].visible) shots[0].visible = true;
			else if (!shots[0].visible && shots[0].getPosition().y < sizeY / numShot) shots[0].visible = true;

			for (int i = 1; i < numShot; i++)
			{
				if (shots[i - 1].visible && shots[i - 1].getPosition().y < sizeY / numShot) shots[i].visible = true;
			}
		}

		for (int i = 0; i < numEnemy; i++)
		{
			if (enemies[i].visible) enemies[i].Move(elapsed);
			if (enemies[i].getPosition().y <= 0) enemies[i].visible = false;
		}
		
		for (int i = 0; i < numShot; i++)
		{
			if(shots[i].getPosition().y <= 0) shots[i].visible = false;
		}

		Vector2f pos = sheep.getPosition();
		if (pos.x > sizeX-50) sheep.setPosition(sizeX-50, pos.y);
		else if (pos.x < 50) sheep.setPosition(50, pos.y);


		auto now= std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
		if (duration.count() >= 700 && enIterator<numEnemy)
		{
			enemies[enIterator].visible = true;
			int x;
			x = 60 + rand() % (sizeX-120);
			enemies[enIterator].setPosition(x, 30);
			enIterator++;
			start = now;
			//if (enIterator == numEnemy) enIterator = 0;
		}



		for (int i = 0; i < numShot; i++)
		{
			if (!shots[i].visible) continue;
			for (int j = 0; j < numEnemy; j++)
			{
				if (!enemies[j].visible) continue;
				double x1, x2, y1, y2;
				x1 = shots[i].getPosition().x;
				y1= shots[i].getPosition().y;
				x2 = enemies[j].getPosition().x;
				y2= enemies[j].getPosition().y;
				double d = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
				if (d < 45 * 45)
				{
					shots[i].visible = false;
					enemies[j].Wound();
					break;
				}
			}
		}

		bool lose = false;

		for (int i = 0; i < numEnemy; i++)
		{
			if (std::abs(enemies[i].getPosition().y - sheep.getPosition().y)<=10)
			{
				lose = true;
				break;
			}
		}
		if (lose) break;


		win.draw(background);

		for (int i = 0; i < numShot; i++)
		{
			win.draw(shots[i]);
		}
		for (int i = 0; i < numEnemy; i++)
		{
			if (enemies[i].visible) win.draw(enemies[i]);
		}
		win.draw(sheep);

		win.display();
		
	}

	Sprite lose;
	int k = 0;
	bool textur=false;
	while (win.isOpen())
	{
		if (victory) break;
		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) win.close();
		}
		
		Texture lose1;
		lose1.loadFromFile("images/lose1.png");
		Texture lose2;
		lose2.loadFromFile("images/lose2.png");

		lose.setOrigin(0, 0);
		lose.setPosition(0, 300);
		k++;
		if (k == 10)
		{
			if (textur) lose.setTexture(lose1);
			else lose.setTexture(lose2);
			k = 0;
			textur = !textur;
		}
		textur = !textur;

		win.clear(Color::Black);
		win.draw(lose); 
		win.display();
	}


}