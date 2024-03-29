// opengl_rgb_to_yuv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "assert.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SimpleShader.h"
#include "Opengl.h"
#include "RgbToNv12.h"
#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"

#pragma comment(lib, "glew32d.lib")
#pragma comment(lib, "glfw3.lib")

#include "stdio.h"


int main() 
{
	glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	int pic_width(0), pic_height(0), channels(0);

	unsigned char *data = stbi_load(".\\p800.jpg", &pic_width, &pic_height, &channels, 0);
	assert(data != NULL);

	GLFWwindow* window = glfwCreateWindow(pic_width, pic_height, "LearnOpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	char *buffer = new char[pic_width * pic_height * 4];

	OpenglConvertRgbToNV12 convert;

	convert.Initial();

	convert.ConvertRgbToNV12(data, pic_width, pic_height, buffer);

	//unsigned char *buff = new unsigned char[pic_width * pic_height * 4];
	//Rgb2NV12(data, 3, pic_width, pic_height, buff);


	return 0;

}


//int main()
//{
//	int pic_width(0), pic_height(0), channels(0);
//	int win_width(0), win_height(0);
//
//	GLfloat vertices[] = {
//		// Positions          // Texture Coords
//		1.0f,  1.0f, 0.0f,		
//		1.0f,	-1.0f, 0.0f,	
//		-1.0f,	-1.0, 0.0f,		
//		-1.0f,	1.0f, 0.0f,		
//	};
//
//	GLfloat tex_crood[] =
//	{
//		1280.f, 800.f,
//		1280.f, 0.f,
//		0.f,	0.f,
//		0.f, 800.f
//	};
//
//	GLuint indices[] = {  // Note that we start from 0!
//		0, 1, 3, // First Triangle
//		1, 2, 3  // Second Triangle
//	};
//
//	unsigned char *data = stbi_load(".\\p800.jpg", &pic_width, &pic_height, &channels, 0);
//	assert(data != NULL);
//
//	glfwInit();
//	// Set all the required options for GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
//	glfwWindowHint(GLFW_ALPHA_BITS, 8);
//	
//	GLFWwindow* window = glfwCreateWindow(pic_width, pic_height, "LearnOpenGL", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	glfwGetFramebufferSize(window, &win_width, &win_height);
//	glViewport(0, 0, win_width, win_height);
//
//	glewInit();
//
//	glEnable(GL_TEXTURE_RECTANGLE);
//
//	unsigned int texture(0), VBO(0), VAO(0), EBO(0), TEX_CROOD(0);
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	glGenBuffers(1, &TEX_CROOD);
//
//	//开始VAO
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ARRAY_BUFFER, TEX_CROOD);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_crood), tex_crood, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, TEX_CROOD);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(0);
//
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_RECTANGLE, texture);
//
//	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, pic_width, pic_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_RECTANGLE, 0);
//
//	Shader sh;
//	sh.LoadFromFile("./texture.vs", "./texture.frag");
//	void *pixels = new char [pic_width * pic_height * 4];
//
//	
//	glUniform1i(glGetUniformLocation(sh.Program, "width"), pic_width);
//	glUniform1i(glGetUniformLocation(sh.Program, "height"), pic_height);
//	glUniform1i(glGetUniformLocation(sh.Program, "ourTexture"), 0);
//
//	
//	//fbo
//	GLuint fbo(0), rbo(0), texture_frame(0);
//	
//	glGenTextures(1, &texture_frame);
//	glBindTexture(GL_TEXTURE_2D, texture_frame);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, pic_width, pic_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	//生成RenderBufferObject, 
//	glGenRenderbuffers(1, &rbo);
//	//绑定rbo
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	//为rbo开辟存储空间
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pic_width, pic_height);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	//生成fbo
//	glGenFramebuffers(1, &fbo);
//	//绑定fbo
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//	//绑定rbo到fbo
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_RENDERBUFFER, rbo);
//	//绑定纹理到fbo
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_frame, 0);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//	assert(e == GL_FRAMEBUFFER_COMPLETE);
//	
//	sh.Use();
//
//	while (!glfwWindowShouldClose(window)) 
//	{
//		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//		glViewport(0, 0,  pic_width, pic_height);
//		glDrawBuffer(GL_COLOR_ATTACHMENT0);
//
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glBindTexture(GL_TEXTURE_RECTANGLE, texture);
//	
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		glReadBuffer(GL_COLOR_ATTACHMENT0);
//		glReadPixels(0, 0, pic_width, pic_height, GL_RED, GL_UNSIGNED_BYTE, pixels);
//
//		glBindTexture(GL_TEXTURE_RECTANGLE, 0);
//
//		//glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
//
//		//glViewport(0, 0, pic_width, pic_height);
//		//glBindTexture(GL_TEXTURE_2D, texture_frame);
//		//glBindVertexArray(VAO);
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		//glBindTexture(GL_TEXTURE_2D, 0);
//
//
//		/*FILE *file = NULL;
//		fopen_s(&file, ".\\lol.yuv", "w");
//
//	
//		for (int i = 0; i < pic_height; i++)
//		{
//			fwrite((char*)(pixels) + i*(pic_width / 4), pic_width / 4, 1, file);
//		}
//		fclose(file);*/
//
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();
//	return 0;
//}

