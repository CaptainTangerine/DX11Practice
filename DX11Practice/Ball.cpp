#include "pch.h"
#include "Ball.h"
#include "Mesh.h"
#include "Transform.h"
#include "Sphere.h"

void UBall::Initialize(ID3D11Device& Device)
{
	UMesh* SimpleMesh = AddComponent<UMesh>();
	SimpleMesh->Load(Device, sphere_vertices, sizeof(sphere_vertices) / sizeof(FVertexSimple));
}
