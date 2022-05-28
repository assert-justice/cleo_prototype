import os

def format_script(fname, text : str):
    chars = [str(ord(c)) for c in text]
    chars.append("0") # zero terminated strings baybeee
    chars = ",".join(chars)
    chars = "{" + chars + "}"
    return f"static const char {fname}_script[] = {chars};"

# def template(files):
#     lines = 
#     return "// Generated automatically from scripts in wren_scripts. Do not edit."

def get_files():
    out = []
    for root, _, files in os.walk("wren_scripts"):
        for name in files:
            path = os.path.join(root, name)
            name, ext = os.path.splitext(name)
            if ext == ".wren":
                out.append((path,name))
    return out

# Build include files based on wren sourcecode

def generate_includes():
    # script_dir = os.path.join("wren_scripts")
    include_dir = os.path.join("src","wren_inc.h")
    lines = []
    for path, name in get_files():
        with open(path) as src_file:
            lines.append(format_script(name, src_file.read()))
    
    lines = "\n".join(lines)
    with open(include_dir, "w") as include_f:
        include_f.write(
            f'''#ifndef WREN_INC
#define WREN_INC
{lines}
#endif
''')
#             lines = []
#             with open(path) as script_f:
#                 lines.append(format_script(name, script_f.read()))
#             print(len(lines))

if __name__ == "__main__":
    generate_includes()