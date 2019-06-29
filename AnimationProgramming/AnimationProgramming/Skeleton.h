#pragma once

#include "Bone.h"

namespace Animation
{
	class Skeleton
	{
	private:
		std::vector<Bone>	m_bones;
		size_t				m_currentKeyFrame;
		size_t				m_keyCount;
		size_t				m_boneCount;
		std::string			m_animationName;

		float timeToUpdate;
		float timeSinceLastUpdate;

	public:
		Skeleton();
		~Skeleton() = default;

		void InitBones();
		void InitBonesTransform();
		void Update(float deltaTime);
		void UpdateAnimation();
		void BindAnimation(const std::string& p_file);
		void LerpAnimation();
		void Draw();
		void UpdateMesh();
		
		Bone& GetBonesByIndex(int p_index);
	};
}