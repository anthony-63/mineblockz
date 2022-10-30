require "crystglfw"
require "lib_gl"

include CrystGLFW

class MWindow
  def initialize(title : String, width : Int32, height : Int32)
    @hints = {
      Window::HintLabel::ContextVersionMajor => 3,
      Window::HintLabel::ContextVersionMinor => 3,
      Window::HintLabel::ClientAPI           => ClientAPI::OpenGL,
      Window::HintLabel::OpenGLProfile       => OpenGLProfile::Core,
    }
    @width = width
    @height = height
    @title = title
  end

  def run
    CrystGLFW.run do
      window = Window.new(width: @width, height: @height, title: @title, hints: @hints)

      window.make_context_current

      until window.should_close?
        CrystGLFW.poll_events

        if window.key_pressed?(Key::Escape)
          window.should_close
        end
        LibGL.clear_color(0.1, 0.2, 0.3, 1.0)
        LibGL.clear(LibGL::COLOR_BUFFER_BIT | LibGL::DEPTH_BUFFER_BIT)

        window.swap_buffers
      end
      window.destroy
    end
  end
end
