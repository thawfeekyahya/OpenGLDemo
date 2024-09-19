#ifndef ABS_SHAPE_H
#define ABS_SHAPE_H

class GLFWwindow;

class AbsShape {
    public:
       ~AbsShape () = default;
       virtual void draw(GLFWwindow* window) = 0;
       virtual void loop() = 0;
};

#endif
