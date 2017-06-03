/*
 * CircularBuffer.h
 *
 *  Created on: Jun 1, 2017
 *      Author: chinm_000
 */

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "active_log.h"

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

using namespace StdEvents;

#define CBE_CAST(cbe) (static_cast<CircularBufferElement>(cbe))

namespace StdDataStruct {

	struct CircularBufferRange {
		uint32_t start;
		uint32_t end;
		CircularBufferRange(int s, int e): start(s), end(e) {}
	};

	class CircularBufferElement{
	public:
		uint32_t timestamp;
		CircularBufferElement(const CircularBufferElement& el)
				: timestamp(el.timestamp) {}
		CircularBufferElement() : timestamp(HAL_GetTick()){}
		CircularBufferElement(uint32_t ts): timestamp(ts) {}
		virtual void print(void) {
			PRINT("%d", timestamp);
		}
	};

	template <class T>
	class CircularBuffer {
	private:
		uint32_t m_first;
		uint32_t m_size;
		uint32_t m_last;
		T * m_buffer;
		uint32_t m_buffersize;
		void validateType(CircularBufferElement  &el ) const {}
		enum {
			GTE, LTE
		} SearchType;


	public:
		CircularBuffer(T *buffer, int buffsize)
			: m_first(0), m_size(0), m_last(0), m_buffer(buffer), m_buffersize(buffsize) {
			T el;
			validateType(el);
		}
		bool empty() const { return m_size == 0; }
		bool full() const { return m_size == m_buffersize; }
		void push(T &value);
		T & operator[] (uint32_t pos);
		T & get(uint32_t pos);
		CircularBufferRange getRange(uint32_t timeX, uint32_t timeY);
		T & getElementAtOrBelow(uint32_t timeX);
		void print();
		uint32_t search(uint32_t timestamp, uint32_t startIndex, uint32_t endIndex, enum_t type) {

			CircularBufferElement &firstEl = (CircularBufferElement &)(this->get(startIndex));
			if (endIndex == startIndex) {
				if (type == GTE && firstEl.timestamp >= timestamp
						|| type == LTE && firstEl.timestamp <= timestamp) {
					return startIndex;
				}
				return -1;
			}
			uint32_t midIndex = (startIndex + endIndex)/2;
			CircularBufferElement &lastEl = (CircularBufferElement &)(get(endIndex));
			CircularBufferElement &midEl = (CircularBufferElement &)(get(midIndex));
			switch (type) {
			case GTE:
				if (firstEl.timestamp >= timestamp) {
					return startIndex;
				}
				if (lastEl.timestamp < timestamp) {
					return -1;
				}
				if (midEl.timestamp >= timestamp) {
					return search(timestamp, startIndex + 1, midIndex, GTE);
				} else {
					return search(timestamp, midIndex + 1, endIndex, GTE);
				}
				break;
			case LTE:
				if (lastEl.timestamp <= timestamp) {
					return endIndex;
				}
				if (firstEl.timestamp > timestamp) {
					return -1;
				}
				if (midEl.timestamp <= timestamp) {
					return search(timestamp, midIndex, endIndex, GTE);
				} else {
					return search(timestamp, startIndex, midIndex, GTE);
				}
				break;
			}
		}
	};

	template<class T>
	void CircularBuffer<T>::push(T &value) {
		if( m_last >= m_buffersize ) {
			m_last = 0 ;
		}
		m_buffer[m_last] = value;
		++m_last;
		if( full() ) {
			m_first = (m_first + 1) %  m_buffersize ;
		} else {
			++m_size;
		}
	}

	template<class T>
	void CircularBuffer<T>::print() {
		CircularBufferElement * el;
		if( m_first < m_last ) {
			for(uint32_t i = m_first ; i < m_last ; ++i ) {
				el = static_cast<CircularBufferElement *>(&m_buffer[i]);
				el->print();
			}
		}
		else {
			for(uint32_t i = m_first ; i < m_buffersize ; ++i ) {
				el = static_cast<CircularBufferElement *>(&m_buffer[i]);
				el->print();
			}
			for(uint32_t i = 0 ; i < m_last ; ++i ) {
				el = static_cast<CircularBufferElement *>(&m_buffer[i]);
				el->print();
			}
		}
	}
	template<class T>
	T &CircularBuffer<T>::operator [](uint32_t pos) {
		return get(pos);
	}

	template<class T>
	T &CircularBuffer<T>::get(uint32_t pos) {
		uint32_t p = ( m_first + pos ) % m_buffersize ;
		return m_buffer[p] ;
	}

	template<class T>
	CircularBufferRange CircularBuffer<T>::getRange(uint32_t timeX,
			uint32_t timeY) {
		if (m_size == 0) {
			return CircularBufferRange(-1, -1);
		}
		return CircularBufferRange(
			search(timeX, 0, m_size-1, GTE),
			search(timeY, 0, m_size-1, LTE));
	}

	template<class T>
	T &CircularBuffer<T>::getElementAtOrBelow(uint32_t timeX) {
		return NULL;
	}
}
#endif /* CIRCULARBUFFER_H_ */
