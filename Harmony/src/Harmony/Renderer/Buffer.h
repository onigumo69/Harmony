#pragma once

#include "Harmony/Core.h"
#include "Harmony/Log.h"

#include <cstdint>

namespace Harmony
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		HM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string _name;
		ShaderDataType _type;
		uint32_t _size;
		uint32_t _offset;
		bool _normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: _name(name), _type(type), _size(ShaderDataTypeSize(type)), _offset(0), _normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (_type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			HM_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: _elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t get_stride() const { return _stride; }
		inline const std::vector<BufferElement>& GetElements() const { return _elements; }

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			_stride = 0;
			for (auto& element : _elements)
			{
				element._offset = offset;
				offset += element._size;
				_stride += element._size;
			}
		}
	private:
		std::vector<BufferElement> _elements;
		uint32_t _stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& get_layout() const = 0;
		virtual void set_layout(const BufferLayout& layout) = 0;

		static VertexBuffer* create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t get_count() const = 0;

		static IndexBuffer* create(uint32_t* indices, uint32_t size);
	};

}