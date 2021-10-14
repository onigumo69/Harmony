#pragma once

#include "Harmony/Core/Core.h"

namespace Harmony
{

	struct FramebufferSpecification
	{
		uint32_t width, height;
		uint32_t samples = 1;

		bool swap_chain_target = false;
	};

	class Framebuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual uint32_t get_color_attachment_renderer_id() const = 0;

		virtual const FramebufferSpecification& get_specification() const = 0;

		static Ref<Framebuffer> create(const FramebufferSpecification& spec);
	};

}