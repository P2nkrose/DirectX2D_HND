#include "pch.h"
//#include "qRigidBody.h"
//
//qRigidBody::qRigidBody()
//	: qComponent(COMPONENT_TYPE::RIGIDBODY)
//	, m_Mass(1.f)
//	, m_InitWalkSpeed(0.f)
//	, m_MaxWalkSpeed(0.f)
//	, m_MaxGravitySpeed(0.f)
//	, m_Friction(500.f)
//	, m_GravityAccel(980.f)
//	, m_UseGravity(false)
//	, m_JumpSpeed(400.f)
//	, m_DoubleJumpSpeed(500.f)
//	, m_GroundFunc(nullptr)
//	, m_AirFunc(nullptr)
//	, m_GroundInst(nullptr)
//	, m_AirInst(nullptr)
//	, m_GroundDelegate(nullptr)
//	, m_AirDelegate(nullptr)
//{
//}
//
//qRigidBody::qRigidBody(const qRigidBody& _Origin)
//	: qComponent(_Origin)
//	, m_Mass(_Origin.m_Mass)
//	, m_InitWalkSpeed(_Origin.m_InitWalkSpeed)
//	, m_MaxWalkSpeed(_Origin.m_MaxWalkSpeed)
//	, m_Friction(_Origin.m_Friction)
//	, m_GravityAccel(_Origin.m_GravityAccel)
//	, m_UseGravity(_Origin.m_UseGravity)
//	, m_JumpSpeed(_Origin.m_JumpSpeed)
//	, m_DoubleJumpSpeed(_Origin.m_DoubleJumpSpeed)
//	, m_GroundFunc(nullptr)
//	, m_AirFunc(nullptr)
//	, m_GroundInst(nullptr)
//	, m_AirInst(nullptr)
//	, m_GroundDelegate(nullptr)
//	, m_AirDelegate(nullptr)
//{
//}
//
//qRigidBody::~qRigidBody()
//{
//}
//
//void qRigidBody::FinalTick()
//{
//	Vec2 vObjPos = GetOwner()->GetPos();
//
//	// F = M x A
//	Vec2 vAccel = m_Force / m_Mass;
//
//	// ���ӵ�
//	// �߷��� ����� ��, ���߿��� ���� ����� ���
//	if (m_UseGravity && !m_Ground)
//	{
//		m_Velocity += vAccel * DT * 0.5f;
//	}
//	else
//	{
//		m_Velocity += vAccel * DT * 1.f;
//	}
//
//	// �ִ�ӵ� ����
//	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
//	{
//		m_Velocity.Normalize();
//		m_Velocity *= m_MaxWalkSpeed;
//	}
//
//	// �ּ� �ӵ� ����
//	if (m_InitWalkSpeed != 0.f && m_Velocity.Length() < 10.f && !vAccel.IsZero())
//	{
//		Vec2 vForceDir = m_Force;
//		vForceDir.Normalize();
//		m_Velocity = vForceDir * m_InitWalkSpeed;
//	}
//
//	// ���� RigidBody �� ����� ���� �����鼭, �ӵ��� �ִ� ���
//	// ������ ���ؼ� ���� �ӵ��� ���δ�.
//
//	if (m_Force.IsZero())
//	{
//		float Speed = m_Velocity.Length();
//
//
//		// �߷� ����� �װ�, ���� ������ ���
//		if (m_UseGravity && !m_Ground)
//		{
//			// ������ �� ���� �����Ѵ�.
//			Speed -= m_Friction * DT * 0.2f;
//		}
//		else
//		{
//			Speed -= m_Friction * DT;
//		}
//
//		// ������ ���ؼ� �ӵ��� ������ ���� ���� ���� ������,
//		// ���ҵ� �ӷ��� ũ�Ⱑ ������ ���� �ʰ� �����Ѵ�.
//		if (Speed < 0)
//			Speed = 0.f;
//
//		if (!m_Velocity.IsZero())
//			m_Velocity.Normalize();
//
//		m_Velocity *= Speed;
//	}
//
//
//	// �߷� ���ӵ��� ���� �ӵ� ����
//	if (m_UseGravity && !m_Ground && !m_Rope)
//	{
//		m_VelocityByGravity += Vec2(0.0f, 1.f) * m_GravityAccel * DT;
//
//		if (0.f != m_MaxGravitySpeed && m_MaxGravitySpeed < m_VelocityByGravity.Length())
//		{
//			m_VelocityByGravity.Normalize();
//			m_VelocityByGravity *= m_MaxGravitySpeed;
//		}
//	}
//
//	// ���� �ӵ�
//	Vec2 vFinalVelocity = m_Velocity + m_VelocityByGravity;
//
//
//	// ���� �ӵ��� ���� �̵�
//	// �ӵ� = �Ÿ� / �ð�
//	vObjPos += vFinalVelocity * DT;
//	GetOwner()->SetPos(vObjPos);
//
//	// �̹� ������ �� �ʱ�ȭ
//	m_Force = Vec2(0.f, 0.f);
//	m_AddVelocity = Vec2(0.f, 0.f);
//
//
//}
//
//
//void qRigidBody::jump()
//{
//}
//
//void qRigidBody::doublejump()
//{
//}
//
//
//void qRigidBody::SaveToFile(FILE* _File)
//{
//}
//
//void qRigidBody::LoadFromFile(FILE* _File)
//{
//}