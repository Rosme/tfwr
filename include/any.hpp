/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <memory>

namespace Core {

	class Any {
	public:
		Any() 
			: m_holder(nullptr) {}

		template<class Type>
		Any(const Type& data)
			: m_holder(new Impl<Type>(data)) {}

		Any(const Any& other)
			: m_holder(other.m_holder ? other.m_holder->copy() : nullptr) {}

		template<class Type>
		Any& operator=(const Type& other) {
			Any(other).swap(*this);
			return *this;
		}

		Any& operator=(Any other) {
			Any(other).swap(*this);
			return *this;
		}

		~Any() {
		}

		bool isValid() const {
			return m_holder != nullptr;
		}

		template<class Type>
		Type& get() const {
			return reinterpret_cast<Impl<Type>*>(m_holder.get())->val;
		}

	private:
		Any& swap(Any& other) {
			std::swap(m_holder, other.m_holder);
			return *this;
		}

		struct Holder {
			virtual ~Holder() {}
			virtual Holder* copy() = 0;
		};

		template<class Type>
		struct Impl : Holder {
			Impl(const Type& t)
				: val(t) {}
			
			Holder* copy() {
				return new Impl(val);
			}

			Type val;
		};

		std::unique_ptr<Holder> m_holder;
	};

}