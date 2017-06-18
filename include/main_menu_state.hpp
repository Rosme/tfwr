/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include "state.hpp"

class MainMenuState
	: public State {
public:
	MainMenuState(StateStack& stateStack, Context context);

	virtual void onMessage(const Core::Message& message, const std::string& key) override;
	virtual void draw() override;
	virtual bool update(const sf::Time& delta) override;
	virtual bool handleEvent(const sf::Event& event) override;

};