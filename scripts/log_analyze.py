import sys, math
def main(fname):
    with open(fname) as f:
        lines = f.read().splitlines()
        # num, min, max, avg
        render_stats = [0.0,math.inf,0.0,0.0]
        script_stats = [0.0,math.inf,0.0,0.0]
        for line in lines:
            line = line.split(" ")
            dur = float(line[4])
            if line[0] == "RENDER":
                stats = render_stats
            else:
                stats = script_stats
            stats[0] += 1
            if dur < stats[1]:
                stats[1] = dur
            if dur > stats[2]:
                stats[2] = dur
            stats[3] += dur
        render_stats[3] /= render_stats[0]
        script_stats[3] /= script_stats[0]
        print(f'''render stats
min frame time: {render_stats[1]} 
max frame time: {render_stats[2]} 
avg frame time: {render_stats[3]} 
script stats
min script time: {script_stats[1]} 
max script time: {script_stats[2]} 
avg script time: {script_stats[3]} 
        ''')


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("log analyze requires a filename")
    else:
        main(sys.argv[1])