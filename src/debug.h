#include <stdio.h>
#include <string.h>
#include <math.h>

TextLayer debug_layer;

//int get_int_length(int number)
//{
//	return (int)(log10(number)) + 1;
//}
	
//void convert_to_char(int number, char *converted)
//{
//	sprintf(converted, "%d", number);
//}

void debug_out(TextLayer *output_layer, const char *text)
{
	text_layer_set_text(output_layer, text);
}

//void debug_out_int(TextLayer *output_layer, int value)
//{
//	int length = get_int_length(value);
//	char buffer[length];
//	convert_to_char(value, buffer);
//	debug_out(output_layer, buffer);
//}

void debug_init()
{
	text_layer_init(&debug_layer, GRect(0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50));
	text_layer_set_background_color(&debug_layer, GColorBlack);
	text_layer_set_text_color(&debug_layer, GColorWhite);
}