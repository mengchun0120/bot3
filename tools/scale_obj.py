import os
import json
import click

def scale_rect(ratio):
    rect_lib_file = os.path.join("res", "libs", "rect_lib.json")
    with open(rect_lib_file) as f:
        rects = json.load(f)

    for _, rect in rects.items():
        rect["width"] *= ratio
        rect["height"] *= ratio

    with open(rect_lib_file, "w") as f:
        json.dump(rects, f, indent=4)

def scale_obj(obj_json, ratio):
    obj_json["collideBreath"] *= ratio
    if "explodeBreath" in obj_json:
        obj_json["explodeBreath"] *= ratio
    for component in obj_json["components"]:
        component["pos"][0] *= ratio
        component["pos"][1] *= ratio

def scale_player(ratio):
    player_file = os.path.join("res", "libs", "player_template.json")
    with open(player_file) as stream:
        obj = json.load(stream)
    scale_obj(obj, ratio)
    with open(player_file, "w") as stream:
        json.dump(obj, stream, indent=4)

def scale_objs(ratio):
    filenames = [
        os.path.join("res", "libs", "tile_template_lib.json"),
        os.path.join("res", "libs", "missile_template_lib.json"),
        os.path.join("res", "libs", "ai_robot_template_lib.json"),
    ]

    for f in filenames:
        with open(f) as stream:
            objs = json.load(stream)
        for _, obj in objs.items():
            scale_obj(obj, ratio)
        with open(f, "w") as stream:
            json.dump(objs, stream, indent=4)

@click.command()
@click.argument("ratio", type=float, required=True)
def main(ratio):
    scale_rect(ratio)
    scale_objs(ratio)
    scale_player(ratio)

if __name__ == "__main__":
    main()
