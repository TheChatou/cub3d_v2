/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:37:13 by chatou            #+#    #+#             */
/*   Updated: 2024/09/25 15:06:12 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# include <stdbool.h>
# include <SDL2/SDL.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xos.h>

# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

# include "structs.h"
# include "for_linux.h"
// # include "for_mac_os.h"
# include "bonus.h"
# include "colors.h"

# define WALL			'1'
# define VOID			'0'
# define PLAYER			'P'
# define NORTH			'N'
# define SOUTH			'S'
# define EAST			'E'
# define WEST			'W'
# define DOOR			'D'
# define TOKEN			'T'
# define TRAP			'B'
# define LIFE			'L'

# define LOADING		99
# define GAME_LOOP		100

# define N_SIDE 0
# define S_SIDE 1
# define W_SIDE 2
# define E_SIDE 3
# define DOOR_SIDE 4

# define WIN_SIZE		800
# define TILE_SIZE		256

// FOR THE MINIMAP, y a des define similaires apres
# define WALL_COLOR 	0x000000
# define EMPTY_COLOR 	0xFFFFFF
# define PLAYER_COLOR 	0xFF0000
# define TOKEN_COLOR 	0xFFD700
# define EXIT_COLOR 	0x00FF00
# define MMAP_WIDTH		200
# define MMAP_HEIGHT	200
# define SCALE_FACTOR	10
# define MMAP_OFFSET_X	20
# define MMAP_OFFSET_Y	20

// Événements
# define KEY_PRESS_EVENT		2
# define KEY_RELEASE_EVENT		3
# define MOUSE_MOVE_EVENT		6
# define MOUSE_PRESS_EVENT		4
# define MOUSE_RELEASE_EVENT	5
# define WIN_CLOSE_EVENT		17

// Masques d'événements
# define KEY_PRESS_MASK		1L<<0
# define KEY_RELEASE_MASK	1L<<1
# define MOUSE_MOVE_MASK	1L<<6
# define MOUSE_PRESS_MASK	1L<<2
# define MOUSE_RELEASE_MASK	1L<<3
# define NO_EVENT_MASK		0

# define CAM_HEIGHT	0.1

# define DIR_N		(t_dpoint){0, -1}
# define DIR_S		(t_dpoint){0, 1}
# define DIR_E		(t_dpoint){1, 0}
# define DIR_W		(t_dpoint){-1, 0}
# define PLANE_N	(t_dpoint){0.66, 0}
# define PLANE_S	(t_dpoint){-0.66, 0}
# define PLANE_E	(t_dpoint){0, 0.66}
# define PLANE_W	(t_dpoint){0, -0.66}

# define FLOOR_PATH_1		"./assets/Alic3D/Floor_Grass.xpm"
# define FLOOR_PATH_2		"./assets/Alic3D/Floor_lvl2.xpm"
# define DOOR_PATH_1		"./assets/Alic3D/Door_RabbitHole.xpm"
# define DOOR_PATH_2		"./assets/Alic3D/Door_RabbitHole.xpm"
# define CEILING_PATH_1		"./assets/Alic3D/Ceiling_Clouds.xpm"
# define CEILING_PATH_2		"./assets/Alic3D/Ceiling_Simple_lv2.xpm"
# define HOMESCREEN_PATH_1	"./assets/Alic3D/HomeScreen_lvl1.xpm"
# define HOMESCREEN_PATH_2	"./assets/Alic3D/HomeScreen_lvl2.xpm"
# define HANDS_PATH_1		"./assets/Alic3D/Hands_Empty_lvl1.xpm"
# define HANDS_PATH_1_W		"./assets/Alic3D/Hands_Watch_lvl1.xpm"
# define HANDS_PATH_2		"./assets/Alic3D/Hands_Empty_lvl2.xpm"
# define HANDS_PATH_2_W		"./assets/Alic3D/Hands_Watch_lvl2.xpm"
# define HEART_PATH			"./assets/Alic3D/heart_25_17.xpm"
# define WATCH_PATH			"./assets/Alic3D/Token_Watch.xpm"
# define POTION_PATH		"./assets/Alic3D/Token_Potion.xpm"
# define LOADING_PATH		"./assets/Alic3D/loading.xpm"

# define INTRO_1			"./assets/Alic3D/sablier_0.xpm"
# define INTRO_2			"./assets/Alic3D/sablier_1.xpm"
# define INTRO_3			"./assets/Alic3D/sablier_2.xpm"
# define INTRO_4			"./assets/Alic3D/sablier_3.xpm"

# define BTRAP_L1_1			"./assets/Alic3D/BoobyTrap_lv1_0.xpm"
# define BTRAP_L1_2			"./assets/Alic3D/BoobyTrap_lv1_1.xpm"
# define BTRAP_L1_3			"./assets/Alic3D/BoobyTrap_lv1_2.xpm"
# define BTRAP_L1_4			"./assets/Alic3D/BoobyTrap_lv1_3.xpm"

# define ALPHA_ZERO -16777216

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

////////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS 	////////////////////////////////////////////////////////////////
////ANIM	////////////////////////////////////////////////////////////////////
//--/anim_00_LoadingScreen.c	-----------------------------------------------/
int				render_loading_screen(t_game *game);
void			load_i_intro(t_game *game);
void			set_p_intro(t_game *game);
int				is_loading(t_game *game);

//--/anim_01_BoobyTrap.c	---------------------------------------------------/
t_img			*render_booby_trap(t_game *game);
void			load_i_btrap(t_game *game);
void			set_p_btrap(t_game *game);

////FREE	////////////////////////////////////////////////////////////////////
//--/free_00.c	---------------------------------------------------------------/
int				destroy_game(t_game *game);
void			free_game(t_game *game);
void			free_img(t_game *game, t_img *img);
void			free_map(t_map *map);
void			free_intro(t_game *game);
void			free_btrap(t_game *game);

////HOOKS	////////////////////////////////////////////////////////////////////
//--/hook_actions_00.c	-------------------------------------------------------/
void			set_hooks(t_game *game);
int				keys_esc(int keycode, t_game *game);
int				keys_moves(int keycode, t_game *game);
void			update_player(t_game *game, char c);

//--/hook_actions_utils.c	---------------------------------------------------/
void			rotate_arrows(t_player *player, double angle);
int				handle_cam_motion(t_game *game, int keycode);

////MOUSE	////////////////////////////////////////////////////////////////////
//--/mouse_tracking.c	-------------------------------------------------------/
int				handle_mouse_press(int button, int x, int y, t_game *game);
int				handle_mouse_release(int button, int x, int y, t_game *game);
void			rotate_cam(t_player *player, double angle);
int				handle_mouse_motion(int x, int y, t_game *game);

////RAYCASTING	////////////////////////////////////////////////////////////////
//--/_init_ray_n_img.c		---------------------------------------------------/
void			init_img(t_img *img, int size);
bool			set_img(t_game *game, t_img *img);

//--/raycasting_00_set_n_cast.c	-----------------------------------------------/
bool			raycasting(t_game *game);
void			set_ray(t_game *game, int x);
void			set_ray_step(t_ray *ray, t_player *player);
void			cast_ray(t_game *game, t_ray *ray, t_line *tk, t_line *btrap);
void			ray_hit_check(t_game *game, t_ray *ray, t_line *tk, t_line *btrap);

//--/raycasting_01_calc.c	---------------------------------------------------/
void			calc_rays(t_ray *ray, t_player *player, t_game *game);
void			calc_ray_token(t_game *game, t_player *player, t_line *tk);
void			calc_wall_tex_pos(t_game *game, t_ray *ray, t_img *wall);
t_dpoint		calc_floor_tex_pos(t_game *game, t_ray *ray,
					int y, t_dpoint *floor);
void			calc_ceiling_tex_pos(t_game *game, t_ray *ray,
					int y, t_dpoint *ceiling);
void			calc_booby_trap(t_game *game, t_player *player, t_line *btrap);

//--/raycasting_02_draw.c	---------------------------------------------------/
t_img			draw_line(t_game *game, t_ray *ray, t_img img, int x);
void			draw_token_tex(t_game *game, t_img *token,
					t_img *img, t_point pxl_pos);
void			draw_wall_tex(t_game *game, t_img *wall,
					t_img *img, t_point pxl_pos);
void			draw_floor_tex(t_game *game, t_ray *ray,
					t_img img, t_point pxl_pos);
void			draw_ceiling_tex(t_game *game, t_ray *ray,
					t_img img, t_point pxl_pos);
void			draw_booby_trap(t_game *game, t_img *trap,
					t_img img, t_point pxl_pos);

//--/raycasting_03_utils.c	---------------------------------------------------/
unsigned int	get_pixel_color(t_img img, int x, int y);
void			set_pixel(t_img *img, int x, int y, unsigned int color);
t_img			select_wall(t_game *game, t_ray *ray);

////START_N_INIT	////////////////////////////////////////////////////////////
//--/_init_player.c	-----------------------------------------------------------/
bool			set_player(t_game *game, t_player *player);
t_player		set_dir_n_plane(t_map *map);

//--/_init_structures.c	-------------------------------------------------------/
bool			set_game(t_game *game, int level);
bool			init_game(char *av, t_game *game);
void			init_cam(t_cam *cam);
bool			init_ray(t_ray *ray);

//--/game_00_Start.c	-------------------------------------------------------/
bool			launch(t_game *game, char *av, int level);
int				start(int keycode, t_game *game);
int				game_loop(t_game *game);
void			*pre_raycasting(void *arg);
bool			display_home_screen(t_game *game, t_img *home);

//--/game_01_UserInterface.c	-----------------------------------------------/
bool			draw_user_interface(t_game *game);
void			lifes(t_game *game, int lifes);
bool			weapon(t_game *game, t_img *img);
void			draw_weapon(t_game *game, t_img *img);

////UTILS	////////////////////////////////////////////////////////////////////
//--/utils_00.c	---------------------------------------------------------------/
t_point			count_lines_n_length(char *path);
bool			no_moves(t_player *player);
double			ft_floor(double x);
int				ft_truncate(float x);
int				ft_strcmp_spe(char *str, char *dest);

//--/utils_01.c	---------------------------------------------------------------/
unsigned int	t_color_to_uint(t_color color);
unsigned int	apply_gradient_shader(unsigned int pixel, double percent,
					SDL_Color target);
long			get_current_time_ms(void);

//--/utils_02_load_imgs.c	---------------------------------------------------/
void			load_imgs(t_game *game, t_map *map);
bool			load_img_n_addr(t_game *game, t_img *img,
					char *path, char *error);
t_img			error_img(void);

//--/utils_03_prints.c	-------------------------------------------------------/
void			print_t_ray(t_ray *ray);
void			print_t_line(t_line *line);
void			print_map(t_map *map);
int				ft_print_map_tab(t_game *game);
int				ft_print_map_info(t_game *game);

//--/utils_04_ending.c	-------------------------------------------------------/
void			you_win(void);
void			game_over(void);
void			game_over(void);

////MATH	////////////////////////////////////////////////////////////////////
////MOVES	////////////////////////////////////////////////////////////////////
//--/control_moves.c	-------------------------------------------------------/
bool			block_sb(t_game *game, int a, int b2);
bool			corner_collision(t_game *game, float move_y, float move_x);
bool			straight_collision(t_game *game, float move_y, float move_x);
bool			is_walkable(t_game *game, float move_y, float move_x);

//--/life_management.c	-------------------------------------------------------/
bool			is_trap(t_game *game, int a, int b);
bool			lose_life(t_game *game, float move_y, float move_x);

//--/crouch.c	---------------------------------------------------------------/
void			crouch(t_player *player);

//--/move_forward.c	-----------------------------------------------------------/
t_player		slide_forward(int y, int x, t_game *game);
t_player		move_forward(t_game *game, t_player player);

//--/move_backward.c	-------------------------------------------------------/
t_player		slide_backward(int y, int x, t_game *game);
t_player		move_backward(t_game *game, t_player player);

//--/move_right.c	-----------------------------------------------------------/
t_player		slide_right(int y, int x, t_game *game);
t_player		move_right(t_game *game, t_player player);

//--/move_left.c	-----------------------------------------------------------/
t_player		slide_left(int y, int x, t_game *game);
t_player		move_left(t_game *game, t_player player);

////PARSING	////////////////////////////////////////////////////////////////////
//--/control_rights.c	-------------------------------------------------------/
void			ft_access_textures(t_game *game);

//--/errors.c	---------------------------------------------------------------/
void			ft_error_map(t_game *game, char *str);
void			ft_error_map1(char *str, t_game *game);

//--/free_functions.c	-------------------------------------------------------/
void			ft_free_map_tab(t_game *game);
void			ft_free_all_textures_colors(t_game *game);
void			ft_free_all(t_game *game);
void			destroy_imgs(t_game *game);

//--/parsing_map_info.c	-------------------------------------------------------/
void			ft_quit_textures_colors(char *src, char **tab, t_game *game, char *mss);
int				ft_get_map_info(char *src, t_game *game);
int				ft_pass_map_info(char *src);
int				ft_free_tab(char **tab); // put in free_functions

//--/stock_textures.c	-------------------------------------------------------/
int				ft_stock_north_texture(char *src, t_game *game);
int				ft_stock_south_texture(char *src, t_game *game);
int				ft_stock_west_texture(char *src, t_game *game);
int				ft_stock_east_texture(char *src, t_game *game);

//--/stock_textures1.c	-------------------------------------------------------/
char			*ft_remove_nl(char *src, t_game *game, char **tab);
void			ft_control_colors(t_color *color, char **tab, t_game *game, char *src);
int				ft_stock_floor_color(char *src, t_game *game);
int				ft_stock_ceiling_color(char *src, t_game *game);

//--/check_map_elements.c	---------------------------------------------------/
int				ft_check_extension(char *name);
int				ft_check_lines(t_game *game);
int				ft_check_surrounding(t_game *game, size_t x, size_t y);
int				ft_check_walls(t_game *game);
int				ft_check_map(char *name, t_game *game);

//--/check_map_symbols.c	---------------------------------------------------/
int				ft_check_symb(char c);
int				ft_player_symb(char c);
int				ft_is_space(char c);
int				ft_check_inner_elements(char c);
int				ft_check_empty_spot(char c);

//--/parsing_map1.c	-----------------------------------------------------------/
int				get_map_size(t_game *game, char *map_file);
int				ft_stock_map_tab(char *map_file, t_game *game);

//--/utils.c	---------------------------------------------------------------/
void			end_game(t_game *game);
bool			check_if_end(t_game *game);
bool			check_if_dead(t_game *game);
t_tri_point		find_player_float(t_map *map);
void			ft_check_if_token(t_game *game);

////FLOOD_FILL	///////////////////////////////
//-/flood_fill.c --------------------------------------------------------------/
char			**ft_copy_map(char **map, t_game *game);
char			**ft_flood_fill(int x, int y, char **copy);
int				ft_find_exit(char **map, t_game *game);
int				control_fill_final(char **map, t_game *game);
int				valid_path(t_game *game);

//-/flood_fill_utils.c --------------------------------------------------------/
bool			check_if_not_walls(char c);

////MINIMAP	///////////////////////////////
//-/minimap.c -----------------------------------------------------------------/
void			ft_draw_square(int x, int y, int color, t_game *game);
void			ft_draw_mmp_background(t_game *game);
void			ft_draw_mmp(t_game *game, int x, int y);
void			minimap(t_game *game);

//-/minimap_utils.c -----------------------------------------------------------/
bool			is_in_circle(t_dpoint *pixel);
void			ft_define_pixel_color(t_game *game, int x, int y);


#endif