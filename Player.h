#pragma once
#include "Engine/GameObject.h"

class Fbx;

class Player :
    public GameObject
{
    int hModel;
//    Fbx* pFbx;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

