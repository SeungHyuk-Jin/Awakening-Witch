#include "level.h"

void level_up(void) {
	int cnt = 0, ran[AMOUNT_DEBUFF] = { 0 }, sel[AMOUNT_DEBUFF] = { 0 };
	while (cnt < 3) {
		int tmp = rand() % AMOUNT_DEBUFF;
		if (tmp == 1 && knights_amount == MAX_KNIGHTS) continue;
		if (!ran[tmp]) {
			ran[tmp] = 1; sel[cnt++] = tmp;
		}
	}
	cnt = 0;
	while(1) {
		al_draw_scaled_bitmap(debuff_background, 
			0, 0, al_get_bitmap_width(debuff_background), al_get_bitmap_height(debuff_background),
			100, 100,
			SCREEN_WIDTH - 200, al_get_bitmap_height(debuff_background) + 300, 0);
		al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 150, ALLEGRO_ALIGN_CENTER, "Select new debuff");
		for (int i = 0; i < 3; i++) {
			al_draw_bitmap(debuff[sel[i]], SCREEN_WIDTH / 2 - DEBUFF_WIDTH / 2 - DEBUFF_WIDTH - 50 + (DEBUFF_WIDTH + 50) * i, 350, 0);
		}
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			int x = ev.mouse.x;
			int y = ev.mouse.y;

			// sel[0] 처리
			if (debuff_button(x, y, SCREEN_WIDTH / 2 - DEBUFF_WIDTH / 2 - (DEBUFF_WIDTH + 50), 350)) {
				debuff_action(sel[0]);
				break;
			}
			// sel[1] 처리
			else if (debuff_button(x, y, SCREEN_WIDTH / 2 - DEBUFF_WIDTH / 2, 350)) {
				debuff_action(sel[1]);
				break;
			}
			// sel[2] 처리
			else if (debuff_button(x, y, SCREEN_WIDTH / 2 - DEBUFF_WIDTH / 2 + (DEBUFF_WIDTH + 50), 350)) {
				debuff_action(sel[2]);
				break;
			}
		}

		al_flip_display();
	}
	backstage = (backstage + 1) % 10;
	COST_ULT = 1;
	// for debug
	//printf("update backstage : %d", backstage);
}

void debuff_action(int flg) {
	if (flg == 0) {
		// 보스 탄막 속도 증가
		boss_bullet_speed += 0.3f;
		score_multiplier += 0.2f;
	}
	else if (flg == 1) {
		// 몬스터 수 증가
		++knights_amount;
		score_multiplier += 0.1f;
	}
	else if (flg == 2) {
		// 기사 몸박뎀 증가
		++debuff_damage_knight;
		score_multiplier += 0.5f;
	}
	else if (flg == 3) {
		// 몬스터 체력 증가
		++enemy_health_plus;
		score_multiplier += 0.3f;
	}
	else if (flg == 4) {
		// 보스 탄막 갯수 증가
		++debuff_amount_bossbullet;
		score_multiplier += 0.1f;
	}
	else if (flg == 5) {
		// 모든 디버프 활성화, 배수 더 높음
		boss_bullet_speed += 0.3f;
		++knights_amount;
		++debuff_damage_knight;
		++enemy_health_plus;
		++debuff_amount_bossbullet;
		score_multiplier += 1.0f;
	}
}
int debuff_button(int mouse_x, int mouse_y, int button_x, int button_y) {
	int button_width = DEBUFF_WIDTH, button_height = DEBUFF_HEIGHT;
	return mouse_x >= button_x && mouse_x <= button_x + button_width
		&& mouse_y >= button_y && mouse_y <= button_y + button_height;
}