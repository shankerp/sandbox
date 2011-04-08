#include <gtk/gtk.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int nScreens;
	int i, j;
	GdkDisplay *display;

	gtk_init (&argc, &argv);

	display = gdk_display_get_default();
	nScreens = gdk_display_get_n_screens(display);
	printf("Display has %d screens\n", nScreens);

	for (i=0; i<nScreens; i++)
	{
		GdkScreen *screen;
		GdkRectangle screen_rect;
		int screen_w, screen_h;
		int nMonitors;

		screen = gdk_display_get_screen(display, i);
		screen_w = gdk_screen_get_width_mm(screen);
		screen_h = gdk_screen_get_height(screen);
		nMonitors = gdk_screen_get_n_monitors(screen);

		printf("    Screen %d: %dmm x %dmm --  has %d monitors\n", i, screen_w, screen_h, nMonitors);
		for (j=0; j<nMonitors; j++)
		{
			GdkRectangle monitor_rect;
			int monitor_w, monitor_h;
			gdk_screen_get_monitor_geometry(screen, j, &monitor_rect);
			monitor_w = gdk_screen_get_monitor_width_mm(screen, j);
			monitor_h = gdk_screen_get_monitor_height_mm(screen, j);

			printf("        Monitor %d: %d x %d -- %dmm x %dmm\n", j,
					monitor_rect.width, monitor_rect.height,
					monitor_w, monitor_h);
		}
	}
}
