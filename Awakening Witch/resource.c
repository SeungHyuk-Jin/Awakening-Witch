#include "resource.h"

void load_resource(void) {
    player_x = SCREEN_WIDTH / 2;
    player_y = SCREEN_HEIGHT / 2;
    player_health = 5;
    player_size = 30;
    invincible_timer = 120;
    // 배경 이미지 로드
    char back[50];
    for (int i = 0; i < 10; i++) {
        sprintf_s(back, sizeof(back), "Resource/pic/battleback%d.png", i + 1);
        //printf("%s", back);
        background[i] = al_load_bitmap(back);
        if (!background[i]) {
            printf("Failed to load image: %s\n", back);
        }
    }

    // 소환수 이미지 로드
    summon_img_l = al_load_bitmap("Resource/pic/zombie_l.png");
    if (!summon_img_l) {
        fprintf(stderr, "zombie_l.png 로드 실패!\n");
        return;
    }
    summon_img_r = al_load_bitmap("Resource/pic/zombie_r.png");
    if (!summon_img_r) {
        fprintf(stderr, "zombie_r.png 로드 실패!\n");
        return;
    }
    summon2_img_l = al_load_bitmap("Resource/pic/goblin_l.png");
    if (!summon_img_l) {
        fprintf(stderr, "goblin_l.png 로드 실패\n");
        return;
    }
    summon2_img_r = al_load_bitmap("Resource/pic/goblin_r.png");
    if (!summon_img_r) {
        fprintf(stderr, "goblin_r.png 로드 실패!\n");
        return;
    }
    summon3_img_r = al_load_bitmap("Resource/pic/bat.png");
    if (!summon_img_r) {
        fprintf(stderr, "goblin_r.png 로드 실패!\n");
        return;
    }
    enermy_img_l = al_load_bitmap("Resource/pic/knight_l.png");
    if (!enermy_img_l) {
        fprintf(stderr, "knight_l.png 로드 실패!\n");
        return;
    }
    enermy_img_r = al_load_bitmap("Resource/pic/knight_r.png");
    if (!enermy_img_r) {
        fprintf(stderr, "knight_r.png 로드 실패!\n");
        return;
    }
    enemy_boss_img_l = al_load_bitmap("Resource/pic/boss_l.png");
    if (!enemy_boss_img_l) {
        fprintf(stderr, "boss_l.png 로드 실패!\n");
        return;
    }
    enemy_boss_img_r = al_load_bitmap("Resource/pic/boss_r.png");
    if (!enemy_boss_img_r) {
        fprintf(stderr, "boss_r.png 로드 실패!\n");
        return;
    }

	char goblin_motion[50];
	for (int i = 0; i < FRAME_COUNT; i++) {
		sprintf_s(goblin_motion, sizeof(goblin_motion), "Resource/pic/goblin_sword_%d.png", i);
		goblin_sword[i] = al_load_bitmap(goblin_motion);
		if (!goblin_sword[i]) {
			printf("Failed to load image: %s\n", goblin_motion);
		}
	}

	char bat_motion[50];
	for (int i = 0; i < FRAME_COUNT; i++) {
		sprintf_s(bat_motion, sizeof(bat_motion), "Resource/pic/bat_%d.png", i);
		bat_sword[i] = al_load_bitmap(bat_motion);
		if (!bat_sword[i]) {
			printf("Failed to load image: %s\n", bat_motion);
		}
	}

	char zombie_motion[50];
	for (int i = 0; i < FRAME_COUNT; i++) {
		sprintf_s(zombie_motion, sizeof(zombie_motion), "Resource/pic/zombie_sword_%d.png", i);
		zombie_sword[i] = al_load_bitmap(zombie_motion);
		if (!zombie_sword[i]) {
			printf("Failed to load image: %s\n", zombie_motion);
		}
	}

	char knight_motion[50];
	for (int i = 0; i < FRAME_COUNT; i++) {
		sprintf_s(knight_motion, sizeof(knight_motion), "Resource/pic/knight_sword_%d.png", i);
		knight_sword[i] = al_load_bitmap(knight_motion);
		if (!knight_sword[i]) {
			printf("Failed to load image: %s\n", knight_motion);
		}
	}


    // 플레이어 이미지 로드
    player_img_l = al_load_bitmap("Resource/pic/player_l.png");
    if (!player_img_l) {
        fprintf(stderr, "player_l.png 로드 실패!\n");
        return;
    }
    player_img_r = al_load_bitmap("Resource/pic/player_r.png");
    if (!player_img_r) {
        fprintf(stderr, "player_r.png 로드 실패!\n");
        return;
    }

    // 투사체 이미지 로드
    fireball_img = al_load_bitmap("Resource/pic/fireball.png");
    if (!fireball_img) {
        fprintf(stderr, "fireball.png 로드 실패!\n");
        return;
    }
    fireball_boss_img = al_load_bitmap("Resource/pic/fireball_boss.png");
    if (!fireball_boss_img) {
        fprintf(stderr, "fireball.png 로드 실패!\n");
        return;
    }

    char laser[50];
    for (int i = 0; i < 6; i++) {
        sprintf_s(laser, sizeof(laser), "Resource/pic/laser_wait%d.png", i + 1);
        laser_img[i] = al_load_bitmap(laser);
        if (!laser_img[i]) {
            printf("Failed to load image: %s\n", laser);
        }
    }

    int scale_factor_width = 1;
    int scale_factor_height = 3;
    int new_width = al_get_bitmap_width(laser_img[0]) * scale_factor_width;
    int new_height = al_get_bitmap_height(laser_img[0]) * scale_factor_height;

    // 레이저 확대
    ALLEGRO_BITMAP* scaled_laser1;
    scaled_laser1 = al_create_bitmap(new_width, new_height);
    al_set_target_bitmap(scaled_laser1);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    al_draw_scaled_bitmap(
        laser_img[0],
        0, 0,
        al_get_bitmap_width(laser_img[0]), al_get_bitmap_height(laser_img[0]),
        0, 0,
        new_width, new_height,
        0
    );
    al_set_target_backbuffer(display);
    laser_img[6] = scaled_laser1;


    for (int i = 0; i < 6; ++i) {
        int scale_factor_width = 2;
        int scale_factor_height = 3;
        int new_width = al_get_bitmap_width(laser_img[i]) * scale_factor_width;
        int new_height = al_get_bitmap_height(laser_img[i]) * scale_factor_height;

        // 레이저 확대
        ALLEGRO_BITMAP* scaled_laser[6];
        scaled_laser[i]=al_create_bitmap(new_width, new_height);
        al_set_target_bitmap(scaled_laser[i]);
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_scaled_bitmap(
            laser_img[i],
            0, 0,
            al_get_bitmap_width(laser_img[i]), al_get_bitmap_height(laser_img[i]),
            0, 0,
            new_width, new_height,
            0
        );
        al_set_target_backbuffer(display);
        laser_img[i] = scaled_laser[i];

    }

    // HUD 이미지 로드
    HUD_score = al_load_bitmap("Resource/pic/score.png");
    if (!HUD_score) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    HUD_money = al_load_bitmap("Resource/pic/money.png");
    if (!HUD_money) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    HUD_life = al_load_bitmap("Resource/pic/life.png");
    if (!HUD_life) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    HUD_speed = al_load_bitmap("Resource/pic/speed.png");
    if (!HUD_speed) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    HUD_damage = al_load_bitmap("Resource/pic/damage.png");
    if (!HUD_damage) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    HUD_bullets = al_load_bitmap("Resource/pic/bullets.png");
    if (!HUD_bullets) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }

    // 상점 이미지 로드
    SHOP_ORIGIN = al_load_bitmap("Resource/pic/shop_icon.png");
    if (!SHOP_ORIGIN) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    SHOP_UP_BAT = al_load_bitmap("Resource/pic/bat_up.png");
    if (!SHOP_ORIGIN) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    SHOP_UP_ZOMBIE = al_load_bitmap("Resource/pic/zombie_up.png");
    if (!SHOP_ORIGIN) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    SHOP_UP_GOBLIN = al_load_bitmap("Resource/pic/goblin_up.png");
    if (!SHOP_ORIGIN) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    SHOP_UP_X = al_load_bitmap("Resource/pic/x.png");
    if (!SHOP_UP_X) {
        printf("이미지를 불러오지 못했습니다!\n");
        return;
    }
    SHOP_UP_ATT = al_create_sub_bitmap(SHOP_ORIGIN, 48, 0, 24, 24);
    SHOP_UP_SPD = al_create_sub_bitmap(SHOP_ORIGIN, 48, 48, 24, 24);
    SHOP_UP_BU = al_create_sub_bitmap(SHOP_ORIGIN, 48, 72, 24, 24);
    ULT = al_create_sub_bitmap(SHOP_ORIGIN, 24, 48, 24, 24);

    SHOP_UP_SPD_MAX = convert_to_grayscale(al_create_sub_bitmap(SHOP_ORIGIN, 144, 48, 24, 24));
    SHOP_UP_BU_MAX = convert_to_grayscale(al_create_sub_bitmap(SHOP_ORIGIN, 144, 72, 24, 24));
    SHOP_UP_ATT_NO = convert_to_grayscale(SHOP_UP_ATT);
    SHOP_UP_SPD_NO = convert_to_grayscale(SHOP_UP_SPD);
    SHOP_UP_BU_NO = convert_to_grayscale(SHOP_UP_BU);
    ULT_NO = convert_to_grayscale(ULT);

    // 디버프 이미지 로드
    debuff_background = al_load_bitmap("Resource/pic/debuff_background.png");
    if (!debuff_background) {
        printf("Cannot load debuff_background\n");
        return;
    }
    debuff_selection = al_load_bitmap("Resource/pic/debuff_select.png");
    if (!debuff_selection) {
        printf("Cannot load debuff_selection\n");
        return;
    }
    for (int i = 0; i < 6; i++) {
        // x 50, 366, 682 -> 316씩
        // y 156, 570 -> 414씩
        debuff[i] = al_create_sub_bitmap(debuff_selection, 50 + 316 * (i % 3), 156 + 414 * (i / 3), DEBUFF_WIDTH, DEBUFF_HEIGHT);
    }

    // 폰트 로드
    font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 70, 0);
    if (!font) {
        fprintf(stderr, "font 로드 실패!\n");
        return;
    }
    title_font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 120, 0);
    if (!title_font) {
        fprintf(stderr, "title_font 로드 실패!\n");
        return;
    }
    button_font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 70, 0);
    if (!button_font) {
        fprintf(stderr, "button_font 로드 실패!\n");
        return;
    }
    hud_font = al_load_ttf_font("Resource/font/DungGeunMo.otf", 50, 0);
    if (!hud_font) {
        fprintf(stderr, "hud_font 로드 실패!\n");
        return;
    }

    // 오디오 로드
    mainMenu = al_load_sample("Resource/audio/mainmenu.ogg");
    if (!mainMenu) {
        fprintf(stderr, "BGM load failed : mainmenu.ogg!\n");
        return;
    }
    sample1 = al_create_sample_instance(mainMenu);
    BGM = al_load_sample("Resource/audio/bgm.ogg");
    if (!BGM) {
        fprintf(stderr, "BGM load failed : bgm.ogg!\n");
        return;
    }
    sample2 = al_create_sample_instance(BGM);
    monster_hit = al_load_sample("Resource/audio/monster_hit.ogg");
    if (!monster_hit) {
        fprintf(stderr, "monster_hit 로드 실패!\n");
        return;
    }
    player_attack = al_load_sample("Resource/audio/player_attack.ogg");
    if (!player_attack) {
        fprintf(stderr, "player_attack 로드 실패!\n");
        return;
    }
    boss_summon = al_load_sample("Resource/audio/boss_summon.ogg");
    if (!player_attack) {
        fprintf(stderr, "boss_summon 로드 실패!\n");
        return;
    }
    laser_audio_1 = al_load_sample("Resource/audio/laser_reversed.ogg");
    if (!laser_audio_1) {
        fprintf(stderr, "laser_audio_1 로드 실패!\n");
        return;
    }
    laser_audio_2 = al_load_sample("Resource/audio/laser.ogg");
    if (!laser_audio_2) {
        fprintf(stderr, "laser_audio_2 로드 실패!\n");
        return;
    }
}

