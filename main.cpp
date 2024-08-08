#include "pch.h"
#include "renderer.h"
// open some namespaces to compact the code a bit
using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;
// allocate an 800x600 pixel buffer for display (keep centered on Resize)
unsigned int XRGB[800 * 600] = { 0, };
// lets pop a window and use GRasterSurface to upload an image with a triangle
int main(){
	GWindow win;
	GEventResponder msgs;
	GRasterSurface raster;
	if (+win.Create(0, 0, 800, 600, GWindowStyle::WINDOWEDBORDERED))
	{
		win.SetWindowName("Raytracing in One Weekend : Owi | Gateware");

		unsigned int color = 0xFFFFFF00;
		msgs.Create([&](const GW::GEvent& e) {
			GW::SYSTEM::GWindow::Events q;
			if (+e.Read(q) && q == GWindow::Events::RESIZE)
			{// Clear the screen broder to a swapping color
				color = ~color;
			}
			});
		win.Register(msgs);
		if (+raster.Create(win))
		{
			Renderer renderer(win, raster);
			// if we had dynamic resolution or animations we would place this inside the loop
			for (int i = 0; i < 800 * 600; i++)
				XRGB[i] = 0xFFFA88FF; // pink
			renderer.Render(XRGB, 800, 600);
			while (+win.ProcessWindowEvents())
			{
				raster.Clear(color);
				raster.SmartUpdateSurface(XRGB, 800 * 600, 800, ALIGN_X_CENTER | ALIGN_Y_CENTER);
				raster.Present();
			}
		}
	}
	return 0; // that's all folks
}

