/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <queue>

#include "message.hpp"

namespace Core {

	class MessageHandler;

	class MessageDispatcher {
	public:
		MessageDispatcher() = default;

		MessageDispatcher(const MessageDispatcher&) = delete;
		MessageDispatcher& operator=(const MessageDispatcher&) = delete;

		void registerHandler(const std::string& name, MessageHandler& handler);

		void pushMessage(const std::string& name, const Message& message);
		void dispatch();

	private:
		typedef std::unordered_multimap<std::string, MessageHandler*> HandlerMap;
		HandlerMap m_handlers;
		std::queue<std::pair<std::string, Message>> m_messages;
	};

}