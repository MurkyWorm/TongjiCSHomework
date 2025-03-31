#include "State.h"

State::State() {
	for (int i = 0; i < 5; i++) {
		this->arg[i] = 0;
	}
	this->dirp = NULL;

	this->cdir = NULL;
	this->pdir = NULL;

	this->dent.m_ino = 0;
	this->dent.m_name[0] = '\0';

	this->dbuf[0] = '\0';
	this->curdir[0] = '/';
	this->curdir[1] = '\0';

	for (int i = 0; i < OpenFiles::NOFILES; i++) {
		this->ofiles.OpenFileTable[i] = NULL;
	}

	this->IOParam.m_Base = NULL;
	this->IOParam.m_Count = 0;
	this->IOParam.m_Offset = 0;
}

State::~State() {
	//do nothing
}

void State::ResetState() {
	for (int i = 0; i < 5; i++) {
		this->arg[i] = 0;
	}
	this->dirp = NULL;

	this->cdir = NULL;
	this->pdir = NULL;
	
	this->dent.m_ino = 0;
	this->dent.m_name[0] = '\0';

	this->dbuf[0] = '\0';
	this->curdir[0] = '/';

	for (int i = 0; i < OpenFiles::NOFILES; i++) {
		this->ofiles.OpenFileTable[i] = NULL;
	}

	this->IOParam.m_Base = NULL;
	this->IOParam.m_Count = 0;
	this->IOParam.m_Offset = 0;
}