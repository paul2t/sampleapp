
#include "resources/liberation-mono.cpp"
#include "resources/icon.cpp"
#include "foosball.h"



static void drawMenuBar(ImGuiIO& io, State& state)
{
	b32 showAbout = false;
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				state.running = false;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				showAbout = true;
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	if (showAbout)
		ImGui::OpenPopup("About");
}


static b32 handleInputs(ImGuiIO& io, State& state)
{
	b32 inputModified = false;

	return inputModified;
}

static void drawAbout()
{
	if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(APPLICATION_NAME " alpha by paul2t");
		ImGui::BulletText("Using imgui and glfw");
		ImGui::BulletText("Font: " DEFAULT_FONT_NAME);
		if (ImGui::Button("OK"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}



static void handleFrame(WINDOW window, ImGuiContext& g, State& state)
{
	ImGuiIO& io = g.IO;

	int framewidth, frameheight;
	GetFramebufferSize(window, &framewidth, &frameheight);
	ImGui::SetNextWindowSize(ImVec2((float)framewidth, (float)frameheight));
	ImGui::SetNextWindowPos(ImVec2());
	ImGui::Begin("MainWindow", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoSavedSettings);

	drawMenuBar(io, state);

	b32 inputModified = handleInputs(io, state);

	drawAbout();
	ImGui::End();

	// Save params if something has been changed or we are closing the application.
	if (inputModified || !state.running)
	{
		// TODO: Save
	}

}



#if APP_INTERNAL && 1
int main()
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
#if APP_INTERNAL
	HINSTANCE hInstance = GetModuleHandle(NULL);
#endif
	
	State state = {};

	WINDOW window = createAndInitWindow(APPLICATION_NAME, state.config.width, state.config.height, state.config.maximized);
	if (!window) return 1;

#if OPENGL
	GLFWimage icon[2] = { { 16, 16, icon_16_map }, { 32, 32, icon_32_map}, };
	glfwSetWindowIcon(window, sizeof(icon)/sizeof(GLFWimage), icon);
#endif
	ImGuiContext& g = *ImGui::GetCurrentContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL; // Disable imgui.ini file.


	// Main loop
    while (state.running)
    {
		if (state.config.fontFile.size)
			reloadFontIfNeeded(state.config.fontFile, state.config.fontSize);
		else
			reloadFontIfNeeded(liberation_mono_ttf, sizeof(liberation_mono_ttf), state.config.fontSize);


		b32 isActiveWindow = IsActiveWindow(window);
		readInputs(window, state.running, state.shouldWaitForEvent, isActiveWindow);
		
		imguiBeginFrame();

		handleFrame(window, g, state);

		imguiEndFrame(window);
    }


	imguiCleanup(window);
    return 0;
}
