#include "../Engine/Includes/GameEngine.h"
#include "../Engine/Includes/FlyCam.h"
#include "../Card.h"
#include "../EffectAnimation.h"
#include "../GameManager.h"

/*
	Keywords :
	- include
	- function / method
	- public / private
	- guard
	- throw / exception
	- try / catch
	- pointer
	- SOLID principles
*/

void initializeEngine()
{
	const char* window_name = "Open GL Window";
	int window_width = 640;
	int window_height = 480;

	ShaderData shader_list[] = {
		"Base Shader", "Engine/GLSL/vertex_core.glsl", "Engine/GLSL/fragment_core.glsl", nullptr, false,
		"UI Shader", "Engine/GLSL/vertex_ui.glsl", "Engine/GLSL/fragment_ui.glsl", nullptr, true,
		"Text Shader", "Engine/GLSL/vertex_ui.glsl", "Engine/GLSL/fragment_text.glsl", nullptr, true
	};
	int shader_array_size = sizeof(shader_list) / sizeof(ShaderData);

	GameEngine::initializeEngine(window_name, window_width, window_height, shader_list, shader_array_size);
}

void runGame()
{
	GameObject* camera = Camera::getMain()->getGameObject();
	camera->getTransform()->setPosition(0.0f, 4.5f, 0.0f);
	camera->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);

	//FlyCam* camera_controller = new FlyCam(camera, 5.0f, 10.0f);

	GameManager::getInstance()->initialize();

	while (!GameEngine::getInstance()->shouldClose())
	{
		try
		{
			GameManager::getInstance()->gameLoop();
			GameEngine::getInstance()->update();
		}
		catch (const std::exception& e)
		{
			std::cerr << "ERROR: " << e.what() << "\n";
		}
	}

	GameEngine::getInstance()->exit();
}

void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* user_param)
{
	std::cout << message << "\n";
}

void enableDebugMode()
{
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(debugCallback, 0);
}

int main()
{
	initializeEngine();

	runGame();

	return 0;
}