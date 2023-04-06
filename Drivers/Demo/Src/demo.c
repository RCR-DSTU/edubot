#include "demo.h"
#include "ssd1306.h"
#include <stdio.h>


char* rcr = " RCR";
char* dstu = "DSTU";
char* menu = "Main menu";
char* settings = "Settings";

char* names_parameters[] = {"name 1", "name2", "name3", "name4", "name5", "name6"};




char* items_menu[2][3] = {
					{"Program #1", "Program #2", "Program #3"},
					{"Program #4", "Program #5", "Program #6"}
						 };


int show_menu_items_X = 10;
int show_menu_items_Y = 18;
int indicator_X = 8;
int indicator_Y = 16;

int number_page = 0;
int number_program = 0;

int parameter_value = 1;
char str[3];




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
		SSD1306_Puts(items_menu[number_page][i], &Font_7x10, SSD1306_COLOR_WHITE);
		show_menu_items_Y += 15;
	}

	show_menu_items_Y = 18;
}


void Indicator(bool IsUp)
{
	switch (IsUp)
			{
				case true:
					if(indicator_Y <= 18 && number_page == 0)
					{
						break;
					}
					else if(indicator_Y <= 18 && number_page != 0)
					{
						number_page -= 1;
						indicator_Y = 46;
						number_program -= 1;
						break;
					}
					indicator_Y -= 15;
					number_program -= 1;

					break;
				case false:
					if(indicator_Y >= 46 && number_page == 1)
					{
						break;
					}
					else if(indicator_Y >= 46 && number_page < 2 )
					{
						number_page += 1;
						indicator_Y = 16;
						number_program += 1;
						break;
					}
					indicator_Y += 15;
					number_program += 1;
					break;
			}

}


void NewFrameMenu()
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	MenuRectangle();
	SSD1306_DrawFilledRectangle(indicator_X, indicator_Y, 110, 13, SSD1306_COLOR_WHITE);
	ShowMenuItems();
}


void ParameterMenu(int value)
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(22, 31, 84, 15, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts(settings, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(22, 20);
	SSD1306_Puts("Select ", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(71, 20);
	SSD1306_Puts(names_parameters[value], &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(63, 34);
	sprintf(str, "%d", parameter_value);
	SSD1306_Puts(str, &Font_7x10, SSD1306_COLOR_WHITE);

}


void SelectParameter(bool IsUp)
{
	switch(IsUp)
	{
		case true:
			parameter_value += 1;
			break;
		case false:
			 if(parameter_value != 1)
			 {
				 parameter_value -= 1;
				 break;
			 }
			break;
	}
}









