#include "pch.h"

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
		auto aspectRatio = 16.f / 9.f;

		//cam
		float focalLength = 1.f;
		float viewportHeight = 2.f;
		float viewportWidth = viewportHeight * (double(w) / h);
		vec3 camCenter = { 0, 0, 0 };

		//Calculate the vectors across the horizontal and down the vertical viewport edges.
		vec3 viewportU = { viewportWidth, 0 ,0 };
		vec3 viewportV = { 0, -viewportHeight, 0 };

		//Calculate the horizontal and vertical delta vectors from pixel to pixel.
		vec3 pixelDeltaU;
		vec3 pixelDeltaV;
		{
			pVec2D::Scale3F(viewportU, (1.f / w), pixelDeltaU);
			pVec2D::Scale3F(viewportV, (1.f / h), pixelDeltaV);
		}

		// Calculate the location of the upper left pixel.
		vec3 viewportUpperLeft;
		{
			vec3 v1, v2;
			pVec2D::Subtract3F(camCenter, vec3{ 0, 0, focalLength }, viewportUpperLeft);
			pVec2D::Scale3F(viewportU, .5f, v1);
			pVec2D::Subtract3F(viewportUpperLeft, v1, viewportUpperLeft);
			pVec2D::Scale3F(viewportV, .5f, v2);
			pVec2D::Subtract3F(viewportUpperLeft, v2, viewportUpperLeft);
		}

		vec3 pixel00Loc;
		{
			vec3 v;
			pVec2D::Add3F(pixelDeltaU, pixelDeltaV, v);
			pVec2D::Scale3F(v, .5f, v);
			pVec2D::Add3F(viewportUpperLeft, v, pixel00Loc);
		}

		for (size_t y = 0; y < h; y++)
		{
			for (size_t x = 0; x < w; x++)
			{
				vec3 pixelCenter;
				{
					vec3 v1;
					pVec2D::Scale3F(pixelDeltaU, x, v1);
					pVec2D::Add3F(pixel00Loc, v1, pixelCenter);
					pVec2D::Scale3F(pixelDeltaV, y, v1);
					pVec2D::Add3F(pixelCenter, v1, pixelCenter);
				}

				vec3 rayDirection;
				{
					pVec2D::Subtract3F(pixelCenter, camCenter, rayDirection);
				}

				Ray r(camCenter, rayDirection);

				vec3 pixColor = RayColor(r);
				xrgb[y * w + x] = RGBtoHEX(0xFF, pixColor);
			}
		}
	}

	~Renderer()
	{
		// nothing to delete
	}

private:

	bool HitSphere(vec3& center, float radius, Ray& r)
	{
		vec3 oc;
		float a, b, c;
		pVec2D::Subtract3F(center, r.Origin(), oc);
		pVec2D::Dot3F(r.Direction(), r.Direction(), a);
		pVec2D::Dot3F(r.Direction(), oc, b);
		b *= -2.f;
		pVec2D::Dot3F(oc, oc, c);
		c -= radius * radius;

		float discriminant = b * b - 4 * a * c;
		return (discriminant >= 0);
	}

	vec3 RayColor(Ray& r)
	{
		vec3 center = { 0.f,0.f,-1.f };
		if (HitSphere(center, 0.5, r))
		{
			return { 1, 0, 0 };
		}

		vec3 unitDirection;
		pVec2D::Normalize3F(r.Direction(), unitDirection);
		float a = .5f * (unitDirection.y + 1.f);

		vec3 out, v1, v2;
		pVec2D::Scale3F(vec3{ 1.f, 1.f, 1.f }, 1.f - a, v1);
		pVec2D::Scale3F(vec3{ .5f, .7f, 1.f }, a, v2);
		pVec2D::Add3F(v1, v2, out);

		return out;
	}

	unsigned int RGBtoHEX(unsigned int x, vec3 color)
	{
		unsigned int r = (int)255.999 * color.x;
		unsigned int g = (int)255.999 * color.y;
		unsigned int b = (int)255.999 * color.z;

		return ((x & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}
};
