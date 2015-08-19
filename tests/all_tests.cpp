
#include "gtest/gtest.h"
#include "gl_mocks.hpp"

#include <iostream>

#include "Viewport.hpp"
#include "Window.hpp"
#include "Mouse.hpp"
#include "Camera.hpp"
#include "OpenGLContext.hpp"

///////////////////////////////
// Camera Tests
///////////////////////////////
class CameraTest : public ::testing::Test {
protected:
    CameraTest() : viewport(1600, 900) {

    }

    Viewport viewport;
};

TEST_F(CameraTest, moveByGlobalTest1) {
    Camera camera(viewport, 45.0f);

    glm::vec3 start_position = glm::vec3(0, 0, 0);
    camera.setPosition(start_position);

    glm::vec3 move_amount = glm::vec3(1, 0, 52);
    camera.moveByGlobal(move_amount);

    EXPECT_EQ(camera.getPosition(), start_position + move_amount);
}

TEST_F(CameraTest, moveByGlobalTest2) {
    Camera camera(viewport, 45.0f);

    glm::vec3 start_position = glm::vec3(10, -50, 32);
    camera.setPosition(start_position);

    glm::vec3 move_amount = glm::vec3(-40, 0, 52);
    camera.moveByGlobal(move_amount);

    EXPECT_EQ(camera.getPosition(), start_position + move_amount);
}

TEST_F(CameraTest, moveByLocalTest) {
    FAIL();
}

TEST_F(CameraTest, rotateByLocalTest) {
    FAIL();
}

TEST_F(CameraTest, getViewMatrixTest) {
    FAIL();
}

TEST_F(CameraTest, getProjectionMatrixTest) {
    FAIL();
}

///////////////////////////////
// Drawable Tests
///////////////////////////////
class DrawableTest : public ::testing::Test {
protected:
    DrawableTest() {

    }
};

TEST_F(DrawableTest, drawTest) {
    FAIL();
}

///////////////////////////////
// Mesh Tests
///////////////////////////////
class MeshTest : public ::testing::Test {
protected:
    MeshTest() {

    }
};

TEST_F(MeshTest, drawTest) {
    FAIL();
}

TEST_F(MeshTest, prepareToBeDrawnTest) {
    FAIL();
}

TEST_F(MeshTest, linkToShaderTest) {
    FAIL();
}

///////////////////////////////
// Mouse Tests
///////////////////////////////
class MouseTest : public ::testing::Test {
protected:
    MouseTest() {

    }

    Mouse mouse;
};

TEST_F(MouseTest, hideTest) {
    mouse.hide();
    EXPECT_EQ(mouse.isHidden(), true);
}

TEST_F(MouseTest, showTest) {
    mouse.show();
    EXPECT_EQ(mouse.isHidden(), false);
}

TEST_F(MouseTest, toggleVisibilityTest) {
    mouse.hide();
    mouse.toggleVisibility();
    EXPECT_EQ(mouse.isHidden(), false);

    mouse.show();
    mouse.toggleVisibility();
    EXPECT_EQ(mouse.isHidden(), true);
}

TEST_F(MouseTest, centerInWindowTest) {
    Viewport viewport(1600, 900);
    Window window(viewport, false);

    mouse.centerInWindow(window);
    EXPECT_EQ(mouse.getPosition(), viewport.getCenter());
}

TEST_F(MouseTest, setPositionGlobalTest) {
    FAIL();
}

TEST_F(MouseTest, setPositionInWindowTest) {
    FAIL();
}

///////////////////////////////
// OpenGLContext Tests
///////////////////////////////
class OpenGLContextTest : public ::testing::Test {
protected:
    OpenGLContextTest() : viewport(1600, 900), window(viewport, false) {

    }

    Viewport viewport;
    Window window;
};

TEST_F(OpenGLContextTest, enableDepthTestTest) {
    OpenGLContext opengl_context(4, 1, window);

    MockGL mock_gl;
    #undef glEnable
    #define glEnable mock_gl.Enable

    EXPECT_CALL(mock_gl, Enable(testing::_)).Times(1);
    glEnable(GL_DEPTH_TEST);
    opengl_context.enableDepthTest();


}

TEST_F(OpenGLContextTest, enableBackfaceCullingTest) {
    FAIL();
}

TEST_F(OpenGLContextTest, setupAlphaBlendingTest) {
    FAIL();
}

TEST_F(OpenGLContextTest, getRendererStringTest) {
    FAIL();
}

TEST_F(OpenGLContextTest, getVersionStringTest) {
    FAIL();
}

TEST_F(OpenGLContextTest, getGLSLVersionStringTest) {
    FAIL();
}

///////////////////////////////
// ShaderFile Tests
///////////////////////////////
class ShaderFileTest : public ::testing::Test {
protected:
    ShaderFileTest() {

    }
};

TEST_F(ShaderFileTest, attachToTest) {
    FAIL();
}

TEST_F(ShaderFileTest, getErrorsTest) {
    FAIL();
}

TEST_F(ShaderFileTest, hasErrorsTest) {
    FAIL();
}

///////////////////////////////
// ShaderProgram Tests
///////////////////////////////
class ShaderProgramTest : public ::testing::Test {
protected:
    ShaderProgramTest() {

    }
};

TEST_F(ShaderProgramTest, useTest) {
    FAIL();
}

TEST_F(ShaderProgramTest, getUniformLocationTest) {
    FAIL();
}

///////////////////////////////
// Viewport Tests
///////////////////////////////
TEST(ViewportTest, getCenterTest) {
    Viewport viewport(1600, 900);
    EXPECT_EQ(viewport.getCenter(), glm::vec2(800, 450));

    viewport = Viewport(1920, 1080);
    EXPECT_EQ(viewport.getCenter(), glm::vec2(960, 540));
}

TEST(ViewportTest, getAspectRatioTest) {
    Viewport viewport(1600, 900);
    EXPECT_NEAR(viewport.getAspectRatio(), 1.778, 0.01);

    viewport = Viewport(800, 600);
    EXPECT_NEAR(viewport.getAspectRatio(), 1.333, 0.01);
}

///////////////////////////////
// Window Tests
///////////////////////////////
class WindowTest : public ::testing::Test {
protected:
    WindowTest() : viewport(1600, 900), window(viewport, false) {

    }
    Viewport viewport;
    Window window;
};

TEST_F(WindowTest, displayTest) {
    FAIL();
}

TEST_F(WindowTest, closeTest) {
    FAIL();
}

TEST_F(WindowTest, clearBuffersTest) {
    FAIL();
}

TEST_F(WindowTest, setFullscreenTest) {
    FAIL();
}

TEST_F(WindowTest, setVsyncTest) {
    FAIL();
}

TEST_F(WindowTest, requestCloseTest) {
    window.requestClose();
    EXPECT_EQ(window.shouldClose(), true);
}

TEST_F(WindowTest, isOpenTest) {
    // No close request was sent, so it should not expect to close, and be open
    EXPECT_EQ(window.isOpen(), true);
}

///////////////////////////////
// Test Execution
///////////////////////////////
int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    //Do whatever setup here you will need for your tests here
    //
    //

    returnValue =  RUN_ALL_TESTS();

    //Do Your teardown here if required
    //
    //

    return returnValue;
}
