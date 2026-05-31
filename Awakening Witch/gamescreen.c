#include "gamescreen.h"


void gamescreen(void) {
    while (player.health > 0) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        keyboard_update(&event);

        if (score_display - prev_score >= (int)(150.0 * score_multiplier)) {
            level_up();
            prev_score = score_display;
            reset_keyboard_event();
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT) {
            reset_keyboard_event();
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // 적 생성
            // if (key[ALLEGRO_KEY_1]) spawn_enermy(1);
            // if (key[ALLEGRO_KEY_2]) spawn_enermy(2);
            
            // 필살기
            if (key[ALLEGRO_KEY_R]) Special_moves(1);

            // 아군 생성
            if (key[ALLEGRO_KEY_A]) spawn_summon(13);
            if (key[ALLEGRO_KEY_S]) spawn_summon(11);
            if (key[ALLEGRO_KEY_D]) spawn_summon(12);

            // 적 삭제(디버그용)
            // if (key[ALLEGRO_KEY_5]) clear_summons(1);
            
            // 아군 삭제(디버그용)
            // if (key[ALLEGRO_KEY_6]) clear_summons(11);

            // 공격
            if (key[ALLEGRO_KEY_SPACE]) fire_bullet();

            // 본인 강화(상점)
            if (key[ALLEGRO_KEY_Q]) player_enhance_sp();
            if (key[ALLEGRO_KEY_W]) player_enhance_dm();
            if (key[ALLEGRO_KEY_E]) player_enhance_bu();
        }

        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == spawn_timer) {
            spawn_enermy(1);
        }

        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == spawn_timer_boss) {
            spawn_enermy(2);
        }

        if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == timer) {
            move_player();
            move_bullets();
            move_summons();
            move_boss_bullets();
            move_boss_lasers();
            check_collision();
            check_bullet_collision();
            check_boss_bullet_collision();
            check_boss_laser_collision();
            check_player_collision();
            attack_boss();
            attack_laser_boss();
            
        }

        update_animation();
        update_animation2();

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(background[backstage], 0, 0, al_get_bitmap_width(background[backstage]), al_get_bitmap_height(background[backstage]),
            0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        render_screen();

        int bullet_size = 80;
        for (int i = 0; i < player.bullets; i++) {
            if (bullets[i].active) {
                al_draw_scaled_bitmap(fireball_img, 0, 0, al_get_bitmap_width(fireball_img), al_get_bitmap_height(fireball_img),
                    bullets[i].x - bullet_size / 2, bullets[i].y - bullet_size / 2, bullet_size, bullet_size, 0);
            }
        }

        for (int j = 0; j < MAX_BOSSES; ++j) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (boss_bullets[j][i].active) {
                    al_draw_scaled_bitmap(fireball_boss_img, 0, 0, al_get_bitmap_width(fireball_boss_img), al_get_bitmap_height(fireball_boss_img),
                        boss_bullets[j][i].x - 35, boss_bullets[j][i].y - 35, 70, 70, 0);
                }
            }
        }

        for (int j = 0; j < MAX_BOSSES; ++j) {
            if (boss_laser_timer[j] >= 350) {
                draw_rotated_laser(j + MAX_KNIGHTS);
            }
        }

        int enemy_size = 100;
        for (int i = 0; i < MAX_KNIGHTS; i++) {
            if (enemies[i].active) {
                al_draw_filled_rectangle(
                    enemies[i].x - ((double)enemy_size / 2.0 - 10.0 + 2.0), 
                    enemies[i].y - enemy_size / 2 - 20 - 2.0,
                    enemies[i].x + ((double)enemy_size / 2.0 - 10.0 + 2.0), 
                    enemies[i].y - enemy_size / 2 - 10 + 2.0,
                    al_map_rgb_f(0, 0, 0));
                al_draw_filled_rectangle(
                    enemies[i].x - ((double)enemy_size / 2.0 - 10.0), enemies[i].y - enemy_size / 2 - 20,
                    enemies[i].x + ((double)enemy_size / 2.0 - 10.0), enemies[i].y - enemy_size / 2 - 10,
                    al_map_rgb_f(255, 0, 0));
                al_draw_filled_rectangle(
                    enemies[i].x - ((double)enemy_size / 2.0 - 10.0), enemies[i].y - enemy_size / 2 - 20,
                    enemies[i].x - ((double)enemy_size / 2.0 - 10.0) + 2 * ((double)enemy_size / 2.0 - 10.0) * ((double)enemies[i].health / (KNIGHT_MAX_HEALTH + enemy_health_plus)), enemies[i].y - enemy_size / 2 - 10,
                    al_map_rgb_f(0, 255, 0));
                if (enemies[i].matched_enemy == -1 && enemies[i].x < player.x) {
                    al_draw_scaled_bitmap(knight_sword[current_enemies_frame[i]], 0, 0, al_get_bitmap_width(knight_sword[current_enemies_frame[i]]), al_get_bitmap_height(knight_sword[current_enemies_frame[i]]),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, ALLEGRO_FLIP_HORIZONTAL);
                }
                else if (enemies[i].matched_enemy == -1 && enemies[i].x >= player.x) {
                    al_draw_scaled_bitmap(knight_sword[current_enemies_frame[i]], 0, 0, al_get_bitmap_width(knight_sword[current_enemies_frame[i]]), al_get_bitmap_height(knight_sword[current_enemies_frame[i]]),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, 0);
                }
                else if (enemies[i].x >= summons[enemies[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(knight_sword[current_enemies_frame[i]], 0, 0, al_get_bitmap_width(knight_sword[current_enemies_frame[i]]), al_get_bitmap_height(knight_sword[current_enemies_frame[i]]),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(knight_sword[current_enemies_frame[i]], 0, 0, al_get_bitmap_width(knight_sword[current_enemies_frame[i]]), al_get_bitmap_height(knight_sword[current_enemies_frame[i]]),
                        enemies[i].x - enemy_size / 2, enemies[i].y - enemy_size / 2, enemy_size, enemy_size, ALLEGRO_FLIP_HORIZONTAL);
                }
                if (enemies[i].matched_enemy == -1)  current_enemies_frame[i] = 0;
            }
        }

        int enermy_boss_size = 200;
        for (int i = MAX_KNIGHTS; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                al_draw_filled_rectangle(
                    enemies[i].x - ((double)enermy_boss_size / 2.0 - 10.0 + 2.0),
                    enemies[i].y - enermy_boss_size / 2 - 20 - 2.0,
                    enemies[i].x + ((double)enermy_boss_size / 2.0 - 10.0 + 2.0),
                    enemies[i].y - enermy_boss_size / 2 - 10 + 2.0,
                    al_map_rgb_f(0, 0, 0));
                al_draw_filled_rectangle(
                    enemies[i].x - ((double)enermy_boss_size / 2.0 - 10.0), 
                    enemies[i].y - enermy_boss_size / 2 - 20,
                    enemies[i].x + ((double)enermy_boss_size / 2.0 - 10.0), 
                    enemies[i].y - enermy_boss_size / 2 - 10,
                    al_map_rgb_f(255, 0, 0));
                al_draw_filled_rectangle(
                    enemies[i].x - ((double)enermy_boss_size / 2.0 - 10.0), 
                    enemies[i].y - enermy_boss_size / 2 - 20,
                    enemies[i].x - ((double)enermy_boss_size / 2.0 - 10.0) + 2 * ((double)enermy_boss_size / 2.0 - 10.0) * ((double)enemies[i].health / (BOSS_MAX_HEALTH + enemy_health_plus)),
                    enemies[i].y - enermy_boss_size / 2 - 10,
                    al_map_rgb_f(0, 255, 0));
                // 보스 레이저 충전 시간
                if (boss_laser_timer[i-MAX_KNIGHTS] > 350 && boss_laser_timer[i-MAX_KNIGHTS]<=500) {
                    // 테두리
                    al_draw_filled_rectangle(
                        enemies[i].x - ((double)enermy_boss_size / 3.0 - 10.0 + 2.0),
                        enemies[i].y + enermy_boss_size / 2 - 5 - 2.0,
                        enemies[i].x + ((double)enermy_boss_size / 3.0 - 10.0 + 2.0),
                        enemies[i].y + enermy_boss_size / 2 + 5 + 2.0,
                        al_map_rgb_f(0, 0, 0));
                    // 배경
                    /*al_draw_filled_rectangle(
                        enemies[i].x - ((double)enermy_boss_size / 2.0 - 10.0),
                        enemies[i].y + enermy_boss_size / 2 - 5,
                        enemies[i].x + ((double)enermy_boss_size / 2.0 - 10.0),
                        enemies[i].y + enermy_boss_size / 2 + 5,
                        al_map_rgb_f(255, 0, 0));*/
                    // 충전 시간
                    al_draw_filled_rectangle(
                        enemies[i].x - ((double)enermy_boss_size / 3.0 - 10.0),
                        enemies[i].y + enermy_boss_size / 2 - 5,
                        enemies[i].x - ((double)enermy_boss_size / 3.0 - 10.0) + 2 * ((double)enermy_boss_size / 3.0 - 10.0) * (((double)(boss_laser_timer[i - MAX_KNIGHTS] - 350) / 150)),
                        enemies[i].y + enermy_boss_size / 2 + 5,
                        al_map_rgb_f(204, 204, 0));
                }
                if (enemies[i].matched_enemy == -1 && enemies[i].x < player.x) {
                    al_draw_scaled_bitmap(enemy_boss_img_r, 0, 0, al_get_bitmap_width(enemy_boss_img_r), al_get_bitmap_height(enemy_boss_img_r),
                        enemies[i].x - enermy_boss_size / 2, enemies[i].y - enermy_boss_size / 2, enermy_boss_size, enermy_boss_size, 0);
                }
                else if (enemies[i].matched_enemy == -1 && enemies[i].x >= player.x) {
                    al_draw_scaled_bitmap(enemy_boss_img_l, 0, 0, al_get_bitmap_width(enemy_boss_img_l), al_get_bitmap_height(enemy_boss_img_l),
                        enemies[i].x - enermy_boss_size / 2, enemies[i].y - enermy_boss_size / 2, enermy_boss_size, enermy_boss_size, 0);
                }
                else if (enemies[i].x >= summons[enemies[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(enemy_boss_img_l, 0, 0, al_get_bitmap_width(enemy_boss_img_l), al_get_bitmap_height(enemy_boss_img_l),
                        enemies[i].x - enermy_boss_size / 2, enemies[i].y - enermy_boss_size / 2, enermy_boss_size, enermy_boss_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(enemy_boss_img_r, 0, 0, al_get_bitmap_width(enemy_boss_img_r), al_get_bitmap_height(enemy_boss_img_r),
                        enemies[i].x - enermy_boss_size / 2, enemies[i].y - enermy_boss_size / 2, enermy_boss_size, enermy_boss_size, 0);
                }
            }
        }
        int summon_size = 90;
        for (int i = 0; i < MAX_ZOMBIES; i++) {
            if (summons[i].active) {
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size / 2.0 - 10.0 + 2.0),
                    summons[i].y - summon_size / 2 - 20 - 2.0,
                    summons[i].x + ((double)summon_size / 2.0 - 10.0 + 2.0),
                    summons[i].y - summon_size / 2 - 10 + 2.0,
                    al_map_rgb_f(255, 255, 255));
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size / 2.0 - 10.0),
                    summons[i].y - summon_size / 2 - 20,
                    summons[i].x + ((double)summon_size / 2.0 - 10.0),
                    summons[i].y - summon_size / 2 - 10,
                    al_map_rgb_f(255, 0, 0));
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size / 2.0 - 10.0),
                    summons[i].y - summon_size / 2 - 20,
                    summons[i].x - ((double)summon_size / 2.0 - 10.0) + 2 *
                    ((double)summon_size / 2.0 - 10.0) *
                    ((double)summons[i].health / ZOMBIE_MAX_HEALTH),
                    summons[i].y - summon_size / 2 - 10,
                    al_map_rgb_f(0, 255, 0));
                int closest_enemy = -1;
                float min_distance = SCREEN_WIDTH * SCREEN_HEIGHT;
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active && !enemies[j].matched) {
                        float dx = summons[i].x - enemies[j].x;
                        float dy = summons[i].y - enemies[j].y;
                        float distance = sqrt(dx * dx + dy * dy);
                        if (distance < min_distance) {
                            min_distance = distance;
                            closest_enemy = j;
                        }
                    }
                }
                if (summons[i].matched_enemy != -1 && summons[i].x < enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(zombie_sword[current_frame[i]], 0, 0, al_get_bitmap_width(zombie_sword[current_frame[i]]), al_get_bitmap_height(zombie_sword[current_frame[i]]),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, 0);

                }
                else if (summons[i].matched_enemy != -1 && summons[i].x >= enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(zombie_sword[current_frame[i]], 0, 0, al_get_bitmap_width(zombie_sword[current_frame[i]]), al_get_bitmap_height(zombie_sword[current_frame[i]]),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, ALLEGRO_FLIP_HORIZONTAL);
                }
                else if (closest_enemy != -1 && summons[i].x < enemies[closest_enemy].x) {
                    al_draw_scaled_bitmap(zombie_sword[current_frame[i]], 0, 0, al_get_bitmap_width(zombie_sword[current_frame[i]]), al_get_bitmap_height(zombie_sword[current_frame[i]]),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(zombie_sword[current_frame[i]], 0, 0, al_get_bitmap_width(zombie_sword[current_frame[i]]), al_get_bitmap_height(zombie_sword[current_frame[i]]),
                        summons[i].x - summon_size / 2, summons[i].y - summon_size / 2, summon_size, summon_size, ALLEGRO_FLIP_HORIZONTAL);
                }
                if (summons[i].matched_enemy == -1)  current_frame[i] = 0;
            }
        }

        int summon_size1 = 120;
        for (int i = MAX_ZOMBIES; i < MAX_ZOMBIES+MAX_GOBLINS; i++) {
            if (summons[i].active) {
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size1 / 2.0 - 10.0 + 2.0),
                    summons[i].y - summon_size1 / 2 - 20 - 2.0,
                    summons[i].x + ((double)summon_size1 / 2.0 - 10.0 + 2.0),
                    summons[i].y - summon_size1 / 2 - 10 + 2.0,
                    al_map_rgb_f(255, 255, 255));
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size1 / 2.0 - 10.0),
                    summons[i].y - summon_size1 / 2 - 20,
                    summons[i].x + ((double)summon_size1 / 2.0 - 10.0),
                    summons[i].y - summon_size1 / 2 - 10,
                    al_map_rgb_f(255, 0, 0));
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size1 / 2.0 - 10.0),
                    summons[i].y - summon_size1 / 2 - 20,
                    summons[i].x - ((double)summon_size1 / 2.0 - 10.0) + 2 *
                    ((double)summon_size1 / 2.0 - 10.0) *
                    ((double)summons[i].health / GOBLIN_MAX_HEALTH),
                    summons[i].y - summon_size1 / 2 - 10,
                    al_map_rgb_f(0, 255, 0));
                int closest_enemy = -1;
                float min_distance = SCREEN_WIDTH * SCREEN_HEIGHT;
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active && !enemies[j].matched) {
                        float dx = summons[i].x - enemies[j].x;
                        float dy = summons[i].y - enemies[j].y;
                        float distance = sqrt(dx * dx + dy * dy);
                        if (distance < min_distance) {
                            min_distance = distance;
                            closest_enemy = j;
                        }
                    }
                }
            
                //오른쪽 바라보기(1,3) 
                if (summons[i].matched_enemy != -1 && summons[i].x < enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(goblin_sword[current_frame[i]], 0, 0, al_get_bitmap_width(goblin_sword[current_frame[i]]), al_get_bitmap_height(goblin_sword[current_frame[i]]),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, ALLEGRO_FLIP_HORIZONTAL);
               
                }
                else if (summons[i].matched_enemy != -1 && summons[i].x >= enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(goblin_sword[current_frame[i]], 0, 0, al_get_bitmap_width(goblin_sword[current_frame[i]]), al_get_bitmap_height(goblin_sword[current_frame[i]]),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1,0);
                }
                else if (closest_enemy != -1 && summons[i].x < enemies[closest_enemy].x) {
                    al_draw_scaled_bitmap(goblin_sword[current_frame[i]], 0, 0, al_get_bitmap_width(goblin_sword[current_frame[i]]), al_get_bitmap_height(goblin_sword[current_frame[i]]),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, ALLEGRO_FLIP_HORIZONTAL);
                }
                else {
                    al_draw_scaled_bitmap(goblin_sword[current_frame[i]], 0, 0, al_get_bitmap_width(goblin_sword[current_frame[i]]), al_get_bitmap_height(goblin_sword[current_frame[i]]),
                        summons[i].x - summon_size1/2, summons[i].y - summon_size1/2, summon_size1, summon_size1, 0);
                }
                if (summons[i].matched_enemy == -1)  current_frame[i] = 0;
            }
        }

        int summon_size2 = 70;
        for (int i = MAX_ZOMBIES + MAX_GOBLINS; i < MAX_ZOMBIES + MAX_GOBLINS + MAX_BATS; i++) {
            if (summons[i].active) {
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size2 / 2.0 - 10.0 + 2.0),
                    summons[i].y - summon_size2 / 2 - 20 - 2.0,
                    summons[i].x + ((double)summon_size2 / 2.0 - 10.0 + 2.0),
                    summons[i].y - summon_size2 / 2 - 10 + 2.0,
                    al_map_rgb_f(255, 255, 255));
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size2 / 2.0 - 10.0),
                    summons[i].y - summon_size2 / 2 - 20,
                    summons[i].x + ((double)summon_size2 / 2.0 - 10.0),
                    summons[i].y - summon_size2 / 2 - 10,
                    al_map_rgb_f(255, 0, 0));
                al_draw_filled_rectangle(
                    summons[i].x - ((double)summon_size2 / 2.0 - 10.0),
                    summons[i].y - summon_size2 / 2 - 20,
                    summons[i].x - ((double)summon_size2 / 2.0 - 10.0) + 2 *
                    ((double)summon_size2 / 2.0 - 10.0) *
                    ((double)summons[i].health / BAT_MAX_HEALTH),
                    summons[i].y - summon_size2 / 2 - 10,
                    al_map_rgb_f(0, 255, 0));
                int closest_enemy = -1;
                float min_distance = SCREEN_WIDTH * SCREEN_HEIGHT;
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active && !enemies[j].matched) {
                        float dx = summons[i].x - enemies[j].x;
                        float dy = summons[i].y - enemies[j].y;
                        float distance = sqrt(dx * dx + dy * dy);
                        if (distance < min_distance) {
                            min_distance = distance;
                            closest_enemy = j;
                        }
                    }
                }
                if (summons[i].matched_enemy != -1 && summons[i].x < enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(bat_sword[current_frame[i]], 0, 0, al_get_bitmap_width(bat_sword[current_frame[i]]), al_get_bitmap_height(bat_sword[current_frame[i]]),
                        summons[i].x - summon_size2 / 2, summons[i].y - summon_size2 / 2, summon_size2, summon_size2, 0);

                }
                else if (summons[i].matched_enemy != -1 && summons[i].x >= enemies[summons[i].matched_enemy].x) {
                    al_draw_scaled_bitmap(bat_sword[current_frame[i]], 0, 0, al_get_bitmap_width(bat_sword[current_frame[i]]), al_get_bitmap_height(bat_sword[current_frame[i]]),
                        summons[i].x - summon_size2 / 2, summons[i].y - summon_size2 / 2, summon_size2, summon_size2, ALLEGRO_FLIP_HORIZONTAL);
                }
                else if (closest_enemy != -1 && summons[i].x < enemies[closest_enemy].x) {
                    al_draw_scaled_bitmap(bat_sword[current_frame[i]], 0, 0, al_get_bitmap_width(bat_sword[current_frame[i]]), al_get_bitmap_height(bat_sword[current_frame[i]]),
                        summons[i].x - summon_size2 / 2, summons[i].y - summon_size2 / 2, summon_size2, summon_size2, 0);
                }
                else {
                    al_draw_scaled_bitmap(bat_sword[current_frame[i]], 0, 0, al_get_bitmap_width(bat_sword[current_frame[i]]), al_get_bitmap_height(bat_sword[current_frame[i]]),
                        summons[i].x - summon_size2 / 2, summons[i].y - summon_size2 / 2, summon_size2, summon_size2, ALLEGRO_FLIP_HORIZONTAL);
                }
                if (summons[i].matched_enemy == -1)  current_frame[i] = 0;
            }
        
        }

        for (int j = 0; j < MAX_BOSSES; ++j) {
            if (boss_laser_timer[j] >= 200) {
                draw_rotated_laser(j + MAX_KNIGHTS);
            }
        }

        int player_size = 80;
        if (invincible_timer > 0) {
            if ((invincible_timer / 15) % 2 == 0) {
                if (player.sees_left) {
                    al_draw_scaled_bitmap(player_img_l, 0, 0, al_get_bitmap_width(player_img_l), al_get_bitmap_height(player_img_l),
                        player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
                }
                else {
                    al_draw_scaled_bitmap(player_img_r, 0, 0, al_get_bitmap_width(player_img_r), al_get_bitmap_height(player_img_r),
                        player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
                }
            }
        }
        else {
            if (player.sees_left) {
                al_draw_scaled_bitmap(player_img_l, 0, 0, al_get_bitmap_width(player_img_l), al_get_bitmap_height(player_img_l),
                    player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
            }
            else {
                al_draw_scaled_bitmap(player_img_r, 0, 0, al_get_bitmap_width(player_img_r), al_get_bitmap_height(player_img_r),
                    player.x - player_size / 2, player.y - player_size / 2, player_size, player_size, 0);
            }
        }

        hud_draw();
        al_flip_display();
    }
    al_stop_sample(sample2);
}