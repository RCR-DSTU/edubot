#include "demo.h"


char* items_menu[2][3] = {
					{"Program #1", "Program #2", "Program #3"},
					{"Program #4", "Program #5", "Program #6"}
						 };

char* names_parameters[] = {"distn", "name2", "name3", "name4", "name5", "name6"};
//char* names_program[] = {"Task1", "Task2", "Task3", "Task4", "Task5", "Task6"};


const uint8_t show_menu_items_X = 10;
uint8_t show_menu_items_Y = 18;

const uint8_t indicator_X = 8;
uint8_t indicator_Y = 16;

const uint8_t progress_bar_X = 14;
uint8_t progress_bar_Y = 43;

uint8_t number_page = 0;
uint8_t number_program = 0;
uint8_t number_clicks_button5 = 0;

float parameter_value = 0.0;
char str[4];




void FirstScreen()
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_GotoXY(12, 4);
	SSD1306_Puts(" RCR", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(84, 4);
	SSD1306_Puts("DSTU", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_Image(logo_RCR_40x40, 40, 40, 10, 16);
	SSD1306_Image(logo_DSTU_40x40, 40, 40, 80, 16);

}


void MenuRectangle()
{
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts("Main menu", &Font_7x10, SSD1306_COLOR_WHITE);
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
	SSD1306_UpdateScreen();
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


void ParameterMenu(uint8_t value)
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(22, 31, 84, 15, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts("Settings", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(22, 20);
	SSD1306_Puts("Select ", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(71, 20);
	SSD1306_Puts(names_parameters[value], &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(56, 34);
	sprintf(str, "%.1f", parameter_value);
	SSD1306_Puts(str, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}


void SelectParameter(bool IsUp)
{
	switch(IsUp)
	{
		case true:
			parameter_value += 0.1;
			break;
		case false:
			 if(parameter_value != 0.0)
			 {
				 parameter_value -= 0.1;
				 break;
			 }
			break;
	}
}


void ScreenExecution(uint8_t value)
{
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_DrawRectangle(3, 3, 122, 58, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(3, 3, 122, 12, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(36, 4);
	SSD1306_Puts("Progress", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(14, 43, 100, 12, SSD1306_COLOR_WHITE);
//	SSD1306_GotoXY(48, 44);
//	SSD1306_Puts(names_program[value], &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(10, 18);
	SSD1306_Puts("Speed:", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_GotoXY(10, 30);
	SSD1306_Puts("Distance:", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
	ProgressBar(0.5);
	SSD1306_UpdateScreen();

}


void ProgressBar(float progress)
{
	if(progress < 0.0 || progress > 1.00 ) return;

	uint16_t pixels = 100 * progress;
		SSD1306_DrawFilledRectangle(progress_bar_X, progress_bar_Y, pixels, 12, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();


}









