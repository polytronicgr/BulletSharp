#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Generic6DofConstraint.h"
#include "RigidBody.h"

RotationalLimitMotor::RotationalLimitMotor()
{
	motor = new btRotationalLimitMotor();
}

RotationalLimitMotor::RotationalLimitMotor(RotationalLimitMotor^ motor)
{
	this->motor = new btRotationalLimitMotor(*motor->motor);
}

RotationalLimitMotor::RotationalLimitMotor(btRotationalLimitMotor* motor)
{
	this->motor = motor;
}

btScalar RotationalLimitMotor::SolveAngularLimits(btScalar timeStep, Vector3 axis,
	btScalar jacDiagABInv, RigidBody^ body0, RigidBody^ body1)
{
	return motor->solveAngularLimits(timeStep, *Math::Vector3ToBtVector3(axis),
		jacDiagABInv, body0->UnmanagedPointer, body1->UnmanagedPointer);
}

int RotationalLimitMotor::TestLimitValue(btScalar test_value)
{
	return motor->testLimitValue(test_value);
}

bool RotationalLimitMotor::IsLimited::get()
{
	return motor->isLimited();
}

bool RotationalLimitMotor::NeedApplyTorques::get()
{
	return motor->needApplyTorques();
}

btScalar RotationalLimitMotor::AccumulatedImpulse::get()
{
	return motor->m_accumulatedImpulse;
}

void RotationalLimitMotor::AccumulatedImpulse::set(btScalar value)
{
	motor->m_accumulatedImpulse = value;
}

btScalar RotationalLimitMotor::Bounce::get()
{
	return motor->m_bounce;
}

void RotationalLimitMotor::Bounce::set(btScalar value)
{
	motor->m_bounce = value;
}

int RotationalLimitMotor::CurrentLimit::get()
{
	return motor->m_currentLimit;
}

void RotationalLimitMotor::CurrentLimit::set(int value)
{
	motor->m_currentLimit = value;
}

btScalar RotationalLimitMotor::CurrentLimitError::get()
{
	return motor->m_currentLimitError;
}

void RotationalLimitMotor::CurrentLimitError::set(btScalar value)
{
	motor->m_currentLimitError = value;
}

btScalar RotationalLimitMotor::CurrentPosition::get()
{
	return motor->m_currentPosition;
}

void RotationalLimitMotor::CurrentPosition::set(btScalar value)
{
	motor->m_currentPosition = value;
}

btScalar RotationalLimitMotor::Damping::get()
{
	return motor->m_damping;
}

void RotationalLimitMotor::Damping::set(btScalar value)
{
	motor->m_damping = value;
}

bool RotationalLimitMotor::EnableMotor::get()
{
	return motor->m_enableMotor;
}

void RotationalLimitMotor::EnableMotor::set(bool value)
{
	motor->m_enableMotor = value;
}

btScalar RotationalLimitMotor::HiLimit::get()
{
	return motor->m_hiLimit;
}

void RotationalLimitMotor::HiLimit::set(btScalar value)
{
	motor->m_hiLimit = value;
}

btScalar RotationalLimitMotor::LimitSoftness::get()
{
	return motor->m_limitSoftness;
}

void RotationalLimitMotor::LimitSoftness::set(btScalar value)
{
	motor->m_limitSoftness = value;
}

btScalar RotationalLimitMotor::LoLimit::get()
{
	return motor->m_loLimit;
}

void RotationalLimitMotor::LoLimit::set(btScalar value)
{
	motor->m_loLimit = value;
}

btScalar RotationalLimitMotor::MaxLimitForce::get()
{
	return motor->m_maxLimitForce;
}

void RotationalLimitMotor::MaxLimitForce::set(btScalar value)
{
	motor->m_maxLimitForce = value;
}

btScalar RotationalLimitMotor::MaxMotorForce::get()
{
	return motor->m_maxMotorForce;
}

void RotationalLimitMotor::MaxMotorForce::set(btScalar value)
{
	motor->m_maxMotorForce = value;
}

btScalar RotationalLimitMotor::NormalCFM::get()
{
	return motor->m_normalCFM;
}

void RotationalLimitMotor::NormalCFM::set(btScalar value)
{
	motor->m_normalCFM = value;
}

btScalar RotationalLimitMotor::StopCFM::get()
{
	return motor->m_stopCFM;
}

void RotationalLimitMotor::StopCFM::set(btScalar value)
{
	motor->m_stopCFM = value;
}

btScalar RotationalLimitMotor::StopERP::get()
{
	return motor->m_stopERP;
}

void RotationalLimitMotor::StopERP::set(btScalar value)
{
	motor->m_stopERP = value;
}

btScalar RotationalLimitMotor::TargetVelocity::get()
{
	return motor->m_targetVelocity;
}

void RotationalLimitMotor::TargetVelocity::set(btScalar value)
{
	motor->m_targetVelocity = value;
}

btRotationalLimitMotor* RotationalLimitMotor::UnmanagedPointer::get()
{
	return motor;
}


TranslationalLimitMotor::TranslationalLimitMotor()
{
	motor = new btTranslationalLimitMotor();
}

