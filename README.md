# PNG Text Image Generator (C++)

## Description
A simple C++ program that generates a PNG image and draws text by manually changing pixel colors.  
It uses predefined 5×5 patterns to render characters in a block-style format using the libpng library.


## Preview
![Output](out.png.png)



## Features
- Generate PNG images from scratch  
- Draw text using pixel-level manipulation  
- Uses simple 5×5 grid patterns for characters  
- Supports characters: **H, E, L, O**  
- Customizable spacing, size, and colors  
- Lightweight and efficient  



## Tech Stack
- **Language:** C++  
- **Library:** libpng  



## How It Works
- Each character is represented using a **5×5 matrix pattern**  
- `1` → filled pixel block  
- `0` → background  
- The program reads input text from command-line arguments  
- Maps each character to its pattern  
- Colors pixels accordingly to form letters  
- Saves the final image as a PNG file  


