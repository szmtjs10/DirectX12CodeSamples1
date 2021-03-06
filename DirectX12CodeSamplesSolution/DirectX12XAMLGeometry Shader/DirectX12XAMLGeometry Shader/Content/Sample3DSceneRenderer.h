#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "ConstantBufferViewHeapManager.h"
#include "CustomSphere.h"
#include "TextureManager.h"
#include "ConstantPixelShaderBufferInformation.h"
#include "CustomCube.h"
#include "PipelineStateManager.h"
#include "CustomPlane.h"
#include "SimpleCamera.h"

namespace DirectX12XAMLGeometry_Shader
{
	// 此示例呈现器实例化一个基本渲染管道。
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~Sample3DSceneRenderer();
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void Update(DX::StepTimer const& timer);
		bool Render();
		void SaveState();

		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }

		void OnHandleCallBack(bool res);
		void SetSphereRotateEnable() 
		{ 
			m_customSphere.SetRotateEnable();
		 }
		void HandleXChanged(float x) {
			m_constantPSBuffer.HandleXChanged(x); 
			m_customSphere.HandleXChanged(x);
			//m_GSCBData.lightDirction = DirectX::XMFLOAT3(x, -1.0f, -1.0f);
			m_lightX = x;
		}

		void HandleExplodeChanged(float x) {
			m_explode = x;
			//m_GSCBData.explode = m_explode;
		}

		void HandleCameraXChanged(float x) 
		{ 
			m_fCameraX = x; 
			m_customSphere.HandleCameraXChanged(x); 
			//m_GSCBData.cameraPosition = DirectX::XMFLOAT3(m_fCameraX, m_fCameraY, 1.5f);
		}//HandleCameraYChanged
		void HandleCameraYChanged(float y) 
		{ 
			m_fCameraY = y; 
			m_customSphere.HandleCameraYChanged(y); 
			//m_GSCBData.cameraPosition = DirectX::XMFLOAT3(m_fCameraX, m_fCameraY, 1.5f);
		}//HandleCameraYChanged

		bool GetIsLoadingComplete() {			return m_loadingComplete;		}
	private:
		void LoadState();
		void Rotate(float radians);

	private:	
		//相机X轴移动量
		float m_fCameraX = 0.0f;
		float m_fCameraY = 0.7f;
		float m_fCameraZ = 1.5f;
		//光的x轴方向
		float m_lightX = -1.0f;
		//几何着色器explode的值
		float m_explode = 0.5f;

		// 常量缓冲区大小必须都是 256 字节的整数倍。
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;

		// 缓存的设备资源指针。
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
	
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;		

		ConstantBufferViewHeapManager m_cbvHeapManager;

		CustomSphere m_customSphere;
		CustomCube m_CustomCube;
		CustomPlane m_customPlane;
		

		D3D12_RECT											m_scissorRect;

		std::vector<byte>									m_vertexShader;
		std::vector<byte>									m_pixelShader;


		// 用于渲染循环的变量。
		bool	m_loadingComplete;
		float	m_radiansPerSecond;
		float	m_angle;
		bool	m_tracking;
		// 用于保存鼠标左键的偏移量。
		float   m_positionX;


		//Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;
		TextureManager m_textureManager;

		//// 像素着色器常量缓存，它也必须是256字节对其的
		//// Constant buffers must be 256-byte aligned.
		ConstantPixelShaderBufferInformation m_constantPSBuffer;

		PipelineStateManager m_pipelineStateManager;

		SimpleCamera             g_SimpleCamera;

		//-----几何着色器的常量缓存-----
		const UINT c_AlignedGSCBSize = (sizeof(ModelViewProjectionGeometryShader) + 255) & ~255;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_GSCB;
		ModelViewProjectionGeometryShader					m_GSCBData;
		UINT8*												m_mappedGSCB;
		int m_iStartOffset = 0;
		UINT												m_cbvDescriptorSize = 0;

		
	};
}

