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
}

void CSimulation::DrawAxis()
{
	DrawLine(0, 0, 0, 50, 0, 0, 1, 0, 0);
	DrawLine(0, 0, 0, 0, 50, 0, 0, 1, 0);
	DrawLine(0, 0, 0, 0, 0, 50, 0, 0, 1);
}
