/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "message_dispatcher.hpp"
#include "message_handler.hpp"

namespace Core {

    MessageDispatcher::AsyncImpl::AsyncImpl() {
        m_running = false;
    }

    
	void MessageDispatcher::AsyncImpl::registerHandler(const std::string& name, MessageHandler& handler) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_handlers.emplace(std::make_pair(name, &handler));
	}

	void MessageDispatcher::AsyncImpl::unregisterHandler(const std::string& name, MessageHandler& handler) {
		std::lock_guard<std::mutex> lock(m_mutex);
		auto range = m_handlers.equal_range(name);
		for(auto it = range.first; it != range.second;) {
			if(it->second == &handler) {
				it = m_handlers.erase(it);
			} else {
				++it;
			}
		}
	}

	void MessageDispatcher::AsyncImpl::pushMessage(const std::string& name, const Message& message) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_messages.emplace(std::make_pair(name, message));
	}

	void MessageDispatcher::AsyncImpl::dispatch() {
		while(m_running) {
			while(m_messages.size() == 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}

			MessageQueue messageQueue;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				messageQueue.swap(m_messages);
			}
			while(!messageQueue.empty()) {
				auto messagePair = messageQueue.front();
				auto range = m_handlers.equal_range(messagePair.first);
				for(auto it = range.first; it != range.second; ++it) {
					it->second->onMessage(messagePair.second, messagePair.first);
				}
				messageQueue.pop();
			}
		}
	}

	void MessageDispatcher::AsyncImpl::start() {
		m_running = true;
		m_thread = std::thread(&AsyncImpl::dispatch, this);
		m_thread.detach();
	}

	void MessageDispatcher::AsyncImpl::stop() {
		m_running = false;
	}

	void MessageDispatcher::SyncImpl::registerHandler(const std::string& name, MessageHandler& handler) {
		m_handlers.emplace(std::make_pair(name, &handler));
	}

	void MessageDispatcher::SyncImpl::unregisterHandler(const std::string& name, MessageHandler& handler) {
		auto range = m_handlers.equal_range(name);
		for(auto it = range.first; it != range.second;) {
			if(it->second == &handler) {
				it = m_handlers.erase(it);
			} else {
				++it;
			}
		}
	}

	void MessageDispatcher::SyncImpl::pushMessage(const std::string& name, const Message& message) {
		m_messages.emplace(std::make_pair(name, message));
	}

	void MessageDispatcher::SyncImpl::dispatch() {
		while(!m_messages.empty()) {
			auto messagePair = m_messages.front();
			auto range = m_handlers.equal_range(messagePair.first);
			for(auto it = range.first; it != range.second; ++it) {
				it->second->onMessage(messagePair.second, messagePair.first);
			}
			m_messages.pop();
		}
	}

	MessageDispatcher::MessageDispatcher(Type type) {
		if(type == Type::Async) {
			m_impl = std::make_unique<AsyncImpl>();
		} else {
			m_impl = std::make_unique<SyncImpl>();
		}
	}

	void MessageDispatcher::registerHandler(const std::string& name, MessageHandler& handler) {
		m_impl->registerHandler(name, handler);
	}

	void MessageDispatcher::unregisterHandler(const std::string& name, MessageHandler& handler) {
		m_impl->unregisterHandler(name, handler);
	}

	void MessageDispatcher::pushMessage(const std::string& name, const Message& message) {
		m_impl->pushMessage(name, message);
	}

	void MessageDispatcher::dispatch() {
		m_impl->dispatch();
	}

	void MessageDispatcher::start() {
		m_impl->start();
	}

	void MessageDispatcher::stop() {
		m_impl->stop();
	}

}
