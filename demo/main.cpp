#include <MeshReconstruction.h>
#include <IO.h>

using namespace MeshReconstruction;

int main()
{
	auto sphereSdf = [](Vec3 const& pos)
	{
		auto const Radius = 1.0;
		return pos.Norm() - Radius;
	};
	auto boxSdf = [](Vec3 const& pos)
	{
		Vec3 const boxsize = { 0.250,0.250,0.250};
		Vec3 q = pos.Fabs() - boxsize;
		Vec3 v1 = { fmax(q.x, 0.0), fmax(q.y, 0.0), fmax(q.z, 0.0) };
		auto v2 = fmin(fmax(q.x, fmax(q.y, q.z)), 0.0);
		return v1.Norm()+v2;
	};
	Rect3 domain;
	domain.min = { -1.5, -1.5, -1.5 };
	domain.size = {3.2, 3.2, 3.2};

	Vec3 cubeSize{ 0.05, 0.05, 0.05 };

	auto mesh = MarchCube(boxSdf, domain, cubeSize,-0.0125);
	WriteObjFile(mesh, "box.obj");
}