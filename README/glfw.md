#GLFW (Graphics Library Framework)

GLFW is a support library for OpenGL that facilitates the creation of windows and the management of input, including keyboard and mouse. 

It offers a straightforward API for creating windows, contexts, and surfaces. GLFW can be initialized using the glfwInit() function, which returns 0 if the initialization is successful and 1 otherwise.

```
if (!glfwInit()) {
	cerr<<"Could not launch GLFW Windows";
}
```

## GLFWwindow

GLFWwindow type is used to create window in using GLFW by utlizing the method `glCreateWindow(widht,height,title)` 

Example
```
GLFWwindow* window = glfwCreateWindow(width,height,title);
```


## Set Anti-Aliasing 

To set the anti-aliasing for the current window you can use the following function

```
glfwWindowHint(GLFW_SAMPLES,4);
```

## Get Primary display

The information realated to the current display can obtained via following function `glfwGetPrimaryMonitor`

```
GLFWmonitor* mon = glfwGetPrimaryMonitor();
const GLFWvidmode* vmode = glfwGetVideoMode(mon);
```
