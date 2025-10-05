// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : arduinoMain.h
// purpose      : calls the setup and loop functions that arduino uses
// created on   : 7/30/2025 - Tyler
// last modified: 7/30/2025 - Tyler
// --------------------------------------------------------------------

#include "Arduino.h"
#include "PinState.h"
#include "main.h"

#include "Printer.h"
#include "spdlog/spdlog-inl.h"
#include "spdlog/spdlog.h"

#ifdef ENABLE_GUI
#include "Gui.h"
#include <GLFW/glfw3.h>
#endif

CANbus ACAN_T4::can1;
CANbus ACAN_T4::can2;
CANbus ACAN_T4::can3;

extern void setup();
extern void loop();

extern PinState pinState;

int main()
{
    spdlog::set_level(spdlog::level::debug);
    clearFile();
    setup();

#ifdef ENABLE_GUI
    GLFWwindow *window = guiSetup();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        loop();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Actual GUI
        pinStateWidget(&pinState);

        // Rendering
        ImGui::Render();
        int displayW;
        int displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    guiShutdown(window);
#else
    while (true)
    {
        loop();
    }
#endif

    return 0;
}
