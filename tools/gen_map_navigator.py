import click
import cairo
import math
import json
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

def gen_map_navigator_png(radius):
    width = 2 * radius
    height = 2 * radius
    surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, width, height)
    ctx = cairo.Context(surface)
    ctx.set_line_width(1.0)
    center = [radius, radius]

    draw_base(ctx, radius, center)
    draw_arrows(ctx, radius, center)
    draw_lines(ctx, radius, center)

    surface.write_to_png("map_navigator.png")

def gen_vertex_array(radius):
    x = radius * math.sqrt(2.0) / 2.0
    y = x
    triangle = np.array([
        [0.0, 0.0],
        [x, y],
        [x, -y],
    ])
    results = [triangle]
    rotation = rotate_matrix(math.pi/2.0)
    for i in range(3):
        triangle = np.dot(triangle, rotation)
        results.append(triangle)
    return results

def gen_tex_pos_array():
    center = np.array([0.5,0.5])
    triangle = np.array([
        [0.0, 0.0],
        [0.5, 0.5],
        [0.5, -0.5],
    ])
    results = [triangle+center]
    rotation = rotate_matrix(math.pi/2.0)
    for i in range(3):
        triangle = np.dot(triangle, rotation)
        results.append(triangle+center)
    return results

def gen_map_navigator_json(vertex_array, tex_pos_array, radius):
    va = []
    result = {
        "texture": "map_navigator",
        "radius": float(radius),
        "vertexArray": va,
    }
    for i in range(4):
        va.append([
            vertex_array[i].tolist(),
            tex_pos_array[i].tolist()
        ])
    with open("map_navigator_config.json", "w") as f:
        json.dump(result, f, indent=4)

@click.command()
@click.argument("radius", type=int, required=True)
def main(radius):
    gen_map_navigator_png(radius)
    vertex_array = gen_vertex_array(radius)
    tex_pos_array = gen_tex_pos_array()
    gen_map_navigator_json(vertex_array, tex_pos_array, radius)

if __name__ == "__main__":
    main()
