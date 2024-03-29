import os
import click
import math

start_angle = click.option("-s",
                           "--start-angle",
                           default=0.0,
                           type=float,
                           required=True,
                           help="Start angle")

clockwise = click.option("-c",
                         "--clockwise",
                         default=False,
                         type=bool,
                         required=True,
                         help="Generate circle clockwise or not")

radius = click.option("-r",
                      "--radius",
                      default=1.0,
                      type=float,
                      required=True,
                      help="Radius of the circle")

num_edges = click.option("-n",
                         "--num-edges",
                         default=100,
                         type=int,
                         required=True,
                         help="Number of edges")

has_texture = click.option("-t",
                           "--has-texture",
                           default=False,
                           type=bool,
                           required=True,
                           help="Whether to include texture coordinates")

prefix = click.option("-p",
                      "--prefix",
                      default="circle",
                      type=str,
                      required=True,
                      help="Prefix of output file")

def validate_params(radius, num_edges):
    if radius <= 0.0:
        print("radius must be greater than zero")
        exit(1)
    if num_edges < 3:
        print("num_edges must be greater than 3")
        exit(1)

def gen_data(start_angle, clockwise, radius, num_edges, has_texture):
    positions = []
    texture_coords = []

    delta = 2.0 * math.pi / num_edges
    if clockwise:
        delta = -delta

    theta = start_angle * math.pi / 180.0
    cos_theta = math.cos(theta)
    sin_theta = math.sin(theta)

    prev_x = radius * cos_theta
    prev_y = radius * sin_theta
    prev_tex_x = 0.5 + 0.5 * cos_theta
    prev_tex_y = 0.5 + 0.5 * sin_theta

    theta += delta

    for _ in range(num_edges):
        cos_theta = math.cos(theta)
        sin_theta = math.sin(theta)

        x = radius * cos_theta
        y = radius * sin_theta

        positions.append((prev_x, prev_y))
        positions.append((x, y))
        positions.append((0.0, 0.0))

        prev_x = x
        prev_y = y

        if has_texture:
            tex_x = 0.5 + 0.5 * cos_theta
            tex_y = 0.5 + 0.5 * sin_theta

            texture_coords.append((prev_tex_x, prev_tex_y))
            texture_coords.append((tex_x, tex_y))
            texture_coords.append((0.5, 0.5))

            prev_tex_x = tex_x
            prev_tex_y = tex_y

        theta += delta

    return positions, texture_coords

def write_data(prefix, positions, texture_coords):
    data_dir = os.path.join("res", "libs", "vertex_array_data")
    pos_data_path = os.path.join(data_dir, f"{prefix}_pos.txt")
    with open(pos_data_path, "w") as f:
        for pos in positions:
            f.write(f"{pos[0]} {pos[1]}\n")

    if len(texture_coords) > 0:
        tex_data_path = os.path.join(data_dir, f"{prefix}_tex.txt")
        with open(tex_data_path, "w") as f:
            for coord in texture_coords:
                f.write(f"{coord[0]} {coord[1]}\n")

@click.command()
@start_angle
@clockwise
@radius
@num_edges
@has_texture
@prefix
def gen_circle(start_angle, clockwise, radius, num_edges, has_texture, prefix):
    validate_params(radius, num_edges)
    positions, texture_coords = gen_data(start_angle, clockwise,
                                         radius, num_edges, has_texture)
    write_data(prefix, positions, texture_coords)

if __name__ == "__main__":
    gen_circle()

