#pragma once

#include "cocos2d.h"
#include <iostream>
#include <string>
#include <chrono>

class  MainScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init() override;;
	CREATE_FUNC(MainScene);
	void update(float) override;
private:
	bool keep_motion;
	bool increase_speed;
	bool finish;
	bool early;
	int overdrive;
	long long counter;
	int start_time;
	float cur_step;

	std::chrono::steady_clock::time_point start;
	cocos2d::Sprite* sprite;
	cocos2d::Sprite* bg_sprite;
	cocos2d::Label* label;
	cocos2d::Label* speed_label;
	cocos2d::Label* time_label;
};

