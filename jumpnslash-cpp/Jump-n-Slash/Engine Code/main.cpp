#include "JumpSlashEngine.h"

int main()
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
	//sf::CircleShape shape(100.0f);
	//shape.setFillColor(sf::Color::Green);

	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//		{
	//			window.close();
	//		}
	//	}

	//	window.clear();
	//	window.draw(shape);
	//	window.display();
	//}

	JumpSlashEngine::Run();

	JumpSlashEngine::Terminate();

	return 0;
}