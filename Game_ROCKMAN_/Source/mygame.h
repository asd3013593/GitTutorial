/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
*/

/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID {				// 定義各種音效的編號
	AUDIO_DING,				// 0
	AUDIO_LAKE,				// 1
	AUDIO_NTUT				// 2
};

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class提供可以用鍵盤或滑鼠控制的擦子
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////
class CAyumi {
public:
	CAyumi();
	void Initialize();
	virtual void LoadBitmap();
	void OnMove();
	void OnShow();
	void SetMovingLeft(bool flag);
	void SetMovingRight(bool flag);
	int  GetX();
	int  GetY();
private:
	CAnimation standAnimation;
	int x, y;
};
class CRole {
public:
	CRole();
	void Initialize();
	virtual void LoadBitmap();
	void OnMove();
	void OnShow();
	void SetMovingLeft(bool flag);
	void SetMovingRight(bool flag);
	void SetMovingUp(bool flag);
	void SetMovingDown(bool flag);
	void SetAttacking(bool flag);
	void SetBulletHit(int,bool flag);
	void bulletMoving(bool flag);
	void SetXY(int nx, int ny);
	void DisplayBullet(int);
	bool HavingBullet(int);
	void BulletReset();
	int  BulletIndex();
	bool KeyDownDelay();
	int GetY();
	int GetBulletX(int);
	int GetBulletY(int);
protected:
	CAnimation	standRightAnimation;
	CAnimation	standLeftAnimation;
	CAnimation	runRightAnimation;
	CAnimation	runLeftAnimation;
	CAnimation	jumpRightAnimation;
	CAnimation	jumpLeftAnimation;
	CAnimation	attackRightAnimation;
	CAnimation	attackLeftAnimation;
	CAnimation	bullet[3];
	CAnimation	test;
	int  x, y;
	int  bulletX[3], bulletY[3];
	int  having_bullet[3];
	bool direction;
	bool isMovingLeft;
	bool isMovingRight;
	bool isMovingUp;
	bool isMovingDown;
	bool isAttacking;
	bool bulletHit[3];
	int	 delay_bullet[3];	// 延緩動畫播放速度的計數器
	int	 delay_count[3];	// 動畫播放速度的常數
	int  bulletIndex;		
	int	 bulletDirection[3];
	
};

class CGameStateInit : public CGameState {
public:
	CGameStateInit(CGame *g);
	void OnInit();  								// 遊戲的初值及圖形設定
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作

	//void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
protected:
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	CMovingBitmap backGround;								// csie的logo
	CMovingBitmap logo;
	CMovingBitmap arrow;
	CMovingBitmap gameStart;
	CMovingBitmap exit;
	int arrow_Location;
	int x, y;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState {
public:
	CGameStateRun(CGame *g);
	~CGameStateRun();
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnInit();  								// 遊戲的初值及圖形設定
	void OnKeyDown(UINT, UINT, UINT);
	void OnKeyUp(UINT, UINT, UINT);
	void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
	void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
protected:
	void OnMove();									// 移動遊戲元素
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	const int		NUMBALLS;	// 球的總數
	CMovingBitmap	help;		// 說明圖
	CMovingBitmap	corner;		// 角落圖
	CInteger		hits_left;	// 剩下的撞擊數
	CMovingBitmap	background;
	CMovingBitmap	rock_stand;
	CRole			role;
	CAyumi			ayumi;
	int				picX,picY;
	bool			role_jump;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState {
public:
	CGameStateOver(CGame *g);
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnInit();
protected:
	void OnMove();									// 移動遊戲元素
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	int counter;	// 倒數之計數器
};

}