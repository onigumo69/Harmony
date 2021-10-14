#pragma once

#include "Harmony/Renderer/Framebuffer.h"

namespace Harmony
{

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void invalidate();

		virtual void bind() override;
		virtual void unbind() override;

		virtual uint32_t get_color_attachment_renderer_id() const override { return _color_attachment; }

		virtual const FramebufferSpecification& get_specification() const override { return _specification; }
	private:
		uint32_t _renderer_id;
		uint32_t _color_attachment, _depth_attachment;
		FramebufferSpecification _specification;
	};

}