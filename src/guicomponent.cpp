/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "guicomponent.hpp"

namespace Gui {

	Component::Component() 
		: m_isSelected(false)
		, m_isActive(false) {}

	Component::~Component() {}

	const bool Component::isSelected() const {
		return m_isSelected;
	}

	void Component::select() {
		m_isSelected = true;
	}

	void Component::unselect() {
		m_isSelected = false;
	}

	const bool Component::isActive() const {
		return m_isActive;
	}

	void Component::activate() {
		m_isActive = true;
	}

	void Component::deactivate() {
		m_isActive = false;
	}

}

