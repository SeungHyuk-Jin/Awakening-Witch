#include "menu.h"

void draw_menu() {
    // 배경 이미지 크기 맞추기
    al_draw_scaled_bitmap(background[backstage], 0, 0, al_get_bitmap_width(background[backstage]), al_get_bitmap_height(background[backstage]),
        0, 0, 1500, 900, 0);  // 화면 크기 1500x900으로 변경

    // 제목 텍스트는 여전히 가운데 정렬
    al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 220, ALLEGRO_ALIGN_CENTER, "Awaken Witch");

    // 버튼 크기와 위치 조정
    int button_width = 600;  // 버튼의 너비를 키움
    int button_height = 70;  // 버튼의 높이를 키움
    int button_x = 1500 / 2 - button_width / 2;  // 버튼을 가운데에 정렬
    int button_y = 400;  // 첫 번째 버튼의 y 좌표


    // 텍스트 크기 설정
    int text_size = 70;  // 텍스트 크기 키움

    // 텍스트 위치를 버튼 중앙에 맞추기 위해 버튼 중앙에 맞게 정렬
    const char* button_labels[] = { "Play", "Rankings", "Exit" };
    int num_buttons = sizeof(button_labels) / sizeof(button_labels[0]);

    for (int i = 0; i < num_buttons; i++) {
        al_draw_text(button_font, al_map_rgb(0, 0, 0),
            button_x + button_width / 2,
            button_y + button_height / 2 - text_size / 2 + i * 100,
            ALLEGRO_ALIGN_CENTER, button_labels[i]);
    }
}

bool is_button_clicked(int mouse_x, int mouse_y, int button_y_offset) {
    int button_width = 600;  // 버튼의 너비
    int button_height = 70;  // 버튼의 높이
    int button_x = 1500 / 2 - button_width / 2;  // 버튼의 X 좌표는 여전히 가운데로
    int button_y = 400 + button_y_offset;  // 버튼의 Y 좌표 (offset에 따라 조정)

    return mouse_x >= button_x && mouse_x <= button_x + button_width && mouse_y >= button_y && mouse_y <= button_y + button_height;
}

void show_rankings(ALLEGRO_FONT* font) {
    Player1 players[5];  
    int num_players = read_rankings(players, 5);

    static bool has_displayed_message = false; // 메시지 중복 방지

    if (num_players == 0 && !has_displayed_message) {
        printf("No rankings to display.\n");
        has_displayed_message = true; // 한 번만 출력하도록 설정
        return;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 90, ALLEGRO_ALIGN_CENTER, "Rankings");

    for (int i = 0; i < num_players; i++) {
        char ranking_text[50];
        sprintf_s(ranking_text, sizeof(ranking_text), "%d. %s - %d", i + 1, players[i].name, players[i].score);
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 300 + (i * 70), ALLEGRO_ALIGN_CENTER, ranking_text);
    }

    int button_width = 200;
    int button_height = 110;
    int last_rank_y = 300 + (num_players * 70);
    int button_x = SCREEN_WIDTH / 2 - button_width - 20;
    int button_y = last_rank_y + 50;

    // "Back" 버튼
    al_draw_filled_rectangle(button_x, button_y, button_x + button_width, button_y + button_height, al_map_rgb(255, 255, 255));
    al_draw_rectangle(button_x, button_y, button_x + button_width, button_y + button_height, al_map_rgb(0, 0, 0), 3);
    al_draw_text(font, al_map_rgb(0, 0, 0), button_x + button_width / 2, button_y + 15, ALLEGRO_ALIGN_CENTER, "Back");

    // "Clear" 버튼
    int clear_x = SCREEN_WIDTH / 2 + 20;
    al_draw_filled_rectangle(clear_x, button_y, clear_x + button_width, button_y + button_height, al_map_rgb(255, 0, 0));
    al_draw_rectangle(clear_x, button_y, clear_x + button_width, button_y + button_height, al_map_rgb(0, 0, 0), 3);
    al_draw_text(font, al_map_rgb(0, 0, 0), clear_x + button_width / 2, button_y + 15, ALLEGRO_ALIGN_CENTER, "Clear");

    al_flip_display();

    // ?? 버튼 클릭 이벤트 감지 추가
    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Back 버튼 클릭 확인
            if (mouse_x >= button_x && mouse_x <= button_x + button_width &&
                mouse_y >= button_y && mouse_y <= button_y + button_height) {
                strcpy(state, "menu");
                running = false;  // 루프 종료 → 메뉴로 돌아감
            }

            // Clear 버튼 클릭 확인
            if (mouse_x >= clear_x && mouse_x <= clear_x + button_width &&
                mouse_y >= button_y && mouse_y <= button_y + button_height) {
                clear_rankings();  // 랭킹 초기화
                running = false;  // 루프 종료 → 메뉴로 돌아감
            }
        }

        // ESC 키 입력 시 메뉴로 돌아가기
        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            strcpy(state, "menu");
            running = false;
        }
    }
}

