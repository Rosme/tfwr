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

	class SelectableText
		: public Component {
	public:
		SelectableText(const sf::Font& font, const std::string& text);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text m_text;
	};

}