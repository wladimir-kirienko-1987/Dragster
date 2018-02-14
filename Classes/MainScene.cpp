#include "MainScene.h"


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

	keep_motion = false;
	increase_speed = false;
	finish = false;
	counter = 0;
	start_time = 9;
	cur_step = 0;
	early = false;

	bg_sprite = Sprite::create("bg1.png");
	bg_sprite->setPosition(640 / 2, 480 / 2);
	this->addChild(bg_sprite, 0);
	
	overdrive = 0;

	label = Label::createWithSystemFont("N", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	label->setTextColor(Color4B::BLACK);
	this->addChild(label, 1);

	speed_label = Label::createWithSystemFont("0", "Arial", 96);
	speed_label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	speed_label->setPositionX(420);
	speed_label->setTextColor(Color4B::BLACK);
	//speed_label->setHorizontalAlignment(TextHAlignment::RIGHT);
	this->addChild(speed_label, 1);
	
	time_label = Label::createWithSystemFont("0", "Arial", 96);
	time_label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	time_label->setPositionX(110);
	time_label->setTextColor(Color4B::BLACK);
	//time_label->setLineHeight(1);
	//speed_label->setHorizontalAlignment(TextHAlignment::RIGHT);
	this->addChild(time_label, 1);

	sprite = Sprite::create("dragster-300px.png");
	sprite->setPosition(640 / 2 - 200, 480 / 2);
	this->addChild(sprite, 0);
	auto flip = cocos2d::FlipX::create(true);
	sprite->runAction(flip);
	this->scheduleUpdate();

	auto action = cocos2d::ScaleBy::create(0, static_cast<float>(0.8));
	sprite->runAction(action);

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event){
		if (keyCode == EventKeyboard::KeyCode::KEY_W){
			keep_motion = true;
			increase_speed = true;
		}

		if (keyCode == EventKeyboard::KeyCode::KEY_E){
			if (!increase_speed && overdrive<4) label->setString(std::to_string(++overdrive));
			if (start_time > 0){
				time_label->setString("EARLY");
				early = true;
			}
		}
		
		if (keyCode == EventKeyboard::KeyCode::KEY_Q){
			auto *pScene = MainScene::createScene();
			CCDirector::getInstance()->replaceScene(pScene);
		}
	};

	eventListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event){
		if (keyCode == EventKeyboard::KeyCode::KEY_W){
			//keep_motion = false;
			increase_speed = false;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);

	return true;
}

void MainScene::update(float delta){

	if (counter < 500 && (counter++ % 30 == 0) && !early){
		time_label->setString(std::to_string(start_time--));
		start = std::chrono::steady_clock::now();
	}

	if (start_time < 0 && !finish && !early){
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		if (time_span.count() < 10.0)
			time_label->setString(std::to_string(time_span.count()).substr(0,4));
		else
			time_label->setString(std::to_string(time_span.count()).substr(0,5));
	}

	if (keep_motion && overdrive && !finish){

		if (cur_step < 1000.0)
			speed_label->setString(std::to_string(cur_step).substr(0, 3));
		else
			speed_label->setString(std::to_string(cur_step).substr(0, 4));

		if (increase_speed){
			float increase = 8.0;
			float max_step = 700 * overdrive;

			if (cur_step < max_step)
				cur_step += (increase / overdrive);
		}
		else{
			if (cur_step > 0.0)
				cur_step -= 10;
			else{
				cur_step = double();
				keep_motion = false;
				speed_label->setString(std::to_string(0));
			}
		}

		auto position = sprite->getPosition();
		position.x += (cur_step / 70) * delta;
		if (position.x > 640 - 120)
			finish = true;
		sprite->setPosition(position);

		auto position_ = bg_sprite->getPosition();
		position_.x -= cur_step * delta;
		if (position_.x < 30)
			position_.x = 630;
		bg_sprite->setPosition(position_);

	}
}
