#include "Main.h"
#include "HelloWindow.h"
#include "HelloShaders.h"
#include "HelloTextures.h"
#include "HelloTransformation.h"
#include "HelloCoordinates.h"
#include "HelloCamera.h"

int main()
{
	/*if (helloWindow() == 1)
		exit(EXIT_FAILURE);*/

	/*if (helloShaders() == 1)
		exit(EXIT_FAILURE);*/

	/*if (helloTextures() == 1)
		exit(EXIT_FAILURE);*/

	/*if (helloTransformation() == 1)
		exit(EXIT_FAILURE);*/

	/*if (helloCoordinates() == 1)
		exit(EXIT_FAILURE);*/

	if (helloCamera() == 1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}