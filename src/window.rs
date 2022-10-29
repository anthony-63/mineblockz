use bgfx_rs::static_lib as bgfx;

use raw_window_handle::{HasRawWindowHandle, RawWindowHandle};
use std::sync::mpsc::Receiver;
pub struct MWindow {
    raw_win: glfw::Window,
    events: Receiver<(f64, glfw::WindowEvent)>,
    glfw_: glfw::Glfw,
    width: u32,
    height: u32,
    dt: f32,
    last: f32,
}

impl MWindow {
    pub fn new(title: &str, width: u32, height: u32) -> Self {
        let mut glfw = glfw::init(glfw::FAIL_ON_ERRORS).unwrap();

        glfw.window_hint(glfw::WindowHint::Resizable(false));
        glfw.window_hint(glfw::WindowHint::ClientApi(glfw::ClientApiHint::NoApi));

        let (mut window, events) = glfw
            .create_window(width, height, title, glfw::WindowMode::Windowed)
            .expect("Failed to create GLFW window");

        window.set_key_polling(true);

        let mut init = bgfx::Init::new();

        init.type_r = bgfx::RendererType::Vulkan;
        init.resolution.width = width;
        init.resolution.height = height;
        init.resolution.reset = bgfx::ResetFlags::VSYNC.bits();
        init.platform_data = Self::get_platform_data(&mut window);

        if !bgfx::init(&init) {
            panic!("Failed to initialize BGFX");
        }

        bgfx::set_debug(bgfx::DebugFlags::TEXT.bits());

        bgfx::set_view_clear(
            0,
            bgfx::ClearFlags::COLOR.bits() | bgfx::ClearFlags::DEPTH.bits(),
            bgfx::SetViewClearArgs {
                rgba: 0x103030ff,
                ..Default::default()
            },
        );

        Self {
            glfw_: glfw,
            raw_win: window,
            events,
            width,
            height,
            dt: 0.0,
            last: 0.0,
        }
    }

    fn draw(&mut self) {
        bgfx::set_view_rect(0, 0, 0, self.width as u16, self.height as u16);
        bgfx::touch(0);

        bgfx::dbg_text_clear(bgfx::DbgTextClearArgs::default());

        // for color palette refer to https://www.fountainware.com/EXPL/vgapalette.png (TOP ROW ONLY)
        bgfx::dbg_text(
            0,
            0,
            0x70,
            format!("FPS: {}", (1.0 / self.dt) as u32).as_str(),
        );

        bgfx::frame(false);
    }

    fn update(&mut self) {
        self.dt = self.glfw_.get_time() as f32 - self.last;
        self.last = self.glfw_.get_time() as f32;
    }

    pub fn run(&mut self) {
        while !self.raw_win.should_close() {
            self.glfw_.poll_events();

            self.update();
            self.draw();

            for (_, ev) in glfw::flush_messages(&self.events) {
                Self::handle_event(&mut self.raw_win, ev);
            }
        }
        bgfx::shutdown();
    }

    fn handle_event(window: &mut glfw::Window, event: glfw::WindowEvent) {
        match event {
            glfw::WindowEvent::Close => {
                window.set_should_close(true);
            }
            _ => {}
        }
    }

    fn get_platform_data(window: &mut glfw::Window) -> bgfx::PlatformData {
        let mut pd = bgfx::PlatformData::new();

        match window.raw_window_handle() {
            #[cfg(any(
                target_os = "linux",
                target_os = "dragonfly",
                target_os = "freebsd",
                target_os = "netbsd",
                target_os = "openbsd"
            ))]
            RawWindowHandle::Xlib(data) => {
                pd.nwh = data.window as *mut _;
                pd.ndt = data.display as *mut _;
            }
            #[cfg(any(
                target_os = "linux",
                target_os = "dragonfly",
                target_os = "freebsd",
                target_os = "netbsd",
                target_os = "openbsd"
            ))]
            RawWindowHandle::Wayland(data) => {
                pd.ndt = data.surface;
                pd.nwh = data.display;
            }
            #[cfg(target_os = "macos")]
            RawWindowHandle::MacOS(data) => {
                pd.nwh = data.ns_window;
            }
            #[cfg(target_os = "windows")]
            RawWindowHandle::Windows(data) => {
                pd.nwh = data.hwnd;
            }
            _ => panic!("Window manager/Device not supported"),
        }

        pd
    }
}
