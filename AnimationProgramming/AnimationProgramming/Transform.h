#pragma once

#include "AltMath.h"

namespace Component
{
	class Transform
	{
	private:
		AltMath::Matrix4<float>		m_worldTransform;
		AltMath::Matrix4<float>		m_localTransform;
		AltMath::Matrix4<float>		m_initialTransform;
		AltMath::Matrix4<float>		m_initialWorldTransform;

		AltMath::Quaternion			m_worldRotation;
		AltMath::Quaternion			m_localRotation;
		AltMath::Quaternion			m_initalRotation;
		AltMath::Quaternion			m_oldRotation;
		AltMath::Quaternion			m_newRotation;

		AltMath::Vector3<float>		m_worldPosition;
		AltMath::Vector3<float>		m_localPosition;
		AltMath::Vector3<float>		m_initalPosition;
		AltMath::Vector3<float>		m_oldPosition;
		AltMath::Vector3<float>		m_newPosition;

	public:
		Transform();
		~Transform() = default;

		void NormalizeLocalRotation();
		void InitLocalTransform();
		
		AltMath::Matrix4F&			GetWorldMatrix();
		AltMath::Matrix4F&			GetLocalMatrix();
		
		AltMath::Matrix4F&			GetInitialMatrix();
		AltMath::Matrix4F&			GetInitialWorldMatrix();

		AltMath::Vector3<float>&	GetWorldPosition();
		AltMath::Quaternion&		GetWorldRotation();

		AltMath::Vector3<float>&	GetLocalPosition();
		AltMath::Quaternion&		GetLocalRotation();

		AltMath::Vector3<float>&	GetInitialPosition();
		AltMath::Quaternion&		GetInitialRotation();

		AltMath::Vector3<float>&	GetOldPosition();
		AltMath::Quaternion&		GetOldRotation();

		AltMath::Vector3<float>&	GetNewPosition();
		AltMath::Quaternion&		GetNewRotation();

		void SetLocalPosition(float p_x, float p_y, float p_z);
		void SetLocalPosition(const AltMath::Vector3<float>& p_position);
		void SetLocalRotation(float p_r, float p_x, float p_y, float p_z);
		void SetLocalRotation(const AltMath::Quaternion& p_rotation);
	};
}