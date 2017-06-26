/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include "guicomponent.hpp"

#include <SFML/Graphics/Text.hpp>

namespace Gui {

	class Text 
		: public Component {
	public:
		Text() = default;
		Text(const sf::Font& font, const std::string& text);
		Text(const sf::Font& font, const std::string& text, unsigned int characterSize);
		virtual ~Text() = default;

		void setFont(const sf::Font& font);
		void setString(const std::string& text);
		void setCharacterSize(unsigned int size);
		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBounds() const;

	protected:
		sf::Text m_text;
	};

}