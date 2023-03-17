import click
import cairo
from math import pi

@click.command()
@click.argument("file-name", type=str, required=True)
@click.argument("radius", type=int, required=True)
def gen_map_navigator(file_name, radius):
    width = 2 * radius
    height = 2 * radius
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx = cairo.Context(surface)
    ctx.set_line_width(0.04)
    ctx.set_source_rgb(0, 0.8, 0)
    ctx.arc(radius, radius, radius, 0, 2*pi)
    ctx.fill()
    surface.write_to_png(file_name)

if __name__ == "__main__":
    gen_map_navigator()
