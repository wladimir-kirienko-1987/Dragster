#include "MainScene.h"
#include <iostream>

USING_NS_CC;

Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto bg_sprite = Sprite::create("bg.png");
	bg_sprite->setPosition(640 / 2, 480 / 2);
	this->addChild(bg_sprite, 0);

	sprite = Sprite::create("dragster-300px.png");
	sprite->setPosition(640 / 2, 480 / 2);
	this->addChild(sprite, 0);
	auto flip = cocos2d::FlipX::create(true);
	sprite->runAction(flip);
	this->scheduleUpdate();
	return true;
}

void MainScene::update(float delta){
	auto position = sprite->getPosition();
	position.x += 350 * delta;
	if (position.x  > 640 + 150)
		position.x = -150;
	sprite->setPosition(position);
}
