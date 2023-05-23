#include <Novice.h>
#include "Vector3.h"

struct Line 
{
	Vector3 origin; //!< 始点
	Vector3 diff; //!< 終点への差分ベクトル
};

struct Ray
{
	Vector3 origin; //!< 始点
	Vector3 diff; //!< 終点への差分ベクトル
};

struct Segment
{
	Vector3 origin; //!< 始点
	Vector3 diff; //!< 終点への差分ベクトル
};

Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
const char kWindowTitle[] = "GC2B_04_サワダカズキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

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
	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	
	Sphere pointSphere{ point,0.01f }; // 1cmの球を描画
	Sphere closestPointSphere{ closestPoint,0.01f };
	DrawSphere(pointSphere, viewProjectMatrix, viewportMatrix,RED);
	DrawSphere(closestPointSphere, viewProjectMatrix, viewportMatrix, BLACK);


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
