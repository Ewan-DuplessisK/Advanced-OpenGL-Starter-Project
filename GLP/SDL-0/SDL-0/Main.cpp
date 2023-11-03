//#include <iostream>
//#include <SDL.h>
//#include <glew.h>
//#include <fstream>
//#include <string>
//using namespace std;
////#define GLEW_STATIC
//
//string LoadShader(string fileName) {
//	ifstream myFile;
//	myFile.open(fileName);
//	if (myFile.fail()) {
//		cerr << "Error - failed to open " << fileName << endl;
//	}
//	string fileText = "";
//	string line = "";
//	while (getline(myFile, line)) {
//		fileText += line + '\n';
//	}
//
//	myFile.close();
//	return fileText;
//}
//
//
//int main(int argc, char* argv[]){
//
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//	{
//		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
//	}
//	else
//	{
//		cout << "SDL initialization succeeded!\n";
//	}
//	///////////SETTING UP SDL/////////////
//	//Create a simple window
//	int width = 400;
//	int height = 400;
//	unsigned int center = SDL_WINDOWPOS_CENTERED;
//	SDL_Window* Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
//	//SDL_WINDOW_OPENGL is a u32 flag !
//
//
//	//Create an OpenGL compatible context to let glew draw on it
//	SDL_GLContext Context = SDL_GL_CreateContext(Window);
//
//	/////////SETTING UP OPENGL WITH GLEW///
//	//Initialize glew
//	glewExperimental = GL_TRUE;
//	if (glewInit() == GLEW_OK) {
//		cout << "Glew initialized successfully\n";
//	}
//
//	//Set the viewing frame through which we will see the objects
//	glViewport(0, 0, width, height);
//
//	//Put the color you want here for the background
//	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
//
//	//Use depth management
//	glEnable(GL_DEPTH_TEST);
//
//	//0 is our origin, the higher the z, the farther the object
//	glDepthFunc(GL_LESS);
//
//
//	//Describe the shape by its vertices
//
//	float vertices[] = {
//		// positions
//			 -0.5f, 1.0f, 0.0f,
//			-1.0f, 0.0f, 0.0f,
//			 0.0f,  -1.0f, 0.0f,
//			 1.0f, 0.0f, 0.0f,
//			 0.5f, 1.0f, 0.0f
//	};
//	float verticesColor[] = {
//		1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//	};
//
//
//	//Create an ID to be given at object generation
//	unsigned int vbo;
//
//
//	//Pass how many buffers should be created and the reference of the ID to get the value set
//	//glGenBuffers(1, &vbo);
//
//	string vs = LoadShader("foxVertex.shader");
//	const char* vertexShaderSource = vs.c_str();
//	string fs = LoadShader("foxFragment.shader");
//	const char* fragmentShaderSource = fs.c_str();
//
//	string vsc = LoadShader("notSimpleVertex.shader");
//	const char* vertexShaderColorSource = vsc.c_str();
//	string fsc = LoadShader("notSimpleFragment.shader");
//	const char* fragmentShaderColorSource = fsc.c_str();
//
//
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	unsigned int vertexShaderColor;
//	vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
//
//
//	//now that we have a vertex shader, let’s put the code text inside
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//
//
//	//aaaaand… Compile !
//	glCompileShader(vertexShader);
//
//	glShaderSource(vertexShaderColor, 1, &vertexShaderColorSource, NULL);
//	glCompileShader(vertexShaderColor);
//
//
//	//Do the same with the fragment shader !
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	unsigned int fragmentShaderColor;
//	fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShaderColor, 1, &fragmentShaderColorSource, NULL);
//	glCompileShader(fragmentShaderColor);
//
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//
//	unsigned int shaderProgramColor;
//	shaderProgramColor = glCreateProgram();
//
//
//
//	//now attach shaders to use to the program
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//
//	//and link it 
//	glLinkProgram(shaderProgram);
//
//	glAttachShader(shaderProgramColor, vertexShaderColor);
//	glAttachShader(shaderProgramColor, fragmentShaderColor);
//	glLinkProgram(shaderProgramColor);
//
//	//now that the program is complete, we can use it 
//	glUseProgram(shaderProgram);
//
//	//Create one ID to be given at object generation
//	unsigned int vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glGenBuffers(1, &vbo);
//	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	glUseProgram(shaderProgramColor);
//
//	unsigned int vaoColor;
//	glGenVertexArrays(1, &vaoColor);
//	glBindVertexArray(vaoColor);
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor), verticesColor, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	glBindVertexArray(0);
//
//	//Finally send the vertices array in the array buffer 
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// Position attribute
//	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);*/
//	// Color attribute
//	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);*/
//
//
//	
//
//
//
//	//bool isRunning = true;
//	//while (isRunning) {
//	//	// Get the time in seconds 
//	//	float timeValue = (float)SDL_GetTicks() / 500;
//	//	/*float redColor = (sin(timeValue) / 2.0f) + 0.5f;
//	//	float greenColor = (sin(timeValue+0.5f) / 2.0f) + 0.5f;
//	//	float blueColor = (sin(timeValue + 4.0f) / 2.0f) + 0.5f;
//	//	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//	//	glUseProgram(shaderProgram);
//	//	glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);*/
//	//	int offset = glGetUniformLocation(shaderProgramColor, "offset");
//	//	float offsetX = (sin(timeValue) / 2.0f);
//	//	float offsetY = (sin(timeValue) / 2.0f)+0.3f;
//	//	float offsetZ = (sin(timeValue) / 2.0f)+0.5f;
//	//	glUseProgram(shaderProgramColor);
//	//	glUniform3f(offset, offsetX,offsetY,offsetZ);
//
//
//	//	// Inputs
//	//	SDL_Event event;
//	//	while (SDL_PollEvent(&event)) {
//	//		switch (event.type) {
//	//		case SDL_QUIT:
//	//			isRunning = false;
//	//			break;
//	//		default:
//	//			break;
//	//		}
//	//	}
//	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
//	//	//Shader to use next
//	//	glUseProgram(shaderProgram);
//
//	//	//VAO to use next
//	//	glBindVertexArray(vao);
//
//	//	//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
//	//	//We draw from vertex 0 and we will be drawing 3 vertices
//	//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
//
//	//	glUseProgram(shaderProgramColor);
//	//	glBindVertexArray(vaoColor);
//	//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
//
//	//	SDL_GL_SwapWindow(Window); // Swapbuffer
//	//}
//	//// Quit
//	//SDL_DestroyWindow(Window);
//	//SDL_GL_DeleteContext(Context);
//
//
//	//cin.get();
//	//return 0;
//}