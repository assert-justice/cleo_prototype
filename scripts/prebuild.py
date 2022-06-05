import os

def format_script(fname, text : str):
    chars = [str(ord(c)) for c in text]
    chars.append("0") # zero terminated strings baybeee
    chars = ",".join(chars)
    chars = "{" + chars + "}"
    return f"static const char {fname}_script[] = {chars};"

def get_files(dir, ext):
    out = []
    for root, _, files in os.walk(dir):
        for name in files:
            path = os.path.join(root, name)
            name, f_ext = os.path.splitext(name)
            if f_ext == f".{ext}":
                out.append((path,name))
    return out

# Build include files based on wren sourcecode

def generate_includes(script_dir, include_name : str, ext, ):
    include_dir = os.path.join("src",f"{include_name}.h")
    lines = []
    for path, name in get_files(script_dir, ext):
        with open(path) as src_file:
            lines.append(format_script(name, src_file.read()))
    lines = "\n".join(lines)
    with open(include_dir, "w") as include_f:
        include_f.write(
            f'''#ifndef {include_name.upper()}
#define {include_name.upper()}
{lines}
#endif
''')

if __name__ == "__main__":
    generate_includes("wren_scripts", "wren_inc", "wren")
    generate_includes("shaders", "shader_inc", "glsl")