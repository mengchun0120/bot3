import click

width = click.option("-w",
                     "--width",
                     type=float,
                     required=True,
                     help="Width of the progress bar")

height = click.option("-h",
                      "--height",
                      type=float,
                      required=True,
                      help="Height of the progress bar")

num_blocks = click.option("-n",
                          "--num-blocks",
                          type=int,
                          required=True,
                          help="Number of blocks")

has_texture = click.option("-t",
                           "--has-texture",
                           type=bool,
                           default=False,
                           required=False,
                           help="Whether to include texture coordinates")

prefix = click.option("-p",
                      "--prefix",
                      type=str,
                      required=True,
                      help="Prefix of output file")

def validate_params(width, height, num_blocks):
    if width <= 0.0:
        print("width must be greater than zero")
        exit(1)
    if height <= 0.0:
        print("height must be greater than zero")
        exit(1)
    if num_blocks < 1:
        print("num_blocks must be greater than zero")
        exit(1)

def gen_data(width, height, num_blocks, has_texture):
    delta_x = width / num_blocks
    delta_tex_x = 1.0 / num_blocks
    positions = [
        (0.0, 0.0),
        (0.0, height),
        (delta_x, 0.0),
        (delta_x, height)
    ]

    if has_texture:
        texture_coords = [
            (0.0, 0.0),
            (0.0, 1.0),
            (delta_tex_x, 0.0),
            (delta_tex_x, 1.0)
        ]
    else:
        texture_coords = []

    x = delta_x
    tex_x = delta_tex_x
    for _ in range(1, num_blocks):
        x += delta_x
        tex_x += delta_tex_x
        positions.extend([(x, 0.0), (x, height)])
        if has_texture:
            texture_coords.extend([(tex_x, 0.0), (tex_x, 1.0)])

    return positions, texture_coords

def write_data(prefix, positions, texture_coords):
    with open(f"{prefix}_pos.txt", "w") as f:
        for pos in positions:
            f.write(f"{pos[0]} {pos[1]}\n")

    if len(texture_coords) > 0:
        with open(f"{prefix}_tex.txt", "w") as f:
            for coord in texture_coords:
                f.write(f"{coord[0]} {coord[1]}\n")

@click.command()
@width
@height
@num_blocks
@has_texture
@prefix
def gen_progress_bar(width, height, num_blocks, has_texture, prefix):
    validate_params(width, height, num_blocks)
    positions, texture_coords = gen_data(width, height, num_blocks, has_texture)
    write_data(prefix, positions, texture_coords)

if __name__ == "__main__":
    gen_progress_bar()

