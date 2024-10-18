#include "../Engine/Includes/GameEngine.h"
#include "../Engine/Includes/FlyCam.h"
#include "../Card.h"
#include "../EffectAnimation.h"

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
	FlyCam* camera_controller = new FlyCam(camera, 5.0f, 10.0f);

	GameObject* card = GameEngine::createGameObject("Card", glm::vec3(0.0f, -0.3f, 0.0f));
	Card* card_component = new Card(card, "CardComponent", 1, 5, "Images/Card.png");

	GameObject* target = GameEngine::createGameObject("Target", glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f));
	card_component->moveAndRotateTo(target, 10.0f);

	IAnimation* effect = new EffectAnimation();

	while (!GameEngine::getInstance()->shouldClose())
	{
		if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_1))
			effect->play(0);
		else if (GameEngine::getInstance()->isKeyPressed(GLFW_KEY_2))
			effect->play(1);

		try
		{
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