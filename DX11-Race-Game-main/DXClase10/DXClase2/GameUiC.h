#pragma once


#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include <imgui.h>



#include "GameMath.h"

class GameUi {
private:
public:


	void initialize(HWND hwnd,	ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(d3d11Device, d3d11DevCon);
	}

	void m_loop() {
		// (Your code process and dispatch Win32 messages)
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(); // Show demo window! :)
	}

	void refresh_buffer() {
		// Rendering
		// (Your code clears your framebuffer, renders your other stuff etc.)
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		// (Your code calls swapchain's Present() function)
	}


	void shutdown() {
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void program() {
		ImGui::Text("Hello, world %d", 123);
		
		
	}

}gameui;