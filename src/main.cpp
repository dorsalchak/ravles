#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow *pWindow);
void framebuffer_size_callback(GLFWwindow *pWindow, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Name", nullptr, nullptr);

	if (!pWindow)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(pWindow);
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

	if (!gladLoadGL())
	{
		std::cout << "Glad failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "VERTEX SHADER COMPILE FAILED" << std::endl;
		}
	}
	//проверка вершинного шейдера

	

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	{
		int success1;
		char infoLog1[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success1);

		if (!success1)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog1);
			std::cout << "FRAGMENT SHADER COMPILE FAILED" << std::endl;
		}
	}
	//проверка фрагментного шейдера

	//Создание шейдерной программы и объединение шейдеров
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	{
	int success2;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success2);

	if (!success2)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "SHADER PROGRAM FAILED" << std::endl;
	}
	}
	// проверка шейдерной программый
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float firstTriangle[] =
	{
		-0.5f, -0.5f, 0.0f,   //
		 0.0f, -0.5f, 0.0f,   //
		-0.25f, 0.0f, 0.0f,   
	};
	float secondTriangle[] =
	{
		0.5f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.25f, 0.0f, 0.0f,
	};
	
	/*unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};*/

	
	unsigned int VBOs[2], VAOs[2];

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	//Первый треугольник
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
	glEnableVertexAttribArray(0);

	//втоорой тругольник
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//----------------------------------------------------
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); отрисовка только линий треугольников, каркас

	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		/*glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);*/

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *pWindow)
{
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, true);
}
void framebuffer_size_callback(GLFWwindow *pWindow, int width, int height)
{
	glViewport(0, 0, width, height);
}
