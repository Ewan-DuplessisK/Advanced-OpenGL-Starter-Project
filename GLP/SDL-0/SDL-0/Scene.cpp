#include "Scene.h"
#include <SDL.h>
#include "glew.h"

Scene::Scene(std::string nameP) {
	m_name = nameP;
	LastTick = (float)SDL_GetTicks()/1000;
	glGenBuffers(1, &m_vbo);
}

Scene::~Scene(){
	glDeleteVertexArrays(1, &m_vao); 
}