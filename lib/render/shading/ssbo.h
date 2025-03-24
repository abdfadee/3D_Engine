#pragma once
#include <glad/glad.h>


class SSBO {
private:
	unsigned int id;


public:
	SSBO() {}

	SSBO(unsigned int binding, unsigned int size) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, 0, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, id);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void upload(unsigned int offset, unsigned int size, void* data) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

};