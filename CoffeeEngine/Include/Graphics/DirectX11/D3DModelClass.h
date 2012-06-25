//--------------------------------------------------------------------------------------
// Description: The D3D model class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3D_MODEL_CLASS_H_
#define _D3D_MODEL_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\ModelClass.h"

#include "Graphics\DirectX11\D3DCommon.h"
#include "Graphics\DirectX11\D3DGraphicsClass.h"
#include <d3d10.h>
#include <d3dx10math.h>

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX11
		{
			class D3DModelClass : public ModelClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Data types
				// 
				////////////////////////////////////////////////////////////

				struct VertexType
				{
					D3DXVECTOR3 position;
					D3DXVECTOR4 color;
					D3DXVECTOR2 texture;
				};

				struct MatrixBufferType
				{
					D3DXMATRIX world;
					D3DXMATRIX view;
					D3DXMATRIX projection;
				};

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				ID3D11Buffer *m_pVertexBuffer, *m_pIndexBuffer;
				int m_nVertexCount, m_nIndexCount;
				
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
				/// Begins the process of cleaning up the model.
				/// </summary>
				void Shutdown();

				/// <summary>
				/// Assigns a shader to the model.
				/// </summary>
				//void SetShader(IShader* pShader);

				/// <summary>
				/// Begin rendering the model.
				/// </summary>
				void Render(IShader* pShader);

			private:
				bool InitializeShaders();
				void ShutdownShaders();
				void RenderShaders();
			};
		};
	};
};

#endif