#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <iostream>
#include "imgui-util-events/event_dispatcher.hpp"
#include "imgui-util-events/input_event.hpp"
#include "imgui-util-events/navigation_event.hpp"

enum Routes
{
    Settings,
    Editor
};

struct State
{
    EventDispatcher<InputEvent> inputDispatcher;
    EventDispatcher<NavigationEvent<void>> navigationDispatcher;
    Routes currentRoute = Routes::Editor;
};

int main()
{
    State state;
    // Create a window
    int screenWidth = 640;
    int screenHeight = 480;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window *window = SDL_CreateWindow("ImGui Util Events",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          screenWidth,
                                          screenHeight,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 130");

    state.inputDispatcher.addListener([&state](const InputEvent &event)
                                      { std::visit(
                                            [&state](auto &&e)
                                            {
                                                using T = std::decay_t<decltype(e)>;

                                                if constexpr (std::is_same_v<T, SDLKeyEvent>)
                                                {
                                                    // Detect Ctrl + 1 to navigate to settings page
                                                    // Detect Ctrl + 2 to navigate to editor page
                                                    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
                                                    bool ctrlDown = keystates[SDL_SCANCODE_LCTRL] ||
                                                                    keystates[SDL_SCANCODE_RCTRL];
                                                    if (ctrlDown && e.isDown && e.key == SDLK_1)
                                                    {
                                                        std::cout << "Ctrl+1 detected → navigating to settings "
                                                                     "page\n";
                                                        state.navigationDispatcher.dispatch(NavigationEvent<void>{"settings"});
                                                    }
                                                    else if (ctrlDown && e.isDown && e.key == SDLK_2)
                                                    {
                                                        std::cout << "Ctrl+2 detected → navigating to editor "
                                                                     "page\n";
                                                        state.navigationDispatcher.dispatch(NavigationEvent<void>{"editor"});
                                                    }
                                                }
                                            },
                                            event); });

    state.navigationDispatcher.addListener([&state](const NavigationEvent<void> &event)
                                           {
                                               std::cout << "Navigating to " << event.routeName << std::endl;
                                               state.currentRoute = event.routeName == "settings" ? Routes::Settings : Routes::Editor; });

    bool running = true;

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                SDLKeyEvent keyEvent = {
                    .key = event.key.keysym.sym,
                    .isDown = event.type == SDL_KEYDOWN};
                state.inputDispatcher.dispatch(InputEvent{keyEvent});
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        glViewport(0, 0, screenWidth, screenHeight);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (state.currentRoute == Routes::Settings)
        {
            ImGui::Begin("Settings");
            ImGui::Text("Settings");
            ImGui::End();
        }
        else
        {
            ImGui::Begin("Editor");
            ImGui::Text("Editor");
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}