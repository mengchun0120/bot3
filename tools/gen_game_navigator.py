import click
import json
import cairo
import math
import os

def gen_base_navigator(base_radius, toggle_radius):
    width = int(2 * base_radius)
    height = width
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx = cairo.Context(surface)

    ctx.set_source_rgb(0.5, 0.5, 1.0)
    ctx.arc(base_radius, base_radius, toggle_radius, 0, 2*math.pi)
    ctx.arc_negative(base_radius, base_radius, base_radius, 2*math.pi, 0)
    ctx.fill()

    surface.write_to_png(os.path.join("res", "pics", "base_navigator.png"))

def gen_toggle_buttons(toggle_radius):
    width = int(2 * toggle_radius)
    height = width
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx = cairo.Context(surface)

    ctx.set_source_rgb(0.5, 1.0, 0.5)
    ctx.arc(toggle_radius, toggle_radius, toggle_radius, 0, 2*math.pi)
    ctx.fill()

    surface.write_to_png(os.path.join("res", "pics", "green_toggle_button.png"))

    ctx.set_source_rgb(1.0, 0.5, 0.5)
    ctx.arc(toggle_radius, toggle_radius, toggle_radius, 0, 2*math.pi)
    ctx.fill()

    surface.write_to_png(os.path.join("res", "pics", "red_toggle_button.png"))

def gen_arrow(width, height):
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, int(width), int(height))
    ctx = cairo.Context(surface)

    ctx.set_source_rgb(1.0, 1.0, 0.0)
    ctx.move_to(0.0, 0.0)
    ctx.line_to(width, height/2.0)
    ctx.line_to(0.0, height)
    ctx.line_to(0.0, 0.0)
    ctx.fill()

    surface.write_to_png(os.path.join("res", "pics", "game_nav_arrow.png"))

def gen_game_nav_json(base_radius, toggle_radius, arrow_width, arrow_height):
    nav_json = {
        "baseRadius": base_radius,
        "toggleRadius": toggle_radius,
        "arrowRadius": base_radius,
        "alpha": 0.6,
        "baseTexture": "base_navigator.png",
        "toggleButtons": ["green_toggle_button.png", "red_toggle_button.png"],
        "arrowTexture": "game_nav_arrow.png",
        "arrowWidth": arrow_width,
        "arrowHeight": arrow_height,
    }

    with open(os.path.join("config", "game_navigator_config.json"), "w") as f:
        json.dump(nav_json, f, indent=4)

@click.command()
@click.argument("base-radius", type=float, required=True)
def main(base_radius):
    toggle_radius = base_radius / 3.0
    arrow_width = base_radius / 5.0
    arrow_height = 2 * arrow_width

    gen_base_navigator(base_radius, toggle_radius)
    gen_toggle_buttons(toggle_radius)
    gen_arrow(arrow_width, arrow_height)
    gen_game_nav_json(base_radius, toggle_radius, arrow_width, arrow_height)

if __name__ == "__main__":
    main()

