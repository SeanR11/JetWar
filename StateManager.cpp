#include "StateManager.h"

#include <SFML/Graphics.hpp>

void StateManager::isAdding(stateRef newState, bool isReplacing) {

	this->_newState = move(newState);
	this->_isReplacing = isReplacing;
	this->_isAdding = true;

}

void StateManager::isRemoving() {
	this->_isRemoving = true;
}

void StateManager::processStateChanges() {

	if (this->_isRemoving && !this->_states.empty()) {
		this->_states.pop();
		if (!this->_states.empty())
			this->_states.top()->Resume();
		this->_isRemoving = false;
		
	}
	if (this->_isAdding) {
		if (!this->_states.empty()) {
			if (this->_isReplacing)
				this->_states.pop();
			else
				this->_states.top()->Pause();
		}
		this->_states.push(move(this->_newState));
		this->_states.top()->Init();
		this->_isAdding = false;
	}
}

stateRef  &StateManager::GetActiveState() {
	return this->_states.top();
}
