#include "RootJob.h"
#include "../SceneManager.h"


RootJob::RootJob(GameObject *parent)
	:GameObject(parent,"RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	//PlayScene* pPlayScene;
	//pPlayScene = new PlayScene(this);
	//pPlayScene->Initialize();
	//childList_.push_back(pPlayScene);
	Instantiate<SceneManager>(this);
	//���������V�[���}�l�[�W���[�ɒu�������āA�V�[��������s������
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
	//for (auto& e : childList_)
	//	e->Draw();
}

void RootJob::Release()
{
}