TranslationalLimitMotor::TranslationalLimitMotor(TranslationalLimitMotor^ motor)
{
	this->motor = new btTranslationalLimitMotor(*motor->motor);
}

TranslationalLimitMotor::TranslationalLimitMotor(btTranslationalLimitMotor* motor)
{
	this->motor = motor;
}

btScalar TranslationalLimitMotor::SolveLinearAxis(btScalar timeStep, btScalar jacDiagABInv,
			RigidBody^ body1, Vector3 pointInA, RigidBody^ body2, Vector3 pointInB,
			int limit_index, Vector3 axis_normal_on_a, Vector3 anchorPos)
{
	return motor->solveLinearAxis(timeStep, jacDiagABInv,
		*body1->UnmanagedPointer, *Math::Vector3ToBtVector3(pointInA),
		*body2->UnmanagedPointer, *Math::Vector3ToBtVector3(pointInB),
		limit_index, *Math::Vector3ToBtVector3(axis_normal_on_a),
		*Math::Vector3ToBtVector3(anchorPos)
	);
}

int TranslationalLimitMotor::TestLimitValue(int limitIndex, btScalar test_value)
{
	return motor->testLimitValue(limitIndex, test_value);
}

bool TranslationalLimitMotor::IsLimited(int limitIndex)
{
	return motor->isLimited(limitIndex);
}

bool TranslationalLimitMotor::NeedApplyForce(int limitIndex)
{
	return motor->needApplyForce(limitIndex);
}

Vector3 TranslationalLimitMotor::AccumulatedImpulse::get()
{
	return Math::BtVector3ToVector3(&motor->m_accumulatedImpulse);
}

void TranslationalLimitMotor::AccumulatedImpulse::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_accumulatedImpulse);
}

int TranslationalLimitMotor::CurrentLimit::get(int index)
{
	return motor->m_currentLimit[index];
}

void TranslationalLimitMotor::CurrentLimit::set(int index, int value)
{
	motor->m_currentLimit[index] = value;
}

Vector3 TranslationalLimitMotor::CurrentLimitError::get()
{
	return Math::BtVector3ToVector3(&motor->m_currentLimitError);
}

void TranslationalLimitMotor::CurrentLimitError::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_currentLimitError);
}

Vector3 TranslationalLimitMotor::CurrentLinearDiff::get()
{
	return Math::BtVector3ToVector3(&motor->m_currentLinearDiff);
}

void TranslationalLimitMotor::CurrentLinearDiff::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_currentLinearDiff);
}

btScalar TranslationalLimitMotor::Damping::get()
{
	return motor->m_damping;
}

void TranslationalLimitMotor::Damping::set(btScalar value)
{
	motor->m_damping = value;;
}

bool TranslationalLimitMotor::EnableMotor::get(int index)
{
	return motor->m_enableMotor[index];
}

void TranslationalLimitMotor::EnableMotor::set(int index, bool value)
{
	motor->m_enableMotor[index] = value;;
}

btScalar TranslationalLimitMotor::LimitSoftness::get()
{
	return motor->m_limitSoftness;
}

void TranslationalLimitMotor::LimitSoftness::set(btScalar value)
{
	motor->m_limitSoftness = value;;
}

Vector3 TranslationalLimitMotor::LowerLimit::get()
{
	return Math::BtVector3ToVector3(&motor->m_lowerLimit);
}

void TranslationalLimitMotor::LowerLimit::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_lowerLimit);
}

Vector3 TranslationalLimitMotor::MaxMotorForce::get()
{
	return Math::BtVector3ToVector3(&motor->m_maxMotorForce);
}

void TranslationalLimitMotor::MaxMotorForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_maxMotorForce);
}

Vector3 TranslationalLimitMotor::NormalCFM::get()
{
	return Math::BtVector3ToVector3(&motor->m_normalCFM);
}

void TranslationalLimitMotor::NormalCFM::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_normalCFM);
}

btScalar TranslationalLimitMotor::Resitution::get()
{
	return motor->m_restitution;
}

void TranslationalLimitMotor::Resitution::set(btScalar value)
{
	motor->m_restitution = value;;
}

Vector3 TranslationalLimitMotor::StopCFM::get()
{
	return Math::BtVector3ToVector3(&motor->m_stopCFM);
}

void TranslationalLimitMotor::StopCFM::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_stopCFM);
}

Vector3 TranslationalLimitMotor::StopERP::get()
{
	return Math::BtVector3ToVector3(&motor->m_stopERP);
}

void TranslationalLimitMotor::StopERP::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_stopERP);
}

Vector3 TranslationalLimitMotor::TargetVelocity::get()
{
	return Math::BtVector3ToVector3(&motor->m_targetVelocity);
}

void TranslationalLimitMotor::TargetVelocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_targetVelocity);
}

Vector3 TranslationalLimitMotor::UpperLimit::get()
{
	return Math::BtVector3ToVector3(&motor->m_upperLimit);
}

void TranslationalLimitMotor::UpperLimit::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &motor->m_upperLimit);
}

btTranslationalLimitMotor* TranslationalLimitMotor::UnmanagedPointer::get()
{
	return motor;
}


