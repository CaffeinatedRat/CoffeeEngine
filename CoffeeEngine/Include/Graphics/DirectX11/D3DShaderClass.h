//--------------------------------------------------------------------------------------
// Description: The D3D shader class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.

// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3D_SHADER_CLASS_H_
#define _D3D_SHADER_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\ShaderClass.h"

#include "Graphics\DirectX11\D3DCommon.h"
#include "Graphics\DirectX11\D3DGraphicsClass.h"

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX11
		{
			class D3DShaderClass : public ShaderClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				//Direct3d
				ID3D11VertexShader* m_pVertexShader;
				ID3D11PixelShader* m_pPixelShader;

				ID3D11InputLayout* m_pLayout;
				ID3D11Buffer* m_pMatrixBuffer;
				ID3D11SamplerState* m_pSampleState;

				D3DXMATRIX m_worldMatrix;

			private:
				D3DShaderClass();

			public:
			
				D3DShaderClass(BaseGraphicsClass* pBaseGraphicsClass);
				D3DShaderClass(const D3DShaderClass& object);
				virtual ~D3DShaderClass();

				virtual bool Initialize(std::string sFileName);
				virtual void Render(float fElapsedTime);
				virtual void Shutdown();

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////
				void SetWorldMatrix(D3DXMATRIX& worldMatrix) { m_worldMatrix = worldMatrix; }

			private:
				bool SetShaderParameters(float fElapsedTime);
			};
		};
	};
};

#endif