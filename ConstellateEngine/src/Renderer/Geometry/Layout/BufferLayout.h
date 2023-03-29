#pragma once

#include "BufferElement.h"

namespace csl {

	class BufferLayout {
	private:
		std::vector<BufferElement> _elements;
		unsigned int stride = 0;
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) :
			_elements(elements)
		{
			CalculateOffet();
		}

		std::vector<BufferElement> GetElements() {
			return _elements;
		}

		unsigned int GetStride() {
			return stride;
		}

	private:
		void CalculateOffet() {
			unsigned int offset = 0;
			for (auto& element : _elements) {
				element._offset = offset;
				offset += element._size;
				stride += element._size;
			}
		}
	};




}