int read_rankings(Player1 players[], int max_players) {
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "r");
    if (!file) {
        printf("파일 열기 실패!\n");
        return 0;
    }

    Player1 all_players[100]; // 최대 100명까지 저장 가능하도록 설정 (필요하면 조절 가능)
    int num_players = 0;

    // 모든 데이터를 읽어들임
    while (fscanf_s(file, "%19s %d", all_players[num_players].name,
        (unsigned)_countof(all_players[num_players].name),
        &all_players[num_players].score) == 2) {
        num_players++;
        if (num_players >= 100) break; // 100명을 초과하면 중단
    }

    fclose(file);

    // 점수 기준으로 내림차순 정렬
    qsort(all_players, num_players, sizeof(Player1), compare_players);

    // 상위 max_players명만 저장
    int limit = (num_players < max_players) ? num_players : max_players;
    for (int i = 0; i < limit; i++) {
        players[i] = all_players[i];
    }

    return limit;  // 최종적으로 저장된 플레이어 수 반환
}


// 점수 기준으로 내림차순으로 비교 함수
int compare_players(const void* a, const void* b) {
    Player1* playerA = (Player1*)a;
    Player1* playerB = (Player1*)b;

    return playerB->score - playerA->score;  // 내림차순 정렬
}

void rank(void) {
    show_rankings(font);

    ALLEGRO_EVENT ranking_event;
    al_wait_for_event(event_queue, &ranking_event);

    if (ranking_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
        (ranking_event.type == ALLEGRO_EVENT_KEY_DOWN && ranking_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
        strcpy(state, "menu");
    }
}

void save_score(const char* player_name, long score) {
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "a");
    if (file) {
        fprintf(file, "%s %ld\n", player_name, score);
        fclose(file);
    }
    else {
        printf("점수 저장 실패!\n");
    }
}

void clear_rankings() {
    FILE* file;
    fopen_s(&file, "Resource/rank_db/rank.txt", "w");
    if (file) {
        fclose(file);
        printf("랭킹 데이터 초기화 완료!\n");
    }
    else {
        printf("랭킹 초기화 실패!\n");
    }
}

void name(ALLEGRO_FONT* font) {
    char name[20] = { 0 };
    int index = 0;
    bool done = false;

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && index > 0) {
                name[--index] = '\0';
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                done = true;
            }
            else if (index < sizeof(name) - 1) {  // 배열 오버플로우 방지
                if (event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_A + 'A';
                }
                else if (event.keyboard.keycode >= ALLEGRO_KEY_0 && event.keyboard.keycode <= ALLEGRO_KEY_9) {
                    name[index++] = event.keyboard.keycode - ALLEGRO_KEY_0 + '0';
                }
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Please enter your name:");
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTER, name);
        al_flip_display();
    }

    save_score(name, score_display);
    printf("입력한 이름: %s, 점수: %ld\n", name, score_display);
}

void exit_game() {
    al_uninstall_system();
    exit(0);
}
