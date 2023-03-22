import click
import json
import cairo
import math
import os

def gen_game_navigator(radius):
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, int(2*radius), int(2*radius))
    ctx = cairo.Context(surface)

    ctx.set_source_rgb(0.0, 1.0, 0.0)
    ctx.arc(radius, radius, radius, 0, 2*math.pi)
    ctx.fill()

    ctx.set_source_rgb(1.0, 0.0, 0.0)
    ctx.arc(radius, radius, radius/3.0, 0, 2*math.pi)
    ctx.fill()

    surface.write_to_png(os.path.join("res", "pics", "game_navigator.png"))

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

def gen_game_nav_json(radius, arrow_width, arrow_height):
    nav_json = {
        "baseRadius": radius,
        "stopRadius": radius/3.0,
        "arrowRadius": radius,
        "alpha": 0.6,
        "baseTexture": "game_navigator.png",
        "arrowTexture": "game_nav_arrow.png",
        "baseWidth": 2.0*radius,
        "baseHeight": 2.0*radius,
        "arrowWidth": arrow_width,
        "arrowHeight": arrow_height,
    }

    with open(os.path.join("config", "game_navigator_config.json"), "w") as f:
        json.dump(nav_json, f, indent=4)

@click.command()
@click.argument("radius", type=float, required=True)
def main(radius):
    arrow_width = radius / 5.0
    arrow_height = 2 * arrow_width
    gen_game_navigator(radius)
    gen_arrow(arrow_width, arrow_height)
    gen_game_nav_json(radius, arrow_width, arrow_height)

if __name__ == "__main__":
    main()

