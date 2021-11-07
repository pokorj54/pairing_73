import subprocess


def get_all_points():
    res = []
    for i in range(7):
        for j in range(7):  
            for k in range(7):
                res.append(str(i)+str(j)+str(k))
    return res

def check_play(points):
    proc_board = subprocess.run(["./exe/determine_board_pc", *points], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    board = proc_board.stdout.decode('utf-8').strip()
    if proc_board.returncode != 0:
        return
    proc_selector = subprocess.run(["./exe/position_selector", board], stdout=subprocess.PIPE)
    if proc_selector.returncode != 0:
        print('selector', proc_selector.stderr.decode('utf-8'), points, board)
        return
    byte_solution = proc_selector.stdout
    proc_verifier = subprocess.Popen(["./exe/verifier"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    proc_verifier.stdin.write(byte_solution)
    verifier_output = proc_verifier.communicate()[0]
    proc_verifier.stdin.close()

    if proc_verifier.returncode != 0:
        print('veifier', verifier_output.decode('utf-8'), points, board)
        return 


def main():
    all_points = get_all_points()

    for a in all_points:
        print(a)
        if(a == '333'):
            continue
        for b in all_points:
            print(a, b)
            for c in all_points:
                check_play([a,b,c])
                check_play(['333',a,b,c])
    print("done")


if __name__ == '__main__':
    main()