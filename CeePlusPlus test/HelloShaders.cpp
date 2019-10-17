#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Main.h"
#include "HelloShaders.h"
#include "shader.h"

#include <iostream>

//// Vertex shader source code
//const char *helloVertexShaderSource = "#version 330 core\n"
//"layout(location = 0) in vec3 aPos;\n"
//"layout(location = 1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos, 1.0);\n"
//"ourColor = aColor;\n"
//"}\n";
//
//// Fragment shader source code
//const char *helloFragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"FragColor = vec4(ourColor, 1.0f);\n"
//"}\n";


int helloShaders() {
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
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//glShaderSource(vertexShader, 1, &helloVertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//// Check for shader compilation errors
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED::\n" << infoLog << std::endl;
	//}
	//else {
	//	std::cout << "Vertex Shader Initialised!!" << std::endl;
	//}

	// Create and compile fragment shader
	/*unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &helloFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);*/

	// Check for fragment shader compilation errors
	/*glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Fragment Shader Initialised!!" << std::endl;
	};*/

	// Create shader program and link both shaders
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//// Check if linked
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::LINK::FAILED\n" << infoLog << std::endl;
	//}
	//else {
	//	std::cout << "Shaders Linked!!" << std::endl;
	//};

	//glUseProgram(shaderProgram);

	/*glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);*/

	Shader ourShader("vertshader.vert", "fragshader.frag");

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int VBO; // vertex buffer object
	unsigned int VAO; // vertex array object

	// Gen buffers and arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind buffers and arrays, bind VAO FIRST, then VBO, then EBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Uncomment to draw in wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// RENDER LOOP, render the window as dark turquoise
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.68f, 0.36f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		//glUseProgram(shaderProgram);

		// Update shader uniform
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		// Draw our triangle
		ourShader.use();
		ourShader.setFloat("someUniform", 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glfwTerminate();
	return 0;
}