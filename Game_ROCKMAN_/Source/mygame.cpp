/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/
#include <conio.h>
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
//#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
		x = 215;
		y = 255;
		arrow_Location = 0;
	}

	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		backGround.LoadBitmap(IDB_INITBACKGROUND);
		logo.LoadBitmap(IDB_INITGOD);
		gameStart.LoadBitmap(IDB_GAMESTART);
		exit.LoadBitmap(IDB_EXIT);
		arrow.LoadBitmap(IDB_ARROW);

		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_ENTER = 13;
		const char KEY_UP = 38;
		const char KEY_DOWN = 40;

		if (nChar == KEY_ENTER && arrow_Location == 0)
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
		else if (nChar == KEY_ENTER && arrow_Location == 1)  		// Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
		else if (nChar == KEY_DOWN && arrow_Location == 0) {
			arrow_Location = 1;
			y += 30;
		}
		else if (nChar == KEY_UP && arrow_Location == 1) {
			arrow_Location = 0;
			y -= 30;
		}

	}


	void CGameStateInit::OnShow()
	{
		//
		// �K�Wlogo
		//
		backGround.SetTopLeft(0, 0);
		logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		gameStart.SetTopLeft(240, 260);
		exit.SetTopLeft(238, 285);
		arrow.SetTopLeft(x, y);
		backGround.ShowBitmap();
		logo.ShowBitmap();
		gameStart.ShowBitmap();
		exit.ShowBitmap();
		arrow.ShowBitmap();

		//
		// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;

		f.CreatePointFont(80, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f

		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5, 5, "Press Ctrl-Q to pause the Game.");
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �̲׶i�׬�100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), NUMBALLS(28)
	{
		picX = picY = 0;
	}

	CGameStateRun::~CGameStateRun()
	{
	
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;

		//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		
		role.OnMove();
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		role_jump = false;
		role.LoadBitmap();
		background.LoadBitmap(IDB_Background1);
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		//
		// �}�l���J���
		//
		
		//CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
		//CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
		//CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_Z = 90;
		if (nChar == KEY_LEFT)
			role.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			role.SetMovingRight(true);
		if (nChar == KEY_UP && role.GetY() == 430)
			role.SetMovingUp(true);

		if (nChar == KEY_Z && role.HavingBullet(role.BulletIndex()))
		{
			role.SetAttacking(true);
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_Z = 90;
		if (nChar == KEY_LEFT)
			role.SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			role.SetMovingRight(false);
		/*	if (nChar == KEY_UP) {
				role.SetMovingUp(false);
				role_jump = false;
			}*/
		if (nChar == KEY_Z) {
			role.SetAttacking(false);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
	
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		
	}

	void CGameStateRun::OnShow()
	{
		background.ShowBitmap();
		role.OnShow();
	}

	CRole::CRole()
	{
		Initialize();
	}
	void CRole::Initialize()
	{
		const int nX = 5;
		const int nY = 430;
		x = nX;  y = nY;
		for (int i = 0; i < 3; i++) { having_bullet[i] = 0; bulletDirection[i] = 0; }
		bulletIndex = 0;
		direction =  isAttacking = isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
		DisplayBullet(35);
	}
	void CRole::LoadBitmap()
	{
		for (int i = 0; i < 3; i++) bullet[i].AddBitmap(IDB_ICEBAR,RGB(255,255,255));
		
		test.AddBitmap(IDB_Blue);
		standRightAnimation.AddBitmap(IDB_BITMAP8, RGB(255, 255, 255));
		standLeftAnimation.AddBitmap(IDB_ROCKMANLEFT, RGB(255, 255, 255));
		runRightAnimation.AddBitmap(IDB_RUNRIGHT_1, RGB(255, 255, 255));
		runRightAnimation.AddBitmap(IDB_RUNRIGHT_2, RGB(255, 255, 255));
		//runRightAnimation.AddBitmap(IDB_RUNNINGRIGHT_3, RGB(255, 255, 255));
		//runRightAnimation.AddBitmap(IDB_RUNNINGRIGHT_1, RGB(255, 255, 255));
		runLeftAnimation.AddBitmap(IDB_RUNLEFT_1, RGB(255, 255, 255));
		runLeftAnimation.AddBitmap(IDB_RUNLEFT_2, RGB(255, 255, 255));
		//runLeftAnimation.AddBitmap(IDB_RUNNINGLEFT_3, RGB(255, 255, 255));
		jumpRightAnimation.AddBitmap(IDB_JUMPINGRIGHT, RGB(255, 255, 255));
		jumpLeftAnimation.AddBitmap(IDB_JUMPINGLEFT, RGB(255, 255, 255));
		attackLeftAnimation.AddBitmap(IDB_ROCKMANATTACKL, RGB(255, 255, 255));
		attackRightAnimation.AddBitmap(IDB_ROCKMANATTACK, RGB(255, 255, 255));
	}
	void CRole::OnMove()
	{
		const int LEFTWALL_LIMIT = -20;
		const int RIGHTWALL_LIMIT = 617;
		const int STEP_SIZE = 9;
		const int JDSTEP_SIZE = 15;
		const int BULLET_SPEED = 25;
		const int floor = 430;
		const int air = floor - JDSTEP_SIZE * 9;


		if (isMovingRight) direction = true;
		else if (isMovingLeft) direction = false;

		if (isMovingUp && y > air) {
			y -= JDSTEP_SIZE;
			if (isMovingLeft && x - STEP_SIZE > -LEFTWALL_LIMIT) x -= STEP_SIZE;
			if (isMovingRight && x + STEP_SIZE < RIGHTWALL_LIMIT) x += STEP_SIZE;
			if (y == air) {
				SetMovingUp(false);
				SetMovingDown(true);
			}
		}
		if (isMovingDown && y < floor) {
			y += JDSTEP_SIZE;
			if (y == floor) SetMovingDown(false);
		}

		if (isMovingLeft && !isMovingUp) {
			runLeftAnimation.OnMove();
			if ((x - STEP_SIZE) > LEFTWALL_LIMIT) x -= STEP_SIZE;
		}
		if (isMovingRight && !isMovingUp) {
			runRightAnimation.OnMove();
			if ((x + STEP_SIZE) < RIGHTWALL_LIMIT)
				x += STEP_SIZE;
		}
		for (int i = 0; i < 3; i++)
		{
			if (having_bullet[i] == 1)
				if(bulletDirection[i] == 1) bulletX[i] += BULLET_SPEED;
				else bulletX[i] -= BULLET_SPEED;
		}

		BulletReset();
	}
	void CRole::OnShow()
	{	

		for (int i = 0; i < 3; i++) {
			if (having_bullet[i] == 1) {
				bullet[i].SetTopLeft(bulletX[i], bulletY[i]);
				bullet[i].OnShow();
			}
		}
		if (isAttacking) {
			if (direction == 1) {
				attackRightAnimation.SetTopLeft(x, y);
				attackRightAnimation.OnShow();
			}
			else {
				attackLeftAnimation.SetTopLeft(x, y);
				attackLeftAnimation.OnShow();
			}
		}
		else if (isMovingUp || isMovingDown) {
			if (direction) {
				jumpRightAnimation.SetTopLeft(x, y);
				jumpRightAnimation.OnShow();
			}
			else {
				jumpLeftAnimation.SetTopLeft(x, y);
				jumpLeftAnimation.OnShow();
			}
		}

		else if (isMovingRight) {
			runRightAnimation.SetTopLeft(x, y);
			runRightAnimation.OnShow();
		}
		else if (isMovingLeft) {
			runLeftAnimation.SetTopLeft(x, y);
			runLeftAnimation.OnShow();
		}

		else {
			if (direction == true) {
				standRightAnimation.SetTopLeft(x, y);
				standRightAnimation.OnShow();
			}
			else {
				standLeftAnimation.SetTopLeft(x, y);
				standLeftAnimation.OnShow();
			}
		}
	}
	void CRole::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void CRole::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void CRole::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void CRole::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}
	void CRole::SetAttacking(bool flag)
	{
		isAttacking = flag;
	}
	void CRole::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CRole::DisplayBullet(int count)
	{
		for (int i = 0; i < 3; i++) {
			delay_bullet[i] = delay_count[i] = count;
		}
	}
	bool CRole::HavingBullet(int i)
	{
		if (having_bullet[i] == 0)
		{
			bulletDirection[i] = direction;
			bulletX[i] = x; bulletY[i] = y + 17;
			having_bullet[i] = 1;
			bulletIndex += 1;
			if (bulletIndex == 3) bulletIndex = 0;
			return true;
		}
		return false;
	}

	void CRole::BulletReset()
	{
		for (int i = 0; i < 3; i++)
		{
			if (having_bullet[i] == 1)
			{
				if (--delay_bullet[i]<= 10)
				{
					delay_bullet[i] = delay_count[i];
					having_bullet[i] = 0;
				}
			}
		}
	}
	int CRole::BulletIndex()
	{
		return bulletIndex;
	}


	int CRole::GetY()
	{
		return y;
	}
}