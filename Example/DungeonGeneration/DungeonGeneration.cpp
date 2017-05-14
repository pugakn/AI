// DungeonGeneration.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "DungeonMap.h"
#include <vector>
#include <thread>

const int NUM_BLOCKS = 200;
int main()
{
	const sf::Uint32 winWidth = 1080;
	const sf::Uint32 winHeight = 680;
	const float MOVE_AREA_X = 300;
	const float MOVE_AREA_Y = 150;
	const float CAM_VEL = 1;
	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Map");
	std::vector<sf::RectangleShape> shapes;


	DungeonMapData tmpData;
	tmpData.m_blockMinSize = Vector3D(5, 5, 5);
	tmpData.m_blockMaxSize = Vector3D(150, 100, 80);
	tmpData.m_fMinSpanningTreeProbability = 1;
	tmpData.m_fSpawnRadius = 30;
	tmpData.m_initialPos = Vector3D(512, 768 / 2.f, 0);
	tmpData.m_iNumBlocks = NUM_BLOCKS;
	tmpData.m_iSeed = 6697;
	tmpData.m_minValidSize = Vector3D(30, 40, 0);
	tmpData.m_fMinSeparation = 0.f;
	DungeonMap map;
	std::thread mapThread([&map, tmpData]() {map.GenerateMap(tmpData); });
#if !VISUAL_DEBUG_MODE
	mapThread.join();
#endif
	shapes.resize(NUM_BLOCKS);
	for (size_t i = 0; i < shapes.size(); ++i)
	{
		shapes[i].setFillColor(sf::Color::Green);
		shapes[i].setOutlineColor(sf::Color::Red);
		shapes[i].setOutlineThickness(2);
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
#if VISUAL_DEBUG_MODE
		map.m_mutex.lock();
#endif
		for (int i = 0; i < map.m_blocks.size(); ++i)
		{
			shapes[i].setSize(sf::Vector2f(map.m_blocks[i].size.x, map.m_blocks[i].size.y));
			shapes[i].setPosition(sf::Vector2f(map.m_blocks[i].position.x, map.m_blocks[i].position.y));
			shapes[i].setOrigin(shapes[i].getSize() / 2.f);
		}
		shapes.resize(map.m_blocks.size());
#if VISUAL_DEBUG_MODE
		map.m_mutex.unlock();
#endif

		auto pos = sf::Mouse::getPosition(window);

		if ((winWidth - pos.x)< MOVE_AREA_X)
		{
			float factor = (MOVE_AREA_X - winWidth + pos.x) / MOVE_AREA_X;
			float move = CAM_VEL * factor;
			sf::View biew = window.getView();
			biew.move(move, 0);
			window.setView(biew);
		}
		if ((pos.x)< MOVE_AREA_X)
		{
			float factor = (MOVE_AREA_X - pos.x) / MOVE_AREA_X;
			sf::View biew = window.getView();
			float move = CAM_VEL * factor;
			biew.move(-move, 0);
			window.setView(biew);
		}
		if ((winHeight - pos.y)< MOVE_AREA_Y)
		{
			float factor = (MOVE_AREA_Y - winHeight + pos.y) / MOVE_AREA_Y;
			sf::View biew = window.getView();
			float move = CAM_VEL * factor;
			biew.move(0, move);
			window.setView(biew);
		}
		if ((pos.y)< MOVE_AREA_Y)
		{
			float factor = (MOVE_AREA_Y - pos.y) / MOVE_AREA_Y;
			sf::View biew = window.getView();
			float move = CAM_VEL * factor;
			biew.move(0, -move);
			window.setView(biew);
		}

		window.clear();
		for (auto &shape : shapes)
		{
			window.draw(shape);
		}
		window.display();
	}
#if VISUAL_DEBUG_MODE
	mapThread.join();
#endif
	return 0;
}

