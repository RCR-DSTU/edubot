#include "demo.h"
#include "ssd1306.h"

char* rcr = " RCR";
char* dstu = "DSTU";
char* menu = "Main menu";
char* items_menu[] = {"Program #1", "Program #2", "Program #3", "Program #4", "Program #5"};

int show_menu_items_X = 10, show_menu_items_Y = 18;
int indicator_X = 8, indicator_Y = 16;


void FirstScreen()
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(12, 4);
	SSD1306_Puts(rcr, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(84, 4);
	SSD1306_Puts(dstu, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_Image(logo_RCR_40x40, 40, 40, 10, 16);
	SSD1306_Image(logo_DSTU_40x40, 40, 40, 80, 16);

}


void MenuRectangle()
{
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts(menu, &Font_7x10, SSD1306_COLOR_WHITE);
}


void ShowMenuItems()
{
	for(int i = 0; i < 3; i++)
	  {
		  SSD1306_GotoXY(show_menu_items_X, show_menu_items_Y);
		  SSD1306_Puts(items_menu[i], &Font_7x10, SSD1306_COLOR_WHITE);
		  show_menu_items_Y += 15;
	  }
}


void Indicator()
{
//	if(indicator_Y < 8)
//	{
//		SSD1306_DrawFilledRectangle(indicator_X, indicator_Y, 110, 14, SSD1306_COLOR_WHITE);
//		continue;
//	}

	SSD1306_DrawFilledRectangle(indicator_X, indicator_Y, 110, 14, SSD1306_COLOR_WHITE);
}






