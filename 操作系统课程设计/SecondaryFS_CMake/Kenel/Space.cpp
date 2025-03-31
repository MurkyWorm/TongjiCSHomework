#include "Space.h"
#include "stdlib.h"

Space::Space() {
	this->pathParam[0] = '\0';
	this->buffer = (unsigned char*)malloc(sizeof(unsigned char) * 5 * 1024 * 1024);
}

Space::~Space() {
	free(this->buffer);
}

void Space::ResetSpace() {
	this->pathParam[0] = '\0';
	free(this->buffer);
	this->buffer = (unsigned char*)malloc(sizeof(unsigned char) * 5 * 1024 * 1024);
}