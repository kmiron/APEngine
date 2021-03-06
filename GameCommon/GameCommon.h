//
//  Game.h
//  RogueLikeBox
//
//  Created by Keith Miron on 2/18/15.
//  Copyright (c) 2015 Acoustic Games. All rights reserved.
//

#ifndef __RogueLikeBox__GameCommon__
#define __RogueLikeBox__GameCommon__

#pragma warning(disable:4244)

#include <stdio.h>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "HandleManager.h"
#include "RenderingSystem.h"
#include <stdint.h>

class System;
class Entity;

class Random
{
public:
	template<class T>
	static T Next(T min, T max)
	{
		std::uniform_int_distribution<T> uniform_dist(min, max);
		return uniform_dist(s_re);
	}

	template<>
	static double Next(double min, double max)
	{
		std::uniform_real_distribution<double> uniform_dist(min, max);
		return uniform_dist(s_re);
	}

	template<class T>
	static T NextNormal(T mean, T range)
	{
		std::normal_distribution<T> distribution(mean, range);
		return distribution(s_re);
	}

	static std::random_device s_rd;
	static std::linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647> s_re;
};

class GameCommon
{
public:
	GameCommon();
	~GameCommon();
	virtual void Init();
	void Draw(sf::RenderWindow* window);
	virtual void Update(float dt);

	Entity* CreateEntity();
	void RegisterSystem(System* system);

	void SetRenderSystem(RenderingSystem* system) { m_renderSystem = system;  }
	RenderingSystem* GetRenderSystem() { return m_renderSystem;  }

	void SetPaused(bool paused) { m_paused = paused; }
	void TogglePause() { m_paused = !m_paused; }
	bool IsPaused() { return m_paused; }
	void AdvanceFrames(int count) { m_advanceFrameCount += count; }
private:
	std::vector<System*> m_systems;
	std::vector<Entity*> m_objects;
	RenderingSystem* m_renderSystem;
	bool m_paused;
	int m_advanceFrameCount;
};

extern GameCommon* g_clientGame;
#endif /* defined(__RogueLikeBox__GameCommon__) */
