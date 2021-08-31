// imgui对应的东西
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
// 系统glfw库
#include <GLFW/glfw3.h>

int main()
{
    // 设置出错时的回调函数，可以是lambda，也可以是回调函数
    glfwSetErrorCallback([](int err, const char *desc)
                         { std::cerr << "glfw error" << err << ":" << desc << std::endl; });
    if (!glfwInit())
        std::cerr << "init error" << std::endl;

    // 设置版本信息，我也不知道咋看,反正是抄的
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // 创建窗体
    GLFWwindow *window = glfwCreateWindow(1280, 800, "min_demo", NULL, NULL);
    if (window == nullptr)
        std::cerr << "create window err" << std::endl;

    glfwMakeContextCurrent(window);
    // 这个是垂直同步？和下边的swap一起的
    glfwSwapInterval(1);

    // 初始化dear imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // 这句是干啥的
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // 设置小窗背景风格
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    // ImGui::StyleColorsLight();

    // 设置平台和渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ///////////////////////初始化完成/////////////////////////////////////////////

    // 下边是主要的程序
    bool isShowDemoWin = true;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec2 random_pos = ImVec2(0, 0);
    srand(123456);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 显示新的ImGui帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 显示他的自有的demo窗口 这里还必须是左值，只能传参进去
        if (isShowDemoWin)
            ImGui::ShowDemoWindow(&isShowDemoWin);
        {
            // 设定下一窗口位置，应在begin前边
            // 中心点相对于左上角的坐标位置(int)和小控件的中心点位置
            ImGui::SetNextWindowPos(random_pos, 0, ImVec2(0, 0));
            ImGui::Begin("hello");
            if (ImGui::Button("close"))
            {
                int x = 1280 * (rand() % 1000) / 1000;
                int y = 800 * (rand() % 1000) / 1000;
                random_pos = ImVec2(x, y);
            }
            if (ImGui::Button("isShowDemo"))
                isShowDemoWin = !isShowDemoWin;
            ImGui::End();
        }

        // 一定要记得渲染哦
        {
            ImGui::Render();
            int display_w, display_h;
            // 只有这三句是可以没有，其他的都必须要
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.w, clear_color.z);
            ////////
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            // 这一句最重要，没有他全都是黑的
            glfwSwapBuffers(window);
        }
    }

    // 清除窗口内容
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}