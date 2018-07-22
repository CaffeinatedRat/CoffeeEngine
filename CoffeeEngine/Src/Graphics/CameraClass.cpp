//--------------------------------------------------------------------------------------
// Description: The base camera class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "CameraClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
CameraClass::CameraClass(const BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == nullptr)
		throw NullArgumentException("CameraClass", "Constructor", "pBaseGraphicsClass");

	m_pGraphicsClass = pBaseGraphicsClass;
}

CameraClass::CameraClass(const CameraClass& object)  noexcept
	: m_pGraphicsClass(object.m_pGraphicsClass),
	m_yaw(object.m_yaw),
	m_pitch(object.m_pitch),
	m_roll(object.m_roll),
	m_strafe(object.m_strafe),
	m_forward(object.m_forward),
	m_position(object.m_position),
	m_orientation(object.m_orientation),
	m_lookAt(object.m_lookAt),
	m_up(object.m_up)
{
}

CameraClass::CameraClass(CameraClass&& object) noexcept
	: m_pGraphicsClass(object.m_pGraphicsClass),
	m_yaw(object.m_yaw),
	m_pitch(object.m_pitch),
	m_roll(object.m_roll),
	m_strafe(object.m_strafe),
	m_forward(object.m_forward),
	m_position(std::move(object.m_position)),
	m_orientation(std::move(object.m_orientation)),
	m_lookAt(std::move(object.m_lookAt)),
	m_up(std::move(object.m_up))
{
	object.m_pGraphicsClass = nullptr;
	object.m_yaw = object.m_pitch = object.m_roll = 0.0f;
	object.m_strafe = object.m_forward = 0.0f;
}