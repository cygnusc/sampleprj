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

	//States for button/events
	bool aPressed = false;
	bool aReleased = false;
	bool space = false;
	bool leftClick = false;

	//Variables
	int numberOfClicks = 0;	//For counting the number of clicks
	int mouseX = 0, mouseY = 0;		//For storing the mouse position
	int rectXPosition = 0;	//Rectangles X position

	//Images
	sf::Texture image1; //Image/texture object
	

	//Render shapes
	//Rectangle shape
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 100)); //Width and height
	rect.setPosition(0, 0); //Position
	rect.setFillColor(sf::Color::White); //White fill color so we don't change the images colors
	//rect.setTexture(&image1); //Bind an image/texture to the rectangle

	//Circle shape
	sf::CircleShape circle;
	circle.setRadius(50); //Radius
	circle.setPosition(400, 300); //Position
	circle.setFillColor(sf::Color::Blue); //Color

	// font
	sf::Font font;
	if (font.loadFromFile("Data/arial.ttf") == 0)
	{
		return 1;
	}

	// text
	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(30);
	title.setString("Hello World!");
	title.setPosition(300, 50);
	title.setColor(sf::Color::Magenta);

	// Sounds
	sf::SoundBuffer ExplosionBuffer;
	if (ExplosionBuffer.loadFromFile("Data/explosion.wav") == 0)
	{
		return 1;
	}

	sf::Sound explosion;
	explosion.setBuffer(ExplosionBuffer);
	explosion.setVolume(200);
	//explosion.setLoop(true);
	explosion.play();

	// Music
	sf::Music anthem;
	if (anthem.openFromFile("Data/anthem.ogg") == 0)
	{
		return 1;
	}
	anthem.setVolume(200);
	anthem.play();
	

	//Game loop
	while (play == true)
	{
		//EVENTS
		while (window.pollEvent(event))
		{
			//Event type is key pressed and the key is 'A'
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				//Set the state to true
				aPressed = true;
			}

			//Event type is key released and the key is 'A'
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
			{
				aReleased = true;
			}

			//Space key pressed
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				space = true;
			}

			//Space key released
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				space = false;
			}

			//Left mouse button pressed down (clicked)
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				leftClick = true;
			}

			//Mouse moved in the window
			if (event.type == sf::Event::MouseMoved)
			{
				mouseX = event.mouseMove.x; //X position of the mouse
				mouseY = event.mouseMove.y; //Y position of the mouse
			}

			//Event type is window closed
			if (event.type == sf::Event::Closed)
			{
				//Set play to false in order to stop the game loop
				play = false;
			}
		}

		//LOGIC
		if (aPressed == true)
		{
			//Print to the console
			std::cout << "The A key has been pressed\n";

			aPressed = false;
		}

		if (aReleased == true)
		{
			std::cout << "The A key has been released\n";

			aReleased = false;
		}

		//If the left mouse button was clicked
		if (leftClick == true)
		{
			numberOfClicks++; //numberOfClicks = numberOfClicks + 1;

			std::cout << "Number of clicks is " << numberOfClicks << "\n";

			leftClick = false;
		}

		//Print out the position of the mouse.
		std::cout << "Mouse x: " << mouseX << " mouse y: " << mouseY << "\n";

		//Basic movement
		rectXPosition++; //X position variable of the rectangle
		rect.setPosition(rectXPosition, rectXPosition); //We set the rectangles X and Y position to the variable rectXPosition

		//RENDERING
		window.clear();

		window.draw(rect); //Draw the rectangle shape
		window.draw(circle); //Draw the circle shape
		window.draw(title);

		window.display();
	}
	///////////

	//Clean up and close the window
	window.close();

	//Close the program
	return 0;
}
