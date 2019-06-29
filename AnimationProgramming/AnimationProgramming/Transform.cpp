#include "Transform.h"

Component::Transform::Transform() : m_worldPosition(1.0f, 1.0f, 1.0f), m_localPosition(1.0f, 1.0f, 1.0f)
{
}

void Component::Transform::NormalizeLocalRotation()
{
	if (!m_localRotation.IsNormalized())
	{
		m_localRotation.Normalize();
	}
}

void Component::Transform::InitLocalTransform()
{
	m_localTransform = AltMath::Matrix4F::Translation(m_localPosition) * m_localRotation.ToMatrix4();
}

AltMath::Matrix4F& Component::Transform::GetWorldMatrix()
{
	return m_worldTransform;
}

AltMath::Matrix4F& Component::Transform::GetLocalMatrix()
{
	return m_localTransform;
}

AltMath::Matrix4F& Component::Transform::GetInitialMatrix()
{
	return m_initialTransform;
}

AltMath::Matrix4F& Component::Transform::GetInitialWorldMatrix()
{
	return m_initialWorldTransform;
}

AltMath::Vector3<float>& Component::Transform::GetWorldPosition()
{
	return m_worldPosition;
}

AltMath::Quaternion& Component::Transform::GetWorldRotation()
{
	return m_worldRotation;
}

AltMath::Vector3<float>& Component::Transform::GetLocalPosition()
{
	return m_localPosition;
}

AltMath::Quaternion & Component::Transform::GetLocalRotation()
{
	return m_localRotation;
}

AltMath::Vector3<float>& Component::Transform::GetInitialPosition()
{
	return m_initalPosition;
}

AltMath::Quaternion& Component::Transform::GetInitialRotation()
{
	return m_initalRotation;
}

AltMath::Vector3<float>& Component::Transform::GetOldPosition()
{
	return m_oldPosition;
}

AltMath::Quaternion& Component::Transform::GetOldRotation()
{
	return m_oldRotation;
}

AltMath::Vector3<float>& Component::Transform::GetNewPosition()
{
	return m_newPosition;
}

AltMath::Quaternion& Component::Transform::GetNewRotation()
{
	return m_newRotation;
}

void Component::Transform::SetLocalPosition(float p_x, float p_y, float p_z)
{
	m_localPosition.x = p_x;
	m_localPosition.y = p_y;
	m_localPosition.z = p_z;
}

void Component::Transform::SetLocalPosition(const AltMath::Vector3<float>& p_position)
{
	m_localPosition = p_position;
}

void Component::Transform::SetLocalRotation(float p_r, float p_x, float p_y, float p_z)
{
	m_localRotation.SetRealValue(p_r);
	m_localRotation.SetXAxisValue(p_x);
	m_localRotation.SetYAxisValue(p_y);
	m_localRotation.SetZAxisValue(p_z);
}

void Component::Transform::SetLocalRotation(const AltMath::Quaternion & p_rotation)
{
	m_localRotation = p_rotation;
}