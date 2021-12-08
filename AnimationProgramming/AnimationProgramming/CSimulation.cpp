#include "CSimulation.h"

void CSimulation::Init()
{
	skeleton.InitBones();
	skeleton.InitBonesTransform();
	skeleton.BindAnimation("ThirdPersonWalk.anim");
}

void CSimulation::Update(float frameTime)
{
	DrawAxis();
	skeleton.Update(frameTime);
	skeleton.Draw();
	HandleInput();
	inputManager.Update();
}

void CSimulation::DrawAxis()
{
	DrawLine(0, 0, 0, 50, 0, 0, 1, 0, 0);
	DrawLine(0, 0, 0, 0, 50, 0, 0, 1, 0);
	DrawLine(0, 0, 0, 0, 0, 50, 0, 0, 1);
}

void CSimulation::HandleInput()
{
	if (inputManager.IsKeyPressedEventOccured('2'))
	{
		skeleton.BindAnimation("ThirdPersonRun.anim");
	}
	if (inputManager.IsKeyPressedEventOccured('1'))
	{
		skeleton.BindAnimation("ThirdPersonWalk.anim");
	}
}
