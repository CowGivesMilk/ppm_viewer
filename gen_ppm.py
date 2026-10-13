import math
import random
def radial_rainbow(filename, width, height):
    cx, cy = width / 2, height / 2
    with open(filename, "w") as f:
        f.write(f"P3\n{width} {height}\n255\n")
        for y in range(height):
            for x in range(width):
                dx, dy = x - cx, y - cy
                angle = math.atan2(dy, dx)          # -pi..pi
                dist  = math.hypot(dx, dy) / math.hypot(cx, cy)
                # HSV -> RGB (simplified)
                h = (angle + math.pi) / (2 * math.pi)
                s, v = 1.0, 1.0 - 0.6 * dist
                i = int(h * 6)
                fq = h * 6 - i
                p, q, t = v*(1-s), v*(1-s*fq), v*(1-s*(1-fq))
                rgb = [(v,t,p),(q,v,p),(p,v,t),(p,q,v),(t,p,v),(v,p,q)][i % 6]
                f.write(f"{int(rgb[0]*255)} {int(rgb[1]*255)} {int(rgb[2]*255)}\n")
def mandelbrot_set(filename, width, height, max_iter=100):
    def clamp(v):
        return max(0, min(255, int(v)))

    with open(filename, "w") as f:
        f.write(f"P3\n{width} {height}\n255\n")
        for y in range(height):
            for x in range(width):
                cr = (x / width) * 3.5 - 2.5
                ci = (y / height) * 2.0 - 1.0
                zr = zi = 0.0
                i = 0
                while zr*zr + zi*zi < 4 and i < max_iter:
                    zr, zi = zr*zr - zi*zi + cr, 2*zr*zi + ci
                    i += 1

                if i == max_iter:
                    r = g = b = 0
                else:
                    t = i / max_iter
                    # classic smooth palette
                    r = 9  * (1 - t) * t**3 * 255
                    g = 15 * (1 - t)**2 * t**2 * 255
                    b = 8.5 * (1 - t)**3 * t * 255

                f.write(f"{clamp(r)} {clamp(g)} {clamp(b)}\n")

def perlin_style_smooth_noise(filename, width, height, cell=32):
    gw, gh = width // cell + 2, height // cell + 2
    grid = [[random.random() for _ in range(gw)] for _ in range(gh)]
    def lerp(a, b, t): return a + (b - a) * t
    with open(filename, "w") as f:
        f.write(f"P3\n{width} {height}\n255\n")
        for y in range(height):
            for x in range(width):
                gx, gy = x / cell, y / cell
                x0, y0 = int(gx), int(gy)
                fx, fy = gx - x0, gy - y0
                # smoothstep
                fx = fx*fx*(3-2*fx); fy = fy*fy*(3-2*fy)
                v = lerp(lerp(grid[y0][x0],   grid[y0][x0+1],   fx),
                         lerp(grid[y0+1][x0], grid[y0+1][x0+1], fx), fy)
                c = int(v * 255)
                f.write(f"{c} {c} {c}\n")
                
mandelbrot_set("image.ppm", 1920, 1080)