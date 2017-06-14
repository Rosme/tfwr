/*
Copyright (C) - Jean-S�bastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <string>

namespace Core {

	class Message;

	class MessageHandler {
	public:
		MessageHandler() = default;
		virtual ~MessageHandler() = default;

		MessageHandler(const MessageHandler&) = delete;
		MessageHandler& operator=(const MessageHandler&) = delete;

		virtual void onMessage(const Message& message, const std::string& key) = 0;
	};
}