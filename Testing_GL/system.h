#include "glm/glm.hpp"


template <class T>
static T* CreateObjectComponent()
{
	return new T;
}

bool keys[1024];
bool first_Mouse = true;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

struct Last_MousePos
{
    GLfloat x = WINDOW_WIDTH / 2.0;
    GLfloat y = WINDOW_HEIGHT / 2.0;
}lastMPOS;

bool bCursorInWindow = false;
bool bActivateInCursor = false;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};