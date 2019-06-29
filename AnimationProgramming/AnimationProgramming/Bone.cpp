#include "Bone.h"
#include <Simulation.h>

Animation::Bone::Bone() : m_index(0), m_parentIndex(0), hasParent(false) {}

void Animation::Bone::SetupBoneIndex(int p_index)
{
	m_index = p_index;
	m_parentIndex = GetSkeletonBoneParentIndex(m_index);

	//hasParent = (m_parentIndex == -1) ? false : true;

	//hasParent = !(m_parentIndex == -1);
	hasParent = m_parentIndex != -1;
	/*if(m_parentIndex == -1)
	{
		hasParent = false;
	}
	else
	{
		hasParent = true;
	}*/
}

void Animation::Bone::DrawJoint()
{
	AltMath::Vector4<float> position(m_transform.GetWorldMatrix().GetColumn(3));

	DrawLine(position.x - 2, position.y - 100, position.z, position.x + 2, position.y - 100, position.z, 0, 0, 0);

	DrawLine(position.x, position.y - 100, position.z - 2, position.x, position.y - 100, position.z + 2, 0, 0, 0);
}

Component::Transform& Animation::Bone::GetTransform()
{
	return m_transform;
}

int Animation::Bone::GetIndex() const
{
	return m_index;
}

int Animation::Bone::GetParentIndex() const
{
	return m_parentIndex;
}

bool Animation::Bone::isParented() const
{
	return hasParent;
}