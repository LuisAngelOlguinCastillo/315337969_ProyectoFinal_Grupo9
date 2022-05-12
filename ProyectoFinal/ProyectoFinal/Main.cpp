#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacionP();
void animacionT();
void animacionC();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(5.6f, 3.2f, -5.7f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot;
float rotT;
float rotTM;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIniAD(-30.501f, 11.757f, 0.0f);
glm::vec3 PosIniAI(-30.0f, 12.0f, 0.0f);
glm::vec3 PosIniPC(-30.501f, 11.757f, 0.0f);
glm::vec3 PosIniP(-30.501f, 11.757f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

glm::vec3 LightP1;

//Animación del coche
float movKitX;
float movKitZ;
float movKitY;
float rotKit;
float movKitXT;
float movKitZT;
float rotKitT;
float movKitXC;
float movKitZC;
float rotKitC;
float movKitYS;
float movKitYL;
float movKitYA;
float movKitXP;
float golpe;

int tiempo = 0;

bool anim = false;
bool anim2 = true;
bool anim3 = false;
bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool golp = false;

bool anim4 = false;
bool anim5 = true;
bool anim6 = false;
bool anim7 = false;
bool anim8 = true;
bool anim9 = false;
bool circuito2 = false;
bool recorrido7 = true;
bool recorrido8 = false;
bool recorrido9 = false;
bool recorrido10 = false;
bool tiradoA1 = false;
bool tiradoA2 = false;
bool tiradoA3 = false;
bool tiradoA4 = false;
bool tiradoA5 = false;

bool circuito3 = false;
bool recorrido11 = true;
bool recorrido12 = false;
bool recorrido13 = false;
bool recorrido14 = false;

bool anim10 = false;
bool anim11 = true;
bool anim12 = true;
bool anim13 = false;
bool anim14 = true;
bool anim15 = true;

bool anim16 = false;
bool anim17 = false;
bool anim18 = true;
// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	// Load textures
	Model Exterior((char*)"Models/Exterior/Exterior.obj");
	Model Interior((char*)"Models/Interior/Interior.obj");
	Model Puerta((char*)"Models/Interior/PuertaCentral.obj");
	Model Piso((char*)"Models/Exterior/Piso.obj");
	Model Sol((char*)"Models/Exterior/Sol.obj");
	Model Luna((char*)"Models/Exterior/Luna.obj");
	Model Atardecer((char*)"Models/Exterior/Atardecer.obj");
	Model Arboles((char*)"Models/Exterior/Arboles.obj");
	Model ArbolTirado((char*)"Models/Exterior/ArbolG.obj");
	Model Carroseria((char*)"Models/Exterior/Carro/Carroseria.obj");
	Model Llanta1((char*)"Models/Exterior/Carro/Llanta1.obj");
	Model Llanta2((char*)"Models/Exterior/Carro/Llanta2.obj");
	Model Cola((char*)"Models/Exterior/Trex/Cola.obj");
	Model Cuerpo((char*)"Models/Exterior/Trex/Cuerpo.obj");
	Model GarraDer((char*)"Models/Exterior/Trex/GarraDer.obj");
	Model GarraIzq((char*)"Models/Exterior/Trex/GarraIzq.obj");
	Model Mandibula((char*)"Models/Exterior/Trex/Mandibula.obj");
	Model PataDer((char*)"Models/Exterior/Trex/PataDer.obj");
	Model PataIzq((char*)"Models/Exterior/Trex/PataIzq.obj");
	Model CabezaP((char*)"Models/Exterior/Pterodactilo/Cabezas.obj");
	Model CuerpoP((char*)"Models/Exterior/Pterodactilo/Cuerpo.obj");
	Model AlaDer((char*)"Models/Exterior/Pterodactilo/AlaDer.obj");
	Model AlaIzq((char*)"Models/Exterior/Pterodactilo/AlaIzq.obj");
	// Build and compile our shader program

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};

	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Load textures
	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);

	int textureWidth, textureHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map
	image = stbi_load("images/TexturesCom_GravelCobble0019_7_S.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	// Specular map
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image = stbi_load("images/piso.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window)){

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacionP();
		animacionT();
		animacionC();

		// Clear the colorbuffer
		glClearColor(0.5f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// /*Bind diffuse map*/
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture1);

		// /*Bind specular map*/
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);


		glBindVertexArray(VAO);
		glm::mat4 model(1);

		//Carga de modelo 
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//Edificio
		Exterior.Draw(lightingShader);
		Interior.Draw(lightingShader);
		
		//Pasto en el que estaran los modelos
		Piso.Draw(lightingShader);

		//Arboles inamobibles
		Arboles.Draw(lightingShader);
		
		//Puerta del traje
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXP, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta.Draw(lightingShader);

		//Sol
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0, movKitYS, 0));
		model = glm::translate(model, glm::vec3(0.0f, 20.0f, -80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sol.Draw(lightingShader);
		
		//Luna
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0, movKitYL, 0));
		model = glm::translate(model, glm::vec3(0.0f, -20.0f, -80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Luna.Draw(lightingShader);

		//Arboles que se van a caer
		// Arbol 1
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-31.908f, 0.006f, 24.037f));
		if(tiradoA1)
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ArbolTirado.Draw(lightingShader);
		// Arbol 2
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-19.256f, 0.0f, 0.389f));
		if(tiradoA2)
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ArbolTirado.Draw(lightingShader);
		// Arbol 3
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-31.7f, 0.0f, -20.102f));
		if (tiradoA3)
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ArbolTirado.Draw(lightingShader);
		// Arbol 4
		 view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-19.267f, 0.0f, -39.63f));
		if (tiradoA4)
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ArbolTirado.Draw(lightingShader);
		// Arbol 5
		 view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 33.905f));
		if (tiradoA5)
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ArbolTirado.Draw(lightingShader);

		//Auto
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXC, 0, movKitZC));
		model = glm::rotate(model, glm::radians(rotKitC), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-26.68f, 0.038f, 21.029f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Carroseria.Draw(lightingShader);
		//Llanta Derecha Adelante
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXC, 0, movKitZC));
		model = glm::rotate(model, glm::radians(rotKitC), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-25.314f, 0.538f, 18.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Llanta2.Draw(lightingShader);
		//Llanta Derecha Atras
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXC, 0, movKitZC));
		model = glm::rotate(model, glm::radians(rotKitC), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-25.314f, 0.538f, 23.34f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Llanta2.Draw(lightingShader);
		//Llanta Izquierda Adelante
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXC, 0, movKitZC));
		model = glm::rotate(model, glm::radians(rotKitC), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-28.066f, 0.538f, 18.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Llanta1.Draw(lightingShader);
		//Llanta Izquierda Atras
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXC, 0, movKitZC));
		model = glm::rotate(model, glm::radians(rotKitC), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-28.066f, 0.538f, 23.34f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Llanta1.Draw(lightingShader);
		
		//Cola T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-26.376f, 4.478f, 38.598f));
		model = glm::rotate(model, glm::radians(rotT), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cola.Draw(lightingShader);
		//Cuerpo T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-26.152f, 7.0f, 34.672f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo.Draw(lightingShader);
		//Garra Derecha T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-25.5f, 6.915f, 31.211f));
		model = glm::rotate(model, glm::radians(rotT), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GarraDer.Draw(lightingShader);
		//Garra Izquierda T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-27.0f, 6.915, 31.311f));
		model = glm::rotate(model, glm::radians(-rotT), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GarraIzq.Draw(lightingShader);
		//Mandibula T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-26.3f, 9.476f, 29.0f));
		model = glm::rotate(model, glm::radians(rotTM), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mandibula.Draw(lightingShader);
		//Pata Derecha T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-25.2f, 6.5f, 35.0f));
		model = glm::rotate(model, glm::radians(rotT), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PataDer.Draw(lightingShader);
		//Pata Izquierda T-Rex
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitXT, 0, movKitZT));
		model = glm::rotate(model, glm::radians(rotKitT), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-27.3f, 6.255f, 35.0f));
		model = glm::rotate(model, glm::radians(-rotT), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PataIzq.Draw(lightingShader);

		//Cabeza del Pterodactilo
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-30.501f, 11.757f, 0.0f));
		if (golp) {
			model = glm::rotate(model, glm::radians(golpe), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0, 0, movKitY));
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CabezaP.Draw(lightingShader);
		//Cuerpo del Pterodactilo
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-30.501f, 11.757f, 0.0f));
		if (golp) {
			model = glm::rotate(model, glm::radians(golpe), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0, 0, movKitY));
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoP.Draw(lightingShader);
		//Ala Derecha
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-30.501f, 12.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
		if (golp) {
			model = glm::rotate(model, glm::radians(golpe), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0, 0, movKitY));
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		AlaDer.Draw(lightingShader);
		//Ala Izquierda
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-30.501f, 12.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, 0.0f, 1.0f));
		if (golp) {
			model = glm::rotate(model, glm::radians(golpe), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0, 0, movKitY));
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		AlaIzq.Draw(lightingShader);

		glBindVertexArray(0);

		circuito = true;

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++){
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement(){

	if (keys[GLFW_KEY_1]){
		range += 0.1;
		rot += 1;
		printf("El rango es %f\n", range);
	}

	if (keys[GLFW_KEY_2]){
		range -= 0.1;
		printf("El rango es %f\n", range);
	}

	if (keys[GLFW_KEY_3]){
		range += 0.1;
		printf("El spotangle es %f\n", range);
	}

	if (keys[GLFW_KEY_4]){
		range -= 0.1;
		printf("El spotangle es %f\n", range);
	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]){
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]){
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]){
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]){
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T]){
		pointLightPositions[0].z += 0.1f;
	}
	
	if (keys[GLFW_KEY_G]){
		pointLightPositions[0].z -= 0.1f;
	}

	if (keys[GLFW_KEY_Y]){
		pointLightPositions[1].x += 0.1f;
		pointLightPositions[1].y += 0.1f;
		pointLightPositions[1].z += 0.1f;
	}

	if (keys[GLFW_KEY_H]){
		anim17 = true;
		anim16 = false;
	}
	
	if (keys[GLFW_KEY_U]){
		anim16 = true;
		anim17 = false;
	}
	
	if (keys[GLFW_KEY_J]){
		anim13 = true;
		anim10 = false;
	}
	
	if (keys[GLFW_KEY_I]){
		circuito2 = true;
		circuito3 = true;
		anim4 = true;
		anim7 = true;

	}

	if (keys[GLFW_KEY_O]){
		circuito2 = false;
		circuito3 = false;
		anim4 = false;
		anim7 = false;
	}
	
	if (keys[GLFW_KEY_K]){
		anim10 = true;	
		anim13 = false;
	}
	//Movimiento de las alas del Pterodactilo
	if (anim){
		if (anim2){
			rot += 0.5f;
			if (rot > 45.0f){
				anim2 = false;
				anim3 = true;
			}
		}

		if (anim3){
			rot -= 0.5f;
			if (rot < -45.0f){
				anim3 = false;
				anim2 = true;
			}
		}
	}
	//Movimiento de los brazos, piernas y cola del T-Rex
	if (anim4){
		if (anim5){
			rotT += 0.5f;
			if (rotT > 35.0f){
				anim5 = false;
				anim6 = true;
			}
		}

		if (anim6){
			rotT -= 0.5f;
			if (rotT < -35.0f){
				anim6 = false;
				anim5 = true;
			}
		}
	}
	//Movimiento de Madibula del T-Rex
	if (anim7) {
		if (anim8) {
			rotTM += 0.2;
			if (rotTM > 10.0f) {
				anim8 = false;
				anim9 = true;
			}
		}

		if (anim9) {
			rotTM -= 0.2;
			if (rotTM < -10.0f) {
				anim9 = false;
				anim8 = true;
			}
		}
	}
	//Cambio entre el sol y la luna
	if (anim10) {
		if (anim11) {
			movKitYS -= 0.5;
			if (movKitYS < -40.0f) {
				anim11 = false;
			}
		}

		if (anim12) {
			movKitYL += 0.5;
			if (movKitYL > 40.0f) {
				anim12 = false;
			}
		}
	}
	//Cambio entre la luna y el sol
	if (anim13) {
		if (anim14) {
			movKitYS += 0.5;
			if (movKitYS > 20.0f) {
				anim14 = false;
			}
		}

		if (anim15) {
			movKitYL -= 0.5;
			if (movKitYL < -40.0f) {
				anim15 = false;
			}
		}
	}

	if (anim16) {
		while (movKitXP > 7.6f) {
			movKitXP += 0.5;
			if (movKitXP > 7.6f)
				anim16 = false;
		}
	}

	if (anim17) {
		while (movKitXP < 5.9f) {
			movKitXP -= 0.5;
			if (movKitXP < 5.9f) {
				anim17 = false;
			}
		}
	}
}

