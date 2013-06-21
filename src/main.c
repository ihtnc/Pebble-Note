#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "note.h"
#include "debug.h"

#define MY_UUID { 0x84, 0x12, 0x47, 0xF4, 0x1D, 0x85, 0x4E, 0xFB, 0x90, 0x9E, 0x44, 0xA7, 0xC0, 0x43, 0xAE, 0x96 }

PBL_APP_INFO(MY_UUID,
             NOTE_NAME, "ihopethisnamecounts",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
ScrollLayer scroll_layer;
TextLayer content_layer;

void handle_init(AppContextRef ctx) 
{
	(void)ctx;
		
	window_init(&window, "Watchface");
	window_stack_push(&window, true /* Animated */);
	window_set_fullscreen(&window, true);
	
	GContext *gctx = app_get_current_graphics_context();
	GSize content_size = graphics_text_layout_get_max_used_size
		(gctx, 
		 text_content, 
		 fonts_get_system_font(TEXT_FONT), 
		 MAX_WINDOW_FRAME, 
		 TEXT_OVERFLOWMODE, 
		 TEXT_ALIGNMENT, 
		 NULL);
	
	text_layer_init(&content_layer, GRect(0, 0, content_size.w, content_size.h));	
	text_layer_set_overflow_mode(&content_layer, TEXT_OVERFLOWMODE);
	text_layer_set_font(&content_layer, fonts_get_system_font(TEXT_FONT));
	text_layer_set_text_alignment(&content_layer, TEXT_ALIGNMENT);
	text_layer_set_text(&content_layer, text_content);
	layer_set_clips(&content_layer.layer, false);
	
	scroll_layer_init(&scroll_layer, WINDOW_FRAME);
	scroll_layer_set_click_config_onto_window(&scroll_layer, &window); 
	scroll_layer_add_child(&scroll_layer, &content_layer.layer);	
	scroll_layer_set_content_size(&scroll_layer, content_size);
	
	layer_add_child(&window.layer, &scroll_layer.layer);
}

void pbl_main(void *params) 
{
	PebbleAppHandlers handlers = 
	{
		.init_handler = &handle_init
	};
	app_event_loop(params, &handlers);
}
