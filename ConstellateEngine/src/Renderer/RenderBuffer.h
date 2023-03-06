#pragma once

#include "cslpch.h"

namespace csl {

	enum class OpenGLDataType {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static unsigned int OpenGLDataTypeSize(OpenGLDataType type) {

		using enum OpenGLDataType;
		switch (type) {
		case Float: return sizeof(float);
		case Float2: return sizeof(float) * 2;
		case Float3: return sizeof(float) * 3;
		case Float4: return sizeof(float) * 4;
		case Mat3: return sizeof(float) * 3 * 3;
		case Mat4: return sizeof(float) * 4 * 4;
		case Int: return sizeof(int);
		case Int2: return sizeof(int) * 2;
		case Int3: return sizeof(int) * 3;
		case Int4: return sizeof(int) * 4;
		case Bool: return sizeof(bool);
		}

		return 0;
	};



	struct BufferElements {
		std::string _name;
		OpenGLDataType _type;
		unsigned int _size;
		unsigned int _offset;
		bool _normalized;

		BufferElements(OpenGLDataType type, const std::string name, bool normalized = false)
			: _name(name), _type(type), _size(OpenGLDataTypeSize(type)), _offset(0),
			_normalized(normalized)
		{}

		unsigned int GetComponentCount() const
		{
			using enum OpenGLDataType;
			switch (_type)
			{
			case Float:   return 1;
			case Float2:  return 2;
			case Float3:  return 3;
			case Float4:  return 4;
			case Mat3:    return 3 * 3;
			case Mat4:    return 4 * 4;
			case Int:     return 1;
			case Int2:    return 2;
			case Int3:    return 3;
			case Int4:    return 4;
			case Bool:    return 1;
			}
			return 0;
		}
	};


	class BufferLayout {
	private:
		std::vector<BufferElements> _elements;
		unsigned int stride = 0;
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElements>& elements) :
			_elements(elements)
		{
			CalculateOffet();
		}

		std::vector<BufferElements> GetElements() {
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

	class VertexBuffer {
	private:

	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout GetLayout() = 0;

		static VertexBuffer* VertexBufferOf(float* vertices, size_t size);
	};

	class IndexBuffer {
	private:
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetCount() const = 0;


		static IndexBuffer* IndexBufferOf(unsigned int* vertices, size_t size);
	};

}