/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <thor/Time/Timer.hpp>
#include <vector>

namespace Gui {

	class AnimatedText
		: public sf::Drawable
		, public sf::Transformable {
	public:
		enum class AnimationType {
			None,
			TextChange
		};

	public:
		AnimatedText(AnimationType animationType = AnimationType::None);
		AnimatedText(const sf::Font& font, AnimationType animationType = AnimationType::None);
		AnimatedText(const sf::Font& font, const sf::String& text, AnimationType animationType = AnimationType::None);
		AnimatedText(const sf::Font& font, const sf::String& text, unsigned int characterSize, AnimationType animationType = AnimationType::None);

		void setFont(const sf::Font& font);
		void setString(const sf::String& text);
		void setCharacterSize(unsigned int size);
		sf::FloatRect getGlobalBounds() const;
		void setAnimationType(AnimationType animationType);
		void animate();
		void setAnimationDelay(sf::Time delay);

		//Animate Text functions
		void setChangeStrings(const std::vector<std::string>& strings);
		void pushChangeString(const std::string& string);
		void clear();

	private:
		void animateTextChange();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text m_text;
		AnimationType m_animationType;
		thor::Timer m_animationTimer;
		sf::Time m_delay;

		//Text Change
		std::vector<std::string> m_textChangeStrings;
		unsigned int m_textChangeIndex;	
	};

}