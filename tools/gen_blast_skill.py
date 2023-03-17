import argparse
import math

def write_vector_list(outputList, fileName):
    with open(fileName, "w") as f:
        for i in outputList:
            for k in i:
                f.write(f"{k} ")
            f.write("\n")

def gen_blast_skill(numFirePos, radius, prefix):
    if numFirePos < 1:
        print(f"numFirePos must be greater than zero")
        exit(1)

    firePoints = []
    fireDirections = []
    theta = 0.0
    delta = 2.0*math.pi / numFirePos

    for i in range(numFirePos):
        direction = [math.cos(theta), math.sin(theta)]
        fireDirections.append(direction)

        pos = [radius*direction[0], radius*direction[1]]
        firePoints.append(pos)

        theta += delta

    write_vector_list(firePoints, f"{prefix}_fire_pos.txt")
    write_vector_list(fireDirections, f"{prefix}_fire_direction.txt")

def main():
    parser = argparse.ArgumentParser(description="Generate blast skill data")
    parser.add_argument("-n", "--numFirePos", type=int, required=True,
                        help="Num of fire points")
    parser.add_argument("-r", "--radius", type=float, required=True,
                        help="radius")
    parser.add_argument("-p", "--prefix", type=str, required=True,
                        help="Prefix of output file")

    args = parser.parse_args()

    gen_blast_skill(args.numFirePos, args.radius, args.prefix)

if __name__ == "__main__":
    main()

