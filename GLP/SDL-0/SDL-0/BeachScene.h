#pragma once
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include <Matrix4.h>

class BeachScene : public Scene{
private:
	Texture2D m_sandTexture;
	Shader m_sandVertex,m_sandFragment,m_sandTessControl,m_sandTessEval,m_waterVertex,m_waterFragment,m_waterTessControl,m_waterTessEval,m_waterGeometry;
	ShaderProgram m_sandProgram, m_waterProgram;
	unsigned int m_vao2,m_vbo2;
	virtual void LoadShaders();
	virtual void CreateShaderPrograms();
	virtual void VerticeInformationSlicer();

	// Uniforms
	Matrix4 mvp;
	Matrix4 view;
	Matrix4 proj;
	float dmapDepth;
	bool isFogEnabled;

	GLuint texDisplacement,waterTexDisplacement;
	GLuint texColor;
	bool isDisplacementEnabled;
	bool wireframe;
	bool paused;

	float totalTime;
	float t, r, h;
	
public:
	BeachScene();
	~BeachScene();
	virtual void SetupScene();
	virtual void UpdateScene();
	void HandleInputs(SDL_Event& e) override;
};