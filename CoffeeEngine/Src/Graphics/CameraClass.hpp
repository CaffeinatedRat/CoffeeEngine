//--------------------------------------------------------------------------------------
// Description: The base camera class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Common.hpp"
#include "BaseGraphicsClass.hpp"
#include "ICamera.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class CameraClass : public ICamera
		{
		protected:
			const BaseGraphicsClass *m_pGraphicsClass = nullptr;

		public:
			
			CameraClass() = delete;
			CameraClass(const BaseGraphicsClass* pBaseGraphicsClass);
			CameraClass(const CameraClass& object);
			virtual ~CameraClass() { };
		};
	};
};

#endif
