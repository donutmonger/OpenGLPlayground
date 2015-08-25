#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Mouse.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Drawable.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"
#include "ShaderProgramFactory.hpp"
#include "MouseCameraController.hpp"
#include "MeshFileParserDAE.hpp"
#include "MeshFileParserOBJ.hpp"
#include "VertexAttribute.hpp"
#include "MeshData.hpp"
#include "FlatDrawable.hpp"
#include "UserInterfaceElement.hpp"
#include "Transform3D.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <cstdio>

using namespace std;

char getKeyboardInputCharacter(SDL_Event& event) {

    char key = 0;
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode keycode = event.key.keysym.sym;
        key = keycode;
    }

    return key;
}

void handleInputs(Mouse& mouse, Window& window, Transform3D& camera_transform) {
    // Misleading argument and function name combination. The input handling does not draw from the mouse or window at all, it simply does things with them

    // Key repeat delay input
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window.requestClose();
        }

        SDL_Scancode key_scancode = event.key.keysym.scancode;
        if (key_scancode == SDL_SCANCODE_ESCAPE) {
            window.requestClose();
        }

        char key = getKeyboardInputCharacter(event);
        if (key == 'm'){
            mouse.toggleVisibility();
        } else if (key == 'c') {
            mouse.centerInWindow(window);
        }

    }

    // Continuous input
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    glm::vec3 camera_movement(0, 0, 0);
    if (keyboard[SDL_SCANCODE_W]) {
        camera_movement += glm::vec3(0, 0, -1);
    }
    if (keyboard[SDL_SCANCODE_S]) {
        camera_movement += glm::vec3(0, 0, 1);
    }
    if (keyboard[SDL_SCANCODE_A]) {
        camera_movement += glm::vec3(-1, 0, 0);
    }
    if (keyboard[SDL_SCANCODE_D]) {
        camera_movement += glm::vec3(1, 0, 0);
    }
    if (keyboard[SDL_SCANCODE_SPACE]) {
        camera_movement += glm::vec3(0, 1, 0);
    }
    if (keyboard[SDL_SCANCODE_LSHIFT]) {
        camera_movement += glm::vec3(0, -1, 0);
    }

    if (glm::length(camera_movement) != 0){
        camera_movement = glm::normalize(camera_movement);
    }
    camera_movement = camera_movement * 0.1f;
    camera_transform.moveByLocal(camera_movement);

}

int main(int argc, char* argv[]) {

    Viewport viewport(1600, 900);
    Window window(viewport, false);
    OpenGLContext gl_context(4, 1, window);
    Mouse mouse;

    ShaderProgramFactory shader_program_factory;
    ShaderProgram shader = shader_program_factory.createShaderProgram("shaders/temp.vs", "shaders/temp.fs");

    float field_of_view = 45.0f;
    float near_clip = 0.1f;
    float far_clip = 500.0f;
    Transform3D camera_transform;
    Camera camera(viewport, camera_transform, field_of_view, near_clip, far_clip);

    MouseCameraController mouse_camera_controller(mouse, camera_transform, window, 0.001);

    glm::vec3 camera_start_position(-1, 2, 6);
    camera_transform.setPosition(camera_start_position);

    MeshFileParserDAE mesh_file_parser_dae;
    MeshFileParserOBJ mesh_file_parser_obj;

    VertexSpecification vertex_specification;
    vertex_specification.addAttribute(VertexAttribute("position", 3, 0));
    vertex_specification.addAttribute(VertexAttribute("normal", 3, 3));
    vertex_specification.addAttribute(VertexAttribute("texture_coordinates", 2, 6));

    mesh_file_parser_dae.loadMeshFromFile("res/castle_tower.dae");
    MeshData castle_tower_mesh_data(mesh_file_parser_dae.getVertexArray(), mesh_file_parser_dae.getFaceArray());
    Mesh castle_tower_mesh(castle_tower_mesh_data, vertex_specification);

    mesh_file_parser_obj.loadMeshFromFile("res/fence.obj");
    MeshData fence_mesh_data(mesh_file_parser_obj.getVertexArray(), mesh_file_parser_obj.getFaceArray());
    Mesh fence_mesh(fence_mesh_data, vertex_specification);

    Texture castle_tower_diffuse("res/castle_tower_diff.png");
    TextureManager castle_tower_textures(castle_tower_diffuse);
    Transform3D castle_tower1_transform;
    Drawable castle_tower1(castle_tower_mesh, shader, castle_tower_textures, castle_tower1_transform);
    castle_tower1_transform.rotateByGlobal(glm::vec3(-M_PI / 2.0, 0, 0));

    Transform3D castle_tower2_transform;
    Drawable castle_tower2(castle_tower_mesh, shader, castle_tower_textures, castle_tower2_transform);
    castle_tower2_transform.setPosition(glm::vec3(-4, 0, 1));
    castle_tower2_transform.rotateByGlobal(glm::vec3(-M_PI / 2.0, 0, 0));

    Texture fence_diffuse("res/fence_diff.png");
    TextureManager fence_textures(fence_diffuse);
    Transform3D fence_transform;
    Drawable fence(fence_mesh, shader, fence_textures, fence_transform);
    fence_transform.setPosition(glm::vec3(2, 0, 1));

    ShaderProgram flat_shader = shader_program_factory.createShaderProgram("shaders/flat.vs", "shaders/flat.fs");

    VertexSpecification flat_mesh_vertex_specification;
    flat_mesh_vertex_specification.addAttribute(VertexAttribute("position", 2, 0));
    flat_mesh_vertex_specification.addAttribute(VertexAttribute("texture_coordinates", 2, 2));

    vector<GLfloat> vertices = {
             -1.0f,  1.0f,  0.0f, 1.0f,
             -1.0f, -1.0f,  0.0f, 0.0f,
              1.0f,  1.0f,  1.0f, 1.0f,
              1.0f, -1.0f,  1.0f, 0.0f,

    };

    vector<GLuint> elements = {
            0, 1, 2,
            1, 3, 2,
    };

    MeshData flat_mesh_data(vertices, elements);
    Mesh flat_mesh(flat_mesh_data, flat_mesh_vertex_specification);

    Transform2D text_box_transform;
    FlatDrawable test_box(flat_mesh, flat_shader, text_box_transform);
    UserInterfaceElement ui_element(viewport, test_box);
    ui_element.setWidthInPixels(1600);
    ui_element.setHeightInPixels(100);
    ui_element.setCenterInPixels(glm::vec2(800, 50));

    // Display loop
    while(window.isOpen()) {
        window.clearBuffers();

        castle_tower1.draw(camera);
        castle_tower2.draw(camera);
        fence.draw(camera);

        ui_element.draw();

        castle_tower1_transform.rotateByGlobal(glm::vec3(0, 0.01, 0));

        handleInputs(mouse, window, camera_transform);
        mouse_camera_controller.update();
        window.display();

    }

    // Close the window
    window.close();

    // Nothing went wrong!
    return 0;
}
