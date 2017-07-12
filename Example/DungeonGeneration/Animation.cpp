#include "stdafx.h"
#include "Animation.h"
#include <fstream>
extern sf::RenderWindow window;
Animation::Animation()
{
}

void Animation::Init()
{
	texture = new sf::Texture();
	if(!texture->loadFromFile("Anim/champion.png"))
		exit(-1);
	sprite.setTexture(texture);
	sprite.setSize((sf::Vector2f)texture->getSize());
	sprite.setOutlineColor(sf::Color::Red);
	sprite.setOutlineThickness(1.0);
}

void Animation::OnEnter()
{
	timeAccum = 0;
}

void Animation::Update(float delta,Vector3D pos,bool flip )
{
	timeAccum += delta;
	int index = (int)(timeAccum*FRAMES_PER_SECOND);
	if (index >= frames.size())
		index = index % frames.size();
	auto actualFrame = frames[index];
	
	sprite.setSize(sf::Vector2f(actualFrame.spriteSourceSizeW, actualFrame.spriteSourceSizeH));
	sprite.setPosition(sf::Vector2f(actualFrame.spriteSourceSizeX,actualFrame.spriteSourceSizeY) + sf::Vector2f(pos.x,pos.y) - sf::Vector2f(80.f,80.f)) ;
	sprite.setTextureRect(sf::IntRect(actualFrame.x, actualFrame.y, actualFrame.w, actualFrame.h));
	sprite.setScale(sf::Vector2f(flip ? -1.0 : 1.0, 1.0));
	sprite.setOrigin(flip ? sf::Vector2f(sprite.getSize().x, 0) :sf::Vector2f(0,0));
}

void Animation::Render()
{
	window.draw(sprite);
}

Animation::~Animation()
{
}

std::vector<Animation> AnimationLoader::Load(const char * file)
{
	std::vector<Animation> animationSet;
	std::ifstream input(file, std::ios::binary);
	
	input.seekg(0, input.end);
	std::streamsize size = input.tellg();
	input.seekg(0, std::ios::beg);
	char * buff = new char[size];
	input.read(buff,size);

	uint32_t framesSize = *reinterpret_cast<uint32_t*>(&buff[0]);

	std::vector<uint16_t> animFramesNum;
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[4]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[6]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[8]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[10]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[12]));

	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[14]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[16]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[18]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[20]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[22]));

	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[24]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[26]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[28]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[30]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[32]));

	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[34]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[36]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[38]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[40]));
	animFramesNum.push_back(*reinterpret_cast<uint16_t*>(&buff[42]));

	short startByte = 44;
	for (size_t i = 0; i< animFramesNum.size(); i++)
	{
		Animation anim;
		std::vector<Animation::Frame> frameVec(reinterpret_cast<Animation::Frame*>(&buff[startByte]), reinterpret_cast<Animation::Frame*>(&buff[startByte]) + animFramesNum[i]);
		anim.frames = frameVec;
		startByte += animFramesNum[i]*sizeof(Animation::Frame);
		animationSet.push_back(anim);
	}

	delete[] buff;
	return animationSet;
}
