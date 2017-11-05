#include "Texture2D.h"

Texture2D::Texture2D(){
	_textureId = 0;
}

Texture2D::~Texture2D(){
	glDeleteTextures(1, &_textureId);
}

void Texture2D::LoadTexture(string path){
	//DEVil
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(path.c_str());

	//OpenGL
	glGenTextures(1, &_textureId);
	Bind();
	//texture filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// y wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	Unbind();

}

void Texture2D::Bind(){
	
	glBindTexture(GL_TEXTURE_2D, _textureId);

}

void Texture2D::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
