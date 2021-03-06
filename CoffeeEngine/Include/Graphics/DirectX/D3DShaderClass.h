//--------------------------------------------------------------------------------------
// Description: The D3D shader class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.

// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#pragma once
#ifndef _D3D_SHADER_CLASS_H_
#define _D3D_SHADER_CLASS_H_

#include "Common.h"
#include "Graphics/BaseGraphicsClass.h"
#include "Graphics/ShaderClass.h"

#include "Graphics/DirectX/D3DCommon.h"
#include "Graphics/DirectX/D3DGraphicsClass.h"

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX
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
				ID3D11VertexShader* m_pVertexShader = nullptr;
				ID3D11PixelShader* m_pPixelShader = nullptr;

				ID3D11InputLayout* m_pLayout = nullptr;
				ID3D11Buffer* m_pMatrixBuffer = nullptr;
				ID3D11SamplerState* m_pSampleState = nullptr;

				XMMATRIX m_worldMatrix;

			public:
			
				D3DShaderClass() = delete;
				D3DShaderClass(BaseGraphicsClass* pBaseGraphicsClass);
				D3DShaderClass(const D3DShaderClass& object);
				virtual ~D3DShaderClass();

				virtual bool Initialize(const std::string&);
				virtual void Render(float fElapsedTime);
				virtual void Shutdown();

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////
				inline void SetWorldMatrix(XMMATRIX& worldMatrix) { m_worldMatrix = worldMatrix; }

			private:
				bool SetShaderParameters(float fElapsedTime);
			};
		};
	};
};

#endif

#endif