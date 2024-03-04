#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Global variables to keep track of frame speed
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//Functions ----------------------------------------------------------------------------------- 


int main()
{
    //SETUP OF PROGRAM -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "Michael Evans Module 6 Assignment", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;

    }
    glfwMakeContextCurrent(window);
    //functions to capture mouse
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



    //BUILD AND COMPILE OUR SHADER PROGRAM ------------------------------------------------------------------------------------------------------------------------------------*********************************

    // build and compile our shader program
    // ------------------------------------
    Shader PyramidShader("pyramid_shader.vs", "pyramid_shader.fs"); 
    Shader PlaneShader("PlaneShader.vs", "PlaneShader.fs");
    Shader MakeupBoxShader("MakeupBox.vs", "MakeupBox.fs");
    Shader BookShader("BookShader.vs", "BookShader.fs");
    Shader LightShader("lightsource_shader.vs", "lightsource_shader.fs");
    Shader NailPolishShader("NailPolish.vs", "NailPolish.fs");
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //SETUP VERTEX INPUT DATA-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    float PyramidVertices[] = {

        //Location            //Normal          //Texture

        // Front face
        -0.75f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,  0.5f, 1.0f, // vertex 0
        -1.0f, -0.5f, -0.25f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // vertex 1
        -0.5f, -0.5f, -0.25f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // vertex 2

        // Right face
        -0.75f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f,  0.5f, 1.0f, // vertex 3
        -0.5f, -0.5f, -0.25f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // vertex 4
        -0.5f, -0.5f, -0.75f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // vertex 5

        // Back face
        -0.75f, 0.0f, -0.5f,   0.0f, 0.0f, -1.0f,  0.5f, 1.0f, // vertex 6
        -0.5f, -0.5f, -0.75f,   0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // vertex 7
        -1.0f, -0.5f,  -0.75f,   0.0f, 0.0f, -1.0f,  1.0f, 0.0f, // vertex 8

        // Left face
        -0.75f, 0.0f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.5f, 1.0f, // vertex 9
        -1.0f, -0.5f, -0.75f,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // vertex 10
        -1.0f, -0.5f, -0.25f,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // vertex 11

        // Bottom face
        -1.0f, -0.5f, -0.25f,   0.0f, -1.0f, 0.0f,  0.0f, 1.0f, // vertex 12
        -0.5f, -0.5f, -0.25f,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f, // vertex 13
        -0.5f, -0.5f, -0.75f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // vertex 14
        -0.5f, -0.5f, -0.75f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // vertex 15
        -1.0f, -0.5f, -0.75f,   0.0f, -1.0f, 0.0f,  0.0f, 0.0f, // vertex 16
        -1.0f, -0.5f, -0.25f,   0.0f, -1.0f, 0.0f,  0.0f, 1.0f  // vertex 17
    };
    float PlaneVertices[] = {
        
        // Vertices                // Normals           // Texture Coordinates
        -2.0f, -0.51f, -2.0f,      0.0f, 1.0f, 0.0f,    0.0f, 0.0f,  // bottom-left
        -2.0f, -0.51f,  2.0f,      0.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // top-left
         2.0f, -0.51f, -2.0f,      0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  // bottom-right
         2.0f, -0.51f, -2.0f,      0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  // bottom-right
        -2.0f, -0.51f,  2.0f,      0.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // top-left
         2.0f, -0.51f,  2.0f,      0.0f, 1.0f, 0.0f,    1.0f, 1.0f   // top-right
        
    };
    float MakeupBoxVertices[] = {
        // Vertices                 // Normals           //Texture Coordinates
        // Back face
        -1.5f, -0.5f, 0.75f,       0.0f, 0.0f, -1.0f,  0.0f, 0.0f,  // bottom-front-left
        -1.5f, -0.25f, 0.75f,      0.0f, 0.0f, -1.0f,  0.0f, 1.0f,  // top-front-left
        -1.0f, -0.5f, 0.75f,       0.0f, 0.0f, -1.0f,  1.0f, 0.0f,  // bottom-front-right
        -1.0f, -0.5f, 0.75f,       0.0f, 0.0f, -1.0f,  1.0f, 0.0f,  // bottom-front-right
        -1.5f, -0.25f, 0.75f,      0.0f, 0.0f, -1.0f,  0.0f, 1.0f,  // top-front-left
        -1.0f, -0.25f, 0.75f,      0.0f, 0.0f, -1.0f,  1.0f, 1.0f,  // top-front-right

        // Front face
        -1.5f, -0.5f, 1.25f,       -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // bottom-back-left
        -1.5f, -0.25f, 1.25f,      -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // top-back-left
        -1.0f, -0.5f, 1.25f,       -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-left
        -1.0f, -0.5f, 1.25f,       -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-left
        -1.5f, -0.25f, 1.25f,      -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // top-back-left
        -1.0f, -0.25f, 1.25f,      -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // top-front-left

        // Top face
        -1.5f, -0.25f, 0.75f,      0.0f, 1.0f, 0.0f,   0.5f, 0.0f,  // top-front-left
        -1.5f, -0.25f, 1.25f,      0.0f, 1.0f, 0.0f,   0.5f, 1.0f,  // top-back-left
        -1.0f, -0.25f, 0.75f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // top-front-right
        -1.0f, -0.25f, 0.75f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // top-front-right
        -1.5f, -0.25f, 1.25f,      0.0f, 1.0f, 0.0f,   0.5f, 1.0f,  // top-back-left
        -1.0f, -0.25f, 1.25f,      0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // top-back-right

        // Right face
        -1.0f, -0.5f, 0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-right
        -1.0f, -0.25f, 0.75f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // top-front-right
        -1.0f, -0.5f, 1.25f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // bottom-back-right
        -1.0f, -0.5f, 1.25f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // bottom-back-right
        -1.0f, -0.25f, 0.75f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // top-front-right
        -1.0f, -0.25f, 1.25f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top-back-right

        // Bottom face
        - 1.5f, -0.5f, 0.75f,       0.0f, -1.0f, 0.0f,  0.0f, 0.0f,  // bottom-front-left
        -1.0f, -0.5f, 0.75f,       0.0f, -1.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-right
        -1.5f, -0.5f, 1.25f,       0.0f, -1.0f, 0.0f,  0.0f, 1.0f,  // bottom-back-left
        -1.5f, -0.5f, 1.25f,       0.0f, -1.0f, 0.0f,  0.0f, 1.0f,  // bottom-back-left
        -1.0f, -0.5f, 0.75f,       0.0f, -1.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-right
        -1.0f, -0.5f, 1.25f,       0.0f, -1.0f, 0.0f,  1.0f, 1.0f,  // bottom-back-right

        // Left face
        -1.5f, -0.5f, 1.25f,       1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // bottom-back-left
        -1.5f, -0.25f, 1.25f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-back-left
        -1.5f, -0.5f, 0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-left
        -1.5f, -0.5f, 0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-left
        -1.5f, -0.25f, 1.25f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-back-left
        -1.5f, -0.25f, 0.75f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f   // top-front-left
    };
    float BookVertices[] =
    {
        // Vertices                 // Normals           //Texture
        // Front face
        0.0f, -0.5f, -0.75f,       0.0f, 0.0f, -1.0f,  0.0f, 0.0f,  // bottom-front-left
        0.0f, 0.75f, -0.75f,       0.0f, 0.0f, -1.0f,  0.0f, 1.0f,  // top-front-left
        0.25f, -0.5f, -0.75f,      0.0f, 0.0f, -1.0f,  1.0f, 0.0f,  // bottom-front-right
        0.25f, -0.5f, -0.75f,       0.0f, 0.0f, -1.0f,  1.0f, 0.0f,  // bottom-front-right
        0.0f, 0.75f, -0.75f,       0.0f, 0.0f, -1.0f,  0.0f, 1.0f,  // top-front-left
        0.25f, 0.75f, -0.75f,      0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-front-right

        // Back face
        0.0f, -0.5f, -1.75f,       -1.0f, 0.0f, 0.0f,  0.9f, 0.0f,  // bottom-back-left
        0.0f, 0.75f, -1.75f,       -1.0f, 0.0f, 0.0f,  0.9f, 1.0f,  // top-back-left
        0.25f, -0.5f, -1.75f,      -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-left
        0.25f, -0.5f, -1.75f,      -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-left
        0.0f, 0.75f, -1.75f,       -1.0f, 0.0f, 0.0f,  0.9f, 1.0f,  // top-back-left
        0.25f, 0.75f, -1.75f,      -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // top-front-left

        // Top face
        0.0f, 0.75f, -0.75f,       0.0f, 1.0f, 0.0f,   0.5f, 0.0f,  // top-front-left
        0.0f, 0.75f, -1.75f,       0.0f, 1.0f, 0.0f,   0.5f, 1.0f,  // top-back-left
        0.25f, 0.75f, -0.75f,       0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // top-front-right
        0.25f, 0.75f, -0.75f,       0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // top-front-right
        0.0f, 0.75f, -1.75f,       0.0f, 1.0f, 0.0f,   0.5f, 1.0f,  // top-back-left
        0.25f, 0.75f, -1.75f,       0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // top-back-right

        // Right face
        0.25f, -0.5f, -0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-right
        0.25f, 0.75f, -0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // top-front-right
        0.25f, -0.5f, -1.75f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // bottom-back-right
        0.25f, -0.5f, -1.75f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // bottom-back-right
        0.25f, 0.75f, -0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // top-front-right
        0.25f, 0.75f, -1.75f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-back-right

        // Bottom face
        0.0f, -0.5f, -0.75f,       0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-left
        0.25f, -0.5f, -0.75f,       0.0f, -1.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-right
        0.0f, -0.5f, -1.75f,       0.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // bottom-back-left
        0.0f, -0.5f, -1.75f,       0.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // bottom-back-left
        0.25f, -0.5f, -0.75f,       0.0f, -1.0f, 0.0f,  1.0f, 0.0f,  // bottom-front-right
        0.25f, -0.5f, -1.75f,       0.0f, -1.0f, 0.0f,  1.0f, 1.0f,  // bottom-back-right

        // Left face
        0.0f, -0.5f, -1.75f,       1.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // bottom-back-left
        0.0f, 0.75f, -1.75f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-back-left
        0.0f, -0.5f, -0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-left
        0.0f, -0.5f, -0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-front-left
        0.0f, 0.75f, -1.75f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-back-left
        0.0f, 0.75f, -0.75f,       1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top-front-left
    };

    float NailPolishBaseVertices[] =
    {
        // Vertices             // Normals           // Texture Coordinates

        //Top Of Base Of Bottle Hexagon
        // 
        //Triangle1
        0.812475f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle
        0.687525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Top Right Back
        0.5625f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f, //Point G Top Center Point
        //Triangle2
        0.687525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Top Right Back
        0.437525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Top Left Back
        0.5625f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle3
        0.437525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Top Left Back
        0.3125f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle
        0.5625f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle4
        0.3125f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle
        0.437525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front
        0.5625f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle5
        0.437525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front
        0.687525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front
        0.5625f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle6
        0.687525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front
        0.812475f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle
        0.5625f, 0.0625f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,   //Point G Center Point

        //Bottom Of Base Of Bottle Hexagon
        // 
        //Triangle1
        0.812475f, -0.5f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Bottom Right Middle
        0.687525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Bottom Right Back
        0.5625f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f, //Point G Bottom Center Point
        //Triangle2
        0.687525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Bottom Right Back
        0.437525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Bottom Left Back
        0.5625f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle3
        0.437525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Bottom Left Back
        0.3125f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Bottom Left Middle
        0.5625f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G  BottomCenter Point
        //Triangle4
        0.3125f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Bottom Left Middle
        0.437525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Bottom Left Front
        0.5625f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle5
        0.437525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Bottom Left Front
        0.687525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Bottom Rigth Front
        0.5625f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle6
        0.687525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Bottom Rigth Front
        0.812475f, -0.5f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Bottom Right Middle
        0.5625f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,   //Point G Bottom Center Point

        //Front Middle Base Rectangle
        //Triangle1
        0.687525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front
        0.437525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front
        0.687525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Bottom Rigth Front
        //Triangle2
        0.687525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Bottom Rigth Front
        0.437525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Bottom Left Front
        0.437525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front

        //Front Right Base Rectangle
        //Triangle1
        0.687525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front
        0.812475f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle
        0.812475f, -0.5f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Bottom Right Middle
        //triangle2
        0.812475f, -0.5f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Bottom Right Middle
        0.687525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Bottom Rigth Front
        0.687525f, 0.0625f, 0.645f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front

        //Back Right Base Rectangle
        //Triangle1
        0.812475f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle
        0.812475f, -0.5f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Bottom Right Middle
        0.687525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Bottom Right Back
        //Triangle2
        0.687525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Top Right Back
        0.687525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Bottom Right Back
        0.812475f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle

        //Back Middle Base Rectangle
        //triangle1 
        0.687525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Bottom Right Back
        0.437525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Bottom Left Back
        0.437525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Top Left Back
        //triangle2
        0.687525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Top Right Back
        0.437525f, 0.0625f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Top Left Back
        0.687525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Bottom Right Back

        //Back Left Base Rectangle
        //triangle1
        0.437525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Bottom Left Back
        0.3125f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Bottom Left Middle
        0.3125f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle
        //triangle2
        0.437525f, 0.0625f, 1.080f,   0.0f, -1.0f, 0.0f,   0.25f, 0.75f, //Point C Top Left Back
        0.3125f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,   0.0f, 0.5f, // Point D Top Left Middle
        0.437525f, -0.5f, 1.080f,     0.0f, -1.0f, 0.0f,   0.25f, 0.75f, //Point C Bottom Left Back

        //Front Left Base Rectangle
        //triangle1
        0.3125f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle
        0.437525f, 0.0625f, 0.645f,   0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front
        0.437525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Bottom Left Front
        //triangle2
        0.3125f, -0.5f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Bottom Left Middle
        0.437525f, -0.5f, 0.645f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Bottom Left Front
        0.3125f, 0.0625f, 0.8625f,    0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle


        //Top of Cap Of Bottle Hexagon
        // 
        //Triangle1
        0.6874875f, 0.25f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle
        0.6250125f, 0.25f, 0.97125f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Top Right Back
        0.5625f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f, //Point G Top Center Point
        //Triangle2
        0.6250125f, 0.25f, 0.97125f,     0.0f, -1.0f, 0.0f,    0.75f, 0.75f, //Point B Top Right Back
        0.4990125f, 0.25f, 0.97125f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Top Left Back
        0.5625f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle3
        0.4990125f, 0.25f, 0.97125f,     0.0f, -1.0f, 0.0f,    0.25f, 0.75f, //Point C Top Left Back
        0.4375f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle
        0.5625f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle4
        0.4375f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.0f, 0.5f, // Point D Top Left Middle
        0.4990125f, 0.25f, 0.75375f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front
        0.5625f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle5
        0.4990125f, 0.25f, 0.75375f,     0.0f, -1.0f, 0.0f,    0.25f, 0.25f, // Point E Top Left Front
        0.6250125f, 0.25f, 0.75375f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front
        0.5625f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,  //Point G Center Point
        //Triangle6
        0.6250125f, 0.25f, 0.75375f,     0.0f, -1.0f, 0.0f,    0.75f, 0.25f, //Point F Top Rigth Front
        0.6874875f, 0.25f, 0.8625f,    0.0f, -1.0f, 0.0f,    1.0f, 0.5f, //point A Top Right Middle
        0.5625f, 0.25f, 0.8625f,      0.0f, -1.0f, 0.0f,    0.5f, 0.5f,   //Point G Center Point

        //Bottom of Cap Of Bottle Hexagon
        // 
        //Triangle1
        0.6874875f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Bottom Right Middle
        0.6250125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Bottom Right Back
        0.5625f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f, //Point G Bottom Center Point
        //Triangle2
        0.6250125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Bottom Right Back
        0.4990125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Bottom Left Back
        0.5625f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle3
        0.4990125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Bottom Left Back
        0.4375f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Bottom Left Middle
        0.5625f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle4
        0.4375f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Bottom Left Middle
        0.4990125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Bottom Left Front
        0.5625f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle5
        0.4990125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Bottom Left Front
        0.6250125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Bottom Rigth Front
        0.5625f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,  //Point G Bottom Center Point
        //Triangle6
        0.6250125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Bottom Rigth Front
        0.6874875f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Bottom Right Middle
        0.5625f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,   //Point G Bottom Center Point

        //Front middle cap rectangle
            //triangle1
            0.4990125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Top Left Front
            0.6250125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Top Rigth Front
            0.6250125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Bottom Rigth Front
            //triangle2
            0.4990125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Bottom Left Front
            0.6250125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Bottom Rigth Front
            0.4990125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Top Left Front

        //front right cap rectangle
            //triangle1 
            0.6250125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Top Rigth Front
            0.6874875f, 0.25f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Top Right Middle
            0.6874875f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Bottom Right Middle
            //triangle2
            0.6250125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Bottom Rigth Front
            0.6874875f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Bottom Right Middle
            0.6250125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.75f, 0.25f, //Point F Top Rigth Front

        //back right cap rectangle
            //triangle1
            0.6874875f, 0.25f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Top Right Middle
            0.6250125f, 0.25f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Top Right Back
            0.6250125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Bottom Right Back
            //triangle2
            0.6874875f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Bottom Right Middle
            0.6250125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Bottom Right Back
            0.6874875f, 0.25f, 0.8625f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, //point A Top Right Middle

        //Back middle cap rectangle
        //triangle1
            0.6250125f, 0.25f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Top Right Back
            0.4990125f, 0.25f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Top Left Back
            0.4990125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Bottom Left Back
        //triangle2
            0.6250125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Bottom Right Back
            0.4990125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Bottom Left Back
            0.6250125f, 0.25f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.75f, 0.75f, //Point B Top Right Back

        //back left cap rectangle
        //triangle1 
            0.4990125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Bottom Left Back
            0.4375f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Bottom Left Middle
            0.4375f, 0.25f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Top Left Middle
        //triangle2
            0.4990125f, 0.25f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Top Left Back
            0.4375f, 0.25f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Top Left Middle
            0.4990125f, 0.0625f, 0.97125f, 0.0f, -1.0f, 0.0f, 0.25f, 0.75f, //Point C Bottom Left Back

        //front left cap rectangle
        //triangle1
            0.4375f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Bottom Left Middle
            0.4990125f, 0.0625f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Bottom Left Front
            0.4990125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Top Left Front
        //triangle2
            0.4375f, 0.25f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Top Left Middle
            0.4990125f, 0.25f, 0.75375f, 0.0f, -1.0f, 0.0f, 0.25f, 0.25f, // Point E Top Left Front
            0.4375f, 0.0625f, 0.8625f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, // Point D Bottom Left Middle

    };
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // positions of the point lights (There are only 2 point lights as defined in the fragment shader of the PyramaidShader)
    glm::vec3 pointLightPositions[] = 
    {
        glm::vec3(-2.0f,  0.75f,  0.0f),
        glm::vec3(2.0f, 0.0f, 0.0f),
    };

    //Buffers For Pyramid Object
    //---------------------------------------------------------------------------------------------
    unsigned int PyramidVBO, PyramidVAO;
    glGenVertexArrays(1, &PyramidVAO);
    glGenBuffers(1, &PyramidVBO);

    glBindVertexArray(PyramidVAO);

    glBindBuffer(GL_ARRAY_BUFFER, PyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PyramidVertices), PyramidVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Texture Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //Buffers For Plane Object
    //----------------------------------------------------------------------------------------------
    
    unsigned int PlaneVBO, PlaneVAO;
    glGenVertexArrays(1, &PlaneVAO);
    glGenBuffers(1, &PlaneVBO);

    glBindVertexArray(PlaneVAO);

    glBindBuffer(GL_ARRAY_BUFFER, PlaneVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PlaneVertices), PlaneVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Texture Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Buffers For Makeup Object
    //----------------------------------------------------------------------------------------------

    unsigned int MakeupVBO, MakeupVAO;
    glGenVertexArrays(1, &MakeupVAO);
    glGenBuffers(1, &MakeupVBO);

    glBindVertexArray(MakeupVAO);

    glBindBuffer(GL_ARRAY_BUFFER, MakeupVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MakeupBoxVertices), MakeupBoxVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Color Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Buffers For Book Object
    //----------------------------------------------------------------------------------------------

    unsigned int BookVBO, BookVAO;
    glGenVertexArrays(1, &BookVAO);
    glGenBuffers(1, &BookVBO);

    glBindVertexArray(BookVAO);

    glBindBuffer(GL_ARRAY_BUFFER, BookVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BookVertices), BookVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Color Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    

    //Buffers For NailPolish Object
    //----------------------------------------------------------------------------------------------

    unsigned int NailPolishVBO, NailPolishVAO;
    glGenVertexArrays(1, &NailPolishVAO);
    glGenBuffers(1, &NailPolishVBO);

    glBindVertexArray(NailPolishVAO);

    glBindBuffer(GL_ARRAY_BUFFER, NailPolishVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(NailPolishBaseVertices), NailPolishBaseVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Color Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Light Source Pyramid----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, PyramidVBO);
    // set the vertex attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    // load textures(we now use a utility function to keep the code more organized)
        // -----------------------------------------------------------------------------
        unsigned int pyramidDiffuseMap = loadTexture("textures/pink.jpg");
        unsigned int planeDiffuseMap = loadTexture("textures/whitedesk.jpg");
        unsigned int makeupDiffuseMap = loadTexture("textures/makeup.jpg");
        unsigned int bookDiffuseMap = loadTexture("textures/book.jpg");
        unsigned int nailpolishpDiffuseMap = loadTexture("textures/nailpolishBase.jpg");

    // shader configuration
    // --------------------
    PyramidShader.use();
    PyramidShader.setInt("material.diffuse", 0);
    PlaneShader.use();
    PlaneShader.setInt("material.diffuse", 0);
    MakeupBoxShader.use();
    MakeupBoxShader.setInt("material.diffuse", 0);
    BookShader.use();
    BookShader.setInt("material.diffuse", 0);
    NailPolishShader.use();
    NailPolishShader.setInt("material.diffuse", 0);
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //MAIN RENDER LOOP THAT KEEPS THE PROGRAM RUNNING -----------------------------------------------------------------------------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // per - frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        //rendering commands here 
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        //Pyramid Object Properties ------------------------------------------------------------------------------------------
        
        //bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pyramidDiffuseMap);
        
        //activate shader
        PyramidShader.use();

        //Pyramid Shader Attributes       
        PyramidShader.setVec3("viewPos", camera.Position);
        PyramidShader.setFloat("material.shininess", 32.0f);

        // light properties
        // point light 1
        PyramidShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        PyramidShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        PyramidShader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        PyramidShader.setVec3("pointLights[0].specular", 0.25f, 0.5f, 0.25f);
        PyramidShader.setFloat("pointLights[0].constant", 1.0f);
        PyramidShader.setFloat("pointLights[0].linear", 0.09f);
        PyramidShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        PyramidShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        PyramidShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        PyramidShader.setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
        PyramidShader.setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);
        PyramidShader.setFloat("pointLights[1].constant", 1.0f);
        PyramidShader.setFloat("pointLights[1].linear", 0.09f);
        PyramidShader.setFloat("pointLights[1].quadratic", 0.032f);

        // material properties
        PyramidShader.setFloat("material.shininess", 32.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        PyramidShader.setMat4("projection", projection);
        PyramidShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        PyramidShader.setMat4("model", model);
             
        // render pyramid
        glBindVertexArray(PyramidVAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);
        //--------------------------------------------------------------------------------------------------------------------------

        //Plane Object Creation ----------------------------------------------------------------------------------------------------
        
        //bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, planeDiffuseMap);

        //activate shader
        PlaneShader.use();

        //Plane Material Attributes
        PlaneShader.setVec3("viewPos", camera.Position);
        PlaneShader.setFloat("material.shininess", 32.0f);

        // light properties
        // point light 1
        PlaneShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        PlaneShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        PlaneShader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        PlaneShader.setVec3("pointLights[0].specular", 0.25f, 0.25f, 0.25f);
        PlaneShader.setFloat("pointLights[0].constant", 1.0f);
        PlaneShader.setFloat("pointLights[0].linear", 0.09f);
        PlaneShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        PlaneShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        PlaneShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        PlaneShader.setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
        PlaneShader.setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);
        PlaneShader.setFloat("pointLights[1].constant", 1.0f);
        PlaneShader.setFloat("pointLights[1].linear", 0.09f);
        PlaneShader.setFloat("pointLights[1].quadratic", 0.032f);

        PlaneShader.setMat4("projection", projection);
        PlaneShader.setMat4("view", view);
        PlaneShader.setMat4("model", model);

        // render plane
        glBindVertexArray(PlaneVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //--------------------------------------------------------------------------------------------------------------------------

        //MakeupBox Object Creation ----------------------------------------------------------------------------------------------------

        //bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, makeupDiffuseMap);

        //activate shader
        MakeupBoxShader.use();

        //Makeup Material Attributes
        MakeupBoxShader.setVec3("viewPos", camera.Position);
        MakeupBoxShader.setFloat("material.shininess", 32.0f);

        // light properties
        // point light 1
        MakeupBoxShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        MakeupBoxShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        MakeupBoxShader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        MakeupBoxShader.setVec3("pointLights[0].specular", 0.25f, 0.25f, 0.25f);
        MakeupBoxShader.setFloat("pointLights[0].constant", 1.0f);
        MakeupBoxShader.setFloat("pointLights[0].linear", 0.09f);
        MakeupBoxShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        MakeupBoxShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        MakeupBoxShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        MakeupBoxShader.setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
        MakeupBoxShader.setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);
        MakeupBoxShader.setFloat("pointLights[1].constant", 1.0f);
        MakeupBoxShader.setFloat("pointLights[1].linear", 0.09f);
        MakeupBoxShader.setFloat("pointLights[1].quadratic", 0.032f);

        MakeupBoxShader.setMat4("projection", projection);
        MakeupBoxShader.setMat4("view", view);
        MakeupBoxShader.setMat4("model", model);

        // render Makeup Box
        glBindVertexArray(MakeupVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //--------------------------------------------------------------------------------------------------------------------------

        //Book Object Creation ----------------------------------------------------------------------------------------------------

       //bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bookDiffuseMap);

        //activate shader
        BookShader.use();

        //Makeup Material Attributes
        BookShader.setVec3("viewPos", camera.Position);
        BookShader.setFloat("material.shininess", 32.0f);

        // light properties
        // point light 1
        BookShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        BookShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        BookShader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        BookShader.setVec3("pointLights[0].specular", 0.25f, 0.25f, 0.25f);
        BookShader.setFloat("pointLights[0].constant", 1.0f);
        BookShader.setFloat("pointLights[0].linear", 0.09f);
        BookShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        BookShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        BookShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        BookShader.setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
        BookShader.setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);
        BookShader.setFloat("pointLights[1].constant", 1.0f);
        BookShader.setFloat("pointLights[1].linear", 0.09f);
        BookShader.setFloat("pointLights[1].quadratic", 0.032f);

        BookShader.setMat4("projection", projection);
        BookShader.setMat4("view", view);
        BookShader.setMat4("model", model);

        // render plane
        glBindVertexArray(BookVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //--------------------------------------------------------------------------------------------------------------------------

        // NailPolish Object Properties ---------------------------------------------------------------------------------------------------
        
        //bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, nailpolishpDiffuseMap);

        //activate shader
        NailPolishShader.use();

        //Makeup Material Attributes
        NailPolishShader.setVec3("viewPos", camera.Position);
        NailPolishShader.setFloat("material.shininess", 32.0f);

        // light properties
        // point light 1
        NailPolishShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        NailPolishShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        NailPolishShader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        NailPolishShader.setVec3("pointLights[0].specular", 0.25f, 0.25f, 0.25f);
        NailPolishShader.setFloat("pointLights[0].constant", 1.0f);
        NailPolishShader.setFloat("pointLights[0].linear", 0.09f);
        NailPolishShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        NailPolishShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        NailPolishShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        NailPolishShader.setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
        NailPolishShader.setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);
        NailPolishShader.setFloat("pointLights[1].constant", 1.0f);
        NailPolishShader.setFloat("pointLights[1].linear", 0.09f);
        NailPolishShader.setFloat("pointLights[1].quadratic", 0.032f);

        NailPolishShader.setMat4("projection", projection);
        NailPolishShader.setMat4("view", view);
        NailPolishShader.setMat4("model", model);

        // render NailPolish
        glBindVertexArray(NailPolishVAO);
        glDrawArrays(GL_TRIANGLES, 0, 144);

        //------------------------------------------------------------------------------------------------------------------------------


        // Lamp Object Properties ---------------------------------------------------------------------------------------------------
        LightShader.use();
        LightShader.setMat4("projection", projection);
        LightShader.setMat4("view", view);
        
        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            LightShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 18);
        }
        //------------------------------------------------------------------------------------------------------------------------------
        

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //TERMINATION OF THE PROGRAM --------------------------------------------------------------------------------------------------------------------------------------------------------------------

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//FUNCTIONS 


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}