#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// â ũ��
const GLint WIDTH = 800, HEIGHT = 600;

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

	if (!glewInit())
	{
		cout << "GLEW initialisation failed" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport Size - Viewport? ������ ������ � �κп� ������������ ����
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Loop Until window Closed 
	while (!glfwWindowShouldClose(mainWindow)) // ������ â�� ���� ������ �ݺ� 
	{
		// Get + Handler user input events 
		glfwPollEvents(); // Ŭ��, ȭ�� �̵�, �������� ��, �� ��� �̺�Ʈ�� ����

		// Clear Window 
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Ư�� ��(����)���� �����
		glClear(GL_COLOR_BUFFER_BIT); // �� ���۸� Ư�� ��(����)���� �����

	}

	return 0;
}