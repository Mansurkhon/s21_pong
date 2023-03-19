#include <stdio.h>

void cross_and_toe_display(int cross_pos, int toe_pos, int x, int y, int total_points_1, int total_points_2,
                           int l_rocket, int r_rocket, int l_rocket_pos, int r_rocket_pos);
int ball_vector(int x, int vec, int border);
int hit(int x, int y, int vec_x, int l_rocket_pos_x, int r_rocket_pos_x, int l_rocket_pos_y,
        int r_rocket_pos_y);
int player_turn(char command, int flag, int l_rocket_pos_x, int r_rocket_pos_x, int border);

int main() {
    int cross_position = 25, toe_position = 80;  // размеры поля: cross_position -> y, toe_position -> x
    int x = cross_position / 2, y = toe_position / 2;  // координаты мяча: х->y  y->x
    int vec_x = 1, vec_y = 1;
    int total_points_1 = 0, total_points_2 = 0;
    int l_rocket_pos_x = cross_position / 2, r_rocket_pos_x = cross_position / 2;
    int l_rocket_pos_y = 0 + 10, r_rocket_pos_y = toe_position - 10;
    char pos;
    printf("\033[0d\033[2J");
    cross_and_toe_display(cross_position, toe_position, x, y, total_points_1, total_points_2, l_rocket_pos_x,
                          r_rocket_pos_x, l_rocket_pos_y, r_rocket_pos_y);
    while (total_points_1 < 21 && total_points_2 < 21) {
        if (scanf("%1c", &pos) == 1 && getchar() == '\n') {
            if (y > toe_position - 10) {
                total_points_1 += 1;
                x = cross_position / 2;
                y = toe_position / 2;
                printf("\x1B[2J\x1B[H");
                cross_and_toe_display(cross_position, toe_position, x, y, total_points_1, total_points_2,
                                      l_rocket_pos_x, r_rocket_pos_x, l_rocket_pos_y, r_rocket_pos_y);
                continue;

            } else if (y < 0 + 10) {
                total_points_2 += 1;
                x = cross_position / 2;
                y = toe_position / 2;
                printf("\x1B[2J\x1B[H");
                cross_and_toe_display(cross_position, toe_position, x, y, total_points_1, total_points_2,
                                      l_rocket_pos_x, r_rocket_pos_x, l_rocket_pos_y, r_rocket_pos_y);
                continue;
            }

            if (pos == 'a' || pos == 'z' || pos == 'k' || pos == 'm' ||
                pos == ' ') { /*проверяем движение ракеток*/
                vec_y = hit(x, y, vec_y, l_rocket_pos_x, r_rocket_pos_x, l_rocket_pos_y, r_rocket_pos_y);
                vec_x = ball_vector(x, vec_x, cross_position);
                x += vec_x;
                y += vec_y;
                l_rocket_pos_x = player_turn(pos, 1, l_rocket_pos_x, r_rocket_pos_x, cross_position);
                r_rocket_pos_x = player_turn(pos, 0, l_rocket_pos_x, r_rocket_pos_x, cross_position);

                printf("\x1B[2J\x1B[H");
                cross_and_toe_display(cross_position, toe_position, x, y, total_points_1, total_points_2,
                                      l_rocket_pos_x, r_rocket_pos_x, l_rocket_pos_y, r_rocket_pos_y);
                continue;
            } else {
                printf("not that value\n");
            }
        }
    }
    printf("\x1B[2J\x1B[H");
    printf((total_points_1 > total_points_2) ? "\n\t\t\t\tplayer 1 wins\n" : "\n\t\t\t\tplayer 2 wins\n");
    return 0;
}

void cross_and_toe_display(int cross_pos, int toe_pos, int x, int y, int total_points_1, int total_points_2,
                           int l_rocket, int r_rocket, int l_rocket_pos,
                           int r_rocket_pos) { /*cross_pos -- левый край    toe_pos -- правый край*/
    char space = ' ';
    char ball = '@';
    printf("\t\t\t\tScore: %d | %d \n", total_points_1, total_points_2);
    for (int c = 0; c < cross_pos; c++) {
        for (int t = 0; t < toe_pos; t++) {
            if (t == 0) {
                printf("║");
            } else if (t == toe_pos - 1) {
                printf("║\n");
            } else if (c == 0 || c == cross_pos - 1) {
                printf("═");
            } else {
                if (t == r_rocket_pos && (c == r_rocket || c == r_rocket - 1 || c == r_rocket + 1)) {
                    printf("■");
                } else if (t == l_rocket_pos && (c == l_rocket || c == l_rocket - 1 || c == l_rocket + 1)) {
                    printf("■");
                } else if (c == x && t == y) {
                    printf("%c", ball);
                } else {
                    printf("%c", space);
                }
            }
        }
    }
}

int ball_vector(int x, int vec, int border) {
    if ((x + vec == border - 1) || (x + vec == 0)) {
        vec *= -1;
    }
    return vec;
}

int hit(int x, int y, int vec_x, int l_rocket_pos_x, int r_rocket_pos_x, int l_rocket_pos_y,
        int r_rocket_pos_y) {
    if (((x == r_rocket_pos_x) || (x == r_rocket_pos_x + 1) || (x == r_rocket_pos_x - 1) ||
         (x == l_rocket_pos_x) || (x == l_rocket_pos_x - 1) || (x == l_rocket_pos_x + 1)) &&
        (y == (r_rocket_pos_y - 1) || y == (l_rocket_pos_y + 1))) {
        vec_x *= -1;
    }
    return vec_x;
}

int player_turn(char command, int flag, int l_rocket_pos_x, int r_rocket_pos_x, int border) {
    if ((flag) && (command == 'a' || command == 'z')) {
        if ((command == 'a') && (l_rocket_pos_x - 1 > 1)) {
            --l_rocket_pos_x;
        } else if (command == 'z' && l_rocket_pos_x + 1 < border - 2) {
            ++l_rocket_pos_x;
        }
    } else if (!(flag) && (command == 'k' || command == 'm')) {
        if (command == 'k' && r_rocket_pos_x - 1 > 1) {
            --r_rocket_pos_x;
        } else if (command == 'm' && r_rocket_pos_x + 1 < border - 2) {
            ++r_rocket_pos_x;
        }
    }
    if (flag) {
        return l_rocket_pos_x;
    }
    return r_rocket_pos_x;
}
