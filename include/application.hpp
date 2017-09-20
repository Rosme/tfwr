/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include "message_dispatcher.hpp"
#include "state_stack.hpp"
#include "resourceids.hpp"
#include "message_handler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

class Application 
	: public Core::MessageHandler {
public:
	explicit Application();

	void run();


	virtual void onMessage(const Core::Message& message, const std::string& key) override;

private:
	void registerStates();
	void draw();
	void handleEvents();

private:
	static const sf::Time MaximumTimePerFrame;

	sf::RenderWindow m_window;
	Core::MessageDispatcher m_dispatcher;
	StateStack m_stateStack;
	FontHolder m_fontHolder;
    bool m_isClosing = false;
};
