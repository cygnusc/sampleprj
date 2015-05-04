//Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

//Glboal variables, functions, classes

//C++ program entry point
int main()
{
	//Creating the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

	//Settign the framerate limit to 60 FPS
	window.setFramerateLimit(60);

	window.setKeyRepeatEnabled(false);

	//Variable that keeps the game loop running
	bool play = true;

	//Event object holding all events
	sf::Event event;

	// font
	sf::Font font;
	if (font.loadFromFile("Data/arial.ttf") == 0)
	{
		return 1;
	}

	// States
	bool rButton = false;
	bool leftButton = false;
	bool rightButton = false;
	bool upButton = false;
	bool downButton = false;

	// Variables
	int rectRotation = 0;
	int xVelocity = 0;
	int yVelocity = 0;

	// Shapes
	sf::RectangleShape shape1;
	shape1.setSize(sf::Vector2f(50, 50));
	shape1.setPosition(400, 300);

	sf::RectangleShape shape2;
	shape2.setSize(sf::Vector2f(100, 200));
	shape2.setPosition(200, 200);
	shape2.setFillColor(sf::Color::Red);

	//Game loop
	while (play == true)
	{
		//EVENTS
		while (window.pollEvent(event))
		{
			//Event type is window closed
			if (event.type == sf::Event::Closed)
			{
				//Set play to false in order to stop the game loop
				play = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				rButton = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
			{
				rButton = false;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left) leftButton = true;
				if (event.key.code == sf::Keyboard::Right) rightButton = true;
				if (event.key.code == sf::Keyboard::Up) upButton = true;
				if (event.key.code == sf::Keyboard::Down) downButton = true;
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left) leftButton = false;
				if (event.key.code == sf::Keyboard::Right) rightButton = false;
				if (event.key.code == sf::Keyboard::Up) upButton = false;
				if (event.key.code == sf::Keyboard::Down) downButton = false;
			}
		}

		// Logic
		if (rButton == true)
		{
			rectRotation++;
			shape1.setRotation(rectRotation);
		}

		// Movement
		if (rightButton == true)
		{
			xVelocity = 5;
		}
		if (leftButton == true)
		{
			xVelocity = -5;
		}

		if (leftButton == true && rightButton == true)
		{
			xVelocity = 0;
		}

		if (leftButton == false && rightButton == false)
		{
			xVelocity = 0;
		}

		if (upButton == true)
		{
			yVelocity = -5;
		}
		if (downButton == true)
		{
			yVelocity = 5;
		}

		if (upButton == true && downButton == true)
		{
			yVelocity = 0;
		}

		if (upButton == false && downButton == false)
		{
			yVelocity = 0;
		}

		// Move
		shape1.move(xVelocity, 0);

		if (shape1.getGlobalBounds().intersects(shape2.getGlobalBounds()) == true)
		{
			shape1.move(-xVelocity, 0);
		}

		shape1.move(0, yVelocity);

		if (shape1.getGlobalBounds().intersects(shape2.getGlobalBounds()) == true)
		{
			shape1.move(0, -yVelocity);
		}
		
		//RENDERING
		window.clear();

		window.draw(shape1);
		window.draw(shape2);

		window.display();
	}
	///////////

	//Clean up and close the window
	window.close();

	//Close the program
	return 0;
}
