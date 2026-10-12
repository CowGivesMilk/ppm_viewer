def generate_ppm(filename, width, height):
    max_color = 255

    with open(filename, "w") as f:
        # PPM header
        f.write("P3\n")
        f.write(f"{width} {height}\n")
        f.write(f"{max_color}\n")

        # Image pixels (RGB)
        for y in range(height):
            for x in range(width):
                # Generate a color gradient
                r = int(255 * x / (width - 1)) if width > 1 else 0
                g = int(255 * y / (height - 1)) if height > 1 else 0
                b = 128

                f.write(f"{r} {g} {b}\n")


# Generate a 100x100 image
generate_ppm("image.ppm", 865, 500)

print("PPM image generated successfully!")