Generic6DofConstraint::Generic6DofConstraint(btGeneric6DofConstraint* constraint)
: TypedConstraint(constraint)
{
}

Generic6DofConstraint::Generic6DofConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix frameInA, Matrix frameInB, bool useReferenceFrameA)
: TypedConstraint(new btGeneric6DofConstraint(*rbA->UnmanagedPointer,
	*rbB->UnmanagedPointer, *Math::MatrixToBtTransform(frameInA),
	*Math::MatrixToBtTransform(frameInB), useReferenceFrameA))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

Generic6DofConstraint::Generic6DofConstraint(RigidBody^ rbB, Matrix frameInB,
	bool useReferenceFrameA)
: TypedConstraint(new btGeneric6DofConstraint(*rbB->UnmanagedPointer,
	*Math::MatrixToBtTransform(frameInB), useReferenceFrameA))
{
	this->RigidBodyB = rbB;
}

void Generic6DofConstraint::CalcAnchorPos()
{
	UnmanagedPointer->calcAnchorPos();
}

void Generic6DofConstraint::CalculateTransforms()
{
	UnmanagedPointer->calculateTransforms();
}

void Generic6DofConstraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	UnmanagedPointer->calculateTransforms(*Math::MatrixToBtTransform(transA),
		*Math::MatrixToBtTransform(transB));
}

btScalar Generic6DofConstraint::GetAngle(int axis_index)
{
	return UnmanagedPointer->getAngle(axis_index);
}

#pragma managed(push, off)
btVector3* Generic6DofConstraint_GetAxis(btGeneric6DofConstraint* constraint, int axis_index)
{
	return &constraint->getAxis(axis_index);
}
#pragma managed(pop)

Vector3 Generic6DofConstraint::GetAxis(int axis_index)
{
	return Math::BtVector3ToVector3(Generic6DofConstraint_GetAxis(UnmanagedPointer, axis_index));
}

btScalar Generic6DofConstraint::GetRelativePivotPosition(int axis_index)
{
	return UnmanagedPointer->getRelativePivotPosition(axis_index);
}

RotationalLimitMotor^ Generic6DofConstraint::GetRotationalLimitMotor(int index)
{
	return gcnew RotationalLimitMotor(UnmanagedPointer->getRotationalLimitMotor(index));
}

bool Generic6DofConstraint::IsLimited(int limitIndex)
{
	return UnmanagedPointer->isLimited(limitIndex);
}

void Generic6DofConstraint::SetAngularLowerLimit(Vector3 value)
{
	UnmanagedPointer->setAngularLowerLimit(*Math::Vector3ToBtVector3(value));
}

void Generic6DofConstraint::SetAngularUpperLimit(Vector3 value)
{
	UnmanagedPointer->setAngularUpperLimit(*Math::Vector3ToBtVector3(value));
}

void Generic6DofConstraint::SetLimit(int axis, btScalar lo, btScalar hi)
{
	UnmanagedPointer->setLimit(axis, lo, hi);
}

void Generic6DofConstraint::SetLinearLowerLimit(Vector3 linearLower)
{
	UnmanagedPointer->setLinearLowerLimit(*Math::Vector3ToBtVector3(linearLower));
}

void Generic6DofConstraint::SetLinearUpperLimit(Vector3 linearUpper)
{
	UnmanagedPointer->setLinearUpperLimit(*Math::Vector3ToBtVector3(linearUpper));
}

bool Generic6DofConstraint::TestAngularLimitMotor(int axis_index)
{
	return UnmanagedPointer->testAngularLimitMotor(axis_index);
}

void Generic6DofConstraint::UpdateRHS(btScalar timeStep)
{
	UnmanagedPointer->updateRHS(timeStep);
}

Matrix Generic6DofConstraint::CalculatedTransformA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getCalculatedTransformA());
}

Matrix Generic6DofConstraint::CalculatedTransformB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getCalculatedTransformB());
}

Matrix Generic6DofConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetA());
}
void Generic6DofConstraint::FrameOffsetA::set(Matrix value)
{
	btScalar m[15];
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	UnmanagedPointer->getFrameOffsetA().setFromOpenGLMatrix(m);
}

Matrix Generic6DofConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetB());
}
void Generic6DofConstraint::FrameOffsetB::set(Matrix value)
{
	btScalar m[15];
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	UnmanagedPointer->getFrameOffsetB().setFromOpenGLMatrix(m);
}

BulletSharp::TranslationalLimitMotor^ Generic6DofConstraint::TranslationalLimitMotor::get()
{
	return gcnew BulletSharp::TranslationalLimitMotor(UnmanagedPointer->getTranslationalLimitMotor());
}

bool Generic6DofConstraint::UseFrameOffset::get()
{
	return UnmanagedPointer->getUseFrameOffset();
}

void Generic6DofConstraint::UseFrameOffset::set(bool value)
{
	UnmanagedPointer->setUseFrameOffset(value);
}

btGeneric6DofConstraint* Generic6DofConstraint::UnmanagedPointer::get()
{
	return (btGeneric6DofConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
