#include "Engine/Includes/GameEngine.h"
#include "Engine/Includes/FlyCam.h"

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
		"Base Shader", "vertex_core.glsl", "fragment_core.glsl", nullptr, false,
		"UI Shader", "vertex_ui.glsl", "fragment_ui.glsl", nullptr, true,
		"Text Shader", "vertex_ui.glsl", "fragment_text.glsl", nullptr, true
	};
	int shader_array_size = sizeof(shader_list) / sizeof(ShaderData);

	GameEngine::initializeEngine(window_name, window_width, window_height, shader_list, shader_array_size);
}

void runGame()
{
	Shader* shader = Shader::Find("Base Shader");

	GameObject* camera = Camera::getMain()->getGameObject();
	FlyCam* camera_controller = new FlyCam(camera, 5.0f, 10.0f);

	GameObject* sphere = GameEngine::createGameObject("Sphere", glm::vec3(-1.0f, 0.0f, -2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	Material* sphere_material = new Material(shader, glm::vec3(1.0f, 0.5f, 0.5f));
	sphere_material->setInt("lit", 0);
	sphere_material->setInt("use_emissive", 1);
	sphere_material->setFloat("emissive_intensity", 2.0f);
	sphere_material->setVector3("emissive_color", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh* sphere_mesh = OBJLoader::loadObj("Meshes/Sphere.obj", false);
	MeshRenderer* sphere_renderer = new MeshRenderer(sphere, sphere_mesh, sphere_material);

	GameObject* quad = GameEngine::createGameObject("Quad", glm::vec3(-1.0f, -2.0f, -2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	Texture* quad_texture = new Texture("Images/Numbers/One.png", 0);
	Material* quad_material = new Material(shader, glm::vec3(0.0f, 0.5f, 0.5f), quad_texture);
	Mesh* quad_mesh = OBJLoader::loadObj("Meshes/Quad.obj", false);
	MeshRenderer* quad_renderer = new MeshRenderer(quad, quad_mesh, quad_material);

	GameObject* object = GameEngine::createGameObject("Oui", glm::vec3(1.0f, 0.0f, -2.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	Texture* texture = new Texture("Images/Card.png", 0);
	Material* material = new Material(shader, glm::vec3(1.0f, 1.0f, 1.0f), texture);
	Mesh* voxmon = OBJLoader::loadObj("Meshes/Card.obj", false);
	MeshRenderer* renderer = new MeshRenderer(object, voxmon, material);

	GameObject* ui_text = GameEngine::createUiElement("ui_text", glm::vec2(0.0f, 0.0f), 45.0f, glm::vec2(1.0f, 1.0f));
	Shader* text_shader = Shader::Find("Text Shader");
	Material* text_material = new Material(text_shader, glm::vec3(1.0f, 1.0f, 1.0f));
	TextRenderer* text = new TextRenderer(ui_text, text_material, "Bonjour");

	while (!GameEngine::getInstance()->shouldClose())
	{
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