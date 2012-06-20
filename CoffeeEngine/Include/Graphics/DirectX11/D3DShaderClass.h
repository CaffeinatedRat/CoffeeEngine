//--------------------------------------------------------------------------------------
// Description: The D3D shader class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.

// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3D_SHADER_CLASS_H_
#define _D3D_SHADER_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\ShaderClass.h"

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
			class D3DShaderClass : public ShaderClass
			{
			private:
				D3DShaderClass();

				struct VertexType
				{
					D3DXVECTOR3 position;
					D3DXVECTOR4 color;
				};

				struct MatrixBufferType
				{
					D3DXMATRIX world;
					D3DXMATRIX view;
					D3DXMATRIX projection;
				};

			public:
			
				D3DShaderClass(BaseGraphicsClass* pBaseGraphicsClass);
				D3DShaderClass(const D3DShaderClass& object);
				virtual ~D3DShaderClass();

				virtual bool Initialize(std::string sFileName);
				virtual void Shutdown();
				virtual void Render();

			protected:

			private:
				ID3D11VertexShader* m_pVertexShader;
				ID3D11PixelShader* m_pPixelShader;

				ID3D11InputLayout* m_pLayout;
				ID3D11Buffer* m_pMatrixBuffer;
				ID3D11SamplerState* m_pSampleState;
			};
		};
	};
};

#endif