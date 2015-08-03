#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include <iostream>
#include <GL/glew.h>

static const int DISPLAY_WIDTH = 1000;
static const int DISPLAY_HEIGHT = 500;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(0.5, 1.0)),
	};

	unsigned int indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("res/monkey3.obj");
	Shader shader("res/basicShader");
	Texture texture("res/fur.jpg");
	Camera camera(glm::vec3(0, 0, -150.0), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.01f, 1000.0f); 
	Transform transform;

	float counter = 0.0f;

	while (!display.IsClosed()){
		
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		float sinCounter = sinf(counter);
		float cosCounter = cosf(5*counter);

		transform.GetPos().x = 0.5*sinCounter;
		transform.GetPos().z = 0.5*cosCounter;
		//transform.GetRot().z = counter;
		transform.GetRot().z = 1* counter;
		transform.GetRot().y = 5* counter;
		transform.GetRot().x = 3* counter;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		transform.GetScale() *= (1+0.001*cosf(counter));
		
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();

		display.Update();
		counter += 0.001f;
	}

	return 0;
}
