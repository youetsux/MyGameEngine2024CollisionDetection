#pragma once
#include "Engine/GameObject.h"

class Fbx;

class ChildOden :
    public GameObject
{
    //Fbx* pFbx;
    int hModel;
    public:
        //�R���X�g���N�^
        //�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
        ChildOden(GameObject* parent);

        //������
        void Initialize() override;

        //�X�V
        void Update() override;

        //�`��
        void Draw() override;

        //�J��
        void Release() override;

        void OnCollision(GameObject* pTarget) override;
};

