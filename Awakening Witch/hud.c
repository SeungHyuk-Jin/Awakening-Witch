#include "hud.h"

// hud
void hud_init() {
	score_display = 0;
}

void hud_draw() {
	al_draw_scaled_bitmap(HUD_score, 0, 0, 
		al_get_bitmap_width(HUD_score), al_get_bitmap_height(HUD_score),
		50, 55, 40, 40, 0);
	al_draw_scaled_bitmap(HUD_money, 0, 0, 
		al_get_bitmap_width(HUD_money), al_get_bitmap_height(HUD_money),
		50, 105, 40, 40, 0);
	al_draw_scaled_bitmap(HUD_speed, 0, 0, 
		al_get_bitmap_width(HUD_speed), al_get_bitmap_height(HUD_speed),
		50, 210, 40, 40, 0);
	al_draw_scaled_bitmap(HUD_damage, 0, 0, 
		al_get_bitmap_width(HUD_damage), al_get_bitmap_height(HUD_damage),
		220, 210, 40, 40, 0);
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 1310, 0, 0, "Q");
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 1365, 0, 0, "W");
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 1420, 0, 0, "E");
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 325, 100, 0, "R");
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 1310, 150, 0, "A");
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 1365, 150, 0, "S");
	al_draw_text(hud_font, al_map_rgb_f(1, 1, 1), 1420, 150, 0, "D");
	al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 1310, 200, 0, "%1d", now_alley[2]);
	al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 1365, 200, 0, "%1d", now_alley[0]);
	al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 1420, 200, 0, "%1d", now_alley[1]);
	al_draw_textf(
		hud_font,
		al_map_rgb_f(1, 1, 1),
		100, 50,
		0,
		"%06ld",
		score_display
	); 
	al_draw_textf(
		hud_font,
		al_map_rgb_f(1, 1, 1),
		270, 50,
		0,
		"x%.1f",
		score_multiplier
	);
	al_draw_textf(
		hud_font,
		al_map_rgb_f(1, 1, 1),
		100, 100,
		0,
		"%06ld",
		money_display
	);
	al_draw_textf(
		hud_font,
		al_map_rgb_f(1, 1, 1),
		270, 200,
		0,
		"%.1f",
		player.damage
	);
	if (player.player_att_delay <= 0.01) {
		al_draw_textf(
			hud_font,
			al_map_rgb_f(1, 1, 1),
			100, 200,
			0,
			"MAX"
		);
	}
	else {
		al_draw_textf(
			hud_font,
			al_map_rgb_f(1, 1, 1),
			100, 200,
			0,
			"%.2f",
			player.player_att_delay
		);
	}
	for (int i = 0; i < player.health; ++i) {
		al_draw_scaled_bitmap(HUD_life, 0, 0, al_get_bitmap_width(HUD_life),
			al_get_bitmap_height(HUD_life), 50 + i * 50, 160, 40, 40, 0);
	}

	int cnt = 0;
	for (int i = 0; i < player.bullets; ++i) {
		if (!bullets[i].active) {
			al_draw_scaled_bitmap(HUD_bullets, 0, 0, al_get_bitmap_width(HUD_bullets),
				al_get_bitmap_height(HUD_bullets), 50 + cnt * 30, 260, 40, 40, 0);
			cnt++;
		}
	}
	al_draw_scaled_bitmap(SHOP_UP_BAT, 0, 0, al_get_bitmap_width(SHOP_UP_BAT),
		al_get_bitmap_height(SHOP_UP_BAT), 1295, 105, 55, 55, 0);
	al_draw_scaled_bitmap(SHOP_UP_ZOMBIE, 0, 0, al_get_bitmap_width(SHOP_UP_ZOMBIE),
		al_get_bitmap_height(SHOP_UP_ZOMBIE), 1350, 105, 55, 55, 0);
	al_draw_scaled_bitmap(SHOP_UP_GOBLIN, 0, 0, al_get_bitmap_width(SHOP_UP_GOBLIN),
		al_get_bitmap_height(SHOP_UP_GOBLIN), 1405, 105, 55, 55, 0);

	if (money_display >= COST_ATT) {
		al_draw_scaled_bitmap(SHOP_UP_ATT, 0, 0, al_get_bitmap_width(SHOP_UP_ATT),
			al_get_bitmap_height(SHOP_UP_ATT), 1350, 50, 55, 55, 0);
	}
	else {
		al_draw_scaled_bitmap(SHOP_UP_ATT_NO, 0, 0, al_get_bitmap_width(SHOP_UP_ATT_NO),
			al_get_bitmap_height(SHOP_UP_ATT_NO), 1350, 50, 55, 55, 0);
	}
	if (player.player_att_delay <= 0.01) {
		al_draw_scaled_bitmap(SHOP_UP_SPD_MAX, 0, 0, al_get_bitmap_width(SHOP_UP_SPD_MAX),
			al_get_bitmap_height(SHOP_UP_SPD_MAX), 1295, 50, 55, 55, 0);
	}
	else if (money_display >= COST_SPD) {
		al_draw_scaled_bitmap(SHOP_UP_SPD, 0, 0, al_get_bitmap_width(SHOP_UP_SPD),
			al_get_bitmap_height(SHOP_UP_SPD), 1295, 50, 55, 55, 0);
	}
	else {
		al_draw_scaled_bitmap(SHOP_UP_SPD_NO, 0, 0, al_get_bitmap_width(SHOP_UP_SPD_NO),
			al_get_bitmap_height(SHOP_UP_SPD_NO), 1295, 50, 55, 55, 0);
	}
	if (player.bullets >= MAX_PLAYER_BULLETS) {
		al_draw_scaled_bitmap(SHOP_UP_BU_MAX, 0, 0, al_get_bitmap_width(SHOP_UP_BU_MAX),
			al_get_bitmap_height(SHOP_UP_BU_MAX), 1405, 50, 55, 55, 0);
	}
	else if (money_display >= COST_BU) {
		al_draw_scaled_bitmap(SHOP_UP_BU, 0, 0, al_get_bitmap_width(SHOP_UP_BU),
			al_get_bitmap_height(SHOP_UP_BU), 1405, 50, 55, 55, 0);
	}
	else {
		al_draw_scaled_bitmap(SHOP_UP_BU_NO, 0, 0, al_get_bitmap_width(SHOP_UP_BU_NO),
			al_get_bitmap_height(SHOP_UP_BU_NO), 1405, 50, 55, 55, 0);
	}
	
	if (COST_ULT) {
		al_draw_scaled_bitmap(ULT, 0, 0, al_get_bitmap_width(ULT),
			al_get_bitmap_height(ULT), 270, 105, 40, 40, 0);
	}
	else {
		al_draw_scaled_bitmap(ULT_NO, 0, 0, al_get_bitmap_width(ULT_NO),
			al_get_bitmap_height(ULT_NO), 270, 105, 40, 40, 0);
	}

	if (summons[0 + MAX_GOBLINS + MAX_ZOMBIES].active && summons[1 + MAX_GOBLINS + MAX_ZOMBIES].active && summons[2 + MAX_GOBLINS + MAX_ZOMBIES].active && summons[3 + MAX_GOBLINS + MAX_ZOMBIES].active && summons[4 + MAX_GOBLINS + MAX_ZOMBIES].active) {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1295, 105, 55, 55, 0);
	}
	else if (money_display < COST_BAT) {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1295, 105, 55, 55, 0);
	}
	/*else {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1295, 105, 55, 55, 0);
	}*/
	if (summons[0].active && summons[1].active && summons[2].active && summons[3].active && summons[4].active) {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1350, 105, 55, 55, 0);
	}
	else if (money_display < COST_ZOMBIE) {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1350, 105, 55, 55, 0);
	}
	/*else {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1350, 105, 0, 0, 0);
	}*/
	if (summons[0 + MAX_ZOMBIES].active && summons[1 + MAX_ZOMBIES].active && summons[2 + MAX_ZOMBIES].active && summons[3 + MAX_ZOMBIES].active && summons[4 + MAX_ZOMBIES].active) {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1405, 105, 55, 55, 0);
	}
	else if (money_display < COST_GOBLIN) {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1405, 105, 55, 55, 0);
	}
	/*else {
		al_draw_scaled_bitmap(SHOP_UP_X, 0, 0, al_get_bitmap_width(SHOP_UP_X),
			al_get_bitmap_height(SHOP_UP_X), 1405, 105, 0, 0, 0);
	}*/

}