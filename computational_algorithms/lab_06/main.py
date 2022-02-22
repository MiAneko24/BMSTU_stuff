def one_side_diff_single(x, y, h, i):
    diff = 0
    if (i + h >= len(y)):
        diff = (y[i] - y[i - h]) / (x[i] - x[i - h])
    else:
        diff = (y[i + h] - y[i]) / (x[i + h] - x[i])
    return diff


def one_side_diff(x, y, h):
    diff = []
    # h = x[1] - x[0]
    for i in range(len(y) - 1):
        diff.append((y[i + 1] - y[i]) / h)
    diff.append((y[-1] - y[-2]) / h)
    return diff

def center_diff(x, y):
    h = x[1] - x[0]
    diff = []
    diff.append((-3 * y[0] + 4 * y[1] - y[2]) / (2 * h))
    for i in range(1, len(y) -1):
        diff.append((y[i + 1] - y[i - 1]) / (2 * h))
    diff.append((y[-3] - 4 * y[-2] + 3 * y[-1]) / (2 * h))
    return diff

def second_Runge(x, y):
    h = x[1] - x[0]
    m = 2
    p = 1
    diff = []
    for i in range(len(y)):
        diff.append(one_side_diff_single(x, y, h, i) + (one_side_diff_single(x, y, h, i) - one_side_diff_single(x, y, m * h, i)) / (m ** p - 1))
    return diff

def rounding_variables(x, y):
    ksi = [1 / i for i in x]
    eta = [1 / i for i in y]
    eta_diff = [one_side_diff_single(ksi, eta, 1, i) for i in range(len(ksi))]
    diff = [(eta_diff[i] * (-1 / x[i] ** 2)) / (- 1 / y[i] ** 2) for i in range(len(y))]
    return diff

def second_diff(x, y):
    h = x[1] - x[0]
    diff = []
    diff.append((y[2] - 2 * y[1] + y[0]) / h ** 2)
    for i in range(1, len(y) - 1):
        diff.append((y[i - 1] - 2 * y[i] + y[i + 1]) / h ** 2)
    diff.append((y[-3] - 2 * y[-2] + y[-1]) / h ** 2)
    return diff
    

if __name__ == '__main__':
    y = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]
    x = [1, 2, 3, 4, 5, 6]
    osd = one_side_diff(x, y, 1)
    cd = center_diff(x, y)
    runge = second_Runge(x, y)
    r_var = rounding_variables(x, y)
    sec_d = second_diff(x, y)
    print("┌───────┬───────┬───────┬───────┬───────┬───────┬────────┐")
    print("│   X   │   Y   │   1   │   2   │   3   │   4   │    5   │")
    
    for i in range(len(x)):
        print("├───────┼───────┼───────┼───────┼───────┼───────┼────────┤")
        print("│ {:5.3f} │ {:5.3f} │ {:5.3f} │ {:5.3f} │ {:5.3f} │ {:5.3f} │ {:5.3f} │".format(x[i], \
            y[i], osd[i], cd[i], runge[i], r_var[i], sec_d[i]))
    
    print("└───────┴───────┴───────┴───────┴───────┴───────┴────────┘")
    