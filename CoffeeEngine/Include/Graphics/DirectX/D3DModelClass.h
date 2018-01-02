//--------------------------------------------------------------------------------------
// Description: The D3D model class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#pragma once
#ifndef _D3D_MODEL_CLASS_H_
#define _D3D_MODEL_CLASS_H_

//#include "Common.h"

#include "Graphics/BaseGraphicsClass.h"
#include "Graphics/ModelClass.h"

#include "Graphics/DirectX/D3DCommon.h"
#include "Graphics/DirectX/D3DGraphicsClass.h"

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX
		{
			class D3DModelClass : public ModelClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				//Primitives
				int m_nVertexCount, m_nIndexCount;

				//Direct3d
				ID3D11Buffer *m_pVertexBuffer, *m_pIndexBuffer;
				XMFLOAT3 m_rotate, m_scale, m_translate;

				//Temporary...
				ID3D11ShaderResourceView* m_pTexture;

			private:
				D3DModelClass();

			public:
			
				D3DModelClass(BaseGraphicsClass* pBaseGraphicsClass);
				D3DModelClass(const D3DModelClass& object);
				virtual ~D3DModelClass();

				/// <summary>
				/// Attempts to initialize the model object.
				/// </summary>
				bool Initialize();

				/// <summary>
				/// Begin rendering the model.
				/// </summary>
				void Render(IShader* pShader, float fElapsedTime);

				/// <summary>
				/// Begins the process of cleaning up the model.
				/// </summary>
				void Shutdown();

				/// <summary>
				/// Rotate the object among one or more of the 3-axises.
				/// </summary>
				void Rotate(float x, float y, float z);

				/// <summary>
				/// Translate the object among one or more of the 3-axises.
				/// </summary>
				void Translate(float x, float y, float z);

				/// <summary>
				/// Scale the object among one or more of the 3-axises.
				/// </summary>
				void Scale(float x, float y, float z);
			};
		};
	};
};

#endif

#endif