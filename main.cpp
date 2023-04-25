#include <Novice.h>
#include "Matrix4x4.h"
#include "cmath"
const char kWindowTitle[] = "GC2B_04_サワダカズキ";
struct Vector3 {
	float x;
	float y;
	float z;
};

// 1. X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;
	result.m[0][0] = 
}

// 2, Y軸回転移動
Matrix4x4 MakeRotateYMatrix(float radian);

// 3. Z軸回転移動
Matrix4x4 MakeRotateZMatrix(float radian);
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	cosf(radian);
	std::cosf(radian);


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
