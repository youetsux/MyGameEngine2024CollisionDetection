#pragma once
#include "Engine/GameObject.h"
class TestScene :
    public GameObject
{
    public:
        //�R���X�g���N�^
        //�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
        TestScene(GameObject * parent);
        void Initialize() override;
        void Update() override;
        void Draw() override;
        void Release() override;
};

