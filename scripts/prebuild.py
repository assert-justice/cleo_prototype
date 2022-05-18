import os

def template(fname, ext, text : str):
    lines = [f'"{line}\\n"' for line in text.splitlines()]
    lines = "\n".join(lines)
    return f'''// Generated automatically from {fname + ext}. Do not edit.
static const char* {fname} =
{lines};
'''

def get_files():
    out = []
    for root, _, files in os.walk("wren_scripts"):
        for name in files:
            path = os.path.join(root, name)
            name, ext = os.path.splitext(name)
            if ext == ".wren":
                out.append((path,name,ext,))
    return out

# Build include files based on wren sourcecode

def generate_includes():
    # script_dir = os.path.join("wren_scripts")
    include_dir = os.path.join("src","wren_scripts")
    for path, name, ext in get_files():
        with open(path) as script_f:
            with open(os.path.join(include_dir, name + ext + ".inc"), "w") as include_f:
                text = template(name, ext, script_f.read())
                include_f.write(text)
    # scripts = [fname for fname in os.scandir(script_dir) if os.path.splitext(fname)[1] == ".wren"]
    # for script in scripts:
    #     with open(os.path.join(script_dir, script.name)) as script_f:
    #         with open(os.path.join(include_dir, script.name + ".inc"), "w") as include_f:
    #             text = template(script.name, script_f.read())
    #             include_f.write(text)

if __name__ == "__main__":
    generate_includes()