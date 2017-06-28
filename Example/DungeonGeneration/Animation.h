#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector3D.h"
class Animation
{
private:
	const float FRAMES_PER_SECOND = 10;
	float timeAccum;
	sf::RectangleShape sprite;//TODO: Sólo cargar una vez para todas las animaciones
public:
	sf::Texture* texture;
	enum ANIMATION_TYPE
	{
		attackN,
		attackNW,
		attackS,
		attackSW,
		attackW,
		dieN,
		dieNW,
		dieS,
		dieSW,
		dieW,
		idleN,
		idleNW,
		idleS,
		idleSW,
		idleW,
		runN,
		runNW,
		runS,
		runSW,
		runW
	};
	struct Frame
	{
		int16_t x, y, w, h;
		bool rotated, trimmed;
		int16_t spriteSourceSizeX, spriteSourceSizeY, spriteSourceSizeW, spriteSourceSizeH;
		int16_t sourceSizeW, sourceSizeH;
	};
	std::vector<Frame> frames;
	Animation();
	void Init();
	void OnEnter();
	void Update(float delta, Vector3D pos);
	void Render();
	~Animation();
};

class AnimationLoader
{
public:
	std::vector<Animation> Load(const char* file);
};

