#include "GameObject.h"
#include "Direct3D.h"
#include "../SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name), isDead_(false), pCollider_(nullptr)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();

	//for(auto itr:childList_)
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr=childList_.begin(); itr!=childList_.end(); )
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			//(*itr)->Release();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}

	}

}

void GameObject::ReleaseSub()
{
	Release();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindObject(string objName)
{
	//�l���Ă݂āI
	//�������猩�āA���[�g�W���u��T���āA
	// ���̃��[�g�W���u����S���̎q�����ǂ���_objName��T���I
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(objName);
	return(result);

}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindChildObject(string objName)
{
	if (this->objectName_ == objName)
	{
		return this;
	}
	else
	{
		for (auto itr : childList_)
		{
			GameObject* obj = itr->FindChildObject(objName);
			if(obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

void GameObject::AddCollider(SphereCollider* pColl)
{
	pCollider_ = pColl;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (this->pCollider_ == nullptr || pTarget->pCollider_ == nullptr || this == pTarget)
		return;
	//�����ƃ^�[�Q�b�g�̃R���C�_�[���m�̓����蔻��������I
	// this->position��pTarget->position�̋����@<= this->pCollider.radius_+pTarget->pCollider.radius_
	XMVECTOR me = XMLoadFloat3(&(transform_.position_));
	XMVECTOR ta = XMLoadFloat3(&(pTarget->transform_.position_));

	float dist = XMVectorGetX(XMVector3Length(me-ta)); //this��Target�̋���
	float rDist= this->pCollider_->GetRadius()+ pTarget->pCollider_->GetRadius(); //this��Target�̃R���C�_�[�̔��a�̘a
	if (dist <= rDist)//�Q�_�Ԃ̋����������a�̑����Z
	{
		//onCollision()���Ăԁ��������Ă鎞�̏���
		OnCollision(pTarget);
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//�����ƃ^�[�Q�b�g�̓����蔻��
	if (this->pCollider_ == nullptr)
		return;
	if(pTarget->pCollider_ != nullptr)
		Collision(pTarget);
	//�����ƃ^�[�Q�b�g�̎q�I�u�W�F�N�g�S���̓����蔻��i�ċA�j
	for (auto& itr : pTarget->childList_)
	{
		RoundRobin(itr);
	}
}
