#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// 창 크기
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	// glfw 초기화
	if (!glfwInit())
	{
		cout << "GLFW Initialisation failed!" << endl;
		glfwTerminate(); // glfw 종료
		return 1;
	}

	//윈도우 속성 셋업
	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Version  3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Core profile = No Backwards Compatibility (백워드 호환 불가능)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility (포워드 호환 가능)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// 윈도우 창 만들기
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "test window", NULL, NULL);
	if (!mainWindow)
	{
		cout << "GLFW window creation failed" << endl;
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size Information - 윈도우 창의 버퍼 크기를 가져옴
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to use 
	// OpenGl 컨텍스트를 현재 스레드의 컨텍스트로 만드는 함수 = OpenGL 명령이 지정된 창의 컨텍스트에 적용되도록 함
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE; // GLEW의 확장 기능을 초기화할 수 있음

	if (!glewInit())
	{
		cout << "GLEW initialisation failed" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport Size - Viewport? 프레임 버퍼의 어떤 부분에 렌더링할지를 결정
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Loop Until window Closed 
	while (!glfwWindowShouldClose(mainWindow)) // 윈도우 창이 닫힐 때까지 반복 
	{
		// Get + Handler user input events 
		glfwPollEvents(); // 클릭, 화면 이동, 리사이즈 등, 등 모든 이벤트를 감지

		// Clear Window 
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 특정 색(빨강)으로 지우기
		glClear(GL_COLOR_BUFFER_BIT); // 색 버퍼를 특정 색(빨강)으로 지우기

	}

	return 0;
}