#pragma once
#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> stateRef;

class StateManager
{
public:

	StateManager() { }
	~StateManager() { }

	void isAdding(stateRef newState, bool isReplacing = true);
	void isRemoving();
	void processStateChanges();

	stateRef &GetActiveState();

private:
	std::stack<stateRef> _states;
	stateRef _newState;

	bool _isAdding;
	bool _isRemoving;
	bool _isReplacing;
};

