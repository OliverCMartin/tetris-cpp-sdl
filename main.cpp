#include <SDL.h>
#include <iostream>
#include <array>
#include <random>

using Board = std::array<std::array<int, 10>, 20>;
constexpr int CELL_SIZE = 48;

struct Piece {
    int x;
    int y;

    int type;
    // 1 = Purple T
    // 2 = Blue Backwards L
    // 3 = Red Backwards Stairs
    // 4 = Yellow Square
    // 5 = Green Stairs
    // 6 = Orange L
    // 7 = Cyan Line

    int rotation;
};

constexpr int T_PIECE[4][4][4] = {
    // Rotation 0
    {
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // Rotation 1
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },

    // Rotation 2
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // Rotation 3
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};


//Backwards Left
constexpr int BL_PIECE[4][4][4] = {
    {
        {2, 0, 0, 0},
        {2, 2, 2, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 2, 2, 0},
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {2, 2, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {2, 2, 0, 0},
        {0, 0, 0, 0}
    }
};

//Backwards stairs
constexpr int BS_PIECE[4][4][4] = {
    {
        {3, 3, 0, 0},
        {0, 3, 3, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 3, 0},
        {0, 3, 3, 0},
        {0, 3, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {3, 3, 0, 0},
        {0, 3, 3, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 3, 0, 0},
        {3, 3, 0, 0},
        {3, 0, 0, 0},
        {0, 0, 0, 0}
    }

};

//O Piece
constexpr int O_PIECE[4][4][4] = {
    {
        {4, 4, 0, 0},
        {4, 4, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {4, 4, 0, 0},
        {4, 4, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {4, 4, 0, 0},
        {4, 4, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {4, 4, 0, 0},
        {4, 4, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

//Stair Piece
constexpr int S_PIECE[4][4][4] = {
    {
        {0, 5, 5, 0},
        {5, 5, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {5, 0, 0, 0},
        {5, 5, 0, 0},
        {0, 5, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 5, 5, 0},
        {5, 5, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {5, 0, 0, 0},
        {5, 5, 0, 0},
        {0, 5, 0, 0},
        {0, 0, 0, 0}
    }

};

//L Piece
constexpr int L_PIECE[4][4][4] = {
    {
        {6, 0, 0, 0},
        {6, 0, 0, 0},
        {6, 6, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {6, 6, 6, 0},
        {6, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {6, 6, 0, 0},
        {0, 6, 0, 0},
        {0, 6, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 6, 0},
        {6, 6, 6, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

//I Piece
constexpr int I_PIECE[4][4][4] = {
    {
        {7, 0, 0, 0},
        {7, 0, 0, 0},
        {7, 0, 0, 0},
        {7, 0, 0, 0}
    },
    {
        {7, 7, 7, 7},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {7, 0, 0, 0},
        {7, 0, 0, 0},
        {7, 0, 0, 0},
        {7, 0, 0, 0}
    },
    {
        {7, 7, 7, 7},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }

};

const int (*get_shape(const Piece& piece))[4]
{
    switch (piece.type)
    {
        case 1: return T_PIECE[piece.rotation];
        case 2: return BL_PIECE[piece.rotation];
        case 3: return BS_PIECE[piece.rotation];
        case 4: return O_PIECE[piece.rotation];
        case 5: return S_PIECE[piece.rotation];
        case 6: return L_PIECE[piece.rotation];
        case 7: return I_PIECE[piece.rotation];
        default: return O_PIECE[0];
    }
}

void get_piece_colour(int type, int& red, int& green, int& blue)
{
    switch (type)
    {
        case 1: // T
            red = 125; green = 0; blue = 125;
            break;

        case 2: // Backwards L
            red = 100; green = 110; blue = 255;
            break;

        case 3: // Backwards stairs
            red = 230; green = 5; blue = 5;
            break;

        case 4: // Square (O)
            red = 250; green = 240; blue = 15;
            break;

        case 5: // Stairs
            red = 0; green = 255; blue = 0;
            break;

        case 6: // L
            red = 255; green = 145; blue = 70;
            break;

        case 7: // Line (I)
            red = 65; green = 255; blue = 255;
            break;

        default:
            red = green = blue = 255;
            break;
    }
}

void draw_cell(SDL_Renderer* renderer,
    int x,
    int y,
    int width,
    int height,
    int red,
    int green,
    int blue)
{
    //Drawing a block
    SDL_Rect block = {
        x,
        y,
        width,
        height
    };

    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderFillRect(renderer, &block);
}

void draw_piece(SDL_Renderer* renderer, const Piece& piece)
{
    const auto shape = get_shape(piece);

    int red;
    int green;
    int blue;

    get_piece_colour(piece.type, red, green, blue);

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (shape[row][col] != 0)
            {
                draw_cell(
                    renderer,
                    (piece.x + col) * CELL_SIZE,
                    (piece.y + row) * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE,
                    red,
                    green,
                    blue
                );
            }
        }
    }
}

Piece spawnPiece() {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 7);

    return{
    4,
    0,
    dist(gen),
    0};
}

bool canMove(const Board& board, const Piece& piece, int dx, int dy) {

    const auto outline = get_shape(piece);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col <4; col++) {
            if (outline[row][col] == 0) {
                continue;
            }

            int newX = piece.x + col + dx;
            int newY = piece.y + row + dy;

            //left wall
            if (newX < 0) {
                return false;
            }

            //right wall
            if (newX >= 10) {
                return false;
            }

            //floor
            if (newY >= 20) {
                return false;
            }

            //existing block
            if (board[newY][newX] != 0) {
                return false;
            }
        }
    }

    return true;

}

void draw_board(const Board& board, SDL_Renderer* renderer)
{
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            // Skip empty cells
            if (board[row][col] == 0)
            {
                continue;
            }

            int red;
            int green;
            int blue;

            get_piece_colour(
                board[row][col],
                red,
                green,
                blue
            );

            draw_cell(
                renderer,
                col * CELL_SIZE,
                row * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE,
                red,
                green,
                blue
            );
        }
    }

}

void lock_Piece(Board& board, const Piece& piece) {
    const auto shape = get_shape(piece);

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++) {

            if (shape[row][col] != 0) {
                board[piece.y + row][piece.x + col] = piece.type;
            }

        }


    }

}



int main()
{
    //Initialise the SDL library
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize SDL\n";
        return -1;
    }

    //Creating the window address
    SDL_Window* window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        480, // Playing area of 480
        960, // Playing area of 960
        0
    );

    //Checking if the window has loaded
    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    //Rendering
    SDL_Renderer* renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
    );

    if (!renderer)
    {
        std::cout << "Failed to create renderer\n";
        return -1;
    }

    Board board = {{
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0,0}}
    }};

    Piece currentPiece = spawnPiece();


    // Permanent window loop
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {

            //If program is closed.
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        if (canMove(board, currentPiece, -1, 0)) {
                            currentPiece.x--;
                        }
                        break;

                    case SDLK_RIGHT:
                        if (canMove(board, currentPiece, 1, 0)) {
                            currentPiece.x++;
                        }
                        break;

                    case SDLK_DOWN:
                        if (canMove(board, currentPiece, 0, 1)) {
                            currentPiece.y++;
                        }
                        else {
                            lock_Piece(board, currentPiece);
                            currentPiece = spawnPiece();
                        }
                        break;

                    case SDLK_UP:
                    {
                        Piece rotatedPiece = currentPiece;

                        rotatedPiece.rotation++;
                        rotatedPiece.rotation %= 4;

                        if (canMove(board, rotatedPiece, 0, 0))
                        {
                            currentPiece.rotation = rotatedPiece.rotation;
                        }

                        break;
                    }
                }
            }
        }


        //Main game process locations

        // Background colour
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        //Drawing a block
        draw_board(board, renderer);
        draw_piece(renderer, currentPiece);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}