import click

def gen_dashed_line(solid_length, dash_spacing, total_length):
    points = []
    start_x = 0.0
    while start_x <= total_length:
        end_x = start_x + solid_length
        if end_x >= total_length:
            end_x = total_length
        points.append((start_x, 0.0))
        points.append((end_x, 0.0))
        start_x = end_x + dash_spacing

    return points

def write_points_to_file(points, output_file):
    with open(output_file, "w") as f:
        for p in points:
            f.write(f"{p[0]} {p[1]}\n")

@click.command()
@click.argument("solid-length", type=float, required=True)
@click.argument("dash-spacing", type=float, required=True)
@click.argument("total-length", type=float, required=True)
@click.argument("output-file", type=str, required=True)
def main(solid_length, dash_spacing, total_length, output_file):
    points = gen_dashed_line(solid_length, dash_spacing, total_length)
    write_points_to_file(points, output_file)

if __name__ == "__main__":
    main()
