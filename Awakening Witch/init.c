#include "init.h"

void reset_game_state() {
    // 배경 초기화
    al_stop_sample(sample1);
    al_play_sample(BGM, 0.3, 0, 1, ALLEGRO_PLAYMODE_LOOP, sample2);
    for(int i = 0; i < 3; ++i) now_alley[i] = 0;
    // 플레이어 초기화
    player.health = PLAYER_HEALTH;
    //player.health = 1;
    player.damage = BULLET_DAMAGE;
    player.speed = PLAYER_SPEED;
    player.sees_left = true;
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.bullets = 3;
    invincible_timer = 0;
    player.player_att_delay = ATTACK_DELAY;
    COST_ULT = 1;
    /*for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        key[i] = 0;
    }*/
    memset(key, 0, sizeof(key));

    // 점수 및 재화 초기화
    score_display = 0;
    money_display = 0;
    prev_score = 0;
    score_multiplier = 1.0f;
    //score_display = 1000;
    //money_display = 100000;

    // 난이도 초기화
    enemy_health_plus = 0;
    boss_attack_delay = 20;
    boss_bullet_speed = 0.5f; 
    knights_amount = 3;
    debuff_damage_knight = 0;
    debuff_amount_bossbullet = 5;

    // 모션 초기화
    for (int i = 0; i < MAX_GOBLINS; ++i) {
        current_frame[i] = 0;
        current_enemies_frame[i] = 0;
        last_update_time[i] = 0;
        last_update_enemies_time[i] = 0;
    }

    // 전체 몬스터 수
    MAX_SUMMONS = MAX_ZOMBIES + MAX_GOBLINS + MAX_BATS;
    MAX_ENEMIES = MAX_KNIGHTS + MAX_BOSSES;

    // 몬스터 초기화
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;  // 모든 적 비활성화
      // 모든 적 보스 
        enemies[i].matched_enemy = -1;
    }

    // 소환수 초기화
    for (int i = 0; i < MAX_SUMMONS; i++) {
        summons[i].active = false;  // 모든 소환수 비활성화
        summons[i].matched_enemy = -1;
    }

    // 투사체 관련 초기화
    for (int i = 0; i < player.bullets; i++) {
        bullets[i].active = false;
    }
    for (int i = 0; i < MAX_BOSSES; i++) {
        for (int j = 0; j < MAX_BULLETS; j++) {
            boss_bullets[i][j].active = false;
        }
    }

    // 보스 타이머 초기화
    for (int i = 0; i < MAX_BOSSES; i++) {
        boss_laser_timer[i] = 0;
    }

    // 플레이어 공격 관련 초기화
    last_att = 0;  // 공격 타이밍 초기화
}

void reset_keyboard_event() {
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        key[i] = false;
    }
}

void init(void) {
    backstage = 0;
    strcpy(state, "menu");
    //strcpy(state, "game");
    srand(time(NULL));

    if (!al_init()) {
        fprintf(stderr, "Allegro 초기화 실패!\n");
        return;
    }
    last_att = -1.0f;

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "디스플레이 생성 실패!\n");
        return;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Allegro primitives 초기화 실패!\n");
        return;
    }
    if(!al_init_image_addon()) {
        fprintf(stderr, "Allegro image 초기화 실패!\n");
        return;
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Allegro mouse 초기화 실패!\n");
        return;
    }
    if(!al_install_keyboard()) {
        fprintf(stderr, "Allegro keyboard 초기화 실패!\n");
        return;
    }
    if(!al_init_font_addon()) {
        fprintf(stderr, "Allegro font 초기화 실패!\n");
        return;
    }
    if(!al_init_ttf_addon()) {
        fprintf(stderr, "Allegro ttf 초기화 실패!\n");
        return;
    }
    if (!al_install_audio()) {
        fprintf(stderr, "Allegro audio 초기화 실패!\n");
        return;
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Allegro audio 초기화 실패!\n");
        return;
    }

    for (int i = 0; i < MAX_SUMMONS; i++) enemies[i].matched_enemy = -1;
    for (int i = 0; i < MAX_SUMMONS; i++) summons[i].matched_enemy = -1;

    al_reserve_samples(16);
    load_resource();
    hud_init();

    timer = al_create_timer(1.0 / 60.0);
    spawn_timer = al_create_timer(2.0);
    spawn_timer_boss = al_create_timer(15.0);
    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(spawn_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(spawn_timer_boss));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());    
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);
    al_start_timer(spawn_timer);
    al_start_timer(spawn_timer_boss);

    al_draw_scaled_bitmap(background[backstage], 0, 0, al_get_bitmap_width(background[backstage]), al_get_bitmap_height(background[backstage]),
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    al_flip_display();
}