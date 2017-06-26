/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "selectabletext.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace Gui {

	SelectableText::SelectableText(const sf::Font& font, const std::string& text, unsigned int characterSize)
		: Text(font, text, characterSize) {}

	void SelectableText::setCallback(Callback callback) {
		m_callback = callback;
	}

	void SelectableText::select() {
		Component::select();
		m_text.setFillColor(SelectedColor);
	}

	void SelectableText::unselect() {
		Component::unselect();
		m_text.setFillColor(DefaultColor);
	}

	void SelectableText::activate() {
		Component::activate();
		
		m_text.setFillColor(ActivationColor);

		if(m_callback) {
			m_callback();
		}
	}

	void SelectableText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(m_text, states);
	}

}