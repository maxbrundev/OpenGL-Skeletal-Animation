#pragma once

#include "Simulation.h"
#include "Skeleton.h"

class CSimulation : public ISimulation
{
	Animation::Skeleton skeleton;

	void Init() override;
	void Update(float frameTime) override;

	void DrawAxis();
};
