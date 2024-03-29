#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Main.h"
#include "HelloWindow.h"

#include <iostream>

// Vertex shader source code
const char *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

// Fragment shader source code
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";


int helloWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); ONLY FOR MAC

	// Attempt to create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "YEET", NULL, NULL);
	if (window == NULL) {
	std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Attempt to init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Create and attempt to compile vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for shader compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED::\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Vertex Shader Initialised!!" << std::endl;
	}

	// Create and compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for fragment shader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Fragment Shader Initialised!!" << std::endl;
	};

	// Create shader program and link both shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check if linked
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK::FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Shaders Linked!!" << std::endl;
	};

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Triangle
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f, 0.5f, 0.0f
	//};

	// Rectangle (two triangles)
	//float vertices[] = {
	//	0.5f,  0.5f, 0.0f,  // top right
	//	0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left 
	//};
	//unsigned int indices[] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3 // second triangle
	//};

	float vertices[] = {
		// first triangle
		-0.45f, -0.25f, 0.0f,  // left 
		-0.0f, -0.25f, 0.0f,  // right
		-0.225f, 0.25f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.25f, 0.0f,  // left
		 0.45f, -0.25f, 0.0f,  // right
		 0.225f, 0.25f, 0.0f,   // top
		// third triangle
		-0.225f, 0.25f, 0.0f,
		0.225f, 0.25f, 0.0f,
		0.0f, 0.75f, 0.0f

	};

	unsigned int VBO; // vertex buffer object
	unsigned int VAO; // vertex array object

	// For rectangles
	//unsigned int EBO;

	// Gen buffers and arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//For rectangles
	//glGenBuffers(1, &EBO);

	// Bind buffers and arrays, bind VAO FIRST, then VBO, then EBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//For rectangles
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Uncomment to draw in wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	 
	// RENDER LOOP, render the window as dark turquoise
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();

		// default color
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClearColor(0.68f, 0.36f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// For triangles
		glDrawArrays(GL_TRIANGLES, 0, 9);

		// For rectangles
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glfwTerminate();
	return 0;
}