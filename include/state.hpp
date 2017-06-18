/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include "message_handler.hpp"
#include "resourceids.hpp"

#include <SFML/Graphics/Font.hpp>
#include <Thor/Resources.hpp>
#include <memory>

typedef thor::ResourceHolder<sf::Font, Resources::FontIds> FontHolder;

namespace sf {
	class RenderWindow;
	class Event;
	class Time;
}

namespace Core {
	class Message;
	class MessageDispatcher;
}

class StateStack;

class State 
	: public Core::MessageHandler {
public:
	typedef std::unique_ptr<State> Ptr;
	
	struct Context {
		Context(sf::RenderWindow& window, Core::MessageDispatcher& dispatcher, FontHolder& fontHolder);

		sf::RenderWindow& window;
		Core::MessageDispatcher& dispatcher;
		FontHolder& fontHolder;
	};

public:
	State(StateStack& stateStack, Context context);

	virtual ~State();
	
	virtual void onMessage(const Core::Message& message, const std::string& key) override;
	
	virtual void draw() = 0;
	virtual bool update(const sf::Time& delta) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	Context m_context;
	StateStack& m_stateStack;
};