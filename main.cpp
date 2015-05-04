//Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

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

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setColor(sf::Color::Red);
	score.setPosition(350, 10);
	score.setString("0 : 0");

	// Images
	sf::Texture tex_pad;
	sf::Texture tex_ball;
	sf::Texture tex_background;
	if (tex_pad.loadFromFile("Data/pad.png") == false)
	{
		return -1;
	}

	if (tex_ball.loadFromFile("Data/ball.png") == false)
	{
		return -1;
	}

	if (tex_background.loadFromFile("Data/background.png") == false)
	{
		return -1;
	}

	// Sounds
	sf::SoundBuffer buff_hit;

	sf::Sound hit;

	hit.setBuffer(buff_hit);
	if (buff_hit.loadFromFile("Data/hit.wav") == false)
	{
		return -1;
	}
	// States
	bool up = false;
	bool down = false;

	// Variables
	
	int yVelocityPad1 = 0;

	int xVelocityBall = -5;
	int yVelocityBall = -5;

	int yVelocityPad2 = 0;

	int pad1score = 0;
	int pad2score = 0;

	// Shapes
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex_background);

	// Pad1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(50, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&tex_pad);

	// Pad2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(50, 100));
	pad2.setPosition(700, 200);
	pad2.setTexture(&tex_pad);

	// Ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(50, 50));
	ball.setPosition(400, 200);
	ball.setTexture(&tex_ball);

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
			// key pressed
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			{
				up = true;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				down = true;
			}

			// key released
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				up = false;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				down = false;
			}
		}

		// Logic
		if (up == true)
		{
			yVelocityPad1 = -5;
		}

		if (down == true)
		{
			yVelocityPad1 = 5;
		}
		
		if (up == true && down == true) 
		{
			yVelocityPad1 = 0;
		}

		if (up == false && down == false)
		{
			yVelocityPad1 = 0;
		}

		pad1.move(0, yVelocityPad1);

		// Out of bounds check
		if (pad1.getPosition().y < 0)
		{
			pad1.setPosition(50, 0);
		}

		if (pad1.getPosition().y > 500)
		{
			pad1.setPosition(50, 500);
		}	

		// Pad2
		if (ball.getPosition().y < pad2.getPosition().y)
		{
			yVelocityPad2 = -2;
		}

		if (ball.getPosition().y > pad2.getPosition().y)
		{
			yVelocityPad2 = 2;
		}

		pad2.move(0, yVelocityPad2);

		// Ball
		ball.move(xVelocityBall, yVelocityBall);

		if (ball.getPosition().y < 0)
		{
			yVelocityBall = -yVelocityBall;
		}

		if (ball.getPosition().y > 550)
		{
			yVelocityBall = -yVelocityBall;
		}

		if (ball.getPosition().x < -50)
		{
			pad2score++;
			ball.setPosition(300, 200);
		}

		if (ball.getPosition().x > 850)
		{
			pad1score++;
			ball.setPosition(300, 200);
		}

		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true)
		{
			xVelocityBall = -xVelocityBall;
			hit.play();
		}

		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds()) == true)
		{
			xVelocityBall = -xVelocityBall;
			hit.play();
		}

		//RENDERING
		window.clear();

		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);

		// Score
		std::stringstream text;
		text << pad1score << " : " << pad2score;
		score.setString(text.str());
		window.draw(score);

		window.display();
	}
	///////////

	//Clean up and close the window
	window.close();

	//Close the program
	return 0;
}
