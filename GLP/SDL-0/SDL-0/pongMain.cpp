#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <fstream>
#include <string>
using namespace std;
//#define GLEW_STATIC

string LoadShader(string fileName) {
	ifstream myFile;
	myFile.open(fileName);
	if (myFile.fail()) {
		cerr << "Error - failed to open " << fileName << endl;
	}
	string fileText = "";
	string line = "";
	while (getline(myFile, line)) {
		fileText += line + '\n';
	}

	myFile.close();
	return fileText;
}

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	int width = 800;
	int height = 400;
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !


	//Create an OpenGL compatible context to let glew draw on it
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0, 0, width, height);

	//Put the color you want here for the background
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	//Use depth management
	glEnable(GL_DEPTH_TEST);

	//0 is our origin, the higher the z, the farther the object
	glDepthFunc(GL_LESS);

	float paddleLvertices[]={
		-0.85f,0.2f,0.0f,
		-0.8f,0.2f,0.0f,
		-0.85f,-0.2f,0.0f,
		-0.8f,-0.2f,0.0f,
	};

	float paddleRvertices[] = {
		0.8f,0.2f,0.0f,
		0.85f,0.2f,0.0f,
		0.8f,-0.2f,0.0f,
		0.85f,-0.2f,0.0f,
	};

	float fieldVertices[] = {
		-1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		-1.0f,0.9f,0.0f,
		1.0f,0.9f,0.0f,

		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		-1.0f,-0.9f,0.0f,
		1.0f,-0.9f,0.0f,

		-0.025f,0.75f,0.0f,
		0.025f,0.75f,0.0f,
		-0.025f,0.45f,0.0f,
		0.025f,0.45f,0.0f,

		-0.025f,0.15f,0.0f,
		0.025f,0.15f,0.0f,
		-0.025f,-0.15f,0.0f,
		0.025f,-0.15f,0.0f,

		-0.025f,-0.75f,0.0f,
		0.025f,-0.75f,0.0f,
		-0.025f,-0.45f,0.0f,
		0.025f,-0.45f,0.0f,
	};

	float ballVertices[] = {
		-0.425f,0.05f,0.0f,
		-0.375f,0.05f,0.0f,
		-0.425f,-0.05f,0.0f,
		-0.375f,-0.05f,0.0f,
	};

	unsigned int vbo;
	string vs = LoadShader("foxVertex.shader");
	const char* vertexShaderSource = vs.c_str();
	string fs = LoadShader("foxFragment.shader");
	const char* fragmentShaderSource = fs.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	unsigned int vaoL;
	glGenVertexArrays(1, &vaoL);
	glBindVertexArray(vaoL);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(paddleLvertices), paddleLvertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vaoR;
	glGenVertexArrays(1, &vaoR);
	glBindVertexArray(vaoR);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(paddleRvertices), paddleRvertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vaoF;
	glGenVertexArrays(1, &vaoF);
	glBindVertexArray(vaoF);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fieldVertices), fieldVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vaoB;
	glGenVertexArrays(1, &vaoB);
	glBindVertexArray(vaoB);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ballVertices), ballVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	float paddleLpos = 0.2f;
	float paddleRpos = 0.2f;
	float ballXpos = 0.25f;
	float ballYpos = 0.5f;

	bool isRunning = true;
	while (isRunning) {

		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}

		if (ballXpos <= -0.8f) {
			if (paddleLpos >= ballYpos && paddleLpos - 0.4f <= ballYpos) {
				//bounce right
			}
			else; //score
			
		}
		if (ballXpos >= 0.75f) {
			if (paddleRpos >= ballYpos && paddleRpos - 0.4f <= ballYpos) {
				//bounce left
			}
			else; //score
		}
		if (ballYpos <= -0.85f) {
			//bounce up
		}
		if (ballYpos >= 0.9f) {
			//bounce down
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shaderProgram);

		glBindVertexArray(vaoL);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(vaoR);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(vaoB);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(vaoF);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);


		SDL_GL_SwapWindow(Window); // Swapbuffer
	}
	// Quit
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);


	cin.get();
	return 0;
}