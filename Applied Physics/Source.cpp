#include<iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Go Physics!!");

	sf::RectangleShape ground;
	ground.setFillColor(sf::Color::Red);
	ground.setPosition(0, 700);
	ground.setSize(sf::Vector2f{ 800,100 });

	sf::CircleShape shape(.50f);
	shape.setFillColor(sf::Color::Green);

	sf::Vector2f velocity(0, 0);
	sf::Vector2f position(400, 699);

	sf::Vector2f gravity(0.0f, 9.8f);

	sf::Time currentTime;
	sf::Text timeInAir;
	sf::Font font;
 	font.loadFromFile("game_over.ttf");
	timeInAir.setCharacterSize(10);
	timeInAir.setFillColor(sf::Color::Blue);
	timeInAir.setFont(font);
	timeInAir.setPosition(50, 50);


	sf::Clock clock;

	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	clock.restart();

	while (window.isOpen())
	{

		//read keyboard inout
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				velocity = { 0,-50 };
				currentTime = sf::seconds(0.0f);
			}
		}



		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{

			if (position.y + 2.0 <= ground.getPosition().y || velocity.y < 0)
			{
				velocity = velocity + gravity * timeSinceLastUpdate.asSeconds();
				position = position + velocity * timeSinceLastUpdate.asSeconds() + (0.5f * gravity * (timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds()));
				currentTime += timeSinceLastUpdate;
				
				timeInAir.setString("Time: " + std::to_string(currentTime.asSeconds()));

			}
	


			window.clear();

			// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().


			//update shape on screen
			shape.setPosition(position);


			window.draw(shape);
			window.draw(ground);
			window.draw(timeInAir);

			window.display();
			timeSinceLastUpdate = sf::Time::Zero;
		}



	}

	return 0;
}

