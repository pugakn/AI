// DungeonGeneration.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "DungeonMap.h"
#include <vector>
#include <thread>
#include "sfLineT.h"
#include <conio.h>


int main()
{
	const sf::Uint32 winWidth = 1080;
	const sf::Uint32 winHeight = 680;
	const float MOVE_AREA_X = 300;
	const float MOVE_AREA_Y = 150;
	const float CAM_VEL = 30;

	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Map");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Edges: ");
	text.setCharacterSize(24); 
	text.setFillColor(sf::Color::Red);

	std::vector<sf::RectangleShape> shapes;
	std::vector<std::vector<sf::Vertex>> lines;
	std::vector<std::vector<sfLine>> corridors;

	const int NUM_BLOCKS = 100;
	DungeonMapData tmpData;
	tmpData.m_blockMinSize = Vector2Di(5, 5);
	tmpData.m_blockMaxSize = Vector2Di(100, 100);
	tmpData.m_iMinSpanningTreeProbability = 85;
	tmpData.m_fSpawnRadius = 30;
	tmpData.m_initialPos = Vector2Di(512, 768 / 2.f);
	tmpData.m_iNumBlocks = NUM_BLOCKS;
	tmpData.m_iSeed = 666366;
	tmpData.m_minValidSize = Vector2Di(50, 50);
	tmpData.m_fMinSeparation = 3.f;
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

		//for (auto &edge : map.m_finalEdges)
		//{
		//	std::vector<sf::Vertex> tmp;
		//	sf::Vertex v1(sf::Vector2f(edge.p1.p.x,edge.p1.p.y));
		//	sf::Vertex v2(sf::Vector2f(edge.p2.p.x, edge.p2.p.y));
		//	//sf::Vertex v3(sf::Vector2f(triangle.p3.x, triangle.p3.y));
		//	tmp.push_back(v1);
		//	tmp.push_back(v2);
		//	lines.push_back(tmp);
		//}
		static bool first = true;
		if (first) {
			if (map.m_blocks[0].graphConnections.size() != 0){
				for (auto &block : map.m_blocks)
				{
					std::vector<sf::Vertex> tmp;
					for (auto &con : block.graphConnections)
					{
						sf::Vertex v1(sf::Vector2f(block.position.x, block.position.y));
						sf::Vertex v2(sf::Vector2f(con->position.x, con->position.y));
						tmp.push_back(v1);
						tmp.push_back(v2);
					}
					//sf::Vertex v3(sf::Vector2f(triangle.p3.x, triangle.p3.y));
					lines.push_back(tmp);
				}
				first = false;
				text.setString("Edges: " + std::to_string(map.m_finalEdges.size()));
			}

			if (map.m_corridors.size() != 0) {
				for (auto &corridor : map.m_corridors)
				{
					std::vector<sfLine> tmp;
					//for (auto &corridorPoint : corridor.points)
					//{
					sf::Vector2f v1(corridor.points[0].x, corridor.points[0].y);
					sf::Vector2f v2(corridor.points[1].x, corridor.points[1].y);
					tmp.push_back(sfLine(v1,v2));
					tmp.back().SetColor( sf::Color::Red);
					v1 = sf::Vector2f(corridor.points[1].x, corridor.points[1].y);
					v2 = sf::Vector2f(corridor.points[2].x, corridor.points[2].y);
					tmp.push_back(sfLine(v1, v2));
					tmp.back().SetColor(sf::Color::Red);

					//}
					corridors.push_back(tmp);
				}
				first = false;
			}
		}

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
		sf::RenderStates rs;
		if (map.m_corridors.size() != 0) {
			for (int i = 0; i < corridors.size(); i++)
			{
				for (int j = 0; j < 2; j++)
				{
					corridors[i][j].draw(window, rs);
				}
			}
		}

		//for (auto &it : lines)
		//{
		//	window.draw(&it[0], it.size(), sf::LinesStrip);
		//}


		//for (auto &it : corridors)
		//{
		//	//window.draw(&it[0], it.size(), sf::LinesStrip);
		//	window.draw(&corridors[0][0], corridors[0].size(), sf::LinesStrip);
		//}
		//static int num = 0;
		//static float t = 0;
		//t += 0.02;
		//if (t > 1 && num < corridors.size()-1)
		//{
		//	num++;
		//	t = 0;
		//}
		//window.draw(&corridors[0].back(), corridors.size(), sf::LinesStrip);

		window.draw(text);
		window.display();
	}
#if VISUAL_DEBUG_MODE
	mapThread.join();
#endif
	return 0;
}

