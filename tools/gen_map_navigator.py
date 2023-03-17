import click
import cairo
import math
import numpy as np

def draw_triangle(ctx, triangle):
    ctx.move_to(triangle[0][0], triangle[0][1])
    for k in range(1,4):
        next_idx = k if k < 3 else 0
        ctx.line_to(triangle[next_idx][0], triangle[next_idx][1])
    ctx.fill()

def rotate_matrix(angle):
    cos_angle = math.cos(angle)
    sin_angle = math.sin(angle)
    return [
        [cos_angle, sin_angle],
        [-sin_angle, cos_angle]
    ]

def draw_base(ctx, radius, center):
    ctx.set_source_rgb(0, 0.8, 0)
    ctx.arc(center[0], center[1], radius, 0, 2*math.pi)
    ctx.fill()


def draw_arrows(ctx, radius, center):
    ctx.set_source_rgb(0.6, 1.0, 0.6)

    arrow_bottom = 2.0 * radius / 3.0
    arrow_top = arrow_bottom + radius/4.0
    arrow_height = 0.4 * radius

    arrow = [
        [arrow_bottom, arrow_height],
        [arrow_bottom, -arrow_height],
        [arrow_top, 0.0],
    ]
    rotation = rotate_matrix(math.pi/2.0)

    for i in range(4):
        draw_triangle(ctx, np.add(arrow, center))
        if i < 3:
            arrow = np.dot(arrow, rotation)

def draw_lines(ctx, radius, center):
    ctx.set_source_rgb(0, 0.3, 0)

    start = [radius * math.cos(math.pi/4.0), radius * math.sin(math.pi/4.0)]
    end = np.dot(-1.0, start)
    line = [start, end]
    rotation = rotate_matrix(math.pi/2.0)

    for i in range(2):
        points = np.add(line, center)
        ctx.move_to(points[0][0], points[0][1])
        ctx.line_to(points[1][0], points[1][1])
        ctx.stroke()

        if i < 1:
            line = np.dot(line, rotation)

@click.command()
@click.argument("file-name", type=str, required=True)
@click.argument("radius", type=int, required=True)
def gen_map_navigator(file_name, radius):
    width = 2 * radius
    height = 2 * radius
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx = cairo.Context(surface)
    ctx.set_line_width(1.0)
    center = [radius, radius]

    draw_base(ctx, radius, center)
    draw_arrows(ctx, radius, center)
    draw_lines(ctx, radius, center)

    surface.write_to_png(file_name)

if __name__ == "__main__":
    gen_map_navigator()
