/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace Gui {

	class Component
		: public sf::Transformable
		, public sf::Drawable {
	public:
		typedef std::unique_ptr<Component> Ptr;

	public:
		Component();
		virtual ~Component();

		const bool isSelected() const;
		virtual void select();
		virtual void unselect();

		const bool isActive() const;
		virtual void activate();
		virtual void deactivate();

	private:
		bool m_isSelected;
		bool m_isActive;
	
	};

}