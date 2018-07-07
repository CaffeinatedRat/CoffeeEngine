//--------------------------------------------------------------------------------------
// Description: The model interface.  Used to provide a light-weight skeleton to prevent circuluar references for the graphic classes.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _IMODEL_INTERFACE_H_
#define _IMODEL_INTERFACE_H_

#pragma once

//#include "Common.hpp"
#include "IShader.hpp"
#include "ITransform.hpp"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class IModel : public ITransform
		{
		public:

			/// <summary>
			/// Attempts to initialize the model object.
			/// </summary>
			virtual bool Initialize(IShader*) = 0;

			/// <summary>
			/// Begin rendering the model.
			/// </summary>
			virtual void Render(float) const = 0;

			/// <summary>
			/// A method for adding shaders to a model.
			/// </summary>
			virtual void AddShader(const IShader*) = 0;
			virtual void AddShaders(std::vector<const IShader*>&) = 0;

			/// <summary>
			/// Begins the process of cleaning up the model.
			/// </summary>
			virtual void Shutdown() = 0;
		};
	};
};

#endif
