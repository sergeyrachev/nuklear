/*
    Copyright (c) 2015
    vurtun <polygone@gmx.net>
    MIT licence
*/
#ifndef TINY_GUI_H_
#define TINY_GUI_H_

#define GUI_UTF_SIZE 4
#define GUI_INPUT_MAX 16
#define GUI_GLYPHES_MAX 512

typedef int gui_int;
typedef int gui_bool;
typedef unsigned char gui_char;
typedef float gui_float;
typedef void* gui_texture;
typedef unsigned char gui_byte;
typedef unsigned long gui_flag;
typedef unsigned long gui_size;
typedef gui_char gui_glyph[GUI_UTF_SIZE];

enum {gui_false, gui_true};
struct gui_color {gui_byte r,g,b,a;};
struct gui_texCoord {gui_float u,v;};
struct gui_vec2 {gui_float x,y;};
struct gui_rect {gui_float x,y,w,h;};

struct gui_vertex {
    struct gui_vec2 pos;
    struct gui_texCoord uv;
    struct gui_color color;
};

struct gui_draw_command {
    struct gui_vertex *vertexes;
    gui_int vertex_count;
    gui_int vertex_write;
    struct gui_rect clip_rect;
    gui_texture texture;
};

struct gui_draw_list {
    struct gui_draw_command *begin;
    struct gui_draw_command *end;
    gui_byte *memory;
    gui_size size;
    gui_size needed;
};

enum gui_keys {
    GUI_KEY_SHIFT,
    GUI_KEY_CTRL,
    GUI_KEY_DEL,
    GUI_KEY_ENTER,
    GUI_KEY_BACKSPACE,
    GUI_KEY_ESCAPE,
    GUI_KEY_SPACE,
    GUI_KEY_MAX
};

struct gui_input {
    gui_int keys[GUI_KEY_MAX];
    gui_glyph text[GUI_INPUT_MAX];
    gui_size glyph_count;
    gui_bool shift;
    gui_bool ctrl;
    struct gui_vec2 mouse_pos;
    struct gui_vec2 mouse_prev;
    struct gui_vec2 mouse_delta;
    gui_bool mouse_down;
    gui_int mouse_clicked;
    struct gui_vec2 mouse_clicked_pos;
};

struct gui_font_glyph {
    gui_glyph glpyh;
};

struct gui_font {
    struct gui_font_glyph glyphes[GUI_GLYPHES_MAX];
};

void gui_begin(struct gui_draw_list *list, gui_byte *memory, gui_size size);
gui_size gui_end(struct gui_draw_list *list);
const struct gui_draw_command *gui_next(const struct gui_draw_list *list,
                                        const struct gui_draw_command*);

void gui_input_begin(struct gui_input *in);
void gui_input_motion(struct gui_input *in, gui_int x, gui_int y);
void gui_input_key(struct gui_input *in, enum gui_keys key, gui_int down);
void gui_input_button(struct gui_input *in, gui_int x, gui_int y, gui_int down);
void gui_input_char(struct gui_input *in, gui_glyph glyph);
void gui_input_end(struct gui_input *in);

gui_int gui_button(struct gui_draw_list *list, const struct gui_input *in,
                    struct gui_color bg, struct gui_color fg,
                    gui_int x, gui_int y, gui_int w, gui_int h, gui_int pad,
                    const char *str, gui_int len);
gui_int gui_toggle(struct gui_draw_list *list, const struct gui_input *in,
                    struct gui_color bg, struct gui_color fg,
                    gui_int x, gui_int y, gui_int w, gui_int h, gui_int pad,
                    const char *str, gui_int len, gui_int active);
gui_int gui_slider(struct gui_draw_list *list, const struct gui_input *in,
                    struct gui_color bg, struct gui_color fg,
                    gui_int x, gui_int y, gui_int w, gui_int h, gui_int pad,
                    gui_float min, gui_float v, gui_float max, gui_float step);
gui_int gui_progress(struct gui_draw_list *list, const struct gui_input *in,
                    struct gui_color bg, struct gui_color fg,
                    gui_int x, gui_int y, gui_int w, gui_int h, gui_int pad,
                    gui_float cur, gui_float max, gui_bool modifyable);
gui_int gui_scroll(struct gui_draw_list *list, const struct gui_input *in,
                    struct gui_color bg, struct gui_color fg,
                    gui_int x, gui_int y, gui_int w, gui_int h,
                    gui_int offset, gui_int dst);
gui_int gui_input(struct gui_draw_list *list,
                    const struct gui_input *in, gui_char *buffer, gui_int *len,
                    struct gui_color bg, struct gui_color fg,
                    gui_int x, gui_int y, gui_int w, gui_int h, gui_int active);

#endif