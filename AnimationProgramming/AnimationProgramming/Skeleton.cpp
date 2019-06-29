#include "Skeleton.h"

#include <Engine.h>
#include "Transform.h"
Animation::Skeleton::Skeleton()
{
	timeSinceLastUpdate = 0.0f;
	timeToUpdate = 0.03333f;
}

void Animation::Skeleton::InitBones()
{
	m_boneCount = GetSkeletonBoneCount() - 7; //-7 for IK 
	m_bones.reserve(m_boneCount);

	Bone bone;

	for(int i = 0; i < m_boneCount; i++)
	{
		bone.SetupBoneIndex(i);
		m_bones.push_back(bone);
	}
}

void Animation::Skeleton::InitBonesTransform()
{
	float xPos;
	float yPos;
	float zPos;

	float rValue;
	float xValue;
	float yValue;
	float zValue;

	for (int i = 0; i < m_boneCount; i++)
	{
		GetSkeletonBoneLocalBindTransform(m_bones[i].GetIndex(), xPos, yPos, zPos, rValue, xValue, yValue, zValue);
		
		Component::Transform* transform = &m_bones[i].GetTransform();
		transform->SetLocalPosition(xPos, yPos, zPos);
		transform->SetLocalRotation(rValue, xValue, yValue, zValue);
		transform->NormalizeLocalRotation();
		transform->InitLocalTransform();

		if(m_bones[i].isParented())
		{
			transform->GetWorldMatrix() = GetBonesByIndex(m_bones[i].GetParentIndex()).GetTransform().GetWorldMatrix() * m_bones[i].GetTransform().GetLocalMatrix();
		}
		else
		{
			transform->GetWorldMatrix() = m_bones[i].GetTransform().GetLocalMatrix();
		}

		transform->GetInitialMatrix() = m_bones[i].GetTransform().GetLocalMatrix();
		transform->GetInitialWorldMatrix() = m_bones[i].GetTransform().GetWorldMatrix();
		transform->GetOldPosition() = m_bones[i].GetTransform().GetInitialPosition();
		transform->GetOldRotation() = m_bones[i].GetTransform().GetInitialRotation();
		transform->GetNewPosition() = m_bones[i].GetTransform().GetInitialPosition();
		transform->GetNewRotation() = m_bones[i].GetTransform().GetInitialRotation();
	}
}

void Animation::Skeleton::Update(float deltaTime)
{
	timeSinceLastUpdate += deltaTime;

	while (timeSinceLastUpdate >= timeToUpdate)
	{
		UpdateAnimation();
		m_currentKeyFrame++;
		timeSinceLastUpdate -= timeToUpdate;

		if (m_currentKeyFrame == m_keyCount)
			m_currentKeyFrame = 0;
	}
	LerpAnimation();
	UpdateMesh();
}

void Animation::Skeleton::UpdateAnimation()
{
	float xPos;
	float yPos;
	float zPos;

	float rValue;
	float xValue;
	float yValue;
	float zValue;

	AltMath::Vector3<float> animPos;
	AltMath::Quaternion animRot;

	for (int i = 0; i < m_boneCount; i++)
	{
		GetAnimLocalBoneTransform(m_animationName.c_str(), m_bones[i].GetIndex(), m_currentKeyFrame, xPos, yPos, zPos, rValue, xValue, yValue, zValue);

		animPos.x = xPos;
		animPos.y = yPos;
		animPos.z = zPos;

		animRot.SetXAxisValue(xValue);
		animRot.SetYAxisValue(yValue);
		animRot.SetZAxisValue(zValue);
		animRot.SetRealValue(rValue);

		if (!animRot.IsNormalized())
		{
			animRot.Normalize();
		}
		Component::Transform* transform = &m_bones[i].GetTransform();
		transform->GetOldPosition() = m_bones[i].GetTransform().GetNewPosition();
		transform->GetOldRotation() = m_bones[i].GetTransform().GetNewRotation();
		transform->GetNewPosition() = animPos;
		transform->GetNewRotation() = animRot;
	}
}

void Animation::Skeleton::BindAnimation(const std::string& p_file)
{
	m_currentKeyFrame = 0.0f;
	m_keyCount = GetAnimKeyCount(p_file.c_str());
	m_animationName = p_file;
}

void Animation::Skeleton::LerpAnimation()
{
	AltMath::Vector3<float> position;
	AltMath::Quaternion		rotation;

	float coefficient = timeSinceLastUpdate / timeToUpdate;

	for (int i = 0; i < m_bones.size(); i++)
	{
		position = AltMath::Vector3F::Lerp(m_bones[i].GetTransform().GetOldPosition(), m_bones[i].GetTransform().GetNewPosition(), coefficient);
		rotation = AltMath::Quaternion::Slerp(m_bones[i].GetTransform().GetOldRotation(), m_bones[i].GetTransform().GetNewRotation(), coefficient);
		Component::Transform* transform = &m_bones[i].GetTransform();
		transform->GetLocalMatrix() = AltMath::Matrix4F::Translation(position) * rotation.ToMatrix4();

		transform->GetLocalMatrix() = m_bones[i].GetTransform().GetInitialMatrix() *  m_bones[i].GetTransform().GetLocalMatrix();

		if (m_bones[i].isParented())
		{
			transform->GetWorldMatrix() = GetBonesByIndex(m_bones[i].GetParentIndex()).GetTransform().GetWorldMatrix() * m_bones[i].GetTransform().GetLocalMatrix();
		}
		else
		{
			transform->GetWorldMatrix() = m_bones[i].GetTransform().GetLocalMatrix();
		}
	}
}

Animation::Bone& Animation::Skeleton::GetBonesByIndex(int p_index)
{
	for (int i = 0; i < m_bones.size(); i++)
	{
		if (m_bones[i].GetIndex() == p_index)
			return m_bones[i];
	}
}

void Animation::Skeleton::Draw()
{
	for(int i = 0; i < m_boneCount; i++)
	{
		m_bones[i].DrawJoint();

		if(m_bones[i].isParented())
		{
			DrawLine(m_bones[i].GetTransform().GetWorldMatrix().GetColumn(3).x, m_bones[i].GetTransform().GetWorldMatrix().GetColumn(3).y - 100, m_bones[i].GetTransform().GetWorldMatrix().GetColumn(3).z, GetBonesByIndex(m_bones[i].GetParentIndex()).GetTransform().GetWorldMatrix().GetColumn(3).x, GetBonesByIndex(m_bones[i].GetParentIndex()).GetTransform().GetWorldMatrix().GetColumn(3).y - 100, GetBonesByIndex(m_bones[i].GetParentIndex()).GetTransform().GetWorldMatrix().GetColumn(3).z, 1, 1, 0);
		}
	}
}

void Animation::Skeleton::UpdateMesh()
{
	std::vector<float> matrices;

	for (int i = 0; i < m_bones.size(); i++)
	{
		AltMath::Matrix4F meshWorldMatrix = m_bones[i].GetTransform().GetWorldMatrix() * m_bones[i].GetTransform().GetInitialWorldMatrix().Inverse();

		for (int j = 0; j < 16; j++)
		{
			matrices.push_back(meshWorldMatrix.ToArray()[j]);
		}
	}

	SetSkinningPose(matrices.data(), m_boneCount);
}