import subprocess


def get_all_points():
    res = []
    for i in range(7):
        for j in range(7):  
            for k in range(7):
                res.append(str(i)+str(j)+str(k))
    return res

def check_play(points):
    subprocess.run(['ls', '-l'], stdout=subprocess.PIPE).stdout.decode('utf-8')


all_points = get_all_points()




for a in all_points:
    print(a)
    if(a == '333'):
        continue
    for b in all_points:
        for c in all_points:
            check_play([a,b,c])
            check_play(['333',a,b,c])
