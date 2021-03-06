#ifndef Mouse_h
#define Mouse_h

#include "includes/sdl.hpp"

#include "Window.hpp"

class Mouse {
public:
    Mouse();

    void hide();
    void show();
    void toggleVisibility();

    void centerInWindow(Window& window);

    void setPositionInWindow(Window& window, glm::vec2 position);

    bool isHidden();
    glm::vec2 getPosition();

private:

    void setHidden(bool hidden);
    bool is_hidden;
};

#endif
