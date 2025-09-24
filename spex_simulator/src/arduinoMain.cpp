// --------------------------------------------------------------------
//                           SPEX ROVER 2025
// --------------------------------------------------------------------
// file name    : arduinoMain.h
// purpose      : calls the setup and loop functions that arduino uses
// created on   : 7/30/2025 - Tyler
// last modified: 7/30/2025 - Tyler
// --------------------------------------------------------------------

#include "Gui.h"
#include "main.h"

#include "Printer.h"

#include <GLFW/glfw3.h>
#include <iostream>


CANbus ACAN_T4::can1;
CANbus ACAN_T4::can2;
CANbus ACAN_T4::can3;

extern void setup();
extern void loop();

int main()
{

    clearFile();
    setup();

    GLFWwindow *window = guiSetup();

    bool showDemoWindow = true;

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
        ImGui::ShowDemoWindow(&showDemoWindow);

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

    return 0;
}
