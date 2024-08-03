#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <functional> 

class GLFWwindow;

class MainWindow {
    public:
           MainWindow();
           int initialize();
           GLFWwindow* createWindow(unsigned width,unsigned height,std::string title);
           void makeEnv(GLFWwindow* window);

           void glfw_windowSize_callback(GLFWwindow* window,unsigned width,unsigned height);
           void glfw_frameBuffer_callback(GLFWwindow* window,unsigned width,unsigned height);
           void loop(std::function<void()> func,GLFWwindow* window);
    private:
         GLFWwindow* m_window = nullptr;
         unsigned m_width;
         unsigned m_height;
         std::string m_title;
         
         unsigned global_window_height = 0;
         unsigned global_window_width = 0;

         unsigned buffer_window_height = 0;
         unsigned buffer_window_width = 0;
         
         
};

#endif // MAINWINDOW_H
