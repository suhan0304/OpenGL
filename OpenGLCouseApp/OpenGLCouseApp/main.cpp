#include <stdio.h>
#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// 창 크기
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

	glValidateProgram(shader); // 셰이더가 OpenGl 콘텍스트에서 유효한지 검사	
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW initialisation failed" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport Size - Viewport? 프레임 버퍼의 어떤 부분에 렌더링할지를 결정
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriagnle();
	CompileShaders();

	// Loop Until window Closed 
	while (!glfwWindowShouldClose(mainWindow)) // 윈도우 창이 닫힐 때까지 반복 
	{
		// Get + Handler user input events 
		glfwPollEvents(); // 클릭, 화면 이동, 리사이즈 등, 등 모든 이벤트를 감지

		// Clear Window 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 특정 색(빨강)으로 지우기
		glClear(GL_COLOR_BUFFER_BIT); // 색 버퍼를 특정 색(빨강)으로 지우기

		glUseProgram(shader); // 생성한 셰이더 ID를 잡음 (셰이더가 여러개 일 때 구별해서 잡는데 사용)
		// 여기에 작성되는 것은 위에서 잡은 셰이더 프로그램으로 그려짐

		glBindVertexArray(VAO); //VAO 바인드
		glDrawArrays(GL_TRIANGLES, 0, 3); // 0~3번째 점까지 사용해서 삼각형 그리기
		glBindVertexArray(0); // VAO 언바인드
		 
		glUseProgram(0); //잡은 셰이더를 해제

		// 화면에 보여지는 버퍼와 렌더링에 사용되는 버퍼를 교체
		glfwSwapBuffers(mainWindow); 

	}

	return 0;
}