import click
import math

def to_radius(degree):
    return degree * math.pi / 180.0

def gen_dashed_circle(theta_1, theta_2, radius):
    points = []

    dash_start_angle = 0.0
    end_angle = 2.0 * math.pi

    while dash_start_angle < end_angle:
        dash_end_angle = dash_start_angle + theta_1
        if dash_end_angle > end_angle:
            dash_end_angle = end_angle

        dash_start_x = radius * math.cos(dash_start_angle)
        dash_start_y = radius * math.sin(dash_start_angle)
        points.append((dash_start_x, dash_start_y))

        dash_end_x = radius * math.cos(dash_end_angle)
        dash_end_y = radius * math.sin(dash_end_angle)
        points.append((dash_end_x, dash_end_y))

        dash_start_angle = dash_end_angle + theta_2

    return points

def write_points_to_file(points, output_file):
    with open(output_file, "w") as f:
        for x, y in points:
            f.write(f"{x} {y}\n")

@click.command()
@click.argument("theta-1", type=float, required=True)
@click.argument("theta-2", type=float, required=True)
@click.argument("radius", type=float, required=True)
@click.argument("output-file", type=str, required=True)
def main(theta_1, theta_2, radius, output_file):
    points = gen_dashed_circle(to_radius(theta_1), to_radius(theta_2), radius)
    write_points_to_file(points, output_file)

if __name__ == "__main__":
    main()

