/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "stateids.hpp"
#include "state.hpp"

class StateStack {
public:
	StateStack(State::Context context);

	template<class T>
	void registerState(States::ID stateId);

private:
	std::vector<State::Ptr> m_stack;
	std::unordered_map<States::ID, std::function<State::Ptr()>> m_factories;

	State::Context m_context;
};

template<class T>
void StateStack::registerState(States::ID stateId) {
	m_factories[stateId] = [this]() {
		return std::make_unique<T>(this, m_context);
	}
}