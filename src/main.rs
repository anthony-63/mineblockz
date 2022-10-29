mod window;
extern crate bgfx_rs;

const TITLE: &str = "MineBlockz! | v0.1 ALPHA";
const WIDTH: u32 = 1280;
const HEIGHT: u32 = 720;

fn main() {
    let mut window = window::MWindow::new(TITLE, WIDTH, HEIGHT);

    window.run();
}
