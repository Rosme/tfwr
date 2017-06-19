/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "state_stack.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
	: m_stack()
	, m_factories()
	, m_context(context) {}

void StateStack::update(const sf::Time& delta) {
	for(auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {
		if(!(*itr)->update(delta)) {
			break;
		}
	}

	applyPendingChanges();
}

void StateStack::draw() {
	for(auto& state : m_stack) {
		state->draw();
	}
}

void StateStack::handleEvents(const sf::Event& event) {
	for(auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {
		if(!(*itr)->handleEvent(event)) {
			break;
		}
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateId) {
	m_pendingChanges.push_back(PendingChange(Action::Push, stateId));
}

void StateStack::pop() {
	m_pendingChanges.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates() {
	m_pendingChanges.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const {
	return m_stack.size() == 0;
}

void StateStack::applyPendingChanges() {
	for(auto& pendingChange : m_pendingChanges) {
		switch(pendingChange.action) {
		case Action::Push:
			m_stack.push_back(createState(pendingChange.stateId));
			break;
		case Action::Pop:
			m_stack.pop_back();
			break;
		case Action::Clear:
			m_stack.clear();
			break;
		default:
			assert("Error by design");
		}
	}

	m_pendingChanges.clear();
}

State::Ptr StateStack::createState(States::ID stateId) {
	auto state = m_factories.find(stateId);
	assert(state != m_factories.end());

	return state->second();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateId) 
	: action(action), stateId(stateId){}
