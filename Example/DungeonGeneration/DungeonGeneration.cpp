// DungeonGeneration.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <thread>
#include "sfLineT.h"
#include <conio.h>
#include "GameObjects\World.h"
extern const sf::Uint32 winWidth ;
extern const sf::Uint32 winHeight ;
sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Map");
int main()
{
	sf::Clock clock; 
	window.setFramerateLimit(60);
	CWorld world;
	world.Init();
	std::thread mapThread([&world]() {world.InitMap(); });
#if !VISUAL_DEBUG_MODE
	mapThread.join();
#endif
	auto t = clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		world.Update(t.asSeconds(),window);

		window.clear();
		world.Render(window);
		window.display();
		t = clock.restart();
	}
	world.Destroy();
#if VISUAL_DEBUG_MODE
	mapThread.join();
#endif
	return 0;
}

