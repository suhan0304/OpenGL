#include <stdio.h>
#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// â ũ��
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;


// Vertex Shader
static const char* vShader = "									\n\
#version 330													\n\
																\n\
layout(location = 0) in vec3 pos;								\n\
																\n\
void main()														\n\
{																\n\
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);	\n\
}																\n\
";

// Fragmen shader
static const char* fShader = "									\n\
#version 330													\n\
																\n\
out vec4 colour;												\n\
																\n\
void main()														\n\
{																\n\
	colour = vec4(1.0, 0.0, 0.0f, 1.0);							\n\
}																\n\
";


void CreateTriagnle() {
	GLfloat verticies[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;			// result
	GLchar eLog[1024] = { 0 };  // Error Log

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error compiling the " << shaderType << " shader : " << eLog << endl;
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders() {
	shader = glCreateProgram();

	if (!shader)
	{
		cout << "Error creating shader program" << endl;
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;			// result
	GLchar eLog[1024] = { 0 };  // Error Log

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) 
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error linking program : " << eLog << endl;
		return;
	}

	glValidateProgram(shader); // ���̴��� OpenGl ���ؽ�Ʈ���� ��ȿ���� �˻�	
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error validating program : " << eLog << endl;
		return;
	}
}

int main()
{
	// glfw �ʱ�ȭ
	if (!glfwInit())
	{
		cout << "GLFW Initialisation failed!" << endl;
		glfwTerminate(); // glfw ����
		return 1;
	}

	//������ �Ӽ� �¾�
	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Version  3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No Backwards Compatibility (����� ȣȯ �Ұ���)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility (������ ȣȯ ����)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// ������ â �����
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "test window", NULL, NULL);
	if (!mainWindow)
	{
		cout << "GLFW window creation failed" << endl;
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size Information - ������ â�� ���� ũ�⸦ ������
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to use 
	// OpenGl ���ؽ�Ʈ�� ���� �������� ���ؽ�Ʈ�� ����� �Լ� = OpenGL ����� ������ â�� ���ؽ�Ʈ�� ����ǵ��� ��
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE; // GLEW�� Ȯ�� ����� �ʱ�ȭ�� �� ����

	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW initialisation failed" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport Size - Viewport? ������ ������ � �κп� ������������ ����
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriagnle();
	CompileShaders();

	// Loop Until window Closed 
	while (!glfwWindowShouldClose(mainWindow)) // ������ â�� ���� ������ �ݺ� 
	{
		// Get + Handler user input events 
		glfwPollEvents(); // Ŭ��, ȭ�� �̵�, �������� ��, �� ��� �̺�Ʈ�� ����

		// Clear Window 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Ư�� ��(����)���� �����
		glClear(GL_COLOR_BUFFER_BIT); // �� ���۸� Ư�� ��(����)���� �����

		glUseProgram(shader); // ������ ���̴� ID�� ���� (���̴��� ������ �� �� �����ؼ� ��µ� ���)
		// ���⿡ �ۼ��Ǵ� ���� ������ ���� ���̴� ���α׷����� �׷���

		glBindVertexArray(VAO); //VAO ���ε�
		glDrawArrays(GL_TRIANGLES, 0, 3); // 0~3��° ������ ����ؼ� �ﰢ�� �׸���
		glBindVertexArray(0); // VAO ����ε�
		 
		glUseProgram(0); //���� ���̴��� ����

		// ȭ�鿡 �������� ���ۿ� �������� ���Ǵ� ���۸� ��ü
		glfwSwapBuffers(mainWindow); 

	}

	return 0;
}