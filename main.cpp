#include <Novice.h>
#include "MT3.h"


static const int kWindowHeight = 720;
static const int kWindowWidth = 1280;


const char kWindowTitle[] = "GC2B_04_サワダカズキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Segment segment{ 
		.origin{0.0f,0.5f,-1.0f},
		.diff{0.0f,0.5f,2.0f}
	};
	Vector3 point{ -0.0f,0.0f,0.0f };

	Vector3 rotate{};

	Vector3 translate{};

	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraPosition	 { 0.0f, 0.0f, -10.0f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

	Vector3 kLocalVertices[3]{
		{-0.5f, -0.5f, 0.0f},
		{ 0.0f,  0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f},
	};

	Triangle triangle 
	{
		{{-1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{1.0f,0.0f,0.0f}}
	};

	Plane plane =
	{
		{0.1f,0.1f,0.1f},
		1.0f
	};

	Sphere sphere =
	{
		{0.0f,0.0f,0.0f},
		0.5f
	};

	Line line =
	{
		.origin{0.0f,0.0f,0.0f},
		.diff{1.0f,0.0f,0.0f},
	};

	Vector3 v1{ 1.2f, -3.9f, 2.5f };
	Vector3 v2{ 2.8f, 0.4f, -1.3f };

	AABB aabb1
	{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},
	};

	AABB aabb2
	{
		.min{0.2f,0.2f,0.2f},
		.max{1.0f,1.0f,1.0f},
	};

	aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
	aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
	aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
	aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
	aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
	aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

	aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
	aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
	aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
	aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
	aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
	aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize({ 300, 200 });

	ImGui::Begin("window");


	ImGui::DragFloat3("aabb1.min", &aabb1.min.x, 0.01f);
	ImGui::DragFloat3("aabb1.max", &aabb1.max.x, 0.01f);

	ImGui::DragFloat3("aabb2.min", &aabb2.min.x, 0.01f);
	ImGui::DragFloat3("aabb2.max", &aabb2.max.x, 0.01f);

	 
	ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
	//ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
	//ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);

	//ImGui::DragFloat3("Triangle.v0", &triangle.vertices[0].x, 0.01f);
	//ImGui::DragFloat3("Triangle.v1", &triangle.vertices[1].x, 0.01f);
	//ImGui::DragFloat3("Triangle.v2", &triangle.vertices[2].x, 0.01f);
	//ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.01f);
	//ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);


	//ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);
	//ImGui::DragFloat("Plane.distance", &plane.distance, 0.01f);
	ImGui::End();

	plane.normal = Normalize(plane.normal);

	//IsCollision(sphere, plane);
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f, 0.0f,0.0f }, translate);

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);


	Vector3 start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(segment.origin,segment.diff), worldViewProjectionMatrix), viewportMatrix);
	
	segment.color = IsCollision4(aabb1, aabb2) ? RED : WHITE;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	//Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

	

	DrawGrid(worldViewProjectionMatrix, viewportMatrix);
	//DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
	//DrawSegment(segment, worldViewProjectionMatrix, viewportMatrix, segment.color);
	//DrawTriangle(triangle, worldViewProjectionMatrix, viewportMatrix, WHITE);
	DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, segment.color);
	DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, WHITE);


	//DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix,color);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
