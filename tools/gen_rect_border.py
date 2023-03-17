import click

width = click.option("-w",
                     "--width",
                     type=float,
                     required=True,
                     help="Width of the rectangle")

height = click.option("-h",
                      "--height",
                      type=float,
                      required=True,
                      help="Height of the rectangle")

has_texture = click.option("-t",
                           "--has-texture",
                           default=False,
                           type=bool,
                           required=False,
                           help="Whether to generate texture coordinates")

prefix = click.option("-p",
                      "--prefix",
                      type=str,
                      required=True,
                      help="Prefix of the output file")

def validate_param(width, height):
    if width <= 0.0:
        print("width must be positive")
        exit(1)
    if height <= 0.0:
        print("height must be positive")
        exit(1)

def gen_data(width, height, has_texture):
    pos_data = [(0.0, 0.0), (0.0, height), (width, height), (width, 0.0)]
    if has_texture:
        tex_data = [(0.0, 0.0), (0.0, 1.0), (1.0, 1.0), (1.0, 0.0)]
    else:
        tex_data = None
    return pos_data, tex_data

def write_vertices(file_name, vertices):
    with open(file_name, "w") as f:
        for x, y in vertices:
            f.write(f"{x} {y}\n")

def write_data(prefix, pos_data, tex_data):
    write_vertices(f"{prefix}_pos.txt", pos_data)
    if tex_data is not None:
        write_vertices(f"{prefix}_tex.txt", tex_data)

@click.command()
@width
@height
@has_texture
@prefix
def gen_rect(width, height, has_texture, prefix):
    validate_param(width, height)
    pos_data, tex_data = gen_data(width, height, has_texture)
    write_data(prefix, pos_data, tex_data)

if __name__ == "__main__":
    gen_rect()
