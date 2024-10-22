#include "Player.h"
#include "Engine/Fbx.h"
#include "ChildOden.h"
#include "Engine/Input.h"
#include "Model.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"), hModel(-1)
{
}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel = Model::Load("Assets/oden.fbx");
	//pFbx = new Fbx;
	//pFbx->Load("Assets/oden.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	this->transform_.position_.y = -1.5;
	//GameObject *pCo = Instantiate<ChildOden>(this);
	//pCo->SetPosition(2, 0, -1);
	//GameObject* pCo2 = Instantiate<ChildOden>(this);
	//pCo2->SetPosition(-2, 0, 1);
}

void Player::Update()
{
	transform_.rotate_.y += 1;
	//if (transform_.rotate_.y > 60 * 10)
	//{
	//	KillMe();
	//}
	//transform_.position_.x += 0.01;
	if(Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.2;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.2;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject *p = Instantiate<ChildOden>(this);
		p->SetPosition(transform_.position_);
		p->SetScale(0.2, 0.2, 0.2);
	}

}

void Player::Draw()
{
	//pFbx->Draw(transform_);
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
	//pFbx->Release();
	//delete pFbx;
}
