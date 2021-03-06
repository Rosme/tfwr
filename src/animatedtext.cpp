/*
Copyright (C) - Jean-S�bastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "animatedtext.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <rsm/logger.hpp>

namespace Gui {

	AnimatedText::AnimatedText(AnimationType animationType)
		: m_animationType(animationType) {}

	AnimatedText::AnimatedText(const sf::Font& font, AnimationType animationType)
		: m_text("", font), m_animationType(animationType) {}

	AnimatedText::AnimatedText(const sf::Font& font, const sf::String& text, AnimationType animationType)
		: m_text(text, font), m_animationType(animationType) {}

	AnimatedText::AnimatedText(const sf::Font& font, const sf::String& text, unsigned int characterSize, AnimationType animationType)
		: m_text(text, font, characterSize), m_animationType(animationType) {}


	void AnimatedText::setFont(const sf::Font& font) {
		m_text.setFont(font);
	}

	void AnimatedText::setString(const sf::String& text) {
		m_text.setString(text);
	}

	void AnimatedText::setCharacterSize(unsigned int size) {
		m_text.setCharacterSize(size);
	}

	sf::FloatRect AnimatedText::getGlobalBounds() const {
		return m_text.getGlobalBounds();
	}

	sf::FloatRect AnimatedText::getLocalBounds() const {
		return m_text.getLocalBounds();
	}

	void AnimatedText::setAnimationType(AnimationType animationType) {
		m_animationType = animationType;
	}

	void AnimatedText::animate(const sf::Time& delta) {
		if(m_animationType == AnimationType::None) {
			return;
		}

		if(!m_animationTimer.isRunning()) {
			m_animationTimer.start();
		}

		switch(m_animationType) {
		case AnimationType::TextChange:
			animateTextChange();
			break;
		case AnimationType::Rotating:
			animateWaving(delta);
			break;
		default:
			RSM_LOG_CRITICAL("Unsupported Animation Type");
		}
	}

	void AnimatedText::setAnimationDelay(const sf::Time& delay) {
		m_delay = delay;
		m_animationTimer.reset(m_delay);
	}

	void AnimatedText::setChangeStrings(const std::vector<std::string>& strings) {
		m_textChangeStrings = strings;
		m_textChangeIndex = m_textChangeStrings.size();
	}

	void AnimatedText::pushChangeString(const std::string& string) {
		m_textChangeStrings.push_back(string);
		++m_textChangeIndex;
	}

	void AnimatedText::clear() {
		m_textChangeStrings.clear();
		m_textChangeIndex = 0;
	}

	void AnimatedText::setRotatingAngleLimit(float angle) {
		m_angleLimit = angle;
	}

	void AnimatedText::setRotatingAngleStep(float angle) {
		m_angleStep = angle;
	}

	void AnimatedText::animateTextChange() {
		if(m_animationTimer.isExpired()) {
			++m_textChangeIndex;
			if(m_textChangeIndex >= m_textChangeStrings.size()) {
				m_textChangeIndex = 0;
			}
			m_text.setString(m_textChangeStrings[m_textChangeIndex]);
			m_animationTimer.restart(m_delay);
		}
	}

	void AnimatedText::animateWaving(const sf::Time& delta) {
		if(m_animationTimer.isExpired()) {
			float angle = m_angleStep*delta.asSeconds()*m_angleDirection;
			m_currentAngle += angle;
			if(m_currentAngle >= m_angleLimit || m_currentAngle <= m_angleLimit*-1) {
				m_angleDirection *= -1;
			}

			rotate(angle);

			m_animationTimer.restart(m_delay);
		}
	}

	void AnimatedText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(m_text, states);
	}

}

