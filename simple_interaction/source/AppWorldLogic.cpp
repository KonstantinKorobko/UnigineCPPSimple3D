/* Copyright (C) 2005-2022, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */

 /*
 * @author  Konstantin Korobko
 */

#include "AppWorldLogic.h"

 // World logic, it takes effect only when the world is loaded.
 // These methods are called right after corresponding world script's (UnigineScript) methods.

AppWorldLogic::AppWorldLogic()
{}

AppWorldLogic::~AppWorldLogic()
{}

int AppWorldLogic::init()
{
	Visualizer::setEnabled(true);

	Unigine::Console::setOnscreen(true);
	Unigine::Console::setFontSize(20);
	Unigine::Console::setMessageColor(Unigine::Math::vec4(0, 1, 0, 1));
	Unigine::Console::setWarningColor(Unigine::Math::vec4(0, 0, 1, 1));
	Unigine::Console::setErrorColor(Unigine::Math::vec4(1, 0, 0, 1));

	Unigine::ComponentSystem::get()->initialize();

	if (objGlobalRadar.getPlayer().get() == NULL)
	{
		VehicleFactory::constructVehicle(VehicleFactory::T_VEHICLE_PLAYER, objGlobalRadar);
	}

	spawnVehicle();
	// Write here code to be called on world initialization: initialize resources for your world scene during the world start.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
	if ((Input::isKeyPressed(Input::KEY_ANY_CTRL)) && (Input::isKeyUp(Input::KEY_C)))
	{
		VehicleFactory::constructVehicle(3, objGlobalRadar);
	}
	//World saving just for debuging in redactor. Vehicles should be delated manually in redactor.
	if ((Input::isKeyPressed(Input::KEY_ANY_CTRL)) && (Input::isKeyUp(Input::KEY_S)))
	{
		World::saveWorld();
	}
	// Write here code to be called before updating each render frame: specify all graphics-related functions you want to be called every frame while your application executes.
	return 1;
}

int AppWorldLogic::postUpdate()
{
	// The engine calls this function after updating each render frame: correct behavior after the state of the node has been updated.
	return 1;
}

int AppWorldLogic::updatePhysics()
{
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
	// Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr& stream)
{
	// Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr& stream)
{
	// Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
	UNIGINE_UNUSED(stream);
	return 1;
}

void AppWorldLogic::spawnVehicle()
{
	Math::Random rand;
	unsigned int seed = rand.getSeed();
	std::mt19937 random;
	random.seed(seed);
	std::uniform_real_distribution<> chanceRange(0.0, 1.0);
	std::uniform_real_distribution<> spawnRange(-20.0, 20.0);
	int type = VehicleFactory::T_VEHICLE_LIGHT;

	for (int i = 0; i < 10; i++)
	{
		float chance = chanceRange(random);		
		if (chance >= 0.90)
		{
			type = VehicleFactory::T_VEHICLE_HARD;
		}
		else if (chance >= 0.60)
		{
			type = VehicleFactory::T_VEHICLE_MIDDLE;
		}

		float posX = spawnRange(random);
		float posY = spawnRange(random);
		objGlobalRadar.setSpawnPos(posX, posY);

		VehicleFactory::constructVehicle(type, objGlobalRadar);
	}
}
