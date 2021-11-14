import subprocess
import sys


def get_all_points():
    res = []
    for i in range(7):
        for j in range(7):  
            for k in range(7):
                res.append(str(i)+str(j)+str(k))
    return res

def get_solution_from_db(points):
    proc_board = subprocess.run(["./exe/determine_board_pc", *points], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    board = proc_board.stdout.decode('utf-8').strip()
    if proc_board.returncode != 0:
        return
    proc_selector = subprocess.run(["./exe/position_selector", board], stdout=subprocess.PIPE)
    if proc_selector.returncode != 0:
        print('selector', proc_selector.stderr.decode('utf-8'), points, board)
        return
    byte_solution = proc_selector.stdout
    return byte_solution


def calculate_solution(points):
    proc_calculate_strategy = subprocess.run(["./exe/calculate_strategy", *points], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    solution = proc_calculate_strategy.stdout
    
    # 0 is success, 1 is invalid arguments, 2 means the solution was not found
    if proc_calculate_strategy.returncode == 1: # this is ok
        return
    if proc_calculate_strategy.returncode == 2: # this is not ok
        print('calculate_strategy', solution, points)
        return
    return solution



def check_play(points, get_solution):
    byte_solution =  get_solution(points)
    if byte_solution is None:
        return
    proc_verifier = subprocess.Popen(["./exe/verifier"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    proc_verifier.stdin.write(byte_solution)
    verifier_output = proc_verifier.communicate()[0]
    proc_verifier.stdin.close()

    if proc_verifier.returncode != 0:
        print('veifier', verifier_output.decode('utf-8'), points, byte_solution)
        return 


def main():
    all_points = get_all_points()
    get_solution = get_solution_from_db if sys.argv[1] in {'DB', 'db', 'database'} else  calculate_solution
    for a in all_points:
        print(a)
        if(a == '333'):
            continue
        for b in all_points:
            print(a, b)
            for c in all_points:
                check_play([a,b,c], get_solution)
                check_play(['333',a,b,c], get_solution)
    print("done")


if __name__ == '__main__':
    if len(sys.argv )== 1:
        print('Expected one argument either DB or calculate')
        exit(1)
    elif sys.argv[1] not in {'DB', 'db', 'database', 'calc', 'calculate'}:
        print('Argument has to be one of ', {'DB', 'db', 'database', 'calc', 'calculate'})
        exit(1)
    main()