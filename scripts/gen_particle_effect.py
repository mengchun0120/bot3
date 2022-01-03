import sys
import argparse
import random
import math
import json

def write_scalar_list(outputList, fileName):
    with open(fileName, "w") as f:
        for i in outputList:
            f.write(f"{i}\n")

def write_vector_list(outputList, fileName):
    with open(fileName, "w") as f:
        for i in outputList:
            for k in i:
                f.write(f"{k} ")
            f.write("\n")

def gen_effects(numParticles, startRadius, minSpeed, maxSpeed,
                randomDirection, prefix):
    startPosList = []
    directionList = []
    initSpeedList = []
    incr = 2.0*math.pi / numParticles

    for i in range(numParticles):
        if randomDirection:
            theta = random.uniform(0.0, 2.0*math.pi)
        else:
            theta = i*incr

        direction = [math.cos(theta), math.sin(theta)]
        directionList.append(direction)

        radius = random.uniform(0.0, startRadius)
        startPosList.append([radius*direction[0], radius*direction[1]])

        initSpeedList.append(random.uniform(minSpeed, maxSpeed))

    write_vector_list(startPosList, f"{prefix}_start_pos.txt")
    write_vector_list(directionList, f"{prefix}_direction.txt")
    write_scalar_list(initSpeedList, f"{prefix}_init_speed.txt")

def main():
    parser = argparse.ArgumentParser(description="Generate particle effect")
    parser.add_argument("-n", "--numParticles", type=int, required=True,
                        help="Num of particles")
    parser.add_argument("-s", "--startRadius", type=float, default=0.0,
                        help="Starting radius")
    parser.add_argument("-m", "--minSpeed", type=float, default=0.0,
                        help="Minimum speed")
    parser.add_argument("-M", "--maxSpeed", type=float, required=True,
                        help="Maximum speed")
    parser.add_argument("-r", "--randomDirection", action="store_true",
                        help="Generate directions randomly")
    parser.add_argument("-p", "--prefix", type=str, required=True,
                        help="Prefix of output file")

    args = parser.parse_args()

    gen_effects(args.numParticles, args.startRadius, args.minSpeed, args.maxSpeed,
                args.randomDirection, args.prefix)

if __name__ == "__main__":
    main()

