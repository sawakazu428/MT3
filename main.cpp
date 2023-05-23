#include <Novice.h>
#include "Matrix4x4.h"
#include "cmath"
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include "math.h"
struct Sphere
{
	Vector3 center; //!< 中心点
	float radius;   //!< 半径
};

// 1. 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;
	//float theta = 3.14f;
	float tan = std::tanf(fovY / 2);
	float cot = 1.0f / tan;

	result = {
		1.0f / aspectRatio * cot, 0.0f, 0.0f, 0.0f,
		0.0f, cot, 0.0f, 0.0f,
		0.0f, 0.0f, farClip / (farClip - nearClip), 1.0f,
		0.0f, 0.0f, (-nearClip * farClip) / (farClip - nearClip),0.0f
	};
	return result;
};

// 2. 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result;
	result = {
		2.0f / (right - left), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (top - bottom), 0.0f ,0.0f,
		0.0f, 0.0f, 1.0f / (farClip - nearClip), 0.0f,
		(left + right) / (left - right),  (top + bottom) / (bottom - top), nearClip / (nearClip - farClip), 1.0f
	};
	return result;
};

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;
	result = {
		width / 2.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -height / 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, maxDepth - minDepth, 0.0f,
		left + (width / 2.0f), top + (height / 2.0f), minDepth ,1.0f
	};
	return result;
};

//Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height)
//{
//	Matrix4x4 result;
//	result = { width / 2.0f, 0.0f,	0.0f, 0.0f,
//		0.0f, -height / 2.0f, 0.0f, 0.0f,
//		1.0f, 0.0f ,0.0f, 1.0f,
//		left + (width / 2.0f), top + (height / 2.0f), 0.0f, 1.0f
//	};
//	return result;
//}

void DrawGrid(const Matrix4x4& ViewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;                                     // Gridの半分の幅
	const uint32_t kSubdvision = 10;                                       // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdvision); // 一つ分の長さ
	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdvision; ++xIndex)
	{
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		// スクリーン座標系まで変換をかける
		// 変換した座標を使って表示色は薄い灰色(0xAAAAAAFF),原点は黒ぐらいが良いが、何でも良い
		Novice::DrawLine(xIndex,xIndex,kGridEvery, kGridEvery, 0xAAAAAAFF);
	}
	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdvision; ++zIndex)
	{
	// 奥から手前が左右に変わるだけ
		//Novice::DrawLine();
	}

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& ViewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	float pi = M_PI / 1.0f;
	const uint32_t kSubdvision = 10; // 分割数
	const float kLonEvery = 2.0f;    // Gridの半分の幅
	const float kLatEvery = 2;         // 一つ分の長さ



	// 緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdvision; ++latIndex)
	{
		float lat = -pi / 2.0f + kLatEvery * latIndex; // 現在の緯度
		// 緯度の方向に分割θ ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdvision; ++lonIndex)
		{
			float lon = lonIndex * kLonEvery; // 現在の経度
			// world座標系でのa,b,cを求める
			Vector3 a, b, c;



			// a,b,cをScreen座標系まで変換...
			// ab,bcで線を引く
			//Novice::DrawLine(color);
			//Novice::DrawLine(color);
		}
	}
}
const char kWindowTitle[] = "GC2B_04_サワダカズキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
