import random
import math
from collections import namedtuple
import matplotlib.pyplot as plt


Point = namedtuple('Point', ['x', 'y'])

def generate_random_points_inside_square(num_points, square_size):
    points = []
    for _ in range(num_points):
        p = Point(random.uniform(0, square_size), random.uniform(0, square_size))
        points.append(p)
    return points

def generate_random_points_in_circle(num_points, radius):
    points = []
    for _ in range(num_points):
        angle = random.uniform(0, 2 * math.pi)
        r = random.uniform(0, radius)
        p = Point(r * math.cos(angle), r * math.sin(angle))
        points.append(p)
    return points

from math import atan2

def convex_hull(points_o, stack):
    points = [p for p in points_o if p not in stack]
    
    if not points:
        return stack

    lowest_point = min(points, key=lambda p: p.y)
    points.remove(lowest_point)
    
    points.sort(key=lambda p: atan2(p.y - lowest_point.y, p.x - lowest_point.x))
    points.insert(0, lowest_point)
    
    stack.append(points[0])
    if len(points) < 2:
        return stack
    stack.append(points[1])
    
    for i in range(2, len(points)):
        c = points[i]
        
        while len(stack) >= 2:
            b = stack.pop()
            a = stack[-1]
            
            ab = (b.x - a.x, b.y - a.y)
            ac = (c.x - a.x, c.y - a.y)
            cross_product = ab[0] * ac[1] - ab[1] * ac[0]
            
            if cross_product > 0:
                stack.append(b)
                break
        
        stack.append(c)
    
    return stack

def count_rings(points):
    count = 0
    con_hull = []
    while (len(points) != len(con_hull)):
        con_hull = convex_hull(points, con_hull)
        count += 1
    return count

def count_points_inside_square(n):
    points = generate_random_points_inside_square(n, 100)
    total_points = count_rings(points)
    return total_points

def count_points_inside_circle(n):
    points = generate_random_points_in_circle(n, 100)
    total_points = count_rings(points)
    return total_points

def task1_4():
    x = []
    y1 = []
    y2 = []
    yMean = []

    for i in range(10, 1001, 10):
        x.append(i)
        y1.append(n1 := count_points_inside_square(i))
        y2.append(n2 := count_points_inside_circle(i))
        yMean.append((n1 + n2) / 2)

    plt.scatter(x, y1, color='blue', marker='o', label="квадрат")
    plt.scatter(x, y2, color='blueviolet', marker='o', label="окружность")
    plt.plot(x, yMean, color='red', marker='o', label="среднее")
    plt.legend()
    plt.savefig("graph1_4.png", bbox_inches='tight', dpi=300)
    plt.show()


    data = list(zip(x, y1, y2, yMean))
    columns = ["num_points", "square", "circle", "mean"]

    fig, ax = plt.subplots(figsize=(10, 6))
    ax.axis('tight')
    ax.axis('off')

    table = ax.table(cellText=data, colLabels=columns, cellLoc='center', loc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1, 1)
    plt.savefig("table1_4.png", bbox_inches='tight', dpi=300)
    plt.show()

task1_4()
