#pragma once

#include "Transform.h"

namespace Animation
{
	class Bone
	{
	private:
		Component::Transform m_transform;
		
		int		m_index;
		int		m_parentIndex;
		bool	hasParent;

	public:
		Bone();
		~Bone() = default;

		void SetupBoneIndex(int p_index);
		void DrawJoint();

		Component::Transform& GetTransform();
		int GetIndex() const;
		int GetParentIndex() const;
		bool isParented() const;
	};
}