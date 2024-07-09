class Renderer
{
	// proxy handles
	GW::SYSTEM::GWindow _win;
	GW::GRAPHICS::GRasterSurface _ras;
	// what we need at a minimum to draw a triangle
	float verts[6] =
	{
		   0,   0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};
public:
	Renderer(GW::SYSTEM::GWindow win, GW::GRAPHICS::GRasterSurface ras)
	{
		_win = win;
		_ras = ras;
	}

	void Render(unsigned int* xrgb, unsigned int w, unsigned int h)
	{
		for (size_t y = 0; y < h; y++)
		{
			for (size_t x = 0; x < w; x++)
			{
				auto r = double(x) / (w - 1);
				auto g = double(y) / (h - 1);
				auto b = 0.0;

				unsigned int ir = (int)255.999 * r;
				unsigned int ig = (int)255.999 * g;
				unsigned int ib = (int)255.999 * b;

				xrgb[y * w + x] = RGBtoHEX(0xFF, ir, ig, ib);
			}
		}
	}

	~Renderer()
	{
		// nothing to delete
	}

private:
	unsigned int RGBtoHEX(unsigned int x, int r, int g, int b)
	{
		return ((x & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}
};