void destroy_resource(void) {
    for (int i = 0; i < 10; i++) al_destroy_bitmap(background[i]);
    al_destroy_bitmap(summon_img_l);
    al_destroy_bitmap(summon_img_r);
    al_destroy_bitmap(goblin_sword[0]);
    al_destroy_bitmap(goblin_sword[1]);
    al_destroy_bitmap(goblin_sword[2]);
    al_destroy_bitmap(goblin_sword[3]);
    al_destroy_bitmap(summon2_img_l);
    al_destroy_bitmap(summon2_img_r);
    al_destroy_bitmap(summon3_img_r);
    al_destroy_bitmap(enermy_img_l);
    al_destroy_bitmap(enermy_img_r);
    al_destroy_bitmap(enemy_boss_img_l);
    al_destroy_bitmap(enemy_boss_img_r);
    al_destroy_bitmap(player_img_l);
    al_destroy_bitmap(player_img_r);
    al_destroy_bitmap(fireball_img);
    al_destroy_bitmap(fireball_boss_img);
    al_destroy_bitmap(HUD_score);
    al_destroy_bitmap(HUD_money);
    al_destroy_bitmap(HUD_life);
    al_destroy_bitmap(HUD_speed);
    al_destroy_bitmap(HUD_damage);
    al_destroy_bitmap(HUD_bullets);
    al_destroy_bitmap(SHOP_ORIGIN);
    al_destroy_bitmap(SHOP_UP_ATT);
    al_destroy_bitmap(SHOP_UP_ATT_NO);
    al_destroy_bitmap(SHOP_UP_SPD);
    al_destroy_bitmap(SHOP_UP_SPD_NO);
    al_destroy_bitmap(SHOP_UP_SPD_MAX);
    al_destroy_bitmap(SHOP_UP_BU);
    al_destroy_bitmap(SHOP_UP_BU_NO);
    al_destroy_bitmap(SHOP_UP_BU_MAX);
    al_destroy_bitmap(SHOP_UP_BAT);
    al_destroy_bitmap(SHOP_UP_ZOMBIE);
    al_destroy_bitmap(SHOP_UP_GOBLIN);
    al_destroy_bitmap(SHOP_UP_X);
    al_destroy_bitmap(debuff_background);
    al_destroy_bitmap(debuff_selection);
    for (int i = 0; i < AMOUNT_DEBUFF; i++) al_destroy_bitmap(debuff[i]);

    al_destroy_display(display);

    al_destroy_event_queue(event_queue);

    al_destroy_timer(timer);
    al_destroy_timer(spawn_timer);
    al_destroy_timer(spawn_timer_boss);

    al_destroy_font(font);
    al_destroy_font(title_font);
    al_destroy_font(button_font);
    al_destroy_font(hud_font);

    al_destroy_sample(mainMenu);
    al_destroy_sample(BGM);
    al_destroy_sample(monster_hit);
    al_destroy_sample(player_attack);
    al_destroy_sample(boss_summon);
}


ALLEGRO_BITMAP* convert_to_grayscale(ALLEGRO_BITMAP* original) {
	int width = al_get_bitmap_width(original);
	int height = al_get_bitmap_height(original);

	ALLEGRO_BITMAP* gray_bitmap = al_create_bitmap(width, height);
	if (!gray_bitmap) {
		printf("그레이스케일 비트맵 생성 실패!\n");
		return NULL;
	}
    
	al_set_target_bitmap(gray_bitmap);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			ALLEGRO_COLOR color = al_get_pixel(original, x, y);
			unsigned char r, g, b;
			al_unmap_rgb(color, &r, &g, &b);

			// ITU-R BT.601 가중치를 적용한 그레이스케일 변환
			unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);

			al_put_pixel(x, y, al_map_rgb(gray, gray, gray));
		}
	}

	al_set_target_backbuffer(al_get_current_display());

	return gray_bitmap;
}
