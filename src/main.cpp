#include<iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
 const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
    float vertices1[]= {
        //first triangle
         -0.9f,0.0f, 0.0f,
         -0.8f,0.3f, 0.0f,
         -0.7f, 0.0f, 0.0f
    };
    float vertices2 []{
        //second triangle
         0.9f, 0.0f, 0.0f,
         0.8f, 0.3f, 0.0f,
         0.7f,0.0f,0.0f
    };
    unsigned int indices []= {
        0,1,3,
        1,2,3
    };
   void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
int main (){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    unsigned int VAO[2];
    glGenVertexArrays(2,VAO);
   

    unsigned int VBO[2];
    glGenBuffers(2,VBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1),vertices1,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

   unsigned int EBO;
   glGenBuffers(1,&EBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);
   
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
glCompileShader(vertexShader);
  //error debugging compilation
  int success;
  char infolog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(vertexShader,512,NULL,infolog);
    std:: cout <<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
  }

  //fragment shader
  unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);


  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader,512,NULL,infolog);
    std:: cout <<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
  }
  //Shader program to link

  unsigned int shaderProgram;
shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
//

glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
    std:: cout <<"ERROR::SHADER Program::LINKING_FAILED\n" << infolog << std::endl;
    
}
glUseProgram(shaderProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
glBindVertexArray(0);
while(!glfwWindowShouldClose(window))
{
    glClearColor(0.06f, 0.8f, 0.03f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO[0]);
   glDrawArrays(GL_TRIANGLES,0,3);
   glBindVertexArray(VAO[1]);
   glDrawArrays(GL_TRIANGLES,0,3);

     glfwSwapBuffers(window);
    glfwPollEvents();  
}
glfwTerminate();
 return 0;
}