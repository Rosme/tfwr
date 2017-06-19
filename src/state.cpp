/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "state.hpp"
#include "message_dispatcher.hpp"

State::Context::Context(sf::RenderWindow& window, Core::MessageDispatcher& dispatcher, FontHolder& fontHolder)
	: window(window), dispatcher(dispatcher), fontHolder(fontHolder) {}

State::State(StateStack& stateStack, Context context) 
	: m_stateStack(stateStack), m_context(context) {
	context.dispatcher.registerHandler("state.loaded", *this);
}

State::~State() {
	m_context.dispatcher.unregisterHandler("state.loaded", *this);
}
