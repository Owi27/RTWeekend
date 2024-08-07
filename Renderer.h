#include "pch.h"

class Renderer
{
public:
	Renderer(GW::SYSTEM::GWindow win, GW::GRAPHICS::GRasterSurface ras)
	{
		_win = win;
		_ras = ras;
	}

	void Render(unsigned int* xrgb, unsigned int w, unsigned int h)
	{
		auto aspectRatio = 16.f / 9.f;
		int samplesPerPixel = 100;

		//world
		HittableList world;
		world.Add(make_shared<Sphere>(vec3{ 0, 0, -1 }, .5f));
		//world.Add(make_shared<Sphere>(vec3{ 0, -100.5, -1 }, 100));

		//cam
		float focalLength = 1.f;
		float viewportHeight = 2.f;
		float viewportWidth = viewportHeight * (double(w) / h);

		_pixelSamplesScale = 1.f / samplesPerPixel;

		_camCenter = { 0, 0, 0 };

		//Calculate the vectors across the horizontal and down the vertical viewport edges.
		vec3 viewportU = { viewportWidth, 0 ,0 };
		vec3 viewportV = { 0, -viewportHeight, 0 };

		//Calculate the horizontal and vertical delta vectors from pixel to pixel.
		_pixelDeltaU;
		_pixelDeltaV;
		{
			pVec2D::Scale3F(viewportU, (1.f / w), _pixelDeltaU);
			pVec2D::Scale3F(viewportV, (1.f / h), _pixelDeltaV);
		}

		// Calculate the location of the upper left pixel.
		vec3 viewportUpperLeft;
		{
			vec3 v1, v2;
			pVec2D::Subtract3F(_camCenter, vec3{ 0, 0, focalLength }, viewportUpperLeft);
			pVec2D::Scale3F(viewportU, .5f, v1);
			pVec2D::Subtract3F(viewportUpperLeft, v1, viewportUpperLeft);
			pVec2D::Scale3F(viewportV, .5f, v2);
			pVec2D::Subtract3F(viewportUpperLeft, v2, viewportUpperLeft);
		}

		_pixel00Loc;
		{
			vec3 v;
			pVec2D::Add3F(_pixelDeltaU, _pixelDeltaV, v);
			pVec2D::Scale3F(v, .5f, v);
			pVec2D::Add3F(viewportUpperLeft, v, _pixel00Loc);
		}

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				//std::cout << x << ' ' << y << '\n';
				vec3 pixColor = { 0, 0, 0 };
				for (size_t sample = 0; sample < samplesPerPixel; sample++)
				{
					Ray r = GetRay(x, y);
					pVec2D::Add3F(pixColor, RayColor(r, world), pixColor);
				}

				pVec2D::Scale3F(pixColor, _pixelSamplesScale, pixColor);
				pixColor = { fabs(pixColor.x), fabs(pixColor.y), fabs(pixColor.z) };
				xrgb[y * w + x] = RGBtoHEX(0xFF, pixColor);

			}
		}
	}

	~Renderer()
	{
		// nothing to delete
	}

private:
	// proxy handles
	GW::SYSTEM::GWindow _win;
	GW::GRAPHICS::GRasterSurface _ras;
	vec3 _camCenter;
	vec3 _pixel00Loc;
	vec3 _pixelDeltaU;
	vec3 _pixelDeltaV;
	float _pixelSamplesScale;

	Ray GetRay(int x, int y) const
	{
		vec3 offset = SampleSquare();

		vec3 v[2], pixelSample;
		pVec2D::Scale3F(_pixelDeltaU, x + offset.x, v[0]);
		pVec2D::Scale3F(_pixelDeltaV, y + offset.y, v[1]);
		pVec2D::Add3F(_pixel00Loc, v[0], v[0]);
		pVec2D::Add3F(v[0], v[1], pixelSample);

		vec3 rayOrigin = _camCenter;
		vec3 rayDirection;
		pVec2D::Subtract3F(pixelSample, rayOrigin, rayDirection);

		return Ray(rayOrigin, rayDirection);
	}

	vec3 SampleSquare() const
	{
		return { RandomFloat() - .5f, RandomFloat() - .5f, 0 };
	}

	vec3 RayColor(Ray& r, const Hittable& world) const
	{
		HitRecord rec;

		if (world.Hit(r, Interval(0, INFINITY), rec))
		{
			vec3 out;
			//vec3 direction = RandomOnHemisphere(rec.normal);
			//Ray ray(rec.point, direction);
			pVec2D::Scale3F(vec3{ rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1 }, .5f, out);

			return out;
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
		static const Interval intensity(0.000, 0.999);
		unsigned int r = (int)256 * intensity.Clamp(color.x);
		unsigned int g = (int)256 * intensity.Clamp(color.y);
		unsigned int b = (int)256 * intensity.Clamp(color.z);

		return ((x & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}
};
