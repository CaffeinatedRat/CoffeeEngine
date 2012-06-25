//--------------------------------------------------------------------------------------
// Description: The base camera class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Interfaces\ICamera.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class CameraClass : public ICamera
		{
		protected:
			BaseGraphicsClass* m_pGraphicsClass;

		private:
			CameraClass();

		public:
			
			CameraClass(BaseGraphicsClass* pBaseGraphicsClass);
			CameraClass(const CameraClass& object);
			virtual ~CameraClass() { };
		};
	};
};

#endif