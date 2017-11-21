// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include "../../../glm/glm/glm.hpp"
#include <../../../glm/glm/gtc/matrix_transform.hpp>
#include <../../../glm/glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include <iostream>
#include <stdio.h> 
#include <direct.h>
#include <string>


//linker-imput
//glfw3.lib;opengl32.lib;glew32s.lib;SOIL.lib;assimp-vc140-mt.lib
/*
include
D:\project\OpenglFiles\glfw-3.2.1\include\
d:\project\OpenglFiles\glew-2.0.0\include\
D:\project\OpenglFiles\project_vs\Simple OpenGL Image Library\src\
d:\project\OpenglFiles\project_vs\assimp\include
//D:\project\OpenglFiles\glfw-3.2.1\include\;d:\project\OpenglFiles\glew-2.0.0\include\;D:\project\OpenglFiles\project_vs\Simple OpenGL Image Library\src\;d:\project\OpenglFiles\project_vs\assimp\include
library
D:\project\OpenglFiles\glfw-3.2.1\build_vs\src\Debug\
d:\project\OpenglFiles\glew-2.0.0\lib\Release\Win32\
D:\project\OpenglFiles\project_vs\Simple OpenGL Image Library\lib\
d:\project\OpenglFiles\project_vs\assimp\lib
//D:\project\OpenglFiles\glfw-3.2.1\build_vs\src\Debug\;d:\project\OpenglFiles\glew-2.0.0\lib\Release\Win32\;D:\project\OpenglFiles\project_vs\Simple OpenGL Image Library\lib\;d:\project\OpenglFiles\project_vs\assimp\lib
source directories
D:\project\OpenglFiles\glfw-3.2.1\include\;d:\project\OpenglFiles\glew-2.0.0\include\GL;D:\project\OpenglFiles\project_vs\Simple OpenGL Image Library\src\;d:\project\OpenglFiles\project_vs\assimp\include
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 000.0f, 1000.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar system", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}*/

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	// build and compile shaders
	// ------------F-------------
	Shader shaderOrb("model.v", "model.f");
	Shader shaderPlanets("modelTex.v", "modelTex.f");

	// load models
	// -----------


	char current_work_dir[FILENAME_MAX];
	char b = *"\\";
	_getcwd(current_work_dir, sizeof(current_work_dir));
	for (int i = 0; i < sizeof(current_work_dir); i++) {
		if (current_work_dir[i] == b)
			current_work_dir[i] = '/';
	}
	string path = current_work_dir;
	Model modelFone( path + "/model/foneCube/foneCube.obj");
	Model modelOrb(path + "/model/orbits/orbits.obj");
	Model modelSun(path + "/model/sun/sun.obj");
	Model modelMercur(path + "/model/mercury/mercury.obj");
	Model modelVenera(path + "/model/venera/venera.obj");
	Model modelTerra(path + "/model/terra/terra.obj");
	Model modelMars(path + "/model/mars/mars.obj");
	Model modelYpiter(path + "/model/ypiter/ypiter.obj");
	Model modelSaturn(path + "/model/saturn/saturn.obj");
	Model modelYran(path + "/model/yran/yran.obj");
	Model modelNeptun(path + "/model/neptun/neptun.obj");
	Model modelMoon(path + "/model/moon/moon.obj");


	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	float time = (GLfloat)glfwGetTime();
	float timeMerc = 0;
	float timeVenera = 0;
	float timeTerra = 0;
	float timeMars = 0;
	float timeYpiter = 0;
	float timeSaturn = 0;
	float timeYran = 0;
	float timeNeptun = 0;
	float timeMoon = 0;

	while (!glfwWindowShouldClose(window))
	{
		
		//«адание скоростей вращени€ вокруг солнца
		timeMerc = timeMerc + 0.001;
		timeVenera = timeVenera + 0.000729;
		timeTerra = timeTerra + 0.0006;
		timeMars = timeMars + 0.0005;
		timeYpiter = timeYpiter + 0.00027;
		timeSaturn = timeSaturn + 0.0002;
		timeYran = timeYran + 0.000145;
		timeNeptun = timeNeptun + 0.0001;
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.00f, 0.00f, 0.00f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		shaderOrb.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 20000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shaderOrb.setMat4("projection", projection);
		shaderOrb.setMat4("view", view);

		// render the loaded model
		//glm::mat4 model;
		//model = glm::translate(model, glm::vec3(0.0f, -300.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::rotate(model, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		//ourShader.setMat4("model", model);
		//ourModel.Draw(ourShader);


		glm::mat4 model1;
		model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		//model1 = glm::rotate(model1, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		//model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shaderOrb.setMat4("model", model1);
		modelOrb.Draw(shaderOrb);
		//
		//planets------------------
		//
		shaderPlanets.use();

		//sun
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 sun;
		sun = glm::translate(sun, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		sun = glm::rotate(sun, (GLfloat)glfwGetTime()* 0.1f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", sun);
		modelSun.Draw(shaderPlanets);
		//mercur
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 mercur;
		float x, y;
		time = time + timeMerc;
		
		x = 50 * cos(time);
		y = 50 * sin(time);
		time = time - timeMerc;
		mercur = glm::translate(mercur, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		mercur = glm::rotate(mercur, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", mercur);
		modelMercur.Draw(shaderPlanets);
		//venera
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 venera;
		time = time + timeVenera;
		x = 110 * cos(time);
		y = 110 * sin(time);
		time = time - timeVenera;
		venera = glm::translate(venera, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		venera = glm::rotate(venera, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", venera);
		modelVenera.Draw(shaderPlanets);
		//Terra
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 terra;
		time = time + timeTerra;
		x = 200 * cos(time);
		y = 200 * sin(time);
		time = time - timeTerra;
		terra = glm::translate(terra, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		terra = glm::rotate(terra, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", terra);
		modelTerra.Draw(shaderPlanets);
		//Moon
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 moon;
		float a = x + 40 * cos(time);
		float b = y + 40 * sin(time);
		time = time + timeTerra + 0.01;
		  a = x + 40 * cos(time);
		  b = y + 40 * sin(time);
		time = time - timeTerra - 0.01;
		moon = glm::translate(moon, glm::vec3(a, b, 0.0f)); // translate it down so it's at the center of the scene
		moon = glm::rotate(moon, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", moon);
		modelMoon.Draw(shaderPlanets);
		
		
		
		//Mars
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 mars;
		time = time + timeMars;
		x = 290 * cos(time);
		y = 290 * sin(time);
		time = time - timeMars;
		mars = glm::translate(mars, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		mars = glm::rotate(mars, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", mars);
		modelMars.Draw(shaderPlanets);
		//Ypiter
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 ypiter;
		time = time + timeYpiter;
		x = 500 * cos(time);
		y = 500 * sin(time);
		time = time - timeYpiter;
		ypiter = glm::translate(ypiter, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		ypiter = glm::rotate(ypiter, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", ypiter);
		modelYpiter.Draw(shaderPlanets);
		//Saturn
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 Saturn;
		time = time + timeSaturn;
		x = 700 * cos(time);
		y = 700 * sin(time);
		time = time - timeSaturn;
		Saturn = glm::translate(Saturn, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		Saturn = glm::rotate(Saturn, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", Saturn);
		modelSaturn.Draw(shaderPlanets);
		//Yran
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 Yran;
		time = time + timeYran;
		x = 900 * cos(time);
		y = 900 * sin(time);
		time = time - timeYran;
		Yran = glm::translate(Yran, glm::vec3(x, y, 0.0f)); // translate it down so it's at the center of the scene
		Yran = glm::rotate(Yran, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", Yran);
		modelYran.Draw(shaderPlanets);
		//Neptun
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 Neptun;
		time = time + timeNeptun;
		x = 1100 * cos(time);
		y = 1100 * sin(time);
		time = time - timeNeptun;
		Neptun = glm::translate(Neptun, glm::vec3(x,y, 0.0f)); // translate it down so it's at the center of the scene
		Neptun = glm::rotate(Neptun, (GLfloat)glfwGetTime()* 0.5f, glm::vec3(0.0, 0.0, 1.0));
		shaderPlanets.setMat4("model", Neptun);
		modelNeptun.Draw(shaderPlanets);
		
		time = time + 0.001;
		//Fone
		//projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 6000.0f);
		//view = camera.GetViewMatrix();
		shaderPlanets.setMat4("projection", projection);
		shaderPlanets.setMat4("view", view);
		glm::mat4 fone;
		fone = glm::translate(fone, glm::vec3(0.0f, 0, 0.0f)); // translate it down so it's at the center of the scene
		fone = glm::rotate(fone, (GLfloat)glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
		shaderPlanets.setMat4("model", fone);
		modelFone.Draw(shaderPlanets);
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime+5);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime+5);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime+5);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime+5);
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
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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
	camera.ProcessMouseScroll(yoffset);
}