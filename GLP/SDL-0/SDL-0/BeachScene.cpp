#include "BeachScene.h"

#include "Assets.h"
#include "Window.h"

using namespace std;

const bool ENABLE_GEOMETRY_SHADER = false;

BeachScene::BeachScene():dmapDepth(8.0f), isFogEnabled(true), isDisplacementEnabled(true),
	wireframe(false), paused(false), totalTime(0){}


void BeachScene::LoadShaders() {
	m_sandVertex.LoadFrom("terrainTessVertex.shader",VERTEX);
	m_sandFragment.LoadFrom("terrainTessFragment.shader",FRAGMENT);
	m_sandTessControl.LoadFrom("terrainTessControl.shader",TESSELLATION_CONTROL);
	m_sandTessEval.LoadFrom("sandTessEval.shader",TESSELLATION_EVALUATION);
	m_waterVertex.LoadFrom("terrainTessVertex.shader",VERTEX);
	m_waterFragment.LoadFrom("simpleFragment.shader",FRAGMENT);
	m_waterTessControl.LoadFrom("terrainTessControl.shader", TESSELLATION_CONTROL);
	m_waterTessEval.LoadFrom("waterTessEval.shader", TESSELLATION_EVALUATION);
	if(ENABLE_GEOMETRY_SHADER)m_waterGeometry.LoadFrom("", GEOMETRY);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void BeachScene::CreateShaderPrograms(){
	m_sandProgram.Compose(vector<Shader*>{&m_sandVertex,&m_sandFragment,&m_sandTessControl,&m_sandTessEval});
	m_waterProgram.Compose(vector<Shader*>{&m_waterVertex,&m_waterFragment,&m_waterTessControl,&m_waterTessEval,&m_waterGeometry});
}

void BeachScene::VerticeInformationSlicer(){}

void BeachScene::SetupScene(){
	LoadShaders();
	CreateShaderPrograms();

	//Create one ID to be given at object generation and store it in m_vao via reference
	glGenVertexArrays(1, &m_vao);
	//Binding the VAO 
	//   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
	glBindVertexArray(m_vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glPatchParameteri(GL_PATCH_VERTICES, 4);

	glEnable(GL_CULL_FACE);
	//TEXTURES
	glActiveTexture(GL_TEXTURE1);
	Assets::loadTexture("./Textures/sandDisp.png", "sandDisp");
	texDisplacement = Assets::getTexture("sandDisp").id;
	glBindTexture(GL_TEXTURE_2D, texDisplacement);

	glActiveTexture(GL_TEXTURE2);
	Assets::loadTexture("./Textures/sandColor.jpg", "sandColor");
	texColor = Assets::getTexture("sandColor").id;
	glBindTexture(GL_TEXTURE_2D, texColor);

	glActiveTexture(GL_TEXTURE3);
	Assets::loadTexture("./Textures/waterDisp.png", "waterDisp");
	waterTexDisplacement = Assets::getTexture("waterDisp").id;
	glBindTexture(GL_TEXTURE_2D, waterTexDisplacement);
}

void BeachScene::UpdateScene(){
	totalTime = (float)SDL_GetTicks() / 1000;
	t = totalTime * 0.03f;
	r = sinf(t * 5.37f) * 15.0f + 35.0f;
	h = cosf(t * 4.79f) * 2.0f + 15.f;
	static const GLfloat bgColor[] = { 0.0f, 0.0f, 0.2f, 1.0f };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, bgColor);
	glClearBufferfv(GL_DEPTH, 0, &one);

	view = Matrix4::createLookAt(Vector3(sinf(t) * r, h, cosf(t) * r), Vector3(0.0f,0.0f,0.0f), Vector3(0.0f, 1.0f, 0.0f));
	proj = Matrix4::createPerspectiveFOV(45.0f, Window::Dimension.x, Window::Dimension.y, 0.1f, 1000.0f);

	m_sandProgram.Use();
	m_sandProgram.setMatrix4("mv_matrix", view);
	m_sandProgram.setMatrix4("proj_matrix", proj);
	m_sandProgram.setMatrix4("mvp_matrix", proj * view);
	m_sandProgram.setFloat("dmap_depth", isDisplacementEnabled ? dmapDepth : 0.0f);
	m_sandProgram.setFloat("enable_fog", isFogEnabled ? 1.0f : 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);

	m_waterProgram.Use();
	m_waterProgram.setMatrix4("mv_matrix", view);
	m_waterProgram.setMatrix4("proj_matrix", proj);
	m_waterProgram.setMatrix4("mvp_matrix", proj * view);
	m_waterProgram.setFloat("dmap_depth", isDisplacementEnabled ? dmapDepth : 0.0f);
	m_waterProgram.setFloat("enable_fog", isFogEnabled ? 1.0f : 0.0f);
	m_waterProgram.setFloat("time",totalTime);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
}

void BeachScene::HandleInputs(SDL_Event& e){
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if(e.key.keysym.sym == SDLK_w)
		{
			//press W to switch with wireframe view
			wireframe = !wireframe;
		}
        
	}
}