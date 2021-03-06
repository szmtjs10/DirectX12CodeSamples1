#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"


// 在屏幕上呈现 Direct3D 内容。用于管理应用程序资源、更新应用程序状态和呈现帧的方法。
namespace DirectX12UWPBase
{
	class DirectX12UWPBaseMain
	{
	public:
		DirectX12UWPBaseMain();
		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();

	private:
		// TODO: 替换为你自己的内容呈现器。
		//std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;

		// 渲染循环计时器。
		DX::StepTimer m_timer;
	};
}