void animacionP(){
	//Movimiento del Pterodactilo
	if (circuito){
		if (recorrido1){
			anim = true;
			movKitZ -= 0.1f;
			if (movKitZ < -20){
				movKitX = -20;
				movKitZ = 10;
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2){
			rotKit = -90;
			movKitX += 0.1f;
			if (movKitX > 30){
				movKitZ = -10;
				movKitX = 0;
				recorrido2 = false;
				recorrido3 = true;
			}
		}

		if (recorrido3){
			rotKit = 180;
			movKitZ += 0.1f;
			if (movKitZ > -6){
				movKitX = 30;
				movKitZ = -40;
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4){
			rotKit = 90;
			movKitX -= 0.1f;
			if (movKitX < 17){
				movKitZ = -40;
				movKitX = 15;
				movKitY = 0;
				recorrido4 = false;
				recorrido5 = true;
			}
		}

		if (recorrido5) {
			anim = false;
			golp = true;
			golpe = 90;
			movKitY += 0.1f;
			if (movKitY > 13) {
				golp = false;
				rotKit = 0;
				movKitX = 10;
				movKitZ = 20;
				recorrido5 = false;
				recorrido1 = true;
			}
		}
	}
}

void animacionT(){
	//Movimiento del T-Rex
	if (circuito2){
		if (recorrido7){
			movKitZT -= 0.05f;
			if (movKitZT < -10)
				tiradoA1 = true;
			if (movKitZT < -50.1)
				tiradoA3 = true;
			if (movKitZT < -60) {
				movKitXT = 5;
				movKitZT = -5;
				recorrido7 = false;
				recorrido8 = true;
			}
		}

		if (recorrido8){
			rotKitT = -90;
			movKitXT += 0.1f;
			if (movKitXT > 7)
				tiradoA4 = true;
			if (movKitXT > 15) {
				movKitZT = 0;
				movKitXT = -40;
				recorrido8 = false;
				recorrido9 = true;
			}
		}

		if (recorrido9) {
			rotKitT = 180;
			movKitZT += 0.1f;
			if (movKitZT > 32.3)
				tiradoA2 = true;
			if (movKitZT > 61)
				tiradoA5 = true;
			if (movKitZT > 70) {
				movKitXT = -45;
				movKitZT = 10;
				recorrido9 = false;
				recorrido10 = true;
			}
		}

		if (recorrido10) {
			rotKitT = 90;
			movKitXT -= 0.1f;
			if (movKitXT < -45) {
				rotKitT = 0;
				movKitXT = 0;
				movKitZT = 0;
				recorrido10 = false;
				recorrido7 = true;
			}
		}
	}
}

void animacionC() {
	//Movimiento del T-Rex
	if (circuito3) {
		if (recorrido11) {
			movKitZC -= 0.05f;
			if (movKitZC < -50) {
				movKitXC = 0;
				movKitZC = -5;
				recorrido11 = false;
				recorrido12 = true;
			}
		}

		if (recorrido12) {
			rotKitC = -90;
			movKitXC += 0.1f;
			if (movKitXC > 5) {
				movKitZC = 0;
				movKitXC = -40;
				recorrido12 = false;
				recorrido13 = true;
			}
		}

		if (recorrido13) {
			rotKitC = 180;
			movKitZC += 0.1f;
			if (movKitZC > 60) {
				movKitXC = -40;
				movKitZC = 10;
				recorrido13 = false;
				recorrido14 = true;
			}
		}

		if (recorrido14) {
			rotKitC = 90;
			movKitXC -= 0.1f;
			if (movKitXC < -50) {
				rotKitC = 0;
				movKitXC = 0;
				movKitZC = 0;
				recorrido14 = false;
				recorrido11 = true;
			}
		}
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024){
		if (action == GLFW_PRESS){
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE){
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE]){
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	if (keys[GLFW_KEY_N]){
		
	}

	if (keys[GLFW_KEY_M]){
		
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse){
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}