// fdf_ui_template.c
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define WIN_W 1920
#define WIN_H 1080

typedef struct s_button {
    int x, y, w, h;
    char *label;
    void (*on_click)(void *);
} t_button;

typedef struct s_slider {
    int x, y, w;
    int min, max;
    int value;
    int knob_radius;
} t_slider;

typedef struct s_ui {
    void *mlx;
    void *win;
    t_button buttons[5];
    int button_count;
    t_slider slider;
    int angle;
} t_ui;

// ---------------- Callbacks ------------------
void on_cube(void *p) { printf("[cube]\n"); }
void on_prev(void *p) { printf("[prev]\n"); }
void on_play(void *p) { printf("[play]\n"); }
void on_next(void *p) { printf("[next]\n"); }
void on_grid(void *p) { printf("[grid]\n"); }

// ---------------- Helpers ------------------
void add_button(t_ui *ui, int x, int y, char *label, void (*cb)(void *)) {
    t_button *b = &ui->buttons[ui->button_count++];
    b->x = x; b->y = y; b->w = 60; b->h = 60; b->label = label; b->on_click = cb;
}

void draw_slider(t_ui *ui) {
    t_slider *s = &ui->slider;
    int knob_x = s->x + (s->value - s->min) * s->w / (s->max - s->min);

    mlx_string_put(ui->mlx, ui->win, s->x - 20, s->y + 5, 0xFFFFFF, "0");
    mlx_string_put(ui->mlx, ui->win, s->x + s->w + 10, s->y + 5, 0xFFFFFF, "360");

    for (int i = 0; i < s->w; i++)
        mlx_pixel_put(ui->mlx, ui->win, s->x + i, s->y, 0xFFFFFF);

    for (int dx = -s->knob_radius; dx <= s->knob_radius; dx++) {
        for (int dy = -s->knob_radius; dy <= s->knob_radius; dy++) {
            if (dx * dx + dy * dy <= s->knob_radius * s->knob_radius)
                mlx_pixel_put(ui->mlx, ui->win, knob_x + dx, s->y + dy, 0xFFFFFF);
        }
    }
}

void draw_ui(t_ui *ui) {
    mlx_clear_window(ui->mlx, ui->win);

    // info box
    mlx_string_put(ui->mlx, ui->win, 20, 30, 0xFFFFFF, "info");
    mlx_string_put(ui->mlx, ui->win, 20, 70, 0xFFFFFF, "size: x=42, y=20");
    mlx_string_put(ui->mlx, ui->win, 20, 100, 0xFFFFFF, "vertices: 840");
    mlx_string_put(ui->mlx, ui->win, 20, 130, 0xFFFFFF, "z_max: 128");
    mlx_string_put(ui->mlx, ui->win, 20, 160, 0xFFFFFF, "z_min: -16");

    // image placeholder
    mlx_string_put(ui->mlx, ui->win, 900, 360, 0xFFFFFF, "image");

    // file list (display only)
    mlx_string_put(ui->mlx, ui->win, 1650, 100, 0xFFFFFF, "sample.fdf");
    mlx_string_put(ui->mlx, ui->win, 1650, 160, 0xFFFFFF, "42.fdf");

    // current file
    mlx_string_put(ui->mlx, ui->win, 850, 750, 0xFFFFFF, "sample.fdf");

    // slider
    draw_slider(ui);

    // buttons
    for (int i = 0; i < ui->button_count; i++) {
        t_button *b = &ui->buttons[i];
        mlx_string_put(ui->mlx, ui->win, b->x + 10, b->y + 20, 0x00FF00, b->label);
    }
}

int mouse_click(int btn, int x, int y, void *p) {
    t_ui *ui = (t_ui *)p;
    t_slider *s = &ui->slider;

    if (btn == 1 && y >= s->y - 10 && y <= s->y + 10 && x >= s->x && x <= s->x + s->w) {
        s->value = (x - s->x) * (s->max - s->min) / s->w + s->min;
        printf("angle: %d\n", s->value);
        draw_ui(ui);
        return 0;
    }
    for (int i = 0; i < ui->button_count; i++) {
        t_button *b = &ui->buttons[i];
        if (x >= b->x && x <= b->x + b->w && y >= b->y && y <= b->y + b->h) {
            b->on_click(ui);
            break;
        }
    }
    return 0;
}


