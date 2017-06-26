/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include "text.hpp"

#include <SFML/Graphics/Color.hpp>
#include <functional>

namespace Gui {

	class SelectableText
		: public Text {
	public:
		typedef std::function<void()> Callback;

	public:
		SelectableText(const sf::Font& font, const std::string& text, unsigned int characterSize = 35);

		void setCallback(Callback callback);

		virtual void select() override;
		virtual void unselect() override;
		virtual void activate() override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		const sf::Color DefaultColor = sf::Color::White;
		const sf::Color ActivationColor = sf::Color::Cyan;
		const sf::Color SelectedColor = sf::Color::Red;
		Callback m_callback;
	};

}