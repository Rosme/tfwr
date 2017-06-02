/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <memory>

#include "any.hpp"

namespace Core {

	class Message {
	public:
		template<class T>
		Message(T t)
			: m_content(t) {}

		const Any& getContent() const {
			return m_content;
		}

	private:
		Any m_content;
	};

}