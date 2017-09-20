/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include "message.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>

namespace Core {

	class MessageHandler;

	class MessageDispatcher {
	public:
		enum class Type {
			Async,
			Sync
		};

	public:
		MessageDispatcher(Type type = Type::Sync);

		MessageDispatcher(const MessageDispatcher&) = delete;
		MessageDispatcher& operator=(const MessageDispatcher&) = delete;

		void registerHandler(const std::string& name, MessageHandler& handler);
		void unregisterHandler(const std::string& name, MessageHandler& handler);

		void pushMessage(const std::string& name, const Message& message = Message());
		void dispatch();
		void start();
		void stop();

	private:
		struct Impl {
			virtual ~Impl() = default;
			virtual void registerHandler(const std::string& name, MessageHandler& handler) = 0;
			virtual void unregisterHandler(const std::string& name, MessageHandler& handler) = 0;
			virtual void pushMessage(const std::string& name, const Message& message) = 0;
			virtual void dispatch() = 0;
			virtual void start() {};
			virtual void stop() {};

			typedef std::unordered_multimap<std::string, MessageHandler*> HandlerMap;
			HandlerMap m_handlers;
			typedef std::queue<std::pair<std::string, Message>> MessageQueue;
			MessageQueue m_messages;
		};

		struct AsyncImpl
			: public Impl {
            AsyncImpl();
			virtual void registerHandler(const std::string& name, MessageHandler& handler) override;
			virtual void unregisterHandler(const std::string& name, MessageHandler& handler) override;
			virtual void pushMessage(const std::string& name, const Message& message) override;
			virtual void dispatch() override;
			virtual void start() override;
			virtual void stop() override;

			std::thread m_thread;
			std::mutex m_mutex;
            std::atomic<bool> m_running;
		};

		struct SyncImpl
			: public Impl {
			virtual void registerHandler(const std::string& name, MessageHandler& handler) override;
			virtual void unregisterHandler(const std::string& name, MessageHandler& handler) override;
			virtual void pushMessage(const std::string& name, const Message& message) override;
			virtual void dispatch() override;
		};

	private:
		std::unique_ptr<Impl> m_impl;
	};

}
