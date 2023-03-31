#include "demo.h"
#include "ssd1306.h"

char* rcr = " RCR";
char* dstu = "DSTU";
const char* items_menu[] = {"Program #1", "Program #2", "Program #3", "Program #4", "Program #5"};

void FirstScreen()
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(13, 4);
	SSD1306_Puts(rcr, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(82, 4);
	SSD1306_Puts(dstu, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_Image(logo_RCR_40x40, 40, 40, 10, 16);
	SSD1306_Image(logo_DSTU_40x40, 40, 40, 80, 16);

}
